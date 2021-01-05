/**
* \file
* Cookies.
* 
*/

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include <cstdlib>
#include <ctime>

#include <curl-asio.h>


class YesNo
{
public:
    explicit YesNo(bool yn) : yesno(yn) {}
		std::string operator()() const {
        return yesno ? "Yes" : "No";
    }
		friend std::ostream &operator<<(std::ostream &strm, const YesNo &yn) {
        strm << yn();
        return strm;
    }
private:
    bool yesno;
};

struct MyCookie
{
	std::string name;
	std::string value;
	std::string domain;
	std::string path;
	time_t expires;
	bool tail;
	bool secure;
};

std::ostream &
operator<<(std::ostream &strm, const MyCookie &cook)
{
	strm << "Cookie: '" << cook.name << "' (secure: " << YesNo(cook.secure) << ", tail: "
		<< YesNo(cook.tail) << ") for domain: '" << cook.domain << "', "
		<< "path: '" << cook.path << "'.\n";
	strm << "Value: '" << cook.value << "'.\n";
	strm << "Expires: '" << ctime(&cook.expires) << "'.\n";

	return strm;
}

std::vector<std::string> &
split_cookie_str(const std::string &str, std::vector<std::string> &in)
{
	std::string part;

	std::istringstream strm(str);
	while (getline(strm, part, '\t'))
		in.push_back(part);

	return in;
}

std::vector<std::string>
splitCookieStr(const std::string &str)
{
	std::vector<std::string> split;
	split_cookie_str(str, split);
	return split;
}

std::vector<std::string> &
splitCookieStr(const std::string &str, std::vector<std::string> &in)
{
	return split_cookie_str(str, in);
}

int StrToInt(const std::string &str)
{
	std::istringstream strm(str);
	int i = 0;
	if (!(strm >> i)) {
		throw std::runtime_error("Unable to convert string '" + str + "' to integer!");
	}
	return i;
}

MyCookie
MakeCookie(const std::string &str_cookie)
{
	std::vector<std::string> vC = splitCookieStr(str_cookie);
	MyCookie cook;

	cook.domain = vC[0];
	cook.tail = vC[1] == "TRUE";
	cook.path = vC[2];
	cook.secure = vC[3] == "TRUE";
	cook.expires = StrToInt(vC[4]);
	cook.name = vC[5];
	cook.value = vC[6];

	return cook;
}

template<class OS>
OS& operator<<(OS& os, const std::vector<std::string>& vec){
	os<<"{\n";
	std::for_each(vec.begin(), vec.end(), [&os](const std::string& v){
		os<<v<<"\n";
	});
	os<<"}\n";
	return os;
}

int
main(void)
{
	try
	{
		curl::initialization initer();
		curl::easy request;
		// curl::string_list cookieList;
		std::vector<std::string> cookieslist;

		// a cookie as in HTTP header
		cookieslist.push_back("Set-Cookie: GMAIL_AT=EXPIRED;expires=Sun, 17-Jan-2038 19:14:07 GMT; path=/; domain=.google.com");

		// a Netscape style cookie with \t
		cookieslist.push_back(".google.com\tTRUE\t/\tFALSE\t2147483647\tLSID\tI like you GOOGLE");

		// a Netscape style cookie with tabs in string
		cookieslist.push_back(".yahoo.com	TRUE	/	FALSE	0	YAHOO_COOKIE	I like you yahoo, too");

		request.set_url("http://www.google.com");
		request.set_file_time(true);
		request.set_verbose(true);

		// loop throught the cookies and add one by one
		//
		std::for_each(cookieslist.begin(), cookieslist.end(), [&request](const std::string &str){
			request.set_cookie_list(str);
		});
		
		request.perform();

		// see what cookies we got
		//
		std::cout << "\nCookies from cookie engine:" << std::endl;
		// std::cout<<request.get_cookielist()<<std::endl;
		auto cookies = request.get_cookielist();

		std::for_each(cookies.begin(), cookies.end(), [](const std::string &str){
			static size_t i =0;
			std::cout << "[" << i++ << "]: " << MakeCookie(str) << std::endl;
		});
		// std::list<std::string> cookies;
		// curlpp::infos::CookieList::get(request, cookies);
		// int i = 1;
		// for (std::list<std::string>::const_iterator it = cookies.begin();
		// 	it != cookies.end();
		// 	++it, i++)
		// {
		// 	std::cout << "[" << i << "]: " << MakeCookie(*it) << std::endl;
		// }

		exit(EXIT_SUCCESS);
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	catch(...)
	{
		std::cout << "unknow exception" << std::endl;
	}
}

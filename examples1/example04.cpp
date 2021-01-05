/*
 *    Copyright (c) <2002-2005> <Jean-Philippe Barrette-LaPierre>
 *    
 *    Permission is hereby granted, free of charge, to any person obtaining
 *    a copy of this software and associated documentation files 
 *    (curlpp), to deal in the Software without restriction, 
 *    including without limitation the rights to use, copy, modify, merge,
 *    publish, distribute, sublicense, and/or sell copies of the Software,
 *    and to permit persons to whom the Software is furnished to do so, 
 *    subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included
 *    in all copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 *    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
* \file
* Getting options using curlpp::infos.
* 
*/


#include <cstdlib>

#include <curl-asio.h>
#include <algorithm>
#include <fstream>

template<class OS>
OS& operator<<(OS& os, const std::vector<std::string>& vec){
	os<<"{\n";
	std::for_each(vec.begin(), vec.end(), [&os](const std::string& v){
		os<<v<<"\n";
	});
	os<<"}\n";
	return os;
}
 

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cerr << "Example 04: Wrong number of arguments" << std::endl 
			<< "Example 04: Usage: example04 url" 
			<< std::endl;
		return EXIT_FAILURE;
	}
	char *url = argv[1];

	try 
	{
		curl::initialization initer();
		curl::easy request;


		request.set_verbose(true);
		request.set_url(url);
		request.set_sink(std::make_shared<std::ofstream>("./tmp"));

		request.perform();

		// std::string effURL =request.get_effective_url();

		// std::cout << "Effective URL: " << effURL << std::endl;

		//other way to retreive URL
		std::cout << std::endl 
			<< "Effective URL: " 
			<< request.get_effective_url()
			<< std::endl;

		std::cout << "Response code: " 
			<< request.get_response_code()
			<< std::endl;

		std::cout << "SSL engines: " 
			<< request.get_ssl_engines()
			<< std::endl;
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	catch(...)
	{
		std::cout << "unknow exception" << std::endl;
	}

	return 0;
}


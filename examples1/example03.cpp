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
* DebugFunction option using functor as a callback.
*/


#include <cstdlib>

#include <curl-asio.h>

class MyWindow
{
public:
	int writeDebug(curl_infotype, char *data, size_t size)
	{
		fprintf(stderr, "Debug: ");
		fwrite(data, size, 1, stderr);
		return size;
	}
};

int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		std::cerr	<< "Example 3: Wrong number of arguments" << std::endl 
							<< "Example 3: Usage: example3 url" 
							<< std::endl;
		return EXIT_FAILURE;
	}
	char *url = argv[1];

	MyWindow myWindow;

	try 
	{
		curl::initialization initer();
		curl::easy request;


		request.set_verbose(true);
		request.set_debug_data(&myWindow);
		request.set_debug_function([](native::CURL*, native::curl_infotype info, char* data, size_t size, void* userp)->int{
			MyWindow* myWindow = (MyWindow*)userp;
			return myWindow->writeDebug(info, data, size);
		});
		request.set_url(url)

		request.perform();
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


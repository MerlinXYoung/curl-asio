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
* Uploading of string.
* ReadFunction option using functor.
* Setting custom headers.
*/


#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <curl-asio.h>
#include <stringstream>
 
/*
   anonymous namespace to prevent name clash in case other examples using the same global entities
   would be compiled in the same project
*/


int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		std::cerr << "Example 2: Missing argument" << std::endl 
							<< "Example 2: Usage: example02 url string-to-send" 
							<< std::endl;
		return EXIT_FAILURE;
	}

	char *url = argv[1];
	std::shared_ptr<std::istringstream> iss(new std::istringstream(argv[2]));
	size_t size = strlen(argv[2]);

	char buf[50];
	try
	{
		curl::initialization initer();
		curl::easy request;

		curl::string_list headers
		headers.add("Content-Type: text/*"); 
		sprintf(buf, "Content-Length: %lu", strlen(argv[2])); 
		headers.add(buf);

		request.set_verbose(true);
		// request.setOpt(new ReadFunction(curlpp::types::ReadFunctionFunctor(readData)));
		request.set_source(iss);
		request.set_infile_size(size);
		request.set_upload(true);
		request.set_headers(headers);
		request.set_url(url);

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


/**
* \file
* The most simple example.
* 
*/

#include <curl-asio.h>


int main(int, char **)
{
	try
	{
		// That's all that is needed to do cleanup of used resources (RAII style).
		curl::initialization initer();

		// Our request to be sent.
		curl::easy myRequest;

		// Set the URL.
		myRequest.set_url("http://example.com");

		// Send request and get a result.
		// By default the result goes to standard output.
		myRequest.perform();
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

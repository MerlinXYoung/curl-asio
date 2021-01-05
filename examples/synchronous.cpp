#include <curl-asio.h>
#include <fstream>
#include <cinttypes>

int main(int argc, char* argv[])
{
	// expect two arguments
	if (argc != 3)
	{
		std::cerr << "usage: " << argv[0] << " url file" << std::endl;
		return 1;
	}

	// this example program downloads argv[1] to argv[2]
	char* url = argv[1];
	char* file_name = argv[2];
	
	curl::initialization initer();
	// start by creating an io_service object
	asio::io_service io_service;
	
	// construct an instance of curl::easy
	curl::easy downloader;//(/*io_service*/);

	// set the object's properties
	downloader.set_url(url);
	downloader.set_sink(std::make_shared<std::ofstream>(file_name, std::ios::binary));
	downloader.set_progress_callback([file_name](curl::native::curl_off_t dltotal, curl::native::curl_off_t dlnow, curl::native::curl_off_t ultotal, curl::native::curl_off_t ulnow)->bool{
		printf("\r%s:%8" PRId64 "/%" PRId64, file_name, dlnow, dltotal);
		fflush(stdout);
		// if(dlnow == dltotal && dlnow != 0 )
		// {	
		// 	printf("\n");
		// }
		return true;
	});
	// download the file
	asio::error_code ec;
	downloader.perform(ec);

	// error handling
	if (!ec)
	{
		std::cerr << "Download succeeded" << std::endl;
	}
	else
	{
		std::cerr << "Download failed: " << ec.message() << std::endl;
	}
	
	return 0;
}

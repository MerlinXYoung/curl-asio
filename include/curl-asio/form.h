/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	C++ wrapper for constructing libcurl forms
*/

#pragma once

#include "config.h"
#include <asio/detail/noncopyable.hpp>
#include <asio/error_code.hpp>
#include <string>
#include <memory>
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
#include "initialization.h"
#endif
#include "native.h"

namespace curl
{
	class CURLASIO_API form:
		public std::enable_shared_from_this<form>,
		public asio::noncopyable
	{
	public:
		form();
		~form();

		inline native::curl_httppost* native_handle() { return post_; };

		void add_content(const std::string& key, const std::string& content);
		void add_content(const std::string& key, const std::string& content, asio::error_code& ec);
		void add_content(const std::string& key, const std::string& content, const std::string& content_type);
		void add_content(const std::string& key, const std::string& content, const std::string& content_type, asio::error_code& ec);
		void add_file(const std::string& key, const std::string& file_path);
		void add_file(const std::string& key, const std::string& file_path, asio::error_code& ec);
		void add_file(const std::string& key, const std::string& file_path, const std::string& content_type);
		void add_file(const std::string& key, const std::string& file_path, const std::string& content_type, asio::error_code& ec);
		void add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name);
		void add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, asio::error_code& ec);
		void add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, const std::string& content_type);
		void add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, const std::string& content_type, asio::error_code& ec);
		void add_file_content(const std::string& key, const std::string& file_path);
		void add_file_content(const std::string& key, const std::string& file_path, asio::error_code& ec);
		void add_file_content(const std::string& key, const std::string& file_path, const std::string& content_type);
		void add_file_content(const std::string& key, const std::string& file_path, const std::string& content_type, asio::error_code& ec);

	private:
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
		initialization::ptr initref_;
#endif
		native::curl_httppost* post_{nullptr};
		native::curl_httppost* last_{nullptr};
	};
}

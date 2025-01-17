/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	C++ wrapper for constructing libcurl forms
*/

#include <curl-asio/form.h>
#include <curl-asio/error_code.h>
#include <asio.hpp>


using namespace curl;

form::form():
	post_(nullptr),
	last_(nullptr)
{
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
	initref_ = initialization::ensure_initialization();
#endif
}

form::~form()
{
	if (post_)
	{
		native::curl_formfree(post_);
		post_ = nullptr;
	}
}

void form::add_content(const std::string& key, const std::string& content)
{
	asio::error_code ec;
	add_content(key, content, ec);
	asio::detail::throw_error(ec, "add_content");
}

void form::add_content(const std::string& key, const std::string& content, asio::error_code& ec)
{
	ec = asio::error_code(native::curl_formadd(&post_, &last_,
		native::CURLFORM_COPYNAME, key.c_str(),
		native::CURLFORM_NAMELENGTH, key.length(),
		native::CURLFORM_COPYCONTENTS, content.c_str(),
		native::CURLFORM_CONTENTSLENGTH, content.length(),
		native::CURLFORM_END
		), asio::system_category());
}

void form::add_content(const std::string& key, const std::string& content, const std::string& content_type)
{
	asio::error_code ec;
	add_content(key, content, content_type, ec);
	asio::detail::throw_error(ec, "add_content");
}

void form::add_content(const std::string& key, const std::string& content, const std::string& content_type, asio::error_code& ec)
{
	ec = asio::error_code(native::curl_formadd(&post_, &last_,
		native::CURLFORM_COPYNAME, key.c_str(),
		native::CURLFORM_NAMELENGTH, key.length(),
		native::CURLFORM_COPYCONTENTS, content.c_str(),
		native::CURLFORM_CONTENTSLENGTH, content.length(),
		native::CURLFORM_CONTENTTYPE, content_type.c_str(),
		native::CURLFORM_END
		), asio::system_category());
}

void form::add_file(const std::string& key, const std::string& file_path)
{
	asio::error_code ec;
	add_file(key, file_path, ec);
	asio::detail::throw_error(ec, "add_file");
}

void form::add_file(const std::string& key, const std::string& file_path, asio::error_code& ec)
{
	ec = asio::error_code(native::curl_formadd(&post_, &last_,
		native::CURLFORM_COPYNAME, key.c_str(),
		native::CURLFORM_NAMELENGTH, key.length(),
		native::CURLFORM_FILE, file_path.c_str(),
		native::CURLFORM_END
		), asio::system_category());
}

void form::add_file(const std::string& key, const std::string& file_path, const std::string& content_type)
{
	asio::error_code ec;
	add_file(key, file_path, content_type, ec);
	asio::detail::throw_error(ec, "add_file");
}

void form::add_file(const std::string& key, const std::string& file_path, const std::string& content_type, asio::error_code& ec)
{
	ec = asio::error_code(native::curl_formadd(&post_, &last_,
		native::CURLFORM_COPYNAME, key.c_str(),
		native::CURLFORM_NAMELENGTH, key.length(),
		native::CURLFORM_FILE, file_path.c_str(),
		native::CURLFORM_CONTENTTYPE, content_type.c_str(),
		native::CURLFORM_END
		), asio::system_category());
}

void form::add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name)
{
	asio::error_code ec;
	add_file_using_name(key, file_path, file_name, ec);
	asio::detail::throw_error(ec, "add_file_using_name");
}

void form::add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, asio::error_code& ec)
{
	ec = asio::error_code(native::curl_formadd(&post_, &last_,
		native::CURLFORM_COPYNAME, key.c_str(),
		native::CURLFORM_NAMELENGTH, key.length(),
		native::CURLFORM_FILE, file_path.c_str(),
		native::CURLFORM_FILENAME, file_name.c_str(),
		native::CURLFORM_END
		), asio::system_category());
}

void form::add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, const std::string& content_type)
{
	asio::error_code ec;
	add_file_using_name(key, file_path, file_name, content_type, ec);
	asio::detail::throw_error(ec, "add_file_using_name");
}

void form::add_file_using_name(const std::string& key, const std::string& file_path, const std::string& file_name, const std::string& content_type, asio::error_code& ec)
{
	ec = asio::error_code(native::curl_formadd(&post_, &last_,
		native::CURLFORM_COPYNAME, key.c_str(),
		native::CURLFORM_NAMELENGTH, key.length(),
		native::CURLFORM_FILE, file_path.c_str(),
		native::CURLFORM_FILENAME, file_name.c_str(),
		native::CURLFORM_CONTENTTYPE, content_type.c_str(),
		native::CURLFORM_END
		), asio::system_category());
}

void form::add_file_content(const std::string& key, const std::string& file_path)
{
	asio::error_code ec;
	add_file_content(key, file_path, ec);
	asio::detail::throw_error(ec, "add_file_content");
}

void form::add_file_content(const std::string& key, const std::string& file_path, asio::error_code& ec)
{
	ec = asio::error_code(native::curl_formadd(&post_, &last_,
		native::CURLFORM_COPYNAME, key.c_str(),
		native::CURLFORM_NAMELENGTH, key.length(),
		native::CURLFORM_FILECONTENT, file_path.c_str(),
		native::CURLFORM_END
		), asio::system_category());
}

void form::add_file_content(const std::string& key, const std::string& file_path, const std::string& content_type)
{
	asio::error_code ec;
	add_file_content(key, file_path, content_type, ec);
	asio::detail::throw_error(ec, "add_file_content");
}

void form::add_file_content(const std::string& key, const std::string& file_path, const std::string& content_type, asio::error_code& ec)
{
	ec = asio::error_code(native::curl_formadd(&post_, &last_,
		native::CURLFORM_COPYNAME, key.c_str(),
		native::CURLFORM_NAMELENGTH, key.length(),
		native::CURLFORM_FILECONTENT, file_path.c_str(),
		native::CURLFORM_CONTENTTYPE, content_type.c_str(),
		native::CURLFORM_END
		), asio::system_category());
}

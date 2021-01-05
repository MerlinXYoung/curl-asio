/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	Helper to automatically initialize and cleanup libcurl resources
*/

#pragma once

#include "config.h"
#include <asio/detail/noncopyable.hpp>
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
#include <memory>
#endif
namespace curl
{
	class initialization:public asio::noncopyable
	{
	public:
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
		typedef std::shared_ptr<initialization> ptr;
		static ptr ensure_initialization();
#endif
		~initialization();
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
	protected:
#endif
		initialization();
	};
}

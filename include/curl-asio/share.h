/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	C++ wrapper for libcurl's share interface
*/

#pragma once

#include "config.h"
#include <asio/detail/noncopyable.hpp>
#include <mutex>
#include <memory>
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
#include "initialization.h"
#endif
#include "native.h"

namespace curl
{
	class CURLASIO_API share:
		public std::enable_shared_from_this<share>,
		public asio::noncopyable
	{
	public:
		share();
		~share();

		inline native::CURLSH* native_handle() { return handle_; }
		void set_share_cookies(bool enabled);
		void set_share_dns(bool enabled);
		void set_share_ssl_session(bool enabled);

		typedef void (*lock_function_t)(native::CURL* handle, native::curl_lock_data data, native::curl_lock_access access, void* userptr);
		void set_lock_function(lock_function_t lock_function);

		typedef void (*unlock_function_t)(native::CURL* handle, native::curl_lock_data data, void* userptr);
		void set_unlock_function(unlock_function_t unlock_function);

		void set_user_data(void* user_data);

	private:
		static void lock(native::CURL* handle, native::curl_lock_data data, native::curl_lock_access access, void* userptr);
		static void unlock(native::CURL* handle, native::curl_lock_data data, void* userptr);

#ifdef CURL_ASIO_ENSURE_INITIALIZATION
		initialization::ptr initref_;
#endif
		native::CURLSH* handle_{nullptr};
		std::mutex mutex_;
	};
}

/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	Integration of libcurl's multi interface with Boost.Asio
*/

#pragma once

#include "config.h"
#include <asio.hpp>
#include <functional>
#include <asio/detail/noncopyable.hpp>
#include <asio/steady_timer.hpp>
#include <memory>
#include <map>
#include <set>
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
#include "initialization.h"
#endif
#include "native.h"
#include "socket_info.h"

namespace curl
{
	class easy;

	class CURLASIO_API multi:
		public asio::noncopyable
	{
	public:
		multi(asio::io_service& io_service);
		~multi();

		inline asio::io_service& get_io_service() { return io_service_; }
		inline native::CURLM* native_handle() { return handle_; }

		void add(easy* easy_handle);
		void remove(easy* easy_handle);

		void socket_register(std::shared_ptr<socket_info> si);
		void socket_cleanup(native::curl_socket_t s);

	private:
		typedef std::shared_ptr<socket_info> socket_info_ptr;

		void add_handle(native::CURL* native_easy);
		void remove_handle(native::CURL* native_easy);

		void assign(native::curl_socket_t sockfd, void* user_data);
		void socket_action(native::curl_socket_t s, int event_bitmask);

		typedef int (*socket_function_t)(native::CURL* native_easy, native::curl_socket_t s, int what, void* userp, void* socketp);
		void set_socket_function(socket_function_t socket_function);
		void set_socket_data(void* socket_data);

		typedef int (*timer_function_t)(native::CURLM* native_multi, long timeout_ms, void* userp);
		void set_timer_function(timer_function_t timer_function);
		void set_timer_data(void* timer_data);

		void monitor_socket(socket_info_ptr si, int action);
		void process_messages();
		bool still_running();

		void start_read_op(socket_info_ptr si);
		void handle_socket_read(const asio::error_code& err, socket_info_ptr si);
		void start_write_op(socket_info_ptr si);
		void handle_socket_write(const asio::error_code& err, socket_info_ptr si);
		void handle_timeout(const asio::error_code& err);

		typedef asio::ip::tcp::socket socket_type;
		typedef std::map<socket_type::native_handle_type, socket_info_ptr> socket_map_type;
		socket_map_type sockets_;
		socket_info_ptr get_socket_from_native(native::curl_socket_t native_socket);

		static int socket(native::CURL* native_easy, native::curl_socket_t s, int what, void* userp, void* socketp);
		static int timer(native::CURLM* native_multi, long timeout_ms, void* userp);

		typedef std::set<easy*> easy_set_type;

		asio::io_service& io_service_;
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
		initialization::ptr initref_;
#endif
		native::CURLM* handle_{nullptr};
		easy_set_type easy_handles_;
		asio::steady_timer timeout_;
		int still_running_;
	};
}

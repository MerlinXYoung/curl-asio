/**
	curl-asio: wrapper for integrating libcurl with boost.asio applications
	Copyright (c) 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
	See COPYING for license information.

	Constructs libcurl string lists
*/

#pragma once

#include "config.h"
#include <asio/detail/noncopyable.hpp>
#include <string>
#include <memory>
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
#include "initialization.h"
#endif
#include "native.h"

namespace curl
{
	class CURLASIO_API string_list:
		public std::enable_shared_from_this<string_list>,
		public asio::noncopyable
	{
	public:
		string_list();
		~string_list();

		inline native::curl_slist* native_handle() { return list_; }

		void add(const char* str);
		void add(const std::string& str);

		struct iterator{ 
			iterator(native::curl_slist* p = nullptr) :ptr_(p){}
			iterator& operator++(){ 
				if(ptr_) ptr_ = ptr_->next;
				return *this;
			}
			iterator operator++(int){ 
				iterator old(ptr_);
				if(ptr_) ptr_ = ptr_->next;
				return old;
			}

			inline const char* operator*(){ return ptr_->data;}

			inline bool operator==(const iterator& other)const noexcept{ return ptr_ == other.ptr_; }
			inline bool operator!=(const iterator& other)const noexcept{ return ptr_ != other.ptr_; }

		private:
			native::curl_slist* ptr_{nullptr};
		};

		iterator begin() { return iterator(list_);}
		iterator end() { return iterator();}

		iterator begin() const{ return iterator(list_);}
		iterator end() const { return iterator();}


		
	private:
#ifdef CURL_ASIO_ENSURE_INITIALIZATION
		initialization::ptr initref_;
#endif
		native::curl_slist* list_{nullptr};
	};
}

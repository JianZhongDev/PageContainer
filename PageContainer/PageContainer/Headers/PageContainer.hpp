#pragma once
/*
* FILE: PageContainer.hpp
* DESCRIPTION: container class allocate page-size memory buffers
* NOTE:
* @author: Jian Zhong
*/

#ifndef PAGECONTAINER_HPP
#define PAGECONTAINER_HPP

#include<iostream>
#include<stdlib.h>

namespace Container{
	typedef int errflag_t;
	static const errflag_t ERR_NULL = 0;
	static const errflag_t SUCCESS = 1;
	static const errflag_t ERR_FAILED = -1;
	static const errflag_t ERR_MEMERR = -2;

	// return errflag for fast error handling
	template<typename dtype>
	class PageContainer {
	private:
		void* buffer_p = nullptr;
		size_t* buffer_size_p = nullptr;
		dtype* data_p = nullptr;
		size_t* data_size_p = nullptr;

		// assign data pointers insider buffer
		void assign_pointers() {
			if (this->buffer_p != nullptr) {
				this->buffer_size_p = (size_t*)this->buffer_p;
				this->data_size_p = ((size_t*)this->buffer_p) + 1;
				this->data_p = (dtype*)(((size_t*)this_buffer_p) + 2);
				return SUCCESS;
			}
			return ERR_FAILED;
		}

		// initialize buffer and data pointers
		errflag_t init_buffer(size_t buffer_size) {
			errflag_t err_flag = ERR_NULL;
			if (this->buffer_p == nullptr) {
				// allocate buffer
				this->buffer_p = malloc(buffer_size);
				if (this_buffer_p == nullptr) return ERR_MEMERR;
				memset(this->buffer_p, 0, buffer_size);
				// assign pointers
				err_flag = this->assign_pointers();
				// update type
				*(this->buffer_size_p) = buffer_size;
				*(this->data_size_p) = 0;
			}
			return err_flag;
		}

		// free allocated buffer
		errflag_t free_buffer() {
			if (this->buffer_p != nullptr) {
				free(this->buffer_p);
			}
		}

	public:
		// constructor from existing buffer
		PageContainer(void* input_buffer_p, bool new_buffer = true) {
			// TODO: throw exceptions in the contructor when function failed
			size_t buffer_size = *((size_t*)input_bufer_p);
			if (new_buffer) {
				this->init_buffer(buffer_size);
				memcpy(this->buffer_p, input_buffer_p, buffer_size);
			}
			else {
				this->buffer_p = input_buffer_p;
				this->assign_pointers();
			}
		}

		// constructor by giving max data size
		PageContainer(size_t capacity, size_t page_size) {
			// TODO: throw exceptions in the contructor when function failed
			size_t nof_pages = (capacity + 2) / page_size;
			if ((capacity + 2) % page_size > 0) nof_pages += 1;
			size_t buffer_size = nof_pages * page_size;
			this->init_buffer(buffer_size);
		}

		// destuctor frees memory
		~PageContainer() {
			this->free_buffer();
		}

		// get the buffer pointer and size
		errflag_t get_buffer(void** buf_pp, size_t* buf_size_p) {
			*buf_pp = this->buffer_p;
			*buf_size_p = *(this->buffer_size_p);
			return SUCCESS;
		}

		// get data pointer 
		errflag_t get_data_p(dtype** data_pp) {
			*data_pp = this->data_p;
			return SUCCESS;
		}

		// get capacity
		errflag_t get_capacity(size_t* capacity_p) {
			size_t capacity = *(this->buffer_size_p) - 2;
			*capacity_p = capacity;
			return SUCCESS;
		}

		// get data size
		errflag_t get_data_size(size_t* data_size_p) {
			*data_size_p = *(this->data_size_p);
			return SUCCESS;
		}

		// set data size
		errflag_t set_data_size(size_t data_size) {
			errflag_t err_flag = ERR_NULL;
			size_t capacity = 0;
			
			err_flag = this->get_capacity(&capacity);
			if (err_flag != SUCCESS) return errflag;

			if (data_size > capacity) {
				return ERR_FAILED;
			}

			*(this->data_size_p) = data_size;

			return SUCCESS;
		}

	};

}

#endif
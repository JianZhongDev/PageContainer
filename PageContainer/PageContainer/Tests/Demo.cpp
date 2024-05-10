/*
* FILE: Demo.cpp
* DESCRIPTION: demonstration for PageContainer
* NOTE:
*	1. #define MAIN to enable the main() function here
* @author: Jian Zhong
*/

#define MAIN

#ifdef MAIN

#include<iostream>
#include<string>
#include<Windows.h>

#include "../Headers/PageContainer.hpp"
#include "../Headers/DemoHelper.hpp"

void main() {
	std::wstring file_path = L"test_file.bin";
	HANDLE file_handle = INVALID_HANDLE_VALUE;
	size_t page_size = 4 * 1024; // 4KB page size
	Container::errflag_t errflag = Container::ERR_NULL;
	DWORD error_flag = NULL;
	DWORD d_error = NULL;

	// get system page size
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	page_size = sys_info.dwPageSize;
	std::cout << "system page size: " << page_size << std::endl;

	// initialize test array
	const size_t array_len = 10;
	float* test_array = new float[array_len];
	size_t data_size = array_len * sizeof(float);

	for (size_t idx = 0; idx < array_len; ++idx) {
		test_array[idx] = rand_float(0.0f, 1.0f, 1000);
	}

	std::cout << "write array: " << carray_to_string(test_array, array_len) << std::endl;

	// create container with page size
	Container::PageContainer<float> write_container(array_len * sizeof(float), page_size);
	
	// copy data into container 
	size_t data_size_to_write = data_size;
	float* write_data_p = nullptr;
	size_t write_capacity = 0;
	errflag = write_container.get_data_p(&write_data_p);
	if (errflag != Container::SUCCESS) {
		std::cout << "ERR:\t failed to access data pointer." << std::endl;
	}
	write_container.get_capacity(&write_capacity);
	memcpy(write_data_p, test_array, data_size_to_write);
	write_container.set_data_size(data_size_to_write);

	// write data to file (bypassing system buffer)
	// open file
	file_handle = CreateFileW(
		file_path.c_str(),
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING, 
		NULL);
	if (file_handle == INVALID_HANDLE_VALUE) {
		std::cout << "ERR:\t failed to create file." << std::endl;
		return;
	}

	void* write_buffer_p = nullptr;
	size_t write_buffer_size = 0;
	write_container.get_buffer(&write_buffer_p, &write_buffer_size);

	// write data
	error_flag = WriteFile(file_handle, write_buffer_p, write_buffer_size, NULL, NULL);
	d_error = GetLastError();
	if (error_flag == FALSE && d_error != ERROR_IO_PENDING) {
		std::cout << "ERR:\t error in write file, error code = " << d_error << std::endl;
		return;
	}

	// close file
	CloseHandle(file_handle);
	file_handle = INVALID_HANDLE_VALUE;

	std::cout << "data write to: ";
	std::wcout << file_path;
	std::cout << std::endl;

	// read data from file
	void* read_buffer_p = nullptr;
	size_t read_buffer_size = 0;
	DWORD bytes_read = 0;

	// open file
	file_handle = CreateFileW(
		file_path.c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (file_handle == INVALID_HANDLE_VALUE) {
		std::cout << "ERR:\t failed to create file." << std::endl;
		return;
	}
	// get buffer size
	error_flag = ReadFile(file_handle, &read_buffer_size, sizeof(size_t), &bytes_read, NULL);
	d_error = GetLastError();
	if (error_flag == FALSE && d_error != ERROR_IO_PENDING) {
		std::cout << "ERR:\t error in read file, error code = " << d_error << std::endl;
		return;
	}

	std::cout << "read_buffer_size = " << read_buffer_size << std::endl;
	Container::PageContainer<float> read_container(read_buffer_size);
	read_container.get_buffer(&read_buffer_p, &read_buffer_size);

	// set file pointer to start of the buffer 
	SetFilePointer(file_handle, 0, NULL, FILE_BEGIN);
	d_error = GetLastError();
	if (d_error != 0) {
		std::cout << "ERR:\t error set file pointer, error code = " << d_error << std::endl;
		return;
	}

	// load file from the buffer 
	error_flag = ReadFile(file_handle, read_buffer_p, read_buffer_size, &bytes_read, NULL);
	d_error = GetLastError();
	if (error_flag == FALSE && d_error != ERROR_IO_PENDING) {
		std::cout << "ERR:\t error in read file, error code = " << d_error << std::endl;
		return;
	}

	// close file
	CloseHandle(file_handle);
	file_handle = INVALID_HANDLE_VALUE;

	std::cout << "data read from: ";
	std::wcout << file_path;
	std::cout << std::endl;

	// display read data
	float* read_arr = nullptr;
	size_t read_data_size = 0;
	size_t read_arr_len = 0;
	read_container.get_data_p(&read_arr);
	read_container.get_data_size(&read_data_size);
	read_arr_len = read_data_size / sizeof(float);
	
	std::cout << "read array: " << carray_to_string(read_arr, read_arr_len) << std::endl;

}

#endif
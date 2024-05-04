#pragma once
/*
* FILE: DemoHelper.hpp
* DESCRIPTION: helper functions for demonstration
* NOTE:
* @author: Jian Zhong
*/

#ifndef DEMOHELPER_HPP
#define DEMOHELPER_HPP

#include<iostream>
#include<sstream>
#include<string>

template<typename dtype>
std::string carray_to_string(dtype* arr, size_t nof_elems) {
	std::stringstream tmp_sstream;
	tmp_sstream << "{";
	for (size_t i_elem = 0; i_elem < nof_elems; ++i_elem) {
		tmp_sstream << arr[i_elem];
		if (i_elem < nof_elems - 1) tmp_sstream << ", ";
	}
	tmp_sstream << "}";
	return tmp_sstream.str();
}
#endif
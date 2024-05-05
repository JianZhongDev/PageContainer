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

float rand_float(float min = 0.0f, float max = 1.0f, int granularity = 100) {
	int rand_int_num = std::rand() % granularity;
	float rand_unit_float = (1.0f * rand_int_num) / (1.0f * granularity);
	float rand_float = rand_unit_float * (max - min) + min;
	return rand_float;
}
#endif
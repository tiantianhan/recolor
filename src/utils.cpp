/*
 * utils.cpp
 *
 *  Created on: May 12, 2017
 *      Author: tina
 */

#include "utils.hpp"

using namespace std;

string remove_extension(const string& fullname){
	return fullname.substr(0, fullname.find_last_of("."));
}

string remove_paths(const string& fullname){
	return fullname.substr(fullname.find_last_of("/") + 1, string::npos); //TODO make more robust
}

/**
 * @file utils.hpp
 * @date 04.07.17
 * @author galarius
 * @copyright Copyright © 2017 galarius.
 * @brief Resources Compiler Helper Functions
 */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <algorithm>
#include <vector>
#include <cctype>
#include <fstream>
#include <stdexcept>

inline std::vector<std::string> split(const std::string &text, std::string sep)
{
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;

	while((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}

	tokens.push_back(text.substr(start));
	return tokens;
}

inline void trim(std::string &s)
{
	// ltrim
	s.erase(s.begin(),
	        find_if(s.begin(), s.end(),
	                std::not1(std::ptr_fun<int, int>(std::isspace))));
	// rtrim
	s.erase(find_if(s.rbegin(), s.rend(),
	                std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
	        s.end());
}

inline std::string trimmed(std::string s)
{
	trim(s);
	return s;
}

inline bool ends_with(const std::string &s, const std::string &suffix)
{
	return (s.size() >= suffix.size()) &&
	       equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}
#endif // __UTILS_HPP__
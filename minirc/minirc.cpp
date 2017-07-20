/**
 * @file minirc.cpp
 * @date 03.07.17
 * @author galarius
 * @copyright Copyright © 2017 galarius
 * @brief Resources Compiler
 */

#include "minirc.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

void MiniRC::create_rc_file(const std::string &file) throw(std::invalid_argument)
{
	std::ofstream out(file);

	if(out.fail()) {
		throw std::invalid_argument(file);
	}

	out << "# Mini GRC Resources File" << std::endl
	    << std::endl
	    << "# Specify resources files separated with space" << std::endl
	    << "# or per line, ending with \\" << std::endl
	    << "# Example RESOURCES = image.jpg sound.wav" << std::endl
	    << std::endl
	    << "RESOURCES =" << std::endl
	    << std::endl
		<< "# Generate resources header file with specified name" << std::endl
		<< "HEADER_NAME = resource.h" << std::endl
		<< std::endl
		<< "# Generate resources source file with specified name" << std::endl
		<< "SOURCE_NAME = resource.c" << std::endl
		<< std::endl;
}

void MiniRC::load_rc_file(const std::string &file) throw(std::invalid_argument)
{
	std::ifstream in(file);

	if(in.fail()) {
		throw std::invalid_argument(file);
	}

	bool multiline_value = false;
	std::string key;
	std::string value;

	while(in.good() && ! in.eof()) {
		std::string line;
		getline(in, line);

		// filter comments
		if(!line.empty()) {
			std::size_t pos = line.find('#');

			if(pos != std::string::npos) {
				line = line.substr(0, pos);
			}
		}

		// split line into key and value
		if(!line.empty()) {
			std::size_t pos = line.find('=');

			if(pos != std::string::npos) {
				// key and value at single line
				multiline_value = false;
				key = line.substr(0, pos);
				trim(key);
				value = line.substr(pos + 1);
				trim(value);
			} else {
				// value at line without a key or a garbage
				multiline_value = ends_with(value, "\\");

				if(multiline_value) {
					value = line;
					value.pop_back();
					trim(value);
				} else {
					value = std::string();
				}
			}

			if(!value.empty()) {
				parse_kv(key, value, multiline_value);
			}
		}
	}
}

void MiniRC::compile() throw(std::invalid_argument)
{
	try {
		if(header_name_.empty()) {
			throw std::invalid_argument(header_name_);
		}
		if(source_name_.empty()) {
			throw std::invalid_argument(source_name_);
		}
		generate_header(header_name_);
		generate_source(source_name_);
	} catch(const std::invalid_argument &ia) {
		throw ia;
	}
}

std::string MiniRC::rc_name(const std::string &resource_fname)
{
	std::string name = resource_fname;
	std::replace_if(name.begin(), name.end(),
	                std::not1(std::ptr_fun<int, int>(&std::isalnum)), '_');
	return name;
}

void MiniRC::parse_kv(const std::string &key, const std::string &value, bool multiline_value)
{
	auto valid_name = [&](const std::string& res_name) -> bool {
		return resources_.find(res_name) == resources_.end() && !res_name.empty();
	};

	//---
	if(key == "RESOURCES") {
		std::string name;

		if(multiline_value) {
			name = rc_name(value);

			if(valid_name(name)) {
				resources_[name] = value;
			}
		} else {
			auto values = split(value, " ");
			std::string trimmed_value;

			for(auto &val : values) {
				trimmed_value = trimmed(val);
				name = rc_name(trimmed_value);

				if(valid_name(name)) {
					resources_[name] = trimmed_value;
				}
			}
		}
	} else if(key == "HEADER_NAME") {
		header_name_ = value;
	} else if(key == "SOURCE_NAME") {
		source_name_ = value;
	}
}

void MiniRC::generate_header(const std::string &file) throw(std::invalid_argument)
{
	std::ofstream out(file);

	if(out.fail()) {
		throw std::invalid_argument(file);
	}

	std::string pragma_once = rc_name("__"+ header_name_ +"__");

	out << "/** Generated with MiniRC */" << std::endl
	    << std::endl
	    << "#ifndef " << pragma_once << std::endl
	    << "#define " << pragma_once << std::endl
	    << std::endl
	    << "#include <stddef.h>" << std::endl
	    << std::endl;
	out << R"!(/**
* @brief Restores binary file in file system to specified location
* @param[in] fname Full file name for saving in file system
* @param[in] content Saved with resource compiler hex content of a binary file
* @@return 1 if everything went well, 0 if `fname` is invalid or 
*            error occured during hex to bin conversion.
*/)!"   << std::endl
	    << "int rc_restore(const char* fname, const int* content, size_t length);" << std::endl
	    << std::endl;

	for(auto &kvmap : resources_) {
		if(valid_resource(kvmap.second)) {
			out << "/* " << kvmap.second << " */" << std::endl;
			out << "extern const int " << kvmap.first << "[];" << std::endl;
			out << "extern const size_t " << kvmap.first << "_len;" << std::endl;
		} else {
			std::cerr << "Invalid resource file: " << kvmap.second << std::endl;
		}
	}

	out << std::endl << "#endif /* "<< pragma_once <<" */" << std::endl;
}

void MiniRC::generate_source(const std::string &file) throw(std::invalid_argument)
{
	std::ofstream out(file);

	if(out.fail()) {
		throw std::invalid_argument(file);
	}

	out << "/** Generated with MiniRC */" << std::endl
	    << std::endl
	    << "#include \"" << header_name_ << "\"" << std::endl
	    << std::endl
	    << "#include <stdio.h>"  << std::endl
	    << "#include <stdlib.h>" << std::endl
	    << "#include <string.h>" << std::endl
	    << std::endl
	    << "#define BUFFER_SIZE 255" << std::endl
	    << std::endl
	    << R"!(int rc_restore(const char* fname, const int* content, size_t length)
{
    int restored = 0;           /* result */
    FILE* ptr_file = NULL;      
    char buffer[BUFFER_SIZE];   
    if ((ptr_file = fopen(fname, "wb")))
    {
        for(int i = 0; i < length; ++i) 
        {
            memset(buffer, '\0', BUFFER_SIZE);
            restored = snprintf(buffer, BUFFER_SIZE, "%.2x", content[i]) >= 0;
            putc((unsigned char)(strtol(buffer, NULL, 16)), ptr_file);
        }
        fclose(ptr_file);
        restored = 1;
    }
    return restored;
})!" << std::endl << std::endl;
	out << "/*********************************************"
	    << "*****************************************************/"
	    << "/*                                          RESOURCES "
	    << "                                            */"
	    << "/*****************************************************"
	    << "*********************************************/" << std::endl
	    << std::endl;
	size_t size = 0;

	for(auto &kvmap : resources_) {
		if(valid_resource(kvmap.second)) {
			size = 0;
			out << "/* " << kvmap.second << " */" << std::endl;
			out << "const int " << kvmap.first << "[] = {" << std::endl;
			// convert binary file at `kvmap.second` to hex and
			// save it to out (resource source file)
			to_hex(kvmap.second, [&](const std::string& hex) {
				static int i = 0;
				out << "0x" << hex << ",";

				if(!(++i % 20)) {
					i = 0;
					out << std::endl;
				}

				++size;
			});
			out << "};" << std::endl << std::endl;
			out << "const size_t " << kvmap.first << "_len = " << size << ";" << std::endl
			    << std::endl;
		} else {
			std::cerr << "Invalid resource file: " << kvmap.second << std::endl;
		}
	}
}

void MiniRC::to_hex(const std::string &file, std::function<void(const std::string &hex)> each)
{
	std::ifstream in(file, std::ios::binary);

	if(in.good()) {
		unsigned char uch;
		std::stringstream buf;
		in >> std::noskipws;

		while(!in.eof()) {
			in >> uch;
			buf << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(uch);
			each(buf.str()); // send hex representation of current byte
			buf.str("");     // clear stringstream
		}
	}
}

bool MiniRC::valid_resource(const std::string &res_fname)
{
	std::ifstream in(res_fname, std::ifstream::binary);
	return in.good();
};
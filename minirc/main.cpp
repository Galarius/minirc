/**
 * @file main.cpp
 * @date 03.07.17
 * @author galarius
 * @copyright Copyright © 2017 galarius.
 * @brief Resources Compiler Entry Source File
 */

#include "minirc.hpp"

#include <iostream>

static void show_usage(char *name)
{
	std::cerr << "Mini RC" << std::endl
			  << "Version: " << VERSION << std::endl
	          << "Creates resources.h and resources.c with hex representations of" << std::endl
	          << "binary files specified in RESOURCES_FILE." << std::endl
	          << "Usage: " << name << " <option(s)> RESOURCES_FILE" << std::endl
	          << "Options:" << std::endl
	          << "\t-h,--help\tShow this help message" << std::endl
	          << "\t-n,--new\tGenerate new resource file" << std::endl
	          << std::endl;
}

int main(int argc, char *argv[])
{
	if(argc < 2) {
		show_usage(argv[0]);
		return 1;
	}

	MiniRC rc;
	std::string rc_file = argv[argc-1];

	for(int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		std::cout << arg;
		if(arg == "-h" || arg == "--help") {
			show_usage(argv[0]);
			return 0;
		} else if(arg == "-n" || arg == "--new") {
			try {
				rc.create_rc_file(rc_file);
			} catch(const std::invalid_argument &ia) {
				std::cerr << "Invalid argument " << ia.what() << std::endl;
				return 1;
			}

			return 0;
		}
	}

	try {
		rc.load_rc_file(rc_file);
		rc.compile();
	} catch(const std::invalid_argument &ia) {
		std::cerr << "Invalid argument " << ia.what() << std::endl;
		return 1;
	}

	return 0;
}
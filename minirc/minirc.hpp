/**
 * @file minirc.hpp
 * @date 03.07.17
 * @author galarius
 * @copyright Copyright © 2017 galarius
 * @brief Resources Compiler
 */

#ifndef __MINIRC_HPP__
#define __MINIRC_HPP__

#include <string>
#include <sstream>
#include <stdexcept>
#include <functional>
#include <unordered_map>

class MiniRC
{
public:
	MiniRC() = default;
	~MiniRC() = default;
	MiniRC(const MiniRC &) = delete;
	MiniRC &operator=(const MiniRC &other) = delete;
public:
	/**
	 * @brief Creates new *.rc file
	 * @exception std::invalid_argument
	 */
	void create_rc_file(const std::string &file) throw(std::invalid_argument);
	/**
	 * @brief Loads *.rc file with file paths to resources
	 * @exception std::invalid_argument
	 */
	void load_rc_file(const std::string &file) throw(std::invalid_argument);
	/**
	 * @brief Compile resources
	 * @exception std::invalid_argument
	 */
	void compile() throw(std::invalid_argument);
public:
	/**
	 * @brief Generates valid resource name (to use in code) from it's file name
	 */
	static std::string rc_name(const std::string &resource_fname);
private:
	/**
	 * @brief Parse key & value during rc file reading
	 * @param[in] multiline_value The value is one of several parts located at
	 *            different lines, ending with `\`
	 */
	void parse_kv(const std::string &key, const std::string &value, bool multiline_value);
	/**
	 * @brief Generates c header file
	 * @exception std::invalid_argument
	 */
	void generate_header(const std::string &file) throw(std::invalid_argument);
	/**
	 * @brief Generates c source file
	 * @exception std::invalid_argument
	 */
	void generate_source(const std::string &file) throw(std::invalid_argument);
	/**
	 * @brief Creates hex representation of binary file
	 * @param[in] each Function that is called every time when
	 *            byte in binary file is converted to hex representation
	 * @note No notifications occured if resource file is unavailable, use valid_resource
	 */
	void to_hex(const std::string &file,
	            std::function<void(const std::string &hex)> each);
private:
	/**
	 * @brief Checks if resource is a valid one (size is OK, and it's reachable)
	 */
	static bool valid_resource(const std::string &res_fname);
private:
	/**
	 * @brief Collection of resources ( <name, generated with `rc_name`, file name> )
	 */
	std::unordered_map<std::string, std::string> resources_;
	std::string header_name_;
	std::string source_name_;
};

#endif  // __MINIRC_HPP__
#pragma once

#include <string>
#include <map>

class kernel_info {

	public:
		std::string path();
		std::string cmdline();
		std::map<std::string, std::string> pairs();
		bool io_error();

		kernel_info(const std::string& path = "/proc/cmdline");

	private:
		std::string _path;
		std::string _cmdline;
		std::map<std::string, std::string> _pairs;
		bool _io_error = false;

		void parse();
};

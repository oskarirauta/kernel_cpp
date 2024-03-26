#include <iostream>
#include "kernel_info.hpp"

int main(int argc, char **argv) {

	kernel_info *kernel = nullptr;

	try {
		kernel = new kernel_info();

	} catch ( const std::runtime_error& e ) {

		std::cout << "\nfailed to retrieve kernel's info, reason:\n" << e.what() << std::endl;
		return 1;
	}

	std::cout << "\nkernel info's path: " << kernel -> path() << "\n\n" <<
			"kernel's cmdline: " << kernel -> cmdline() << "\n\n" <<
			"cmdline parsed to value pairs:" << std::endl;

	for ( const auto& p : kernel -> pairs())
		std::cout << p.first <<
			( p.second.empty() ? "" : ( " = " + p.second )) << std::endl;

	std::cout << std::endl;

	delete kernel;
	return 0;
}

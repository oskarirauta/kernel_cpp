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

	std::cout << "\nsecurity features:\n" <<
		"selinux: " << ( kernel -> security -> selinux -> enabled() ? "enabled, " : "disabled, " ) <<
		"state: " << kernel -> security -> selinux -> mode() << "\n";
	std::cout << "apparmor: " << ( kernel -> security -> apparmor -> enabled() ?
			( "enabled, " + std::to_string(kernel -> security -> apparmor -> profile_count()) + " profiles") : "disabled" ) << "\n";
	std::cout << "seccomp: " << ( kernel -> security -> seccomp -> enabled() ? "enabled" : "disabled" ) << "\n";

	if ( kernel -> security -> seccomp -> enabled())
		std::cout << "\tactions: " << kernel -> security -> seccomp -> operator std::string() << "\n";
	std::cout << std::endl;

	delete kernel;
	return 0;
}

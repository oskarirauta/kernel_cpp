#include <fstream>
#include <istream>
#include <sstream>

#ifdef SELINUX_ENABLED
#include <selinux/selinux.h>
#endif

#include "kernel_info.hpp"


kernel_info::security_info::security_info() {

	this -> selinux = new kernel_info::security_info::selinux_info();
	this -> apparmor = new kernel_info::security_info::apparmor_info();
	this -> seccomp = new kernel_info::security_info::seccomp_info();

	this -> update();
}

kernel_info::security_info::~security_info() {

	if ( this -> selinux != nullptr ) delete this -> selinux;
	if ( this -> apparmor != nullptr ) delete this -> apparmor;
	if ( this -> seccomp != nullptr ) delete this -> seccomp;
}

void kernel_info::security_info::update() {

	std::string line;

#ifdef SELINUX_ENABLED
	int rc = is_selinux_enabled();
	if ( rc < 0 )
		this -> selinux -> _state = -1;
	else if ( rc == 1 ) {
		rc = security_getenforce();
		if ( rc < 0 )
			this -> selinux_state = -1;
		else this -> selinux -> state = rc + 1;
	} this -> selinux -> _state = 0;
#else
	this -> selinux -> _state = -1;
#endif

	this -> apparmor -> _profile_count = 0;
	std::ifstream fd1("/sys/kernel/security/apparmor/profiles", std::ios::in);

	if ( fd1.is_open() && fd1.good()) {

		while ( std::getline(fd1, line))
			this -> apparmor -> _profile_count++;

		fd1.close();

	} else if ( fd1.is_open()) fd1.close();

	this -> seccomp -> _actions.clear();
	std::ifstream fd2("/proc/sys/kernel/seccomp/actions_avail");

	if ( fd2.is_open() && fd2.good()) {

		while ( std::getline(fd2, line)) {

			std::string act;
			std::istringstream ss(line);

			while ( ss >> act ) {

				if ( !act.empty())
					this -> seccomp -> _actions.push_back(act);
			}

		}

		fd2.close();

	} else if ( fd2.is_open()) fd2.close();
}

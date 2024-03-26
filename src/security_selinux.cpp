#include "kernel_info.hpp"

kernel_info::security_info::selinux_info::operator bool() {

	return this -> _state > 1;
}

bool kernel_info::security_info::selinux_info::enabled() {

	return this -> _state > 1;
}

kernel_info::security_info::selinux_info::operator std::string() {

	switch ( this -> _state ) {
		case -1: return "not supported";
		case 0: return "disabled";
		case 1: return "permissive";
		case 2: return "enforcing";
		default: ;
	}

	return "unknown";
}

const std::string kernel_info::security_info::selinux_info::mode() {

	return this -> operator std::string();
}

int kernel_info::security_info::selinux_info::state() {

	return this -> _state;
}

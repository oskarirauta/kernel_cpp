#include "kernel_info.hpp"

kernel_info::security_info::apparmor_info::operator bool() {

	return this -> _profile_count > 0;
}

bool kernel_info::security_info::apparmor_info::enabled() {

	return this -> _profile_count > 0;
}

int kernel_info::security_info::apparmor_info::profile_count() {

	return this -> _profile_count;
}

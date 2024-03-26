#include <utility>
#include <numeric>

#include "kernel_info.hpp"

kernel_info::security_info::seccomp_info::operator bool() {

	return !this -> _actions.empty();
}

bool kernel_info::security_info::seccomp_info::enabled() {

	return !this -> _actions.empty();
}

const std::vector<std::string> kernel_info::security_info::seccomp_info::actions() {

	return std::as_const(this -> _actions);
}

kernel_info::security_info::seccomp_info::operator std::string() {

	if ( this -> _actions.empty())
		return "";

	return std::accumulate(this -> _actions.begin(), this -> _actions.end(), std::string(),
			[](const std::string& a, const std::string& b) -> std::string {
				return a + ( a.size() > 0 ? "," : "" ) + b;
			});
}

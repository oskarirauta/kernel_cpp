#include <fstream>
#include <sstream>

#include "throws.hpp"
#include "common.hpp"
#include "kernel_info.hpp"

kernel_info::kernel_info(const std::string& path) {

	this -> _path = path;

	if ( path.empty())
		throws << "cannot construct class kernel_info, path \"" << path << "\" is not valid path" << std::endl;

	std::fstream fd(path, std::ios::in);

	if ( !fd.is_open() || !fd.good()) {

		if ( fd.is_open())
			fd.close();
		throws << "failed to construct kernel_info, " << path << " is not readable" << std::endl;
	}

	this -> _cmdline = "";
	std::string::value_type ch, quote, prev = 0;
	bool quoted = false;

	while ( fd >> std::noskipws >> ch && !fd.eof() && fd.good() && ch != std::char_traits<std::string::value_type>::eof()) {

		if ( ch == '\r' || ch == '\n' || ( !quoted && ch == '\t' ))
			ch = ' ';

		if ( !quoted && ch == ' ' && prev == ' ' )
			continue;

		if ( !quoted && ( ch == '\'' || ch == '\"' )) {
			quoted = true;
			quote = ch;
		} else if ( quoted && ch == quote )
			quoted = false;

		this -> _cmdline += ch;
	}

	if ( !this -> _cmdline.empty()) {
		this -> _cmdline = common::trim_ws(this -> _cmdline);
		this -> parse();
	}

	if ( fd.is_open())
		fd.close();
}

void kernel_info::parse(void) {

	bool is_name = true;
	bool escaping = false;
	std::string::value_type quote = 0;
	std::string key, val;

	for ( const std::string::value_type& ch : this -> _cmdline ) {

		if ( !is_name && (
			( quote != 0 && !escaping && ch == quote ) ||
			( quote == 0 && ch == ' ' ))) {

			quote = 0;
			escaping = false;
			is_name = true;
			this -> _pairs[key] = val;
			key = "";
			val = "";

		} else if ( is_name && ch == ' ' ) {

			quote = 0;
			escaping = false;
			is_name = true;
			this -> _pairs[key] = "";
			key = "";
			val = "";

		} else if ( is_name && ch == '=' ) {

			quote = 0;
			escaping = false;
			is_name = false;

		} else if ( !is_name && val.empty() && ( ch == '\'' || ch == '\"' )) {

			quote = ch;

		} else if ( !is_name && !escaping && ch == '\\' ) {

			escaping = true;

		} else {

			if ( !is_name && escaping && ch != '\'' && ch != '\"' && ch != '\\' ) {

				escaping = false;
				val += '\\';
			}

			if ( is_name ) key += ch;
			else val += ch;

			escaping = false;
		}
	}

	if ( !key.empty())
		this -> _pairs[key] = val;

}

std::string kernel_info::path() {

	return this -> _path;
}

std::string kernel_info::cmdline() {

	return this -> _cmdline;
}

std::map<std::string, std::string> kernel_info::pairs() {

	return this -> _pairs;
}

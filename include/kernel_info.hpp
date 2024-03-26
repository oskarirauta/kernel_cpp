#pragma once

#include <string>
#include <vector>
#include <map>

class kernel_info {

	public:

		class security_info {

			public:

				class selinux_info {

					friend class kernel_info;
					friend class kernel_info::security_info;

					public:

						operator bool();
						operator std::string();

						bool enabled();
						int state();
						const std::string mode();

					private:
						int _state = -2;

				};

				class apparmor_info {

					friend class kernel_info;
					friend class kernel_info::security_info;

					public:

						operator bool();

						bool enabled();
						int profile_count();

					private:
						bool _enabled = false;
						int _profile_count = 0;

				};

				class seccomp_info {

					friend class kernel_info;
					friend class kernel_info::security_info;

					public:

						operator bool();
						operator std::string();

						bool enabled();
						const std::vector<std::string> actions();

					private:
						bool _enabled = false;
						std::vector<std::string> _actions;
						std::string _string = "";
				};

				selinux_info* selinux = nullptr;
				apparmor_info* apparmor = nullptr;
				seccomp_info* seccomp = nullptr;

				void update();
				security_info();
				~security_info();

			private:
				int get_selinux_status();
				int get_apparmor_profiles();
				bool get_seccomp_actions(std::vector<std::string> &actions);

		};

		security_info* security = nullptr;

		std::string path();
		std::string cmdline();
		std::map<std::string, std::string> pairs();

		void update();

		kernel_info(const std::string& path = "/proc/cmdline");
		~kernel_info();

	private:

		std::string _path;
		std::string _cmdline;
		std::map<std::string, std::string> _pairs;

		void parse();
};

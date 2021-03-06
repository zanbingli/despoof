#include <new>
#include <boost/assign/std/vector.hpp>
#include <despoof/config.h>
#include "command_line.h"
#include <despoof/argtable.h>

using namespace std;
using namespace boost::assign;
using namespace despoof;

#define STR2(x) #x
#define STR(x) STR2(x)

void despoof::command_line_to_configuration(configuration &config, int argc, char **argv)
{
	auto interval = alloc_check(arg_int0("i", "interval", "<n>", "Time of one despoof iteration in milliseconds; Default: " STR(DESPOOF_DEFAULT_INTERVAL)));
	auto log_module = alloc_check(arg_str0("o", "log", "<mod>", "Name of the log module, without the \"log\" prefix; Default: " DESPOOF_DEFAULT_LOG_MODULE));
	auto nw_module = alloc_check(arg_str0("n", "network", "<mod>", "Name of the network module, without the \"nw\" prefix; Default: " DESPOOF_DEFAULT_NET_MODULE));
	auto help = alloc_check(arg_lit0("h", "help", "Displays this help text"));
	auto version = alloc_check(arg_lit0("V", "version", "Displays version information"));

	auto end = alloc_check(arg_end(20));
	auto table = make_shared<argtable>();

#ifndef BUILD_SERVICE
	(*table) += help, version;
#endif
	(*table) += interval, log_module, nw_module, end;

	if(arg_parse(argc, argv, table->data()) > 0) {
		throw argtable_error(argv[0], table, end);
	}

	if(interval->count > 0) {
		config.interval = interval->ival[0];
	}
	if(log_module->count > 0) {
		config.log_module = log_module->sval[0];
	}
	if(nw_module->count > 0) {
		config.nw_module = nw_module->sval[0];
	}
	if(help->count > 0) {
		print_help(*table, argv[0]);
		config._nostart = true;
	}
	if(version->count > 0) {
		printf("%s\n%s\n\n", "Despoof " DESPOOF_VERSION, "Copyright (c) 2011 - 2012 Raphael Robatsch. All rights reserved.");
		printf("%s\n%s\n", "See the accompanying \"COPYING.txt\" file for the license agreement", "of this software. If there is no COPYING.txt in your software distribution, see");
		printf("\"%s\".\n", "https://raw.github.com/raphaelr/despoof/master/COPYING.txt", ".");
		config._nostart = true;
	}
}

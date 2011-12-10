#include "context.h"

using namespace std;
using namespace despoof;

context::context(configuration &config, collect_function collect, log_function log)
	: config_(config), collect_(collect), log_(logger(log))
{
}

configuration& context::config()
{
	return config_;
}

logger& context::log()
{
	return log_;
}

list<adapter_address> context::reload()
{
	auto interfaces = collect_();
	list<adapter_address> result;

	for(auto ifaceit = interfaces.begin(); ifaceit != interfaces.end(); ++ifaceit) {
		for(auto addrit = (*ifaceit)->addresses().begin(); addrit != (*ifaceit)->addresses().end(); ++addrit) {
			for(auto gwit = (*ifaceit)->gateways().begin(); gwit != (*ifaceit)->gateways().end(); ++gwit) {
				result.push_back(adapter_address(*ifaceit, *addrit, *gwit));
			}
		}
	}

	return result;
}
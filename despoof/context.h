#pragma once

#include <list>
#include <despoof/import/collect.h>
#include <despoof/logger.h>
#include "configuration.h"
#include "adapter_address.h"

namespace despoof {
	class context {
		logger log_;
		std::unique_ptr<network_api> api_;
		configuration config_;

		logger& log();
		configuration& config();
		std::list<adapter_address> reload();
	public:
		context(configuration &config, std::unique_ptr<network_api> &&api, log_function log);		

		void iterate(std::list<adapter_address> &addresses);
	};
}

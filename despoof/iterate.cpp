#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include "context.h"

using namespace std;
using namespace despoof;

void context::iterate(list<adapter_address> &addresses)
{
	if(addresses.empty()) {
		api_->wait_until_invalid();
		addresses = reload();
		return;
	}
	int delay = config().interval / addresses.size();

	for(auto it = addresses.begin(); it != addresses.end(); ++it) {
		if(api_->invalid()) {
			addresses = reload();
			return;
		}

		it->interface->fix(it->address, it->gateway, log_);
		Sleep(delay);
	}
}

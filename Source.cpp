#include <iostream>
#include <string>
#include <sqlite_modern_cpp.h>
#include "CLIManager.h"

int main() {
	try {
		CLIManager* manager = new CLIManager();
		manager->run();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
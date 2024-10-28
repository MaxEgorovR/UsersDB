#pragma once
#include <iostream>
#include <sqlite_modern_cpp.h>
#include <string>
#include "AccountManager.h"

class CLIManager {
public:
	void run() {

		int choise;
		bool result;
		std::string login, password;
		int choise1;
		while (true) {
			std::cout << "1 - Continue\nElse - Exit\n";
			std::cin >> choise;
			if (choise == 1) {
				std::cout << "1 - Register\n2 - log in\n3 - Quit\n4 - Check information about account\n";
				std::cin >> choise1;
				switch (choise1)
				{
				case 1:
					std::cout << "Enter the login:\n";
					std::cin >> login;
					std::cout << "Enter the password:\n";
					std::cin >> password;
					result = this->sing_in(login, password);
					if (result) {
						std::cout << "You have successfully registered!\n";
					}
					else {
						std::cout << "You failed to register.\nPossible problems: the account already exists or you are already on the account\n";
					}
					break;
				case 2:
					std::cout << "Enter the login:\n";
					std::cin >> login;
					std::cout << "Enter the password:\n";
					std::cin >> password;
					result = this->log_in(login, password);
					if (result) {
						std::cout << "You have successfully logged into your account!\n";
					}
					else {
						std::cout << "You were unable to log into your account.\nPossible problems: incorrect login or password, or you are already logged into your account\n";
					}
					break;
				case 3:
					result = this->log_out();
					if (result) {
						std::cout << "You have successfully logged out of your account!\n";
					}
					else {
						std::cout << "You are no longer logged in.\n";
					}
					break;
				case 4:
					result = this->info();
					if (!result) {
						std::cout << "You are no longer logged in.\n";
					}
					break;
				}
			}
			else {
				break;
			}
		}
	}

	bool sing_in(std::string login, std::string password) {
		if (this->login == "\0") {
			if (!this->manager->access(login)) {
				this->manager->add(login, password);
				this->login = login;
				this->password = password;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	bool log_in(std::string login, std::string password) {
		if (this->login == "\0") {
			if (this->manager->access(login, password)) {
				this->login = login;
				this->password = password;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	bool log_out() {
		if (this->login != "\0") {
			this->login = "\0";
			this->password = "\0";
			return true;
		}
		else {
			return false;
		}
	}

	bool info() {
		if (this->login != "\0") {
			std::cout << "You are currently logged in: " << this->login << std::endl;
			return true;
		}
		else {
			return false;
		}
	}

	CLIManager(AccountManger* manager) {
		this->manager = manager;
	}
	CLIManager(){}
private:
	AccountManger* manager = new AccountManger();

	std::string login = "\0";
	std::string password = "\0";
};
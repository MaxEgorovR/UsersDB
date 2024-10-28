#pragma once
#include <iostream>
#include <sqlite_modern_cpp.h>
#include <string>

class AccountManger {
public:
	bool access(std::string login) {
		int count;

		db << "select count(*) from users where login = ?;" << login >> count;
		if (count > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool access(std::string login, std::string password) {
		int count;

		db << "select count(*) from users where login = ? AND password = ?;" << login << password >> count;
		if (count > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool add(std::string login, std::string password) {
		int count;
		db << "select count(*) from users where login = ?;" << login >> count;
		if (count == 0) {
			db << u"insert into users (login, password) values (?,?);"
				<< login
				<< password;
			return true;
		}
		else {
			return false;
		}
	}

	AccountManger()
	{
		db << "create table if not exists users ("
			"	id integer primary key autoincrement not null,"
			"	login text,"
			"	password text"
			");";
	}
private:
	sqlite::database db{ "database.db" };
};
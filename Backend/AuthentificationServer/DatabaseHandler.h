#pragma once
#include <pqxx/pqxx>

class DatabaseHandler {
public:
	DatabaseHandler(const std::string& localHost , int16_t port , const std::string& dbName ,
		const std::string& user , const std::string& password);
	~DatabaseHandler();
	bool isNameTaken(const char* name);
	bool addUser(const char* name, const char* email, const char* password);
private:
	static std::string createConnectionString(const std::string& localHost, int16_t port, const std::string& dbName,
		const std::string& user, const std::string& password);
private:
	std::unique_ptr<pqxx::connection> conn;
};
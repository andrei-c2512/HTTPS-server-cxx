#include "DatabaseHandler.h"
#include "ConsoleLog.h"


DatabaseHandler::DatabaseHandler(const std::string& localHost, int16_t port, const std::string& dbName,
	const std::string& user, const std::string& password) 
{
	ConsoleLog::info(createConnectionString(localHost, port, dbName, user, password));
	//if it doesn't crash then it connected , that's how libpqxx works
	try {
		conn = std::make_unique<pqxx::connection>(createConnectionString(localHost, port, dbName, user, password));
		ConsoleLog::message("Sucessfully connected to the database!");
	}
	catch (const std::exception& e) {
		ConsoleLog::error(e.what());
	}
	catch (...) {
		ConsoleLog::error("Something went wrong");
	}
}

DatabaseHandler::~DatabaseHandler() {
	try {
		pqxx::work worker(*conn);
		worker.exec_params("DELETE * FROM person WHERE name = '$1';", "Apetrei");
		worker.commit();
	}
	catch (std::exception& e) {
		ConsoleLog::error(e.what());
	}
}

std::string DatabaseHandler::createConnectionString(
	const std::string& localHost, int16_t port, const std::string& dbName,
	const std::string& user, const std::string& password) 
{
	return "host=" + localHost +
		" port=" + std::to_string(port) +
		" dbname=" + dbName +
		" user=" + user +
		" password=" + password +
		" connect_timeout=2";
}
bool DatabaseHandler::isNameTaken(const char* name)  {
	try {
		pqxx::work worker(*conn);

		return worker.exec_params("SELECT id FROM person WHERE name = $1 LIMIT 1;" , name)
			.empty() == false;
	}
	catch (const std::exception& e) {
		ConsoleLog::error(e.what());
		return false;
	}
}

bool DatabaseHandler::addUser(const char* name, const char* email, const char* password) {
	try {
		pqxx::work worker(*conn);
		worker.exec_params("INSERT INTO person (name , email , password) VALUES ( $1 , $2 , $3);" , name , email , password);
		worker.commit();
		return true;
	}
	catch (const std::exception& e) {
		ConsoleLog::error(e.what());
		return false;
	}
}
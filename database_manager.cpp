//
// Created by Vladimir Shubarin on 27.05.2021.
//

#include "database_manager.hpp"
#include <QMessageBox>
#include <QSettings>
#include <QtConcurrent>
#include <spdlog/spdlog.h>

pqxx::connection *DatabaseManager::connect(const QString &connectionString)
{
    pqxx::connection *connection{nullptr};
    try {
        connection = new pqxx::connection(connectionString.toStdString());
    } catch (const std::exception &e) {
        spdlog::error(e.what());
        return nullptr;
    }
    spdlog::info(std::string("Connected to: ") + connection->username() + "@" + connection->hostname() + ":"
                 + connection->port() + "/" + connection->dbname());
    return connection;
}

DatabaseManager::DatabaseManager()
{
    updateServerList();
}

/**
 * @brief loads data about servers from computer storage
 * @param serverListToFill ref to QList<Server> that you want to fill
 */
void DatabaseManager::loadServers(QList<Server> &serverListToFill)
{
    serverListToFill.clear();
    auto settings_loc = new QSettings("vhundef", "DB_Coursework");
    int size = settings_loc->beginReadArray("db/servers");
    for (int i = 0; i < size; ++i) {
        settings_loc->setArrayIndex(i);
        Server server;
        server.host = settings_loc->value("host").toString();
        server.port = settings_loc->value("port").toString();
        server.user = settings_loc->value("user").toString();
        server.password = settings_loc->value("password").toString();
        server.db = settings_loc->value("db").toString();
        serverListToFill.push_back(server);
    }
    settings_loc->endArray();
}

QString DatabaseManager::constructConnectionString(Server &server)
{
    return "host= " + server.host + " user=" + server.user + " port= " + server.port + " dbname= " + server.db
           + " password= " + server.password + " connect_timeout= 4";
}

pqxx::connection *DatabaseManager::connect(Server &server)
{
    return connect(constructConnectionString(server));
}

QList<Server> &DatabaseManager::servers()
{
    if (serverList.empty()) {
        updateServerList();
    }
    return serverList;
}
const pqxx::connection &DatabaseManager::connection()
{
    return *dbConnection;
}
void DatabaseManager::updateServerList()
{
    loadServers(serverList);
}

void DatabaseManager::addServer(Server &server)
{
    serverList.append(server);
}
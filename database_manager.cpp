//
// Created by Vladimir Shubarin on 27.05.2021.
//

#include "database_manager.hpp"
#include <QMessageBox>
#include <QSettings>
#include <QtConcurrent>
#include <spdlog/spdlog.h>

DatabaseManager::DatabaseManager()
{
    dbWorker = new DatabaseWorker;
    dbWorker->moveToThread(&workerThread);
    //
    connect(&workerThread, &QThread::finished, dbWorker, &QObject::deleteLater);

    // Server Availability related
    connect(this, &DatabaseManager::isServerAvailable, dbWorker, &DatabaseWorker::isServerAvailable);
    connect(dbWorker, &DatabaseWorker::serverAvailabilityResult, this, &DatabaseManager::serverAvailabilityResult);

    connect(this, &DatabaseManager::loadData, dbWorker, &DatabaseWorker::loadData);

    connect(dbWorker, &DatabaseWorker::connectionEstablished, this, &DatabaseManager::connectToServer);
    //  connect(worker, &DatabaseWorker::serverAvailabilityResult, this, &DatabaseManager::serverAvailabilityResult);
    //
    workerThread.start();
    updateServerList();
}

DatabaseManager::~DatabaseManager()
{
    workerThread.quit();
    workerThread.wait();
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

QList<Server> &DatabaseManager::servers()
{
    if (serverList.empty()) {
        updateServerList();
    }
    return serverList;
}
pqxx::connection *DatabaseManager::connection()
{
    return dbConnection;
}
void DatabaseManager::updateServerList()
{
    loadServers(serverList);
}

void DatabaseManager::addServer(Server &server)
{
    serverList.append(server);
}
void DatabaseManager::closeConnection()
{
    if (dbConnection != nullptr) {
        dbConnection->close();
        dbConnection = nullptr;
    }
}
DatabaseWorker *DatabaseManager::worker()
{
    return dbWorker;
}
void DatabaseManager::connectToServer(pqxx::connection *connection_)
{
    spdlog::info("DatabaseManager::ConnectToServer: connected");
    dbConnection = connection_;
}

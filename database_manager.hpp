//
// Created by Vladimir Shubarin on 27.05.2021.
//

#ifndef DB_COURSEWORK__DATABASE_MANAGER_HPP_
#define DB_COURSEWORK__DATABASE_MANAGER_HPP_

#include "Common.hpp"
#include <QList>
#include <pqxx/connection>
class DatabaseManager
{
public:
    [[nodiscard]] QList<Server> &servers();
    [[nodiscard]] const pqxx::connection &connection();
    [[nodiscard]] static pqxx::connection *connect(const QString &connectionString);
    static pqxx::connection *connect(Server &server);
    void updateServerList();
    void updateServerList(QList<Server>);
    DatabaseManager();
    bool addServer(Server &server);

private:
    QList<Server> serverList;

    pqxx::connection *dbConnection{nullptr};
    static void loadServers(QList<Server> &serverListToFill);
    static QString constructConnectionString(Server &server);
};

#endif // DB_COURSEWORK__DATABASE_MANAGER_HPP_

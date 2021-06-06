//
// Created by Vladimir on 06.06.2021.
//

#ifndef DB_COURSEWORK__DATABASE_WORKER_HPP_
#define DB_COURSEWORK__DATABASE_WORKER_HPP_

#include <QObject>
#include <pqxx/connection>
#include <spdlog/spdlog.h>
class DatabaseWorker : public QObject
{
    Q_OBJECT

private:
    pqxx::connection *connect(QString &connectionString)
    {
        pqxx::connection *connection{nullptr};
        try {
            connection = new pqxx::connection(connectionString.toStdString());
        } catch (const std::exception &e) {
            spdlog::error(e.what());
            emit connectionEstablished(nullptr);
            return nullptr;
        }
        spdlog::info(std::string("Connected to: ") + connection->username() + "@" + connection->hostname() + ":"
                     + connection->port() + "/" + connection->dbname());
        return connection;
    }
    QString constructConnectionString(Server &server)
    {
        return "host= " + server.host + " user=" + server.user + " port= " + server.port + " dbname= " + server.db
               + " password= " + server.password + " connect_timeout= 4";
    }
public slots:
    void connectToServer(Server *server)
    {
        QString connectionString = constructConnectionString(*server);
        emit connectionEstablished(connect(connectionString));
    }
    void isServerAvailable(Server *server)
    {
        QString connectionString = constructConnectionString(*server);
        emit serverAvailabilityResult(server, connect(connectionString) != nullptr);
    }
signals:
    void connectionEstablished(pqxx::connection *connection);
    void serverAvailabilityResult(Server *server, bool isAvailable);
};

#endif // DB_COURSEWORK__DATABASE_WORKER_HPP_

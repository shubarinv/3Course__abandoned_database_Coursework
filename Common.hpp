//
// Created by Vladimir on 26.05.2021.
//

#ifndef DB_COURSEWORK__COMMON_HPP_
#define DB_COURSEWORK__COMMON_HPP_
#include <QString>

struct Server
{
    QString host {}, port {}, db {}, user {}, password {};
    bool    operator==(const Server &rhs) const
    {
        return (this->host == rhs.host && this->port == rhs.port && this->user == rhs.user && this->db == rhs.db &&
                this->password == this->password);
    }
};

#endif // DB_COURSEWORK__COMMON_HPP_

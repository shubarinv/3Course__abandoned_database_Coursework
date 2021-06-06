//
// Created by Vladimir on 26.05.2021.
//

#ifndef DB_COURSEWORK__SELECT_SERVER_UI_HPP_
#define DB_COURSEWORK__SELECT_SERVER_UI_HPP_
#include "Common.hpp"
#include "database_manager.hpp"
#include <QDialog>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QTableWidget>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class SelectServerUI : public QDialog
{
    Q_OBJECT
public:
    explicit SelectServerUI(DatabaseManager *dbManager);

private:
    QString windowTitle = "Select Server"; ///< title that is used as window title and header
    QGridLayout gridLayout;
    QWidget mainWidget;
    DatabaseManager *dbManager{nullptr};

    // UI elements
    QLabel headerLabel;

    QPushButton add_btn;
    QPushButton remove_btn;
    QPushButton edit_btn;
    QPushButton refresh_btn;
    QPushButton useSelected_btn;

    QTableWidget table_wgt;

    QSpacerItem *spacer{};

    void setupLayout(); ///< sets ui elements locations
    void initializeElements();
    void setupSlotsAndConnections();
    void fillTable();
    void addServer();
    void reject() override;
    static QString constructServerListString(Server &serverData);

public slots:
    void handleServerAvailabilityResult(Server *server, bool isAvailable);
    void updateServerStatus(Server *server, const QString &newStatus);
    void updateServersAvailability();

signals:
    void dialogRejected();
};

#endif // DB_COURSEWORK__SELECT_SERVER_UI_HPP_

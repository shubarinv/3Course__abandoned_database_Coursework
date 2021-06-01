//
// Created by Vladimir on 31.05.2021.
//

#include "db_ui.hpp"
#include "Common.hpp"
#include <QGuiApplication>
#include <QScreen>
#include <QTableWidget>
#include <spdlog/spdlog.h>
DbUI::DbUI()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    resize(width / 2, height / 2);
    initializeElements();
    setupUI();
}
void DbUI::initializeElements()
{
    setLayout(&gridLayout);
    // initializing buttons
    back_btn.setText("<-");
    add_btn.setText("Добавить");
    edit_btn.setText("Редактировать");
    delete_btn.setText("Удалить");
}
void DbUI::setupUI()
{

    table_widget.setColumnCount(2);
    table_widget.setHorizontalHeaderLabels({"Server", "Status"});
    table_widget.setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget.setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget.verticalHeader()->hide();

    add_btn.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    edit_btn.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    delete_btn.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    table_widget.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    gridLayout.addWidget(&back_btn, 0, 0);
    gridLayout.addWidget(&table_widget, 1, 0, 3, 1);
    gridLayout.addWidget(&add_btn, 1, 1);
    gridLayout.addWidget(&edit_btn, 2, 1);
    gridLayout.addWidget(&delete_btn, 3, 1);

    // Font size related manipulations
    auto font = back_btn.font();
    font.setPixelSize(20);

    back_btn.setFont(font);
    add_btn.setFont(font);
    edit_btn.setFont(font);
    delete_btn.setFont(font);
}
void DbUI::setupConnections()
{
    spdlog::info("DB_UI::setupConnections");
    connect(&back_btn, &QPushButton::clicked, this, [this]() {
        spdlog::info("Layout switch: Whatever->mainMenu");
        close();
    });
}
void DbUI::setTableHeaders(const QList<QString> &tableHeaders)
{
    table_widget.setColumnCount(tableHeaders.size());
    table_widget.setHorizontalHeaderLabels(tableHeaders);
}
// ContractsUI Class
void ContractsUI::setupConnections()
{
    spdlog::info("ContractsUI::setupConnections");
    DbUI::setupConnections();
}
ContractsUI::ContractsUI() : DbUI() {}
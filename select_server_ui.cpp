//
// Created by Vladimir on 26.05.2021.
//

#include "select_server_ui.hpp"
#include "input_dialog.hpp"
#include <QFormLayout>
#include <QLineEdit>
SelectServerUI::SelectServerUI(DatabaseManager *dbManager) : dbManager(dbManager)
{
    if (dbManager == nullptr) {
        spdlog::critical("SelectServerUI::SelectServerUI: error Pointer to DatabaseManger is NULL");
    }
    setWindowTitle(windowTitle);
    spdlog::info("SelectServerUI::construct");
    initializeElements();
    setupLayout();
    setupSlotsAndConnections();
    fillTable();
}
void SelectServerUI::initializeElements()
{
    spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    headerLabel.setText(windowTitle);
    add_btn.setText("+");
    remove_btn.setText("-");
    edit_btn.setText("✎");
    refresh_btn.setText("Refresh");
    useSelected_btn.setText("Use selected");

    // size policies(states how widgets behave on expansion)
    headerLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    add_btn.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    remove_btn.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    edit_btn.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    refresh_btn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    useSelected_btn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    auto font = headerLabel.font();
    font.setPixelSize(20);
    headerLabel.setFont(font);

    // Settings for table
    table_wgt.setColumnCount(2);
    table_wgt.setHorizontalHeaderLabels({"Server", "Status"});
    table_wgt.verticalHeader()->hide();
    table_wgt.setSelectionBehavior(QAbstractItemView::SelectRows);
    table_wgt.setSelectionMode(QAbstractItemView::SingleSelection);
    table_wgt.horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table_wgt.horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table_wgt.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    table_wgt.resizeRowsToContents();
    table_wgt.resizeColumnsToContents();

    gridLayout.setHorizontalSpacing(2);
}
void SelectServerUI::setupLayout()
{
    setLayout(&gridLayout);
    gridLayout.addWidget(&headerLabel, 0, 0);
    gridLayout.addWidget(&table_wgt, 1, 0, 4, 2);
    gridLayout.addWidget(&add_btn, 1, 2);
    gridLayout.addWidget(&remove_btn, 2, 2);
    gridLayout.addWidget(&edit_btn, 3, 2);
    gridLayout.addItem(spacer, 4, 1);
    gridLayout.addWidget(&refresh_btn, 5, 0);
    gridLayout.addWidget(&useSelected_btn, 5, 1, 1, 1);
}
void SelectServerUI::setupSlotsAndConnections()
{
    connect(&add_btn, &QPushButton::clicked, this, [this]() { addServer(); });
    connect(&refresh_btn, &QPushButton::clicked, this, [this]() { fillTable(); });
    connect(&useSelected_btn, &QPushButton::clicked, this, [this]() {
        dbManager->connect(dbManager->servers()[table_wgt.selectedItems()[0]->row()], true);
        close();
    });

    connect(&table_wgt, &QTableWidget::clicked, this, [=, this](const QModelIndex &index) {
        spdlog::info("{}:{}", index.row(), table_wgt.item(index.row(), 0)->text().toUtf8().toStdString());
        if (table_wgt.item(index.row(), 1)->text() == "Bad") {
            table_wgt.clearSelection();
            spdlog::info("serverSelection: removed selection from {}: BAD SERVER",
                         table_wgt.item(index.row(), 0)->text().toStdString());
            useSelected_btn.setDisabled(true);
        } else {
            useSelected_btn.setEnabled(true);
        }
    });
}

void SelectServerUI::fillTable()
{
    table_wgt.setRowCount(0);

    for (auto &srv : dbManager->servers()) {
        table_wgt.insertRow(table_wgt.rowCount());
        table_wgt.setItem(table_wgt.rowCount() - 1, 0, new QTableWidgetItem(constructServerListString(srv)));

        if (dbManager->connect(srv, false) != nullptr) {
            table_wgt.setItem(table_wgt.rowCount() - 1, 1, new QTableWidgetItem("OK"));
        } else {
            table_wgt.setItem(table_wgt.rowCount() - 1, 1, new QTableWidgetItem("Bad"));
        }
    }
}

/**
 * @brief Constructs string that is used in Server list
 * @param serverData pointer to Server(instance) that contains data about connection
 * @return string in format  [user]@[host]:[port]/[database_name]
 */
QString SelectServerUI::constructServerListString(Server &serverData)
{
    return serverData.user + "@" + serverData.host + ":" + serverData.port + "/" + serverData.db;
}
void SelectServerUI::addServer()
{

    InputDialog inputDialog;
    inputDialog.setTitle("Add Server");

    inputDialog.addField("Hostname");
    inputDialog.addField("Port", new QIntValidator(1, 65525, &inputDialog));
    inputDialog.addField("User");
    inputDialog.addField("Password", nullptr, QLineEdit::Password);
    inputDialog.addField("Database name");
    inputDialog.exec();

    if (!inputDialog.getResults().empty()) {
        Server newServer;
        newServer.host = inputDialog.getResults().front();
        inputDialog.getResults().pop_front();
        newServer.port = inputDialog.getResults().front();
        inputDialog.getResults().pop_front();
        newServer.db = inputDialog.getResults().front();
        inputDialog.getResults().pop_front();
        newServer.user = inputDialog.getResults().front();
        inputDialog.getResults().pop_front();
        newServer.password = inputDialog.getResults().front();
        inputDialog.getResults().pop_front();
        spdlog::info("Added new server: {}", constructServerListString(newServer).toStdString());
        dbManager->addServer(newServer);
        fillTable();
    }
}

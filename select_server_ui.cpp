//
// Created by Vladimir on 26.05.2021.
//

#include "select_server_ui.hpp"
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
}

void SelectServerUI::fillTable()
{
    // filling table with servers and their status
    for (auto &srv : dbManager->servers()) {
        table_wgt.insertRow(table_wgt.rowCount());
        table_wgt.setItem(table_wgt.rowCount() - 1, 0, new QTableWidgetItem(constructServerListString(srv)));

        if (DatabaseManager::connect(srv) != nullptr) {
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
    spdlog::info("SelectServerUI::AddServerUI construct");
    QString addServer_label = "Add Server";
    QDialog addServerUI;
    addServerUI.setModal(true);

    // Layouts
    QGridLayout addServerGridLayout;  // main layout
    QFormLayout addServer_formLayout; // this layout holds input form

    addServerUI.setLayout(&addServerGridLayout);

    // Validators
    QValidator *validator = new QIntValidator(1, 65525, this);

    QLabel addServer_headerLabel;
    auto font = addServer_headerLabel.font();
    font.setPixelSize(20);
    addServer_headerLabel.setFont(font);

    // fields
    QLineEdit hostname_inp;
    QLineEdit port_inp;
    QLineEdit user_inp;
    QLineEdit password_inp;
    QLineEdit dbName_inp;

    // buttons
    QPushButton cancel_btn;
    QPushButton save_btn;

    // setting text to buttons and label
    addServerUI.setWindowTitle(addServer_label);
    addServer_headerLabel.setText(addServer_label);
    cancel_btn.setText("Cancel");
    save_btn.setText("Save");

    // per field settings
    port_inp.setValidator(validator);
    password_inp.setEchoMode(QLineEdit::Password);

    addServerGridLayout.addWidget(&addServer_headerLabel, 0, 0);
    addServerGridLayout.addLayout(&addServer_formLayout, 1, 0, 1, 2);
    addServerGridLayout.addWidget(&cancel_btn, 2, 0);
    addServerGridLayout.addWidget(&save_btn, 2, 1);

    addServer_formLayout.addRow("Hostname", &hostname_inp);
    addServer_formLayout.addRow("Port", &port_inp);
    addServer_formLayout.addRow("User", &user_inp);
    addServer_formLayout.addRow("Password", &password_inp);
    addServer_formLayout.addRow("Database name", &dbName_inp);

    addServerUI.exec();

    connect(&save_btn, &QPushButton::clicked, this, [&, this]() {
        Server newServer;
        newServer.host = hostname_inp.text();
        newServer.port = port_inp.text();
        newServer.db = dbName_inp.text();
        newServer.user = user_inp.text();
        newServer.password = password_inp.text();

        if (dbManager->addServer(newServer)) {
            addServerUI.close();
        }
    });
}

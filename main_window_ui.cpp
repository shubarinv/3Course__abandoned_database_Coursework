//
// Created by Vladimir on 27.05.2021.
//

#include "main_window_ui.hpp"
#include "db_ui.hpp"
#include "select_server_ui.hpp"
#include <QPushButton>
#include <spdlog/spdlog.h>
MainWindowUI::MainWindowUI(QPair<int, int> screenSize)
{
    dbManager = new DatabaseManager();
    resize(screenSize.first / 2, screenSize.second / 2);
    if (dbManager->connection() == nullptr) {
        drawSelectServerUI();
    }
    drawMainMenu();
}

void MainWindowUI::drawSelectServerUI() const
{
    SelectServerUI selectServerUI(dbManager);
    selectServerUI.exec();
}

void MainWindowUI::drawMainMenu()
{
    spdlog::info("Drawing main menu");
    mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    mainWidget->show();
    gridLayout = new QGridLayout(mainWidget);

    // initializing buttons
    auto suppliers_btn = new QPushButton("Поставщики");
    auto checkForm_btn = new QPushButton("Формирование чека");
    auto report_btn = new QPushButton("Отчёт");
    auto contracts_btn = new QPushButton("Договора");
    auto merchandise_btn = new QPushButton("Товары");
    auto shipments_btn = new QPushButton("Поставки");
    auto help_btn = new QPushButton("Справка");

    // Font size related manipulations
    auto font = suppliers_btn->font();
    font.setPixelSize(20);

    // increasing buttons font size
    suppliers_btn->setFont(font);
    checkForm_btn->setFont(font);
    report_btn->setFont(font);
    contracts_btn->setFont(font);
    merchandise_btn->setFont(font);
    shipments_btn->setFont(font);
    help_btn->setFont(font);

    gridLayout->addWidget(suppliers_btn, 0, 0);
    gridLayout->addWidget(checkForm_btn, 0, 1);
    gridLayout->addWidget(report_btn, 0, 2);
    gridLayout->addWidget(contracts_btn, 1, 0);
    gridLayout->addWidget(merchandise_btn, 1, 1);
    gridLayout->addWidget(shipments_btn, 1, 2);
    gridLayout->addWidget(help_btn, 2, 1);

    suppliers_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    checkForm_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    report_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    contracts_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    merchandise_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    shipments_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    help_btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    connect(suppliers_btn, &QPushButton::clicked, this,
            [this]() { spdlog::info("Layout switch: mainMenu->suppliersMenu"); });
    connect(contracts_btn, &QPushButton::clicked, this, [this]() {
        spdlog::info("Layout switch: mainMenu->contractsMenu");
        std::function<void()> drawFunc = [this] { drawMainMenu(); };
        hide();
        ContractsUI contract;
        contract.setupConnections();
        contract.exec();
        show();
    });
    update();
}
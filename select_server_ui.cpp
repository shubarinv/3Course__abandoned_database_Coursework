//
// Created by Vladimir on 26.05.2021.
//

#include "select_server_ui.hpp"
SelectServerUI::SelectServerUI()
{
    setWindowTitle(windowTitle);
    spdlog::info("SelectServerUI::construct");
    initializeElements();
    setupLayout();
    setupSlotsAndConnections();
}
void SelectServerUI::initializeElements()
{
    spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    headerLabel.setText(windowTitle);
    headerLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    add_btn.setText("+");
    add_btn.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    remove_btn.setText("-");
    remove_btn.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    edit_btn.setText("✎");
    edit_btn.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    refresh_btn.setText("Refresh");
    refresh_btn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    useSelected_btn.setText("Use selected");
    useSelected_btn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    table_wgt.setColumnCount(2);
    table_wgt.setRowCount(20);
    table_wgt.setHorizontalHeaderLabels({"Server", "Status"});
    table_wgt.verticalHeader()->hide();
    table_wgt.setSelectionBehavior(QAbstractItemView::SelectRows);
    table_wgt.setSelectionMode(QAbstractItemView::SingleSelection);

    auto font = headerLabel.font();
    font.setPixelSize(20);
    headerLabel.setFont(font);

    table_wgt.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
void SelectServerUI::setupSlotsAndConnections() {}

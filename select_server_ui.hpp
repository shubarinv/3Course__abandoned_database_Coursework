//
// Created by Vladimir on 26.05.2021.
//

#ifndef DB_COURSEWORK__SELECT_SERVER_UI_HPP_
#define DB_COURSEWORK__SELECT_SERVER_UI_HPP_
#include "Common.hpp"
#include <QDialog>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class SelectServerUI : public QDialog
{
    Q_OBJECT
public:
    SelectServerUI();

private:
    QString windowTitle = "Select Server"; ///< title that is used as window title and header
    QGridLayout gridLayout;
    QWidget mainWidget;

    // UI elements
    QLabel headerLabel;

    QPushButton add_btn;
    QPushButton remove_btn;
    QPushButton edit_btn;
    QPushButton refresh_btn;
    QPushButton useSelected_btn;

    QTableWidget table_wgt;

    void setupLayout();
    void initializeElements();
    void setupSlotsAndConnections();
};

#endif // DB_COURSEWORK__SELECT_SERVER_UI_HPP_

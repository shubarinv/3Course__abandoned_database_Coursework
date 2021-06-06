//
// Created by Vladimir on 27.05.2021.
//

#ifndef DB_COURSEWORK__MAIN_WINDOW_UI_HPP_
#define DB_COURSEWORK__MAIN_WINDOW_UI_HPP_

#include "database_manager.hpp"
#include <QGridLayout>
#include <QMainWindow>
class MainWindowUI : public QMainWindow
{
    Q_OBJECT;

private:
    QGridLayout *gridLayout{};
    DatabaseManager *dbManager{};
    QWidget *mainWidget{};
    bool closeWindow{false};

public:
    explicit MainWindowUI(QPair<int, int> screenSize);
    void drawMainMenu();
    void drawSelectServerUI() const;
    static void closeMainWindow();

signals:
    void closeApp();
};

#endif // DB_COURSEWORK__MAIN_WINDOW_UI_HPP_

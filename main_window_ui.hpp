//
// Created by Vladimir on 27.05.2021.
//

#ifndef DB_COURSEWORK__MAIN_WINDOW_UI_HPP_
#define DB_COURSEWORK__MAIN_WINDOW_UI_HPP_

#include <QMainWindow>
class MainWindowUI : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindowUI(QPair<int, int> screenSize);
};

#endif // DB_COURSEWORK__MAIN_WINDOW_UI_HPP_

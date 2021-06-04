//
// Created by Vladimir on 31.05.2021.
//

#ifndef DB_COURSEWORK__DB_UI_HPP_
#define DB_COURSEWORK__DB_UI_HPP_

#include <QDialog>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
class DbUI : public QDialog
{
    Q_OBJECT
protected:
    DbUI();
    void setTableHeaders(const QList<QString> &tableHeaders);
    virtual void setupConnections();

    std::function<void()> drawMainMenuCallback;

    QPushButton back_btn;
    QGridLayout gridLayout;
    QPushButton add_btn;
    QPushButton edit_btn;
    QPushButton delete_btn;
    QTableWidget table_widget;
    QLabel windowHeader;

public:
    void setWindowHeaderAndTitle(QString windowHeader_);

private:
    void initializeElements();
    void setupUI();
};

#endif // DB_COURSEWORK__DB_UI_HPP_

class ContractsUI : public DbUI
{
public:
    explicit ContractsUI();
    void setupConnections() override;
};
class SuppliersUI : public DbUI
{
public:
    explicit SuppliersUI();
    void setupConnections() override;
};
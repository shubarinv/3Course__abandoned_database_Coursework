//
// Created by Vladimir on 31.05.2021.
//

#ifndef DB_COURSEWORK__DB_UI_HPP_
#define DB_COURSEWORK__DB_UI_HPP_

#include "database_manager.hpp"
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
    explicit DbUI(DatabaseManager *);
    void setTableHeaders(const QList<QString> &tableHeaders);
    virtual void setupConnections();
    void setQueryString(const QString &query);
    std::function<void()> drawMainMenuCallback;

    QPushButton back_btn;
    QGridLayout gridLayout;
    QPushButton add_btn;
    QPushButton edit_btn;
    QPushButton delete_btn;
    QTableWidget table_widget;
    QLabel windowHeader;
    QString queryString;
    DatabaseManager *dbManager{nullptr};
    void loadDataFromDb();

public:
    void setWindowHeaderAndTitle(QString windowHeader_);

private:
    void initializeElements();
    void setupUI();

    void processQuery(QList<QString> results);
};

#endif // DB_COURSEWORK__DB_UI_HPP_

class ContractsUI : public DbUI
{
public:
    explicit ContractsUI(DatabaseManager *);
    void setupConnections() override;
};
class SuppliersUI : public DbUI
{
public:
    explicit SuppliersUI(DatabaseManager *);
    void setupConnections() override;
};
#pragma once

#include <QObject>
#include <QSqlDatabase>

class DbManager : public QObject
{
    Q_OBJECT
public:
    static DbManager& instance();

    bool init();

    bool insertMenu(const QString &name, int price, const QString &category);
    void printMenus();
    bool insertTestOrder(int tableNo);
    void printOrders();

private:
    explicit DbManager(QObject *parent = nullptr);

    bool createTables();

    QSqlDatabase m_db;
};

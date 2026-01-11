#pragma once

#include <QObject>
#include <QVariantList>
#include <QMap>

class TableManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList tableList READ tableList NOTIFY tableListChanged)

public:
    explicit TableManager(QObject *parent = nullptr);

    QVariantList tableList() const;

    Q_INVOKABLE QVariantList getOrders(int tableId);

    Q_INVOKABLE void addOrder(int tableId,
                              const QString &menu,
                              int quantity,
                              int price);

    Q_INVOKABLE void refresh();


    Q_INVOKABLE void clearTable(int tableId);

signals:
    void tableListChanged();
    void ordersChanged(int tableId);

private:
    int m_tableCount = 6;
    QVariantList m_tableList;
    QMap<int, QVariantList> m_orders;

    void loadTableStates();
};

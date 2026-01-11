#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "DbManager.h"
#include "TableManager.h"
#include "echo_server.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);


    if (!DbManager::instance().init()) {
        qWarning() << "[Main] DB init failed. Exit.";
        return -1;
    }
    qDebug() << "[DB] Drivers:" << QSqlDatabase::drivers();


    QQmlApplicationEngine engine;


    TableManager tableManager;
    EchoServer server;


    QObject::connect(
        &server,
        &EchoServer::jsonReceived,
        &tableManager,
        [&](const QString &sender, const QJsonDocument &doc) {

            Q_UNUSED(sender);

            if (!doc.isObject()) {
                qWarning() << "[Main] JSON is not object";
                return;
            }

            QJsonObject obj = doc.object();


            int tableId = -1;
            if (obj.contains("tableId"))
                tableId = obj["tableId"].toInt();
            else if (obj.contains("tabled"))
                tableId = obj["tabled"].toInt();

            qDebug() << "[Main] parsed tableId =" << tableId;

            QString menu    = obj["menu"].toString();
            int quantity    = obj["quantity"].toInt();
            int price       = obj["price"].toInt();

            qDebug() << "[Main] calling addOrder:"
                     << tableId << menu << quantity << price;

            tableManager.addOrder(tableId, menu, quantity, price);
        }
        );


    engine.rootContext()->setContextProperty("tableManager", &tableManager);
    engine.rootContext()->setContextProperty("echoServer", &server);


    const QUrl url(QStringLiteral("qrc:/KioskServer1/qml/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
        );

    engine.load(url);


    tableManager.refresh();

    return app.exec();
}

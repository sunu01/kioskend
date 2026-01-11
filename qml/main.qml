import QtQuick 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1024
    height: 768
    title: "POS Server System"


    Connections {
        target: echoServer

        function onJsonReceived(address, doc) {
            console.log("📥 JSON from", address, JSON.stringify(doc))


            var page = stackView.currentItem
            if (!page)
                return


            if (page.tableId === undefined || typeof page.addOrder !== "function")
                return


            if (page.tableId !== doc.tableId)
                return


            page.addOrder(doc.menu, doc.quantity, doc.price)
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainMenu
    }

    Component {
        id: mainMenu

        Rectangle {
            anchors.fill: parent
            color: "#2E2E2E"

            Column {
                spacing: 20
                anchors.centerIn: parent

                Button {
                    text: "서버 관리"
                    width: 200
                    height: 60
                    onClicked: stackView.push("ServerPage.qml")
                }

                Button {
                    text: "POS 테이블 화면"
                    width: 200
                    height: 60
                    onClicked: stackView.push("TablePage.qml")
                }
            }
        }
    }
}

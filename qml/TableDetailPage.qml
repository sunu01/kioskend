import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: detailPage
    anchors.fill: parent

    property int tableId: -1

    HeaderBar {
        id: header
        title: tableId + "번 테이블"
        anchors.top: parent.top
    }

    Rectangle {
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#1F1F1F"

        Column {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 16

            //주문 리스트 영역
            Rectangle {
                width: parent.width
                height: 320
                color: "transparent"

                ListView {
                    id: orderList
                    anchors.fill: parent
                    clip: true
                    model: tableManager.getOrders(tableId)

                    delegate: Rectangle {
                        width: orderList.width
                        height: 50
                        radius: 6
                        color: "#2A2A2A"

                        Row {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 10

                            Text {
                                text: modelData.menu
                                color: "white"
                                width: 120
                            }

                            Text {
                                text: modelData.quantity + "개"
                                color: "#CCCCCC"
                                width: 60
                            }

                            Text {
                                text: modelData.price + " 원"
                                color: "#CCCCCC"
                                width: 80
                            }
                        }
                    }
                }
            }

            Text {
                text: "총 금액: " + totalPrice() + " 원"
                color: "white"
                font.pixelSize: 20
                font.bold: true
            }

            Row {
                spacing: 16

                Button {
                    text: "주문 추가(테스트)"
                    onClicked: {
                        tableManager.addOrder(
                            tableId,
                            "아메리카노",
                            1,
                            4000
                        )
                    }
                }

                Button {
                    text: "테이블 초기화"
                    onClicked: tableManager.clearTable(tableId)
                }
            }
        }
    }

    //서버 주문 실시간 반영
    Connections {
        target: tableManager

        function onOrdersChanged(id) {
            if (id === tableId) {
                orderList.model = tableManager.getOrders(tableId)
            }
        }
    }

    // 총 금액 계산 (TableManager 기반)
    function totalPrice() {
        var orders = tableManager.getOrders(tableId)
        var sum = 0

        for (var i = 0; i < orders.length; i++) {
            sum += orders[i].price * orders[i].quantity
        }
        return sum
    }
}

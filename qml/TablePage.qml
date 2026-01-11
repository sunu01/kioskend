import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: tablePage
    title: "테이블 현황"

    Component.onCompleted: {
        console.log("TablePage LOADED")
    }

    contentItem: Column {
        spacing: 0

        // 헤더
        HeaderBar {
            id: header
            title: "테이블 현황"
        }

        // 본문 영역
        Rectangle {
            color: "#1F1F1F"
            width: parent.width
            height: parent.height - header.height

            GridView {
                id: tableGrid

                //중앙 정렬
                anchors.centerIn: parent

                cellWidth: 200
                cellHeight: 180
                width: cellWidth * 3
                height: cellHeight * 2

                model: tableManager.tableList

                delegate: TableCard {
                    width: 180
                    height: 150

                    tableNumber: modelData.id
                    occupied: modelData.busy
                    statusText: modelData.busy
                        ? (modelData.total + " 원")
                        : "비어있음"

                    onClicked: {
                        stackView.push("TableDetailPage.qml", {
                            tableId: tableNumber
                        })
                    }
                }
            }
        }
    }
}

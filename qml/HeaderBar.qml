import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: header
    height: 60
    width: parent.width
    color: "#1E1E1E"

    property string title: ""

    Item {
        id: leftSlot
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        text: header.title
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: 20
        font.bold: true
    }

    Item {
        id: rightSlot
        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.verticalCenter: parent.verticalCenter
    }

    Button {
        text: "←"
        parent: leftSlot
        onClicked: stackView.pop()
    }
}

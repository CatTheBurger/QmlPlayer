import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: body

    property var cColor: "#298b8f"
    property var tColor: "#FFF"
    property var bColor: "#262626"
    property var aText: "Hello, World"
    property var valueChangeSignaleEnable: true
    property var value: 0
    property var currentX: 0

    signal sliderMoved()

    function cursorMoved(mouseX) {
        console.log("moved to " + cursor.x);
        progress.width = cursor.x + cursor.width;
        progressPreview.width = mouseX + cursor.width / 2;
        currentX = cursor.x;

        if (valueChangeSignaleEnable) {
            console.log("Move event!");
            sliderMoved();
        }
    }

    function setValue(inValue) {
        var v = Math.abs(cursor.x - (background.width * (inValue / 100)));

        cursor.x += v;
        progress.width = cursor.x + cursor.width;

        value = v;
    }

    function getValue() {
        return value;
    }

    Text {
        id: additionalText
        z: 2
        height: parent.height
        color: tColor
        text: aText

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: 10

        anchors.left: body.left
        anchors.leftMargin: 5
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        drag.target: this
        drag.minimumY: 0
        drag.maximumY: 0
        drag.minimumX: 0
        drag.maximumX: background.width - 15

//        onDragChanged: {
//            cursor.x = mouseX - cursor.width / 2;
//            console.log("moved to " + cursor.x);
//            progress.width = cursor.x + cursor.width;
//            progressPreview.width = mouseX + cursor.width / 2;
//        }

        onClicked: function() {
            cursor.x = mouseX - cursor.width / 2;
            cursorMoved(mouseX);
        }

        onMouseXChanged: function() {
            progressPreview.width = mouseX + cursor.width / 2;
        }

        onExited: function() {
            progressPreview.width = 0;
        }
    }

    Rectangle {
        z: 1
        id: cursor
        width: parent.height
        height: parent.height
        color: cColor
        radius: 90

        MouseArea {
            anchors.fill: parent

            drag.target: cursor
            drag.minimumY: 0
            drag.maximumY: 0
            drag.minimumX: 0
            drag.maximumX: background.width - 15

            onPositionChanged: {
                cursorMoved(mouseX);
            }
        }
    }

    Rectangle {
        z: 1
        id: progressPreview
        width: 0
        height: parent.height
        color: cColor
        opacity: 0.3
        radius: 90
    }

    Rectangle {
        z: 1
        id: progress
        width: 0
        height: parent.height
        color: cColor
        radius: 90
    }

    Rectangle {
        z: 0
        id: background
        anchors.fill: parent
        color: bColor
        radius: 45
    }
}


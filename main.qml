import QtQuick 2.15
import QtQuick.Window 2.15
import com.video.decoder 1.0
import com.video.preview 1.0

Window {
    id: window
    width: 640
    height: 360
    visible: true
    title: qsTr("Hello World")
    color: "#000"

    VideoDecoder {
        id: decoder

        Component.onCompleted: {
            //decoder.setFile("/mnt/media/Temp/vid.mp4");
            decoder.setFile("/mnt/media/Videos/vid_original.mp4");
            preview.start();
        }
    }

    Column {
        id: body
        anchors.fill: parent

        PreviewFrame {
            id: preview
            anchors.fill: parent

            function start() {
                console.log("Completed!");

                setFrame(decoder.extractQImage());
            }
        }

        Row {
            id: bottom_panel
            width: parent.width
            height: 30
            anchors.bottom: preview.bottom

            Text {
                id: time
                height: parent.height
                color: "#FFF"
                text: "0:00"

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                minimumPixelSize: 17
                minimumPointSize: 17

                anchors.left: bottom_panel.left
                anchors.leftMargin: 3
            }

            VideoSlider {
                anchors.left: time.right
                anchors.leftMargin: 3
                width: parent.width - time.width - 5
                height: parent.height
            }
        }
    }
}

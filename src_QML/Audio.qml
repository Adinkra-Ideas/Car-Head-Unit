import QtQuick
import QtMultimedia

Item {
    implicitHeight: Screen.height

    ListView {
        id: theListView
        anchors {
            fill: parent
            topMargin: 55       // TopControls height == 40
            leftMargin: 10
            rightMargin: 10
            bottomMargin: 90    // MediaControls height == 55
        }

        property int delegateHeight: 40

        model: Car.audiopaths
        delegate: Item {
            width: parent.width
            height: theListView.delegateHeight
            Text {
                text: modelData.slice(modelData.lastIndexOf('/') + 1)
                color: index % 2 ? "grey" : "yellow"
                font.pointSize: 12
            }
            MouseArea {
                anchors.fill : parent
                onClicked: {
                    Car.activeMedia = modelData
                    Car.audio = MediaPlayer.PlayingState
                }
            }
        }
    }
}

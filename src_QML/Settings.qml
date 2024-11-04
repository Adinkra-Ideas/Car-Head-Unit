import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    // anchors{
    //     left: parent.left
    //     right: parent.right
    //     top: parent.top
    //     topMargin: 50 // TopControls height == 40
    //     leftMargin: 10
    //     rightMargin: 10
    // }
    anchors{
        top: parent.top
        left: parent.left
        right: parent.right
        topMargin: 55       // TopControls height == 40
        leftMargin: 10
        rightMargin: 10
        bottomMargin: 90    // MediaControls height == 55
    }
    spacing: 10

    Item {
        id: lapCountComponent
        Layout.preferredWidth: parent.width
        Layout.preferredHeight: 42
        opacity: !Media.intervalStatus
        Text {
            id: lapCountText
            text: "Lap Count: (Secs)"
            color: "white"
            font.pointSize: 13
        }
        Slider {
            id: lapCount
            implicitWidth: parent.width * 0.7;
            implicitHeight: 20
            anchors {
                top: lapCountText.bottom
                topMargin: 3
            }
            from: 1
            value: 1
            to: 99
            stepSize: 1
        }
        TextField {
            validator: IntValidator {bottom: lapCount.from; top: lapCount.to}
            anchors {
                top: lapCountText.top
                bottom: lapCount.bottom
                left: lapCount.right
                margins: 5
            }
            color: "white"
            text: lapCount.value
            font.pointSize: 12
            background : Item {}
            onEditingFinished: {
                lapCount.value = text
            }
        }
    }

    Item {
        id: lapDurationComponent
        Layout.preferredWidth: parent.width
        Layout.preferredHeight: 42
        opacity: !Media.intervalStatus
        Text {
            id: lapDurText
            text: "Duration for each Lap: (Secs)"
            color: "white"
            font.pointSize: 13
        }
        Slider {
            id: lapDuration
            implicitWidth: parent.width * 0.7;
            implicitHeight: 20
            anchors {
                top: lapDurText.bottom
                topMargin: 3
            }
            from: 0
            value: 0
            to: 10800
            stepSize: 1
        }
        TextField {
            validator: IntValidator {bottom: lapDuration.from; top: lapDuration.to}
            anchors {
                top: lapDurText.top
                bottom: lapDuration.bottom
                left: lapDuration.right
                margins: 5
            }
            color: "white"
            text: lapDuration.value
            font.pointSize: 12
            background : Item {}
            onEditingFinished: {
                lapDuration.value = text
            }
        }
    }

    Item {
        id: restDurationComponent
        Layout.preferredWidth: parent.width
        Layout.preferredHeight: 42
        opacity: !Media.intervalStatus
        Text {
            id: restDurText
            text: "Rest: (Secs)"
            color: "white"
            font.pointSize: 13
        }
        Slider {
            id: restDuration
            implicitWidth: parent.width * 0.7;
            implicitHeight: 20
            anchors {
                top: restDurText.bottom
                topMargin: 3
            }
            from: 1
            value: 1
            to: 1800
            stepSize: 1
        }
        TextField {
            validator: IntValidator {bottom: restDuration.from; top: restDuration.to}
            anchors {
                top: restDurText.top
                bottom: restDuration.bottom
                left: restDuration.right
                margins: 5
            }
            color: "white"
            text: restDuration.value
            font.pointSize: 12
            background : Item {}
            onEditingFinished: {
                restDuration.value = text
            }
        }
    }

    Item {
        Layout.preferredWidth: parent.width
        Layout.preferredHeight: 42
        Switch {
            id: startStop
            font.pointSize: 12
            y: 10
            checked: Media.intervalStatus
            onClicked: {
                if (startStop.checked) {
                    // pass values of all three to CPP
                    Media.lapCount = lapCount.value
                    Media.lapDuration = lapDuration.value
                    Media.restDuration = restDuration.value

                    Media.intervalStatus = true;
                } else {
                    Media.intervalStatus = false;
                }
            }

            indicator: Rectangle {
                implicitWidth: 48
                implicitHeight: 20
                radius: 10
                color: startStop.checked ? "#1777B7" : "grey"

                Rectangle {
                    x: startStop.checked ? parent.width - width : 0
                    Behavior on x { NumberAnimation { duration: 200 } }
                    width: 20
                    height: 20
                    radius: 13
                    color: startStop.down ? "#cccccc" : "#ffffff"
                    border.color: startStop.checked ? (startStop.down ? "#17a81a" : "#21be2b") : "#999999"
                }
            }
        }
    }




    Rectangle {
        id: last
        color: "transparent"
        Layout.preferredWidth: parent.width
        Layout.preferredHeight: 60 // MediaControls height == 55
    }


}

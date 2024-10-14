import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Window {
    id: root
    // width: 1024
    // height: 600
    width: 768
    height: 450
    color: "black"
    visible: true
    title: qsTr("Head Unit")

    AnimatedImage {
        id: carLogo
        paused: (car.gear > 0) ? false : true;
        source: (car.gear < 2) ? "qrc:/images/HU_logo.gif" : "qrc:/images/cameraView.gif";
        anchors.top: parent.top;
        anchors.topMargin: -2;
        anchors.horizontalCenter: parent.horizontalCenter;
    }
    DropShadow {
        anchors.fill: carLogo
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 25
        color: "#1777B7"
        source: carLogo
    }

    // NavBar
    Row {
        spacing: 10;
        anchors.top: parent.top;
        anchors.topMargin: 5;
        anchors.right: parent.right;
        anchors.rightMargin: 15;

        Image { source: "qrc:/images/home.png"; width: 20; height: 20 }
        Image { source: "qrc:/images/music.png"; width: 20; height: 20 }
        Image { source: "qrc:/images/monitor.png"; width: 20; height: 20 }
        Text {
            id: timeTopRight;
            color: "#F6D101";
            text: Qt.formatTime(new Date(),"hh:mm");
            font.pointSize: 10;
        }
        Timer {
            interval: 10000
            repeat: true
            running: true
            onTriggered:
            {
                timeTopRight.text =  Qt.formatTime(new Date(),"hh:mm");
            }
        }
    }

    // LeftBar
    Column {
        spacing: 25;
        anchors.left: parent.left;
        anchors.leftMargin: 20;
        anchors.verticalCenter: parent.verticalCenter;

        AnimatedImage {
            width: 40;
            height: 25;
            paused: (car.gear === 0) ? false : true;
            source: (car.gear === 0) ? "qrc:/images/selected_gear.gif" : "";
            Text {
                color: (car.gear === 0) ? "#FF3131" : "#3B3200";
                text: "P";
                width: 50;
                height: 50;
                font.pointSize: 15;
                anchors.left: parent.left;
                anchors.leftMargin: 15;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    car.gear = 0;
                }
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: (car.gear === 1) ? false : true;
            source: (car.gear === 1) ? "qrc:/images/selected_gear.gif" : "";
            Text {
                color: (car.gear === 1) ? "#FF3131" : "#3B3200";
                text: "N";
                width: 50;
                height: 50;
                font.pointSize: 15;
                anchors.left: parent.left;
                anchors.leftMargin: 14;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    car.gear = 1;
                }
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: (car.gear === 2) ? false : true;
            source: (car.gear === 2) ? "qrc:/images/selected_gear.gif" : "";
            Text {
                color: (car.gear === 2) ? "#FF3131" : "#3B3200";
                text: "D";
                width: 50;
                height: 50;
                font.pointSize: 15;
                anchors.left: parent.left;
                anchors.leftMargin: 13;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    car.gear = 2;
                }
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: (car.gear === 3) ? false : true;
            source: (car.gear === 3) ? "qrc:/images/selected_gear.gif" : "";

            Text {
                color: (car.gear === 3) ? "#FF3131" : "#3B3200";
                text: "R";
                width: 50;
                height: 50;
                font.pointSize: 15;
                anchors.left: parent.left;
                anchors.leftMargin: 14;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    car.gear = 3;
                }
            }
        }
    }

    // acceleration control
    Slider {
        id: accelerateControl
        width: 30;
        height: 184;
        anchors.right: steeringControl.left;
        anchors.rightMargin: 80;
        anchors.verticalCenter: steeringControl.verticalCenter;
        from: 0
        value: car.speed;
        to: 4000;
        snapMode: Slider.SnapAlways;
        stepSize: 1.0;
        orientation: Qt.Vertical
        onMoved: {
            car.speed = accelerateControl.value;
        }
        background: Rectangle {
            x: (accelerateControl.width  - width) / 2
            y: (accelerateControl.height - height) / 2
            implicitWidth: accelerateControl.horizontal ? 200 : 1
            implicitHeight: accelerateControl.horizontal ? 1 : 200
            width: accelerateControl.horizontal ? accelerateControl.availableWidth : implicitWidth
            height: accelerateControl.horizontal ? implicitHeight : accelerateControl.availableHeight
            radius: 2
            color: "#FF3131"
            Rectangle {
                width: accelerateControl.visualPosition * parent.width
                height: parent.height
                color: "#3B3200"
                radius: 2
            }
        }
        handle: Rectangle {
            x: accelerateControl.leftPadding + (accelerateControl.horizontal ? accelerateControl.visualPosition * (accelerateControl.availableWidth - width) : (accelerateControl.availableWidth - width) / 2)
            y: accelerateControl.topPadding + (accelerateControl.vertical ? accelerateControl.visualPosition * (accelerateControl.availableHeight - height) : (accelerateControl.availableHeight - height) / 2)
            implicitWidth: 20
            implicitHeight: 20
            radius: width/2
            color: accelerateControl.pressed ? "#1777B7" : "#3B3200"
            ToolTip {
                x: accelerateControl.handle.implicitWidth + 5 // x offset
                y: -(accelerateControl.handle.implicitHeight / 5)
                parent: accelerateControl.handle
                visible: accelerateControl.pressed
                text: car.speed.toFixed(1) / 40 // 40 because 4000 AKA max speed of D gear, divided by 40 == 100%
                delay: 100;
                timeout: 0;
                background: Rectangle { radius: 3; border.width: 1; opacity: 0.7 }
            }
        }

    }

    // Steering Controls
    Rectangle {
        id: steeringControl
        width: 184;
        height: 184;
        radius: width / 2;
        // border.color: "blue";
        // border.width: 5;
        color: "transparent"
        anchors.bottom: wallFrameForSteering.bottom;
        anchors.bottomMargin: 25;
        anchors.horizontalCenter: parent.horizontalCenter;
        
        property alias steeringWheel: steeringWheel

        Dial {
            id: steeringWheel
            from: 0.0;
            value: car.steering;
            to: 140.0;
            snapMode: Dial.SnapAlways;
            stepSize: 1.0;
            palette.dark: "#1777B7"; //"red";
            onMoved: {
                car.steering = steeringWheel.value;
            }

            handle: Rectangle {
                id: steeringWheelHandle
                x: steeringWheel.background.x + steeringWheel.background.width / 2 - width / 2
                y: steeringWheel.background.y + steeringWheel.background.height / 2 - height / 2
                width: 16
                height: 16
                color: steeringWheel.pressed ? "#1777B7" : "#3B3200"
                radius: 8
                antialiasing: true
                opacity: steeringWheel.enabled ? 1 : 0.3
                transform: [
                    Translate {
                        y: -Math.min(steeringWheel.background.width, steeringWheel.background.height) * 0.4 + steeringWheelHandle.height / 2
                    },
                    Rotation {
                        angle: steeringWheel.angle
                        origin.x: steeringWheelHandle.width / 2
                        origin.y: steeringWheelHandle.height / 2
                    }
                ]
            }
        }
    }
    DropShadow {
        anchors.fill: steeringControl
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 25
        color: "blue"
        source: steeringControl
    }

    Image {
        id: wallFrameForSteering
        source: "qrc:/images/boardBg.png";
        width: 750;
        height: 69;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        anchors.horizontalCenter: parent.horizontalCenter;
    }
    DropShadow {
        anchors.fill: wallFrameForSteering
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 25
        color: "#1777B7"
        source: wallFrameForSteering
    }

}

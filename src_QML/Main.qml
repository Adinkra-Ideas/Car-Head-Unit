import QtQuick
import QtQuick.Window
import Qt5Compat.GraphicalEffects
import QtQuick.Controls
import QtQml

Window {
    id: root
    width: 1024
    height: 600
    minimumWidth: 640
    minimumHeight: 375
    maximumWidth: 1024
    maximumHeight: 600
    color: "black"
    visible: true
    title: qsTr("Head Unit")

    // For Dropping the Shadow
    Rectangle {
        id: changingBg
        width: root.width * 0.4885 // 500.224
        height: root.width * 0.293 // 300
        color: root.color
        anchors.top: parent.top;
        anchors.topMargin: -2;
        anchors.horizontalCenter: parent.horizontalCenter;
    }
    DropShadow {
        anchors.fill: changingBg
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 25
        color: "#1777B7"
        source: changingBg
    }

    // 1
    AnimatedImage {
        id: carLogo
        width: changingBg.width
        height: changingBg.height
        visible: true
        paused: (Car.gear > 0) ? false : true;
        source: (Car.gear < 2) ? "images/HU_logo.gif" : "images/cameraView.gif";
        anchors.fill: changingBg
    }

    // musicplayer app
    Dinkplay {
        id: dinkPlayer
        width: root.width * 0.293 // 300
        height: root.height * 0.8584 // 515
        z: 1
        color: "#191950" //root.color
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        visible: false
        // purpleOpacity: 0.5
        Behavior on width { NumberAnimation { duration: 200 } }
        MouseArea {
            id: activityListener
            anchors.fill: parent
            z: 2
            propagateComposedEvents: true
            hoverEnabled: true
            property bool inactiveMouse: false
            // hide if inactive for 10 seconds
            Timer {
                id: hideOpenedApps
                interval: 10000
                running: true
                repeat: true
                onTriggered: {
                    dinkPlayer.visible = false
                    ambientLightingControl.visible = false
                }
            }
            function mouseEventHandler(mouse) {
                hideOpenedApps.restart()
                hideOpenedApps.start()
                mouse.accepted = false
            }
            onPressed: mouse => mouseEventHandler(mouse)
            onPositionChanged: mouse => mouseEventHandler(mouse)
            onWheel: mouse => mouseEventHandler(mouse)
            onDoubleClicked: mouse => mouse.accepted = false // setting mouse.accepted to false prevents the cursor from grabbing
        }
    }
    DropShadow {
        anchors.fill: dinkPlayer
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 25
        color: "#1777B7"
        source: dinkPlayer
        visible: dinkPlayer.visible
    }

    // ambient lighting app
    Item {
        id: ambientLightingControl
        anchors {
           top: topNavbar.bottom
           left: topNavbar.left
           right: topNavbar.right
           topMargin: 10
        }
        z: 5
        visible: false
        Behavior on visible { NumberAnimation { duration: 200 } }

        Slider {
            id: ambientLightingControlSlider
            implicitWidth: parent.width;
            implicitHeight: 20
            anchors {
                top: ambientLightingControl.top
                left: ambientLightingControl.left
            }
            from: 0
            value: ambientGreenLighting.opacity
            to: 0.5
            stepSize: 0.01
            onMoved: {
                ambientGreenLighting.opacity = value
            }
        }
    }

    // NavBar
    Row {
        id: topNavbar
        spacing: 15;
        anchors.top: parent.top;
        anchors.topMargin: 5;
        anchors.right: parent.right;
        anchors.rightMargin: 15;

        Image { source: "images/monitor.png"; width: 30; height: 30
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // So that the next iteration of timer wont
                    // hide the app soon as we just opening it
                    if (!ambientLightingControl.visible) {
                        hideOpenedApps.restart()
                    }
                    ambientLightingControl.visible = !ambientLightingControl.visible
                }
            }
        }
        Image { source: "images/music.png"; width: 30; height: 30
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (!dinkPlayer.visible) {
                        hideOpenedApps.restart()
                    }
                    dinkPlayer.visible = !dinkPlayer.visible
                }
            }
        }
        Text {
            id: timeTopRight;
            color: "#F6D101";
            text: Qt.formatTime(new Date(),"hh:mm");
            font.pointSize: 15;
        }
        Timer {
            interval: 10000
            repeat: true
            running: true
            onTriggered: {
                timeTopRight.text =  Qt.formatTime(new Date(),"hh:mm");
            }
        }
    }

    // LeftBar
    Column {
        spacing: 40;
        anchors.left: parent.left;
        anchors.leftMargin: 20;
        anchors.verticalCenter: parent.verticalCenter;

        AnimatedImage {
            width: 48;
            height: 30;
            paused: (Car.gear === 0) ? false : true;
            source: (Car.gear === 0) ? "images/selected_gear.gif" : "";
            Text {
                color: (Car.gear === 0) ? "#FF3131" : "#3B3200";
                text: "P";
                width: 50;
                height: 50;
                font.pointSize: 20;
                anchors.left: parent.left;
                anchors.leftMargin: 15;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Car.gear = 0;
                }
            }
        }
        AnimatedImage {
            width: 48;
            height: 30;
            paused: (Car.gear === 1) ? false : true;
            source: (Car.gear === 1) ? "images/selected_gear.gif" : "";
            Text {
                color: (Car.gear === 1) ? "#FF3131" : "#3B3200";
                text: "N";
                width: 50;
                height: 50;
                font.pointSize: 20;
                anchors.left: parent.left;
                anchors.leftMargin: 14;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Car.gear = 1;
                }
            }
        }
        AnimatedImage {
            width: 48;
            height: 30;
            paused: (Car.gear === 2) ? false : true;
            source: (Car.gear === 2) ? "images/selected_gear.gif" : "";
            Text {
                color: (Car.gear === 2) ? "#FF3131" : "#3B3200";
                text: "D";
                width: 50;
                height: 50;
                font.pointSize: 20;
                anchors.left: parent.left;
                anchors.leftMargin: 13;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Car.gear = 2;
                }
            }
        }
        AnimatedImage {
            width: 48;
            height: 30;
            paused: (Car.gear === 3) ? false : true;
            source: (Car.gear === 3) ? "images/selected_gear.gif" : "";

            Text {
                color: (Car.gear === 3) ? "#FF3131" : "#3B3200";
                text: "R";
                width: 50;
                height: 50;
                font.pointSize: 20;
                anchors.left: parent.left;
                anchors.leftMargin: 14;
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Car.gear = 3;
                }
            }
        }
    }

    // acceleration control
    Slider {
        id: accelerateControl
        width: 30;
        height: 184;
        anchors.right: steeringWheel.left;
        anchors.rightMargin: 60;
        anchors.verticalCenter: steeringWheel.verticalCenter;
        from: 0
        value: Car.speed;
        to: 4000;
        snapMode: Slider.SnapAlways;
        stepSize: 1.0;
        orientation: Qt.Vertical
        onMoved: {
            Car.speed = accelerateControl.value;
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
                text: Car.speed.toFixed(1) / 40 // 40 because 4000 AKA max speed of D gear, divided by 40 == 100%
                delay: 100;
                timeout: 0;
                background: Rectangle { radius: 3; border.width: 1; opacity: 0.7 }
            }
        }

    }

    Dial {
        id: steeringWheel
        width: 190;
        height: 190;
        anchors.bottom: wallFrameForSteering.bottom;
        anchors.bottomMargin: 35;
        anchors.right: parent.horizontalCenter;
        from: 0.0;
        value: Car.steering;
        to: 140.0;
        snapMode: Dial.SnapAlways;
        stepSize: 1.0;
        onMoved: {
            Car.steering = steeringWheel.value;
        }
        background: Rectangle {
            x: steeringWheel.width / 2 - width / 2
            y: steeringWheel.height / 2 - height / 2
            width: steeringWheel.width
            height: steeringWheel.height
            color: "transparent"
            radius: width / 2
            border.color: "#1777B7"
        }
        handle: Rectangle {
            id: steeringWheelHandle
            x: steeringWheel.background.x + steeringWheel.background.width / 2 - width / 2
            y: steeringWheel.background.y + steeringWheel.background.height / 2 - height / 2
            width: 20
            height: 20
            color: steeringWheel.pressed ? "#1777B7" : "#3B3200"
            radius: 8
            antialiasing: true
            opacity: steeringWheel.enabled ? 1 : 0.3
            transform: [
                Translate {
                    y: -Math.min(steeringWheel.background.width, steeringWheel.background.height) * 0.5 + steeringWheelHandle.height / 2
                },
                Rotation {
                    angle: steeringWheel.angle
                    origin.x: steeringWheelHandle.width / 2
                    origin.y: steeringWheelHandle.height / 2
                }
            ]
        }
    }
    DropShadow {
        anchors.fill: steeringWheel
        horizontalOffset: 0
        verticalOffset: 0
        radius: 12.0
        samples: 25
        color: "blue"
        source: steeringWheel
    }

    Image {
        id: wallFrameForSteering
        source: "images/boardBg2.png";
        width: root.width * 0.879 // 900;
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


    Rectangle {
        id: ambientGreenLighting
        width: Screen.width
        height: Screen.height
        x: 0
        y: 0
        z: 5
        color: "#5865F2"
        opacity: 0
    }
    // Rectangle {
    //     id: ambientBlueLighting
    //     width: Screen.width
    //     height: Screen.height
    //     x: 0
    //     y: 0
    //     z: 5
    //     color: "blue"
    //     opacity: 0.5
    // }

}


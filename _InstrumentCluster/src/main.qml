import QtQuick 2.15
import QtQuick.Window 2.15
// import QtQuick.Window 2.15 // this was uncommented out and replaced with below line before it worked on my Qt
import QtQuick.Shapes 1.0

Window {
    id: root
    width: 1280
    height: 400
    //color: "#36454F"
    color: "transparent"
    visible: true
    title: qsTr("Instrument Cluster")
    // flags: Qt.FramelessWindowHint
    
    Image {
        id: bgImage
        source: "qrc:/image/car.jpg"
    }

    // Battery Icon Component
    BatteryIcon {
        id: batteryIcon
        iconSize: 35
        iconColor: "#63E6BE"
        level: (batteryIconObj.isPercent / 24) // dividing by 24 because we want 96-100 to be == 4(full bar)
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 5
    }
    Text {
        color: "white"
        text: batteryIconObj.isPercent
        anchors.left: batteryIcon.right
        anchors.leftMargin: 13
        anchors.top: batteryIcon.bottom
        anchors.topMargin: 6
    }

    // Gear display
    AnimatedImage {
        id: activeGear
        width: 48
        height: 30
        anchors.top: batteryIcon.bottom
        anchors.topMargin: parent.height / 3
        anchors.left: batteryIcon.left

        source: "image/selected_gear.gif"
        Text {
            color: "#FF3131"
            text: "P" // all that is left is to make this text responsive from cpp
            width: 50
            height: 50
            font.pointSize: 20
            anchors.left: parent.left
            anchors.leftMargin: 15
        }

    }

    // outer circle
    Rectangle {
        id: gauge
        width: 360
        height: 360

        //color: root.color
        color: "transparent"

        anchors.centerIn: parent
        radius: width/2
        //border {
          //  width: 5
        //}

        // center circle
        Rectangle {
            id: gaugeCenterDot

            width: 40
            height: 40

            //color: "#000000"
            color: "red"

            anchors.centerIn: parent

            radius: width/2
        }

        // needle
        Shape {
            id: needle
            anchors {
                centerIn: parent
                bottom: parent.verticalCenter
                bottomMargin: -(gaugeCenterDot.width / 4)
                right: parent.horizontalCenter
            }
            transformOrigin: Item.Right
            rotation: -30 + speedometer.newSpeed

            Behavior on rotation {
                NumberAnimation {
                    duration: 1000
                    easing.type: Easing.Bezier
                }
            }

            ShapePath {
                strokeWidth: 0
                //fillColor: "#000000"
                fillColor: "red"
                //strokeColor: "#000000"
                strokeColor: "red"

                startX: 0; startY: -(gaugeCenterDot.width / 4)

                PathLine {
                    x: -140
                    y: 0
                }

                PathLine {
                    x: 0
                    y: (gaugeCenterDot.width / 4)
                }
            }
        }

        Shape {
            anchors {
                centerIn: parent
            }
        }

        function degreesToRadians(degrees)
        {
          var pi = Math.PI
          return degrees * (pi/180)
        }

        // major ticks
        //Repeater {
        //    model: 9
        //    Rectangle {
        //        id: majorTick
        //        width: 20
        //        height: 2
        //        x: (parent.width / 2) + (175 * Math.sin(parent.degreesToRadians(-60 - index * 30)))
        //        y: (parent.height / 2) + (175 * Math.cos(parent.degreesToRadians(-60 - index * 30))) - (majorTick.height/2)
        //        transformOrigin: Item.Left
        //        rotation: -30 + index * 30
        //    }
        //}

        // minor ticks
        //Repeater {
        //    model: 40
        //    Rectangle {
        //        visible: index % 5 !== 0
        //        width: 10
        //        height: 1
        //        x: (parent.width / 2) + (175 * Math.sin(parent.degreesToRadians(-60 - index * 6)))
        //        y: (parent.height / 2) + (175 * Math.cos(parent.degreesToRadians(-60 - index * 6)))
        //        transformOrigin: Item.Left
        //        rotation: -30 + index * 6
        //    }
        //}
    }
}

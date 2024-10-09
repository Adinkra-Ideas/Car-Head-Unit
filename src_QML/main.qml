import QtQuick 2.15
import QtQuick.Window 2.15

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
        paused: (car.isGear > 0) ? false : true;
        source: "qrc:/images/HU_logo.gif";
        anchors.centerIn: parent;
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
            paused: (car.isGear === 0) ? false : true;
            source: (car.isGear === 0) ? "qrc:/images/selected_gear.gif" : "";
            Text {
                color: (car.isGear === 0) ? "#F6D101" : "#3B3200";
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
                    car.setGearToP();
                }
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: (car.isGear === 1) ? false : true;
            source: (car.isGear === 1) ? "qrc:/images/selected_gear.gif" : "";
            Text {
                color: (car.isGear === 1) ? "#F6D101" : "#3B3200";
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
                    car.setGearToN();
                }
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: (car.isGear === 2) ? false : true;
            source: (car.isGear === 2) ? "qrc:/images/selected_gear.gif" : "";
            Text {
                color: (car.isGear === 2) ? "#F6D101" : "#3B3200";
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
                    car.setGearToD();
                }
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: (car.isGear === 3) ? false : true;
            source: (car.isGear === 3) ? "qrc:/images/selected_gear.gif" : "";

            Text {
                color: (car.isGear === 3) ? "#F6D101" : "#3B3200";
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
                    car.setGearToR();
                }
            }
        }
    }


}

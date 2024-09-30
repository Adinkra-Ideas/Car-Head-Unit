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
        paused: true;
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
            paused: false;
            source: "qrc:/images/selected_gear.gif";
            Text {
                color: "#F6D101";
                text: "P";
                width: 50;
                height: 50;
                font.pointSize: 15;
                anchors.left: parent.left;
                anchors.leftMargin: 15;
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: true;
            source: "qrc:/images/selected_gear.gif";
            Text {
                color: "#3B3200";
                text: "N";
                width: 50;
                height: 50;
                font.pointSize: 15;
                anchors.left: parent.left;
                anchors.leftMargin: 14;
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: true;
            source: "qrc:/images/selected_gear.gif";
            Text {
                color: "#3B3200";
                text: "D";
                width: 50;
                height: 50;
                font.pointSize: 15;
                anchors.left: parent.left;
                anchors.leftMargin: 13;
            }
        }
        AnimatedImage {
            width: 40;
            height: 25;
            paused: true;
            source: "qrc:/images/selected_gear.gif";

            Text {
                color: "#3B3200";
                text: "R";
                width: 50;
                height: 50;
                font.pointSize: 15;
                anchors.left: parent.left;
                anchors.leftMargin: 14;
            }
        }
    }


}

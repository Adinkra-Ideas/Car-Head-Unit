import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs
import QtMultimedia

Rectangle {
    id: topControls

    property bool playingTab
    signal playSignal
    required property bool audioTab
    signal audioSignal
    required property bool settingsTab
    signal settingsSignal

    signal maximizeWinSignal
    signal minimizeWinSignal

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Item {
            id: playing
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            visible: Car.mp_audio !== MediaPlayer.StoppedState
            Connections {
                target: Car
                function onMp_playingChanged() {
                    if (Car.mp_audio === MediaPlayer.PlayingState) {
                        topControls.playSignal()
                    }
                }
            }
            Image {
                source: topControls.playingTab ? "images/musicIco/playing_white.png" : "images/musicIco/playing.png"
                width: 30
                height: 30
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    topControls.playSignal()
                }
            }
        }
        Item {
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            Image {
                source: topControls.audioTab ? "images/musicIco/audio_white.png" : "images/musicIco/audio.png"
                width: 30
                height: 30
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    topControls.audioSignal()
                }
            }
        }
        Item {
            id: add
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            Image {
                source: "images/musicIco/add.png"
                width: 30
                height: 30
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    folderDialog.open()
                }
            }
        }
        Item {
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            Image {
                source: topControls.settingsTab ? "images/musicIco/screen_w.png" : "images/musicIco/screen.png"
                width: 30
                height: 30
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    topControls.settingsSignal()
                }
            }
        }
        Item {
            id: minimizer
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            property bool fullWindow: false
            Image {
                source: minimizer.fullWindow ? "images/musicIco/minimize_w.png" : "images/musicIco/minimize.png"
                width: 30
                height: 30
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (minimizer.fullWindow)
                        topControls.minimizeWinSignal()
                    else
                        topControls.maximizeWinSignal()

                    minimizer.fullWindow = !minimizer.fullWindow
                }
            }
        }
    }

    // called when add is clicked
    FolderDialog {
        id: folderDialog

        onAccepted: {
            folderDialog.currentFolder = folderDialog.selectedFolder
            Car.mp_audiopaths = folderDialog.selectedFolder
        }
    }
}

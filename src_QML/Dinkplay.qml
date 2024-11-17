import QtQuick
import QtQuick.Controls
import QtMultimedia

Rectangle {
    id: dinkPlayer

    ScrollView {
        id: view
        anchors.fill: parent
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff
        contentWidth: parent.width
        contentHeight: audioPage.height

        Playing {
            id: playingPage
            width: parent.width
            visible: false
        }
        Audio {
            id: audioPage
            width: parent.width
            visible: true
        }
        Settings {
            id: settingsPage
            width: parent.width
            visible: false
        }
    }



    TopControls {
        id: topControls
        color: parent.color
        opacity: 1
        Behavior on opacity { NumberAnimation { duration: 500 } }
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
        playingTab: playingPage.visible
        audioTab: audioPage.visible
        settingsTab: settingsPage.visible

        // onClickSet the play tab active and bring put the playing window into view
        onPlaySignal: {
            hideAllTabs()
            view.contentHeight = playingPage.height
            playingPage.visible = true
        }
        onAudioSignal: {
            hideAllTabs()
            view.contentHeight = audioPage.height
            audioPage.visible = true
            print("scrollview height", view.height)
            print("audio height", audioPage.height)
        }
        onSettingsSignal: {
            hideAllTabs()
            view.contentHeight = settingsPage.height
            settingsPage.visible = true
        }
        function hideAllTabs() {
            playingPage.visible = false
            audioPage.visible = false
            settingsPage.visible = false
        }

        onMaximizeWinSignal: {
            dinkPlayer.height = Window.height - 20
            dinkPlayer.width = Window.width - 20
        }
        onMinimizeWinSignal: {
            dinkPlayer.height = root.height * 0.8584
            dinkPlayer.width = root.width * 0.293
        }
    }


    MediaControls {
        id: mediaControls
        color: parent.color
        visible:  Car.mp_audio !== MediaPlayer.StoppedState
        opacity: 1
        Behavior on opacity { NumberAnimation { duration: 500 } }
        anchors.bottom: parent.bottom
        // anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        height: 55
    }

    // MouseArea {
    //     id: activityListener
    //     anchors.fill: parent
    //     z: 2
    //     propagateComposedEvents: true
    //     hoverEnabled: true

    //     onPressed: mouse => mouseEventHandlerInDinkplay(mouse)
    //     // onPositionChanged: mouse => mouseEventHandlerInDinkplay(mouse)
    //     onWheel: mouse => mouseEventHandlerInDinkplay(mouse)
    //     onDoubleClicked: mouse => mouse.accepted = false // setting mouse.accepted to false prevents the cursor from grabbing

    //     Timer {
    //         id: hideTopAndMediaControls
    //         interval: 3000
    //         running: true
    //         repeat: true
    //         onTriggered: {
    //             mediaControls.opacity = 0
    //             topControls.opacity = 0
    //         }
    //     }
    //     function mouseEventHandlerInDinkplay(mouse) {
    //         mediaControls.opacity = 1
    //         topControls.opacity = 1
    //         hideTopAndMediaControls.restart()
    //         hideTopAndMediaControls.start()
    //         mouse.accepted = false
    //     }
    // }
}

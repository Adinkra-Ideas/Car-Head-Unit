import QtQuick 2.15

Item {
    property string iconColor   // so wie CSS
    property int iconSize: 32   // in pixel
    property int level          // 0-4 levels

    function getUnicode()
    {
        if (level == 0)
            return "\uf244" // fa-battery-empty
        else if (level == 1)
            return "\uf243" // fa-battery-quarter
        else if (level == 2)
            return "\uf242" // fa-battery-half
        else if (level == 3)
            return "\uf241" // fa-battery-three-quarters
        else if (level == 4)
            return "\uf240" // fa-battery-full
        else
            return "\ue0b1" // fa-battery-error
    }

    Text {
        id: batteryIcon
        font.family: fontAwesome.name
        color: iconColor
        font.pixelSize: iconSize
        text: getUnicode()
    }

    FontLoader { id: fontAwesome; source: "qrc:/BatteryIcon.ttf" }
}

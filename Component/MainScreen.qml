import QtQuick 2.15
import QtQuick.Controls
import QtLocation 5.15
import pLogger 1.0

Item
{
    Logger
    {

        id: _Logger
        Component.onCompleted:
        {

            _Logger._Constructor(Qt.application.arguments[1])
            console.log("Logger initialized, Items count: " + _Logger._Items.length)
        }

    }
    Rectangle
    {
        z: 1
        id: _CheckBoxCorner
        anchors.top: parent.top
        width: parent.width
        height: parent.height / ColorsNSizes._CheckBoxLineScaleY
        color: ColorsNSizes._ThirdColor
        border.color: "black"
        border.width: 1
        Row
        {
            id: _CheckBoxRow
            height: parent.height

            anchors.top: parent.top
            spacing: parent.width / 3
            CheckBox
            {
                id: _ErrorCheckBox
                checked: true
                font.bold: true
                font.pixelSize: ColorsNSizes._SmallFont
                text: qsTr("Error")
                height: parent.height

            }
            CheckBox
            {
                id: _WarningCheckBox
                checked: true
                font.bold: true
                font.pixelSize: ColorsNSizes._SmallFont
                text: qsTr("Warning")
                height: parent.height
            }
            CheckBox
            {
                id: _InfoCheckBox
                checked: true
                font.bold: true
                font.pixelSize: ColorsNSizes._SmallFont
                text: qsTr("Info")
                height: parent.height
            }

        }
    }



    ListView
    {
        z: -1
        id: _ListLines
        anchors.top: _CheckBoxCorner.bottom
        width: parent.width
        height: 90 * 60
        model: _Logger._Items
        delegate:

            Rectangle
                {
                    id: _Deligated
                    border.color: "black"
                    border.width: 1
                    width: parent.width
                    height: 60
                    Text {

                        id: name
                        font.bold: true
                        text: modelData
                        anchors.fill: parent
                        // anchors.verticalCenter: parent.verticalCenter
                        // anchors.horizontalCenter: parent.horizontalCenter
                        font.pointSize: 12
                        color: "black"

                    }
                }
    }
    WheelHandler {
            onWheel: (event)=>{_ListLines.flick(0, event.angleDelta.y*event.y)}
    }
}

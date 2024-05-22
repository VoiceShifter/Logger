import QtQuick
import QtQuick.Controls
Item
{
    Rectangle
    {
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
            width: parent.width
            anchors.top: parent.top
        }
    }

    // ListView
    // {
    //     id: _ListLines
    //     anchors.top: _CheckBoxRow
    //     width: parent.width
    // }
}

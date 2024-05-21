import QtQuick
import "Component"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Logger")
    color: "#5682a3"

    Row {

        id: _ButtonRow
        width: parent.width / ColorsNSizes._ButtonScaleY
        height: parent.height / ColorsNSizes._ButtonScaleY
        spacing: -1

        Rectangle {
            color: ColorsNSizes._SecondaryColor
            border.color: "black"
            border.width: 1

            width: parent.width + 1
            height: parent.height

            Text{

                    id: _AppName
                    text: qsTr("Logger")
                    anchors.left: parent.left
                    font.bold: true


                    color: "black"
                    minimumPointSize: 10
                    font.pointSize: 18
                    fontSizeMode: Text.Fit

                    anchors.centerIn: parent
                }
        }
        Rectangle {
            color: ColorsNSizes._SecondaryColor
            border.color: "black"
            border.width: 1

            width: parent.width + 1
            height: parent.height
            Text{
                    text: qsTr("Graphics")
                    anchors.left: parent.left
                    font.bold: true


                    color: "black"
                    minimumPointSize: 10
                    font.pointSize: 18
                    fontSizeMode: Text.Fit

                    anchors.centerIn: parent
                }
        }
        Rectangle {
            color: ColorsNSizes._SecondaryColor
            border.color: "black"
            border.width: 1

            width: parent.width + 1
            height: parent.height
            Text{
                    text: qsTr("ML")
                    anchors.left: parent.left
                    font.bold: true


                    color: "black"
                    minimumPointSize: 10
                    font.pointSize: 18
                    fontSizeMode: Text.Fit

                    anchors.centerIn: parent
                }
        }
        Rectangle {
            color: ColorsNSizes._SecondaryColor
            border.color: "black"
            border.width: 1

            width: parent.width + 1
            height: parent.height
            Text{
                    text: qsTr("Update")
                    anchors.left: parent.left
                    font.bold: true


                    color: "black"
                    minimumPointSize: 10
                    font.pointSize: 18
                    fontSizeMode: Text.Fit

                    anchors.centerIn: parent
                }
        }



    }
    Row
    {
        id: _CheckBoxRow
        height: parent.height / ColorsNSizes._CheckBoxLineScaleY
        width: parent.width
        Rectangle
        {
            anchors.fill: parent
            color: ColorsNSizes._ThirdColor
            border.color: "black"
            border.width: 1
        }
        anchors.top: _ButtonRow.bottom
        anchors.topMargin: -1
    }
}

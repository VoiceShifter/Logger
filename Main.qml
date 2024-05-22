import QtQuick
import QtQuick.Controls
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
    } //row ending
    Loader
    {
        id: _Loader
        anchors.top: _ButtonRow.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: parent.height - _ButtonRow.height
        source: "Component/MainScreen.qml"


        MouseArea
        {
            anchors.fill: parent
            onClicked: {
                console.log("Loader territory clicked");
            }
        }

    }
}

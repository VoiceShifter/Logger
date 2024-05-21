pragma Singleton

import QtQuick

Item {

    QtObject{
        id: _Themes
        readonly property var _Dark: ["Dark" , "#5682a3", "#4b728f", "#78889c", "#697989", "#a5b0bd"]
        readonly property var _Light: ["Light" , "#1E0342", "#0E46A3", "#9AC8CD", "#E1F7F5"]
    }
    property var _CurrentTheme: _Themes._Dark
    property var themes: _Themes


    readonly property string _ThemeName : _CurrentTheme[0]
    readonly property string _PrimaryColor: _CurrentTheme[1]
    readonly property string _SecondaryColor: _CurrentTheme[2]
    readonly property string _ThirdColor: _CurrentTheme[3]
    readonly property string _ForthColor: _CurrentTheme[4]
    readonly property string _FifthColor: _CurrentTheme[5]


    readonly property string _LightBlue: "#dbe2ef"
    readonly property string _LightPurple: "#7881ae"
    readonly property string _PowderBlue: "#aab2cf"
    readonly property string _CoolGray: "#848cb5"
    readonly property int _SideButtonHeight: 140
    readonly property int _SideButtonWidth: 400
    readonly property int _BigFont: 52
    readonly property int _MediumFont: 32
    readonly property int _SmallFont: 16



    readonly property double _IconHolderScale : 0.25
    readonly property double _TextFieldScale : 1.2
    readonly property double _ButtonScaleX : 5
    readonly property double _ButtonScaleY : 4
    readonly property double _CheckBoxLineScaleY : 14


    readonly property double _SubjectScaleX : 1.1
    readonly property double _SubjectScaleY : 5

    readonly property double _MenuButtonScaleX : 7

    readonly property double _SideButtonScaleY : 8

    readonly property double _SliderScaleX : 4
    readonly property double _SliderScaleY : 20

    readonly property double _BreakerScaleY : 8




}

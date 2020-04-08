pragma Singleton
import QtQuick 2.0

QtObject {

    property bool isDarkTheme: true

    property string basicColor: isDarkTheme? "white" : "black"
    property string backgroundColor: isDarkTheme? "black" : "white"
    property string textColor: isDarkTheme? "white" : "black"

    property int basicMargin: 5
    property int mediumOffset: 15
}

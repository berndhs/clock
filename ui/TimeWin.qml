import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle  {

    id: bigBox;
    objectName: "TheBigBox";
    width: 167; height: 100;
    color: "green";

    signal quit();
    signal showCopyright();
    signal changeFormat();

    property string timeValue: "now it is";
    Text {
        id: dateText;
        anchors.centerIn: parent;
        objectName: "TheDateText";
        text: bigBox.timeValue;
        font.family: "Deja Serif";
        font.pixelSize: 27;
    }

    Row {
        spacing: 10;
        Button {
            id: quitButton;
            width: 60;
            height: 20;
            text: "Quit";
            onReleased: {
                console.log("released quit");
                bigBox.quit();
            }
        }
        Button {
            id: formatButton;
            width: 80; height:20;
            text: "Format";
            onReleased: {
                bigBox.changeFormat();
            }
        }
        Button {
            id: copyrightButton;
            width: 133; height: 88;
//            iconSource: "qrc:/rights.png";
            onReleased: {
                bigBox.showCopyright();
            }
        }
    }
}

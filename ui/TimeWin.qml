import QtQuick 2.0
import QtQuick.Controls 2.0


//***************************************************************
// * This file is distributed under the following license:
// *
// * Copyright (C) 2017, Bernd Stramm

//This is free software: you can redistribute it and/or modify
//it under the terms of the GNU Affero General Public License as
//published by the Free Software Foundation, either version 3 of the
//License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU Affero General Public License for more details.

//You should have received a copy of the GNU Affero General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

// ***************************************************************


Rectangle  {

    id: bigBox;
    objectName: "TheBigBox";
    width: 167; height: 100;
    color: backColor;

    signal quit();
    signal showCopyright();
    signal changeFormat();
    signal sizeUp();
    signal sizeDown();
    signal toggleFrame();

    function flipButtonVisible(h) {
        buttonsVisible = h;
    }

    property bool buttonsVisible: false;
    property string timeValue: "now it is";
    property real pixelSize: 15;
    property string backColor: "green";
    property string textColor: "black";

    MouseArea {
        id: mouseBox;
        hoverEnabled: true;
        property bool hoovered: false;
        anchors.fill : bigBox;
        onContainsMouseChanged: {

            hoovered = containsMouse;
            bigBox.flipButtonVisible(hoovered)
        }
    }

    Text {
        id: dateText;
        anchors.centerIn: parent;
        z: 100;
        objectName: "TheDateText";
        text: bigBox.timeValue;
        color: bigBox.textColor;
        font.family: "Deja Serif";
        font.pixelSize: bigBox.pixelSize;
    }

    Column {
        id: leftCol;
        spacing: 10;
        anchors {
            left: bigBox.left;
            leftMargin: 3;
            top: bigBox.top;
            topMargin: 10;
        }
        visible: bigBox.buttonsVisible;
        opacity: 0.8;
        z: dateText.z+1;
        Button {
            id: upButton;
            text: "up";
            width: 40; height: 40;
            Image {
                anchors.fill: upButton;
                source: "qrc:/uparrow.png";
            }
            onReleased: {
                bigBox.sizeUp();
            }
        }
        Button {
            id: downButton;
            text: "up";
            width: 40; height: 40;
            Image {
                anchors.fill: downButton;
                source: "qrc:/downarrow.png";
            }
            onReleased: {
                bigBox.sizeDown();
            }
        }
    }

    Flow {
        spacing: 10;
        id: buttonRow;
        opacity: 0.8;
        visible: bigBox.buttonsVisible;
        z: dateText.z+1;
        width: bigBox.width - leftCol.width - 5;
        anchors {
            left: leftCol.right;
            leftMargin: 5;
            top: leftCol.top;
            topMargin: upButton.height/2;
        }

        Button {
            id: quitButton;
            objectName: "quitButton"
            z: dateText.z+1;
            width: 60;
            height: 20;
            text: "Quit";
            onReleased: {
                bigBox.quit();
            }
        }
        Button {
            id: formatButton;
            objectName: "formatButton";
            width: 80; height:20;
            text: "Format";
            onReleased: {
                bigBox.changeFormat();
            }
        }
        Button {
            id: copyrightButton;
            objectName: "copyrightButton";
            z: dateText.z+1;

            width: 88; height: 31;
            Image {
                anchors.fill: copyrightButton;
                source: "qrc:/rights.png";
            }
            onReleased: {
                bigBox.showCopyright();
            }
        }
        Button {
            id: frameButton;
            objectName: "frameButton"
            z: dateText.z+1;
            width: 60;
            height: 20;
            text: "Frame";
            onReleased: {
                bigBox.toggleFrame();
            }
        }
    }

}

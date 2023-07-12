import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item {
    id: root
    property string movieId: ""
    property string imageUrl: ""
    property string movieTitle: ""
    readonly property string baseUrl: "https://image.tmdb.org/t/p/original/"

    width: 200
    height: 300

    Image {
        id: movieImage
        source: root.baseUrl + root.imageUrl
        width: parent.width
        height: parent.height - 50
        anchors.top: parent.top
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: movieText
        text: root.movieTitle
        width: parent.width
        height: 50
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.top: movieImage.bottom
        font.pixelSize: 16
        color: "#D4ADFC"
    }

    BusyIndicator {
        id: loadingIndicator
        width: 40
        height: 40
        anchors.centerIn: movieImage
        visible: movieImage.status === Image.Loading
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            movieDetailPopup.open()
        }
    }

    Popup {
        id: movieDetailPopup
        width: 400
        height: 600
        modal: true
        focus: true

        parent: Overlay.overlay
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        Behavior on y {
            SpringAnimation {
                spring: 2
                damping: 0.2
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "#D4ADFC"

            Column {
                anchors.fill: parent
                padding: 10
                spacing: 10

                Image {
                    id: detailImage
                    source: movieImage.source
                    width: parent.width
                    height: parent.height / 2
                    fillMode: Image.PreserveAspectFit
                }

                Label {
                    id: detailLabel
                    text: movieText.text
                    font.pixelSize: 24
                    wrapMode: Text.WordWrap
                }


                RowLayout {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.margins: 10
                    Button {
                        text: "watched"
                        onClicked: {
                            console.log("rate the movie")
                            ratingController.createRatingQML(userController.currentUserId, root.movieId, 5)
                            movieDetailPopup.close()
                        }
                    }
                    Button {
                        text: "want to watch"
                        onClicked: {
                        console.log("added to watch list")
                        movieDetailPopup.close()
                        }
                    }
                }

            }
        }
    }
}


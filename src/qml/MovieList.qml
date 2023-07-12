import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: root
    property var movies: []
    property string listTitle: ""
    width: parent.width
    Rectangle {
        id: listViewBackground
        color: "#1D267D"
        anchors.bottom: root.bottom
        height:340
        width: parent.width
        z: -1
    }

    Column {
        width: parent.width
        spacing: 40

        Label {
            id: listTitleLabel
            text: root.listTitle
            font.pointSize: 24
            font.bold: true
            color:"#D4ADFC"
        }

        ListView {
            id: listView
            width: parent.width
            height: 320
            orientation: ListView.Horizontal
            model: root.movies
            flickableDirection: Flickable.HorizontalFlick
            delegate: Movie {
                movieId: modelData.movieId
                imageUrl: modelData.url
                movieTitle: modelData.title
            }
            spacing: 10
        }
    }
}

import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: root
    property var movies: []
    property string listTitle: ""

    Column {
        anchors.fill: parent

        Label {
            id: listTitleLabel
            text: root.listTitle
            font.pointSize: 24
            font.bold: true
            color: "#D4ADFC"
        }

        GridView {
            id: gridView
            width: parent.width
            height: parent.height - listTitleLabel.height
            model: root.movies
            delegate: Movie {
                imageUrl: modelData.url
                movieTitle: modelData.title
            }
            cellWidth: 200
            cellHeight: 300
        }
    }
}

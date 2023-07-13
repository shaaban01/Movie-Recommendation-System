import QtQuick 2.12
import QtQuick.Controls 2.12

TextField {
    id: searchInput
    width: parent.width
    height: parent.height
    placeholderText: "Search"

    Keys.onReturnPressed: {
        searchMovies(text)
    }
    onAccepted: {
        searchMovies(text)
    }
}


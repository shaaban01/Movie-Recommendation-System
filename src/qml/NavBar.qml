import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Item {
    width: parent.width
    height: 100  // Adjust the height as needed for the desired padding

    property int horizontalMargin: 30
        property int currentPage: 0

            RowLayout {
                id: navbar
                width: parent.width - (2 * horizontalMargin)
                height: 40
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Item {
                    Layout.preferredHeight: 30
                }
                // Navigation links
                Repeater {
                    model: ["For You", "Your Ratings", "Saved To Watch", "Settings"]
                    delegate: Rectangle {
                        width: 120
                        height: parent.height
                        color: index === currentPage ? "lightblue" : "transparent"
                        border.color: "black"
                        Text {
                            text: modelData
                            anchors.centerIn: parent
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                // Handle navigation link click event
                                currentPage = index;
                            }
                        }
                    }
                }

                Item {
                    Layout.preferredHeight: 30
                }

                // Search bar component
                SearchBar {
                    id: searchBar
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    placeholderText: "Search"
                    // Handle search events, e.g., onTextChanged, onSearchButtonClicked, etc.
                    // ...
                }

            }
            Rectangle {
                color: "#D4ADFC"
                width: parent.width
                height: parent.height - navbar.height
                z: -1
            }
        }

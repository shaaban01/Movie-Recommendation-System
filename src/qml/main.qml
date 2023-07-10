import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import user.controller 1.0

Window {
    property var isAuth: false
        property int userId: 0
            visible: true
            width: 1280
            height: 720
            title: "Movie Recommendation System"
            color:"#0C134F"


            NavBar {
                id: navBar
                visible: isAuth
                anchors.top: parent.top
                currentPage: 0
                z: 99
            }
            Loader {
                id: authenticationLoader
                anchors.fill: parent
                sourceComponent: Item {


                    Rectangle {
                        radius: 20
                        anchors.centerIn: parent
                        width: 480
                        height: 480

                        StackView {
                            id: stackView
                            initialItem: Component { Login {} }
                            anchors.fill: parent
                            Component.onCompleted: {
                                stackView.onEmptyChanged.connect(function() {
                                if (stackView.empty)
                                {
                                    console.log("Authentication is completed");
                                    userId = userController.getUserId();
                                    console.log("Login Successful: " + userId);
                                    authenticationLoader.sourceComponent = null;  // Unload the Loader once authentication is complete
                                    isAuth = true;
                                }
                            });
                        }
                    }
                }
            }
        }
        Button {
            id: btn
            text: "qsTr(OK)"
            onClicked: console.log("userId: " + userId + " isAuth: " + isAuth)
            anchors.centerIn: parent
        }
        
        // MovieGrid {
        //     id: yourRatings
        //     visible: navBar.currentPage === 1 && isAuth
        //     anchors.top: navBar.bottom
        //     anchors.bottom: parent.bottom
        //     anchors.left: parent.left
        //     anchors.right: parent.right
        //     movies: [
        //     {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //     {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //     {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //     {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //     {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //     {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        //     {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //     {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //     {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //     {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //     {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //     {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        //     {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //     {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //     {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //     {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //     {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //     {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},

        //     ]
        // }

        // MovieGrid {
        //     id: toWatch
        //     visible: navBar.currentPage === 2 && isAuth
        //     anchors.top: navBar.bottom
        //     anchors.bottom: parent.bottom
        //     anchors.left: parent.left
        //     anchors.right: parent.right
        //     movies: [
        //     {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //     {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //     {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //     {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //     {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //     {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        //     {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //     {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //     {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //     {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //     {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //     {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        //     {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //     {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //     {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //     {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //     {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //     {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},

        //     ]
        // }


        // Flickable {
        //     id: view
        //     visible: navBar.currentPage === 0 && isAuth
        //     anchors.top: navBar.bottom
        //     anchors.bottom: parent.bottom
        //     anchors.left: parent.left
        //     anchors.right: parent.right
        //     contentHeight: listColumn.height

        //     Column {
        //         id: listColumn
        //         width: parent.width
        //         spacing: 20
        //         MovieList {
        //             width: parent.width
        //             height: 400
        //             listTitle: "Popular Movies"
        //             movies: [
        //             {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //             {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //             {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //             {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //             {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //             {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        //             {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //             {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //             {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //             {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //             {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //             {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        //             {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //             {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //             {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //             {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //             {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //             {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},

        //             ]
        //         }

        //         MovieList {
        //             width: parent.width
        //             height: 400
        //             listTitle: "Similar To What You Have Liked: "
        //             movies: [
        //             {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //             {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //             {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //             {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //             {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //             {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        //             {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //             {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //             {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //             {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //             {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //             {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        //             ]
        //         }

        //         MovieList {
        //             width: parent.width
        //             height: 400
        //             listTitle: "Similar Users Also Liked: "
        //             movies: [
        //             {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        //             {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        //             {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        //             {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        //             {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        //             {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},

        //             ]
        //         }
        //     }
        // }

    }


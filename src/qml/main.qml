import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3


Window {
    property var isAuth: false
        id: windowMain
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
                                authenticationLoader.sourceComponent = null;  // Unload the Loader once authentication is complete
                                isAuth = true;

                                var recommendationsArray = [];
                                var recommendationsVariant = recommendationEnginePopularity.getRecommendations(userController.currentUserId, 30);

                                for (var i = 0; i < recommendationsVariant.length; i++) {
                                    var recommendation = recommendationsVariant[i];
                                    recommendationsArray.push({movieId: recommendation.movieID, url: recommendation.url, title: recommendation.title });
                                }

                                // Set the parsed array as the movies property
                                trendingId.movies = recommendationsArray;

                                recommendationsArray = [];
                                recommendationsVariant = recommendationEngineContentBased.getRecommendations(userController.currentUserId, 30);
                                console.log(recommendationsArray.toString());

                                for (var i = 0; i < recommendationsVariant.length; i++) {
                                    var recommendation = recommendationsVariant[i];
                                    recommendationsArray.push({movieId: recommendation.movieID, url: recommendation.url, title: recommendation.title });
                                }
                                contentBasedId.movies = recommendationsArray;

                                recommendationsArray = [];
                                // recommendationsVariant = recommendationEngineUserBased.getRecommendations(userController.currentUserId, 30);

                                // for (var i = 0; i < recommendationsVariant.length; i++) {
                                //     var recommendation = recommendationsVariant[i];
                                //     recommendationsArray.push({movieId: recommendation.movieID, url: recommendation.url, title: recommendation.title });
                                // }

                                // userBasedId.movies = recommendationsArray;


                            }
                        });
                    }
                }
            }
        }
    }

    MovieGrid {
        id: yourRatings
        visible: navBar.currentPage === 1 && isAuth
        anchors.top: navBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        movies: [
        {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},

        ]
    }

    MovieGrid {
        id: toWatch
        visible: navBar.currentPage === 2 && isAuth
        anchors.top: navBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        movies: [
        {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},
        {url: "/fiVW06jE7z9YnO4trhaMEdclSiC.jpg", title: "Fast X"},
        {url: "/8Vt6mWEReuy4Of61Lnj5Xj704m8.jpg", title: "Spider-Man: Across the Spider-Verse"},
        {url: "/vZloFAK7NmvMGKE7VkF5UHaz0I.jpg", title: "John Wick: Chapter 4"},
        {url: "/qNBAXBIQlnOThrVvA6mA2B5ggV6.jpg", title: "The Super Mario Bros. Movie"},
        {url: "/7gKI9hpEMcZUQpNgKrkDzJpbnNS.jpg", title: "Transformers: Rise of the Beasts"},
        {url: "/gPbM0MK8CP8A174rmUwGsADNYKD.jpg", title: "Extraction 2"},

        ]
    }


    Flickable {
        id: view
        visible: navBar.currentPage === 0 && isAuth
        anchors.top: navBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        contentHeight: listColumn.height

        Column {
            id: listColumn
            width: parent.width
            spacing: 20
            MovieList {
                id: trendingId
                width: parent.width
                height: 400
                listTitle: "Popular Movies"
                movies: []
            }

            MovieList {
                id: contentBasedId
                width: parent.width
                height: 400
                listTitle: "Similar To What You Have Liked: "
                movies: []
            }

            MovieList {
                id: userBasedId
                width: parent.width
                height: 400
                listTitle: "Similar Users Also Liked: "
                movies: []
            }
        }
    }
}


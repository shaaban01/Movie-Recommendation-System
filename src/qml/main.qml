import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3


Window {
    property var isAuth: false
        property var searching: false
            id: windowMain
            visible: true
            width: 1280
            height: 720
            title: "Movie Recommendation System"
            color:"#0C134F"


            function updateMovies()
            {
                var recommendationsArray = [];
                var recommendationsVariant = recommendationEnginePopularity.getRecommendations(userController.currentUserId, 30);

                for (var i = 0; i < recommendationsVariant.length; i++) {
                    var recommendation = recommendationsVariant[i];
                    recommendationsArray.push({movieId: recommendation.movieID, url: recommendation.url, title: recommendation.title, rating: recommendation.rating });
                }

                // Set the parsed array as the movies property
                trendingId.movies = recommendationsArray;

                recommendationsArray = [];
                recommendationsVariant = recommendationEngineContentBased.getRecommendations(userController.currentUserId, 30);
                console.log(recommendationsArray.toString());

                for (var i = 0; i < recommendationsVariant.length; i++) {
                    var recommendation = recommendationsVariant[i];
                    recommendationsArray.push({movieId: recommendation.movieID, url: recommendation.url, title: recommendation.title, rating: recommendation.rating });
                }
                contentBasedId.movies = recommendationsArray;

                recommendationsArray = [];
                recommendationsVariant = recommendationEngineUserBased.getRecommendations(userController.currentUserId, 30);

                for (var i = 0; i < recommendationsVariant.length; i++) {
                    var recommendation = recommendationsVariant[i];
                    recommendationsArray.push({movieId: recommendation.movieID, url: recommendation.url, title: recommendation.title, rating: recommendation.rating });
                }

                userBasedId.movies = recommendationsArray;

                var ratingsArray = [];
                var ratingsVariant = ratingController.getAllRatingsQML(userController.currentUserId);
                for (var i = 0; i < ratingsVariant.length; i++) {
                    var rating = ratingsVariant[i];
                    ratingsArray.push({movieId: rating.movieID, rating: rating.rating, url: rating.url, title: rating.title });
                }
                yourRatings.movies = ratingsArray;
            }

            function searchMovies(searchText)
            {
                if (searchText === "")
                {
                    searching = false;
                    return;
                }
                var searchResultsArray = [];
                var searchResultsVariant = movieController.fetchMoviesByTitleQML(searchText);
                for (var i = 0; i < searchResultsVariant.length; i++) {
                    var searchResult = searchResultsVariant[i];
                    searchResultsArray.push({movieId: searchResult.movieID, url: searchResult.url, title: searchResult.title, rating: 0});
                }
                searchResults.movies = searchResultsArray;
                searching = true;
            }
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
                                    updateMovies();
                                }
                            });
                        }
                    }
                }
            }
        }

        MovieGrid {
            id: searchResults
            visible: isAuth && searching
            anchors.top: navBar.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            movies: []
        }
        MovieGrid {
            id: yourRatings
            visible: navBar.currentPage === 1 && isAuth && !searching
            anchors.top: navBar.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            movies: []
        }

        MovieGrid {
            id: toWatch
            visible: navBar.currentPage === 2 && isAuth && !searching
            anchors.top: navBar.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            movies: []
        }


        Flickable {
            id: view
            visible: navBar.currentPage === 0 && isAuth && !searching
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


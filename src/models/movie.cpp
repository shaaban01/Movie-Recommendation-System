#include "movie.h"

Movie::Movie(const nlohmann::json &movieJson)
{
    adult = movieJson.value("adult", false);

    if (!movieJson["backdrop_path"].is_null())
        backdrop_path = movieJson["backdrop_path"];
        if (movieJson.contains("genres") && movieJson["genres"].is_array()) {
        for (const auto &genre : movieJson["genres"]) {
            if (genre.contains("id") && genre["id"].is_number()) {
                genre_ids.push_back(genre["id"]);
            }
        }
    }
    
    for (auto &genre_id : movieJson.value("genre_ids", std::vector<int>{}))
    {
        genre_ids.push_back(genre_id);
    }

    id = movieJson.value("id", 0);

    if (!movieJson["original_language"].is_null())
        original_language = movieJson["original_language"];

    if (!movieJson["original_title"].is_null())
        original_title = movieJson["original_title"];

    if (!movieJson["overview"].is_null())
        overview = movieJson["overview"];

    popularity = movieJson.value("popularity", 0.0);

    if (!movieJson["poster_path"].is_null())
        poster_path = movieJson["poster_path"];

    if (!movieJson["release_date"].is_null())
        release_date = movieJson["release_date"];

    if (!movieJson["title"].is_null())
        title = movieJson["title"];

    video = movieJson.value("video", false);
    vote_average = movieJson.value("vote_average", 0.0);
    vote_count = movieJson.value("vote_count", 0);
}

Movie::Movie() : adult(false), id(0), popularity(0.0), video(false), vote_average(0.0), vote_count(0) {}

void Movie::printAttributes() const
{
    std::cout << "adult: " << adult << std::endl;
    std::cout << "backdrop_path: " << backdrop_path << std::endl;
    std::cout << "genre_ids: ";
    for (const auto &genre_id : genre_ids)
    {
        std::cout << genre_id << " ";
    }
    std::cout << std::endl;
    std::cout << "id: " << id << std::endl;
    std::cout << "original_language: " << original_language << std::endl;
    std::cout << "original_title: " << original_title << std::endl;
    std::cout << "overview: " << overview << std::endl;
    std::cout << "popularity: " << popularity << std::endl;
    std::cout << "poster_path: " << poster_path << std::endl;
    std::cout << "release_date: " << release_date << std::endl;
    std::cout << "title: " << title << std::endl;
    std::cout << "video: " << video << std::endl;
    std::cout << "vote_average: " << vote_average << std::endl;
    std::cout << "vote_count: " << vote_count << std::endl;
}
#include "movie.h"

Movie::Movie(const nlohmann::json &movieJson)
{
    adult = movieJson.value("adult", false);

    if (!movieJson["backdrop_path"].is_null())
        backdrop_path = movieJson["backdrop_path"];

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

#ifndef VIEW_MOVIES_H
#define VIEW_MOVIES_H

#include <vector>
#include "movie.h"

class ViewMovies
{
public:
    ViewMovies(const std::vector<Movie> &movies) : movies_(movies) {}
    virtual void Display() = 0;

protected:
    std::vector<Movie> movies_;
};

class CmdViewMovies : public ViewMovies
{
public:
    CmdViewMovies(const std::vector<Movie> &movies) : ViewMovies(movies) {}
    void Display() override;
};

// Placeholder for future implementation
// class GuiViewMovies : public ViewMovies { };

#endif /* VIEW_MOVIES_H */

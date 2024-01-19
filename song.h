#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <vector>
#include <algorithm>

class song{

    public:
        song();
        song(std::size_t songNum, std::string titre, std::string artiste);
        std::size_t getSongId();
        std::string getArtist();
        std::string getTitle();

    protected:
        std::size_t songId;
        std::string artist;
        std::string title;
};

#endif // SONG_H

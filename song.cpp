#include "song.h"

song::song(){}

song::song(std::size_t songNum, std::string titre, std::string artiste){
    songId = songNum;
    title =  titre;
    artist = artiste;
}

std::size_t song::getSongId(){
    return songId;
}

std::string song::getArtist(){
    return artist;
}

std::string song::getTitle(){
    return title;
}

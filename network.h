#ifndef NETWORK_H //if user_h has not been defined yet,
#define NETWORK_H //then define it

#include <iostream>
#include <vector>
#include "user.h"
#include "post.h"
#include "song.h"

class Network{
    public:
    Network();
    std::size_t readUsers(char *c);
    std::size_t writeUsers(const char *c);
    void addUser(User* a);
    std::size_t getId(std::string a);
    User *getUser(std::size_t a);
    std::size_t numUsers();
    std::vector<std::size_t> suggestFriends(std::size_t og, std::size_t& score);

    std::size_t readSongs(const char *c);
    void addSong(std::size_t num, std::string titre, std::string artiste);
    song *getSong(std::size_t a); //passed in a song id, what is the song?
    std::string getTitle(std::size_t id); //passed in an id, what is the title?
    std::size_t getSongId(std::string title); //passed in a title, what is the id?
    std::string getArtist(std::string title); //passed in a title, what is the artist?
    std::string getArtistFromId(std::size_t id); //passed in an id, what is the artist?
    std::string displaySongs(std::vector<std::string> display);
    std::size_t numSongs();

    std::size_t addConnection(std::string a, std::string b);
    std::size_t removeConnection(std::string a, std::string b);

    void addPost(std::size_t ownerId, std::string message, std::size_t likes, bool incoming, std::size_t author, bool isPublic);
    int readPosts(const char* filename);
    std::string displayPosts(std::string name, std::size_t howMany, bool showOnlyPublic);

    //unused functions
    std::vector<std::size_t> shortestPath(std::size_t from, std::size_t to);
    std::vector<std::size_t> distanceUser(std::size_t from, std::size_t& to, std::size_t distance);
    std::vector<std::size_t> DFS(std::vector<std::size_t> &users);
    std::vector<std::vector<std::size_t> > groups();

private:
    std::vector<User *> users;
    std::vector<song*> songs;
};

#endif

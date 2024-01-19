#ifndef USER_H //if user_h has not been defined yet,
#define USER_H //then define it
#include <iostream>
#include <vector>
#include "post.h"
#include "song.h"

class User{
    public:
    User();
        User(std::size_t num, std::string nom, std::size_t code, std::size_t yr, std::vector<std::size_t> buds, std::vector<std::size_t> songz);
    std::size_t getId();
    std::string getName();
    std::size_t getYear();
    std::size_t getZip();
    std::vector<std::size_t> getFriends();
    std::vector<std::size_t> getSongs();
    void addFriend(std::size_t add);
    void deleteFriend(std::size_t remove);
    void addPost(Post*);
    void addSong(std::size_t);
    std::string displayPosts(std::size_t howMany, bool showOnlyPublic);
    std::string displaySongs();
    std::size_t previousId = -1; //used for shortest path
    std::size_t distance = -1; //gets the actual distance bwteen from and to in shortest path

private:
    std::size_t id;
    std::string name;
    std::size_t year;
    std::size_t zip;
    std::vector<std::size_t> friends;
    std::vector<std::size_t> songs;
    std::vector<Post*> messages;
};

#endif

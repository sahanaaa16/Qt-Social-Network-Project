#include "user.h"
#include <iostream>
#include <vector>
#include <algorithm>

User::User(){
}

User::User(std::size_t num, std::string nom, std::size_t code, std::size_t yr, std::vector<std::size_t> buds, std::vector<std::size_t> song){
    id = num;
    name = nom;
    zip = code;
    year = yr;
    friends = buds;
    songs = song;
}

std::size_t User::getId(){
    return id;
}

std::string User::getName(){
    return name;
}

std::size_t User::getZip(){
    return zip;
}

std::size_t User::getYear(){
    return year;
}

std::vector<std::size_t> User::getFriends(){
    return friends;
}

std::vector<std::size_t> User::getSongs(){
    return songs;
}

void User::addFriend(std::size_t add){
    bool there = false;
    for(std::size_t i = 0; i < friends.size(); i++){
        if(friends[i] == add){
            there = true;
        }
    }
    if(there == false){
        friends.push_back(add);
    }
}

 void User::deleteFriend(std::size_t remove){
    for(std::size_t i = 0; i < friends.size(); i++){
        if(friends[i] == remove){
            friends.erase(friends.begin()+i);
        }
    }
 }

void User::addPost(Post* post){
    messages.push_back(post);
    //std::cout << "In add posts, messages.size is: " << messages.size() << std::endl;
}

//goal:displays each user's posts
std::string User::displayPosts(std::size_t howMany, bool showOnlyPublic){
    std::string answer = "";
    //std::cout << "messages.size is: " << messages.size() << std::endl;
    //std::cout << "howMany is: " << howMany << std::endl;

    auto element = messages.end();
    while(std::size_t i = 0 < howMany && element != messages.begin()){
        element--;
        std::string currPost = (*element)->displayPost();

        if (showOnlyPublic){ //if it is an incoming post
            if ((currPost.substr(0,7) != "Private")) {
                answer.append(currPost + "\n\n");
                i++;
            }
        }

        else {
            answer.append(currPost + "\n\n");
            i++;
        }

    }

//    for(std::size_t i = 0; i < messages.size() && count <= howMany; i++){
//            std::string postMessage = messages[i] -> displayPost();
//            if (showOnlyPublic){
//            if ((postMessage.substr(0,6) == "Public")) {
//                    answer += postMessage;
//                    answer += "\n\n";
//                    count++;
//                }
//            } else {
//                answer += postMessage;
//                answer += "\n\n";
//                count++;
//            }
//    }
    if(answer == ""){
        answer = "No posts to show :/";
    }
    return answer;
}

std::string User::displaySongs(){
    std::string answer = "";

//    now iterate though the songs to put them in the user box
//    auto element = songs.end();
//    while(element != songs.end()){
//        element --;
//        std::string currSong = (*element)->displaySong();
//    }
}

void User::addSong(std::size_t hi){
    if (std::find(songs.begin(), songs.end(), hi) == songs.end()){
        songs.push_back(hi);
    }
}

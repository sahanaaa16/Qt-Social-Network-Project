#include <iostream>
#include <vector>
#include <fstream>
#include "network.h"
#include "user.h"
#include <string>
#include <sstream>
#include <queue>

//pre: none
//post: creates an empty Network
Network::Network(){
    users=std::vector<User *>();
}

//pre: none
//post: takes in a file of users and add its into our already existing user list
std::size_t Network::readUsers(char *c){
    std::ifstream file;
    file.open(c);

    if(!file.is_open()){
        return -1;
    }

    int size;
    file >> size; //makes and reads in the size of the user list

    for(int i = 0; i < size; i++){
        std::size_t id;
        std::string firstName, lastName, fullName;
        std::size_t year;
        std::size_t zipcode;
        std::vector<std::size_t> friends;
        std::vector<std::size_t> songz;
        friends.clear();

        file >> id;
        file >> firstName >> lastName;
        fullName = firstName + " " + lastName;
        file >> year;
        file >> zipcode;

        std::string line;
        getline(file, line); //goes to next from zipcode line and reads in a dummy value
        getline(file, line); //line gets the user's friends' id
        std::stringstream ss(line);

        std::size_t num;
        while(ss >> num){
            friends.push_back(num);
        }

        getline(file, line);

        std::stringstream sd(line);

        std::size_t songNum;
        while(sd >> songNum){
            songz.push_back(songNum);
        }

        User* a = new User(id, fullName, year, zipcode, friends, songz);
        addUser(a);
    }
    return 0;
}

//pre: none
//post: takes in the name of an unwritten file and writes all of the network's existing users into the file
std::size_t Network::writeUsers(const char *c){
    //std::ifstream file("socialnetwork.txt"); //reads in file from folder
    std::ofstream output(c); //makes a new output file
    std::string line;

    if(!output.is_open()){
        return -1;
    }

    std::cout << users.size() <<std::endl;
    //add the users to the file
    output << users.size() <<std:: endl;

    for(std::size_t i = 0; i < users.size(); i++){
        output << users[i]->getId() << std::endl;
        output << char(9) << users[i]->getName() << std::endl;
        output << char(9) << users[i]->getYear() << std::endl;
        output << char(9) << users[i]->getZip() << std::endl;
        output << char(9); //tab in front of friends
        for(int x = 0; x < users[i]->getFriends().size(); x++){
            output << users[i]->getFriends()[x] << " ";
        }
        output << std::endl;
    }

    output.close();
    return 0;
}

//pre: none
//post: adds a user to the network database by takingg in a pointer to a user object
void Network::addUser(User* a){
    users.push_back(a);
}

//pre: none
//post: makes two users, whose names are passed in, into friends.
std::size_t Network::addConnection(std::string a, std::string b){ //done
    std::cout << "a is: " << a << std::endl;
    std::cout << "b is: " << b << std::endl;
    std::size_t first = 999; //chose an arbitraily high number because - 1is not a size_t
    std::size_t second = 999;

        for(int i = 0; i < users.size(); i++){
            //std::cout << users[i]->getName() <<std::endl;
            if(users[i]->getName() == a){
                first = i;
            }
            if(users[i]->getName() == b){
               second = i; 
            }
        }
        //std::cout << "First is: " << first << std::endl;
        //std::cout << "Second is: " << second << std::endl;

        if(first == 999 || second == 999){
            return -1;
        }

        users[first]->addFriend(users[second]->getId());
        users[second]->addFriend(users[first]->getId());
        return 0;
    }

//pre: none
//post: takes in two user's names and removes them as friends from each other
std::size_t Network::removeConnection(std::string a, std::string b){
    std::cout << "First person: " << a << std::endl;
    std::cout << "Second person: " << b << std::endl;
    std::size_t first = -1;
    std::size_t second = -1;

    for(int i = 0; i < users.size(); i++){
        if(users[i]->getName()== a){
            first = i;
        }
        if(users[i]->getName()== b){
            second = i; 
        }
    }

    std::cout << "First id is: " << first << std::endl;
    std::cout << "Second id is: " << second << std::endl;

    if(first == 999 || second == 999){
        return -1;
    }

    users[first]->deleteFriend(second);
    users[second]->deleteFriend(first);
    return 0;
}

//pre: none
//post: gets the id of a user, given their name
std::size_t Network::getId(std::string a){
    //std::cout << "The name of the person is:" << a << std::endl;
    std::size_t ans = 999;
    for(int i = 0; i < users.size(); i++){
        if(users[i]->getName() == a){
            ans = users[i]->getId();
        }
    }
    return ans;
}

//pre: none
//post: returns the number of users
std::size_t Network::numUsers(){
    return users.size();
}

// pre: none
// post: returns a user given their ID
User* Network::getUser(std::size_t a){
    for(std::size_t i = 0; i < users.size(); i++){
        if(users[i]->getId() == a){
            return users[i];
        }
    }

    return new User();
}

//pre:
//post:
void Network::addPost(std::size_t ownerId, std::string message, std::size_t likes, bool incoming, std::size_t author, bool isPublic){
    User* tempUser = getUser(author);
    std::string name = tempUser -> getName();

    Post* newPost;
    if(incoming){
        newPost = new IncomingPost(ownerId, message, likes, isPublic, name);
    }
    else{
        newPost = new Post(ownerId, message, likes);
    }
    users[ownerId]->addPost(newPost);
}

//goal: displays the posts of a user by checking that a user exists and then the given number of posts
std::string Network::displayPosts(std::string name, std::size_t howMany, bool showOnlyPublic){
    std::size_t tempId = getId(name);
    std::cout << "tempId: " << tempId;
    User* tempUser = getUser(tempId);
    std::cout << "tempUser: " << tempUser;
    if(tempUser){ //if the user exists
        return tempUser -> displayPosts(howMany, showOnlyPublic);
    }
    return "doesn't work :/";
}

//pre: file exists and is in correct format
//post: reads in a file and returns the number of posts in the document
int Network::readPosts(const char* filename){ //reads in all the posts and returns the number of posts
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()){
        return -1;
    }
    int n;
    file >> n; //read in the post number

    for(int i = 0; i < n; i++){
        std::size_t postId;
        std::string message;
        std::size_t userId;
        std::size_t likes;
        std::string first, last;
        std::string line;

        file >> postId;
        std::getline(file, line); //actually reads the message
        std::getline(file, line);
        line.erase(line.begin());
        message = line;
        //std::cout << "  Message: " << message;

        file >> userId;
        //std::cout << "  userId: " << userId;
        file >> likes;
        //std::cout << "  likes: " << likes;

        std::getline(file, line);
        std::getline(file, line);

        if(line.empty()) {
            //std::cout << "  Adding regular post";
            addPost(userId, message, likes, false, 0, true);
            continue;
        }

        bool pub;
        if(line == "public") {
            pub = true;
        } else {
            pub = false;
        }

        file >> first >> last;
        std::string author = first + " " + last;
        //std::cout << "  Author: " << author;
        addPost(userId, message, likes, true, getId(author), pub);
        //std::cout << "  Adding incoming post";
    }

    return n;
}

//pre: none
//post: returns a list of mutuals with the og user that has x amount of connections
//      the higher the score, the more likely og user will want to connect to them
std::vector<std::size_t> Network::suggestFriends(std::size_t who, std::size_t& score) {
    score = 0;
    User* target = getUser(who);
    if (!target) {
    score = -1;
    return std::vector<std::size_t>();
    }

    // Essentially a lookup table
    std::vector<bool> friends(numUsers(), false);
    for (auto id : target->getFriends())
    friends[id] = true;
    std::vector<std::size_t> scores(numUsers(), 0);

    for (auto user : users){ //looks up if currentId is our og
    std::size_t currentId = user->getId();
    if (currentId == who)
            continue;

    for (int i = 0; i < user->getFriends().size(); i++){// If the user is a friend of the target, we don't want them
            if (user->getFriends()[i] == who) {
                scores[currentId] = 0;
                break;
            }

            if (friends[user->getFriends()[i]]) {//increase score by 1 if they match
                scores[currentId]++;
                if (scores[currentId] > score)
                    score = scores[currentId];
            }
    }
    }

    // If nobody had any friends in common, the highest score will be 0
    if (score == 0) {
    score = -1;
    return std::vector<std::size_t>();
    }

    std::vector<std::size_t> ret;
    auto it = scores.begin();
    // Collect indices of users with passed in score connection amount
    while((it = std::find(it, scores.end(), score)) != scores.end()) {
    ret.push_back(it - scores.begin());
    it++;
    }

    for(int i = 0; i < ret.size(); i++){ //remove user if it already exists
        for(int j = 0; j < target->getFriends().size(); j++){
            if(target->getFriends()[j] == ret[i]){
                ret.erase(ret.begin() + i);
            }
        }
    }
    return ret;
}



//pre: none
//post: returns a vector that contains the shortest path between two vectors
std::vector<std::size_t> Network:: shortestPath(std::size_t from, std::size_t to){
    if(from == to){
        return std::vector<std::size_t>(); //if same person, return an empty vector
    }

    std::queue <std::size_t> queue;
    std::vector<size_t> answer;
    queue.push(from); //push temp to queue
    users[from]->distance = 0; //initially make distance from pointer to self 0

    while(!queue.empty()){
        std::size_t temp = queue.front();
        std::vector<size_t> f = users[temp]->getFriends();
        queue.pop();

        for(auto e:f){
            if(users[e]->distance != -1){
                users[e]->distance = users[temp]->distance+1;
                users[e]->previousId = temp;
                queue.push(e);
            }
        }
    }

    std::size_t temp = users[to]->previousId;
    answer.push_back(to);
    while(temp != -1 ){
        answer.push_back(temp);
        temp = users[temp]-> previousId;
    }
    for(std::size_t i = 0; i < users.size(); i++){
        users[i]->distance = -1;
        users[i]->previousId = -1;
    }
    return answer;
}

//pre: none
//post: slay lol traditional DFS
std::vector<std::size_t> Network::DFS(std::vector<std::size_t> &users){
    std::vector<std::size_t> set;
    std::vector<std::size_t> stck;
    std::vector<bool> visited(numUsers(), 0);

    stck.push_back(users[0]);

    while(stck.size() > 0) {
        std::size_t currentId = stck[stck.size() - 1];
        stck.pop_back();

        if(visited[currentId]) { continue; }
        visited[currentId] = true;

        users.erase(std::find(users.begin(), users.end(), currentId));
        set.push_back(currentId);

        for(auto i : getUser(currentId)->getFriends())
            stck.push_back(i);
    }
    return set;
}

void Network::addSong(std::size_t num, std::string titre, std::string artiste){
    song* newSong;
    newSong = new song(num, titre, artiste);
    songs.push_back(newSong);
}

std::size_t Network::readSongs(const char *c){
    std::ifstream file;
    file.open(c);
    if(!file.is_open()){
        return -1;
    }

    int n;
    file >> n; //read in the song number

    for(int i = 0; i < n; i++){
        std::size_t songId;
        std::string title;
        std::string artist;
        std::string line;

        file >> songId;
        std::getline(file, line); //Do a getline to go past the songId

        std::getline(file, line);
        title = line;

        std::getline(file, line);
        artist = line;

        addSong(songId, title, artist);
        std::getline(file, line); //skip a line
        //std::cout << "song added" << songId  << "  " << title << artist;
    }
    std::cout << "Song size is: " << songs.size();
    return n;
}

song* Network::getSong(std::size_t id){
    for(std::size_t i = 0; i < songs.size(); i++){
        if(songs[i]->getSongId() == id){
            return songs[i];
        }
    }
    return new song();
}

std::string Network::getTitle(std::size_t id){
    song* temp = getSong(id);
    return temp->getTitle();
}

std::size_t Network::getSongId(std::string title){
    for(std::size_t i = 0; i < songs.size(); i++){
        if(songs[i]->getTitle() == title){
            return songs[i]->getSongId();
        }
    }
    return -1;
}

std::string Network::getArtist(std::string title){
    for(std::size_t i = 0; i < songs.size(); i++){
        if(songs[i]->getTitle() == title){
            return songs[i]->getArtist();
        }
    }
    return "n/a";
}

std::string Network::getArtistFromId(std::size_t id){
    return songs[id]->getArtist();
}

std::string Network::displaySongs(std::vector<std::string> display){
    std::string ans;
    for(std::size_t i = 0; i < display.size(); i++){
        ans = ans + (display[i] + "\n");
    }
    return ans;
}

std::size_t Network::numSongs(){
    return songs.size();
}

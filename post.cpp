#include "post.h"

    Post::Post(){}
    
    Post::Post(std::size_t id, std::string text, std::size_t heart){
        postId = id;
        message = text;
        likes = heart;
    }

    std::size_t Post::getPostId(){
        return postId;
    }

    std::string Post::getMessage(){
        return message;
    }

    std::size_t Post::getLikes(){
        return likes;
    }

    std::string Post::displayPost(){
        return message + "\nLiked by: " + std::to_string(likes) + " people";
    }

    bool IncomingPost::isPub(){
        return isPublic;
    }

IncomingPost::IncomingPost(){
    isPublic = false;
}

IncomingPost::IncomingPost(std::size_t id, std::string text, std::size_t heart, bool pub, std::string auth){
    postId = id;
    message = text;
    likes = heart;
    isPublic = pub;
    //std::cout << "From: " << auth;
}

std::string IncomingPost::displayPost(){
    if(!isPublic){
        return "Private: " + Post::displayPost();
    }
    else{
        return "Public: " + Post::displayPost();
    }
}

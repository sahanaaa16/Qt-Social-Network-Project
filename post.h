#ifndef POST_H //if post_ has not been defined yet,
#define POST_H //then define it

#include <iostream>
#include <vector>
#include <algorithm>

class Post{
    public:
    Post();
    Post(std::size_t id, std::string text, std::size_t heart);
    std::size_t getPostId();
    std::string getMessage();
    std::size_t getLikes();
    virtual std::string displayPost();

    protected:
    std::size_t postId; //like username but for posts
    std::string message; //actual text
    std::size_t likes; //obvi
};

class IncomingPost : public Post{
public:
    IncomingPost();
    IncomingPost(std::size_t id, std::string text, std::size_t heart, bool pub, std::string writer);
    std::string displayPost();
    bool isPub();

private:
    bool isPublic;
};

#endif
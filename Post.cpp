/****************************************************************************************************************************
Title         :   Post.cpp
Author        :   Dream Team
Description   :   Implementation for Post class
****************************************************************************************************************************/

/**
 *
 * @file: Post.cpp
 *
 */
#include "Post.hpp"


/**
   Parameterized constructor.
   @param      : The title of the post (a string)
   @param      : The body content of the post (a string)
   @param      : The username of the Account that added this post (a string)

   @post         : Sets the title, body and username to the value of the parameters
                   It will also generate the current time and store it
*/
Post::Post(std::string title, std::string body, std::string username) {
    post_title_ = title;
    post_body_ = body;
    time_stamp_ = time(NULL);
    username_ = username;
    likes_ = 0;
}


/**
   @return : the title of the Post
*/
std::string Post::getTitle() const {
    return post_title_;
}


/**
  @param  : a reference to title of the Post
  @post   : sets the private data member to the value of the parameter
*/
void Post::setTitle(const std::string& title) {
    post_title_ = title;
}


/**
   @return : the body of the Post
*/
std::string Post::getBody() const {
    return post_body_;
}


/**
   @param  : a reference to body of the Post
   @post   : sets the private data member to the value of the parameter
*/
void Post::setBody(const std::string& body) {
    post_body_ = body;
}


/*
   Accessor Function
   @return       : username associated with this Post
*/
std::string Post::getUsername() const {
    return username_;
}


/*
   Mutator Function
   @param        : a reference to the username associated with this Post
   @post   : sets the private data member to the value of the parameter
*/
void Post::setUsername(const std::string& username) {
    username_ = username;
}


/**
    @post:  prints out the post in the following format:
    \n
    {post_title_} at {time_stamp_}:
    {post_body_}
    \n
*/
void Post::getTimeStamp() const {
    std::cout << asctime(localtime(&time_stamp_));
}
/**
 *
 * @return time_t value of the current item
 */
time_t Post::getTime() const {
    return time_stamp_;
}


/*
   Mutator Function
   @post   : sets the private data member to the current time
*/
void Post::updateTimeStamp() {
    time_stamp_ = time(0);
}

/**
 * 
 * @note: operator that compares the the usernames of two post objects and sees if the left Post is less than the right post
 * @return: returns true if the Post on the left side is less than  (first in the alpha bet) than the Post on the right side.
 */
bool Post::operator<(const Post& post_)const{
    std::string this_len = this->getUsername();
    std::string post_len = post_.getUsername();
    return this_len < post_len;
}


/**
 * 
 * @note: operator that compares the the usernames of two post objects and sees if the left post is greater than the right post. 
 * @return: returns true if the Post on the left side is greater (farther in the alphabet) than the Post on the right side.
 */
bool Post::operator>(const Post& post_) const{
    std::string this_len = this->getUsername();
    std::string post_len = post_.getUsername();
    return this_len > post_len;
    return false;
}
/**
 *
 * @return like private member of type int
 */
int Post::getLikes() const {
   return likes_;
}
/**
 *
 * @pre: like private member has to be created
 * @post: like integer will be incremented
 *
 */
void Post::like() {
    likes_++;
}
/**
 *
 *
 * @param prior_val: priority value that will be set
 */
void Post::setPriority(const priority& prior_val) {
    priority_id = prior_val;
}
/**
 *
 * @pre: priority enum must be created with the priority_id set to medium in the constructor
 * @return: whichever priority the Post is, as a int 0-2
 */
Post::priority Post::getPriority() const {
    return priority_id;
}



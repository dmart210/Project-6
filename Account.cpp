/****************************************************************************************************************************
Title         :   Account.hpp
Author        :   Dream Team
Description   :   header/interface files for Account class
****************************************************************************************************************************/


/**
 *
 * @author: Dariel A. Martinez
 * @file: Account.cpp
 */
#include "Account.hpp"

//default constructor
//@post:  set username and password to ""
//        creates an empty vector of post objects to store into feed_
Account::Account()
{
    username_ = "";
    password_ = "";
    posts_ = LinkedList<Post*>();
    following_ = {};
}


/**
    Parameterized Constructor
    @param username  : username of the account, stored into username_
    @param password  : password of the account, stored into password_
    @post:             sets the private members to the value of the parameters
*/
Account::Account(std::string username, std::string password) : username_(username), password_(password), posts_(LinkedList<Post*>()), following_({}), net_(nullptr) { }

/**
  @return:     the username of the Account
*/
std::string Account::getUsername() const { return username_; }


/**
  @param:     a reference to the username of the Account
  @psot:      sets the parameter to the value of the private member
*/
void Account::setUsername(const std::string& username) { username_ = username; }


/**
  @return:     the password of the Account
*/
std::string Account::getPassword() const { return password_; }


/**
  @param a reference to the password of the Account
  @post:      sets the private member to the value of the parameter
*/
void Account::setPassword(const std::string& password) { password_ = password; }


/**
      Accessor function
      @return           :   the pointer to the Network the account is in
   */
Network<Account>* Account::getNetwork() const { return net_; }


/**
      Mutator function
      @param            :   a pointer to a Network
      @post             :   the Network pointer private member points to the input Network
   */
void Account::setNetwork(Network<Account>* network) { net_ = network; }


/**
    @param newPost   : The pointer to the Post object that will be added to its list
    @return          : Will return true if a post gets added sucesfully to the vector
    @pre             : a minLike and maxLike stack has to be created which will be compared and then the least will be pushed to
                       the minLike stack, and the greater one will be pushed to the maxLike stack.
    @post:           " Adds post to posts_ and its Networks feed_
*/
bool Account::addPost(Post* newPost){
//    if (posts_.getSize() == 0){
//        minLike.push(newPost);
//        maxLike.push(newPost);
//    }
//    else if (posts_.getSize() > 0 && minLike.top()->getLikes() > newPost->getLikes()){
//        maxLike.push(minLike.top());
//        minLike.push (newPost);
//    }
//    else if (posts_.getSize() > 0 && minLike.top()->getLikes() < newPost->getLikes()){
//        maxLike.push(newPost);
//    }
    posts_.insert(newPost, 0);
    net_->addToFeed(newPost);
    return true;
}



/*
    @post:      Prints the feed_ that contains the post objects by calling their display function
*/
void Account::viewPosts() const {

    Node<Post*>* itt = posts_.getHeadPtr();

    while (itt != nullptr) {
        itt->getItem()->displayPost();
        itt = itt->getNext();
    }

}



/**
      @param            :   the username of the Account to follow
      @return           :   true if the account was successfully able to follow, false otherwise
      @post             :   adds the username to the vector of following accounts only if
                            it is affiliated to a Network AND it is not already following an account
                            with the same username.
   */
bool Account::followAccount(const std::string username){

    bool exists = false;

    for(std::string un : following_) {
        if(un == username) {
            exists = true;
        }
    }

    if(!exists && net_ != nullptr) {
        following_.push_back(username);
        return true;
    }

    return false;
}


/**
      @return           :   the vector of usernames the Account is following
   */
std::vector<std::string> Account::viewFollowing() const {
    return following_;
}


/**
  @return           :  true if account has same private members as parameter,
                       false otherwise
*/
bool Account::operator==(const Account &acc) const {
    if(acc.getUsername() == this->username_ && acc.getPassword() == this->password_) {
        return true;
    }

    return false;
}



/*
@param            :   A pointer to a Post
@return           :   True iff the Post was successfully found and removed,
                      false othewise.
@post             :   Removes the given Post from its list
                      as well as from the Network's feed.
*/
bool Account::removePost(Post* post){
    int postPosition = posts_.getIndexOf(post);

    if (postPosition > -1) {
        posts_.remove(postPosition);
        net_->removePostFromFeed(post);
        return true;
    }
    return false;
}



/*
@param            :   Pointer to a Post object
@param            :   The new title of the Post (or an empty string if you do not
                      want to change it)
@param            :   The new body of the Post (or an empty string if you do not
                      want to change it)

@post            :   This function will take the Post and given the new title and body,
                     update the Posts title and body as appropriate. It will also update
                     the `timestamp_` to the current time of the update. This function should then
                     update the location of the Post in its list of `posts_` to the front of the list
                     as well as utilizing its Network pointer to do the same in the `feed_`.
*/
bool Account::updatePost(Post* post, std::string new_title, std::string new_body) {
    if(new_title != "") { post->setTitle(new_title); }

    if(new_body != "") { post->setBody(new_body); }

    post->updateTimeStamp();
    posts_.moveItemToTop(post);
    return net_->updateFeed(post);
}

/**
 * @pre: a min and max stack has to be created and implemented in the addpost to be able to compare which Post has the greatest
 *       and least amount of likes
 *
 * @return: returns the top which  of the minLike stack that will have the Post with the lowest like count.
 */
Post* Account::getMinLikes() const {
    return minLike.top();
}
/**
 * @pre: a min and max stack has to be created and implemented in the addpost to be able to compare which Post has the greatest
 *       and least amount of likes
 *
 * @return: returns the top of the minLike stack that will have the Post with the lowest like count.
 */
Post* Account::getMaxLikes() const {
    return maxLike.top();
}

/**
 *
 * @pre: A priority stack needs to be established so we can pop the Post* to a temp stack with the ordered Priority in order.
 * @post: For the post to be able to be pushed to the temp stack that will eventually go into the vector, we need to create
 *        a stack and then from that stack push it back to the vector in order
 * @return: A vector of a vector that is increasing in Priority from oldest to newest
 */
std::vector<Post*> Account::increasingPriorityOldestToNewest() {
    std::vector<Post*> fromOldToNew;
//    Node<Post*>* iterator = posts_.getHeadPtr();
//    std::stack<Post*> timeStack;
//
//    std::stack<Post::priority> priority_stack;
//    priority_stack.push(Post::LOW);
//    priority_stack.push(Post::MEDIUM);
//    priority_stack.push(Post::HIGH);
//    while (iterator->getNext()!= nullptr || !priority_stack.empty()){
//        if (iterator->getItem()->getPriority() == priority_stack.top()){
//            timeStack.push(iterator->getItem());
//        }
//        else if (iterator->getItem()->getPriority() < priority_stack.top()){
//            priority_stack.pop();
//            timeStack.push(iterator->getItem());
//        }
//        fromOldToNew.push_back(timeStack.top());
//        iterator = iterator->getNext();
//    }

    return fromOldToNew;
}

/**
 *
 * @pre: A priority stack needs to be established so we can pop the Post* to a temp stack with the ordered Priority in order.
 * @post: For the post to be able to be pushed to the temp stack that will eventually go into the vector, we need to create
 *        a stack and then from that stack push it back to the vector in order
 * @return: A vector of a vector that is increasing in Priority from oldest to newest
 */
std::vector<Post*> Account::increasingPriorityNewestToOldest() {
    std::vector<Post*> fromNewToOld;
    return fromNewToOld;
}

/**
 *
 * @pre: A priority stack needs to be established so we can pop the Post* to a temp stack with the ordered Priority in order.
 * @post: For the post to be able to be pushed to the temp stack that will eventually go into the vector, we need to create
 *        a stack and then from that stack push it back to the vector in order
 * @return: A vector of a vector that is increasing in Priority from oldest to newest
 */
std::vector<Post*> Account::decreasingPriorityOldestToNewest() {
    std::vector<Post*> decreaseOldToNew;
    return decreaseOldToNew;
}

/**
 *
 * @pre: A priority stack needs to be established so we can pop the Post* to a temp stack with the ordered Priority in order.
 * @post: For the post to be able to be pushed to the temp stack that will eventually go into the vector, we need to create
 *        a stack and then from that stack push it back to the vector in order
 * @return: A vector of a vector that is increasing in Priority from oldest to newest
 */
std::vector<Post*> Account::decreasingPriorityNewestToOldest() {
    std::vector<Post *> decreaseNewToOld;
    return decreaseNewToOld;
}

bool Account::increasingTime(Post *ptr1, Post *ptr2) {
    if (ptr1->getTime() < ptr2->getTime()){
        return true;
    }
    return false;
}

bool Account::priorIncrease(Post::priority val, Post::priority val_2) {
    if (val < val_2) return true;
    return false;
}

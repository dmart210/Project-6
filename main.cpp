#include "Account.hpp"
#include "General.hpp"
#include "LinkedList.hpp"
#include "Network.hpp"
#include "Node.hpp"
#include "Post.hpp"
#include <iostream>
using namespace std;

int main() {
    Network <Account>* net_ = new Network<Account>();
    Account acc("username", "password");
    //Post ptr1
    Post* ptr = new General ("username", "password", "user");
    ptr->like();
    ptr->like();
    ptr->setPriority(Post::HIGH);
    // Post ptr 2
    Post* ptr2 = new General ("username", "password", "user");
    ptr2->like();
    ptr2->setPriority(Post::LOW);
    cout << "PRIORITY: " <<  ptr2->getPriority() << endl;
    Post* ptr3 = new General ("userna", "description", "username");
    ptr3->like();
    ptr3->like();
    ptr3->like();
    ptr3->like();
    ptr3->like();
    ptr3->like();
    ptr3->setPriority(Post::MEDIUM);
    // account ptr
    Account* acc_ptr = &acc;
    acc_ptr->setNetwork(net_);
    net_->addAccount(acc_ptr);
    acc_ptr->addPost(ptr);
    acc_ptr->addPost(ptr2);
    acc_ptr->addPost(ptr3);
    vector<Post*> vec;
    vec = acc_ptr->increasingPriorityOldestToNewest();
    cout << "VEC SIZE: " << vec.size() << endl;



}
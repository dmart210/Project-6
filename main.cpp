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
    Post* ptr = new General ("username", "password", "user");
    ptr->like();
    ptr->like();
    ptr->setPriority(LOW);
    cout << ptr->getLikes() << endl;
    Post* ptr2 = new General ("username", "password", "user");
    ptr2->like();
    cout << ptr2->getLikes() << endl;
    Account* acc_ptr = &acc;
    acc_ptr->setNetwork(net_);
    net_->addAccount(acc_ptr);
    acc_ptr->addPost(ptr);
    acc_ptr->addPost(ptr2);

}

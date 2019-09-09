#include <iostream>

using namespace std;


template<typename element_t>
class SimpleNode {
public:
    SimpleNode(element_t* element = nullptr) 
        : element_(element),
          next_(nullptr) {}
    ~SimpleNode() {}

    element_t* element_;
    SimpleNode* next_;
};

template<typename node_t>
class SimpleList {
public:
    SimpleList();
    ~SimpleList();

    node_t* front(void) {
        return head_.next_;
    }
    node_t* back(void) {
        node_t* ret = &head_;
        while (ret->next_) {
            ret = ret->next_;
        }
        return ret;
    }
    node_t* push_front(node_t* node) {
        node_t* temp = head_.next_;
        head_.next_ = node;
        node->next_ = temp;
        return node;
    }
    node_t* pop_front(void);
    node_t* push_back(node_t* node) {
        node_t* back = this->back();
        cout<<"back->element_="<<back->element_<<endl;
        back->next_ = node;
        node->next_ = nullptr;
        return node;
    }
    node_t* pop_back(void);
    node_t* remove(node_t* node) {}

private:
protected:
    node_t head_ = {0};
};
template<typename element_t>
SimpleList<element_t>::SimpleList() {
}

template<typename element_t>
SimpleList<element_t>::~SimpleList() {}

int main () {
    int element = 100;
    SimpleNode<int> node1(&element);
    int element2 = 101;
    SimpleNode<int> node2(&element2);
    int element3 = 102;
    SimpleNode<int> node3(&element3);
    int element4 = 104;
    SimpleNode<int> node4(&element4);
    int element5 = 105;
    SimpleNode<int> node5(&element5);
    SimpleNode<int>* elem;
    SimpleList<SimpleNode<int>> list;
    list.push_front(&node1);
    list.push_front(&node2);
    list.push_front(&node3);
    list.push_back(&node1);
    list.push_back(&node2);
    list.push_back(&node3);
    // list.push_back(&node4);
    // list.push_back(&node5);
    elem = list.front();
    while (elem) {
        cout<<elem->element_<<":"<<*elem->element_<<", ";
        elem = elem->next_;
    }
    cout<<endl;
    cout<<"hello world";
    return 0;
}
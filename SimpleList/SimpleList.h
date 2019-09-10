#ifndef SIMPLE_LIST_H_
#define SIMPLE_LIST_H_

#include <stdio.h>
#include <string.h>

template<class element_t>
class SimpleNode {
 public:
  SimpleNode(element_t element = {0})
      : element_(element),
        next_(nullptr) {}
  ~SimpleNode() {}
  SimpleNode& operator=(const SimpleNode &) = delete;
  SimpleNode(const SimpleNode&) = delete;

  element_t element_;
  SimpleNode* next_;
};

template<class node_t>
class SimpleList {
 public:
  SimpleList() {}
  ~SimpleList() {}
  SimpleList& operator=(const SimpleList &) = delete;
  SimpleList(const SimpleList&) = delete;

  node_t* front(void) {
    return head_.next_;
  }
  node_t* back(void) {
    node_t* ret = head_.next_;
    if (!ret) {
      // list is empty
      return nullptr;
    }
    while (ret->next_) {
      ret = ret->next_;
    }
    return ret;
  }
  node_t* push_front(node_t* node) {
    node_t* temp = head_.next_;
    head_.next_ = node;
    node->next_ = temp;
    size_++;
    return node;
  }
  node_t* pop_front(void) {
    node_t* front = head_.next_;
    if (front && front->next_) {
      head_.next_ = front->next_;
    }
    if (front) {
      size_--;
    }
    return front;
  }
  node_t* push_back(node_t* node) {
    node_t* back = this->back();
    if (!back) {
      // if the list is empty
      return push_front(node);
    }
    back->next_ = node;
    node->next_ = nullptr;
    size_++;
    return node;
  }
  node_t* pop_back(void) {
    if (!front()) {
      return nullptr;
    }
    node_t* prev = &head_;
    node_t* back = prev->next_;
    while (back->next_) {
      prev = back;
      back = back->next_;
    }
    prev->next_ = nullptr;
    if (back) {
      size_--;
    }
    return back;
  }
  node_t* remove(node_t* node) {
    node_t* prev = &head_;
    node_t* ret = prev->next_;
    do {
      if (ret == node) {
        prev->next_=node->next_;
        return node;
      }
      prev = ret;
      ret = ret->next_;
    } while (ret);
    return nullptr;
  }
  void clear(void) {
    head_.next_ = nullptr;
  }
  size_t size(void) { return size_; }

  node_t* get_node_if(bool (*isNode)(node_t*)) {
    node_t* ret = head_.next_;
    while (ret) {
      if (isNode(ret)) {
        return ret;
      }
      ret = ret->next_;
    }
    return ret;
  }

 private:
 protected:
  node_t head_ = { 0 };
  size_t size_ = 0;
};

template<class element_t,size_t DEEP, template<class> class node_t = SimpleNode>
class SimpleQueue : private SimpleList<node_t<element_t>> {
 public:
  SimpleQueue() {}
  ~SimpleQueue() {}
  SimpleQueue& operator=(const SimpleQueue &) = delete;
  SimpleQueue(const SimpleQueue&) = delete;

 element_t& peek(void) { return SimpleList<node_t<element_t>>::front()->element_; };
 element_t& pop(void) {
   node_t<element_t>* node = SimpleList<node_t<element_t>>::pop_front();
   if (node) {
     first_++;
     if (first_ >= DEEP) {
       first_ = 0;
     }
   }
   return node->element_;
 }
 element_t& push(element_t& elem) {
   if (size() >= DEEP) {
     pop();
   }
   memcpy(&node_[last_].element_, &elem, sizeof(element_t));
   SimpleList<node_t<element_t>>::push_back(&node_[last_]);
   last_++;
   if (last_ >= DEEP) {
     last_ = 0;
   }
   return node_[last_].element_;
 }
 size_t size(void) { return SimpleList<node_t<element_t>>::size(); }
 void showMessage() {
  printf("first_ = %lu, last_ = %lu, size = %lu\n", first_, last_, size());
  for (size_t i = 0; i < size(); ++i) {
    printf("%d,", node_[(i+first_)%DEEP].element_);
  }
  printf("\n");
 }

 protected:
  node_t<element_t> node_[DEEP];
  size_t first_ = 0;
  size_t last_ = 0;
};

//template<typename element_t>
//SimpleList<element_t>::SimpleList() {
//}
//
//template<typename element_t>
//SimpleList<element_t>::~SimpleList() {
//}

//int main () {
//    int element = 100;
//    SimpleNode<int> node1(&element);
//    int element2 = 101;
//    SimpleNode<int> node2(&element2);
//    int element3 = 102;
//    SimpleNode<int> node3(&element3);
//    int element4 = 104;
//    SimpleNode<int> node4(&element4);
//    int element5 = 105;
//    SimpleNode<int> node5(&element5);
//    SimpleNode<int>* elem;
//    SimpleList<SimpleNode<int>> list;
//    list.push_front(&node1);
//    list.push_front(&node2);
//    list.push_front(&node3);
//    list.push_back(&node1);
//    list.push_back(&node2);
//    list.push_back(&node3);
//    // list.push_back(&node4);
//    // list.push_back(&node5);
//    elem = list.front();
//    while (elem) {
//        cout<<elem->element_<<":"<<*elem->element_<<", ";
//        elem = elem->next_;
//    }
//    cout<<endl;
//    cout<<"hello world";
//    return 0;
//}

#endif

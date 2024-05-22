#include "SLList.h"

template class SLList<int>;

template<typename Object>
SLList<Object>::Node::Node(const Object &d, Node *n)
        : data{d}, next{n} {}

template<typename Object>
SLList<Object>::Node::Node(Object &&d, Node *n)
        : data{std::move(d)}, next{n} {}

template<typename Object>
SLList<Object>::iterator::iterator() : current{nullptr} {}

template<typename Object>
Object &SLList<Object>::iterator::operator*() {
    if(current == nullptr)
        throw std::logic_error("Trying to dereference a null pointer.");
    return current->data;
}

template<typename Object>
typename SLList<Object>::iterator &SLList<Object>::iterator::operator++() {
    if(current->next) // estaba en current lo cual no tiene sentido lmao
        current = current->next;
    else
        throw std::logic_error("Trying to increment past the end.");
    return *this; 
}

template<typename Object>
const typename SLList<Object>::iterator SLList<Object>::iterator::operator++(int) {
    iterator old = *this;
    ++(*this);
    return old;
} 

template<typename Object>
bool SLList<Object>::iterator::operator==(const iterator &rhs) const {
    return current == rhs.current;
}

template<typename Object>
bool SLList<Object>::iterator::operator!=(const iterator &rhs) const {
    return !(this->current == rhs.current); // got rid of the dereference operator
}

template<typename Object>
SLList<Object>::iterator::iterator(Node *p) : current{p} {}

template<typename Object>
SLList<Object>::SLList() : head(new Node()), tail(new Node()), theSize(0) {
    head->next = tail;
}

template<typename Object>
SLList<Object>::SLList(std::initializer_list <Object> init_list) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    theSize = 0;
    for(const auto& x : init_list) {
        push_front(x);
    }
}

template<typename Object>
SLList<Object>::~SLList() {
    clear();
    delete head;
    delete tail;
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::begin() { return {head->next}; }

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::end() { return {tail}; }

template<typename Object>
int SLList<Object>::size() const { return theSize; }

template<typename Object>
bool SLList<Object>::empty() const { return size() == 0; }

template<typename Object>
void SLList<Object>::clear() { while (!empty()) pop_front(); }

template<typename Object>
Object &SLList<Object>::front() {
    if(empty())
        throw std::logic_error("List is empty.");
    return *begin();
}

template<typename Object>
void SLList<Object>::push_front(const Object &x) { insert(begin(), x); }

template<typename Object>
void SLList<Object>::push_front(Object &&x) { insert(begin(), std::move(x)); }

template<typename Object>
void SLList<Object>::pop_front() {
    if(empty())
        throw std::logic_error("List is empty.");
    erase(begin());
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, const Object &x) {
    Node *p = itr.current;
    Node *newNode = new Node{x, p->next};
    p->next = newNode;
    theSize++;
    return iterator(newNode);
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, Object &&x) {
    Node *p = itr.current;
    Node *newNode = new Node{std::move(x), p->next};
    p->next = newNode;
    theSize++;
    return iterator(newNode);
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::erase(iterator itr) {
    if (itr == end())
        throw std::logic_error("Cannot erase at end iterator");
    Node *p = head;
    while (p->next != itr.current) p = p->next;
    Node *toDelete = itr.current;
    p->next = itr.current->next;
    delete toDelete;
    theSize--;
    return iterator(p->next);
}

template<typename Object>
void SLList<Object>::print() {
    iterator itr = begin();
    while (itr != end()) {
        std::cout << *itr << " ";
        ++itr;
    }
    std::cout << std::endl;
}

template<typename Object>
void SLList<Object>::init() {
    theSize = 0;
    head->next = tail;
}

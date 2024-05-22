#ifndef SLLLIST_H
#define SLLLIST_H

#include <iostream>
#include <utility>

template <typename Object> class SLList {
public:
  struct Node {
    Object data;
    Node *next;
    Node(const Object &d = Object{}, Node *n = nullptr);

    Node(Object &&d, Node *n = nullptr);
  };

public:
  class iterator {
  public:
    iterator();

    Object &operator*();

    iterator &operator++();

    const iterator operator++(int);
    // there's an error right here on cpp, it should return const but it doesn't
    // (or shouldn't return const)

    bool operator==(const iterator &rhs) const;

    bool operator!=(const iterator &rhs) const;

  private:
    Node *current;

    iterator(Node *p);

    friend class SLList<Object>;
  };

public:
  SLList();

  SLList(std::initializer_list<Object> init_list);

  ~SLList();

  iterator begin();

  iterator end();

  int size() const;

  bool empty() const;

  void clear();

  Object &front();

  void push_front(const Object &x);

  void push_front(Object &&x);

  void pop_front();

  iterator insert(iterator itr, const Object &x);

  iterator insert(iterator itr, Object &&x);

  iterator erase(iterator itr);

  void print();

private:
  Node *head;
  Node *tail;
  int theSize;

  void init();
};

#endif

/*****************************************************************************
  Filename: slist.h
  Purpose: Header file for Singly Linked List (implemented with c++)
  Data Structure: Singly Linked List (implemented with c++)
  Version: 1
*****************************************************************************/
#ifndef __SLIST_H_CPP__
#define __SLIST_H_CPP__

#include <iostream> /* cout */

namespace ilrd
{

class SLinkedList
{
public:
    //Ctor
    explicit SLinkedList();

    //Dtor
    ~SLinkedList();

    //Push new element to the front on the list
    void PushFront(void *data);

    //Remove element from the front of the list
    void PopFront();

    //Return the number of elements in the list
    size_t GetSize() const;

    //Return True if list dosent contain any elements false otherwise
    bool IsEmpty()   const;

    //Retrive data from the front of the list, or NULL when list is empty
    void* Peek()     const;

private:
    //to disable default assigment operator
    SLinkedList& operator= (const SLinkedList& other_);

    //to disable default ctor
    SLinkedList(const SLinkedList& other_);

    struct node_t;

    // start node (Stub)
    node_t *m_node;

};// SLinkedList
}//namespace ilrd


#endif /* __SLIST_H_CPP__ */

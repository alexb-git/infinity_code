/****************************************************************************
** Filename:    - slinkedl.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementations of Singly Linked List (implemented with c++)
** Date:        - 5/1/2018
** Version:     - 1
*****************************************************************************/
#include <iostream> /* cout */

#include "slist.h"    /* my_header */

using namespace ilrd;


/****************************************************************************
    node_t struct definition
*****************************************************************************/
struct SLinkedList::node_t
{
    explicit node_t(void* data_, node_t* node_)
    : m_data(data_), m_next(node_) {}

    void    *m_data;    /* pointer to data to store */
    node_t  *m_next;    /* pointer to the next node */
};

/****************************************************************************
    Ctor
*****************************************************************************/
SLinkedList::SLinkedList() : m_node(new node_t(NULL, NULL)) {}

/****************************************************************************
    Dtor
*****************************************************************************/
SLinkedList::~SLinkedList()
{
    /* pop till empty */
    while ( !IsEmpty( ) )
    {
        PopFront();
    }

    /* deallocate stub node */
    delete m_node;
    m_node = NULL;
}

/****************************************************************************
    Push new element to the front on the list
*****************************************************************************/
void SLinkedList::PushFront(void *data)
{
    /*  create new node and assign the given data to it,
        newly created node points to previous 1st node */
    node_t *node = new node_t(data, m_node->m_next);

    /* stub node point to newly created node */
    m_node->m_next = node;
}

/****************************************************************************
    Remove element from the front of the list
*****************************************************************************/
void SLinkedList::PopFront()
{
    /* if list is empty do nothing */
    if ( !IsEmpty() )
    {
        /* temporarily keep pointer to 2nd node */
        node_t *temp = m_node->m_next->m_next;

        /* deallocate to 1st node */
        delete m_node->m_next;

        /* stub node point to previous 2nd node */
        m_node->m_next = temp;
    }
}

/****************************************************************************
    Retrive data from the front of the list, or NULL when list is empty
*****************************************************************************/
void* SLinkedList::Peek() const
{
    if ( IsEmpty() )
    {
        return NULL;
    }
    else
    {
        return m_node->m_next->m_data;
    }
}

/****************************************************************************
    Return the number of elements in the list
*****************************************************************************/
size_t SLinkedList::GetSize() const
{
    size_t  num_of_nodes = 0;
    node_t *next_node    = m_node->m_next;

    while ( next_node ) /* != NULL */
    {
        ++num_of_nodes;
          next_node = next_node->m_next;
    }

    return num_of_nodes;
}

/****************************************************************************
    Return True if list dosent contain any elements false otherwise
*****************************************************************************/
bool SLinkedList::IsEmpty() const
{
    return (NULL == m_node->m_next);
}

/****************************************************************************
    Print the entire list, from first node till last
*****************************************************************************/
// template <typename T>
// void SLinkedList::PrintList(T t) const
// {
//     node_t *curr_node = m_node->m_next;
//
//     std::cout << std::endl;
//     while ( curr_node ) /* != NULL */
//     {
//         std::cout << "|"
//         << reinterpret_cast<T> (curr_node->m_data)
//         << "| -> ";
//         curr_node = curr_node->m_next;
//     }
//
//     std::cout << "|NULL|"<< std::endl;
// }

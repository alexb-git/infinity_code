/**********************************************
  Filename: hasht.h
  Purpose:  Header file for hash table
  Version:  4
***********************************************/
#ifndef __HASHT_H__
#define __HASHT_H__

#include <stddef.h> /* size_t */

typedef struct hash hash_t;

/*****************************************************************************
** description:  hash function which maps "key" to index in array
** arguments:    key - pointer to key to map
** return value: match index in array
******************************************************************************/
typedef size_t (*hash_func_t)(const void *key);

/*****************************************************************************
** description:  compares two keys.
** arguments:    key_1, key_2 - compare between key_1 and key_2
** return value: 1 - keys are equal.
**               0 - keys are NOT equal.
** notes:        function provided by the user.
******************************************************************************/
typedef int (*cmp_func_t)(const void *key_1, const void *key_2);

/*****************************************************************************
**  description:  fetch a key from element
**  arguments:    element - element address.
**  return value: key of specified element
**  notes:        function provided by the user.
******************************************************************************/
typedef void* (*key_func_t)(const void* element);

/*****************************************************************************
**  description:  invokes function on element.
**  arguments:    param   - for the use of bool function,
**                element - the elemnet to invoke the bool function on.
**  return value: true or false / or an integer number.
**  notes:        function provided by the user.
******************************************************************************/
typedef int (*bool_function_t)(void* element, void *param);

/*****************************************************************************
**  description:  fetch a key from element
**  arguments:    hash - Hash Table handler.
**                element - element address.
**  return value: key of specified element
**  notes:
******************************************************************************/
void* HashGetKey(hash_t *hash, const void* element);

/*****************************************************************************
** description:  create a new Hash Table handler
** arguments:    table_size - The Hash Table size.
**               hash_func  - user's hash function, maps key
**                            to index of "hash table"
**               func       - user's function to compare two keys.
**               get_key    - user's function that retrives key from an element
** return value: pointer to hash handler
** notes:        must call HashDestroy at end of use.
******************************************************************************/
hash_t* HashCreate( size_t      table_size,
                    hash_func_t hash_func ,
                    cmp_func_t  func      ,
                    key_func_t  get_key   );

/*****************************************************************************
** description:  free the Hash Table.
** arguments:    hash - Hash Table handler.
** return value: void.
** notes:        must be called at end of use.
******************************************************************************/
void HashDestroy(hash_t *hash);

/*****************************************************************************
** description:  Insert new element to the Hash Table
** arguments:    hash - Hash Table handler.
**               element      - pointer to the element to insert
** return value: 1 - success, 0 - fail
** notes:
******************************************************************************/
int HashInsert(hash_t *hash, const void* element);

/*****************************************************************************
** description:  remove element from a hash table.
** arguments:    hash - Hash Table handler.
**               key          - key of the data to remove.
** return value: void
** notes:
******************************************************************************/
void HashRemove(hash_t *hash,const void *key);

/*****************************************************************************
** description:  find 'key' in the Hash Table.
** arguments:    hash - Hash Table handler
**               key  - key of the data to search for.
** return value: returns the element that corresponds to the key,
**               OR NULL if no element was found
** notes:
******************************************************************************/
void* HashFind(hash_t *hash, const void *key);

/*****************************************************************************
** description:  check if hash table is empty
** arguments:    hash -  handler to hash table.
** return value: 1 - empty, 0 - else.
** notes:
******************************************************************************/
int HashIsEmpty(const hash_t *hash);

/*****************************************************************************
** description:  counts number of elements (nodes) in the hash Table.
** arguments:    hash - pointer to hash table.
** return value: number of elements in hash table.
** notes:
******************************************************************************/
size_t HashSize(const hash_t *hash);

/******************************************************************************
** description:  iterate over all elements untill bool function fails
** arguments:    b_func - user define function.
**               param  - additional parameter for the function
** return value: the first key that failed the bool function,
**               or null if all elements succeed
** notes:
******************************************************************************/
void* HashForEach(hash_t *hash          ,
                  bool_function_t b_func,
                  void *param           );

#endif /* __HASHT_H__ */

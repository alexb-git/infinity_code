 /****************************************************************************
** Filename:    - hasht.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Hash table implementation (based on DLL)
** Date:        - 22/11/2017
** Version:     - 1
*****************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memset */

#include "dlist.h"    /* Doubly Linked List */
#include "hasht.h"    /* Hash Table */
/****************************************************************************
    Macros for this program
*****************************************************************************/
#define ADDRESS_SIZE (sizeof(void*))

/****************************************************************************
    Structs for this program
*****************************************************************************/
/* typedef struct hash hash_t */
struct hash
{

  key_func_t  key_func;  /* retrieve key from element */
  cmp_func_t  cmp_func;  /* compares two keys, 1 - keys are equal */
  hash_func_t hash_func; /* translates key into array index */

  size_t      size;      /* size of table */
  dlist_t    *array[1];  /* hash array pointer */
};

/*****************************************************************************
**  description:  fetch a key from element
**  arguments:    handler - Hash Table handler.
**                element - element address.
**  return value: key of specified element
**  notes:
******************************************************************************/
void* HashGetKey(hash_t *handler, const void* element)
{
    return handler->key_func(element);
}

/*****************************************************************************
** description:  Init Hash table with (Doubly) linked lists.
** arguments:    handler - Hash Table handler.
**               table_size - The Hash Table size.
** return value: 1 - allocations succeeded, 0 - allocation failed
** notes:        boolean function
******************************************************************************/
static int HashInitTable(hash_t *handler, size_t table_size)
{
    size_t i = 0;
    for ( ; i < table_size ; ++i )
    {
        handler->array[i] = DlistCreate();

        /* case: allocation was NOT successful */
        if ( NULL == handler->array[i] )
        {
            /* free previously allocated lists */
            while ( i-- )
            {
                DlistDestroy(handler->array[i]);
            }
            return 0; /* allocation failed */
        }
    }
    return 1; /* allocations succeeded */
}

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
                            key_func_t  get_key   )
{
    hash_t *handler = NULL;

    assert( (hash_func != NULL) && (func != NULL) && (get_key != NULL) );

    handler = (hash_t*) malloc(sizeof(hash_t) + (table_size-1) * ADDRESS_SIZE);
    if ( NULL != handler )
    {
        if ( HashInitTable(handler, table_size) != 0 )
        {
            /* case: allocation of lists was successful */
            handler->cmp_func  = func;
            handler->hash_func = hash_func;
            handler->key_func  = get_key;
            handler->size      = table_size;

            return handler;
        }
    }

    /* case: allocation of hash table failed */
    memset(handler, 0, sizeof(hash_t));
    free(handler);
    handler = NULL;

    return NULL;
}

/*****************************************************************************
** description:  free the Hash Table.
** arguments:    handler - Hash Table handler.
** return value: void.
** notes:        must be called at end of use.
******************************************************************************/
void HashDestroy(hash_t *handler)
{
    dlist_t **dlist = NULL;
    dlist_t **last_list = NULL;

    assert( handler != NULL );

    dlist     = handler->array;
    last_list = dlist + handler->size;

    /* destroy the hash lists */
    for ( ; dlist != last_list ; ++dlist )
    {
        DlistDestroy(*dlist);
        *dlist = NULL;
    }

    /* free the handler */
    memset(handler, 0, sizeof(hash_t));
    free(handler);
    handler = NULL;
}

/*****************************************************************************
** description:  Insert new element to the Hash Table
** arguments:    handler - Hash Table handler.
**               element      - pointer to the element to insert
** return value: 1 - success, 0 - fail
** notes:
******************************************************************************/
int HashInsert(hash_t *handler, const void* element)
{
    size_t index = 0;
    void  *key = NULL;
    itr_t  push_address = NULL;

    assert( (handler != NULL) && (element != NULL) );

    /* find in which list the data (with given key) is stroted */
    key   = handler->key_func(element);
    index = handler->hash_func(key);

    /* insert element to list, save the return value in case push failed */
    push_address = DlistPushBack(handler->array[index], element);
    if ( NULL == push_address )
    {
        /* case: push was not successful */
        return 0;
    }

    return 1;
}

/****************************************************************************
    in order for the dlist compare function to work properly,
    functions interfaces between Hash-KeyCompare-Function and
    dlist compare function must be made. This struct enables that bridge.
*****************************************************************************/
typedef struct for_dlis_find
{
    const void *key;
    key_func_t  key_func;  /* retrieve key from element */
    cmp_func_t  cmp_func;  /* compares two keys, 1 - keys are equal */

} for_dlis_find_t;

/****************************************************************************
    interface function between
    Hash-KeyCompare-Function  and  dlist compare function
*****************************************************************************/
static int CustomizedCmp (const void *data_1, const void *data_2)
{
    for_dlis_find_t *for_dlis_find = (for_dlis_find_t*)data_2;

    /*  in Hash-KeyCompare if keys are equal returns - 1, otherwise returns - 0,
        in   dlist   if   elements are equal returns - 0, otherwise returns - 1,
        (KeysAreEqual ^ 1) => (1 ^ 1) => (0) => elements are equal for dlist */
    return for_dlis_find->cmp_func( for_dlis_find->key_func(data_1) ,
                                    for_dlis_find->key              ) ^ 1;
}

/****************************************************************************
** description:  finds in which node (DLL node) the key is stored
** arguments:    handler - Hash Table handler
**               key          - key of the data to remove.
** return value: itrator to that node that holds the key,
**               OR  NULL if element with corresponding key was not found
** notes:        static function. used in HashRemove and HashFind
*****************************************************************************/
static itr_t FindItr(hash_t *handler, const void *key)
{
    size_t   index  = 0;
    itr_t    itr    = NULL;
    dlist_t *dlist  = NULL;
    for_dlis_find_t for_dlis_find;

    assert( (handler != NULL) && (key != NULL) );

    /* find in which list the data (with given key) is stroted */
    index = handler->hash_func(key);
    dlist = handler->array[index];

    /* init for_dlis_find struct */
    for_dlis_find.key      = key;
    for_dlis_find.cmp_func = handler->cmp_func;
    for_dlis_find.key_func = handler->key_func;

    /* find in which node the data (with given key) is stroted */
    itr = DlistFind( DlistBegin(dlist) ,
                     DlistEnd(dlist)   ,
                     CustomizedCmp     ,
                     &for_dlis_find    );

    return itr;
}

/*****************************************************************************
** description:  remove element from a hash table.
** arguments:    handler - Hash Table handler
**               key          - key of the data to remove.
** return value: void
** notes:
******************************************************************************/
void HashRemove(hash_t *handler, const void *key)
{
    itr_t itr   = NULL;

    assert( (handler != NULL) && (key != NULL) );

    /* find in which node the data (with given key) is stroted */
    itr = FindItr(handler, key);

    if ( NULL != itr )
    {
        /* find in which list the data (with given key) is stroted */
        size_t   index = handler->hash_func(key);
        dlist_t *dlist = handler->array[index];

        /* case: node exists, erase data (with given key) from hash table */
        DlistErase(dlist, itr);
    }
}

/*****************************************************************************
** description:  find 'key' in the Hash Table.
** arguments:    handler - Hash Table handler
**               key  - key of the data to search for.
** return value: returns the element that corresponds to the key,
**               OR NULL if no element was found
** notes:
******************************************************************************/
void* HashFind(hash_t *handler, const void *key)
{
    itr_t itr  = NULL;

    assert( (handler != NULL) && (key != NULL) );

    /* find in which node the data (with given key) is stroted */
    itr = FindItr(handler, key);

    if ( itr ) /* != NULL */
    {
        /* case: data was found */
        return DlistGetData(itr);
    }

    return NULL; /* data with given key was not found */
}

/*****************************************************************************
** description:  check if hash table is empty
** arguments:    handler -  handler to hash table.
** return value: 1 - empty, 0 - else.
** notes:
******************************************************************************/
int HashIsEmpty(const hash_t *handler)
{
    dlist_t **dlist = NULL;
    dlist_t **last_list = NULL;

    assert( handler != NULL );

    dlist     = (dlist_t**)handler->array;
    last_list = dlist + handler->size;

    /* destroy the hash lists */
    for ( ; dlist != last_list ; ++dlist )
    {
        if ( !DlistIsEmpty(*dlist) ) /* ==1 */
        {
            return 0;
        }
    }

    return 1; /* Hash is empty */
}

/*****************************************************************************
** description:  counts number of elements (nodes) in the hash Table.
** arguments:    handler - pointer to hash table.
** return value: number of elements in hash table.
** notes:
******************************************************************************/
size_t HashSize(const hash_t *handler)
{
    size_t size = 0;

    dlist_t **dlist     = NULL;
    dlist_t **last_list = NULL;

    assert( handler != NULL );

    dlist     = (dlist_t**)handler->array;
    last_list = dlist + handler->size;

    /* iterate over the lists and sum their sizes */
    while ( dlist != last_list )
    {
        size += DlistCount(*dlist);
        ++dlist;
    }

    return size; /* sumed up lists sizes */
}

/******************************************************************************
** description:  iterate over all elements untill bool function fails
** arguments:    b_func - user define function.
**               param  - additional parameter for the function
** return value: the first key that failed the bool function,
**               or null if all elements succeed
** notes:
******************************************************************************/
void* HashForEach(hash_t *handler,
                  bool_function_t b_func,
                  void *param )
{
    itr_t  itr = NULL;

    dlist_t **dlist     = NULL;
    dlist_t **last_list = NULL;

    assert( (handler != NULL) && (b_func != NULL) );

    dlist     = handler->array;
    last_list = dlist + handler->size;

    /*  iterate over every list in hash table,
        if one of the lists' ForEach call failed - break */
    for ( ; dlist != last_list ; ++dlist )
    {
        /* apply DlistForEach function on current list */
        itr = DlistForEach( DlistBegin(*dlist),
                            DlistEnd(*dlist)  ,
                            b_func, param    );

        /* case: one of the lists' node failed the bolean function */
        if (itr) /* != NULL */
        {
            return DlistGetData(itr);
        }
    }

    return itr;
}

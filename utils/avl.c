/****************************************************************************
** Filename:    - avl.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - AVL tree implementation
** Date:        - 20/11/2017
** Version:     - 3
*****************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memset */

#include "avl.h"    /* AVL tree */
/****************************************************************************
    Macros for this program
*****************************************************************************/
#define LEFT  (0)
#define RIGHT (1)

#define Right(X) (X->children[RIGHT])
#define Left(X)  (X->children[LEFT])
#define Root(X)  (avl_handler->root)

#define Max(A,B)          ( (A > B) ? (A) : (B) )
#define CheckAlloc(X)     if(NULL==X){return 0;}

/****************************************************************************
    Structs for this program
*****************************************************************************/
/*   typedef struct avl_handler avl_handler_t;  */
struct avl_handler
{
  avl_node_t *root;          /* the first node, root node */
  cmp_func_t  cmp_function;  /* compare function given by the user */
};

/*   typedef struct avl_node avl_node_t;   */
struct avl_node
{
  void        *data;         /* pointer to the data that the node holds */
  avl_node_t  *children[2];  /* left child (0), ritgh child (1) */
  int          height;       /* height of the current node,
                                assumption: height of leaf is 1 */
};

/*============================  Static functions  ============================*/
static int   HeightDiff(avl_node_t *node);
static void  UpdateHeight(avl_node_t *node);
static void* AVLFindRec(avl_node_t *node, const void *key, cmp_func_t cmp_func);
static avl_node_t* Balance(   avl_node_t *node);
static avl_node_t* RemoveNode(avl_node_t *node);
static avl_node_t* RotateTree(avl_node_t *root, int direction);
static avl_node_t* RemoveMin( avl_node_t *node, avl_node_t *parent);
static avl_node_t* RemoveRec( avl_node_t *node, void *key, cmp_func_t cmp_func);

static avl_node_t* InsertRec( avl_node_t *node     ,
                              avl_node_t *new_node ,
                              cmp_func_t  cmp_func );

static void* AVLForEachRec( avl_node_t      *node  ,
                            bool_function_t  b_func,
                            void            *param );

/****************************************************************************
    rotates the sub tree according to direction.
    returns the new sub tree root
*****************************************************************************/
static avl_node_t* RotateTree(avl_node_t *root, int direction)
{
    /* make 'new_root' child of 'root' */
    avl_node_t *new_root = root->children[direction^1];

    /* sub-tree of 'root' holds sub-tree of 'new_root' */
    root->children[direction^1] = new_root->children[direction];

    /* 'new_root' child hold previous 'root' */
    new_root->children[direction] = root;

    UpdateHeight(root);

    return new_root;
}

/****************************************************************************
    returns the height difference between left sub-tree and right sub-tree
*****************************************************************************/
static int HeightDiff(avl_node_t *node)
{
    int  left_height = 0;
    int right_height = 0;

    if ( NULL != node )
    {
        if ( NULL != Left(node) )
        {
            left_height = Left(node)->height;
        }

        if ( NULL != Right(node) )
        {
            right_height = Right(node)->height;
        }
    }

    return left_height - right_height;
}

/****************************************************************************
    identifies the case of the given sub-tree
    ( left-right -OR- left-left -OR- right-left -OR- right-right )
    and performs sub-tree rotations accordingly
*****************************************************************************/
static avl_node_t* Balance(avl_node_t *node)
{
    int diff      = HeightDiff(node);
    int direction = (diff < 0)?(RIGHT):(LEFT);

    if ( diff > 1 || diff < -1)
    {
        if ( HeightDiff(node->children[direction]) * diff < 0 )
        {
            /* case: left-right -OR- right-left */
            node->children[direction] =
                        RotateTree(node->children[direction], direction);
        }

        /* case: left-left -OR- right-right */
        return RotateTree(node, 1^direction);
    }

    return node;
}

/****************************************************************************
** description:  updades the height of the given node
** arguments:    node - avl_node
** return value: void
** notes:        max of height between two children + 1
*****************************************************************************/
static void UpdateHeight(avl_node_t *node)
{
    int  left_height = 0;
    int right_height = 0;

    if ( NULL == node )
    {
        return;
    }

    if ( NULL != Left(node) )
    {
        left_height = Left(node)->height;
    }

    if ( NULL != Right(node) )
    {
        right_height = Right(node)->height;
    }

    node->height = 1 + Max(left_height, right_height);
}

/****************************************************************************
** description:  allocates memory to the new node
**               and initializes data and height fields
** arguments:    left  - left child address
**               right - right child address
**               data  - pointer to the element to insert
**               height - height of the node (when created height is 1)
** return value: address of the newly allocated node
** notes:
*****************************************************************************/
static avl_node_t* CreateNode( avl_node_t *left, avl_node_t *right,
                               void* data, int height )
{
    avl_node_t *new_node = (avl_node_t*)malloc(sizeof(avl_node_t));
    if (NULL != new_node)
    {
        memset(new_node, 0, sizeof(avl_node_t));
        new_node->data   = data;
        new_node->height = height;
    }

    return new_node;
}

/*****************************************************************************
** description:  create a new AVL Tree handler.
** arguments:    func - defines the tree sorting order.
** return value: pointer to AVL Tree handler.
** notes:        must call AVLDestroy at end of use.
******************************************************************************/
avl_handler_t* AVLCreate(cmp_func_t func)
{
    avl_handler_t *handler = NULL;

    assert( func != NULL );

    handler = (avl_handler_t*)malloc(sizeof(avl_handler_t));
    CheckAlloc(handler);

    /* init handler */
    handler->cmp_function = func;
    handler->root = NULL;

    return handler;
}

/****************************************************************************
    recursively remove all the nodes from the tree
*****************************************************************************/
void AVLDestroyRec(avl_node_t *node)
{
    /* base case: found end of branch */
    if ( NULL == node )
    {
        return;
    }

    AVLDestroyRec(Right(node));
    AVLDestroyRec(Left (node));

    free(node);
    node = NULL;
}

/*****************************************************************************
** description:  free the AVL Tree.
** arguments:    avl_handler - AVL Tree handler
** return value: void.
** notes:        must call at end of use.
**               recursive function, post order
******************************************************************************/
void AVLDestroy(avl_handler_t *avl_handler)
{
    /* remove all the nodes from the tree */
    AVLDestroyRec(Root(avl_handler));

    /* free the handler */
    free(avl_handler);
    avl_handler = NULL;

}

/****************************************************************************
    Recursive insertion. Finds place to insert the bed node
*****************************************************************************/
static avl_node_t* InsertRec( avl_node_t *node     ,
                              avl_node_t *new_node ,
                              cmp_func_t  cmp_func )
{
    if ( node == NULL )
    {
        return new_node;
    }
    else /* node is not child of leaf */
    {
        int direction = (cmp_func(new_node->data, node->data) > 0);

        node->children[direction] = InsertRec( node->children[direction],
                                               new_node                 ,
                                               cmp_func                 );

        /* balance and update height of the parent node */
        node = Balance(node);
        UpdateHeight(node);

        return node;
    }
}

/*****************************************************************************
** description:  Insert a new element to the AVL Tree
** arguments:    avl_handler - AVL Tree handler
**               element     - pointer to the element to insert
** return value: 1 - success,
**               0 - fail
** notes:        recursive function
******************************************************************************/
int AVLInsert(avl_handler_t *avl_handler, void* element)
{
    avl_node_t *new_node = NULL;

    assert( avl_handler != NULL );

    new_node = CreateNode(NULL, NULL, element, 1);
    CheckAlloc(new_node);

    Root(avl_handler) = InsertRec( Root(avl_handler)        ,
                                   new_node                 ,
                                   avl_handler->cmp_function);
    return 1;
}

/*****************************************************************************
** description:  check if AVL Tree is empty.
** arguments:    avl_handler - AVL Tree handler.
** return value: 1 - empty,
**               0 - else.
** notes:
******************************************************************************/
int AVLIsEmpty(const avl_handler_t *avl_handler)
{
    assert( avl_handler != NULL );

    return Root(avl_handler) == NULL;
}

/****************************************************************************/
size_t AVLSizeRec(avl_node_t *node)
{
    /* base case: child of leaf node */
    if ( NULL == node )
    {
        return 0;
    }

    /* calculate total tree size, from current node downwards */
    return 1 + AVLSizeRec(Left(node)) + AVLSizeRec(Right(node));
}

/*****************************************************************************
** description:  counts number of elements (nodes) in The AVL Tree.
** arguments:    avl_handler - AVL Tree handler.
** return value: number of elements in AVL Tree.
** notes:        recursive function
******************************************************************************/
size_t AVLSize(const avl_handler_t *avl_handler)
{
    assert( avl_handler != NULL );

    return AVLSizeRec(Root(avl_handler));
}

/*****************************************************************************
** description:  returns the height of the AVL tree.
** arguments:    avl_handler - AVL Tree handler.
** return value: height of the AVL Tree.
** notes:        recursive function
******************************************************************************/
size_t AVLHeight(const avl_handler_t *avl_handler)
{
    assert( avl_handler != NULL );

    if ( AVLIsEmpty(avl_handler) )
    {
        return 0;
    }
    else
    {
        return avl_handler->root->height;
    }
}

/****************************************************************************
** description:  1. find the node that holds the smallest data in right sub-tree
**               2. remove the node from the tree, update the tree accordingly
** arguments:    node - current node
**               node2remove - node we want to remove from the tree
** return value: right child of the node that will
**               be transplanted to node2remove
** notes:        recursive function
*****************************************************************************/
static avl_node_t* RemoveMin(avl_node_t *node, avl_node_t *node2remove)
{
    avl_node_t *return_node = node;

    if ( Left(node) != NULL )
    {
        Left(node) = RemoveMin(Left(node), node2remove);
    }
    else
    {
        node2remove->data = node->data;
        return_node = Right(node);

        free(node);
        node = NULL;
    }

    /* balance and update height of the node */
    return_node = Balance(return_node);
    UpdateHeight(return_node);

    return return_node;
}

/****************************************************************************
** description:  in case: A. node has one child or less - deallocs the node
**                        B. node has two childre - calls RemoveMin methode
** arguments:    node - address of the node to remove
** return value: root of the tree
** notes:        recursive function
*****************************************************************************/
static avl_node_t* RemoveNode(avl_node_t *node)
{
    if ( (size_t)Left(node) * (size_t)Right(node) == 0 )
    {
        /* case: one child or less */
        avl_node_t *next_node =
                        (avl_node_t*)((size_t)Left(node) ^ (size_t)Right(node));

        free(node);
        node = NULL;

        return next_node;
    }

    else /* case: node to remove has two children */
    {
        Right(node) = RemoveMin(Right(node), node);
        return node;
    }
}

/****************************************************************************
** description:  finds the node to remove and calls RemoveNode methode
** arguments:    node - curent node
**               key  - node to remove
**               cmp_func - user given functions
** return value: root of the tree
** notes:        recursive function
*****************************************************************************/
static avl_node_t* RemoveRec(avl_node_t *node, void *key, cmp_func_t cmp_func)
{
    avl_node_t *root_node = node;

    assert( (key != NULL) && (cmp_func != NULL) );

    if ( node != NULL ) /* base case: node is child of leaf */
    {
        if ( cmp_func(key, node->data) == 0 )
        {
            /* node to remove found */
            root_node = RemoveNode(node);
        }
        else
        {
            /* iterate according to the direction of the tree */
            int direction = (cmp_func(key, node->data) > 0);

            node->children[direction] = RemoveRec( node->children[direction],
                                                   key                      ,
                                                   cmp_func                 );
        }
    }

    /* balance and update height of the node */
    root_node = Balance(root_node);
    UpdateHeight(root_node);

    return root_node;
}

/*****************************************************************************
** description:  removes an element from an AVL Tree
** arguments:    avl_handler - pointer to a AVL Tree handler
**               element     - the element to be removed
** return value: void
** notes:
******************************************************************************/
void AVLRemove(avl_handler_t *avl_handler, void *key)
{
    assert( avl_handler != NULL );

    avl_handler->root = RemoveRec( Root(avl_handler)        ,
                                   key                      ,
                                   avl_handler->cmp_function);
}

/****************************************************************************
** description:  recursively iterate over the tree nodes and
**               invoke user defined function on each node
** arguments:    node   - current node.
**               b_func - user define function.
**               param  - additional parameter for the function
** return value: data of the node which failed the b_func
**               OR NULL if all nodes succeeded.
** notes:        recursive function, in order.
*****************************************************************************/
static void* AVLForEachRec( avl_node_t      *node  ,
                            bool_function_t  b_func,
                            void            *param )
{
    void *sub_tree_res = NULL;

    /* base case 1: node is a child of leaf */
    if ( NULL == node )
    {
        return NULL;
    }

    /* base case 2: b_func failed on node */
    if ( b_func(node->data, param) == 0 )
    {
        return node->data;
    }

    /* run the function on left sub-tree */
    sub_tree_res = AVLForEachRec(Left (node), b_func, param);
    if( sub_tree_res != NULL )
    {
        return sub_tree_res;
    }

    /* run the function on right sub-tree */
    sub_tree_res = AVLForEachRec(Right(node), b_func, param);

    return sub_tree_res;
}

/******************************************************************************
** description:  iterate over all nodes in tree untill bool function fails
** arguments:    avl_handler - AVL tree handler
**               b_func - user define function.
**               param  - additional parameter for the function
** return value: the first key that failed the bool function,
**               or null if all elements succeed
** notes:
******************************************************************************/
void* AVLForEach( avl_handler_t   *avl_handler,
                  bool_function_t  b_func     ,
                  void            *param      )
{
    assert( (avl_handler != NULL) && (b_func != NULL) );

    return AVLForEachRec(avl_handler->root, b_func, param);
}

/****************************************************************************
** description:  description
** arguments:    node - avl_node
**               key - data to find
**               cmp_func - compare function given by the user
** return value: data of the node that holds the key
**               OR NULL if key was not found
** notes:        recursive function
*****************************************************************************/
static void* AVLFindRec(avl_node_t *node, const void *key, cmp_func_t cmp_func)
{
    int direction = 0;

    /* base case 1: node is a child of leaf */
    if ( NULL == node )
    {
        return NULL;
    }

    /* base case 2: cmp_func found a match */
    if ( cmp_func(node->data, key) == 0 )
    {
        return node->data;
    }

    /* iteration step */
    direction = (cmp_func(key, node->data) > 0);
    return AVLFindRec(node->children[direction], key, cmp_func);
}

/*****************************************************************************
** description:  find the first occurrence of 'key' in AVL tree
** arguments:    avl_handler - AVL tree handler
**               key  - pointer to the data to search for.
** return value: returns the element that corresponds to the key.
** notes:        recursive function, in order.
******************************************************************************/
void* AVLFind(avl_handler_t *avl_handler, const void *key)
{
    assert( avl_handler != NULL );

    return AVLFindRec(Root(node), key, avl_handler->cmp_function);
}



/*******************************************************************
  Debug Function for printing the current event state and input
*******************************************************************/
#ifdef _DEBUG

/****************************************************************************
** Filename:    - bst_print.c
** Code Author: - Roma Tarasenko
** Mail:        - romatrsnk@gmail.com
** Purpose:     - printing function for Binary search tree max depth :5
** Date:        - 13/11/17
** Version:     - 1
*****************************************************************************/
#include <stdio.h>    /* printf */
#include <math.h>
#include "queue.h"

static size_t GetDepth(avl_node_t *node );
void print(void *handler);
void printNode(avl_node_t *node, size_t pos,size_t my_depth, size_t t_depth);
void printLine(queue_t *nodes_in_line, size_t depth, size_t t_depth);
int insertNode(queue_t *queue, avl_node_t *node);
static int isDummy(avl_node_t *node);
static avl_node_t *createDummy();

long DUMMY_NODE = 99999999;
#define NODE_SIZE (2)
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define YELLOWS	"\x1b[33m"

#define GREEN	"\x1b[32m"
#define RED		"\x1b[91m"
#define RESET	"\x1b[0m"


#define TRUE  (1)
#define FALSE (0)

static size_t GetDepth(avl_node_t *node )
{
    size_t left_depth  = 0;
    size_t right_depth = 0;

    if(node==NULL)
    {
        return 0;
    }

    left_depth  = GetDepth(node->children[LEFT]);
    right_depth = GetDepth(node->children[RIGHT]);

    return left_depth < right_depth ? ++right_depth : ++left_depth ;
}

void print(void *handler)
{
    avl_node_t* node = ((avl_handler_t*)handler)->root;
    size_t depth     = GetDepth(node);
    queue_t *queue   = QueueCreate();

    /*if(!BSTIsEmpty((bst_handler_t*)handler))
    { */
        printf("\n");
        QueueEnqueue(queue, node);
        printLine(queue, 1,  depth);
    /*}*/
}

void printNode(avl_node_t *node, size_t pos,size_t my_depth, size_t t_depth)
{
  char right_branche[100] = {0};
  char left_branche[100]  = {0};

  size_t total_size  = 0;
  size_t branche     = 0;
  size_t spaces      = 0;
  size_t i           = 0;

  if(my_depth != t_depth)
  {
    total_size = ((double)(pow(2, t_depth-my_depth-1)-0.5))*NODE_SIZE;
    branche = (total_size-NODE_SIZE/2 )/2;
    spaces = total_size - branche;
  }

  for(i=0; i<spaces; ++i)
  {
    right_branche[total_size-i-1]=' ';
    left_branche[i]=' ';
  }

  if(i<total_size)
  {
    right_branche[total_size-i-1]='.';
    left_branche[i++]='.';
  }


  for(; i<total_size; ++i)
  {
    right_branche[total_size-i-1]='-';
    left_branche[i]='-';
  }


    printf("%s",left_branche);

    if(isDummy(node))
    {
      printf("[]");

    }
    else
    {
      printf(KGRN"%2.ld",*(size_t*)node->data);
/*	  printf(YELLOWS"|%.u",node->height);
*/    }

    printf(KWHT"%s",right_branche);
}


	void printLine(queue_t *nodes_in_line, size_t depth, size_t t_depth)
{
  queue_t *next_line_nodes = QueueCreate();
  int is_real_nodes = FALSE;
  int left_c  = FALSE;
  int right_c = FALSE;
  size_t pos = 0;

  while(!QueueIsEmpty(nodes_in_line))
  {
      avl_node_t *node = (avl_node_t *)QueueDequeue(nodes_in_line);
      printNode(node,pos++, depth, t_depth);
      if(isDummy(node))
      {
          QueueEnqueue(next_line_nodes, createDummy());
          QueueEnqueue(next_line_nodes, createDummy());
          free(node);
      }
      else
      {
        left_c  = insertNode(next_line_nodes, node->children[LEFT]);
        right_c = insertNode(next_line_nodes, node->children[RIGHT]);
        is_real_nodes = is_real_nodes || left_c || right_c;
      }

  }

  QueueDestroy(nodes_in_line);
  nodes_in_line = NULL;

  printf("\n");
  if(is_real_nodes)
  {
      printLine(next_line_nodes, ++depth, t_depth);
  }
  else
  {
    while(!QueueIsEmpty(next_line_nodes))
    {
        free(QueueDequeue(next_line_nodes));
    }
    QueueDestroy(next_line_nodes);
    next_line_nodes = NULL;
  }

}


int insertNode(queue_t *queue, avl_node_t *node)
{
  if(node == NULL)
  {
    QueueEnqueue(queue, createDummy());
    return  FALSE;
  }
  else
  {
    QueueEnqueue(queue,node) ;
    return TRUE;
  }
}


static avl_node_t *createDummy()
{
  avl_node_t *dummy = (avl_node_t*)malloc(sizeof(avl_node_t));

  memset(dummy, '0', sizeof(avl_node_t));
  dummy->data = &DUMMY_NODE;

  return dummy;
}

static int isDummy(avl_node_t *node)
{
  return DUMMY_NODE == *(long*)node->data;
}

int IsBalancedRec(avl_node_t *node)
{
    int diff;
    /* base case: child of leaf - return balanced */
    if ( NULL == node )
    {
        return 1;
    }

    diff = HeightDiff(node);
    /* base case 2: node is not balanced */
    if ( diff > 1 || diff < -1 )
    {
        return 0;
    }

    return IsBalancedRec(Left(node)) & IsBalancedRec(Right(node));
}

void IsBalanced(avl_handler_t *avl_handler)
{
    int is_balanced = IsBalancedRec(Root(avl_handler));
    if ( is_balanced )
    {
        printf(GREEN "Tree is balanced" RESET);
    }
    else
    {
        printf(RED "Tree is NOT balanced" RESET);
    }
}

#else
    void print(void *handler){}
    void IsBalanced(void *handler){}
#endif

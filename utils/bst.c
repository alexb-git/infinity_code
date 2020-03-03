/****************************************************************************
** Filename:    - bst.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - Binary Search Tree implementations
** Date:        - 9/11/2017
** Version:     - 1
*****************************************************************************/
#include <stdlib.h>    /* malloca, free */
#include <string.h>    /* memset */
#include <assert.h>    /* assert */

#include "bst.h"        /* Header file for Binary Search Tree */

/****************************************************************************
    useful defines and macros for this program
*****************************************************************************/
#define LEFT  (0)
#define RIGHT (1)

#define Right(X) (X->children[RIGHT])
#define Left(X)  (X->children[LEFT])
#define Root(X)  (X->end.children[LEFT])

#define LeftIsBigger(X,Y) (bst_handler->cmp_function(X,BSTGetData(Y),NULL)>0)
#define CompareResul(X,Y) (bst_handler->cmp_function(X,BSTGetData(Y),NULL))
#define CheckAlloc(X)     if(NULL==X){return 0;}

/****************************************************************************
    structs for this program
*****************************************************************************/
typedef struct bst_node bst_node_t;

struct bst_node
{
	bst_node_t *parent;        /* parent node */
	bst_node_t *children[2];   /* left child (0), ritgh child (1) */
	void       *data;          /* pointer to the data that thr node holds */
};

struct bst_handler
{
	bst_node_t  end;           /* stub node, parent to root */
	cmp_func_t  cmp_function;  /* compare function given by the user */
	void       *param;         /* param given by the user */
};

/*============  FIND MINIMUM VALUE IN TREE  ============*/
static bst_node_t* BSTMin(bst_node_t *node)
{
    assert( node != NULL );

	while ( node->children[LEFT] != NULL )
	{
		node = node->children[LEFT];
	}
	return node;
}

/*============  FIND MAXIMUM VALUE IN TREE  ============*/
static bst_node_t* BSTMax(bst_node_t *node)
{
    assert( node != NULL );

    while ( node->children[RIGHT] != NULL )
	{
		node = node->children[RIGHT];
	}
	return node;
}

/*=====================  Create and init new bst node  =====================*/
static bst_node_t* NodeCreate(bst_node_t *left, bst_node_t *right,
                              bst_node_t *parent, void *element)
{
    bst_node_t *new_node = NULL;

    new_node = (bst_node_t*) malloc ( sizeof(bst_node_t) );
    if ( NULL != new_node )
    {
        new_node->children[LEFT]  = left;
        new_node->children[RIGHT] = right;
        new_node->parent          = parent;
        new_node->data            = element;
    }

    return new_node;
}

/****************************************************************************
** description:  make parent of 'parent_node' point to 'child_node'
**               make parent pointer of 'child_node' point to
**               parent pointer of 'parent_node'
** arguments:    bst_handler - Binary Search Tree handler
** return value: void
** notes:        notes
*****************************************************************************/
static void Transplant(bst_node_t *parent, bst_node_t *child)
{
    assert( parent != NULL );

    if ( parent == Left(parent->parent) )
    {
        Left(parent->parent) = child;
    }
    else    /* parent == Right(parent->parent) */
    {
        Right(parent->parent) = child;
    }

    if ( child != NULL )
    {
        child->parent = parent->parent;
    }
}

/*****************************************************************************
** description:  create a new Binary Search Tree handler.
** arguments:    func - defines the tree sorting order.
** return value: pointer to Binary Search Tree handler.
** notes:        must call BSTDestroy at end of use.
******************************************************************************/
bst_handler_t* BSTCreate(cmp_func_t func, void *func_param)
{
	bst_handler_t* bst_handler = (bst_handler_t*)malloc(sizeof(bst_handler_t));
    CheckAlloc(bst_handler);

    assert( func != NULL );

    memset(bst_handler, 0, sizeof(bst_handler_t));
	bst_handler->cmp_function = func;
	bst_handler->param        = func_param;

	return bst_handler;
}

/*****************************************************************************
** description:  free the Binary Search Tree.
** arguments:    bst_handler - Binary Search Tree handler
** return value: void.
** notes:        must call at end of use.
******************************************************************************/
void BSTDestroy(bst_handler_t *bst_handler)
{
    bst_itr_t itr = NULL;
    bst_itr_t end = NULL;

    assert( bst_handler != NULL );

    itr = BSTBegin(bst_handler);
    end = BSTEnd  (bst_handler);

    while ( itr != end )
    {
        itr = BSTRemove(itr);
    }

	free(bst_handler);
	bst_handler = NULL;
}

/*****************************************************************************
** description:  insert a new element to the Binary Search Tree
** arguments:    bst_handler - Binary Search Tree handler
**               element     - pointer to the element to insert
** return value: 1 - success,
**               0 - fail
******************************************************************************/
int BSTInsert(bst_handler_t *bst_handler, void* element)
{
    bst_node_t *parent_node = (bst_node_t*)BSTEnd(bst_handler);
    bst_node_t *child_node  = NULL;
    bst_node_t *new_node    = NULL;
    size_t      direction   = LEFT;

    assert( bst_handler != NULL );

    /* start with top of the tree */
    child_node = Root(bst_handler);

    /* find where to insert the node/element */
    while ( child_node != NULL )
    {
        parent_node = child_node;

        /*  is the element bigger than child_node (1 - RIGHT)
            or the element is smaller than child_node (0 - LEFT) */
        direction   = LeftIsBigger(element, child_node);

        /* promote the child node according to the direction */
        child_node  = child_node->children[direction];
    }

    /*       NodeCreate( *left, *right,  *parent, *data ) */
    new_node = NodeCreate(NULL, NULL, parent_node, element);
    CheckAlloc(new_node);

    parent_node->children[direction] = new_node;

	return 1;
}

/*****************************************************************************
** description:  get the data pointed by iterator
** arguments:    bst_handler - Binary Search Tree handler
**               itr         - iterator to the node containing the data.
** return value: pointer to the data.
** notes:
******************************************************************************/
void* BSTGetData(bst_itr_t itr)
{
    assert( itr != NULL );

    return ((bst_node_t*)itr)->data;
}

/*****************************************************************************
** description:  check if Binary Search Tree is empty.
** arguments:    bst_handler - Binary Search Tree handler.
** return value: 1 - empty,
**               0 - else.
** notes:
******************************************************************************/
int BSTIsEmpty(const bst_handler_t *bst_handler)
{
    assert( bst_handler != NULL );

    return Root(bst_handler) == NULL;
}

/****************************************************************************
    function that is used in BSTCount with the use of the BSTForEach
*****************************************************************************/
static int BoolCount(void* element, const void *param)
{
    ++*(size_t*)param;
    return 1;
}

/*****************************************************************************
** description:  counts number of elements (nodes) in Binary Search Tree.
** arguments:    bst_handler - Binary Search Tree handler.
** return value: number of elements in Binary Search Tree.
** notes:
******************************************************************************/
size_t BSTCount(const bst_handler_t *bst_handler)
{
    size_t counter = 0;

    assert( bst_handler != NULL );

    BSTForEach(BSTBegin(bst_handler), BSTEnd(bst_handler), BoolCount, &counter);

    return counter;
}

/*****************************************************************************
** description:  returns iterator that points to the element
**               with the lowest key value
** arguments:    bst_handler - pointer to BST handler.
** return value: iterator that points to beginning of the BST
**               in case of empty - Undefined result.
** notes:
******************************************************************************/
bst_itr_t BSTBegin(const bst_handler_t *bst_handler)
{
    assert( bst_handler != NULL );

    return BSTMin((bst_node_t*)&bst_handler->end);
}

/*****************************************************************************
** description:  returns iterator that points to the end of the BST.
** arguments:    bst_handler - pointer to BST handler.
** return value: iterator that points to end of BST
** notes:
******************************************************************************/
bst_itr_t BSTEnd(const bst_handler_t *bst_handler)
{
    assert( bst_handler != NULL );

    return (void*)&bst_handler->end;
}

/*****************************************************************************
** description:  promote the iterator to the next element.
** arguments:    itr - binary search tree iterator.
** return value: iterator to the next element (according to compare function).
** notes:        if itr points to end, the return value is unpredicted
******************************************************************************/
bst_itr_t BSTNext(const bst_itr_t itr)
{
    bst_node_t *node        = (bst_node_t*)itr;
    bst_node_t *node_parent = NULL;

    assert( itr != NULL );

    /* case: previous is in the right sub-tree */
    if ( Right(node) != NULL )
    {
        return BSTMin(Right(node));
    }

    node_parent = node->parent;

    /* while: (1) didn't get to the root node
              (2) go up the tree until encounter a node that
                  is the left child of its parent */
    while ( (node_parent != NULL) && (node == Right(node_parent)) )
    {
        node = node_parent;
        node_parent = node_parent->parent;
    }

    return node_parent;
}

/*****************************************************************************
** description:   returns iterator of the previous element.
** arguments:     itr - binary search tree iterator.
** return value:  iterator to the previous element(according to compare function).
** notes:         if itr points to begin, the return value is unpredicted.
******************************************************************************/
bst_itr_t BSTPrev(const bst_itr_t itr)
{
    bst_node_t *node        = (bst_node_t*)itr;
    bst_node_t *node_parent = NULL;

    assert( itr != NULL );

    /* case: previous is in the left sub-tree */
    if ( Left(node) != NULL )
    {
        return BSTMax(Left(node));
    }

    node_parent = node->parent;

    /* while: (1) didn't get to the root node
              (2) go up the tree until encounter a node that
                  is the right child of its parent */
    while ( (node_parent != NULL) && (node == Left(node_parent)) )
    {
        node = node_parent;
        node_parent = node_parent->parent;
    }

    return node_parent;
}

/*****************************************************************************
** description:  removes the node pointed by itr
** arguments:    itr - binary search tree iterator.
** return value: iterator to the next element(according to compare function).
** notes:        if itr points to end, the return value is unpredicted
******************************************************************************/
bst_itr_t BSTRemove(const bst_itr_t itr)
{
    bst_node_t *node2remove = NULL;
    bst_itr_t   return_node = NULL;

    assert( itr != NULL );

    node2remove = (bst_node_t*)itr;


    if ( (size_t)Left(node2remove) * (size_t)Right(node2remove) == 0 )
    {
        /* case: node has only one child */
        Transplant( node2remove,
                    (bst_node_t*)(  (size_t)Left (node2remove)
                                   ^(size_t)Right(node2remove) ) );
    }

    else /* case: node to remove has two children */
    {
        bst_node_t *smallest = BSTMin(Right(node2remove));

        if ( smallest->parent != node2remove )
        {
            /* case: more than 1 level difference between
                    'node2remove' and 'smallest' node */
            Transplant(smallest, Right(smallest));
            Right(smallest)         = Right(node2remove);
            Right(smallest)->parent = smallest ;
        }

        Transplant(node2remove, smallest);
        Left(smallest)         = Left(node2remove);
        Left(smallest)->parent = smallest;
    }

    return_node = BSTNext(node2remove);

    free(node2remove);
    node2remove = NULL;

    return return_node;
}

/******************************************************************************
** description:  invoke `bool_function` on all data from 'start'
**               till 'end', return iterator to the first data
**               that failed the boolean function, or NULL if all succeeded
** arguments:    from - start iterator.
**               to   - end iterator.
**               b_func  - pointer to users' function.
**               param   - additional parameter for the function
** return value: pointer to the first node that failed the boolean
**               function, or itr to end  if all nodes succeeded.
******************************************************************************/
bst_itr_t BSTForEach(bst_itr_t from, bst_itr_t to,
                     bool_function_t b_func, void *param)
{
    assert( (from != NULL) && (to != NULL) && (b_func != NULL) );

    for (  ; from != to ; from = BSTNext(from) )
    {
        if ( !b_func(BSTGetData(from), param) )
        {
            return from;
        }
    }

    return NULL;
}

/*****************************************************************************
** description:  find the first occurrence of 'data' in binary search tree
**               pointed by bst_handler.
** arguments:    bst_handler - pointer to BST handler
**               data  - pointer to the data to search for.
** return value: returns iterator that points to the data,
**               or end if data was not found.
** notes:
******************************************************************************/
bst_itr_t BSTFind(bst_handler_t *bst_handler, const void *data)
{
    bst_node_t *node = NULL;
    size_t      direction = LEFT;

    assert( bst_handler != NULL );

    node = Root(bst_handler);

    /* while (1) not lowest node
             (2) node with the required key not found */
    while (    node != NULL
            && (direction = CompareResul(data, node)) )
    {
        node = node->children[(direction)?(RIGHT):(LEFT)];
    }

    return (node) ? (node) : (BSTEnd(bst_handler));
}



/*******************************************************************
  Debug Function for printing the current event state and input
*******************************************************************/
#ifdef _DEBUG
	#include <stdio.h>    /* printf */
	#include "queue.h"
	#include <math.h>

	size_t GetDepth(bst_node_t *node, size_t depth );
	void print(const bst_handler_t *handler);
	void printNode(bst_node_t *node, size_t pos,size_t my_depth, size_t t_depth);
	void printLine(queue_t *nodes_in_line, size_t depth, size_t t_depth);
	int insertNode(queue_t *queue, bst_node_t *node);
	int isDummy(bst_node_t *node);
	bst_node_t *createDummy();

	long DUMMY_NODE = 99999999;
	#define NODE_SIZE (2)
	#define KGRN  "\x1B[32m"
	#define KWHT  "\x1B[37m"
	#define TRUE  (1)
	#define FALSE (0)

	size_t GetDepth(bst_node_t *node, size_t depth )
	{
	    size_t left_depth  = 0;
	    size_t right_depth = 0;

	    if(node!=NULL)
	    {
	        left_depth  = GetDepth(node->children[0],depth+1);
	        right_depth = GetDepth(node->children[1],depth+1);

	        return left_depth < right_depth ? right_depth : left_depth ;
	    }
	    else
	    {
	      return depth;
	    }

	}

	void print(const bst_handler_t *handler)
	{
	    bst_node_t *node = handler->end.children[0];
	    size_t depth     = GetDepth(node, 0);
	    queue_t *queue   = QueueCreate();

	    if(!BSTIsEmpty(handler))
	    {
	        QueueEnqueue(queue, node);
	        printLine(queue, 1,  depth);
	    }
	}

	void printNode(bst_node_t *node, size_t pos,size_t my_depth, size_t t_depth)
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
            if ( *(size_t*)node->data == 0 )
            {
                printf(KGRN"0 ");
            }
            else
            {
                printf(KGRN"%2.ld",*(size_t*)node->data);
            }

	    }

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
	      bst_node_t *node = (bst_node_t *)QueueDequeue(nodes_in_line);
	      printNode(node,pos++, depth, t_depth);
	      if(isDummy(node))
	      {
	          QueueEnqueue(next_line_nodes, createDummy());
	          QueueEnqueue(next_line_nodes, createDummy());
	          free(node);
	      }
	      else
	      {
	        left_c  = insertNode(next_line_nodes, node->children[0]);
	        right_c = insertNode(next_line_nodes, node->children[1]);
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


	int insertNode(queue_t *queue, bst_node_t *node)
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


	bst_node_t *createDummy()
	{
	  bst_node_t *dummy = (bst_node_t*)malloc(sizeof(bst_node_t));

	  memset(dummy, '0', sizeof(bst_node_t));
	  dummy->data = &DUMMY_NODE;

	  return dummy;
	}

	int isDummy(bst_node_t *node)
	{
	  return DUMMY_NODE == *(long*)node->data;
	}
#else
	#include <stdio.h>    /* printf */
	#include "queue.h"
	#include <math.h>

	void printNode(bst_node_t *node, size_t pos,size_t my_depth, size_t t_depth);
	void printLine(queue_t *nodes_in_line, size_t depth, size_t t_depth);
	void print(const bst_handler_t *handler);
	size_t GetDepth(bst_node_t *node, size_t depth );
	int insertNode(queue_t *queue, bst_node_t *node);
	int isDummy(bst_node_t *node);
	bst_node_t *createDummy();

	size_t GetDepth(bst_node_t *node, size_t depth )
	{
		return 0;
	}
	void print(const bst_handler_t *handler)
	{
		;
	}
	void printNode(bst_node_t *node, size_t pos,size_t my_depth, size_t t_depth)
	{
		;
	}
	void printLine(queue_t *nodes_in_line, size_t depth, size_t t_depth)
	{
		;
	}
	int insertNode(queue_t *queue, bst_node_t *node)
	{
		return 0;
	}
	bst_node_t *createDummy()
	{
		return NULL;
	}
	int isDummy(bst_node_t *node)
	{
		return 0;
	}
#endif

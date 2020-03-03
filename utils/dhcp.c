/****************************************************************************
** Filename:    - dhcp.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - DHCP implementation (based on tries data structure)
** Date:        - 4/12/2017
** Version:     - 30
*****************************************************************************/
#include <stdlib.h>    /* malloc, free */
#include <assert.h>    /* assert */
#include <string.h>    /* memset */
#include <stdio.h>	   /* sscanf */
#include <string.h>    /* strcpy */

#include "dhcp.h"      /* Dynamic Host Configuration Protocol */

/****************************************************************************
    Macros for this program
*****************************************************************************/
#define SUCCESS (1)
#define FAIL    (0)

#define LEFT        (0)
#define RIGHT       (1)
#define BITS_IN_IP (32)

#define Right(X) (X->child[RIGHT])
#define Left(X)  (X->child[LEFT])

#define LAN_IP       (0x00000000)
#define ROUTER_IP    (0x00000001)
#define BROUDCAST_IP (0xFFFFFFFF)

#define IsBitOn(val, i) ( (val & (1 << (i))) != 0 )

#define CalcDepth(dhcp) (BITS_IN_IP - dhcp->subnet_mask)

/****************************************************************************
    Structs for this program
*****************************************************************************/

typedef struct node node_t;

struct node
{
    node_t       *child[2];
    unsigned int  is_occupied;
};

/* typedef struct dhcp dhcp_t; */
struct dhcp
{
  char    *ip;
  node_t  *root;
  size_t   subnet_mask;
};


/*============================  Static functions  ============================*/

/*==========================  StrIp2Int  ==========================*/
static int StrIp2Int(const char* ipAddress)
{
  unsigned int ipbytes[4];

  sscanf(ipAddress, "%u.%u.%u.%u",
        (ipbytes + 3), (ipbytes + 2), (ipbytes + 1), (ipbytes + 0));

  return    ipbytes[0]       | ipbytes[1] << 8 |
            ipbytes[2] << 16 | ipbytes[3] << 24;
}

/*==========================  SetBitTo  ==========================*/
static int SetBitTo(int *ip, int index, int BitValue)
{
	*ip &= (~(int)0 - ((int)1 << index));       /* nullyfy the bit */
	return *ip | ( (int)BitValue << index );    /* set bit to value */
}

/*==========================  IntIp2Str  ==========================*/
static void IntIp2Str(int int_ip, char *ip_offer)
{
    unsigned char bytes[4];

    bytes[0] =  int_ip        & 0xFF;
    bytes[1] = (int_ip >> 8)  & 0xFF;
    bytes[2] = (int_ip >> 16) & 0xFF;
    bytes[3] = (int_ip >> 24) & 0xFF;

    sprintf(ip_offer,"%d.%d.%d.%d",
            bytes[3], bytes[2], bytes[1], bytes[0]);
}

/*==========================  UpdateOcc  ==========================*/
static void UpdateOcc(node_t *node)
{
    int left = 0, right = 0;

    if ( Left(node) != NULL )
    {
        left = Left(node)->is_occupied;
    }

    if ( Right(node) != NULL )
    {
        right = Right(node)->is_occupied;
    }

    node->is_occupied = left && right;
}

/*==========================  CreateNode  ==========================*/
static node_t* CreateNode(void)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    if (NULL != node)
    {
        memset(node, 0, sizeof(node_t));
    }
    return node;
}

/*==========================  ReqIp  ==========================*/
static int ReqIp(node_t *node, int req_ip, int depth)
{
    int direction;
    int ret_val;

    if ( node->is_occupied ) /* ==1 */
    {
        return FAIL;
    }

    if ( 0 == depth )
    {
        /* found required IP */
        node->is_occupied = 1;
        return SUCCESS;
    }

    /* IsBitOn == 0 => LEFT, IsBitOn == 1 => RIGHT */
    direction = IsBitOn(req_ip, depth - 1);

    if ( NULL == node->child[direction] )
    {
        node->child[direction] = CreateNode();
        if ( NULL == node->child[direction] )
        {
            return FAIL;
        }
    }

    ret_val = ReqIp(node->child[direction], req_ip, depth - 1);

    UpdateOcc(node);

    return ret_val;
}

/*==========================  IsIpValid  ==========================*/
static int IsIpValid(const char *ip_1, const char *ip_2, int subnet_mask)
{
    long suffix = BITS_IN_IP - subnet_mask;

    unsigned int int_ip_1 = (unsigned int)StrIp2Int(ip_1) >> suffix;
    unsigned int int_ip_2 = (unsigned int)StrIp2Int(ip_2) >> suffix;

    return int_ip_1 == int_ip_2;
}

/*==========================  IsIpValid  ==========================*/
static int IsBasicIp(const char *ip, int subnet_mask)
{
    int suffix_mask = ~(unsigned int)0 >> subnet_mask;

    int suffix_ip    = 0;
    int lan_ip       = 0;
    int router_ip    = 0;
    int broudcast_ip = 0;

    suffix_ip = StrIp2Int(ip) & suffix_mask;

    lan_ip       = LAN_IP       & suffix_mask;
    router_ip    = ROUTER_IP    & suffix_mask;
    broudcast_ip = BROUDCAST_IP & suffix_mask;

    /* if suffix_ip is equals to one of the basic ips suffix returns 1 */
    return     (lan_ip       == suffix_ip)
            || (router_ip    == suffix_ip)
            || (broudcast_ip == suffix_ip);
}

/*==========================  FirstFree  ==========================*/
static int FirstFree(node_t *node, int depth, int *ip_offer)
{
    assert( (node != NULL) && (ip_offer != NULL) );

    if ( node->is_occupied ) /* ==1 */
    {
        /* already occupied, take another route */
        return FAIL;
    }

    if ( 0 == depth )
    {
        /* found address to give, update is_occupied and return SUCCESS */
        node->is_occupied = 1;
        return SUCCESS;
    }

    /*=======================  Left path  =======================*/
    if ( NULL == Left(node) )
    {
        /* if node doesn't exist allocate it */
        Left(node) = CreateNode();
        if ( NULL == Left(node) )
        {
            return FAIL; /* case: failed to allocate new node */
        }
    }

    if ( FirstFree(Left(node), depth - 1, ip_offer) != FAIL )
    {
        *ip_offer = SetBitTo(ip_offer, depth - 1, LEFT);

        UpdateOcc(node);
        return SUCCESS;
    }

    /*=======================  Right path  =======================*/
    if ( NULL == Right(node) )
    {
        /* if node doesn't exist allocate it */
        Right(node) = CreateNode();
        if ( NULL == Right(node) )
        {
            return FAIL; /* case: failed to allocate new node */
        }
    }

    if ( FirstFree(Right(node), depth - 1, ip_offer) != FAIL )
    {
        *ip_offer = SetBitTo(ip_offer, depth - 1, RIGHT);

        UpdateOcc(node);
        return SUCCESS;
    }

    return FAIL;
}

/*****************************************************************************
** description:   Create a dhcp handler
** arguments:     ip          - subnet ip adrress.
**                subnet_mask - number of bits representing the subnet
** return value:  pointer to the dhcp handler,
** notes:        !!(i love roma)
******************************************************************************/
dhcp_t* DhcpCreate(const char *ip, size_t subnet_mask)
{
    dhcp_t *dhcp = NULL;

    assert( ip != NULL );

    dhcp = (dhcp_t*) malloc(sizeof(dhcp_t));
    if (NULL != dhcp)
    {
        dhcp->subnet_mask = subnet_mask;
        dhcp->ip          = (char*)ip;

        dhcp->root = CreateNode();

        if ( dhcp->root == NULL ||
             (  ReqIp(dhcp->root, LAN_IP      , CalcDepth(dhcp))
             && ReqIp(dhcp->root, ROUTER_IP   , CalcDepth(dhcp))
             && ReqIp(dhcp->root, BROUDCAST_IP, CalcDepth(dhcp)) ) == 0 )
        {
            /* case: one of the basic ips failed to allocate */
            DhcpDestroy(dhcp);
            dhcp = NULL;
        }

        return dhcp;
    }

    return NULL;
}

/*=======================  EraseAllNodesRec  ========================*/
static void EraseAllNodesRec(node_t *node)
{
    /* base case: found end of branch */
    if ( NULL == node )
    {
        return;
    }

    EraseAllNodesRec(Right(node));
    EraseAllNodesRec(Left (node));

    memset(node, 0, sizeof(node_t));
    free(node);
}
/*****************************************************************************
** description:  free dhcp handler.
** arguments:    dhcp_t - Dhcp handler.
** return value: void
** notes:        must be called at end of use.
******************************************************************************/
void DhcpDestroy(dhcp_t *dhcp)
{
    assert( dhcp != NULL );

    EraseAllNodesRec(dhcp->root);

    memset(dhcp, 0, sizeof(dhcp_t));
    free(dhcp);
}

/*****************************************************************************
** description:  alloc the ip requsted if its free. alloc the next free one
                 if requseted NULL.
** arguments:    dhcp - Dhcp handler.
**               ip_request - the requsted ip can be either a legit ip from
                 the possible IP's or 0 if the user just wants some ip
**               ip_offer - the offer for the ip address will assigned there
** return value: 1 - success, 0 - fail
** notes:
******************************************************************************/
int DhcpAllocIp(dhcp_t *dhcp, const char *ip_request, char *ip_offer)
{
    int int_ip_offer = 0;

    assert( (dhcp != NULL) && (ip_offer != NULL) );

    if ( NULL != ip_request )
    {
        /* ip_request was given by the user */

        if ( !IsIpValid(dhcp->ip, ip_request, dhcp->subnet_mask) )
        {
            /* ip_request is NOT valid */
            ip_offer = NULL;
            return FAIL;
        }

        if ( ReqIp(dhcp->root, StrIp2Int(ip_request), CalcDepth(dhcp) ) )/*==1*/
        {
            /* ip_request was found and assigned */
            strcpy(ip_offer, ip_request);
            return SUCCESS;
        }
    }

    /* case: (1). ReqIp failed (required IP occupied or failed)
          OR (2). ip_request was NOT given by the user */
    int_ip_offer = StrIp2Int(dhcp->ip);

    if ( FirstFree(dhcp->root, CalcDepth(dhcp), &int_ip_offer) ) /* ==1 */
    {
        IntIp2Str(int_ip_offer, ip_offer);
        return SUCCESS;
    }
    else
    {
        /* free address was not found or failed at allocation */
        /*ip_offer = NULL;*/
        return FAIL;
    }
}

/*==========================  DhcpFreeIpRec  ==========================*/
static int DhcpFreeIpRec(node_t *node, int ip, int depth)
{
    int ret_val;
    int direction;

    assert( node != NULL );

    if ( 0 == depth )
    {
        node->is_occupied = 0;
        return SUCCESS;
    }

    direction = IsBitOn(ip, depth - 1);

    if ( NULL == node->child[direction] )
    {
        /* case: the node is not allocated,
                 therefore by 'Vacuous truth' its' already free */
        return SUCCESS;
    }

    ret_val = DhcpFreeIpRec(node->child[direction], ip, depth - 1);

    UpdateOcc(node);

    return ret_val;
}

/*****************************************************************************
** description:   free a certain ip address
** arguments:     dhcp - Dhcp handler.
**                ip  - the ip address to be freed
** return value:  1 - success, 0 - fail
** notes:         returns fail if the ip address is reserved
******************************************************************************/
int DhcpFreeIp(dhcp_t *dhcp, char *ip)
{
    assert( dhcp != NULL );

    /* if (1). ip to remove is not valid
       OR (2). ip to remove is one of the basic addresses */
    if (  !IsIpValid(ip, dhcp->ip, dhcp->subnet_mask)
        || IsBasicIp(ip, dhcp->subnet_mask) )
    {
        /* if ip is not valid return failed */
        return FAIL;
    }

    return DhcpFreeIpRec(dhcp->root, StrIp2Int(ip), CalcDepth(dhcp));
}

/*==========================  CountOcc  ==========================*/
static size_t CountOcc(node_t *node, int depth)
{
    if ( NULL == node )
    {
        return 0;
    }

    if ( 0 == depth )
    {
        return node->is_occupied;
    }

    if ( node->is_occupied ) /* ==1 */
    {
        return (1 << depth);
    }

    return    CountOcc( Left(node), depth - 1)
            + CountOcc(Right(node), depth - 1);
}

/*****************************************************************************
** description:  counts the number of free IP's there are in the dhcp.
** arguments:    dhcp - pointer to dhcp.
** return value: number of free IP's in dhcp.
** notes:
******************************************************************************/
size_t DhcpCountFreeIps(const dhcp_t *dhcp)
{
    size_t total_nodes = 0;

    assert( dhcp != NULL );
                        /* 2^(free bits) */
    total_nodes = (1 << (BITS_IN_IP - dhcp->subnet_mask));

    return total_nodes - CountOcc(dhcp->root, CalcDepth(dhcp));
}

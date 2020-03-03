/****************************************************************
  Filename: dhcp.h
  Purpose:  Header file for Dynamic Host Configuration Protocol
  Version:  2
*****************************************************************/
#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>  /* size_t */

typedef struct dhcp dhcp_t;

/*****************************************************************************
** description:   Create a dhcp handler
** arguments:     ip          - subnet ip adrress.
**                subnet_mask - number of bits representing the subnet
** return value:  pointer to the dhcp handler,
** notes:
******************************************************************************/
dhcp_t* DhcpCreate(const char *ip, size_t subnet_mask);

/*****************************************************************************
** description:  free dhcp handler.
** arguments:    dhcp_t - Dhcp handler.
** return value: void
** notes:        must be called at end of use.
******************************************************************************/
void DhcpDestroy(dhcp_t *dhcp);

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
int DhcpAllocIp(dhcp_t *dhcp, const char *ip_request, char *ip_offer);

/*****************************************************************************
** description:   free a certain ip address
** arguments:     dhcp - Dhcp handler.
**                ip  - the ip address to be freed
** return value:  1 - success, 0 - fail
** notes:         returns fail if the ip address is reserved
******************************************************************************/
int DhcpFreeIp(dhcp_t *dhcp, char *ip);

/*****************************************************************************
** description:  counts the number of free IP's there are in the dhcp.
** arguments:    dhcp - pointer to dhcp.
** return value: number of free IP's in dhcp.
** notes:
******************************************************************************/
size_t DhcpCountFreeIps(const dhcp_t *dhcp);

#endif /* __DHCP_H__ */

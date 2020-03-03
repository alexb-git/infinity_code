/****************************************************************************
** Filename:    - dhcp_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - DHCP testing (based on tries data structure)
** Date:        - 4/12/2017
** Version:     - 13
****************************************************************************/
#include <stdio.h>	 /* printf */
#include <string.h>  /* strcpy */

#include "dhcp.h"   /* Dynamic Host Configuration Protocol */

/****************************************************************************
    Helpful colors
*****************************************************************************/
#define YLL	 "\x1b[93m"
#define GRE	 "\x1b[92m"
#define RED	 "\x1b[91m"
#define WHI	 "\x1B[37m"
#define CYA	 "\x1B[36m"
#define BLU	 "\x1B[34m"
#define YEL	 "\x1b[33m"
#define RES	 "\x1b[0m"
#define BLD  "\x1B[1m"
#define UDL  "\x1b[4m"

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLU "\n\t------------"\
                                    "  This is a test for: "\
                                    X" ------------\n" RES)

#define PrintInYellow(X)  ( printf(YEL X RES) )
#define PrintInGreen(X)   ( printf(GRE X RES) )
#define PrintInRed(X)     ( printf(RED X RES) )
#define PrintOK           ( printf(GRE "%s" RES, "-OK") )
#define PrintERR          ( printf(RED "%s" RES, "-ERR"))
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    extern debug functions
*****************************************************************************/




/*==========================  THE MAIN FUNCTION  ==========================*/
int main()
{
    dhcp_t       *dhcp = NULL;
    size_t subnet_mask = 29;
    char        ip[16] = "255.170.240.0";

    size_t curr_free = (1 << (32 - subnet_mask)) - 3;
    char ip_request[16];
    char ip_offer[16];
    int  res;

    printf( YEL "\n-> Create DHCP handler with %lu subnet-mask" RES,
            subnet_mask );

    /*==============  Create DHCP handler and check Free IPs  ==============*/
    dhcp = DhcpCreate(ip, subnet_mask);
    printf("\nFree Ips = %lu ", DhcpCountFreeIps(dhcp));
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    /*==============  Ask to allocate specific address  ==============*/
    printf( YEL "\n\n-> DhcpAllocIp specific address" RES);

    strcpy(ip_request, "255.170.240.3");
    printf( YEL "\n-> request IP : %s" RES, ip_request);

    res = DhcpAllocIp(dhcp, ip_request, ip_offer);

    --curr_free;
    printf("\n%s  ip_offer = %s  ", (res)?("FOUND"):("NOT FOUND"), ip_offer);
    PrintOKorERR( res == 1 );
    PrintOKorERR( strcmp(ip_offer, ip_request) == 0 );
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    /*==============  Ask to allocate specific address  ==============*/
    printf( YEL "\n\n-> DhcpAllocIp specific address that is taken" RES);

    strcpy(ip_request, "255.170.240.3");
    printf( YEL "\n-> request IP : %s" RES, ip_request);

    res = DhcpAllocIp(dhcp, ip_request, ip_offer);

    --curr_free;
    printf("\n%s  ip_offer = %s  ", (res)?("FOUND"):("NOT FOUND"), ip_offer);
    PrintOKorERR( res == 1 );
    PrintOKorERR( strcmp(ip_offer, ip_request) != 0 );
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    /*==============  Allocate All the possible addresses  ==============*/
    printf( YEL "\n\n-> DhcpAllocIp All the possible addresses" RES);

    while ( (res = DhcpAllocIp(dhcp, NULL, ip_offer)) != 0 )
    {
        --curr_free;
        printf("\n%s  ip_offer = %s  ", (res)?("FOUND"):("NOT FOUND"), ip_offer);
        PrintOKorERR( res == 1 );
        PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );
    }

    /*==============  DhcpFreeIp every second address  ==============*/
    printf( YEL "\n\n-> DhcpFreeIp every second address" RES);

    strcpy(ip_request, "255.170.240.2");
    printf( YEL "\n-> Free IP : %s" RES, ip_request);
    res = DhcpFreeIp(dhcp, ip_request);
    ++curr_free;
    printf("\nDhcpFreeIp %s ", (res)?("SUCCEEDED"):("FAILED"));
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    strcpy(ip_request, "255.170.240.4");
    printf( YEL "\n-> Free IP : %s" RES, ip_request);
    res = DhcpFreeIp(dhcp, ip_request);
    ++curr_free;
    printf("\nDhcpFreeIp %s ", (res)?("SUCCEEDED"):("FAILED"));
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    strcpy(ip_request, "255.170.240.6");
    printf( YEL "\n-> Free IP : %s" RES, ip_request);
    res = DhcpFreeIp(dhcp, ip_request);
    ++curr_free;
    printf("\nDhcpFreeIp %s ", (res)?("SUCCEEDED"):("FAILED"));
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    /*==============  Allocate All the possible addresses  ==============*/
    printf( YEL "\n\n-> DhcpAllocIp All the possible addresses" RES);

    while ( (res = DhcpAllocIp(dhcp, NULL, ip_offer)) != 0 )
    {
        --curr_free;
        printf("\n%s  ip_offer = %s  ", (res)?("FOUND"):("NOT FOUND"), ip_offer);
        PrintOKorERR( res == 1 );
        PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );
    }

    /*==============  DhcpFreeIp every second address  ==============*/
    printf( YEL "\n\n-> DhcpFreeIp free freed address" RES);

    strcpy(ip_request, "255.170.240.6");
    printf( YEL "\n-> Free IP : %s" RES, ip_request);
    res = DhcpFreeIp(dhcp, ip_request);
    ++curr_free;
    printf("\nDhcpFreeIp %s ", (res)?("SUCCEEDED"):("FAILED"));
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    strcpy(ip_request, "255.170.240.6");
    printf( YEL "\n-> Free IP : %s" RES, ip_request);
    res = DhcpFreeIp(dhcp, ip_request);
    printf("\nDhcpFreeIp %s ", (res)?("SUCCEEDED"):("FAILED"));
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    /*==============  DhcpFreeIp one of basic addresses  ==============*/
    printf( YEL "\n\n-> Try to DhcpFreeIp one of basic addresses" RES);

    strcpy(ip_request, "255.170.240.0");
    printf( YEL "\n-> Free IP : %s" RES, ip_request);
    res = DhcpFreeIp(dhcp, ip_request);
    printf("\nDhcpFreeIp %s ", (res)?("SUCCEEDED"):("FAILED"));
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    strcpy(ip_request, "255.170.240.7");
    printf( YEL "\n-> Free IP : %s" RES, ip_request);
    res = DhcpFreeIp(dhcp, ip_request);
    printf("\nDhcpFreeIp %s ", (res)?("SUCCEEDED"):("FAILED"));
    PrintOKorERR( curr_free == DhcpCountFreeIps(dhcp) );

    /*printf("\n curr_free = %lu", curr_free);
    printf("\n DhcpCountFreeIps(dhcp) = %lu", DhcpCountFreeIps(dhcp));*/

    DhcpDestroy(dhcp);
    printf("\n");
    return 0;
}

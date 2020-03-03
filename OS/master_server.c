/****************************************************************************
** Filename:    - master_server.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - practicing server services
** Date:        - 19/2/2018
** Version:     - 1
*****************************************************************************/
/*  Example code: A simple server side code, which echos back the
    received message. Handle multiple socket connections with select
    and fd_set on Linux */

#include <stdio.h>      /* printf */
#include <errno.h>      /* errno, EINTR */
#include <string.h>     /* strlen,  */
#include <stdlib.h>     /* exit(0) */
#include <unistd.h>     /* read, close */

#include <sys/time.h>   /* fd_set, FD_ZERO, FD_SET, FD_ISSET */
#include <arpa/inet.h>  /* inet_addr, struct sockaddr_in */

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
/****************************************************************************/

#define N_CLIENTS   (3)     /* number of clients the server can have */
#define BUFFER_SIZE (50)    /* in bytes */
#define TCP_PORT    (5000)  /* my default port */
#define UDP_PORT    (5000)  /* my default port */
#define INPUT_FD    (0)     /* input fd */

#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#define BRODCAST_IP ("255.255.255.255")

void error(const char *msg)
{
    perror(msg);
    printf("FAILED\n" RES);
    exit(EXIT_FAILURE);
}

void MsgIfErr(int val, char *msg)
{
    if ( val < 0 )
    {
        printf(RED);
        error(msg);
    }
    else
    {
        printf(GRE "SUCCEEDED" BLD " %s\n" RES, msg);
    }
}

/*===============================  THE MAIN  ===============================*/
int main(int argc , char *argv[])
{
    /* --------------------- variables declarations --------------------- */
    fd_set set_of_rfds; /* set of socket descriptors */

    int  i;             /* various for loops */
    int  max_sd = 0;    /* for select function */
    int  ret_val;       /* to check function returns */
    int  valread;       /* for measure incoming string length */
    int  addrlen;       /* size of struct */
    int  activity;      /* return val of select function */
    int  soket_des;     /* tmp variable, client_socket[] loads to it */
    int  new_socket;    /* to establish new tcp connection */
    int  broadcast_flag = 1; /* broadcast permission flag */

    int  TCP_socket;    /* socket for TCP */
    int  UDP_socket;    /* socket for UDP */
    int  BCT_socket;    /* socket for Broadcast */
    /* initialise all client_socket[] to 0 (not checked) */
    int  client_socket[N_CLIENTS] = {0};

    struct sockaddr_in TCP_sock_add;    /* struct for TCP uses */
    struct sockaddr_in UDP_sock_add;    /* struct for UDP uses */
    struct sockaddr_in UDP_other;       /* struct for UDP sender info */
    struct sockaddr_in broadcast;       /* struct for Broadcast uses */

    struct timeval tv; /* time out struct */

    char buffer[BUFFER_SIZE] = {0};
    char *message = "Welcome to Alex server 2.01 | "; /* a message */


    /* ----------------------- code begins here ------------------------ */
    /* wait until either socket has data ready to be recvd() (timeout 10.5 secs) */
    tv.tv_sec  = 10;
    tv.tv_usec = 500000;

    /* create a master socket to manage TCP_sockets */
    TCP_socket = socket(AF_INET, SOCK_STREAM, 0);
    MsgIfErr(TCP_socket, "TCP socket");

    /* create a master socket to manage UDP_sockets */
    UDP_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    MsgIfErr(UDP_socket, "UDP socket");

    /* create a master socket to manage UDP_sockets */
    BCT_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    MsgIfErr(UDP_socket, "Broadcast socket");

    /* set premition for broadcast */
    setsockopt( BCT_socket, SOL_SOCKET, SO_BROADCAST,
                &broadcast_flag, sizeof(broadcast_flag));

    /*  set master socket to allow multiple connections,
        this is just a good habit, it will work without this */
    /*ret_val = setsockopt( TCP_socket   ,
                            SOL_SOCKET   ,
                            SO_REUSEADDR ,
                            (char *)&opt ,
                            sizeof(opt)  );
    MsgIfErr(ret_val, "TCP setsockopt");

    ret_val = setsockopt( UDP_socket   ,
                          SOL_SOCKET   ,
                          SO_REUSEADDR ,
                          (char *)&opt ,
                          sizeof(opt)  );
    MsgIfErr(ret_val, "UDP setsockopt");*/


    /* create socket address struct for TCP (connect socket to address) */
    TCP_sock_add.sin_family      = AF_INET;
    TCP_sock_add.sin_addr.s_addr = INADDR_ANY; /* localhost */
    TCP_sock_add.sin_port        = htons( TCP_PORT );

    /* create socket address struct for UDP (connect socket to address) */
    UDP_sock_add.sin_family      = AF_INET;
    UDP_sock_add.sin_addr.s_addr = INADDR_ANY; /* localhost */
    UDP_sock_add.sin_port        = htons( UDP_PORT );

    /* create socket address struct for Broadcast (connect socket to address) */
    broadcast.sin_family      = AF_INET;
    broadcast.sin_addr.s_addr = inet_addr(BRODCAST_IP);
    broadcast.sin_port        = htons(UDP_PORT);

    /* TCP bind the socket to localhost port */
    ret_val = bind(  TCP_socket                      ,
                    (struct sockaddr*)&TCP_sock_add  ,
                     sizeof(TCP_sock_add)            );
    MsgIfErr(ret_val, "TCP bind");

    /* UDP bind the socket to localhost port */
    ret_val = bind(  UDP_socket                      ,
                    (struct sockaddr*)&UDP_sock_add  ,
                     sizeof(UDP_sock_add)            );
    MsgIfErr(ret_val, "UDP bind");

    printf(YEL "Listener on TCP port %d \n" RES, TCP_PORT);
    printf(YEL "Listener on UDP port %d \n" RES, UDP_PORT);

    /*  try to specify maximum of n pending connections
        for the master socket */
    ret_val = listen(TCP_socket, 3);
    MsgIfErr(ret_val, "listen");

    /* accept the incoming connection */
    addrlen = sizeof(TCP_sock_add);
    printf(YEL "Waiting for connections ...\n\n" RES);

    while( 1 )
    {
        /* clear the socket set */
        FD_ZERO(&set_of_rfds);

        /* add master socket to set */
        FD_SET(TCP_socket, &set_of_rfds);
        FD_SET(UDP_socket, &set_of_rfds);
        FD_SET(INPUT_FD,   &set_of_rfds);
        max_sd = MAX(MAX(max_sd, TCP_PORT) , MAX(UDP_PORT, INPUT_FD));

        /* add child sockets to set */
        for ( i = 0 ; i < N_CLIENTS ; ++i)
        {
            /* socket descriptor */
            soket_des = client_socket[i];

            /* if valid socket descriptor then add to read list */
            if(soket_des > 0)
            {
                FD_SET(soket_des, &set_of_rfds);
            }

            /*  highest file descriptor number,
            need it for the select function */
            max_sd = MAX(max_sd, soket_des);
        }

        /*  wait for an activity on one of the sockets,
            timeout is NULL, so wait indefinitely */
        activity = select( max_sd + 1 , &set_of_rfds , NULL , NULL , &tv);

        if ( (activity < 0) && (errno != EINTR) )
        {
            printf("select error");
        }

        if (FD_ISSET(INPUT_FD, &set_of_rfds))
        {
            read(INPUT_FD, buffer, BUFFER_SIZE);

            if ( strncmp("broadcast\n", buffer, strlen("broadcast\n")) == 0 )
            {
                printf("Perform \"broadcast\"\n");

                strcpy(buffer,"Broadcast from Alex");
                ret_val = sendto( BCT_socket,
                                  buffer,
                                  BUFFER_SIZE,
                                  0, /* flags */
                                  (struct sockaddr*)&broadcast,
                                  sizeof(broadcast));
                MsgIfErr(ret_val, "broadcast");
            }

            if ( strncmp("quit\n", buffer, strlen("quit\n")) == 0 )
            {
                printf("Perform \"quit\"\n");
                break; /* break the endless loop of violence */
            }
        }

        /*  If something happened on the master TCP socket,
            then its an incoming connection
            (Return true if fd is in the set) */
        if (FD_ISSET(TCP_socket, &set_of_rfds))
        {
            new_socket = accept( TCP_socket              ,
                                 (struct sockaddr*)&TCP_sock_add ,
                                 (socklen_t*)&addrlen       );
            MsgIfErr(new_socket, "accept");

            /*  inform user of socket number
                used in send and receive commands */
            printf( "New TCP connection | socket_fd: "
                    RED BLD"%d"RES" | ip: "
                    GRE BLD"%s"RES" | port: "
                    BLU BLD"%d\n" RES,
                                new_socket                       ,
                                inet_ntoa(TCP_sock_add.sin_addr) ,
                                ntohs(TCP_sock_add.sin_port)     );

            /* send new connection greeting message */
            if( send( new_socket,
                      message   ,
                      strlen(message), 0) != strlen(message) )
            {
                perror("send");
            }
            else
            {
                printf(YEL "Welcome message sent successfully\n" RES);
            }


            /* add new socket to array of sockets */
            for (i = 0 ; i < N_CLIENTS ; ++i)
            {
                /* if position is empty */
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf(YEL "Adding to list of sockets as "RED"#%d\n" RES, i);
                    break;
                }
            }
        }/* end of recieving message from TCP protocol */

        /* check fot update to UDP socket */
        if ( FD_ISSET(UDP_socket, &set_of_rfds) )
        {
            int ret_val;

            /* try to receive some data, this is a blocking call */
            ret_val = recvfrom( UDP_socket,
                                buffer,
                                BUFFER_SIZE,
                                0, /* flags */
                                (struct sockaddr*)&UDP_other,
                                (socklen_t*)&addrlen);
            MsgIfErr(ret_val, "recvfrom()");

            /*  print details of the client/peer
                and the data received */
            printf( YEL "UDP Received packet from " WHI "%s | "
                    RES BLU "%7d |" CYA " Message: "
                    RED BLD "%s\n" RES,

                            inet_ntoa(UDP_other.sin_addr),
                            ntohs(UDP_other.sin_port),
                            buffer);

            /* now reply the client with the same data */
            strcpy(buffer, "PONG");
            ret_val = sendto( UDP_socket,
                              buffer,
                              BUFFER_SIZE,
                              0,
                              (struct sockaddr*)&UDP_other,
                              addrlen);
            MsgIfErr(ret_val, "sendto()");
        }/* if (UDP_socket touched) */


        /* check fot update to TCP clients socket */
        for (i = 0 ; i < N_CLIENTS ; ++i)
        {
            soket_des = client_socket[i];

            /* Return true if fd is in the set */
            if ( soket_des > 0 && FD_ISSET(soket_des, &set_of_rfds) )
            {
                /*  Check if it was for closing,
                    and also read the incoming message */
                if ((valread = read(soket_des, buffer, BUFFER_SIZE)) == 0)
                {

                    /*  read 0 bytes => somebody disconnected =>
                        get his details and print */
                    getpeername( soket_des                      ,
                                (struct sockaddr*)&TCP_sock_add ,
                                (socklen_t*)&addrlen            );

                    printf( "Host TCP disconnected | ip: "
                            GRE BLD"%s"RES"| port: "
                            BLU BLD"%d\n\n" RES,
                            inet_ntoa(TCP_sock_add.sin_addr) ,
                            ntohs(TCP_sock_add.sin_port)     );

                    /*  Close the socket and mark as 0 in list for reuse */
                    close( soket_des );
                    client_socket[i] = 0;
                }
                else
                {
                    /*  set the string terminating NULL byte
                        on the end of the data read */
                    buffer[valread] = '\0';
                    send(soket_des , buffer , strlen(buffer) , 0 );
                }
            } /* if ( FD_ISSET..) */
        } /* for (... i < N_CLIENTS ...) */
    } /* while (1) */


    /* close all file sockets - exit gresfully*/
    for (i = 0 ; i < N_CLIENTS ; ++i)
    {
        close( client_socket[i] );
        client_socket[i] = 0;
    }
    close(UDP_socket);
    close(TCP_socket);
    close(BCT_socket);


    return 0;
}

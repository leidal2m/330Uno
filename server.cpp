/*****************************************************************
 Sockets Daemon Program

  This code was modified from Nigel Horspools, "The Berkeley
  Unix Environment".

  A daemon process is started on some host.  A socket is acquired
  for use, and it's number is displayed on the screen.  For clients
  to connect to the server, they muse use this socket number.
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <sys/wait.h>

/* Use port number 0 so that we can dynamically assign an unused
 * port number. */
#define PORTNUM         0

#define MAXLINE 512

int main()
{
  struct sockaddr_in saddr;         /* socket information */
  struct hostent *hp;               /* host information */
  char hostname[256];               /* host computer */
  socklen_t slen;                   /* length socket address */
  int sock;                            /* socket return value */
  
  char ch[MAXLINE];                 /* character for i/o */
  int bbf;
  int num_char=MAXLINE;
  size_t = size;
  char color; //current color
  char number; //current number
  
  pid_t fork_return;
  int status;

  fd_set active_fd_set, read_fd_set;


  /*
   * Build up our network address. Notice how it is made of machine name + port.
   */

  //create the socket
  
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons (PORTNUM);
  sadder.sin_addr.s_addr = htonl (INADDR_ANY);
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Clear the data structure (saddr) to 0's. */
 //memset(&saddr,0,sizeof(saddr));


  /* Tell our socket to be of the IPv4 internet family (AF_INET). */
// saddr.sin_family = AF_INET;


  /* Aquire the name of the current host system (the local machine). */
//  gethostname(hostname,sizeof(hostname));


  /* Return misc. host information.  Store the results in the
   * hp (hostent) data structure.  */
// hp = gethostbyname(hostname);


  /* Copy the host address to the socket data structure. */
// memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);


  /* Convert the integer Port Number to the network-short standard
   * required for networking stuff. This accounts for byte order differences.*/
// saddr.sin_port = htons(PORTNUM);
  

  /*
   * Now that we have our data structure full of useful information,
   * open up the socket the way we want to use it.
   */
  

  /* Register our address with the system. */
  bind(sock,(struct sockaddr *)&saddr,sizeof(saddr));

  listen(s,1);
  
  //initilize active sockets
  FD_ZERO (&active_fd_set);
  FD_SET (sock, &active_fd_set);
  /* Display the port that has been assigned to us. */
  slen = sizeof(saddr);
  getsockname(s,(struct sockaddr *)&saddr,&slen);
  printf("Socket assigned: %d\n",ntohs(saddr.sin_port));


  while(1)
  {
    read_fd_set = active_fd_set;
    select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);

    for(I = 0; I < FD_SETSIZE; I++)
    {
      if(FD_ISSET(i, &read_fd_set))
      {
        if (i == sock)
        {
        //connection request on original socket
        int sfd;       /* socket descriptor returned from accept() */
        slen = sizeof (saddr);
        sfd = accept(sock,(struct sockaddr *) &saddr, &slen);
        //add the new connection
        FD_SET (sfd. &active_fd_set);
        while((num_char=read(0,ch,MAXLINE)))
          write(sfd,ch,num_char);

        }
        else
        {
          char buffer[MAXLINE];
          int bytes;

          bytes = read(i, buffer, MAXLINE);
          fprintf(stderr, "Server got message: \"%s\" \n");

          close(i);
          FD_CLR(I);
        }
      }
      
      
    }

  }

  //     fork_return = fork();

  //       /* Tell socket to wait for input.  Queue length is 1. */

  //     if(fork_return == 0) //Loudmouth kid process
  //     {
  //       /* Wait in the 'accept()' call for a client to make a connection. */
          
  //       /*Read from file, write to socket*/
  //       while((num_char=read(0,ch,MAXLINE))> 0)
  //         write(sfd,ch,num_char);

  //       close(sfd);
  //       exit (1);
  //     }
  //     else if(fork_return > 0) //Deadbeat dad process
  //     {
  //       /*Read from file, write to socket*/
  //       while((num_char=read(sfd,ch,MAXLINE))> 0 && waitpid(fork_return, &status,WNOHANG)==0)
  //         write(1,ch,num_char);
  //     }
  //     else if(fork_return < 0)//deformed process
  //     {
  //       printf("AMBER ALERT\n");
  //       switch (errno)
  //       {
  //           case EAGAIN:
  //               printf(" \"JASOOOOON, JASON! JAYYY SOOOON!\" (system process limit reached)");
  //           case ENOMEM:
  //               printf("\"Are you sure you're not the origammy killer?!\" (out of memory)");
  //       }
  //     }

  //     close(sfd);
  //   }

  // }
  return 0;
} 
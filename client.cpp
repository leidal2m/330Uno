/*****************************************************************
 Sockets Client Program 

  This code is a modified version taken from Nigel Horspool's "The Berkeley
  Unix Environment".

  This client connects to a specified server (host) and receives
  information from it.
*****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

/* Display error message on stderr and then exit. */

#define MAXLINE 512

int main(int argc, char *argv[])
{
  struct sockaddr_in bba; /* socket information */
  struct hostent *hp;     /* host information */
  int slen;               /* host computer */
  int s;                  /* length socket address */
  int rfd;
  char ch[MAXLINE];       /* character for i/o */
  int num_char=MAXLINE;   /* number of characters */
  int port;               /* port to connect to */
  pid_t fork_return;
  int status;

  char portnum[20];
  char hostname[20];
  printf("\n hostname:");
  scanf("%s", hostname);

  printf("\n port number:");
  scanf("%s", portnum);

  /* Clear the data structure (saddr) to 0's. */
  memset(&bba,0,sizeof(bba));

  /* Tell our socket to be of the IPv4 internet family (AF_INET). */
  bba.sin_family = AF_INET;

  /* Acquire the ip address of the server */
  hp=gethostbyname(hostname);

  /* Acquire the port #. */
  port=atoi(portnum);

  /* Copy the server's address to the socket address data structure. */
  memcpy(&bba.sin_addr, hp->h_addr, hp->h_length);

  /* Convert the integer Port Number to the network-short standard
   * required for networking stuff. This accounts for byte order differences.*/
  bba.sin_port=htons(port);
  
  /* Now that we have our data structure full of useful information,
   * open up the socket the way we want to use it.
   */
  s = socket(AF_INET, SOCK_STREAM, 0);
  connect(s,(struct sockaddr *)&bba,sizeof(bba));

  fork_return = fork();

  if(fork_return == 0) //Loudmouth kid process
  {
      /*Read from file, write to socket*/
      while((num_char=read(0,ch,MAXLINE))> 0)
        write(s,ch,num_char);

  }
  else if(fork_return > 0) //Deadbeat dad process
  {
        /*Read from file, write to socket*/
        while((num_char=read(s,ch,MAXLINE))> 0)
          write(1,ch,num_char);
  }
  else if(fork_return < 0)//deformed process
  {
    printf("AMBER ALERT\n");
    switch (errno)
    {
        case EAGAIN:
            printf(" \"JASOOOOON, JASON! JAYYY SOOOON!\" (system process limit reached)");
        case ENOMEM:
            printf("\"Are you sure you're not the origammy killer?!\" (out of memory)");
    }
  }
  close(s);

  return 0;
}
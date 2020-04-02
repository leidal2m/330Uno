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
#include <string.h>
#include <string>

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
  char color; //current color
  char number; //current number
  
  pid_t fork_return;
  int status;

  char topcard[2];
  char cards[108][2] = {
                  "R0",
                  "R1",
                  "R1",
                  "R2",
                  "R2",
                  "R3",
                  "R3",
                  "R4",
                  "R4",
                  "R5",
                  "R5",
                  "R6",
                  "R6",
                  "R7",
                  "R7",
                  "R8",
                  "R8",
                  "R9",
                  "R9",
                  "RS",
                  "RS",
                  "R+",
                  "R+",
                  "WD",
                  "D4",
                  "B0",
                  "B1",
                  "B1",
                  "B2",
                  "B2",
                  "B3",
                  "B3",
                  "B4",
                  "B4",
                  "B5",
                  "B5",
                  "B6",
                  "B6",
                  "B7",
                  "B7",
                  "B8",
                  "B8",
                  "B9",
                  "B9",
                  "BS",
                  "BS",
                  "B+",
                  "B+",
                  "WD",
                  "D4",
                  "G0",
                  "G1",
                  "G1",
                  "G2",
                  "G2",
                  "G3",
                  "G3",
                  "G4",
                  "G4",
                  "G5",
                  "G5",
                  "G6",
                  "G6",
                  "G7",
                  "G7",
                  "G8",
                  "G8",
                  "G9",
                  "G9",
                  "GS",
                  "GS",
                  "G+",
                  "G+",
                  "WD",
                  "D4",
                  "Y0",
                  "Y1",
                  "Y1",
                  "Y2",
                  "Y2",
                  "Y3",
                  "Y3",
                  "Y4",
                  "Y4",
                  "Y5",
                  "Y5",
                  "Y6",
                  "Y6",
                  "Y7",
                  "Y7",
                  "Y8",
                  "Y8",
                  "Y9",
                  "Y9",
                  "YS",
                  "YS",
                  "Y+",
                  "Y+",
                  "WD",
                  "D4",
                }
  int hand4[108];
  for (int i = 0; i < 108; i++)
  {
    hand4[i] = 0;
  }
  int hand5[108];
  for (int i = 0; i < 108; i++)
  {
    hand5[i] = 0;
  }
  int hand6[108];
  for (int i = 0; i < 108; i++)
  {
    hand6[i] = 0;
  }
  int hand7[108];
  for (int i = 0; i < 108; i++)
  {
    hand7[i] = 0;
  }
  int taken[108];
  for (int i = 0; i < 108; i++)
  {
    taken[i] = 0;
  }

  for(int i = 0; i < 7; i++)
  {
    bool draw = false;
    while(draw = false)
    {
      int card = rand() % 108
      if(taken[card] !=1)
      {
        hand4[card] == 1;
        taken[card] == 1;
        draw = true;
      }
    }
  }

  for(int i = 0; i < 7; i++)
  {
    bool draw = false;
    while(draw = false)
    {
      int card = rand() % 108
      if(taken[card] !=1)
      {
        hand5[card] == 1;
        taken[card] == 1;
        draw = true;
      }
    }
  }

  for(int i = 0; i < 7; i++)
  {
    bool draw = false;
    while(draw = false)
    {
      int card = rand() % 108
      if(taken[card] !=1)
      {
        hand6[card] == 1;
        taken[card] == 1;
        draw = true;
      }
    }
  }

  for(int i = 0; i < 7; i++)
  {
    bool draw = false;
    while(draw = false)
    {
      int card = rand() % 108
      if(taken[card] !=1)
      {
        hand7[card] == 1;
        taken[card] == 1;
        draw = true;
      }
    }
  }

  int 4cc = 7;
  char 4cchar;
  int 5cc = 7;
  char 5cchar;
  int 6cc = 7;
  char 6cchar;
  int 7cc = 7;
  char 7char;


  int uno[4] = {0, 0, 0, 0};
  int calledUno[4] = {0, 0, 0, 0};
  bool playable = false;

  fd_set active_fd_set, read_fd_set;

  printf("sock = %d\n", sock);
  /*
   * Build up our network address. Notice how it is made of machine name + port.
   */

  //create the socket
  
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons (PORTNUM);
  saddr.sin_addr.s_addr = htonl (INADDR_ANY);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  printf("sock = %d\n", sock);
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
  printf("sock = %d\n", sock);
  listen(sock,1);
  printf("sock = %d\n", sock);
  //initilize active sockets
  FD_ZERO (&active_fd_set);
  FD_SET (sock, &active_fd_set);
  /* Display the port that has been assigned to us. */
  slen = sizeof(saddr);
  getsockname(sock,(struct sockaddr *)&saddr,&slen);
  printf("Socket assigned: %d\n",ntohs(saddr.sin_port));
  printf("sock = %d\n", sock);
  

  int turn = 4;

  while(1)
  {
    read_fd_set = active_fd_set;
    if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
        {
          perror ("select");
          exit (EXIT_FAILURE);
        }

    for(int i = 0; i < FD_SETSIZE; i++)
    {
      if(i < 10)
        //printf("current FD is %d\n", i);
      
      if(FD_ISSET(i, &read_fd_set))
      {
        if (i == sock)
        {
        //connection request on original socket
        int sfd;       /* socket descriptor returned from accept() */
        slen = sizeof (saddr);
        sfd = accept(sock,(struct sockaddr *) &saddr, &slen);
        printf("sfd = %d\n", sfd);
        //add the new connection
        FD_SET (sfd, &active_fd_set);
        

        }
        else
        {
          char buffer[MAXLINE];
          memset(buffer, 0, MAXLINE);
          int bytes;
          bytes = read(i,buffer,MAXLINE);

          




          if(bytes < 0)
          {
            perror("\"AND YOU KNOW WHAT THE WORST PART OF ALL IS?! I NEVER LEARNED TO READ!\"");
            exit(EXIT_FAILURE);
          }
          else if(bytes == 0)
          {
            close(i);
            FD_CLR(i, &active_fd_set);
            return -1;
          }
          else
          {
            for(int j = 0; j < FD_SETSIZE; j++)
            {



              if(FD_ISSET(j, &active_fd_set))
              {
                
                if(j != i)
                {
                  if( j == 0 || j >= 4)
                  {
                    if(FD_ISSET(7, &active_fd_set))
                    {
                      if(gameset == false)
                      {
                        
                        memset(4cchar, 0, 2);
                        memset(5cchar, 0, 2);
                        memset(6cchar, 0, 2);
                        memset(7cchar, 0, 2);
                        sprintf(4cchar, "%d", 5cc);
                        sprintf(5cchar, "%d", 5cc);
                        sprintf(6cchar, "%d", 5cc);
                        sprintf(7cchar, "%d", 5cc);


                        memset(status, 0, MAXLINE);
                        char status[MAXLINE] = "player 2 currently has"
                        if(5cc > 9)
                          sprintf(status, 5cchar, 2);
                        else
                          sprintf(status, 5cchar, 1);
                        
                        sprintf(status, " cards\n", 8);
                        write(4, status, strlen(status))


                        memset(status, 0, MAXLINE);
                        char status[MAXLINE] = "player 3 currently has"
                        if(6cc > 9)
                          sprintf(status, 6cchar, 2);
                        else
                          sprintf(status, 6cchar, 1);
                        
                        sprintf(status, " cards\n", 8);
                        write(4, status, strlen(status))

                        memset(status, 0, MAXLINE);
                        char status[MAXLINE] = "player 4 currently has"
                        if(7cc > 9)
                          sprintf(status, 7cchar, 2);
                        else
                          sprintf(status, 7cchar, 1);
                        
                        sprintf(status, " cards\n", 8);
                        write(4, status, strlen(status))




                        char status[MAXLINE] = "you currently have "
                        if(4cc > 9)
                          sprintf(status, 4cchar, 2);
                        else
                          sprintf(status, 4cchar, 1);
                        
                        sprintf(status, " cards\n", 8);
                        write(4, status, strlen(status))
                        char 4hand


                        

                        strcpy(4hand, "Your hand: ")
                        
                        for(int i = 0; i < 108; i++)
                        {
                          if(hand4[i] == 1 && taken[i] == 1)
                          {
                            strncat(4hand, &cards[i][0], 1);
                            strncat(4hand, &cards[i][1], 1);
                            sprintf(4hand, "%s%*s", str, 1, "");
                          }
                        }
                        strncat(4hand, "\n", 2);

                        write(4, 4hand, strlen("4hand"));

                        if(uno[0] == 1)
                        {
                          if(calledUno[0] == 0)
                          {
                            if(buffer[0] == 'C')
                            {
                              write(4, "Uno challenged, draw 2 cards", strlen("Uno challenged, draw 2 cards"));
                              for(int d = 0; d < 2; i++)
                              {
                              bool draw = false;
                              while(draw = false)
                              {
                                int card = rand() % 108
                                if(taken[card] !=1)
                                {
                                  hand4[card] == 1;
                                  taken[card] == 1;
                                  bool fulldeck = true;
                                for(int r = 0; r < 108; r++)
                                {
                                  if(taken[r] == 0)
                                  {
                                    fulldeck = false;
                                  }
                                }
                                if(fulldeck = true)
                                {
                                  for(int r = 0; r < 108, r++)
                                  {
                                    taken[r] = 0;
                                    if(hand4[r] = 1 ||hand5[r] = 1 ||hand6[r] = 1 ||hand7[r] = 1)
                                    {
                                      taken[r] = 1;
                                    }
                                  }
                                }
                                draw = true;
                                }
                              }
                              }
                            }

                          }
                        }

                        if(uno[1] == 1)
                        {
                          if(calledUno[1] == 0)
                          {
                            if(buffer[0] == 'C')
                            {
                              write(5, "Uno challenged, draw 2 cards", strlen("Uno challenged, draw 2 cards"));
                              for(int d = 0; d < 2; i++)
                              {
                              bool draw = false;
                              while(draw = false)
                              {
                                int card = rand() % 108
                                if(taken[card] !=1)
                                {
                                  hand5[card] == 1;
                                  taken[card] == 1;
                                  bool fulldeck = true;
                                for(int r = 0; r < 108; r++)
                                {
                                  if(taken[r] == 0)
                                  {
                                    fulldeck = false;
                                  }
                                }
                                if(fulldeck = true)
                                {
                                  for(int r = 0; r < 108, r++)
                                  {
                                    taken[r] = 0;
                                    if(hand4[r] = 1 ||hand5[r] = 1 ||hand6[r] = 1 ||hand7[r] = 1)
                                    {
                                      taken[r] = 1;
                                    }
                                  }
                                }
                                draw = true;
                                }
                              }
                              }
                            }

                          }
                        }

                        if(uno[2] == 1)
                        {
                          if(calledUno[2] == 0)
                          {
                            if(buffer[0] == 'C')
                            {
                              write(6, "Uno challenged, draw 2 cards", strlen("Uno challenged, draw 2 cards"));
                              for(int d = 0; d < 2; i++)
                              {
                              bool draw = false;
                              while(draw = false)
                              {
                                int card = rand() % 108
                                if(taken[card] !=1)
                                {
                                  hand6[card] == 1;
                                  taken[card] == 1;
                                  bool fulldeck = true;
                                for(int r = 0; r < 108; r++)
                                {
                                  if(taken[r] == 0)
                                  {
                                    fulldeck = false;
                                  }
                                }
                                if(fulldeck = true)
                                {
                                  for(int r = 0; r < 108, r++)
                                  {
                                    taken[r] = 0;
                                    if(hand4[r] = 1 ||hand5[r] = 1 ||hand6[r] = 1 ||hand7[r] = 1)
                                    {
                                      taken[r] = 1;
                                    }
                                  }
                                }
                                draw = true;
                                }
                              }
                              }
                            }

                          }
                        }

                        if(uno[3] == 1)
                        {
                          if(calledUno[3] == 0)
                          {
                            if(buffer[0] == 'C')
                            {
                              write(7, "Uno challenged, draw 2 cards", strlen("Uno challenged, draw 2 cards"));
                              for(int d = 0; d < 2; i++)
                              {
                              bool draw = false;
                              while(draw = false)
                              {
                                int card = rand() % 108
                                if(taken[card] !=1)
                                {
                                  hand7[card] == 1;
                                  taken[card] == 1;
                                  bool fulldeck = true;
                                for(int r = 0; r < 108; r++)
                                {
                                  if(taken[r] == 0)
                                  {
                                    fulldeck = false;
                                  }
                                }
                                if(fulldeck = true)
                                {
                                  for(int r = 0; r < 108, r++)
                                  {
                                    taken[r] = 0;
                                    if(hand4[r] = 1 ||hand5[r] = 1 ||hand6[r] = 1 ||hand7[r] = 1)
                                    {
                                      taken[r] = 1;
                                    }
                                  }
                                }
                                draw = true;
                                }
                              }
                              }
                            }

                          }
                        }
                        
                        for(int a = 0; a < 108; a++)
                        {
                          if(hand4[a] == 1 && taken[a] == 1)
                          {
                            if(cards[a][0] == topcard[0] && cards[a][1] == topcard[1])
                            playable = true;
                          }
                        }
                        if (playable == true)
                        {
                          if(buffer[0] == 'G' ||buffer[0] == 'Y' ||buffer[0] == 'B' ||buffer[0] == 'R')
                          {
                            if(buffer[1] == '0' ||buffer[1] == '1' ||buffer[1] == '2' ||buffer[1] == '3' ||buffer[1] == '4' ||buffer[1] == '5' ||buffer[1] == '6' ||buffer[1] == '7' ||buffer[1] == '8' ||buffer[1] == '9' ||)
                            for(int a = 0; a < 108; a++)
                            {
                              if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                              {
                                if(hand4[a] == 1)
                                {
                                  hand4[a] == 0;
                                  char play[MAXLINE] = "Player 1 played: ";
                                  strncat(play, &cards[a][0], 1);
                                  strncat(play, &cards[a][1], 1);
                                  sprintf(play, "\n", 2);
                                  for(int c = 4; c <= 7 i++)
                                  {
                                    write(c, play, strlen(play));
                                  }
                                  topcard[0] = buffer[0];
                                  topcard[1] = buffer[1];
                                  4cc--;
                                  if(4cc = 1)
                                  {
                                    uno[0] = 1;
                                  }
                                  if(4cc = 0)
                                  {
                                    for(int c = 4; c <= 7 i++)
                                    {
                                    write(c, "Player 1 wins!", strlen("Player 1 wins!"));
                                    close(c);
                                    FD_CLR(c, &active_fd_set);
                                    return 1;
                                    }
                                  }
                                }
                              }
                            }
                          )


                          }
                        }
                        else
                        {
                          for(int c = 4; c <= 7 i++)
                          {
                          write(c, "Player 1 draws", strlen("Player 1 draws"));
                          while(draw = false)
                            {
                              int card = rand() % 108
                              if(taken[card] !=1)
                              {
                                hand4[card] == 1;
                                taken[card] == 1;
                                bool fulldeck = true;
                                for(int r = 0; r < 108; r++)
                                {
                                  if(taken[r] == 0)
                                  {
                                    fulldeck = false;
                                  }
                                }
                                if(fulldeck = true)
                                {
                                  for(int r = 0; r < 108, r++)
                                  {
                                    taken[r] = 0;
                                    if(hand4[r] = 1 ||hand5[r] = 1 ||hand6[r] = 1 ||hand7[r] = 1)
                                    {
                                      taken[r] = 1;
                                    }
                                  }
                                }
                                draw = true;
                              }
                            }
                            
                          }
                        }
                        

                      
                    }
                    
                  }

            
              }
              if(j == i && j >= 4)
              {
                if(!FD_ISSET(7, &active_fd_set))
                {
                write(j, "waiting for players\n", strlen("waiting for players\n"));
                }
              }

             }
            }
            
            
            
          }
          
          
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
  //       

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
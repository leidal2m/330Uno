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
#include <sstream>
#include <time.h>

/* Use port number 0 so that we can dynamically assign an unused
 * port number. */
#define PORTNUM         0

#define MAXLINE 512

using namespace std;

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
  char *stat;
  size_t statlength;
  
  pid_t fork_return;
  char topcard[2];
  char cards[108][2] = {
                  'R', '0',
                  'R', '1',
                  'R', '1',
                  'R', '2',
                  'R', '2',
                  'R', '3',
                  'R', '3',
                  'R', '4',
                  'R', '4',
                  'R', '5',
                  'R', '5',
                  'R', '6',
                  'R', '6',
                  'R', '7',
                  'R', '7',
                  'R', '8',
                  'R', '8',
                  'R', '9',
                  'R', '9',
                  'R', 'S',
                  'R', 'S',
                  'R', 'T',
                  'R', 'T',
                  'R', '+',
                  'R', '+',
                  'W', 'C',
                  'D', '4',
                  'Y', '0',
                  'Y', '1',
                  'Y', '1',
                  'Y', '2',
                  'Y', '2',
                  'Y', '3',
                  'Y', '3',
                  'Y', '4',
                  'Y', '4',
                  'Y', '5',
                  'Y', '5',
                  'Y', '6',
                  'Y', '6',
                  'Y', '7',
                  'Y', '7',
                  'Y', '8',
                  'Y', '8',
                  'Y', '9',
                  'Y', '9',
                  'Y', 'S',
                  'Y', 'S',
                  'Y', 'T',
                  'Y', 'T',
                  'Y', '+',
                  'Y', '+',
                  'W', 'C',
                  'D', '4',
                  'G', '0',
                  'G', '1',
                  'G', '1',
                  'G', '2',
                  'G', '2',
                  'G', '3',
                  'G', '3',
                  'G', '4',
                  'G', '4',
                  'G', '5',
                  'G', '5',
                  'G', '6',
                  'G', '6',
                  'G', '7',
                  'G', '7',
                  'G', '8',
                  'G', '8',
                  'G', '9',
                  'G', '9',
                  'G', 'S',
                  'G', 'S',
                  'G', 'T',
                  'G', 'T',
                  'G', '+',
                  'G', '+',
                  'W', 'C',
                  'D', '4',
                  'B', '0',
                  'B', '1',
                  'B', '1',
                  'B', '2',
                  'B', '2',
                  'B', '3',
                  'B', '3',
                  'B', '4',
                  'B', '4',
                  'B', '5',
                  'B', '5',
                  'B', '6',
                  'B', '6',
                  'B', '7',
                  'B', '7',
                  'B', '8',
                  'B', '8',
                  'B', '9',
                  'B', '9',
                  'B', 'S',
                  'B', 'S',
                  'B', 'T',
                  'B', 'T',
                  'B', '+',
                  'B', '+',
                  'W', 'C',
                  'D', '4',                  
                };
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
    while(draw == false)
    {
      srand(time(NULL));
      int card = rand() % 108;
      if(taken[card] !=1)
      {
        hand4[card] = 1;
        taken[card] = 1;
        draw = true;
      }
    }
  }

  for(int i = 0; i < 7; i++)
  {
    bool draw = false;
    while(draw == false)
    {
      srand(time(NULL));
      int card = rand() % 108;
      if(taken[card] !=1)
      {
        hand5[card] = 1;
        taken[card] = 1;
        draw = true;
      }
    }
  }

  for(int i = 0; i < 7; i++)
  {
    bool draw = false;
    while(draw == false)
    {
      srand(time(NULL));
      int card = rand() % 108;
      if(taken[card] !=1)
      {
        hand6[card] = 1;
        taken[card] = 1;
        draw = true;
      }
    }
  }

  for(int i = 0; i < 7; i++)
  {
    bool draw = false;
    while(draw == false)
    {
      srand(time(NULL));
      int card = rand() % 108;
      if(taken[card] !=1)
      {
        hand7[card] = 1;
        taken[card] = 1;
        draw = true;
      }
    }
  }

  for(int i = 0; i < 7; i++)
  {
    bool draw = false;
    while(draw == false)
    {
      srand(time(NULL));
      int card = rand() % 108;
      if(cards[card][0] == 'D')
      {
        draw = false;
      }
      else if(cards[card][0] == 'W')
      {
        draw = false;
      }
      else if(taken[card] !=1)
      {
        topcard[0] = cards[card][0];
        topcard[1] = cards[card][1];
        taken[card] = 1;
        draw = true;
      }
    }
  }

  printf("Top card selected is %c%c\n", topcard[0], topcard[1]);


  int fourCardCount = 7;
  char fourCardCharacter[2];
  int fiveCardCount = 7;
  char fiveCardCharacter[2];
  int sixCardCount = 7;
  char sixCardCharacter[2];
  int sevenCardCount = 7;
  char sevenCardCharacter[2];
  string givestatus;
  ostringstream ss;
  string countstring;
  bool draw2 = false;
  bool skip = false;
  bool draw4 = false;
  bool flip = false;

  int uno[4] = {0, 0, 0, 0};
  int calledUno[4] = {0, 0, 0, 0};
  bool playable = false;
  int turn = 4;


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
  

  turn = 4;

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
          int bytes;
          char status1[] = "player 1 currently has";
          char status2[] = "player 2 currently has";
          char status3[] = "player 3 currently has";
          char status4[] = "player 4 currently has";
          char statusHand[] = "You currently have";
          memset(buffer, 0, MAXLINE);
          
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
                  if( j == 0 || j >= 4)
                  {
                    if(FD_ISSET(7, &active_fd_set))
                    {
                        if(turn == 4)
                        {
                          write(4, "It's your turn Player 1\n", strlen("It's your turn Player 1\n"));

                          ss.str(string());

                          ss <<  fiveCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status2);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(4, stat, statlength);

                          ss.str(string());

                          ss << sixCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status3);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(4, stat, statlength);

                          ss.str(string());

                          ss << sevenCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status4);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(4, stat, statlength);

                          ss.str(string());

                          ss << fourCardCount;
                          
                          givestatus.clear();
                          givestatus.append(statusHand);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(4, stat, statlength);

                          //DISPLAY TOP CARD
                          ss.str(string());

                          ss << "Top card:" << topcard[0] << topcard[1] << endl;
                          givestatus.clear();
                          givestatus.append(ss.str());
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                         

                          for(int o = 4; o <= 7; o++)
                          {
                             write(o, stat, statlength);
                          }


                          for(int a = 0; a < 108; a++)
                          {
                            if(hand4[a] == 1 && taken[a] == 1)
                            {
                              if(topcard[0] == cards[a][0])
                              {
                                playable = true;
                              }
                              if(topcard[1] == cards[a][1])
                              {
                                playable = true;
                              }
                              if(cards[a][0] == 'D')
                              {
                                playable = true;
                              }
                              if(cards[a][0] == 'W')
                              {
                                playable = true;
                              }

                            }
                          }
                          if(draw2 == true)
                          {
                            write(4, "You must draw 2\n", strlen("You must draw 2\n"));
                          }
                          else if(draw4 == true)
                          {
                            write(4, "You must draw 4\n", strlen("You must draw 4\n"));
                          }
                          else if(skip == true)
                          {
                            write(4, "Your turn has been skipped\n", strlen("Your turn has been skipped\n"));
                          }
                          else if(playable == true)
                          {
                            write(4, "This is a playable hand\n", strlen("This is a playable hand\n"));
                          }

                          else if(playable == false)
                          {
                            write(4, "This is NOT a playable hand\n", strlen("This is NOT a playable hand\n"));
                          }


                          const char* fourHand = "Your hand: \n";


                          
                          while(turn == 4)
                          {
                            char club[MAXLINE];

                            givestatus.clear();
                            ss.str(string());
                            for(int b = 0; b < 108; b++)
                            {
                              if(hand4[b] == 1 && taken[b] == 1)
                              {
                                ss.str(string());
                                ss << cards[b][0] << cards[b][1] << " ";
                                givestatus.append(ss.str());
                              }
                            }
                            givestatus.append("\n");
                            stat = new char[givestatus.length() + 1];
                            strcpy(stat, givestatus.c_str());
                            statlength = givestatus.length();
                            write(4, stat, statlength);
                           //stat = new char[fourHand.length() + 1];
                           // statlength = fourHand.length() + 1;
                            //write(4, stat, statlength);

                            memset(buffer, 0, MAXLINE);
          
                            bytes = read(turn,buffer,MAXLINE);



                            if(uno[0] == 1)
                            {
                              if(calledUno[0] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[0] = 0;
                                  write(4, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        fourCardCount++;
                                        hand4[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[0] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 1 called uno!\n", strlen("Player 1 called uno!\n"));
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
                                  uno[1] = 0;
                                  write(5, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        fiveCardCount++;
                                        hand5[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[1] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 2 called uno!", strlen("Player 2 called uno!"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[2] == 1)
                            {
                              if(calledUno[2] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[2] = 0;
                                  write(6, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        sixCardCount++;
                                        hand6[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[2] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 3 called uno!\n", strlen("Player 3 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[3] == 1)
                            {
                              if(calledUno[3] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[3] = 0;
                                  write(7, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        sevenCardCount++;
                                        hand7[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                    memset(buffer, 0, MAXLINE);
          
                                    bytes = read(turn,buffer,MAXLINE);
                                  }
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[3] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 4 called uno!\n", strlen("Player 4 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }
                            

                            if (draw2 == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 1 draws 2\n", strlen("Player 1 draws 2\n"));
                              }
                              for(int z = 0; z < 2; z++)
                                {
                                  bool draw = false;
                                  while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      fourCardCount++;
                                      hand4[card] = 1;
                                      taken[card] = 1;
                                      bool fulldeck = true;
                                      for(int r = 0; r < 108; r++)
                                      {
                                        if(taken[r] == 0)
                                        {
                                          fulldeck = false;
                                        }
                                      }
                                      if(fulldeck == true)
                                      {
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                          {
                                            taken[r] = 1;
                                          }
                                        }
                                      }
                                      draw = true;
                                    }
                                  }

                                }
  
                              draw2 = false;

                            }
                            else if(draw4 == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 1 draws 4\n", strlen("Player 1 draws 4\n"));
                              }
                              for(int z = 0; z < 4; z++)
                                {
                                  bool draw = false;
                                  while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      fourCardCount++;
                                      hand4[card] = 1;
                                      taken[card] = 1;
                                      bool fulldeck = true;
                                      for(int r = 0; r < 108; r++)
                                      {
                                        if(taken[r] == 0)
                                        {
                                          fulldeck = false;
                                        }
                                      }
                                      if(fulldeck == true)
                                      {
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                          {
                                            taken[r] = 1;
                                          }
                                        }
                                      }
                                      draw = true;
                                    }
                                  }

                                }
                              
                              draw4 = false;

                            }
                            else if(skip == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 1 turn skipped\n", strlen("Player 1 turn skipped\n"));
                              }
                              skip = false;

                            } 
                            else if (playable == true)
                            {                                  
                              if(buffer[0] == 'G' || buffer[0] == 'Y' || buffer[0] == 'B' || buffer[0] == 'R')
                              {
                                if(buffer[1] == '0' || buffer[1] == '1' || buffer[1] == '2' || buffer[1] == '3' || buffer[1] == '4' || buffer[1] == '5' || buffer[1] == '6' || buffer[1] == '7' || buffer[1] == '8' || buffer[1] == '9')
                                {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand4[a] == 1)
                                        {
                                          hand4[a] = 0;


                                          ss.str(string());

                                          ss << "Player 1 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          fourCardCount--;
                                          if(fourCardCount == 1)
                                          {
                                            uno[0] = 1;
                                          }
                                          if(fourCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 1 wins!\n", strlen("Player 1 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                        }
                                      }
                                      else
                                      {
                                        write(4, "invalid move\n", strlen("invalid move\n"));
                                      }
                                    }
                                  }
                                }
                                else if(buffer[1] == '+')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand4[a] == 1)
                                        {
                                          hand4[a] = 0;
                                          ss.str(string());

                                          ss << "Player 1 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          fourCardCount--;
                                          if(fourCardCount == 1)
                                          {
                                            uno[0] = 1;
                                          }
                                          if(fourCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 1 wins!\n", strlen("Player 1 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                            
                                          }
                                          draw2 = true;
                                        }  
                                      }
                                      else
                                      {
                                        write(4, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                else if(buffer[1] == 'T')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand4[a] == 1)
                                        {
                                          hand4[a] = 0;
                                          ss.str(string());

                                          ss << "Player 1 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          fourCardCount--;
                                          if(fourCardCount == 1)
                                          {
                                            uno[0] = 1;
                                          }
                                          if(fourCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 1 wins!\n", strlen("Player 1 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                      
                                          if(flip == true)
                                          {
                                            flip = false;
                                          }
                                          else
                                          {
                                            flip = true;
                                          }
                                          
                                          
                                        }
                                      }
                                      else
                                      {
                                        write(4, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                else if(buffer[1] == 'S')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand4[a] == 1)
                                        {
                                          hand4[a] = 0;
                                          ss.str(string());

                                          ss << "Player 1 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          fourCardCount--;
                                          if(fourCardCount == 1)
                                          {
                                            uno[0] = 1;
                                          }
                                          if(fourCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 1 wins!\n", strlen("Player 1 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          skip = true;
                                        }
                                      }
                                      else
                                      {
                                        write(4, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                }
                                else if(buffer[0] == 'D')
                                {
                                  if(buffer[1] == '4')
                                  {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(hand4[a] == 1)
                                      {

                                        hand4[a] = 0;
                                          ss.str(string());

                                          ss << "Player 1 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                        bool pick = false;
                                        while(pick == false)
                                        {
                                            write(4, "pick a color\n", strlen("pick a color\n"));
                                            memset(buffer, 0, MAXLINE);
                                            bytes = read(4, buffer, MAXLINE);
                                            if (buffer[0] == 'R' ||buffer[0] == 'G' ||buffer[0] == 'B' ||buffer[0] == 'Y')
                                            {
                                              topcard[0] = buffer[0];
                                              for(int p = 4; p < 7; p++)
                                              {
                                                if(topcard[0] == 'R')
                                                {
                                                  write(p, "the new color is R\n", strlen("the new color is R\n"));
                                                }
                                                if(topcard[0] == 'G')
                                                {
                                                  write(p, "the new color is G\n", strlen("the new color is G\n"));
                                                }
                                                if(topcard[0] == 'B')
                                                {
                                                  write(p, "the new color is B\n", strlen("the new color is B\n"));
                                                }
                                                if(topcard[0] == 'Y')
                                                {
                                                  write(p, "the new color is Y\n", strlen("the new color is Y\n"));
                                                }
                                              }
                                              pick = true;
                                            }
                                        }
                                        fourCardCount--;
                                        if(fourCardCount == 1)
                                        {
                                          uno[0] = 1;
                                        }
                                        if(fourCardCount == 0)
                                        {
                                          for(int c = 4; c <= 7; c++)
                                          {
                                          write(c, "Player 1 wins!\n", strlen("Player 1 wins!\n"));
                                          }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                          return 1;
                                          
                                        }
                                        draw4 = true;
                                      }
                                    }
                                  }
                                  draw4 = true;
                                }
                              }
                              else if(buffer[0] == 'W')
                              {
                                if(buffer[1] == 'C')
                                {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(hand4[a] == 1)
                                      {

                                        hand4[a] = 0;
                                          ss.str(string());

                                          ss << "Player 1 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                        bool pick = false;
                                        while(pick == false)
                                        {
                                            write(4, "pick a color\n", strlen("pick a color\n"));
                                            memset(buffer, 0, MAXLINE);
                                            bytes = read(4, buffer, MAXLINE);
                                            if (buffer[0] == 'R' ||buffer[0] == 'G' ||buffer[0] == 'B' ||buffer[0] == 'Y')
                                            {
                                              topcard[0] = buffer[0];
                                              for(int p = 4; p < 7; p++)
                                              {
                                                if(topcard[0] == 'R')
                                                {
                                                  write(p, "the new color is R\n", strlen("the new color is R\n"));
                                                }
                                                if(topcard[0] == 'G')
                                                {
                                                  write(p, "the new color is G\n", strlen("the new color is G\n"));
                                                }
                                                if(topcard[0] == 'B')
                                                {
                                                  write(p, "the new color is B\n", strlen("the new color is B\n"));
                                                }
                                                if(topcard[0] == 'Y')
                                                {
                                                  write(p, "the new color is Y\n", strlen("the new color is Y\n"));
                                                }
                                              }
                                              pick = true;
                                            }
                                          
                                        }
                                        fourCardCount--;
                                        if(fourCardCount == 1)
                                        {
                                          uno[0] = 1;
                                        }
                                        if(fourCardCount == 0)
                                        {
                                          for(int c = 4; c <= 7; c++)
                                          {
                                          write(c, "Player 1 wins!\n", strlen("Player 1 wins!\n"));
                                          }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                          return 1;
                                          
                                        }
                                      }
                                    }
                                  }
                                  
                                }
                              }
                              else if(buffer[0] == '\n')
                              {
                                for(int c = 4; c <= 7; c++)
                                {
                                write(c, "no play available Player 1 draws\n", strlen("no play available Player 1 draws\n"));
                                }
                                bool draw = false;
                                while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      fourCardCount++;
                                      hand4[card] = 1;
                                      taken[card] = 1;
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
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
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
                            else
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                              write(c, "no play available Player 1 draws\n", strlen("no play available Player 1 draws\n"));
                              }
                              bool draw = false;
                              while(draw == false)
                                {
                                  srand(time(NULL));
                                  int card = rand() % 108;
                                  if(taken[card] !=1)
                                  {
                                    fourCardCount++;
                                    hand4[card] = 1;
                                    taken[card] = 1;
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
                                      for(int r = 0; r < 108; r++)
                                      {
                                        taken[r] = 0;
                                        if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                        {
                                          taken[r] = 1;
                                        }
                                      }
                                    }
                                    draw = true;
                                  }
                                }
                                
                              
                            }
                          
                          if(flip == true)
                          {
                            turn--;
                            if(turn < 4)
                            {
                              turn = 7;
                            }
                          }
                          else
                          {
                            turn++;
                            
                          }

                          for (int t = 4; t <=7; t++)
                          {
                            write(t, "Player 1: end of turn\n", strlen("Player 1: end of turn\n"));
                          }
                          playable = false;
                          
                        }
                          

                        }

                        if(turn == 5)
                        {
                          write(5, "It's your turn Player 2\n", strlen("It's your turn Player 2\n"));
                          ss.str(string());

                          ss <<  fourCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status1);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(5, stat, statlength);

                          ss.str(string());

                          ss << sixCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status3);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(5, stat, statlength);

                          ss.str(string());

                          ss << sevenCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status4);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(5, stat, statlength);

                          ss.str(string());

                          ss << fiveCardCount;
                          
                          givestatus.clear();
                          givestatus.append(statusHand);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(5, stat, statlength);

                          //DISPLAY TOP CARD
                          ss.str(string());

                          ss << "Top card:" << topcard[0] << topcard[1] << endl;
                          givestatus.clear();
                          givestatus.append(ss.str());
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                         

                          for(int o = 4; o <= 7; o++)
                          {
                             write(o, stat, statlength);
                          }


                          for(int a = 0; a < 108; a++)
                          {
                            if(hand5[a] == 1 && taken[a] == 1)
                            {
                              if(topcard[0] == cards[a][0])
                              {
                                playable = true;
                              }
                              if(topcard[1] == cards[a][1])
                              {
                                playable = true;
                              }
                              if(cards[a][0] == 'D')
                              {
                                playable = true;
                              }
                              if(cards[a][0] == 'W')
                              {
                                playable = true;
                              }
                            }
                          }

                          if(draw2 == true)
                          {
                            write(5, "You must draw 2\n", strlen("You must draw 2\n"));
                          }
                          else if(draw4 == true)
                          {
                            write(5, "You must draw 4\n", strlen("You must draw 4\n"));
                          }
                          else if(skip == true)
                          {
                            write(5, "Your turn has been skipped\n", strlen("Your turn has been skipped\n"));
                          }
                          else if(playable == true)
                          {
                            write(5, "This is a playable hand\n", strlen("This is a playable hand\n"));
                          }

                          else if(playable == false)
                          {
                            write(5, "This is NOT a playable hand\n", strlen("This is NOT a playable hand\n"));
                          }


                          const char* fourHand = "Your hand: \n";


                          
                          while(turn == 5)
                          {
 
                            char club[MAXLINE];

                            givestatus.clear();
                            ss.str(string());
                            for(int b = 0; b < 108; b++)
                            {
                              if(hand5[b] == 1 && taken[b] == 1)
                              {
                                ss.str(string());
                                ss << cards[b][0] << cards[b][1] << " ";
                                givestatus.append(ss.str());
                              }
                            }
                            givestatus.append("\n");
                            stat = new char[givestatus.length() + 1];
                            strcpy(stat, givestatus.c_str());
                            statlength = givestatus.length();
                            write(5, stat, statlength);
                           //stat = new char[fourHand.length() + 1];
                           // statlength = fourHand.length() + 1;
                            //write(5, stat, statlength);

                            memset(buffer, 0, MAXLINE);
          
                            bytes = read(turn,buffer,MAXLINE);




                            if(buffer [0] == 'Z')
                            {
                              write(5, "This is a test\n", strlen("This is a test\n"));
                            }
                            if(buffer [1] == 'N')
                            {
                              write(5, "another test\n", strlen("another test\n"));
                            }


                            if(uno[0] == 1)
                            {
                              if(calledUno[0] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[0] = 0;
                                  write(4, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        fourCardCount++;
                                        hand4[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[0] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 1 called uno!\n", strlen("Player 1 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[1] == 1)
                            {
                              if(calledUno[1] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[1] = 0;
                                  write(5, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        fiveCardCount++;
                                        hand5[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[1] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 2 called uno!\n", strlen("Player 2 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[2] == 1)
                            {
                              if(calledUno[2] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[2] = 0;
                                  write(6, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        sixCardCount++;
                                        hand6[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[2] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 3 called uno!\n", strlen("Player 3 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[3] == 1)
                            {
                              if(calledUno[3] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[3] = 0;
                                  write(7, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        sevenCardCount++;
                                        hand7[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[3] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 4 called uno!\n", strlen("Player 4 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }


                            if (draw2 == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 2 draws 2\n", strlen("Player 2 draws 2\n"));
                              }
                              for(int z = 0; z < 2; z++)
                                {
                                  bool draw = false;
                                  while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      fiveCardCount++;
                                      hand5[card] = 1;
                                      taken[card] = 1;
                                      bool fulldeck = true;
                                      for(int r = 0; r < 108; r++)
                                      {
                                        if(taken[r] == 0)
                                        {
                                          fulldeck = false;
                                        }
                                      }
                                      if(fulldeck == true)
                                      {
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                          {
                                            taken[r] = 1;
                                          }
                                        }
                                      }
                                      draw = true;
                                    }
                                  }
                              }
                              draw2 = false;

                            }
                            else if(draw4 == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 2 draws 4\n", strlen("Player 2 draws 4\n"));
                              }
                              for(int z = 0; z < 4; z++)
                                {
                                  bool draw = false;
                                  while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      fiveCardCount++;
                                      hand5[card] = 1;
                                      taken[card] = 1;
                                      bool fulldeck = true;
                                      for(int r = 0; r < 108; r++)
                                      {
                                        if(taken[r] == 0)
                                        {
                                          fulldeck = false;
                                        }
                                      }
                                      if(fulldeck == true)
                                      {
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                          {
                                            taken[r] = 1;
                                          }
                                        }
                                      }
                                      draw = true;
                                    }
                                  }

                                }
                              draw4 = false;

                            }
                            else if(skip == true)
                            {
                                for(int c = 4; c <= 7; c++)
                                {
                                  write(c, "Player 2 turn skipped\n", strlen("Player 2 turn skipped\n"));
                                }
                                skip = false;

                            }   
                            else if (playable == true)
                            {
                          
                              if(buffer[0] == 'G' || buffer[0] == 'Y' || buffer[0] == 'B' || buffer[0] == 'R')
                              {
                                if(buffer[1] == '0' || buffer[1] == '1' || buffer[1] == '2' || buffer[1] == '3' || buffer[1] == '4' || buffer[1] == '5' || buffer[1] == '6' || buffer[1] == '7' || buffer[1] == '8' || buffer[1] == '9')
                                {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand5[a] == 1)
                                        {
                                          hand5[a] = 0;
                                          ss.str(string());

                                          ss << "Player 2 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          fiveCardCount--;
                                          if(fiveCardCount == 1)
                                          {
                                            uno[1] = 1;
                                          }
                                          if(fiveCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 2 wins!\n", strlen("Player 2 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                        }
                                      }
                                      else
                                      {
                                        write(5, "invalid move\n", strlen("invalid move\n"));
                                      }
                                    }
                                  }
                                }
                                else if(buffer[1] == '+')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand5[a] == 1)
                                        {
                                          hand5[a] = 0;
                                          ss.str(string());

                                          ss << "Player 2 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          fiveCardCount--;
                                          if(fiveCardCount == 1)
                                          {
                                            uno[1] = 1;
                                          }
                                          if(fiveCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 2 wins!\n", strlen("Player 2 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          draw2 = true;
                                        }
                                      }
                                      else
                                      {
                                        write(5, "invalid move\n", strlen("invalid move\n"));
                                      }
                                    }
                                  }
                                }
                                else if(buffer[1] == 'T')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand5[a] == 1)
                                        {
                                          hand5[a] = 0;
                                          ss.str(string());
                                          ss << "Player 2 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          fiveCardCount--;
                                          if(fiveCardCount == 1)
                                          {
                                            uno[1] = 1;
                                          }
                                          if(fiveCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 2 wins!\n", strlen("Player 2 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          if(flip == true)
                                          {
                                            flip = false;
                                          }
                                          else
                                          {
                                            flip = true;
                                          }
                                          
                                          
                                        }
                                      }
                                      else
                                      {
                                        write(5, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                else if(buffer[1] == 'S')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand5[a] == 1)
                                        {
                                          hand5[a] = 0;
                                          ss.str(string());
                                          ss << "Player 2 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          fiveCardCount--;
                                          if(fiveCardCount == 1)
                                          {
                                            uno[1] = 1;
                                          }
                                          if(fiveCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 2 wins!\n", strlen("Player 2 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          skip = true;
                                        }
                                      }
                                      else
                                      {
                                        write(5, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                }
                                else if(buffer[0] == 'D')
                                {
                                  if(buffer[1] == '4')
                                  {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(hand5[a] == 1)
                                      {

                                        hand5[a] = 0;
                                          ss.str(string());
                                          ss << "Player 2 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                        bool pick = false;
                                        while(pick == false)
                                        {
                                            write(5, "pick a color\n", strlen("pick a color\n"));
                                            memset(buffer, 0, MAXLINE);
                                            bytes = read(5, buffer, MAXLINE);
                                            if (buffer[0] == 'R' ||buffer[0] == 'G' ||buffer[0] == 'B' ||buffer[0] == 'Y')
                                            {
                                              topcard[0] = buffer[0];
                                              for(int p = 4; p < 7; p++)
                                              {
                                                if(topcard[0] == 'R')
                                                {
                                                  write(p, "the new color is R\n", strlen("the new color is R\n"));
                                                }
                                                if(topcard[0] == 'G')
                                                {
                                                  write(p, "the new color is G\n", strlen("the new color is G\n"));
                                                }
                                                if(topcard[0] == 'B')
                                                {
                                                  write(p, "the new color is B\n", strlen("the new color is B\n"));
                                                }
                                                if(topcard[0] == 'Y')
                                                {
                                                  write(p, "the new color is Y\n", strlen("the new color is Y\n"));
                                                }
                                              }
                                              pick = true;
                                            }
                                          
                                        }
                                        fiveCardCount--;
                                        if(fiveCardCount == 1)
                                        {
                                          uno[1] = 1;
                                        }
                                        if(fiveCardCount == 0)
                                        {
                                          for(int c = 4; c <= 7; c++)
                                          {
                                          write(c, "Player 2 wins!\n", strlen("Player 2 wins!\n"));
                                          }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                          return 1;
                                          
                                        }
                                        draw4 = true;
                                      } 
                                      
                                    }
                                  }
                                 
                                }
                              }
                              else if(buffer[0] == 'W')
                              {
                                if(buffer[1] == 'C')
                                {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(hand5[a] == 1)
                                      {

                                        hand5[a] = 0;
                                          ss.str(string());
                                          ss << "Player 2 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                        bool pick = false;
                                        while(pick == false)
                                        {
                                            write(5, "pick a color\n", strlen("pick a color\n"));
                                            memset(buffer, 0, MAXLINE);
                                            bytes = read(5, buffer, MAXLINE);
                                            if (buffer[0] == 'R' ||buffer[0] == 'G' ||buffer[0] == 'B' ||buffer[0] == 'Y')
                                            {
                                              topcard[0] = buffer[0];
                                              for(int p = 4; p < 7; p++)
                                              {
                                                if(topcard[0] == 'R')
                                                {
                                                  write(p, "the new color is R\n", strlen("the new color is R\n"));
                                                }
                                                if(topcard[0] == 'G')
                                                {
                                                  write(p, "the new color is G\n", strlen("the new color is G\n"));
                                                }
                                                if(topcard[0] == 'B')
                                                {
                                                  write(p, "the new color is B\n", strlen("the new color is B\n"));
                                                }
                                                if(topcard[0] == 'Y')
                                                {
                                                  write(p, "the new color is Y\n", strlen("the new color is Y\n"));
                                                }
                                              }
                                              pick = true;
                                            }
                                          
                                        }
                                        fiveCardCount--;
                                        if(fiveCardCount == 1)
                                        {
                                          uno[1] = 1;
                                        }
                                        if(fiveCardCount == 0)
                                        {
                                          for(int c = 4; c <= 7; c++)
                                          {
                                          write(c, "Player 2 wins!\n", strlen("Player 2 wins!\n"));
                                          }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                          return 1;
                                          
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                              else if(buffer[0] == '\n')
                              {
                                for(int c = 4; c <= 7; c++)
                                {
                                write(c, "no play available Player 2 draws\n", strlen("no play available Player 2 draws\n"));
                                }
                                bool draw = false;
                                while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      fiveCardCount++;
                                      hand5[card] = 1;
                                      taken[card] = 1;
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
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
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
                            else
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                              write(c, "no play available Player 2 draws\n", strlen("no play available Player 2 draws\n"));
                              }
                              bool draw = false;
                              while(draw == false)
                                {
                                  srand(time(NULL));
                                  int card = rand() % 108;
                                  if(taken[card] !=1)
                                  {
                                    fiveCardCount++;
                                    hand5[card] = 1;
                                    taken[card] = 1;
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
                                      for(int r = 0; r < 108; r++)
                                      {
                                        taken[r] = 0;
                                        if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                        {
                                          taken[r] = 1;
                                        }
                                      }
                                    }
                                    draw = true;
                                  }
                                }
                                
                              
                            }
                          
                          if(flip == true)
                          {
                            turn--;
                            if(turn < 4)
                            {
                              turn = 7;
                            }
                          }
                          else
                          {
                              turn++;
                              if( turn > 7)
                              {
                                  turn = 4;
                              }
                            
                            
                          }
                          for (int t = 4; t <=7; t++)
                          {
                            write(t, "Player 2: end of turn\n", strlen("Player 2: end of turn\n"));
                          }
                          playable = false;
                          
                        }
                          

                        }

                        if(turn == 6)
                        {
                          write(6, "It's your turn Player 3\n", strlen("It's your turn Player 3\n"));

                          ss.str(string());

                          ss <<  fourCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status1);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(6, stat, statlength);

                          ss.str(string());

                          ss << fiveCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status2);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(6, stat, statlength);

                          ss.str(string());

                          ss << sevenCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status4);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(6, stat, statlength);

                          ss.str(string());

                          ss << sixCardCount;
                          
                          givestatus.clear();
                          givestatus.append(statusHand);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(6, stat, statlength);

                          //DISPLAY TOP CARD
                          ss.str(string());

                          ss << "Top card:" << topcard[0] << topcard[1] << endl;
                          givestatus.clear();
                          givestatus.append(ss.str());
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                         

                          for(int o = 4; o <= 7; o++)
                          {
                             write(o, stat, statlength);
                          }


                          for(int a = 0; a < 108; a++)
                          {
                            if(hand6[a] == 1 && taken[a] == 1)
                            {
                              if(topcard[0] == cards[a][0])
                              {
                                playable = true;
                              }
                              if(topcard[1] == cards[a][1])
                              {
                                playable = true;
                              }
                              if(cards[a][0] == 'D')
                              {
                                playable = true;
                              }
                              if(cards[a][0] == 'W')
                              {
                                playable = true;
                              }
                            }
                          }
                          if(draw2 == true)
                          {
                            write(6, "You must draw 2\n", strlen("You must draw 2\n"));
                          }
                          else if(draw4 == true)
                          {
                            write(6, "You must draw 4\n", strlen("You must draw 4\n"));
                          }
                          else if(skip == true)
                          {
                            write(6, "Your turn has been skipped\n", strlen("Your turn has been skipped\n"));
                          }
                          else if(playable == true)
                          {
                            write(6, "This is a playable hand\n", strlen("This is a playable hand\n"));
                          }

                          else if(playable == false)
                          {
                            write(6, "This is NOT a playable hand\n", strlen("This is NOT a playable hand\n"));
                          }


                          const char* fourHand = "Your hand: \n";


                          
                          while(turn == 6)
                          {
                            char club[MAXLINE];

                            givestatus.clear();
                            ss.str(string());
                            for(int b = 0; b < 108; b++)
                            {
                              if(hand6[b] == 1 && taken[b] == 1)
                              {
                                ss.str(string());
                                ss << cards[b][0] << cards[b][1] << " ";
                                givestatus.append(ss.str());
                              }
                            }
                            givestatus.append("\n");
                            stat = new char[givestatus.length() + 1];
                            strcpy(stat, givestatus.c_str());
                            statlength = givestatus.length();
                            write(6, stat, statlength);
                           //stat = new char[fourHand.length() + 1];
                           // statlength = fourHand.length() + 1;
                            //write(6, stat, statlength);

                            memset(buffer, 0, MAXLINE);
          
                            bytes = read(turn,buffer,MAXLINE);




                            if(buffer [0] == 'Z')
                            {
                              write(6, "This is a test", strlen("This is a test"));
                            }
                            if(buffer [1] == 'N')
                            {
                              write(6, "another test", strlen("another test"));
                            }


                            if(uno[0] == 1)
                            {
                              if(calledUno[0] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[0] = 0;
                                  write(4, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        fourCardCount++;
                                        hand4[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[0] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 1 called uno!\n", strlen("Player 1 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[1] == 1)
                            {
                              if(calledUno[1] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[1] = 0;
                                  write(5, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        fiveCardCount++;
                                        hand5[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[1] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 2 called uno!\n", strlen("Player 2 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[2] == 1)
                            {
                              if(calledUno[2] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[2] = 0;
                                  write(6, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        sixCardCount++;
                                        hand6[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[2] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 3 called uno!\n", strlen("Player 3 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[3] == 1)
                            {
                              if(calledUno[3] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[3] = 0;
                                  write(7, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        sevenCardCount++;
                                        hand7[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[3] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 4 called uno!\n", strlen("Player 4 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }


                            if (draw2 == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 3 draws 2\n", strlen("Player 3 draws 2\n"));
                              }
                              for(int z = 0; z < 2; z++)
                                {
                                  bool draw = false;
                                  while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      sixCardCount++;
                                      hand6[card] = 1;
                                      taken[card] = 1;
                                      bool fulldeck = true;
                                      for(int r = 0; r < 108; r++)
                                      {
                                        if(taken[r] == 0)
                                        {
                                          fulldeck = false;
                                        }
                                      }
                                      if(fulldeck == true)
                                      {
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                          {
                                            taken[r] = 1;
                                          }
                                        }
                                      }
                                      draw = true;
                                    }
                                  }

                                }
                              
                              draw2 = false;

                            }
                            else if(draw4 == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 3 draws 4\n", strlen("Player 3 draws 4\n"));
                              }
                              for(int z = 0; z < 4; z++)
                                {
                                  bool draw = false;
                                  while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      sixCardCount++;
                                      hand6[card] = 1;
                                      taken[card] = 1;
                                      bool fulldeck = true;
                                      for(int r = 0; r < 108; r++)
                                      {
                                        if(taken[r] == 0)
                                        {
                                          fulldeck = false;
                                        }
                                      }
                                      if(fulldeck == true)
                                      {
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                          {
                                            taken[r] = 1;
                                          }
                                        }
                                      }
                                      draw = true;
                                    }
                                  }

                                }
                              
                              draw4 = false;

                            }  
                            else if(skip == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 3 turn skipped\n", strlen("Player 3 turn skipped\n"));
                              }
                              skip = false;

                            }           
                            else if (playable == true)
                            {      
                              if(buffer[0] == 'G' || buffer[0] == 'Y' || buffer[0] == 'B' || buffer[0] == 'R')
                              {
                                if(buffer[1] == '0' || buffer[1] == '1' || buffer[1] == '2' || buffer[1] == '3' || buffer[1] == '4' || buffer[1] == '5' || buffer[1] == '6' || buffer[1] == '7' || buffer[1] == '8' || buffer[1] == '9')
                                {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand6[a] == 1)
                                        {
                                          hand6[a] = 0;
                                          ss.str(string());
                                          ss << "Player 3 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          sixCardCount--;
                                          if(sixCardCount == 1)
                                          {
                                            uno[2] = 1;
                                          }
                                          if(sixCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 3 wins!\n", strlen("Player 3 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                        }
                                      }
                                      else
                                      {
                                        write(6, "invalid move\n", strlen("invalid move\n"));
                                      }
                                    }
                                  }
                                }
                                else if(buffer[1] == '+')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand6[a] == 1)
                                        {
                                          hand6[a] = 0;
                                          ss.str(string());
                                          ss << "Player 3 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          sixCardCount--;
                                          if(sixCardCount == 1)
                                          {
                                            uno[2] = 1;
                                          }
                                          if(sixCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 3 wins!\n", strlen("Player 3 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          draw2 = true;
                                        }
                                      }
                                      else
                                      {
                                        write(6, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                else if(buffer[1] == 'T')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand6[a] == 1)
                                        {
                                          hand6[a] = 0;
                                          ss.str(string());
                                          ss << "Player 3 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          sixCardCount--;
                                          if(sixCardCount == 1)
                                          {
                                            uno[2] = 1;
                                          }
                                          if(sixCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 3 wins!\n", strlen("Player 3 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          if(flip == true)
                                          {
                                            flip = false;
                                          }
                                          else
                                          {
                                            flip = true;
                                          }
                                          
                                          
                                        }
                                      }
                                      else
                                      {
                                        write(6, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                else if(buffer[1] == 'S')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand6[a] == 1)
                                        {
                                          hand6[a] = 0;
                                          ss.str(string());
                                          ss << "Player 3 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          sixCardCount--;
                                          if(sixCardCount == 1)
                                          {
                                            uno[2] = 1;
                                          }
                                          if(sixCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 3 wins!\n", strlen("Player 3 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          skip = true;
                                        }
                                      }
                                      else
                                      {
                                        write(6, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                }
                                else if(buffer[0] == 'D')
                                {
                                  if(buffer[1] == '4')
                                  {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(hand6[a] == 1)
                                      {

                                        hand6[a] = 0;
                                          ss.str(string());
                                          ss << "Player 3 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                        bool pick = false;
                                        while(pick == false)
                                        {
                                            write(6, "pick a color\n", strlen("pick a color\n"));
                                            memset(buffer, 0, MAXLINE);
                                            bytes = read(6, buffer, MAXLINE);
                                            if (buffer[0] == 'R' ||buffer[0] == 'G' ||buffer[0] == 'B' ||buffer[0] == 'Y')
                                            {
                                              topcard[0] = buffer[0];
                                              for(int p = 4; p < 7; p++)
                                              {
                                                if(topcard[0] == 'R')
                                                {
                                                  write(p, "the new color is R\n", strlen("the new color is R\n"));
                                                }
                                                if(topcard[0] == 'G')
                                                {
                                                  write(p, "the new color is G\n", strlen("the new color is G\n"));
                                                }
                                                if(topcard[0] == 'B')
                                                {
                                                  write(p, "the new color is B\n", strlen("the new color is B\n"));
                                                }
                                                if(topcard[0] == 'Y')
                                                {
                                                  write(p, "the new color is Y\n", strlen("the new color is Y\n"));
                                                }
                                              }
                                              pick = true;
                                            }
                                          
                                        }
                                        sixCardCount--;
                                        if(sixCardCount == 1)
                                        {
                                          uno[2] = 1;
                                        }
                                        if(sixCardCount == 0)
                                        {
                                          for(int c = 4; c <= 7; c++)
                                          {
                                          write(c, "Player 3 wins!\n", strlen("Player 3 wins!\n"));
                                          }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                          return 1;
                                          
                                        }
                                        draw4 = true;
                                      }
                                    }
                                  }
                                }
                              }
                              else if(buffer[0] == 'W')
                              {
                                if(buffer[1] == 'C')
                                {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(hand6[a] == 1)
                                      {

                                        hand6[a] = 0;
                                          ss.str(string());
                                          ss << "Player 3 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                        bool pick = false;
                                        while(pick == false)
                                        {
                                            write(6, "pick a color\n", strlen("pick a color\n"));
                                            memset(buffer, 0, MAXLINE);
                                            bytes = read(6, buffer, MAXLINE);
                                            if (buffer[0] == 'R' ||buffer[0] == 'G' ||buffer[0] == 'B' ||buffer[0] == 'Y')
                                            {
                                              topcard[0] = buffer[0];
                                              for(int p = 4; p < 7; p++)
                                              {
                                                if(topcard[0] == 'R')
                                                {
                                                  write(p, "the new color is R\n", strlen("the new color is R\n"));
                                                }
                                                if(topcard[0] == 'G')
                                                {
                                                  write(p, "the new color is G\n", strlen("the new color is G\n"));
                                                }
                                                if(topcard[0] == 'B')
                                                {
                                                  write(p, "the new color is B\n", strlen("the new color is B\n"));
                                                }
                                                if(topcard[0] == 'Y')
                                                {
                                                  write(p, "the new color is Y\n", strlen("the new color is Y\n"));
                                                }
                                              }
                                              pick = true;
                                            }
                                          
                                        }
                                        sixCardCount--;
                                        if(sixCardCount == 1)
                                        {
                                          uno[2] = 1;
                                        }
                                        if(sixCardCount == 0)
                                        {
                                          for(int c = 4; c <= 7; c++)
                                          {
                                          write(c, "Player 3 wins!\n", strlen("Player 3 wins!\n"));
                                          }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                          return 1;
                                          
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                              else if(buffer[0] == '\n')
                              {
                                for(int c = 4; c <= 7; c++)
                                {
                                write(c, "no play available Player 3 draws\n", strlen("no play available Player 3 draws\n"));
                                }
                                bool draw = false;
                                while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      sixCardCount++;
                                      hand6[card] = 1;
                                      taken[card] = 1;
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
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
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
                            else
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                              write(c, "no play available Player 3 draws\n", strlen("no play available Player 3 draws\n"));
                              }
                              bool draw = false;
                              while(draw == false)
                                {
                                  srand(time(NULL));
                                  int card = rand() % 108;
                                  if(taken[card] !=1)
                                  {
                                    sixCardCount++;
                                    hand6[card] = 1;
                                    taken[card] = 1;
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
                                      for(int r = 0; r < 108; r++)
                                      {
                                        taken[r] = 0;
                                        if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                        {
                                          taken[r] = 1;
                                        }
                                      }
                                    }
                                    draw = true;
                                  }
                                }
                                
                              
                            }
                          
                          if(flip == true)
                          {
                            turn--;
                            if(turn < 4)
                            {
                              turn = 7;
                            }
                          }
                          else
                          {
                              turn++;
                              if( turn > 7)
                              {
                                  turn = 4;
                              }
                            
                            
                          }

                          for (int t = 4; t <=7; t++)
                          {
                            write(t, "Player 3: end of turn\n", strlen("Player 2: end of turn\n"));
                          }
                          playable = false;
                          
                        }
                          

                        }

                        if(turn == 7)
                        {
                          write(7, "It's your turn Player 4\n", strlen("It's your turn Player 4\n"));

                          ss.str(string());

                          ss <<  fourCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status1);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(7, stat, statlength);

                          ss.str(string());

                          ss << fiveCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status2);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(7, stat, statlength);

                          ss.str(string());

                          ss << sixCardCount;
                          
                          givestatus.clear();
                          givestatus.append(status3);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(7, stat, statlength);

                          ss.str(string());

                          ss << sevenCardCount;
                          
                          givestatus.clear();
                          givestatus.append(statusHand);
                          givestatus.append(" ");
                          givestatus.append(ss.str());
                          givestatus.append(" cards\n");
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                          write(7, stat, statlength);

                          //DISPLAY TOP CARD
                          ss.str(string());

                          ss << "Top card:" << topcard[0] << topcard[1] << endl;
                          givestatus.clear();
                          givestatus.append(ss.str());
                          stat = new char[givestatus.length() + 1];
                          strcpy(stat, givestatus.c_str());
                          statlength = givestatus.length();
                         

                          for(int o = 4; o <= 7; o++)
                          {
                             write(o, stat, statlength);
                          }


                          for(int a = 0; a < 108; a++)
                          {
                            if(hand7[a] == 1 && taken[a] == 1)
                            {
                              if(topcard[0] == cards[a][0])
                              {
                                playable = true;
                              }
                              if(topcard[1] == cards[a][1])
                              {
                                playable = true;
                              }
                              if(cards[a][0] == 'D')
                              {
                                playable = true;
                              }
                              if(cards[a][0] == 'W')
                              {
                                playable = true;
                              }
                            }
                          }
                          if(draw2 == true)
                          {
                            write(7, "You must draw 2\n", strlen("You must draw 2\n"));
                          }
                          else if(draw4 == true)
                          {
                            write(7, "You must draw 4\n", strlen("You must draw 4\n"));
                          }
                          else if(skip == true)
                          {
                            write(7, "Your turn has been skipped\n", strlen("Your turn has been skipped\n"));
                          }
                          else if(playable == true)
                          {
                            write(7, "This is a playable hand\n", strlen("This is a playable hand\n"));
                          }

                          else if(playable == false)
                          {
                            write(7, "This is NOT a playable hand\n", strlen("This is NOT a playable hand\n"));
                          }


                          const char* fourHand = "Your hand: \n";


                          
                          while(turn == 7)
                          {
                            char club[MAXLINE];

                            givestatus.clear();
                            ss.str(string());
                            for(int b = 0; b < 108; b++)
                            {
                              if(hand7[b] == 1 && taken[b] == 1)
                              {
                                ss.str(string());
                                ss << cards[b][0] << cards[b][1] << " ";
                                givestatus.append(ss.str());
                              }
                            }
                            givestatus.append("\n");
                            stat = new char[givestatus.length() + 1];
                            strcpy(stat, givestatus.c_str());
                            statlength = givestatus.length();
                            write(7, stat, statlength);
                           //stat = new char[fourHand.length() + 1];
                           // statlength = fourHand.length() + 1;
                            //write(7, stat, statlength);

                            memset(buffer, 0, MAXLINE);
          
                            bytes = read(turn,buffer,MAXLINE);




                            if(buffer [0] == 'Z')
                            {
                              write(7, "This is a test", strlen("This is a test"));
                            }
                            if(buffer [1] == 'N')
                            {
                              write(7, "another test", strlen("another test"));
                            }


                            if(uno[0] == 1)
                            {
                              if(calledUno[0] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[0] = 0;
                                  write(4, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        fourCardCount++;
                                        hand4[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[0] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 1 called uno!\n", strlen("Player 1 called uno!\n"));
                                  }
                                }
                                memset(buffer, 0, MAXLINE);
          
                                bytes = read(turn,buffer,MAXLINE);

                              }
                            }

                            if(uno[1] == 1)
                            {
                              if(calledUno[1] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[1] = 0;
                                  write(5, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  uno[1] = 0;
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        fiveCardCount++;
                                        hand5[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[1] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 2 called uno!\n", strlen("Player 2 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[2] == 1)
                            {
                              if(calledUno[2] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[2] = 0;
                                  write(6, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        sixCardCount++;
                                        hand6[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[2] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 3 called uno!\n", strlen("Player 3 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }

                            if(uno[3] == 1)
                            {
                              if(calledUno[3] == 0)
                              {
                                if(buffer[0] == 'C')
                                {
                                  uno[3] = 0;
                                  write(7, "Uno challenged, draw 2 cards\n", strlen("Uno challenged, draw 2 cards\n"));
                                  for(int d = 0; d < 2; d++)
                                  {
                                    bool draw = false;
                                    while(draw == false)
                                    {
                                      srand(time(NULL));
                                      int card = rand() % 108;
                                      if(taken[card] !=1)
                                      {
                                        sevenCardCount++;
                                        hand7[card] = 1;
                                        taken[card] = 1;
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
                                          for(int r = 0; r < 108; r++)
                                          {
                                            taken[r] = 0;
                                            if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                            {
                                              taken[r] = 1;
                                            }
                                          }
                                        }
                                        draw = true;
                                      }
                                    }
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }
                                if(buffer[0] == 'U')
                                {
                                  calledUno[3] == 1;
                                  for (int d = 4; d < 7; d++)
                                  {
                                    write(d, "Player 4 called uno!\n", strlen("Player 4 called uno!\n"));
                                  }
                                  memset(buffer, 0, MAXLINE);
          
                                  bytes = read(turn,buffer,MAXLINE);
                                }

                              }
                            }
                            

                            else if (draw2 == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 4 draws 2\n", strlen("Player 4 draws 2\n"));
                              }
                              for(int z = 0; z < 2; z++)
                                {
                                  bool draw = false;
                                  while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      sevenCardCount++;
                                      hand7[card] = 1;
                                      taken[card] = 1;
                                      bool fulldeck = true;
                                      for(int r = 0; r < 108; r++)
                                      {
                                        if(taken[r] == 0)
                                        {
                                          fulldeck = false;
                                        }
                                      }
                                      if(fulldeck == true)
                                      {
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                          {
                                            taken[r] = 1;
                                          }
                                        }
                                      }
                                      draw = true;
                                    }
                                  }

                                }
                              
                              draw2 = false;

                            }
                            else if(draw4 == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 4 draws 4\n", strlen("Player 4 draws 4\n"));
                              }
                              for(int z = 0; z < 4; z++)
                                {
                                  bool draw = false;
                                  while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      sevenCardCount++;
                                      hand7[card] = 1;
                                      taken[card] = 1;
                                      bool fulldeck = true;
                                      for(int r = 0; r < 108; r++)
                                      {
                                        if(taken[r] == 0)
                                        {
                                          fulldeck = false;
                                        }
                                      }
                                      if(fulldeck == true)
                                      {
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                          {
                                            taken[r] = 1;
                                          }
                                        }
                                      }
                                      draw = true;
                                    }
                                  }

                                }
                              
                              draw4 = false;

                            }
                            else if(skip == true)
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                                write(c, "Player 4 turn skipped\n", strlen("Player 4 turn skipped\n"));
                              }
                              skip = false;

                            }
                            else if (playable == true)
                            {
                              
                              if(buffer[0] == 'G' || buffer[0] == 'Y' || buffer[0] == 'B' || buffer[0] == 'R')
                              {
                                if(buffer[1] == '0' || buffer[1] == '1' || buffer[1] == '2' || buffer[1] == '3' || buffer[1] == '4' || buffer[1] == '5' || buffer[1] == '6' || buffer[1] == '7' || buffer[1] == '8' || buffer[1] == '9')
                                {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand7[a] == 1)
                                        {
                                          hand7[a] = 0;

                                          ss.str(string());

                                          ss << "Player 4 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          sevenCardCount--;
                                          if(sevenCardCount == 1)
                                          {
                                            uno[3] = 1;
                                          }
                                          if(sevenCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 4 wins!\n", strlen("Player 4 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                        }
                                      }
                                      else
                                      {
                                        write(7, "invalid move\n", strlen("invalid move\n"));
                                      }
                                    }
                                  }
                                }
                                else if(buffer[1] == '+')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand7[a] == 1)
                                        {
                                          hand7[a] = 0;
                                          ss.str(string());

                                          ss << "Player 4 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          sevenCardCount--;
                                          if(sevenCardCount == 1)
                                          {
                                            uno[3] = 1;
                                          }
                                          if(sevenCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 4 wins!\n", strlen("Player 4 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          draw2 = true;
                                        }
                                      }
                                      else
                                      {
                                        write(7, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                else if(buffer[1] == 'T')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand7[a] == 1)
                                        {
                                          hand7[a] = 0;
                                          ss.str(string());

                                          ss << "Player 4 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          sevenCardCount--;
                                          if(sevenCardCount == 1)
                                          {
                                            uno[3] = 1;
                                          }
                                          if(sevenCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 4 wins!\n", strlen("Player 4 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          if(flip == true)
                                          {
                                            flip = false;
                                          }
                                          else
                                          {
                                            flip = true;
                                          }
                                          
                                          
                                        }
                                      }
                                      else
                                      {
                                        write(7, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                else if(buffer[1] == 'S')
                                {
                                for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(topcard[0] == buffer[0] || topcard[1] == buffer[1])
                                      {
                                        if(hand7[a] == 1)
                                        {
                                          hand7[a] = 0;
                                          ss.str(string());

                                          ss << "Player 4 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                          topcard[0] = buffer[0];
                                          topcard[1] = buffer[1];
                                          sevenCardCount--;
                                          if(sevenCardCount == 1)
                                          {
                                            uno[3] = 1;
                                          }
                                          if(sevenCardCount == 0)
                                          {
                                            for(int c = 4; c <= 7; c++)
                                            {
                                            write(c, "Player 4 wins!\n", strlen("Player 4 wins!\n"));
                                            }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                            return 1;
                                            
                                          }
                                          skip = true;
                                        }
                                      }
                                      else
                                      {
                                        write(7, "invalid move\n", strlen("invalid move\n"));
                                      }
                                      

                                    }
                                  }
                                }
                                }
                                else if(buffer[0] == 'D')
                                {
                                  if(buffer[1] == '4')
                                  {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(hand7[a] == 1)
                                      {

                                        hand7[a] = 0;
                                          ss.str(string());

                                          ss << "Player 4 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                        bool pick = false;
                                        while(pick == false)
                                        {
                                            write(7, "pick a color\n", strlen("pick a color\n"));
                                            memset(buffer, 0, MAXLINE);
                                            bytes = read(7, buffer, MAXLINE);
                                            if (buffer[0] == 'R' ||buffer[0] == 'G' ||buffer[0] == 'B' ||buffer[0] == 'Y')
                                            {
                                              topcard[0] = buffer[0];
                                              for(int p = 4; p < 7; p++)
                                              {
                                                if(topcard[0] == 'R')
                                                {
                                                  write(p, "the new color is R\n", strlen("the new color is R\n"));
                                                }
                                                if(topcard[0] == 'G')
                                                {
                                                  write(p, "the new color is G\n", strlen("the new color is G\n"));
                                                }
                                                if(topcard[0] == 'B')
                                                {
                                                  write(p, "the new color is B\n", strlen("the new color is B\n"));
                                                }
                                                if(topcard[0] == 'Y')
                                                {
                                                  write(p, "the new color is Y\n", strlen("the new color is Y\n"));
                                                }
                                              }
                                              pick = true;
                                            }
                                          
                                        }
                                        sevenCardCount--;
                                        if(sevenCardCount == 1)
                                        {
                                          uno[3] = 1;
                                        }
                                        if(sevenCardCount == 0)
                                        {
                                          for(int c = 4; c <= 7; c++)
                                          {
                                          write(c, "Player 4 wins!\n", strlen("Player 4 wins!\n"));
                                          }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                          return 1;
                                          
                                        }
                                        draw4 = true;
                                      }
                                    }
                                  }
                                }
                              }
                              else if(buffer[0] == 'W')
                              {
                                if(buffer[1] == 'C')
                                {
                                  for(int a = 0; a < 108; a++)
                                  {
                                    if(buffer[0] == cards[a][0] && buffer[1] == cards[a][1])
                                    {
                                      if(hand7[a] == 1)
                                      {

                                        hand7[a] = 0;
                                          ss.str(string());

                                          ss << "Player 4 Played: " << cards[a][0] << cards[a][1];
                                          
                                          givestatus.clear();
                                          givestatus.append(ss.str());
                                          givestatus.append("\n");
                                          stat = new char[givestatus.length() + 1];
                                          strcpy(stat, givestatus.c_str());
                                          statlength = givestatus.length();
                                          write(4, stat, statlength);

                                          for(int c = 4; c <= 7; c++)
                                          {
                                            write(c, stat, statlength);
                                          }
                                        bool pick = false;
                                        while(pick == false)
                                        {
                                            write(7, "pick a color\n", strlen("pick a color\n"));
                                            memset(buffer, 0, MAXLINE);
                                            bytes = read(7, buffer, MAXLINE);
                                            if (buffer[0] == 'R' ||buffer[0] == 'G' ||buffer[0] == 'B' ||buffer[0] == 'Y')
                                            {
                                              topcard[0] = buffer[0];
                                              for(int p = 4; p < 7; p++)
                                              {
                                                if(topcard[0] == 'R')
                                                {
                                                  write(p, "the new color is R\n", strlen("the new color is R\n"));
                                                }
                                                if(topcard[0] == 'G')
                                                {
                                                  write(p, "the new color is G\n", strlen("the new color is G\n"));
                                                }
                                                if(topcard[0] == 'B')
                                                {
                                                  write(p, "the new color is B\n", strlen("the new color is B\n"));
                                                }
                                                if(topcard[0] == 'Y')
                                                {
                                                  write(p, "the new color is Y\n", strlen("the new color is Y\n"));
                                                }
                                              }
                                              pick = true;
                                            }
                                          
                                        }
                                        sevenCardCount--;
                                        if(sevenCardCount == 1)
                                        {
                                          uno[3] = 1;
                                        }
                                        if(sevenCardCount == 0)
                                        {
                                          for(int c = 4; c <= 7; c++)
                                          {
                                          write(c, "Player 4 wins!\n", strlen("Player 4 wins!\n"));
                                          }
                                            close(7);
                                            close(6);
                                            close(5);
                                            close(4);
                                            FD_CLR(7, &active_fd_set);
                                            FD_CLR(6, &active_fd_set);
                                            FD_CLR(5, &active_fd_set);
                                            FD_CLR(4, &active_fd_set);
                                          return 1;
                                          
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                              else if(buffer[0] == '\n')
                              {
                                for(int c = 4; c <= 7; c++)
                                {
                                write(c, "no play available Player 4 draws\n", strlen("no play available Player 4 draws\n"));
                                }
                                bool draw = false;
                                while(draw == false)
                                  {
                                    srand(time(NULL));
                                    int card = rand() % 108;
                                    if(taken[card] !=1)
                                    {
                                      sevenCardCount++;
                                      hand7[card] = 1;
                                      taken[card] = 1;
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
                                        for(int r = 0; r < 108; r++)
                                        {
                                          taken[r] = 0;
                                          if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
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
                            else
                            {
                              for(int c = 4; c <= 7; c++)
                              {
                              write(c, "no play available Player 4 draws\n", strlen("no play available Player 4 draws\n"));
                              }
                              bool draw = false;
                              while(draw == false)
                                {
                                  srand(time(NULL));
                                  int card = rand() % 108;
                                  if(taken[card] !=1)
                                  {
                                    sevenCardCount++;
                                    hand7[card] = 1;
                                    taken[card] = 1;
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
                                      for(int r = 0; r < 108; r++)
                                      {
                                        taken[r] = 0;
                                        if(hand4[r] == 1 ||hand5[r] == 1 ||hand6[r] == 1 ||hand7[r] == 1)
                                        {
                                          taken[r] = 1;
                                        }
                                      }
                                    }
                                    draw = true;
                                  }
                                }
                                
                              
                            }
                          
                          if(flip == true)
                          {
                            turn--;
                            if(turn < 4)
                            {
                              turn = 7;
                            }
                          }
                          else
                          {
                              turn++;
                              if( turn > 7)
                              {
                                  turn = 4;
                              }
                            
                            
                          }

                          for (int t = 4; t <=7; t++)
                          {
                            write(t, "Player 4: end of turn\n", strlen("Player 4: end of turn\n"));
                          }
                          playable = false;
                          
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
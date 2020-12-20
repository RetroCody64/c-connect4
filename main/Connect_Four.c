/*
Program name: c-connect4
Author: *Redacted*
Release Date: 19/12/20
Build: 1.0
License: GNU GPL V3.0 (General Public License)
*/

#include <stdio.h>

void initialize_game(); //Set all values on matrix connect_four
void print_game_state(); //Print table
void insert_into_connect_four(char); //Place the thing in the matrix
void verify_game_state(); //Check if someone won

char connect_four[6][7]; //6 rows 7 collumns
int collumn; //Gamer input
int playerN = 1; //Player 1 or 2 (P1 = 1 | P2 = 0)

int main()
{
  initialize_game();
  while (1)
  {
    print_game_state();
    do
    {
      printf("Select a column: ");
      while ( !scanf("%d", &collumn) ) //If input is invalid aka not an integer
      {
        while (getchar() != '\n'); //Clear buffer
        printf("Invalid input, must be 1-7 or 0 to exit: ");
      }
    } while( collumn > 7 || collumn < 0); //While input invalid aka not a value between 0-7 (1-7 for position 0 for exit)
    if (!collumn) break; //If input is 0 terminate program

    if (playerN)
    { insert_into_connect_four('x'); playerN = 0; }
    else
    { insert_into_connect_four('o'); playerN = 1; }

    verify_game_state();
  }
}

void initialize_game() //Literally just initialize the matrix with the char *
{
  for(int i = 0; i < 6; i++)
  {
    for(int j = 0; j < 7; j++)
    {
      connect_four[i][j] = '*';
    }
  }
}

void print_game_state()
{
  puts("   1     2    3    4     5    6     7     (0 to exit)");
  for(int i = 0; i < 6; i++)
  {
    putchar('|');
    for(int j = 0; j < 7; j++)
    {
      printf(" %c |", connect_four[i][j]);
    }
    putchar('\n');
    puts("--------------------------------------");
  }
}

void insert_into_connect_four(char player)
{
  for (int i = 5; i > -1; i--)
    if (connect_four[i][collumn - 1] != 'x' && connect_four[i][collumn - 1] != 'o') //Check if position is already taken
    {
      connect_four[i][collumn - 1] = player;
      break;
    }
}

void verify_game_state() //God help whoever decides to try and make sense of this shit
{
  int victory = 0;
  int defeat = 0;

  // Check horizontally / vertically
  for (int i = 6; i > -1; i--)
  {
    for (int j = 3; j > -1; j--)
    {
      // Horizontally for x
      if ( (i > 5 ? 0 : connect_four[i][j] == 'x') && (i > 5 ? 0 : connect_four[i][j + 1] == 'x') && (i > 5 ? 0 : connect_four[i][j + 2] == 'x') && (i > 5 ? 0 : connect_four[i][j + 3] == 'x'))
      { victory = 1; break; }
      // Vertically for x
      else if (connect_four[j][i] == 'x' && connect_four[j + 1][i] == 'x' && connect_four[j + 2][i] == 'x' && (j > 5 ? 0 : connect_four[j + 3][i] == 'x'))
      { victory = 1; break; }

      // Horizontally for o
      else if ( (i > 5 ? 0 : connect_four[i][j] == 'o') && (i > 5 ? 0 : connect_four[i][j + 1] == 'o') && (i > 5 ? 0 : connect_four[i][j + 2] == 'o') && (i > 5 ? 0 : connect_four[i][j + 3] == 'o'))
      { defeat = 1; break; }
      // Vertically for o
      else if (connect_four[j][i] == 'o' && connect_four[j + 1][i] == 'o' && connect_four[j + 2][i] == 'o' && (j > 5 ? 0 : connect_four[j + 3][i] == 'o'))
      { defeat = 1; break; }
    }
  }

  // Check diagonally
  if (!victory && !defeat) // Prevent pointless verification
  {
    // One combo possible only
    if (connect_four[0][3] == 'x' && connect_four[1][4] == 'x' && connect_four[2][5] == 'x' && connect_four[3][6] == 'x')
      victory = 1;
    else if (connect_four[0][3] == 'x' && connect_four[1][2] == 'x' && connect_four[2][1] == 'x' && connect_four[3][0] == 'x')
      victory = 1;
    else if (connect_four[2][0] == 'x' && connect_four[3][1] == 'x' && connect_four[4][2] == 'x' && connect_four[5][3] == 'x')
      victory = 1;
    else if (connect_four[3][0] == 'x' && connect_four[2][1] == 'x' && connect_four[1][2] == 'x' && connect_four[0][3] == 'x')
      victory = 1;
    else if (connect_four[5][3] == 'x' && connect_four[4][4] == 'x' && connect_four[3][5] == 'x' && connect_four[2][6] == 'x')
      victory = 1;

    else if (connect_four[0][3] == 'o' && connect_four[1][4] == 'o' && connect_four[2][5] == 'o' && connect_four[3][6] == 'o')
      defeat = 1;
    else if (connect_four[0][3] == 'o' && connect_four[1][2] == 'o' && connect_four[2][1] == 'o' && connect_four[3][0] == 'o')
      defeat = 1;
    else if (connect_four[2][0] == 'o' && connect_four[3][1] == 'o' && connect_four[4][2] == 'o' && connect_four[5][3] == 'o')
      defeat = 1;
    else if (connect_four[3][0] == 'o' && connect_four[2][1] == 'o' && connect_four[1][2] == 'o' && connect_four[0][3] == 'o')
      defeat = 1;
    else if (connect_four[5][3] == 'o' && connect_four[4][4] == 'o' && connect_four[3][5] == 'o' && connect_four[2][6] == 'o')
      defeat = 1;
  }
    // Two combo possible only
    if (!victory && !defeat) // Prevent pointless verification
    {
      //Left and right increases
      int j = 0;
      for (int i = 0; i < 2; i++)
      {
          if ( connect_four[i][j + 2] == 'x' && connect_four[i + 1][j + 3] == 'x' && connect_four[i + 2][j + 4] == 'x' && connect_four[i + 3][j + 5] == 'x')
          { victory = 1; break; }
          else if ( connect_four[i + 1][j] == 'x' && connect_four[i + 2][j + 1] == 'x' && connect_four[i + 3][j + 2] == 'x' && connect_four[i + 4][j + 3] == 'x')
          { victory = 1; break; }

          else if ( connect_four[i][j + 2] == 'o' && connect_four[i + 1][j + 3] == 'o' && connect_four[i + 2][j + 4] == 'o' && connect_four[i + 3][j + 5] == 'o')
          { defeat = 1; break; }
          else if ( connect_four[i + 1][j] == 'o' && connect_four[i + 2][j + 1] == 'o' && connect_four[i + 3][j + 2] == 'o' && connect_four[i + 4][j + 3] == 'o')
          { defeat = 1; break; }
          j++;
      }
      //Left increases and right decreases
      if (!victory && !defeat) // Prevent pointless verification
      {
        int j = 4;
        for (int i = 0; i < 2; i++)
        {
            if ( connect_four[i][j] == 'x' && connect_four[i + 1][j - 1] == 'x' && connect_four[i + 2][j - 2] == 'x' && connect_four[i + 3][j - 3] == 'x')
            { victory = 1; break; }

            else if ( connect_four[i][j] == 'o' && connect_four[i + 1][j - 1] == 'o' && connect_four[i + 2][j - 2] == 'o' && connect_four[i + 3][j - 3] == 'o')
            { defeat = 1; break; }
            j--;
        }
      }
      //Left decreases and right increases
      if (!victory && !defeat) // Prevent pointless verification
      {
        int j = 0;
        for (int i = 5; i < 4; i--)
        {
            if ( connect_four[i - 1][j] == 'x' && connect_four[i - 2][j + 1] == 'x' && connect_four[i - 3][j + 2] == 'x' && connect_four[i - 4][j + 3] == 'x')
            { victory = 1; break; }
            else if ( connect_four[i][j + 2] == 'x' && connect_four[i - 1][j + 3] == 'x' && connect_four[i - 2][j + 4] == 'x' && connect_four[i - 3][j + 5] == 'x')
            { victory = 1; break; }

            if ( connect_four[i - 1][j] == 'o' && connect_four[i - 2][j + 1] == 'o' && connect_four[i - 3][j + 2] == 'o' && connect_four[i - 4][j + 3] == 'o')
            { defeat = 1; break; }
            else if ( connect_four[i][j + 2] == 'o' && connect_four[i - 1][j + 3] == 'o' && connect_four[i - 2][j + 4] == 'o' && connect_four[i - 3][j + 5] == 'o')
            { defeat = 1; break; }
            j++;
        }
      }
    }
    // Three combo possible only
    if (!victory && !defeat) // Prevent pointless verification
    {
      //Left and right increases
      int j = 0;
      for (int i = 0; i < 3; i++)
      {
          if ( connect_four[i][j] == 'x' && connect_four[i + 1][j + 1] == 'x' && connect_four[i + 2][j + 2] == 'x' && connect_four[i + 3][j + 3] == 'x')
          { victory = 1; break; }
          else if ( connect_four[i][j + 1] == 'x' && connect_four[i + 1][j + 2] == 'x' && connect_four[i + 2][j + 3] == 'x' && connect_four[i + 3][j + 4] == 'x')
          { victory = 1; break; }

          else if ( connect_four[i][j] == 'o' && connect_four[i + 1][j + 1] == 'o' && connect_four[i + 2][j + 2] == 'o' && connect_four[i + 3][j + 3] == 'o')
          { defeat = 1; break; }
          else if ( connect_four[i][j + 1] == 'o' && connect_four[i + 1][j + 2] == 'o' && connect_four[i + 2][j + 3] == 'o' && connect_four[i + 3][j + 4] == 'o')
          { defeat = 1; break; }
          j++;
      }
      //Left increases and right decreases
      if (!victory && !defeat) // Prevent pointless verification
      {
        int j = 6;
        for (int i = 0; i < 3; i++)
        {
            if ( connect_four[i][j - 1] == 'x' && connect_four[i + 1][j - 2] == 'x' && connect_four[i + 2][j - 3] == 'x' && connect_four[i + 3][j - 4] == 'x')
            { victory = 1; break; }
            else if ( connect_four[i][j] == 'x' && connect_four[i + 1][j - 1] == 'x' && connect_four[i + 2][j - 2] == 'x' && connect_four[i + 3][j - 3] == 'x')
            { victory = 1; break; }

            else if ( connect_four[i][j - 1] == 'o' && connect_four[i + 1][j - 2] == 'o' && connect_four[i + 2][j - 3] == 'o' && connect_four[i + 3][j - 4] == 'o')
            { defeat = 1; break; }
            else if ( connect_four[i][j] == 'o' && connect_four[i + 1][j - 1] == 'o' && connect_four[i + 2][j - 2] == 'o' && connect_four[i + 3][j - 3] == 'o')
            { defeat = 1; break; }
            j--;
        }
      }
      //Left decreases and right increases
      if (!victory && !defeat) // Prevent pointless verification
      {
        int j = 0;
        for (int i = 5; i < 3; i--)
        {
            if ( connect_four[i][j] == 'x' && connect_four[i - 1][j + 1] == 'x' && connect_four[i - 2][j + 2] == 'x' && connect_four[i - 3][j + 3] == 'x')
            { victory = 1; break; }
            else if ( connect_four[i][j + 1] == 'x' && connect_four[i - 1][j + 2] == 'x' && connect_four[i - 2][j + 3] == 'x' && connect_four[i - 3][j + 4] == 'x')
            { victory = 1; break; }

            else if ( connect_four[i][j] == 'o' && connect_four[i - 1][j + 1] == 'o' && connect_four[i - 2][j + 2] == 'o' && connect_four[i - 3][j + 3] == 'o')
            { victory = 1; break; }
            else if ( connect_four[i][j + 1] == 'o' && connect_four[i - 1][j + 2] == 'o' && connect_four[i - 2][j + 3] == 'o' && connect_four[i - 3][j + 4] == 'o')
            { victory = 1; break; }
            j++;
        }
      }
    }
  if (victory) //If x wins
  {
      victory = 0;
      puts("x wins");
      while(getchar() != '\n');
      getchar();
      initialize_game();
  }

  else if (defeat) //If o wins
  {
      defeat = 0;
      puts("o wins");
      while(getchar() != '\n');
      getchar();
      initialize_game();
  }
}

/* Notes

           0         1          2         3         4         5         6
0   |  0.0  |  0.1  |  0.2  |  0.3  |  0.4  |  0.5  |  0.6  |
      ------------------------------------------------------------------
1   |  1.0  |  1.1  |  1.2  |  1.3  |  1.4  |  1.5  |  1.6  |
      ------------------------------------------------------------------
2   |  2.0  |  2.1  |  2.2  |  2.3  |  2.4  |  2.5  |  2.6  |
      ------------------------------------------------------------------
3   |  3.0  |  3.1  |  3.2  |  3.3  |  3.4  |  3.5  |  3.6  |
      ------------------------------------------------------------------
4   |  4.0  |  4.1  |  4.2  |  4.3  |  4.4  |  4.5  |  4.6  |
      ------------------------------------------------------------------
5   |  5.0  |  5.1  |  5.2  |  5.3  |  5.4  |  5.5  |  5.6  |
      ------------------------------------------------------------------
Combinations:
  Horizontally:  C && R, R+1, R+2, R+3 || R+4 R+5 R+6 (R = 0 [in the loop we loop until index 6 but since there is no row with index 6 we just pass 5 (in the 0,0 1,1... instance), essentially skipping it])
  Vertically: C, C+1, C+2, C+3, C+4, C+5 && R (C = 0 [])
  Diagonally
  {
    one combo possible
    0.3 | 1.4 | 2.5 | 3.6
    0.3 | 1.2 | 2.1 | 3.0
    2.0 | 3.1 | 4.2 | 5.3
    3.0 | 2.1 | 1.2 | 0.3
    5.3 | 4.4 | 3.5 | 2.6

    Two combos possible
    0.2 | 1.3 | 2.4 | 3.5 | 4.6      Left and right increases
    1.0 | 2.1 | 3.2 | 4.3 | 5.4

    0.4 | 1.3 | 2.2 | 3.1 | 4.0      Left increases right decreases

    4.0 | 3.1 | 2.2 | 1.3 | 0.4      Left decreases right increases
    5.2 | 4.3 | 3.4 | 2.5 | 1.6

    Three combos possible
    0.0 | 1.1 | 2.2 | 3.3 | 4.4 | 5.5      Left and right increases
    0.1 | 1.2 | 2.3 | 3.4 | 4.5 | 5.6

    0.5 | 1.4 | 2.3 | 3.2 | 4.1 | 5.0      Left increases right decreases
    0.6 | 1.5 | 2.4 | 3.3 | 4.2 | 5.1

    5.0 | 4.1 | 3.2 | 2.3 | 1.4 | 0.5      Left decreases right increases
    5.1 | 4.2 | 3.3 | 2.4 | 1.5 | 0.6
  }
*/

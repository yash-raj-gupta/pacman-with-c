// Libraries required for working of the game
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// Important elements used in the game
#define WIDTH 40
#define HEIGHT 20
#define PACMAN 'C'
#define WALL '#'
#define FOOD '*'
#define EMPTY ' '
#define DEMON '@'
#define SPFOOD '&'

int res = 0;
int score = 0;
int pacman_x, pacman_y;
char board[HEIGHT][WIDTH];
int food = 0;
int curr = 0;
int prev = -1;
void initialize()
{

    // Puting the boundary walls
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1)
            {
                board[i][j] = WALL;
            }
            else
                board[i][j] = EMPTY;
        }
    }

    // Putting some walls inside the board
    int count = 50;
    while (count != 0)
    {
        int i = (rand() % (HEIGHT + 1));
        int j = (rand() % (WIDTH + 1));

        if (board[i][j] != WALL && board[i][j] != PACMAN)
        {
            board[i][j] = WALL;
            count--;
        }
    }

    int val = 5;
    while (val--)
    {
        int row = (rand() % (WIDTH + 1));
        for (int j = 3; j < WIDTH - 3; j++)
        {
            if (board[row][j] != WALL && board[row][j] != PACMAN)
            {
                board[row][j] = WALL;
            }
        }
    }

    //   Putting demons in the game
    count = 10;
    while (count != 0)
    {
        int i = (rand() % (HEIGHT + 1));
        int j = (rand() % (WIDTH + 1));

        if (board[i][j] != WALL && board[i][j] != PACMAN)
        {
            board[i][j] = DEMON;
            count--;
        }
    }

    // Placing pacman at the center of the board
    pacman_x = WIDTH / 2;
    pacman_y = HEIGHT / 2;
    board[pacman_x][pacman_y] = PACMAN;

    //  Placing the food on the board
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i % 2 == 0 && j % 2 == 0 && board[i][j] != PACMAN && board[i][j] != WALL && board[i][j] != DEMON)
            {
                board[i][j] = FOOD;
                food++;
            }
        }
    }
}

void draw()
{
    system("cls");
    // Placing 2 special food on eating every 10 items
    if ((curr / 10) > prev)
    {
        int count = 0;
        prev = curr / 10;
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (count < 2)
                {
                    if (i % 2 == 0 && j % 2 == 0 && board[i][j] != PACMAN && board[i][j] != WALL && board[i][j] != DEMON && board[i][j] != FOOD)
                    {
                        board[i][j] = SPFOOD;
                        food++;
                        count++;
                    }
                }
            }
            if (count == 2)
                break;
        }
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

// Function to move the pacman on the board
void move(int move_x, int move_y)
{
    int x = pacman_x + move_x;
    int y = pacman_y + move_y;
    if (board[y][x] != WALL)
    {
        if (board[y][x] == FOOD || board[y][x] == SPFOOD)
        {
            if (board[y][x] == SPFOOD)
                score += 10;
            else
                score++;
            food--;
            curr++;
            if (food == 0)
            {
                res = 2;
                return;
            }
        }
        else if (board[y][x] == DEMON)
        {
            res = 1;
        }

        board[pacman_y][pacman_x] = EMPTY;
        pacman_x = x;
        pacman_y = y;
        board[pacman_y][pacman_x] = PACMAN;
    }
}

int main()
{
    initialize();
    char ch;
    printf("Use buttons for w(up), a(left), d(right), s(down)\nAlso, press q for quit\n");
    printf("Enter Y to continue:\n");
    ch = getchar();
    if (ch != 'Y' && ch != 'y')
    {
        printf("Exiting Game: %c\n", ch);
        return 1;
    }

    while (1)
    {
        draw();
        printf("Food left: %d\n", food);
        printf("Total food eaten: %d\n", curr);
        if (res == 1)
        {
            system("cls");
            printf("Game over! Dead by Demon\n Your Score: %d\n", score);
            return 1;
        }
        if (res == 2)
        {
            system("cls");
            printf("You win! \n Your Score: %d\n", score);
            return 1;
        }

        ch = getchar();
        switch (ch)
        {
        case 'w':
            move(0, -1);
            break;

        case 's':
            move(0, 1);
            break;

        case 'a':
            move(-1, 0);
            break;

        case 'd':
            move(1, 0);
            break;

        case 'q':
            printf("Game Over! Your Score: %d\n", score);
            return 0;
        }
    }
    return 0;
}
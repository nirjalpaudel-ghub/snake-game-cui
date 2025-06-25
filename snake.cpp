//snake game
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width=60,height=30;
int x=width/2;
int y=height/2;
int fruitX=rand()%width;
int fruitY=rand()%height;
int score;
int nTail=0,tailX[100],tailY[100];
static int highScore=0;

//direction
enum eDirection{STOP=0,UP,DOWN,LEFT,RIGHT};
eDirection dir;


// game over or not
void setup()
{
    dir=STOP;
    gameOver=false;
    score = 0;
    nTail = 0;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;

    for (int i = 0; i < 100; i++) {
        tailX[i] = 0;
        tailY[i] = 0;
    }
}

//boundary
void draw()
{
    //ansii escape sequence 
    //same as system("CLS")
    cout << "\x1B[2J\x1B[H";
    for (int i=0;i<width;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    
    
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0||j==width-1)
            cout<<"#";
            else if(i==y&&j==x)
            {
                cout<<"O";
            }
            else if(i==fruitY&&j==fruitX)
            {
                cout<<"X";
            }
            else
            {
               bool print=false;
             for (int k = 0; k < nTail; k++) 
                {
                  if (tailX[k] == j && tailY[k] == i)
                  {
                    cout << "o"; 
                    print = true;
                    break;
                 }
                
                }
                if (!print)
                cout<<" ";
            }
             
        }
        cout<<endl;
    }
     
    
    for(int i=0;i<width;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    cout<<endl;
    cout<<"\t\tScore: "<<score<<"\t"<<"HighScore: "<<highScore<<endl;  
}

//tail collision test
 void tailCollision()
 {
    for(int i=1;i<nTail;i++)
    {
        if (x==tailX[i]&&y==tailY[i])
        gameOver=true;
    }
 }
//user input
void input()
{
    
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'w':
            dir=UP;
            break;
            case 'a':
            dir=LEFT;
            break;
            case 's':
            dir=DOWN;
            break;
            case 'd':
            dir=RIGHT;
            break;
            default:
            break;
        }
    }
}

//game logic
void logic()
{
    int prevX = x;
    int prevY = y;
    switch(dir)
    {
        case UP:
        y--;
        break;
        case DOWN:
        y++;
        break;
        case LEFT:
        x--;
        break;
        case RIGHT:
        x++;
        break;
        default:
        break;
    }
    for (int i = 0; i < nTail; i++)
    {
        int prev2X = tailX[i];
        int prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
}

//collision test
void collision()
{
    if(x<0||y>height-1||y<0||x>width-1)
    {
        gameOver=true;
    }
}

//eat fruit
void fruitCheck()
{
    if(x==fruitX&&y==fruitY)
    {
        score+=10;
        if(score>highScore)
        {
            highScore=score;
        }
        fruitX=rand()%width;
        fruitY=rand()%height;
        nTail++;
    }
}



int main()
{
    abc:
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        tailCollision();
        collision();
        fruitCheck();
        Sleep(100);
    }
  cout << "\nGame Over! Press '1' to restart or any other key to quit..." << endl;
    Sleep(500);
    while (_kbhit()) _getch(); //same as fflush(stdin)
    char check = _getch();

    if (check == '1') 
    {
        cout << "\x1B[2J\x1B[H";
        goto abc;
    }
    return 0;
}

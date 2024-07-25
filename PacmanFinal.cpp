#include <iostream>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <sstream>


using namespace std;
const int row = 14;
const int col = 14;

void readrecords();      
void printrecords();
void saverecords(string, string, string, string);
void menu();
void pacman();

string records[20][4];

int main()
{
    menu();
}

void readrecords()
{
	fstream read;                                            //object of fstream to read read
    read.open("records.txt", ios::in);                     //opening object for reading purposes
    for (int r = 0; r < 20; r++)                          //20 lines 
        for (int c = 0; c < 4; c++)                       //4 words    
            read >> records[r][c];                    //storing in 2d array
            
    read.close();	                             //closing the object
}

void printrecords()                           
{
    system("cls");
    
	readrecords();               //first we read everyting and then store in aaray
    
	cout << "\t\tName\t\tlevel\t\tScore\t\tTime(seconds)\n";
    for (int r = 0; r < 20; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            cout << "\t\t" << records[r][c];
        }
        cout << endl;
    }
    system("pause");
    system("cls");
    menu();                    //calling the menu again
}

void saverecords(string name, string score, string level, string time)
{

    for (int r = 19; r > 0; r--)
        for (int c = 0; c < 4; c++)
            records[r][c] = records[r - 1][c];                //storing previous array elements     if we have 20 records and store 1 more   last element will be deleted
    

    records[0][0] = name;
    records[0][1] = level;
    records[0][2] = score;
    records[0][3] = time;
    
    fstream save;                                    //object for saving records
    save.open("records.txt", ios::out);              //calling the object for writing purpose        
    for (int r = 0; r < 20; r++) 
    {
        for (int c = 0; c < 4; c++)
            save << records[r][c] << "\t";
        save << endl;
    }
    
    save.close();
}

void menu()
{
    system("cls");
    int choice;
    cout << "\n\n\t\t WELLCOME TO THE PACMAN GAME\n\n 1)Start game \n 2)Access Records\n 3)Exit game\n\nEnter your choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
        pacman();
        break;
    case 2:
        printrecords();
        break;
    case 3:
        return;
    default:
        cout <<endl<< "Invald choice!!!\nPlease try again"<<endl;
        system("pause");
        menu();
    }
}

void pacman() {

    string tab[row][col];
    int x, y;                 // use for loop iteration
    int pac1 = 10, pac2 = 10; //location for the pacman
    int score = 0, op;        //score is initially zero
    int food = 0;             // food item initialized
    string name, level;
    int life = 3; // pacman life has initialize with value 3.



    cout << "Enter you name:";
    cin >> name;
    cout << "\nGame level \n 1: Easy Level \n 2: Hard Level \n \tchoose one option:";


    cin >> op;
    if (op == 1)
    {
        life = 3;
        level = "Easy";
    }
    else {
        life = 1;
        level = "Hard";
    }


    cout << "\n";

    system("pause");
    system("cls");
    for (x = 0; x < col; x++)
    {
        for (y = 0; y < row; y++)
        {
            if (x == 0 || x == (row - 1)) //make first and last row of array, a wall of maze
            {
                tab[x][y] = "-"; // - will be use to make upper and lower boundry
            }
            else if (y == 0 || y == (col - 1)) //left side of array(1th column) and right side of array(last coloumn) will be theboundry of maze.
            {
                tab[x][y] = "|"; // | used to make left and right boundry
            }

            // this commneted section is to make the hurdles on the Maze and if you required these hurdlesyou can uncoment the below section

            else if (x == 3 && y > 3 && y <= 8)
            {

                tab[x][y] = "*";
            }
            else if (y == 2 && x > 4 && y <= 10)
            {

                tab[x][y] = "*";
            }
            else if (x == 11 && y >= 5 && y <= 9)
            {

                tab[x][y] = "*";
            }
            else if (y == 11 && x >= 2 && x < 9) {

                tab[x][y] = "*";
    	}


            else if (y == 5 && x >= 6 && x < 10) //these checks are use to make small cage for the monster start from 5col and 6th row
            {
                tab[x][y] = "*";
            }
            else if (x == 9 && y >= 6 && y < 10) //
            {
                tab[x][y] = "*";
            }
            else if (y == 9 && x >= 6 && x < 10) // cage will be end on 9th col and 10th row
            {
                tab[x][y] = "*";
            }
            else if (x == 5 && y >= 5 && y < 10) //
            {
                tab[x][y] = "*";
            }
            else
            { // otherthan boundry and cage ,all the indexes are food item for Pacman
                tab[x][y] = ".";
                food++;
            }
        }
    }
    
    float Time = 0;
    tab[pac1][pac2] = "^"; // it is notation for pacman to start.
  
    tab[7][7] = "O";
    tab[7][8] = "O"; 
    tab[8][7] = "O";
    tab[5][7] = "."; //make a door for the monster to come out
    food = food - 3;
    cout << "SCORE=" << score;
    cout << "\t\tLIFE=" << life;
    cout << "\t\tTime=" << Time << " sec";
    cout << "\t\tFood Availabe=" << food << "\n\n";
    for (x = 0; x < col; x++) //draw the maze with all the monster,cage and Pacman
    {
        cout << "\t\t";
        for (y = 0; y < row; y++)
        {
            cout << tab[x][y] << " ";
        }
        cout << endl;
    }

    //taking current time of device
    clock_t time_req;
    time_req = clock();
    char move;

    while (1)
    {

        move = _getch();

        if (move == 80) //Ascii value for the down arrow key
        {               //s to go down

            pac1++;                                                                         // pac1 is x-axis location for the Pacman ,upon moving down, x-axis index will be increased
            if (tab[pac1][pac2] == "-" || tab[pac1][pac2] == "|" || tab[pac1][pac2] == "*") //if Pacman touch the boundry or cage
            {
                life--; //pacman has lost is life
                //tab[pac1][pac2] =" ";
                if (pac1 >= 0)
                {
                    tab[pac1 - 1][pac2] = " "; //x-axis of pacman has been increased above and his last index(from where pacman travelled) has made Null
                }
                pac1 = 10;
                pac2 = 10;     //pacman will be placed on initial index
                tab[pac1][pac2] = "^";
                if (life == 0) //if his life is expired then program will terminate
                {
                    system("cls");
                    cout << "Your score is:" << score << endl;
                    cout << "game over...";
                    break;
                }
            }
            else
            {
                if (tab[pac1][pac2] == ".")
                {
                    score += 10; //score incremented by 10 on every food item eaten by pacman  .
                    food--;
                }

                tab[pac1][pac2] = "^";
                if (pac1 >= 0)
                {
                    tab[pac1 - 1][pac2] = " "; //x-axis of pacman has been increased above and his last index(from where pacman travelled) has made Null
                }
            }
        }

        if (move == 72) //ascii value for the upper arrow key
        {               // to go up
            pac1--;
            if (tab[pac1][pac2] == "-" || tab[pac1][pac2] == "|" || tab[pac1][pac2] == "*") //if Pacman touch the boundry or cage
            {
                life--; //pacman has lost is life
                //tab[pac1][pac2] =" ";
                if (pac1 >= 0)
                {
                    tab[pac1 + 1][pac2] = " "; //x-axis of pacman has been increased above and his last index(from where pacman travelled) has made Null
                }
                pac1 = 10;
                pac2 = 10;     //pacman will be placed on initial index
                tab[pac1][pac2] = "^";
                if (life == 0) //if his life is expired then program will terminate
                {
                    system("cls");
                    cout << "Your score is:" << score << endl;
                    cout << "game over...";
                    break;
                }
            }
            else
            {
                if (tab[pac1][pac2] == ".")
                {
                    score += 10; //score incremented by 10 on every food item eaten by pacman  .
                    food--;
                }

                tab[pac1][pac2] = "v";
                if (pac1 >= 0)
                {
                    tab[pac1 + 1][pac2] = " "; //x-axis of pacman has been increased above and his last index(from where pacman travelled) has made Null
                }
            }
        }

        if (move == 77) //ascii value for the right arrow key
        {               // to go right
            pac2++;
            if (tab[pac1][pac2] == "-" || tab[pac1][pac2] == "|" || tab[pac1][pac2] == "*") //if Pacman touch the boundry or cage
            {
                life--; //pacman has lost is life
                //tab[pac1][pac2] =" ";
                if (pac2 >= 0)
                {
                    tab[pac1][pac2 - 1] = " "; //x-axis of pacman has been increased above and his last index(from where pacman travelled) has made Null
                }
                pac1 = 10;
                pac2 = 10;     //pacman will be placed on initial index
                tab[pac1][pac2] = "^";
                if (life == 0) //if his life is expired then program will terminate
                {
                    system("cls");
                    cout << "Your score is:" << score << endl;
                    cout << "game over...";
                    break;
                }
            }
            else
            {
                if (tab[pac1][pac2] == ".")
                {
                    score += 10; //score incremented by 10 on every food item eaten by pacman  .
                    food--;
                }

                tab[pac1][pac2] = "<";
                if (pac2 >= 0)
                {
                    tab[pac1][pac2 - 1] = " "; //x-axis of pacman has been increased above and his last index(from where pacman travelled) has made Null
                }
            }
        }
        if (move == 75) //ascii value for the left arrow key
        {               // to go left
            pac2--;
            if (tab[pac1][pac2] == "-" || tab[pac1][pac2] == "|" || tab[pac1][pac2] == "*") //if Pacman touch the boundry or cage
            {
                life--; //pacman has lost is life
                //tab[pac1][pac2] =" ";
                if (pac2 >= 0)
                {
                    tab[pac1][pac2 + 1] = " "; //x-axis of pacman has been increased above and his last index(from where pacman travelled) has made Null
                }
                pac1 = 10;
                pac2 = 10;     //pacman will be placed on initial index
                tab[pac1][pac2] = "^";
                if (life == 0) //if his life is expired then program will terminate
                {
                    system("cls");
                    cout << "Your score is:" << score << endl;
                    cout << "game over...";
                    break;
                }
            }
            else
            {
                if (tab[pac1][pac2] == ".")
                {
                    score += 10; //score incremented by 10 on every food item eaten by pacman  .
                    food--;
                }

                tab[pac1][pac2] = ">";
                if (pac2 >= 0)
                {
                    tab[pac1][pac2 + 1] = " "; //x-axis of pacman has been increased above and his last index(from where pacman travelled) has made Null
                }
            }
        }

        if (food == 0) //if food is zero then pacman won the game.
        {
            system("cls");
            cout << "\t\t\t\t SCORE=" << score << endl;
            cout << "You Won...";
            break;
        }

        system("cls");

        time_req = clock() - time_req; //this is time taken by the above calculation , and this time is calculated on every iteration

        cout << "SCORE=" << score;
        cout << "\t\tLIFE=" << life;
        cout << "\t\ttime:" << (float)time_req / CLOCKS_PER_SEC << " sec";
        cout << "\t\tFood Availabe=" << food << "\n\n";
        // re-draw the maze
        for (x = 0; x < col; x++)
        {
            cout << "\t\t";
            for (y = 0; y < row; y++)
            {
                cout << tab[x][y] << " ";
            }
            cout << endl;
        }
        // this loop is constructed for the purpose ,if the monster left his place on maze and go somewhere else then his place or index will be fill with food item
        for (x = 0; x < col; x++)
        {
            for (y = 0; y < row; y++)
            {
                if (tab[x][y] == "O" || tab[x][y] == "O") // notation for the monsters
                {
                    tab[x][y] = ".";
                }
            }
        }
        // random:
        srand(time(0));              //random function for the movement of monster
        int killX = rand() % 11 + 1; //x axis for the killing monster
        int killY = rand() % 11 + 1; // y-axis
        int eatX1 = rand() % 11 + 1; //x-axis for the eatable monster
        int eatY1 = rand() % 11 + 1; //y axis and so on
        int eatX2 = rand() % 11 + 1;
        int eatY2 = rand() % 11 + 1;

        if (tab[killX][killY] == "^" || tab[killX][killY] == "v" || tab[killX][killY] == ">" || tab[killX][killY] == "<")
        { //if killing monster touch the pacman ,pacman losses his life
            life--;
            system("cls");
            if (life == 0)
            {
                cout << "Your score is:" << score << endl;
                cout << "game finish...";
                break;
            }
        }
        else if (tab[killX][killY] == "*")
        { //if monster want to break the cage ,then he placed over the fixed value
            tab[3][3] = "O";
        }
        else
            tab[killX][killY] = "O";

        if (tab[eatX1][eatY1] == "^" || tab[eatX1][eatY1] == "v" || tab[eatX1][eatY1] == ">" || tab[eatX1][eatY1] == "<")
        { //if eatable maonster touch the pacman , eatable will placed in cage again

            tab[7][8] = "O";
        }
        else if (tab[eatX1][eatY1] == "*")
        { //if monster want to break the cage ,then he placed over the fixed value
            tab[4][4] = "O";
        }
        else
            tab[eatX1][eatY1] = "O";

        if (tab[eatX2][eatY2] == "^" || tab[eatX2][eatY2] == "v" || tab[eatX2][eatY2] == ">" || tab[eatX2][eatY2] == "<")
        { //if eatable maonster touch the pacman , eatable will placed in cage again
            tab[8][7] = "O";
        }
        else if (tab[eatX2][eatY2] == "*")
        { //if monster want to break the cage ,then he placed over the fixed value
            tab[8][3] = "O";
        }
        else
            tab[eatX2][eatY2] = "O";

    } // move = 0;

	readrecords();
    cout << endl << endl << "Saving records...\n\n";

    stringstream ss;                               //stream of name ss
    ss << score;                                   //putting score in stream ss
    string str_score = ss.str();                   //converting ss in string and storing it in string variable

    float totaltime = float(clock() - time_req) / 1000;         //ending time-staring= total time  and dividing by 1000 to get time in seconds 

    stringstream st;                           //stream of name st
    st << totaltime;                           //putting time in stream st
    string str_time = st.str();                 //converting st in string and storing it in string variable

    saverecords(name, str_score, level, str_time);     //function call
    system("pause");
    menu();
}

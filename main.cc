#include <iostream>
#include <memory.h>
#include <cstdlib>
#include <ctime>
#include<vector>
#include <cctype>
using namespace std;

//Christian Vaughn

//Size of the board
const int MAX_SIZE = 3;
const char EMPTY = '.';
const char AI = '*';  //The appearance of the AI on the board
const char TIE = '#'; // The Symbol if the board is full and there is a tie.
int num_of_moves = 0;
bool cpuGo = false;
//Extra credit: Print out the row and column numbers and/or make it look pretty
void print_array(vector< vector<char> > &arr)
{
    cout << " ";
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << " " << i;
    }
    cout << " " << endl;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << i << " ";
        for (int j = 0; j < MAX_SIZE; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

//Initializes the array to make it ready for a new game
void clear_array(vector< vector<char> > &arr)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            arr[i][j] = EMPTY;
        }
    }
}

//Will examine a board to see if there's a winning position
//A winning position is a horizontal row or vertical column all with the same letter
// in it. Letter '.' means an empty space, so don't win if we have five .'s in a row.
//Return true if there's a winner, false otherwise.
//Write the winning character into the winner parameter
//If the board is invalid (two+ winners, etc.) set error to true, otherwise false
bool check_winner(vector< vector<char> > &arr, char &winner, bool &error)
{
    //YOU: Write all this
    char temp = EMPTY;
    int count = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (arr[j][i] == EMPTY)
                break;
            if (arr[0][i] != EMPTY)
            {
                temp = arr[0][i];

                if (arr[j][i] == temp)
                {
                    count++;
                }
                else if (arr[j][i] == temp)
                {
                    count = 0;
                    break;
                }
                if (count == MAX_SIZE && arr[j][i] == temp)
                {
                    error = false;
                    winner = temp;
                    return true;
                }
            }
        }
        count = 0;
    }

    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (arr[i][j] == EMPTY)
                break;
            if (arr[i][0] != EMPTY)
            {
                temp = arr[i][0];

                if (arr[i][j] == temp)
                {
                    count++;
                }
                else if (arr[i][j] == temp)
                {
                    count = 0;
                    break;
                }
                if (count == MAX_SIZE && arr[i][j] == temp)
                {
                    error = false;
                    winner = temp;
                    return true;
                }
            }
        }
        count = 0;
    }

    temp = arr[0][0];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (arr[i][i] == EMPTY)
            break;

        else if (arr[i][i] != EMPTY)
        {
            if (arr[i][i] == temp)
            {
                count++;
            }

            else if (arr[i][i] != temp)
            {
                count = 0;
                break;
            }

            if (count == MAX_SIZE && arr[i][i] == temp)
            {
                error = false;
                winner = temp;
                return true;
            }
        }
    }

    count = 0;
    temp = arr[MAX_SIZE - 1][0];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (arr[MAX_SIZE - i - 1][i] == EMPTY)
            break;

        else if (arr[MAX_SIZE - i - 1][i] != EMPTY)
        {
            if (arr[MAX_SIZE - i - 1][i] == temp)
            {
                count++;
            }

            else if (arr[MAX_SIZE - i - 1][i] != temp)
            {
                count = 0;
                break;
            }

            if (count == MAX_SIZE && arr[MAX_SIZE - i - 1][i] == temp)
            {
                error = false;
                winner = temp;
                return true;
            }
        }
    }
    count = 0;

    if (num_of_moves >= (MAX_SIZE * MAX_SIZE))
    {
        error = false;
        winner = TIE;
        return true;
    }

    return false;
}

void waiter(string error = "")
{
    cout << error << "Press any key to continue.\n";
    string nothing;
    cin >> nothing;
}

bool monteCarlo(vector< vector<char> >arr, int &initX, int &initY)
{
    bool first = true;
    char whosTurn = '*';
    
    srand(time(NULL));
    while (true)
    {

        int x = rand() % MAX_SIZE;
        int y = rand() % MAX_SIZE;
        bool temp = true;


            if (x < 0 || x > MAX_SIZE)
            {
                temp = false;
            }
            if (y < 0 || y > MAX_SIZE)
            {
                temp = false;
            }

            if (!temp)
            {
                continue;                                     //Let them reenter the move
            }

        //YOU: Check for the spot being filled already
        bool is_open = true;

        if (arr[y][x] != EMPTY)
        {
            is_open = false;
        }
        if (!is_open)
        {
            //cout << "x: " << x << "y:" << y << endl;
            continue; //Let them reenter the move
        }
        else
        {

            //YOU: Enter the move onto the board here
            //my_array[y][x] = input;
            arr[y][x] = whosTurn;
            num_of_moves++;
            whosTurn = (whosTurn == '*') ? 'p' : '*';
            if (first)
            {
                initX = x;
                initY = y;
                first = false;
            }
            //break;
        }
        char winner;
        bool error;
        if (check_winner(arr, winner, error))
        {
            //Print win message and/or error message here

            if (error)
            {
            }
            else
            {
                if (winner == AI)
                    return true;
                else if (winner == TIE)
                    return false;
                else
                    return false;
            }
        }

    }
}

int main()
{
    //char my_array[MAX_SIZE][MAX_SIZE] = {}; //= {} means initialize to zero
    vector< vector<char> > my_array( MAX_SIZE , vector<char> (MAX_SIZE, '0'));
    //Initialize the random number generator

    //Start with empty board
    clear_array(my_array);

    while (true)
    {
        system("clear"); //Clear the screen
        print_array(my_array);
        if (!cpuGo)
        {
            //Handle input and check for errors
            cout << "Input x and y coordinates followed by a letter (letter 'Q' to quit): ";
            int x, y;
            char input;
            cin >> x;
            if (!cin)
                exit(EXIT_FAILURE);
            cin >> y;
            if (!cin)
                exit(EXIT_FAILURE);
            cin >> input;
            if (!cin)
                exit(EXIT_FAILURE);
            if (input == 'Q')
                exit(EXIT_SUCCESS);
            if (!isalpha(input))
                exit(EXIT_FAILURE);

            //YOU: Check to see if the coordinate is out of bounds

            bool temp = true;

            if (x < 0 || x > MAX_SIZE)
            {
                temp = false;
            }
            if (y < 0 || y > MAX_SIZE)
            {
                temp = false;
            }

            if (!temp)
            {
                waiter("That coordinate is out of bounds. "); //Pause
                continue;                                     //Let them reenter the move
            }

            //YOU: Check for the spot being filled already
            bool is_open = true;

            if (my_array[y][x] != EMPTY)
            {
                is_open = false;
            }
            if (!is_open)
            {
                waiter("That spot is already taken. "); //Pause
                continue;                               //Let them reenter the move
            }
            else
            {
                //YOU: Enter the move onto the board here
                //my_array[y][x] = input;
                my_array[y][x] = 'p';
                num_of_moves++;
            }
            cpuGo = !cpuGo;
        }

        else
        {
            int results[MAX_SIZE][MAX_SIZE] = {}; //= {} means initialize to zero
            memset(results, -1, sizeof(results));

            int ogNumMoves = num_of_moves;
            int tempX, tempY = -1;
            for (size_t i = 0; i < 3000; i++)
            {
                //cout << i << endl;
                bool winSim = monteCarlo(my_array, tempX, tempY);
                if (winSim)
                {
                    if (results[tempY][tempX] < 0){
                        results[tempY][tempX] = 0;
                    }
                    results[tempY][tempX]++;
                }
                else {
                    if (results[tempY][tempX] < 0){
                        results[tempY][tempX] = 0;
                    }
                }
                tempX = -1;
                tempY = -1;
            }
            int max = -1;
            for (size_t i = 0; i < MAX_SIZE; i++)
            {
                for (size_t j = 0; j < MAX_SIZE; j++)
                {
                    if (results[j][i] > max)
                    {
                        max = results[j][i];
                        tempX = i;
                        tempY = j;
                    }
                }
            }   
            my_array[tempY][tempX] = AI;
            num_of_moves = ogNumMoves + 1;
            cpuGo = !cpuGo;
        }

        //Extra Credit: Write an AI to play against you

        char winner;
        bool error;
        if (check_winner(my_array, winner, error))
        {
            //Print win message and/or error message here
            system("clear"); //Clear the screen
            print_array(my_array);
            if (error)
                cout << "Error: Multiple winners!\n";
            else
            {
                if (winner == AI)
                    cout << "Failure! The AI has beaten you!\n";
                else if (winner == TIE)
                    cout << "A tie has occured!\n";
                else
                    cout << "Congrats! Player " << winner << " has won!\n";
                exit(EXIT_SUCCESS);
            }
            waiter(); //Pause
        }
    }
}

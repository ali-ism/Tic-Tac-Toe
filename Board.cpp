#include <iostream>

using namespace std;

void print_board(const char (&board)[3][3])
{
    cout << "     1     2     3" << endl;
    cout << " 1 " << "  " << board[0][0] << "  " << "|" << "  " << board[0][1] <<  "  " << "|" << "  " << board[0][2]
         << "  " << endl;
    cout << "   " <<"-----------------" << endl;
    cout << " 2 " << "  " << board[1][0] << "  " << "|" << "  " << board[1][1] <<  "  " << "|" << "  " << board[1][2]
         << "  " << endl;
    cout << "   " << "-----------------" << endl;
    cout << " 3 " << "  " << board[2][0] << "  " << "|" << "  " << board[2][1] <<  "  " << "|" << "  " << board[2][2]
         << "  " << endl;
}

char declare_winner(const char (&board)[3][3])
{
    /*
     * Line coordinates are:
     *  00 01 02
     *  00 11 22
     *  10 11 12
     *  20 21 22
     *  20 11 02
     *  00 10 20
     *  01 11 21
     *  02 12 22
    */

    // X is winner?
    if((board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X') ||
       (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') ||
       (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X') ||
       (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X') ||
       (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X') ||
       (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X') ||
       (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X') ||
       (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X'))
    {
        return 'X';
    }

        // O is winner?
    else if((board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O') ||
            (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') ||
            (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O') ||
            (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O') ||
            (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O') ||
            (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O') ||
            (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O') ||
            (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O'))
    {
        return 'O';
    }
        // tie?
    else
    {
        bool is_tie = true;
        for(int i = 0; i < 3; i++) // NOLINT(modernize-loop-convert)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' ')
                {
                    is_tie = false;
                    goto NoTie;
                }
            }
        }
        NoTie:
        if(is_tie)
        {
            return 'T';
        }
    }
    return 'C'; // no winner
}
#include "Player.h"

bool evaluate_winner(char& winner)
{
    if(winner == 'X')
    {
        cout << "Player X Wins!" << endl;
        return true;
    }
    else if(winner == 'O')
    {
        cout << "Player O Wins!" << endl;
        return true;
    }
    else if(winner == 'T')
    {
        cout << "It's a Tie!" << endl;
        return true;
    }
    return false;
}

int main()
{
    // create playing board
    char board[3][3] = {
            {' ',' ',' '},
            {' ',' ',' '},
            {' ',' ',' '}
    };

    // create players
    Player playerX('X');
    MinimaxAI playerO('O');
    //HeuristicAI playerO('O');

    // play
    print_board(board);
    while(true)
    {
        playerX.make_move(board);
        print_board(board);
        char winner;
        winner = declare_winner(board);
        if(evaluate_winner(winner))
            break;
        playerO.make_move(board);
        print_board(board);
        winner = declare_winner(board);
        if(evaluate_winner(winner))
            break;
    }
    return 0;
}
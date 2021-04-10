#include "Player.h"

void Player::make_move(char (&board)[3][3])
{
    // ask for coordinates
    cout << "Player " << _type << endl;
    cout << "Enter x position: " << flush;
    int coordinates[2];
    cin >> coordinates[0];
    if(coordinates[0] < 1 || coordinates[0] > 3)
        throw out_of_range("Invalid move!");
    cout << "Enter y position: " << flush;
    cin >> coordinates[1];
    if(coordinates[1] < 1 || coordinates[1] > 3)
        throw out_of_range("Invalid move!");
    if(board[coordinates[0] - 1][coordinates[1] - 1] != ' ')
        throw invalid_argument("This cell is already occupied!");
    // make the move
    board[coordinates[0] - 1][coordinates[1] - 1] = _type;
}

vector<vector<int>> HeuristicAI::_get_legal_moves(const char (&board)[3][3])
{
    vector<vector<int>> legal_moves;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                vector<int> coordinates = {i, j};
                legal_moves.push_back(coordinates);
            }
        }
    }
    legal_moves.shrink_to_fit();
    return legal_moves;
}

void HeuristicAI::_make_random_move(char (&board)[3][3])
{
    // get legal moves
    vector<vector<int>> legal_moves = _get_legal_moves(board);

    /* test legal_moves vector
    cout << "Displaying legal_moves." << endl;
    for(unsigned int i = 0; i < legal_moves.size(); i++)
    {
        for (unsigned int j = 0; j < legal_moves[i].size(); j++)
        {
            cout << legal_moves[i][j] << " " << flush;
        }
        cout << " ; " << flush;
    }
    cout << endl;
    */ //end test legal_moves vector

    // pick a random legal move
    static mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> uni(0,legal_moves.size() - 1);
    int randint = uni(rng);
    vector<int> move = legal_moves[randint];

    // execute move
    board[move[0]][move[1]] = _type;
    cout << endl << "AI's turn: Random Move" << endl;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
int* HeuristicAI::_winning_moves(const char (&board)[3][3], const char& type)
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
    int *coordinates = new int[2];
    auto check_line = [&board, &type, &coordinates](const int a[2], const int b[2], const int c[2])
    {
        if(board[a[0]][a[1]] == type && board[b[0]][b[1]] == type && board[c[0]][c[1]] == ' ')
        {
            coordinates[0] = c[0];
            coordinates[1] = c[1];
        }
        else if(board[a[0]][a[1]] == type && board[b[0]][b[1]] == ' ' && board[c[0]][c[1]] == type)
        {
            coordinates[0] = b[0];
            coordinates[1] = b[1];
        }
        else if(board[a[0]][a[1]] == ' ' && board[b[0]][b[1]] == type && board[c[0]][c[1]] == type)
        {
            coordinates[0] = a[0];
            coordinates[1] = a[1];
        }
        else // set coordinates to 9,9 implying that no winning move was found here
        {
            coordinates[0] = 9;
            coordinates[1] = 9;
        }
    };

    int a[2] = {0, 0}, b[2] = {0, 1}, c[2] = {0, 2};
    check_line(a,b,c);
    if(coordinates[0] != 9)
        return coordinates;

    a[0] = 0; a[1] = 0; b[0] = 1; b[1] = 1; c[0] = 2; c[1] = 2;
    check_line(a,b,c);
    if(coordinates[0] != 9)
        return coordinates;

    a[0] = 1; a[1] = 0; b[0] = 1; b[1] = 1; c[0] = 1; c[1] = 2;
    check_line(a,b,c);
    if(coordinates[0] != 9)
        return coordinates;

    a[0] = 2; a[1] = 0; b[0] = 2; b[1] = 1; c[0] = 2; c[1] = 2;
    check_line(a,b,c);
    if(coordinates[0] != 9)
        return coordinates;

    a[0] = 2; a[1] = 0; b[0] = 1; b[1] = 1; c[0] = 0; c[1] = 2;
    check_line(a,b,c);
    if(coordinates[0] != 9)
        return coordinates;

    a[0] = 0; a[1] = 0; b[0] = 1; b[1] = 0; c[0] = 2; c[1] = 0;
    check_line(a,b,c);
    if(coordinates[0] != 9)
        return coordinates;

    a[0] = 0; a[1] = 1; b[0] = 1; b[1] = 1; c[0] = 2; c[1] = 1;
    check_line(a,b,c);
    if(coordinates[0] != 9)
        return coordinates;

    a[0] = 0; a[1] = 2; b[0] = 1; b[1] = 2; c[0] = 2; c[1] = 2;
    check_line(a,b,c);
    if(coordinates[0] != 9)
        return coordinates;

    return coordinates;
}
#pragma clang diagnostic pop

void HeuristicAI::make_move(char (&board)[3][3])
{
    // check for available winning move
    int *winning_move = _winning_moves(board, _type);
    if(winning_move[0] != 9)
    {
        board[winning_move[0]][winning_move[1]] = _type;
        delete[] winning_move;
        cout << endl << "AI's turn: Go for the Win!" << endl;
        return;
    }
    // check for opponent winning move
    char opponent;
    if(_type == 'O')
        opponent = 'X';
    else
        opponent = 'O';
    winning_move = _winning_moves(board, opponent);
    if(winning_move[0] != 9)
    {
        board[winning_move[0]][winning_move[1]] = _type;
        delete[] winning_move;
        cout << endl << "AI's turn: Block opponent." << endl;
    }
    else
        _make_random_move(board); //make random move
}

int MinimaxAI::_minimax(char (&board)[3][3], int depth, char player)
{
    // define opponent
    char opponent;
    if(_type == 'X')
        opponent = 'O';
    else
        opponent = 'X';

    char winner = declare_winner(board);
    if(winner == _type)
        return 20 - depth;
    else if(winner == opponent)
        return 20 + depth;
    else if(winner == 'T')
        return 0;

    vector<vector<int>> legal_moves = _get_legal_moves(board);

    if(player == _type)
    {
        int score = - 1000;
        for(int i = 0; i < legal_moves.size(); i++)
        {
            board[legal_moves[i][0]][legal_moves[i][1]] = player;
            score = max(score, _minimax(board, depth++, opponent));
            board[legal_moves[i][0]][legal_moves[i][1]] = ' ';
        }
        return score;
    }
    else
    {
        int score = 1000;
        for(int i = 0; i < legal_moves.size(); i++)
        {
            board[legal_moves[i][0]][legal_moves[i][1]] = player;
            score = min(score, _minimax(board, depth++, _type));
            board[legal_moves[i][0]][legal_moves[i][1]] = ' ';
        }
        return score;
    }
}

void MinimaxAI::make_move(char (&board)[3][3])
{
    // define opponent
    char opponent;
    if(_type == 'X')
        opponent = 'O';
    else
        opponent = 'X';

    vector<vector<int>> legal_moves = _get_legal_moves(board);

    int best_score = -1000;
    int best_move[2];

    for(int i = 0; i < legal_moves.size(); i++)
    {
        board[legal_moves[i][0]][legal_moves[i][1]] = _type;
        int score = _minimax(board,0,opponent);
        board[legal_moves[i][0]][legal_moves[i][1]] = ' ';
        if(score > best_score)
        {
            best_score = score;
            best_move[0] = legal_moves[i][0];
            best_move[1] = legal_moves[i][1];
        }
    }

    board[best_move[0]][best_move[1]] = _type;
    cout << endl << "AI's Turn" << endl;
}
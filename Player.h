#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H

#include <iostream>
#include <random>
#include <vector>
#include <stdexcept>
#include <chrono>
#include "Board.h"

using namespace std;

class Player
{
protected:
    char _type;
public:
    explicit Player(char type)
    {
        if(type != 'X' && type != 'O')
            throw invalid_argument("Player type is either X or O!");
        _type = type;
    }

    virtual void make_move(char (&board)[3][3]);
};

class HeuristicAI : public Player
        // an AI that makes in order of preference: a move that wins, a move that blocks a loss and a random move
{
public:
    using Player::Player;
    void make_move(char (&board)[3][3]) override;

protected:
    int* _winning_moves(const char (&board)[3][3], const char& type);
    static vector<vector<int>> _get_legal_moves(const char (&board)[3][3]);

private:
    void _make_random_move(char (&board)[3][3]);
};

class MinimaxAI : public HeuristicAI
{
public:
    using HeuristicAI::HeuristicAI;
    void make_move(char (&board)[3][3]) override;

private:
    int _minimax(char (&board)[3][3], int depth, char player);
};
#endif //TICTACTOE_PLAYER_H

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

enum Action {
    Left,
    Up,
    Right,
    Down,
};

bool isValidMove(int state, int action, int size);
int makeAction(int state, int action, int size);
void print_lookup_table(vector<vector<double>> QTable, int size);
vector<vector<double>> init_board(int size, pair<int, int> coord);
int train(int state, int size, vector<vector<double>>& QTable, bool& found, bool isoptimal, pair<int, int> coord);
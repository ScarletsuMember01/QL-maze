#include "Header.h"

using namespace std;
int numberfind = 0;

bool isValidMove(int state, int action, int size) {
    // To check if next state is valid from a side of the grid
    if (((state % size) == 0) && (action == 0))
        return false;
    if ((state < size) && (action == 1))
        return false;
    if (((state % size) == (size - 1)) && (action == 2))
        return false;
    if ((state >= (size * (size - 1))) && (action == 3))
        return false;
    return true;
}

int makeAction(int state, int action, int size) {
    if (!isValidMove(state, action, size))
        return state;
    switch (action)
    {
    case 0:
        //LEFT
        state -= 1;
        break;
    case 1:
        //UP
        state -= size;
        break;
    case 2:
        //RIGHT
        state += 1;
        break;
    case 3:
        //DOWN
        state += size;
        break;
    default:
        break;
    }
    return state;
}

void print_lookup_table(vector<vector<double>> QTable, int size) {
    /*
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < 4; j++) {
            cout << QTable[i][j] << "|";
        }
        cerr << "\n--------------" << endl;
    }
    */
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << *max_element(QTable[i * size + j].begin(), QTable[i * size + j].end()) << "|";
        }
        cerr << "\n--------------" << endl;
    }
}

vector<vector<double>> init_board(int size, pair<int, int> coord) {
    vector<vector<double>> plateau;
    for (int row = 0; row < size; row++) {
        vector<double> cases;
        for (int col = 0; col < size; col++) {
            if (col == coord.first && row == coord.second)
                cases.push_back(30);
            else if (col == (size / 3) && row < (size / 3 + size / 2))
                cases.push_back(-50);
            else
                cases.push_back(-1);
        }
        plateau.push_back(cases);
    }
    return plateau;
}

int train(int state, int size, vector<vector<double>>& QTable, bool& found, bool isoptimal, pair<int,int> coord)
{

    //damier de size * size, donc 16 pixel possible en position, qui auront chacun 4 deplacement possible (haut, bas, gauche, droite)
    vector<vector<double>> plateau = init_board(size, coord);

    // We suppose order is : LEFT UP RIGHT DOWN
    double exploration_rate = 0.4;
    if (numberfind < 10)
        exploration_rate = 1;
    if (isoptimal)
        exploration_rate = 0;
    // Importance des futures moves sur le move actuel
    double gamma = 0.99;
    //action a venir choisis par le player
    int action;
    double lr = 0.2;
    int nstate = -1;

    double r = (float)rand() / RAND_MAX;
    if (r < exploration_rate) {
        //TODO exploration
        action = floor(((double)rand() / (RAND_MAX+1)) * 4);
    }
    else {
        //TODO exploitation
        action = max_element(QTable[state].begin(), QTable[state].end()) - QTable[state].begin();
    }
    nstate = makeAction(state, action, size);
    int new_action = max_element(QTable[nstate].begin(), QTable[nstate].end()) - QTable[nstate].begin();
    //update of lookup table
    if (plateau[state / size][state % size] == 30 || plateau[state / size][state % size] == -50) {
        numberfind += plateau[state / size][state % size] == 30;
        found = true;
        return state;
    }
    QTable[state][action] = QTable[state][action] + lr * (plateau[nstate / size][nstate % size] + gamma * QTable[nstate][new_action] - QTable[state][action]);
    state = nstate;
    return state;
}
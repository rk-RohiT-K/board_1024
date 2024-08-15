#include "Board.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

using std::cout;
using std::vector;

Board::Board() {
    max = 0;
    target = 32;
    numCols = 3;
    numRows = 3;
    allocateMemory();
}

Board::Board(int m) {
    max = 0;
    target = 32;
    numRows = m >= 1 ? m : 3;
    numCols = m >= 1 ? m : 3;
    allocateMemory();
}

Board::Board(int m, int n) {
    max = 0;
    target = 32;
    numRows = m >= 1 ? m : 3;
    numCols = n >= 1 ? n : 3;
    allocateMemory();
}

void Board::allocateMemory() {
    panel = new int* [numRows];
    for (int i = 0; i < numRows; ++i)
        panel[i] = new int[numCols];
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            panel[i][j] = 0;
}

Board::~Board() {
    for(int i = 0; i < numRows; i++)
        delete[] panel[i];
    delete[] panel;
}

void Board::clear() {
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            panel[i][j] = 0;
}

void Board::print() const {
    for(int i = 0; i < 2 * numRows + 1; i++) {
        if(i % 2) {
            for(int j = 0; j < numCols; j++) {
                int n = panel[i/2][j];
                if(n > 0) {
                    int digits = floor(log(n) / log(10)) + 1;
                    switch (digits) {
                        case 1:
                            cout << "|   " << n;
                            break;
                        case 2:
                            cout << "|  " << n;
                            break;
                        case 3:
                            cout << "| " << n;
                            break;
                        case 4:
                            cout << "|" << n;
                            break;
                    }
                } else {
                    cout << "|    ";
                }
            }
            cout << "|\n";
        } else {
            for(int j = 0; j < numCols; j++)
                cout << "+----";
            cout << "+\n";
        }
    }
}

bool Board::noAdjacentSameValue() const {
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if(!panel[i][j])
                return false;
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j) {
            if (i - 1 >= 0 && panel[i][j] == panel[i - 1][j])
                return false;
            if (i + 1 < numRows && panel[i][j] == panel[i + 1][j])
                return false;
            if (j - 1 >= 0 && panel[i][j] == panel[i][j - 1])
                return false;
            if (j + 1 < numCols && panel[i][j] == panel[i][j + 1])
                return false;
        }
    return true;
}

void Board::selectRandomCell(int& row, int& col) {
    vector<int> cells;
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if(!panel[i][j])
                cells.push_back(i * numCols + j);

    if(cells.empty() && noAdjacentSameValue()) {
        cout << "Game over. Try again.\n";
    } else {
        if(!cells.empty()) {
            srand(static_cast<unsigned>(time(nullptr)));
            int n = cells[rand() % cells.size()];
            row = n / numCols;
            col = n % numCols;
            panel[row][col] = 1;
            print();
            if(cells.size() == 1 && noAdjacentSameValue())
                cout << "Game over. Try again.\n";
        }
    }
}

void Board::updateMax() {
    max = 0;
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if (panel[i][j] > max)
                max = panel[i][j];
}

void Board::pressUp() {
    vector<int> col(numRows);
    for(int j = 0; j < numCols; ++j) {
        int index = 0;
        for(int i = 0; i < numRows; ++i)
            if(panel[i][j])
                col[index++] = panel[i][j];
        for(int i = 0; i < numRows - 1; ++i)
            if(col[i] == col[i + 1]) {
                col[i] *= 2;
                col[i + 1] = 0;
            }
        index = 0;
        for(int i = 0; i < numRows; ++i)
            if(col[i])
                panel[index++][j] = col[i];
        while(index < numRows)
            panel[index++][j] = 0;
    }
    updateMax();
    int r, c;
    selectRandomCell(r, c);
}

void Board::pressDown() {
    vector<int> col(numRows);
    for(int j = 0; j < numCols; ++j) {
        int index = numRows - 1;
        for(int i = numRows - 1; i >= 0; --i)
            if(panel[i][j])
                col[index--] = panel[i][j];
        for(int i = numRows - 1; i > 0; --i)
            if(col[i] == col[i - 1]) {
                col[i] *= 2;
                col[i - 1] = 0;
            }
        index = numRows - 1;
        for(int i = numRows - 1; i >= 0; --i)
            if(col[i])
                panel[index--][j] = col[i];
        while(index >= 0)
            panel[index--][j] = 0;
    }
    updateMax();
    int r, c;
    selectRandomCell(r, c);
}

void Board::pressLeft() {
    vector<int> row(numCols);
    for(int i = 0; i < numRows; ++i) {
        int index = 0;
        for(int j = 0; j < numCols; ++j)
            if(panel[i][j])
                row[index++] = panel[i][j];
        for(int j = 0; j < numCols - 1; ++j)
            if(row[j] == row[j + 1]) {
                row[j] *= 2;
                row[j + 1] = 0;
            }
        index = 0;
        for(int j = 0; j < numCols; ++j)
            if(row[j])
                panel[i][index++] = row[j];
        while(index < numCols)
            panel[i][index++] = 0;
    }
    updateMax();
    int r, c;
    selectRandomCell(r, c);
}

void Board::pressRight() {
    vector<int> row(numCols);
    for(int i = 0; i < numRows; ++i) {
        int index = numCols - 1;
        for(int j = numCols - 1; j >= 0; --j)
            if(panel[i][j])
                row[index--] = panel[i][j];
        for(int j = numCols - 1; j > 0; --j)
            if(row[j] == row[j - 1]) {
                row[j] *= 2;
                row[j - 1] = 0;
            }
        index = numCols - 1;
        for(int j = numCols - 1; j >= 0; --j)
            if(row[j])
                panel[i][index--] = row[j];
        while(index >= 0)
            panel[i][index--] = 0;
    }
    updateMax();
    int r, c;
    selectRandomCell(r, c);
}

void Board::setGoal(int goal) {
    target = goal;
}

void Board::start() {
    clear();
    int r, c;
    selectRandomCell(r, c);
    selectRandomCell(r, c);
    print();
}

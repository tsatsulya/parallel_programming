#pragma once

#include <vector>
#include <cassert>
#include <iostream>

static bool check_coord(int i, int j, int m, int k) {
    if (i < 0 || i > m - 1) return false;
    if (j < 0 || j > m - 1) return false;
    return true;
}

typedef class grid {
public:
    int k, m;
    double t, h;
    double coef;
    std::vector<std::vector<double>> field;

    grid(int k_, int m_, double t_, double h_, double coef_) {
        k = k_; t = t_;
        m = m_; h = h_;
        coef = coef_;
        field.resize(k, std::vector<double>(m));
    }

    void set_initials(double (*phi)(int, double), double (*psi)(int, double)) {
        for (int i = 0; i < m; ++i) {
            field[0][i] = phi(i, h);
        }
        for (int j = 0; j < k; ++j) {
            field[j][0] = psi(j, h);
        }
        for (int i = 1; i < m; i++) {
            field[i][m - 1] = field[i-1][m-1] - (t * i);
        }
    }

    double calculate_cell(int i, int j) {
        if (i == 0 || j == 0) return field[i][j];
        assert(check_coord);

        double previous_row = field[i-1][j-1] - 2 * field[i-1][j] + field[i-1][j+1];
        return field[i][j-1] + coef*t*previous_row/h/h;
    }

    void calculate_row(int i) {
        for (int j = 1; j < m-1; ++j)
            field[i][j] = calculate_cell(i, j);
    }

    void calculate_field() {
        for (int i = 1; i < k; ++i) {
            calculate_row(i);}
    }

    void print_field() {
        std::cout << "\n";
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << std::to_string(field[i][j]) + "\t";
            }
            std::cout << "\n";
        }
    }
} grid;
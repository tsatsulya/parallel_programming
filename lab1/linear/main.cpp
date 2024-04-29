#include "equidistant_grid.h"
#include <iostream>

double phi(int x, double h) {return x * 1.0;}
double psi(int x, double h) {return x * 2.0;}

int main() {
    int k = 10, m = 10;
    double t = 1.0, h = 1.0;
    double coef = 1.0;
    grid g(k, m, t, h, coef);
    g.print_field();
    g.set_initials(&phi, &psi);
    g.print_field();
    g.calculate_field();
    g.print_field();

    return 0;
}
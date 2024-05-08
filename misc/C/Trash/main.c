#include <stdio.h>
#include <math.h>

double cvh(long i, long gf, double tv) {
    return (i + gf) / tv;
}

int main() {
    double salario = 25000 * 12 + 25000/2;
    double r1 = salario * .25;
    double i1 = (salario + r1) * .36;
    double I = salario + r1 + i1;
    printf("\nI Salario: %lf", salario);
    printf("\nR1: %lf", r1);
    printf("\nI1: %lf", i1);
    printf("\nI: %lf", I);

    double gf = 30000 * 12;
    printf("\n\nGF = G: %lf", gf);
    double r = gf * .25;
    double i = (gf + r) * .36;
    gf = gf + r + i;
    printf("\nR: %lf", r);
    printf("\nI: %lf", i);
    printf("\nI: %lf", gf);

    int ht = 8 * 5 * 52;
    printf("\n\nTV: %d", ht);
    int hv = 18 * 8;
    printf("\nHV: %d", hv);
    int he = 3 * 8;
    printf("\nHE: %d", he);
    float ha = ht * .21;
    printf("\nHA: %f", ha);
    float hp = ht * .06;
    printf("\nHP: %f", hp);
    double tv = ht - (hv + he + ha + hp);
    printf("\nTV - Todo: %lf", tv);

    printf("\nCVH: %lf", cvh(I, gf, tv));

}
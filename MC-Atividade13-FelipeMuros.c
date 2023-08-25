/*Considerando o Sistema abaixo, implemente o algoritmo de Decomposição de Cholesky para solucioná-lo.
Devem ser criadas as matrizes A, R e Rt
, além dos vetores x, y e b.
Obs. 1.: Todas as matrizes e vetores utilizados devem ser declarados na função main;
Obs. 2.: Seu algoritmo pode ser testado com outro Sistema;
Obs. 3.: Lembre-se que você terá que utilizar os algoritmos de solução de Sistemas Triangulares Superiores e Inferiores (já estudados) para resolver o Sistema.
A = { { 1,2,4 }, { 2, 8,10 }, { 4, 10, 26 } }
y= { 1, -4, 10 }
*/

#include <stdio.h>
#include <math.h>

#define n 3

void calcularR(float A[n][n], float R[n][n]);
void calcularRT(float R[n][n], float RT[n][n]);
void triangularInferior(float Rt[n][n], float y[n], float b[n]);
void triangularSuperior(float R[n][n], float x[n], float y[n]);

int main(){

    float A[n][n] = { { 1,2,4 }, { 2, 8, 10 }, { 4, 10, 26 } }, 
    b[n] = { 1, -4, 10 }, 
    x[n], y[n], 
    R[n][n], Rt[n][n];
    
    calcularR(A, R);
    calcularRT(R, Rt);

    triangularInferior(Rt, y, b);
    triangularSuperior(R, x, y);

    printf("\n\nResuntado do sistema:\n");
    for (int i = 0; i < n; i++){
        printf("x[%d] = %f\n", i, x[i]);
    }

    printf("\n\n");
    return 0;
}

void calcularR(float A[n][n], float R[n][n]){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float sum = 0;
            if (j == i) {
                for (int k = 0; k < j; k++)
                    sum += pow(R[k][i], 2);
                R[i][i] = sqrt(A[i][i] - sum);
            } else {
                for (int k = 0; k < j; k++)
                    sum += R[k][i] * R[k][j];
                R[i][j] = (A[i][j] - sum) / R[i][i];
            }
        }
    }
}

void calcularRT(float R[n][n], float RT[n][n]){
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= i; j++){
            RT[i][j] = R[j][i];
        }
    }
}

void triangularInferior(float Rt[n][n], float y[n], float b[n]){
    float soma = 0;
    for (int i = 0; i < n; i++){
        soma = 0;
        for (int j = 0; j < i; j++){
            soma += Rt[i][j] * y[j];
        }
        y[i] = (b[i] - soma) / Rt[i][i];
    }
}

void triangularSuperior(float R[n][n], float x[n], float y[n]){
    float soma = 0;
    for (int i = n - 1; i >= 0; i--){
        soma = 0;
        for (int j = i + 1; j < n; j++){
            soma += R[i][j] * x[j];
        }
        x[i] = (y[i] - soma) / R[i][i];
    }
}
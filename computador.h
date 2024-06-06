#ifndef COMPUTADOR_H
#define COMPUTADOR_H

int valorTabuleiro(int tabuleiro[8][8], int jogadorAtual);
void copiarTabuleiro(int tabuleiro[8][8]);
int miniMax(int tabuleiro[8][8], int profundidade, int jogador, int chamaMax);


#endif
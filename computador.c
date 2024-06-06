#include "computador.h"
#include "game.c"

//Calcula e devolve o valor do tabuleiro com base no jogador atual
int valorTabuleiro(int tabuleiro[8][8], int jogadorAtual){

    int adversario = jogadorAtual == 1 ? 2 : 1;
    float valor;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tabuleiro[i][j] == jogadorAtual){
                valor++;
            }
            if(tabuleiro[i][j] == adversario){
                valor--;
            }
        } // Mais pra frente vou evaluar as melhores posicoes no tabuleiro e vai ser += ou -= valorPos
    }

    return valor;
}

void copiarTabuleiro(int tabuleiroOriginal[8][8], int tabuleiroCopia){// void passar os dois //2 for
    
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            tabuleiroCopia[i][j] = tabuleiroOriginal[i][j];
        }
    }

    return tabuleiroCopia;
}

int miniMax(int tabuleiro[8][8], int profundidade, int jogador, int chamaMax){
    int valorMaximador =  -100000;
    int valorMinimizador = 100000;
    int camposCopia[8][8];
    int pontuacao;
    int adversario = jogador == 1 ? 2 : 1;

    if(profundidade == 0){
        return valorTabuleiro(tabuleiro);
    }

    camposCopia = copiarTabuleiro(tabuleiro);
    limparJogadasValidas(jogador, camposCopia);
    jogadasValidas(camposCopia);


    for(int i = 0; i < 8; i++){
        for(int j = 0;j < 8; j++){
            if(camposCopia[i][j] == 3){
                comerPecas(int jogador, i, j, camposcopia);
                pontuacao = miniMax(copiaCampos, profundidade - 1, adversario, 1 - chamaMax);
                if(chamaMax){
                    if(pontuacao > valorMaximizador){
                        valorMaximizador = pontuacao;
                        return valorMinimizador;
                    }
                }else{
                    if(pontuacao < valorMinimizador){
                        valorMinimizador = pontuacao;
                        return valorMinimizador;
                    }
                }
            }
            
        }
    }

}
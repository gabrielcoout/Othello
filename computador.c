#include "computador.h"
#include "game.c"

// Calcula e devolve o valor do tabuleiro com base no jogador atual
int valorTabuleiro(int tabuleiro[8][8], int jogadorAtual){

    int adversario = jogadorAtual == 1 ? 2 : 1;
    float valor;

    // valores de cada casa em realcao a posicao no tabuleiro
    float valoresTabuleiro[8][8] = {
        1.5, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.5,
        1.2, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.2,
        1.2, 1.0, 1.1, 1.1, 1.1, 1.1, 1.0, 1.2,
        1.2, 1.0, 1.1, 1.0, 1.0, 1.1, 1.0, 1.2,
        1.2, 1.0, 1.1, 1.0, 1.0, 1.1, 1.0, 1.2,
        1.2, 1.0, 1.1, 1.1, 1.1, 1.1, 1.0, 1.2,
        1.2, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.2,
        1.5, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.5,
    };

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tabuleiro[i][j] == jogadorAtual){
                valor += valoresTabuleiro[i][j];
            }
            if(tabuleiro[i][j] == adversario){
                valor -= valoresTabuleiro[i][j];
            }
        }
    }

    return valor;
}

void copiarTabuleiro(int tabuleiroOriginal[8][8], int tabuleiroCopia){// void passar os dois //2 for
    
    //Loop para copiar os valores
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            tabuleiroCopia[i][j] = tabuleiroOriginal[i][j];
        }
    }

    return tabuleiroCopia;
}

float miniMax(int tabuleiro[8][8], int profundidade, int jogador, int chamaMax){
    int valorMaximador =  -100000;
    int valorMinimizador = 100000;
    int camposCopia[8][8];
    int pontuacao;
    int adversario = jogador == 1 ? 2 : 1;

    //Ponto de parada do miniMax
    if(profundidade == 0){
        return valorTabuleiro(tabuleiro);
    }

    //verificar se o jogo acabou
    /*{
        codigo aq
        e retornar o valor tabuleiro
    }*/

    /*
    
    lembrar de verificar se o jogador tem vez ou passa pro prox

    */
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
                    }
                }else{
                    if(pontuacao < valorMinimizador){
                        valorMinimizador = pontuacao;
                    }
                }
            }
            
        }
    }

    if(chamaMax){
        return valorMaximizador;
    }else{
        return valorMinimizador;
    }

}
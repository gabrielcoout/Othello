#include <stdio.h>
#include "aux.h"

//Declaracao das funcoes
void imprimirJogo(int campos[64]);
void iniciarJogo(int campos[64]);
int jogada(int *jogador, int campos[64]);
void jogadasValidas(int jogador, int campos[64]);
void listarJogadas(int campos[64]);
// int jogadasValidas(int jogador, int campos[64]);
void limparJogadasValidas(int campos[64]);

//funcoes de debug
// void debugJogo(int campos[64]);

int main(){

	//declaracao de variaveis
	int campos[64];
	int jogador = 1;


	iniciarJogo(campos);
    while (1){
    jogadasValidas(jogador, campos);
    imprimirJogo(campos);
    listarJogadas(campos);
	jogada(&jogador, campos);
    limparJogadasValidas(campos);
    }
	return(0);
}

//Mostra na tela o tabuleiro do jogo com X e O para as respectivas jogadas de cada jogador
void imprimirJogo(int campos[64]) {
    printf("---------------------------------\n");
    for (int i = 0; i < 64; i++) {
        printf("|");
		switch (campos[i]){
            case 1: printf(" x "); break;
            case -1: printf(" o "); break;
            case 3: printf("( )"); break;
            default: printf("   "); break;
		}
        if ((i + 1) % 8 == 0) {
            printf("|\n---------------------------------\n");
        }
    }   
}

//Inicia o tabuleiro do jogo deixando somente com as pecas iniciais
void iniciarJogo(int campos[64]){
	for (int i = 0; i < 64; i++) {
			campos[i] = 0;
	}
		campos[27]=-1;
        campos[36]=-1;
        campos[28]=1;
        campos[35]=1;
}       

//Preenche o vetor do jogo de forma que a jogada é gravada
int jogada(int *jogador, int campos[64]){
	int linha, coluna;
	scanf("%d %d", &linha, &coluna);
    while (campos[8*(linha-1) + coluna-1]!=3 || linha>8 || linha<1 || coluna>8 || coluna<1){
        printf("Espaço inválido selecionado. Insira um espaço de jogada válido\n");
        scanf("%d %d", &linha, &coluna);
    }
    
	if(*jogador == 1){
		campos[(linha-1) * 8 + (coluna-1)] = 1;
		*jogador = -*jogador;
		return(0);
	}
	if (*jogador == -1){
		campos[(linha-1) * 8 + (coluna-1)] = -1;
		*jogador = -*jogador;
		return(0);
	}

	return(0);
}


void jogadasValidas(int jogador, int campos[64]){
    for (int i = 0; i < 64; i++){
        // Verifica quais poisções contém a peça do jogador atual
        if (campos[i]==jogador){
            int linha = i/8;
            int coluna = i%8;
            // Percorre as colunas e linhas da peca i
            for (int t = 0; t < 8; t++){
                int elemento_coluna = i+8*(t-linha);
                if (campos[elemento_coluna]==-jogador && elemento_coluna-8>0 && campos[elemento_coluna-8]==jogador){
                    campos[elemento_coluna+8]=3;
                
                }else if(campos[elemento_coluna]==-jogador && elemento_coluna+8<64 && campos[elemento_coluna+8]==jogador){
                    campos[elemento_coluna-8]=3;
                    
                }
                int elemento_linha = i + t - coluna;
                if (campos[elemento_linha]==-jogador && msm_linha(elemento_linha,elemento_linha-1) && campos[elemento_linha-1]==jogador){
                    campos[elemento_linha+1]=3;
                    
                }else if(campos[elemento_linha]==-jogador && msm_linha(elemento_linha,elemento_linha+1) && campos[elemento_linha+1]==jogador){
                    campos[elemento_linha-1]=3;
                    
                }
            }
            
            // Calcula o tamanho da diagonal principal
            int diag_principal = min(linha+1,coluna+1) + 8 -max(linha+1,coluna+1) ;
            int ajuste_dprincipal =  min(linha+1,coluna+1) - 1;

            // Percorre a diagonal principal
            for (int t = 0; t < diag_principal; t++){
                int diag = i + 9*(t-ajuste_dprincipal);
                if (campos[diag]==-jogador && diag-9>0 && campos[diag-9]==jogador){
                    campos[diag+9]=3;

                }else if(campos[diag]==-jogador && diag+9<64 && campos[diag+9]==jogador){
                    campos[diag-9]=3;
                }
            }
            
            // Calcula o tamanho da diagonal invertida
            int diag_inv = min(linha+1,8-coluna) + 8-max(linha+1,8-coluna);
            int ajuste_dinv =  min(linha+1,8-coluna) - 1;

            // Percorre a diagonal invertida
            for (int t = 0; t < diag_inv; t++){
                int diag = i + 7*(t-ajuste_dinv);
                if (campos[diag]==-jogador && diag-7>0 && campos[diag-7]==jogador){
                    campos[diag+7]=3;
                }else if(campos[diag]==-jogador && diag+7<64 && campos[diag+7]==jogador){
                    campos[diag-7]=3;
                }
            }
        }        
    }
    printf("\n");
}

void listarJogadas(int campos[64]){
    for (int i = 0; i < 64; i++){
        if (campos[i]==3){
            printf("(%d,%d) ", i/8 + 1, i%8 + 1);
        }
    }
    printf("\n");
}


// // //Calcula e retorna um vetor com todas as possibilidades de jogadas possíveis para o jogador atual
// int jogadasValidas(int jogador, int campos[64]){

// 		for(int i = 0; i < 64; i++){
// 			if(jogadasValidas(jogador, campos[i]) == 0){
// 				campos[i] = 3;
// 			}
		
// 	}
// 	return(0);
// }

void limparJogadasValidas(int campos[64]){
		for(int i = 0; i < 64; i++){
			if(campos[i] == 3){
				campos[i] = 0;
			}	
	}
}




// //Funcoes para debug
// void debugJogo(int campos[64]){
// 	for (int i = 0; i < 64; i++){
// 		printf("%d", campos[i]);
// 	}
// }

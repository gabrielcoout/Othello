#include <stdio.h>

//Declaracao das funcoes
void imprimirJogo(int campos[8][8]);
void iniciarJogo(int campos[8][8]);
int jogada(int jogador, int campos[8][8]);
void validarJogada(int jogador, int campos[8][8]);
int jogadasValidas(int jogador, int campos[8][8]);
void limparJogadasValidas(int campos[8][8]);

//funcoes de debug
void debugJogo(int campos[8][8]);

int main() {

	//declaracao de variaveis
	int campos[8][8];
	int jogador = 1;

	iniciarJogo(campos);

	jogadasValidas(jogador, campos);
	imprimirJogo(campos);
	limparJogadasValidas(campos);
	jogada(jogador, campos);
	imprimirJogo(campos);

	return 0;
}


//Mostra na tela o tabuleiro do jogo com X e O para as respectivas jogadas de cada jogador
void imprimirJogo(int campos[8][8]) {
	int i, j;
	printf("---------------------------------\n");
	
	for (i = 0; i < 8; i++) {
		printf("|");
		for (j = 0; j < 8; j++) {
			if (campos[i][j]>=0 && campos[i][j]<=2){
				switch (campos[i][j]){
					case 1:
						printf(" x ");
						break;
					case 2:
						printf(" o ");
						break;
					default:
						printf("   ");
						break;
				}
			}
			else{
				printf("error");
				return;
			}
			printf("|");
		}
		printf("\n---------------------------------\n");
	}
	return;
}

//Inicia o tabuleiro do jogo deixando somente com as pecas iniciais
void iniciarJogo(int campos[8][8]){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			campos[i][j] = 0;
		}
	}
	
	campos[3][3]=1;
        campos[4][4]=1;
        campos[3][4]=2;
        campos[4][3]=2;


	return;
}

//Preenche o vetor do jogo de forma que a jogada é gravada
int jogada(int jogador, int campos[8][8]){

	int linha;
	int coluna;

	scanf("%d %d", &linha, &coluna);

	if(jogador == 1){
		campos[linha - 1][coluna - 1] = 1;
		jogador = 2;
		return 0;
	}
	if (jogador == 2){
		campos[linha - 1][coluna - 1] = 2;
		jogador = 1;
		return 0;
	}

	return 1;
}

int validarJogada(int jogador, int campos[8][8]){
	
	int aux = -1;

	if(jogador == 0){
		for(int i = 0; i < 8; i ++){
			for(int j = 0; j < 8; j++){


			}
		}
	}


	return 1;
}


//Calcula e retorna um vetor com todas as possibilidades de jogadas possíveis para o jogador atual
void jogadasValidas(int jogador,int campos[8][8]){

	//loop para verificar quais campos sao jogadas possiveis com base no campo e o jogador da vez
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(validarJogada(jogador, campos[i][j]) == 0){
				campos[i][j] = 3;
			}
		}
	}

	return;
}

void limparJogadasValidas(int campos[8][8]){
	
	//loop que passa pelo tabuleiro todo limpando quais sao os campos ocupados
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(campos[i][j] == 3){
				campos[i][j] = 0;
			}
		}
	}

	return;
}


//Funcoes para debug
void debugJogo(int campos[8][8]){
	for (int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			printf("%d", campos[i][j]);
		}
	}
}

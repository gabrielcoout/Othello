#include <stdio.h>

//Declaracao das funcoes
void imprimirJogo(int campos[8][8]);
void iniciarJogo(int campos[8][8]);
int jogada(int jogador, int campos[8][8]);
int validarJogada(int jogador, int linha, int coluna, int campos[8][8]);
int jogadasValidas(int jogador, int campos[8][8]);
void limparJogadasValidas(int campos[8][8]);
void gameLoop();
int fimDeJogo(int campos[8][8]);

//funcoes de debug
void debugJogo(int campos[8][8]);

int main() {

	//declaracao de variaveis
	//int campos[8][8];
	//int jogador = 1;

	//iniciarJogo(campos);
	//jogadasValidas(jogador, campos);
	//imprimirJogo(campos);
	//limparJogadasValidas(campos);
	//jogada(jogador, campos);
	//imprimirJogo(campos);

	gameLoop();

	//

	return 0;
}


//Mostra na tela o tabuleiro do jogo com X e O para as respectivas jogadas de cada jogador
void imprimirJogo(int campos[8][8]) {
	int i, j;
	printf("---------------------------------\n");
	
	for (i = 0; i < 8; i++) {
		printf("|");
		for (j = 0; j < 8; j++) {

			switch (campos[i][j]){
				case 1:
					printf(" x ");
					break;
				case 2:
					printf(" o ");
					break;
				case 3:
					printf("( )");
					break;
				default:
					printf("   ");
					break;
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

int validarJogada(int jogador, int linha, int coluna, int campos[8][8]){
	// Verificar se a posição está dentro dos limites do tabuleiro
	if (linha < 0 || linha >= 8 || coluna < 0 || coluna >= 8) {
		return 1; // Jogada inválida
	}
	
	// Verificar se a posição já está ocupada
	if (campos[linha][coluna] != 0) {
		return 1; // Jogada inválida
	}
	
	// Verificar se a jogada é válida em alguma direção
	int direcoes[8][2] = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1},           {0, 1},
		{1, -1},  {1, 0},  {1, 1}
	};
	
	for (int i = 0; i < 8; i++) {
		int dx = direcoes[i][0];
		int dy = direcoes[i][1];
		
		int x = linha + dx;
		int y = coluna + dy;
		
		// Verificar se a próxima posição está dentro dos limites do tabuleiro
		if (x >= 0 && x < 8 && y >= 0 && y < 8) {
			// Verificar se a próxima posição é ocupada pelo jogador adversário
			if (campos[x][y] == (jogador == 1 ? 2 : 1)) {
				// Continuar na mesma direção até encontrar uma posição vazia ou uma posição ocupada pelo jogador atual
				while (x >= 0 && x < 8 && y >= 0 && y < 8) {
					if (campos[x][y] == jogador) {
						return 0; // Jogada válida
					}
					if (campos[x][y] == 0) {
						break; // Jogada inválida
					}
					x += dx;
					y += dy;
				}
			}
		}
	}
	
	return 1; // Jogada inválida
}

//Calcula e retorna um vetor com todas as possibilidades de jogadas possíveis para o jogador atual
int jogadasValidas(int jogador,int campos[8][8]){

	int validador = 0;

	//loop para verificar quais campos sao jogadas possiveis com base no campo e o jogador da vez
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(validarJogada(jogador, i, j, campos) == 0){
				campos[i][j] = 3;
				validador = 1;
			}
		}
	}

	if(validador != 0){
		return 1;
	}

	return 0;
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

//game loop
void gameLoop(){
	int campos[8][8];
	int jogador = 1;
	//int jogadas = 0;
	int vencedor = 0;

	while(vencedor == 0){

		//verifica se o jogo acabou
		if(jogadasValidas(jogador, campos) == 1 ){
			printf("Jogador %d nao tem jogadas validas\n", jogador);

			//troca de jogador

			if(jogador == 1){
				jogador = 2;
			}else{
				jogador = 1;
			}

			//verifica se o outro jogador tambem nao tem jogadas validas

			if(jogadasValidas(jogador, campos) == 1){
				printf("Jogo acabou\n");
				vencedor = fimDeJogo(campos);
				break;
			}

		}else{
			printf("Jogador %d tem jogadas validas\n", jogador);
			printf("Digite a linha e a coluna da jogada do jogador %d \n", jogador);
			debugJogo(campos);
			imprimirJogo(campos);
			jogada(jogador, campos);
			limparJogadasValidas(campos);
		}


		//jogadas++;
	}
}

int fimDeJogo(int campos[8][8]){
	int pecasJogador1 = 0;
	int pecasJogador2 = 0;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(campos[i][j] == 1){
				pecasJogador1++;
			}
			if(campos[i][j] == 2){
				pecasJogador2++;
			}
		}
	}

	if(pecasJogador1 > pecasJogador2){
		printf("Jogador 1 venceu\n");
		return 1;
	}
	if(pecasJogador2 > pecasJogador1){
		printf("Jogador 2 venceu\n");
		return 2;
	}
	if(pecasJogador1 == pecasJogador2){
		printf("Empate\n");
		return 3;
	}

	return 0;
}

//Funcoes para debug
void debugJogo(int campos[8][8]){
	for (int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			printf("%d", campos[i][j]);
		}
	}
}

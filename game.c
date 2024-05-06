#include <stdio.h>

// Declaração das funções
void imprimirJogo(int campos[8][8]);
void iniciarJogo(int campos[8][8]);
void jogada(int *jogador, int campos[8][8]);
int validarJogada(int jogador, int linha, int coluna, int campos[8][8]);
int jogadasValidas(int jogador, int campos[8][8]);
void limparJogadasValidas(int campos[8][8]);
void gameLoop();
int fimDeJogo(int campos[8][8]);

void debugJogo(int campos[8][8]);

// Função principal
int main() {
    gameLoop();
    return 0;
}

// Mostra o tabuleiro do jogo com X e O para as respectivas jogadas de cada jogador
void imprimirJogo(int campos[8][8]) {
    printf("---------------------------------\n");
    for (int i = 0; i < 8; i++) {
        printf("|");
        for (int j = 0; j < 8; j++) {
            switch (campos[i][j]){
                case 1:
                    printf(" X ");
                    break;
                case 2:
                    printf(" O ");
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
}

// Inicia o tabuleiro do jogo com as peças iniciais
void iniciarJogo(int campos[8][8]){
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            campos[i][j] = 0;

    campos[3][3] = 1;
    campos[4][4] = 1;
    campos[3][4] = 2;
    campos[4][3] = 2;
}

// Realiza a jogada no tabuleiro
void jogada(int *jogador, int campos[8][8]) {
    int linha, coluna;
	while (1)
	{
		printf("Digite linha e coluna para jogar: ");
		scanf("%d %d", &linha, &coluna);

		if (campos[linha - 1][coluna - 1] == 3) {
			campos[linha - 1][coluna - 1] = *jogador;
			*jogador = (*jogador == 1) ? 2 : 1; // Troca de jogador
			break;
		} else {
			printf("Jogada inválida, tente novamente.\n");
		}
	}
	
		
	}

// Verifica se a jogada é válida
int validarJogada(int jogador, int linha, int coluna, int campos[8][8]) {
    if (linha < 0 || linha >= 8 || coluna < 0 || coluna >= 8 || campos[linha][coluna] != 0)
        return 1; // Jogada inválida

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

        // Primeira verificação: deve haver uma peça adversária adjacente na direção
        if (x >= 0 && x < 8 && y >= 0 && y < 8 && campos[x][y] == (jogador == 1 ? 2 : 1)) {
            // Segunda verificação: deve haver uma peça do próprio jogador em linha
            x += dx;
            y += dy;
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (campos[x][y] == jogador) {
                    return 0; // Jogada válida
                }
                if (campos[x][y] == 0) {
                    break; // Chegou a uma casa vazia antes de fechar o "sanduíche"
                }
                x += dx;
                y += dy;
            }
        }
    }
    return 1; // Jogada inválida
}

// Calcula e marca jogadas válidas no tabuleiro
int jogadasValidas(int jogador, int campos[8][8]) {
    int validador = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (validarJogada(jogador, i, j, campos) == 0) {
                campos[i][j] = 3; // Marca como jogada válida temporária
                validador = 1;
            }
        }
    }
    return validador;
}

// Limpa as jogadas válidas temporárias do tabuleiro
void limparJogadasValidas(int campos[8][8]) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (campos[i][j] == 3){
                campos[i][j] = 0;
	    }
}

// Loop principal do jogo
void gameLoop() {
    int campos[8][8], jogador = 1;
    iniciarJogo(campos);

    while (1) {
        if (!jogadasValidas(jogador, campos)) {  //Uma vez que essa funcao eh usada como flag e como alteracao de campos
						//temos que limpar as jogadas validas depois de usar ela

		printf("Jogador %d não tem jogadas válidas.\n", jogador);
		limparJogadasValidas(campos);
		jogador = (jogador == 1) ? 2 : 1;

		if (!jogadasValidas(jogador, campos)) {
			limparJogadasValidas(campos); //talvez desnecessario, verificar
			printf("Jogo acabou.\n");
			break;
		}
	}
	limparJogadasValidas(campos);
	jogadasValidas(jogador, campos);
	imprimirJogo(campos);
        jogada(&jogador, campos);
        limparJogadasValidas(campos);
    }

    fimDeJogo(campos);
}

// Determina o resultado final do jogo
int fimDeJogo(int campos[8][8]) {
    int pecasJogador1 = 0, pecasJogador2 = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (campos[i][j] == 1)
                pecasJogador1++;
            else if (campos[i][j] == 2)
                pecasJogador2++;

    if (pecasJogador1 > pecasJogador2)
        printf("Jogador 1 venceu!\n");
    else if (pecasJogador2 > pecasJogador1)
        printf("Jogador 2 venceu!\n");
    else
        printf("Empate.\n");

    return 0;
}


//Funcoes para debug
void debugJogo(int campos[8][8]){
	printf("\n");
	for (int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			printf("%d", campos[i][j]);
		}
	}
	printf("\n");
}

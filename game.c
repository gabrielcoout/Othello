//Gabriel Coutinho Chaves 15111760
//Gabriel Gomes Tavares 15111742
#include <stdio.h>
#include <stdlib.h>

// Declaracao das funcoes
void imprimirJogo(int jogador, int campos[8][8]);
void iniciarJogo(int campos[8][8]);
void jogada(int *jogador, int campos[8][8]);
int validarJogada(int jogador, int linha, int coluna, int campos[8][8]);
int jogadasValidas(int jogador, int campos[8][8]);
void limparJogadasValidas(int campos[8][8]);
void gameLoop();
int fimDeJogo(int campos[8][8]);
void comerPecas(int jogadorAtual, int posicaoLinha, int posicaoColuna, int tabuleiro[8][8]);
void debugJogo(int campos[8][8]);

int valorTabuleiro(int tabuleiro[8][8]);
void copiarTabuleiro(int tabuleiroOriginal[8][8], int tabuleiroCopia[8][8]);
int miniMax(int tabuleiro[8][8], int profundidade, int jogador, int chamaMax);
void gameLoopBot();
int verificarFimDeJogo(int tabuleiro[8][8]);
void fimDeJogoBot(int tabuleiro[8][8]);

// Funcao principal
int main() {

    //Declaração de variaveis
    int escolha = 0;


    //Escolha do modo de jogo
    while(escolha != 3){

        printf("1 - PvP\n2 - PvE\n");
        scanf("%d", &escolha);

        switch (escolha){
        case 1:
            gameLoop();
            break;
        case 2:
            gameLoopBot();
            break;
        default:
            printf("Escolha uma opcao valida");
            break;
        }
    }
    
    return 0;
}

// Mostra o tabuleiro do jogo com X e O para as respectivas jogadas de cada jogador (e as coordenadas nas jogadas validas)
void imprimirJogo(int jogador, int campos[8][8]) {
    printf("Turno do jogador %d\n", jogador);
    printf(" -----------------------------------------------------------------\n");
    for (int i = 0; i < 8; i++) {
        printf("%d|", i+1);
        for (int j = 0; j < 8; j++) {
            switch (campos[i][j]){
                case 1:
                    printf("   X   "); break;
                case 2:
                    printf("   O   "); break;
                case 3:
                    printf("( %d %d )", i+1, j+1); break;
                default:
                    printf("       "); break;
            }
            printf("|");
        }
        printf("\n -----------------------------------------------------------------\n");
    }
    printf(" ");
    for (int i = 1; i < 9; i++){
        printf("    %d   ", i);
    }
    printf("\n");

    return;
}

// Inicia o tabuleiro do jogo com as peças iniciais
void iniciarJogo(int campos[8][8]){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            campos[i][j] = 0;
        }
    }

    campos[3][4] = 1;
    campos[4][3] = 1;
    campos[3][3] = 2;
    campos[4][4] = 2;

    return;
}

// Realiza a jogada no tabuleiro
void jogada(int *jogador, int campos[8][8]) {
    int linha, coluna;
    do{

        printf("Digite linha e coluna para jogar: ");
        scanf("%d %d", &linha, &coluna);

        if(campos[linha - 1] [coluna - 1] != 3){
            printf("Jogada inválida, tente novamente.\n");
        }

    }while(campos[linha - 1][coluna - 1] != 3);

    campos[linha - 1][coluna - 1] = *jogador;
    comerPecas(*jogador, linha - 1, coluna - 1, campos);    // Chama a funcao para comer as pecas
    *jogador = (*jogador == 1) ? 2 : 1;                     // Troca de jogador apos a jogada usando operador ternario

    return;
}

// Verifica se a jogada eh valida
// Ela retorna 0 se a jogada for valida e 1 se for invalida.
int validarJogada(int jogador, int linha, int coluna, int campos[8][8]) {
    // Verifica se as coordenadas estao fora dos limites do tabuleiro ou se a casa ja esta ocupada.
    if (linha < 0 || linha >= 8 || coluna < 0 || coluna >= 8 || campos[linha][coluna] != 0)
        return 1; // Retorna 1, indicando jogada invalida

    // Array com as possiveis direcoes de movimento no tabuleiro (diagonais, horizontais e verticais).
    int direcoes[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    // Itera sobre cada direcao para verificar a validade da jogada
    for (int i = 0; i < 8; i++) {
        int dx = direcoes[i][0];
        int dy = direcoes[i][1];
        int x = linha + dx;
        int y = coluna + dy;

        // Primeira verificacao: deve haver uma peça adversaria adjacente na direcao verificada.
        if (x >= 0 && x < 8 && y >= 0 && y < 8 && campos[x][y] == (jogador == 1 ? 2 : 1)) {
            // Continua movendo na mesma direcao para verificar se ha uma peça do proprio jogador.
            x += dx;
            y += dy;
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                // Se encontrar uma peca do proprio jogador, retorna 0 indicando que a jogada eh valida.
                if (campos[x][y] == jogador) {
                    return 0; // Jogada válida
                }
                // Se encontrar uma casa vazia ou uma casa com outra marcacao especifica, interrompe a busca nesta direcao.
                if (campos[x][y] == 0 || campos[x][y] == 3) {
                    break; // Encerra a verificacao nesta direcao, pois não esta entre duas pecas".
                }
                x += dx;
                y += dy;
            }
        }
    }
    return 1; // Se nenhuma condicao valida foi encontrada em todas as direcoes, retorna 1 indicando jogada invalida.
}


// Calcula e marca jogadas validas no tabuleiro
int jogadasValidas(int jogador, int campos[8][8]) {
    int validador = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (validarJogada(jogador, i, j, campos) == 0) {
                campos[i][j] = 3; // Marca como jogada válida temporaria
                validador = 1;
            }
        }
    }
    return validador;
}

// Limpa as jogadas validas temporarias do tabuleiro
void limparJogadasValidas(int campos[8][8]) {
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (campos[i][j] == 3){
                campos[i][j] = 0;
            }
	    }
    }

    return;
}

// Loop principal do jogo
void gameLoop() {
    int campos[8][8], jogador = 1;
    iniciarJogo(campos);

    while (jogadasValidas(jogador, campos) || jogadasValidas(3 - jogador, campos)) { //enquanto pelo menos um dos jogadores tiverem jogadas validas

        limparJogadasValidas(campos);
        
        if (!jogadasValidas(jogador, campos)) {
            printf("Jogador %d não tem jogadas válidas.\n", jogador);
            limparJogadasValidas(campos);
            jogador = (jogador == 1) ? 2 : 1;
            jogadasValidas(jogador, campos);
    	}

        imprimirJogo(jogador, campos);
        jogada(&jogador, campos);
        printf("\n");
    }

    fimDeJogo(campos);

    return;
}

// Determina o resultado final do jogo
int fimDeJogo(int campos[8][8]) {
    int pecasJogador1 = 0, pecasJogador2 = 0;
    printf("Jogo acabou.\n");
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (campos[i][j] == 1){
                pecasJogador1++;
            }
            else if (campos[i][j] == 2){
                pecasJogador2++;
            }
        }
    }
    if (pecasJogador1 > pecasJogador2){
        printf("Jogador 1 venceu!\n");
    }
    else if (pecasJogador2 > pecasJogador1){
        printf("Jogador 2 venceu!\n");
    }
    else{
        printf("Empate.\n");
    }

    return 0;
}

// Funcao para comer as pecas do adversario
// Ela atualiza o tabuleiro depois que uma peca eh jogada em uma determinada posicao.
void comerPecas(int jogadorAtual, int posicaoLinha, int posicaoColuna, int tabuleiro[8][8]) {
    // Define as oito possiveis direcoes de movimento no tabuleiro (diagonais, horizontais e verticais)
    int direcoes[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    // Determina o numero do adversario com base no jogador atual
    int adversario = jogadorAtual == 1 ? 2 : 1;

    // Itera sobre todas as direcoes possiveis para verificar se ha pecas do adversario para capturar
    for (int i = 0; i < 8; i++) {
        int incrementoLinha = direcoes[i][0];
        int incrementoColuna = direcoes[i][1];
        int linhaAtual = posicaoLinha + incrementoLinha;
        int colunaAtual = posicaoColuna + incrementoColuna;
        int contadorPecas = 0;

        // Percorre o tabuleiro na direcao especificada ate encontrar um limite, uma peca vazia ou uma peca do proprio jogador
        while (linhaAtual >= 0 && linhaAtual < 8 && colunaAtual >= 0 && colunaAtual < 8) {
            if (tabuleiro[linhaAtual][colunaAtual] == adversario) {
                contadorPecas++;
                linhaAtual += incrementoLinha;
                colunaAtual += incrementoColuna;
            } else if (tabuleiro[linhaAtual][colunaAtual] == jogadorAtual && contadorPecas > 0) {
                // Se encontrar uma peca do jogador apos uma sequencia de pecas do adversario, retrocede e converte todas as pecas do adversario
                while (contadorPecas > 0) {
                    linhaAtual -= incrementoLinha;
                    colunaAtual -= incrementoColuna;
                    tabuleiro[linhaAtual][colunaAtual] = jogadorAtual;
                    contadorPecas--;
                }
                break;
            } else {
                // Encerra a verificacao nesta direcao se encontrar uma celula vazia ou uma peca do jogador sem pecas do adversario entre elas
                break;
            }
        }
    }

    return;
}


// Funcoes para debug
void debugJogo(int campos[8][8]){
	printf("\n");
	for (int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			printf("%d ", campos[i][j]);
		}
        printf("\n");
	}
	printf("\n");

    return;
}


// Funcoes para jogada do Computador

// Calcula e devolve o valor do tabuleiro com base no jogador atual
int valorTabuleiro(int tabuleiro[8][8]){

    int valor = 0;

    // valores de cada casa em realcao a posicao no tabuleiro
    int valoresTabuleiro[8][8] = {
        20, 15, 15, 15, 15, 15, 15, 20,
        15, 10, 10, 10, 10, 10, 10, 15,
        15, 10, 12, 12, 12, 12, 10, 15,
        15, 10, 12, 12, 12, 12, 10, 15,
        15, 10, 12, 12, 12, 12, 10, 15,
        15, 10, 12, 12, 12, 12, 10, 15,
        15, 10, 10, 10, 10, 10, 10, 15,
        20, 15, 15, 15, 15, 15, 15, 20,
    };

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tabuleiro[i][j] == 2){ //maximizar quando for o bot
                valor += valoresTabuleiro[i][j];
            }
            if(tabuleiro[i][j] == 1){ //minimizar quando for o jogador
                valor -= valoresTabuleiro[i][j];
            }
        }
    }

    return valor;
}

void copiarTabuleiro(int tabuleiroOriginal[8][8], int tabuleiroCopia[8][8]){// void passar os dois //2 for
    
    //Loop para copiar os valores
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            tabuleiroCopia[i][j] = tabuleiroOriginal[i][j];
        }
    }

    return;
}

int miniMax(int tabuleiro[8][8], int profundidade, int jogador, int chamaMax){
    int valorMaximizador =  -100000;
    int valorMinimizador = 100000;
    int camposCopia[8][8];
    int pontuacao;
    int adversario = jogador == 1 ? 2 : 1;
    int flagTemJogada = 0;

    //copiarTabuleiro(tabuleiro, camposCopia);
    //limparJogadasValidas(camposCopia);

    //Ponto de parada do miniMax
    if(profundidade == 0 || verificarFimDeJogo(tabuleiro)){ //VERIFICAR
        return valorTabuleiro(tabuleiro);
    }

    jogadasValidas(jogador, tabuleiro);

    for(int i = 0; i < 8; i++){
        for(int j = 0;j < 8; j++){
            if(camposCopia[i][j] == 3){
                flagTemJogada = 1;                                  // Altera a flag para que nao caia no caso que nao tem jogadas validas
                copiarTabuleiro(tabuleiro, camposCopia);            // Copia o campo somente aqui para nao atrapalhar nas outras jogadas possiveis
                comerPecas(jogador, i, j, camposCopia);             // Faz a jogada nessa jogada valida
                pontuacao = miniMax(camposCopia, profundidade - 1, adversario, 1 - chamaMax);
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

    if (!flagTemJogada) { // Trata o caso do jogador atual nao ter jogadas validas
        pontuacao = miniMax(tabuleiro, profundidade - 1, adversario, 1 - chamaMax);
        return pontuacao;
    }

    if(chamaMax){
        return valorMaximizador;
    }else{
        return valorMinimizador;
    }

}

void gameLoopBot() {
    // Declaração de variáveis
    int escolha = -1;
    int campos[8][8], camposCopia[8][8], jogador = 1;
    int pontuacaoJogada;
    int melhorI = -1, melhorJ = -1;

    // Escolha da dificuldade do bot
    system("clear");
    printf("Escolha a dificuldade do bot: \nmuito fácil          médio          bacalhau\n     |-----------------|----------------|\n     0                 5               10+\n");

    while (escolha < 0) { // Validar para nao passar uma profundidade negativa
        scanf("%d", &escolha);
    }

    // Lógica do loop
    iniciarJogo(campos);

    while (jogadasValidas(jogador, campos) || jogadasValidas(3 - jogador, campos)) { // enquanto pelo menos um dos jogadores tiver jogadas válidas
        limparJogadasValidas(campos);

        if (!jogadasValidas(jogador, campos)) { // Verifica se o jogador tem jogadas validas e ja deixa marcada as posicoes com validas

            limparJogadasValidas(campos);

            if(jogador == 1){
                printf("O jogador nao tem jogadas validas.\n");
            }else{
                printf("O bot nao tem jogadas validas.\n");
            }

            jogador = 3 - jogador;
        }

        jogadasValidas(jogador , campos);
 
        if (jogador == 1) {
            printf("Valor do tabuleiro atualmente: %d\n", valorTabuleiro(campos));
            imprimirJogo(jogador, campos);
            jogada(&jogador, campos);
            limparJogadasValidas(campos);
        } else {
            int melhorJogada = -999999;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (campos[i][j] == 3) { // Verifica jogada válida
                        copiarTabuleiro(campos, camposCopia);
                        comerPecas(jogador, i, j, camposCopia);
                        pontuacaoJogada = miniMax(camposCopia, escolha, jogador, 1);
                        if (pontuacaoJogada > melhorJogada) {
                            melhorJogada = pontuacaoJogada;
                            melhorI = i;
                            melhorJ = j;
                        }
                    }
                }
            }

            if (melhorI != -1 && melhorJ != -1) { // Verifica se encontrou uma jogada
                campos[melhorI][melhorJ] = jogador;
                comerPecas(jogador, melhorI, melhorJ, campos); // Chama a função para comer as peças
                jogador = (jogador == 1) ? 2 : 1;
                limparJogadasValidas(campos);

                printf("O Bot jogou %d,%d\n", melhorI + 1, melhorJ + 1);
                printf("Vantagem do Bot na profundidade %d: %d\n", escolha, melhorJogada)
            }
        }
        
    }

    fimDeJogoBot(campos);
}

int verificarFimDeJogo(int tabuleiro[8][8]){

    limparJogadasValidas(tabuleiro);

    if(!jogadasValidas(1, tabuleiro) && !jogadasValidas(2, tabuleiro)){
        return 1; // Nao tem jogadas validas
    }

    limparJogadasValidas(tabuleiro);

    return 0; // Tem jogadas validas
}

void fimDeJogoBot(int tabuleiro[8][8]){

    int pecasJogador1 = 0, pecasBot = 0;
    printf("Jogo acabou.\n");
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (tabuleiro[i][j] == 1){
                pecasJogador1++;
            }
            else if (tabuleiro[i][j] == 2){
                pecasBot++;
            }
        }
    }
    if (pecasJogador1 > pecasBot){
        printf("Jogador venceu! por %d\n", pecasJogador1 - pecasBot);
    }
    else if (pecasBot > pecasJogador1){
        printf("O Bot ganhou! por %d\n", pecasBot - pecasJogador1);
    }
    else{
        printf("Empate.\n");
    }

    return;   

}
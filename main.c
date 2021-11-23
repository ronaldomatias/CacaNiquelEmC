#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>

typedef struct Jogador{
    char nome[30];
    unsigned short dinheiro;
    unsigned short fichas;
    unsigned short qtde_vitorias;
    float reembolso;
    float premio;
}Jogador;

typedef struct No{
    unsigned short vetor[3];
    No *proximoNo;
}No;

typedef struct Lista{
    No *inicioDaLista, *fim;
    unsigned short tam;
}Lista;

void iniciarLista(Lista *lista){

    lista->inicioDaLista = NULL;
    lista->tam =0;
}

void inserirNoFim(Lista *lista, unsigned short *vetor) {

    No *novoNo = (No*)malloc(sizeof(No));

    unsigned short i =0;
    while(i < 3){   //adicionar valores aleatorios na lista
        novoNo->vetor[i] = vetor[i];
        i++;
    }
    novoNo->proximoNo = NULL;

    if(lista->inicioDaLista == NULL) {
        lista->inicioDaLista = novoNo;
        lista->fim = novoNo;
    } else {
        lista->fim->proximoNo = novoNo;
        lista->fim = novoNo;
    }
    lista->tam++;
}

void imprimirHistoricoDeResultados(Lista *lista, Jogador *jogador){

    No *no = lista->inicioDaLista;

    printf("\n%s, seu historico de jogadas foi este: \n", jogador->nome);

    unsigned short jogada=1;
    while(no != NULL){

        printf("\n");
        printf("Jogada %d: ", jogada);
        for (int i=0; i <3; i++){
            printf("%2d", no->vetor[i]);
        }
        no = no->proximoNo;
        jogada++;
    }
}

void transformarDinheiroEmFichas(Jogador *jogador){

    jogador->fichas = jogador->dinheiro;
    jogador->dinheiro = 0;
}

unsigned short minhaFuncaoAtoi(char *vetor) {

    unsigned short numero =0;

    unsigned short i =0;
    while(vetor[i] != '\0'){

        numero = numero*10 + vetor[i] -'0';
        i++;
    }

    return numero;
}

bool ehNumero(char valorInserido){

    if(valorInserido >47 && valorInserido<58){
        return true;
    }else{
        return false;
    }
}

unsigned short solicitarNumero(){ // filtra input com usuario
                                  // aceita 4 digitos numericos
    unsigned short numero=0;
    char digitado[4];
    char input;

    unsigned short i=0;
    do{
        input=getch();
        if (ehNumero(input) && i<4){

            digitado[i] = input;
            i++;
            printf("%c", input);
        }
        else if(input ==8 && i !=0){
            digitado[i]='\0';
            i--;
            printf("\b \b");
        }
    }while(input!=13);

    digitado[i]='\0';
    numero = minhaFuncaoAtoi(digitado); // converte vetor de char em um short

    return numero;
}

void cadastrarJogador(Jogador *jogador){

    jogador->premio =0;
    jogador->qtde_vitorias =0;

    printf("Qual seu nome? \n");
    scanf("%s", &jogador->nome);
    system("cls");

    printf("CUSTO DO JOGO: 1 REAL POR CADA FICHA! \n \nDESEJA ADQUIRIR QUANTAS FICHAS? \n");
    jogador->dinheiro = solicitarNumero();  // tabela ascii
    system("cls");

    transformarDinheiroEmFichas(jogador);
}

void imprimirCombinacaoGerada(unsigned short *vetor){

    for (int i=0; i<3; i++){
        printf("%10d ", *(vetor++));
    }
    printf("\n");
}

void verificarCombinacaoGerada(unsigned short *vetor, Jogador *jogador){

    if (vetor[0]==vetor[1] & vetor[1]==vetor[2]){

        printf("\n          Resultado:  Ganhou! \n\n\n\n");
        jogador->qtde_vitorias += 1;
        jogador->premio += 60;

    }else{
        printf("\n      Resultado: Nao foi dessa vez. \n\n\n\n");
    }
}

void gerarValoresAleatorios(Lista *lista, Jogador *jogador){

    srand(time(0));

    unsigned short vetorDeValoresAleatorios[4];
    vetorDeValoresAleatorios[0]= rand() %3;
    vetorDeValoresAleatorios[1]= rand() %3;
    vetorDeValoresAleatorios[2]= rand() %3;
    vetorDeValoresAleatorios[3]= '\0';

    inserirNoFim(lista, vetorDeValoresAleatorios);

    imprimirCombinacaoGerada(vetorDeValoresAleatorios);
    verificarCombinacaoGerada(vetorDeValoresAleatorios, jogador);

    jogador->fichas--;
}

void gerarReembolso(Jogador *jogador){

    jogador->reembolso = jogador->fichas;
    jogador->fichas = 0;
}

void imprimirStatusDoJogador(Jogador *jogador){

    printf("%s ganhou %d vezes e recebeu uma premiacao total de %.2f reais. \n", jogador->nome, jogador->qtde_vitorias, jogador->premio);
    printf("Seu reembolso foi de %.2f reais; \n\n", jogador->reembolso);
}


int main(){

    Lista lista;
    iniciarLista(&lista);

    Jogador jogador;
    cadastrarJogador(&jogador);

    unsigned short continuar = 1;
    while(jogador.fichas>0 & continuar==1){

        printf("VOCE PODE SAIR E SERA REEMBOLSADO DE ACORDO COM A QUANTIDADE DE FICHAS QUE POSSUI. \n\n");
        printf("           VOCE POSSUI: %i FICHAS. \n\n", jogador.fichas);
        printf("PARA TENTAR A SORTE, DIGITE: (1). PARA SAIR E RECEBER O REEMBOLSO, DIGITE QUALQUER OUTRO VALOR. \n");
        continuar = solicitarNumero();
        system("cls");

        if (continuar == 1){
            gerarValoresAleatorios(&lista, &jogador);
        }
    }

    gerarReembolso(&jogador);

    imprimirStatusDoJogador(&jogador);
    imprimirHistoricoDeResultados(&lista, &jogador);

    return 0;
}

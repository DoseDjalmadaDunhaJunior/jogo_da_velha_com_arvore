//
// Created by djalma on 28/01/2020.
//

#ifndef ARVOREDEDESISAO_ARVORE_H
#define ARVOREDEDESISAO_ARVORE_H
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

class Arvore {
public:
    Arvore(){
        zera();
        existe();
    }

    // a logica do jogo esta aqui
    void jogo(){
        int vez = aleatorio(1,2);
        if(vez == 2){
            cout<<"Você começa"<<endl;
        }
        else{
            cout<<"Eu começo"<<endl;
        }
        int a = 0, erro;
        char po;
        while((sobram > 0) && !ganho && !perdido && (a == 0)){
            erro = -7;
            //vez do jogador
            opcoes();
            if(vez%2 == 0){
                cout<<"Sua vez"<<endl;
                if(erro != 0){
                    while(erro != 0){
                        cout<<"Escolha uma posição"<<endl;
                        cin>>po;
                        erro = popula(po,2);
                    }
                }
                salva(po,2, false);
            }
            //vez do computador
            else{
                cout<<"Minha vez"<<endl;
                if(erro != 0){
                    while(erro != 0){
                        int ver = aleatorio(65,73);
                        po = intToChar(ver);
                        erro = popula(po,1);
                        //printf("==> %i  <==\n", erro);
                    }
                }
                salva(po,1, false);
            }
            cout << "===========================" << endl;
            a = confereJogo();
            vez++;
        }
        if(a == -1){
            cout<<"Parabens você ganhou"<<endl;
            if((vez-1)%2 == 0){
                salva(po,2, true);
            }
            else{
                salva(po,1, true);
            }
        }
        else if(a == 1){
            cout<<"Que pena, vocế perdeu"<<endl;
        }
        else if(a == 0){
            cout<<"Deu velha"<<endl;
        }
        opcoes();
    }


private:

    // as funções boleano abaixo serão em relação a maquina e não ao jogador
    bool velha = false;
    bool perdido = false;
    bool ganho = false;

    //lugares ainda disponiveis para jogar
    int sobram = 9;

    char caminho[500];

    /* a função aleatorio faz exatamente o que diz no nome, porem a faixa de valores possiveis começa num valor
     * estipulado e vai até onde pode ser mais viavel para a função*/
    int aleatorio(int menor ,int maior){
        srand(time(NULL));; //para gerar números aleatórios reais.
        int var = rand()%(maior-menor+1) + menor;
        return var;
    }

    //uma introdução rapida para o jogador entender como jogar, só é mostrado a 1ª vez que for jogar
    void introducao(){
        cout<<"=== Vamos jogar ==="<<endl;
        cout<<"Para escolher uma posição basta pressionar a letra correspondente\n"
              "ATENÇÃO: cada vez que você jogar mais dificil ficará"<<endl;
    }

    // tabuleiro é basicamente cada espaco do jogo da velha
    struct tabuleiro{
        char conteudo = ' ';
        char po = ' ';
    };

    typedef struct tabuleiro tabuleiro;

    tabuleiro tab[3][3];

    /* ao rederizar o tabuleiro ele tem que ter uma logica para poder ser impresso,
     * essa é a logica*/
    void opcoes(){
        char ver1,ver2;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ver1 = tab[i][j].po;
                ver2 = tab[i][j].conteudo;
                if(tab[i][j].conteudo == ' '){
                    cout<<"| "<<tab[i][j].po<<" |";
                }
                else{
                    cout<<"| "<<tab[i][j].conteudo<<" |";
                }
            }
            puts("");
        }
    }

    // ao iniciar o jogo essa é a configuração do mapa, as letras serão para o jogador se identificar
    void zera(){
        tab[0][0].conteudo = ' ';
        tab[0][0].po = 'A';
        tab[0][1].conteudo = ' ';
        tab[0][1].po = 'B';
        tab[0][2].conteudo = ' ';
        tab[0][2].po = 'C';

        tab[1][0].conteudo = ' ';
        tab[1][0].po = 'D';
        tab[1][1].conteudo = ' ';
        tab[1][1].po = 'E';
        tab[1][2].conteudo = ' ';
        tab[1][2].po = 'F';

        tab[2][0].conteudo = ' ';
        tab[2][0].po = 'G';
        tab[2][1].conteudo = ' ';
        tab[2][1].po = 'H';
        tab[2][2].conteudo = ' ';
        tab[2][2].po = 'I';

        zeraVet(caminho,500);
    }

    // altera o nome da pasta que faz o computador perder para minusculo, para identificar as perdas
    void alteraTrecho(char* vet1, char* vet2) {
        int i = 0, j = 0, c = 0;
        for (i = 0; vet1[i] != 0; i++) {

        }
        strcat(vet2, vet1);
        for (j; j < i; j++) {
            if (j >= (i - 5)) {
                if (c == 0) {
                    vet2[j] = vet1[j] + ('a' - 'A');
                    c++;
                } else if (c == 1) {
                    vet2[j] = vet1[j];
                    c++;
                } else {
                    vet2[j] = 0;
                    vet1[j] = 0;
                }
            }
        }
    }

    //salva é para salvar o aprendizado do sistema
    void salva(char po, int jogador, bool final) {
        char po2 = po;
        if (po >= 'a' && po <= 'z') {
            po = po - ('a' - 'A');
        }
        char nome[5];
        char copia[500];
        char copia2[500];
        zeraVet(nome, 5);
        zeraVet(copia, 500);
        zeraVet(copia2, 500);
        nome[0] = po;
        nome[1] = intToPchar(jogador);
        strcat(copia, "cd ");
        strcat(copia, caminho);
        strcat(copia, "/");
        strcat(copia, nome);
         // esse 1º if grava de uma forma diferente caso o caminho ja tenha feito o computador perder
        if(final){
            char muda[500]; // inicio
            char novo[500]; // final
            zeraVet(muda,500);
            zeraVet(novo,500);
            alteraTrecho(caminho,muda);
            strcat(novo,"mv ");
            strcat(novo, caminho);
            strcat(novo, " ");
            strcat(novo,muda);
            system(novo);
        }
        // esse 2º if só grava caminhos que até então não fizeram perder
        else if ((system(copia)) != 0) {
            strcat(copia2, "mkdir ");
            strcat(copia2, caminho);
            strcat(copia2, "/");
            strcat(copia2, nome);
            system(copia2);
            strcat(caminho, "/");
            strcat(caminho, nome);
        }
    }

    //uma garantia, para caso não exista um BANCO de dados ele cria um vazio, e caso exista não faz nada
    void existe(){
        if((system("cd BANCO")) != 0){
            system("mkdir BANCO");
            introducao();
        }
        strcat(caminho,"BANCO");
    }

    /* a função abaixo confere a cada jogada se alguem ganhou, retornando -1 se o computador perder
     1 se o computador ganhar e se não acontecer nada retorna 0*/
    int confereJogo(){
        //caiu aqui quer dizer que perdeu, tambem referente ao computador
        if((tab[0][0].conteudo == 'X' && tab[0][1].conteudo == 'X' && tab[0][2].conteudo == 'X') ||
           (tab[1][0].conteudo == 'X' && tab[1][1].conteudo == 'X' && tab[1][2].conteudo == 'X') ||
           (tab[2][0].conteudo == 'X' && tab[2][1].conteudo == 'X' && tab[2][2].conteudo == 'X') ||
           (tab[0][0].conteudo == 'X' && tab[1][0].conteudo == 'X' && tab[2][0].conteudo == 'X') ||
           (tab[0][1].conteudo == 'X' && tab[1][1].conteudo == 'X' && tab[2][1].conteudo == 'X') ||
           (tab[0][2].conteudo == 'X' && tab[1][2].conteudo == 'X' && tab[2][2].conteudo == 'X') ||
           (tab[0][0].conteudo == 'X' && tab[1][1].conteudo == 'X' && tab[2][2].conteudo == 'X') ||
           (tab[0][2].conteudo == 'X' && tab[1][1].conteudo == 'X' && tab[2][0].conteudo == 'X')){
            return -1;
        }
        //entrou aqui quer dizer que ganhou, tambem referente quanto ao computador
        else if((tab[0][0].conteudo == 'O' && tab[0][1].conteudo == 'O' && tab[0][2].conteudo == 'O') ||
                (tab[1][0].conteudo == 'O' && tab[1][1].conteudo == 'O' && tab[1][2].conteudo == 'O') ||
                (tab[2][0].conteudo == 'O' && tab[2][1].conteudo == 'O' && tab[2][2].conteudo == 'O') ||
                (tab[0][0].conteudo == 'O' && tab[1][0].conteudo == 'O' && tab[2][0].conteudo == 'O') ||
                (tab[0][1].conteudo == 'O' && tab[1][1].conteudo == 'O' && tab[2][1].conteudo == 'O') ||
                (tab[0][2].conteudo == 'O' && tab[1][2].conteudo == 'O' && tab[2][2].conteudo == 'O') ||
                (tab[0][0].conteudo == 'O' && tab[1][1].conteudo == 'O' && tab[2][2].conteudo == 'O') ||
                (tab[0][2].conteudo == 'O' && tab[1][1].conteudo == 'O' && tab[2][0].conteudo == 'O')){
            return 1;
        }

        return 0;
    }

    //essa função irá checar no BANCO se a posição que está tentando ser preenchida não leva a uma derrota
    bool confereBANCO() {
        int i = 0, j = 0, c = 0;
        cout<<caminho<<endl;
        char ver;
        for (i = 0; caminho[i] != 0; i++) {
                ver = caminho[i];
        }
        for (j; j < i; j++) {
            ver = caminho[j];
            if (j >= (i - 2)) {
                if (caminho[j] >= 'a' && caminho[j] <= 'z') {
                    return true;
                }
            }
        }
        return false;
    }

    /*
     * a função abaixo popula a matriz com as jogadas feitas e retorna um valor que quer dizer algo:
     * -1 = computador tentou jogar em uma posição ja ocupada
     * -2 = jogador tentou jogar em uma posição ja ocupada
     * 1 = computador jogou uma letra invalida
     * 2 = jogador jogou uma letra invalida
     * 0 = ok
     * 5 = de acordo com o BANCO essa jogada fará perder
     */
    int popula(char po, int jogador) {
        if (po >= 'a' && po <= 'z') {
            po = po - ('a' - 'A');
        }

        bool ok = true;
        int i = 0, j = 0;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (ok) {
                    if (tab[i][j].po == po) {
                        // jogador 1 é o computador e o 2 é o jogador mesmo
                        if ((tab[i][j].conteudo != ' ') && (jogador == 1)) {
                            return -1;
                        } else if ((tab[i][j].conteudo != ' ') && (jogador == 2)) {
                            cout<<tab[i][j].conteudo<<endl;
                            cout<<tab[i][j].po<<endl;
                            cerr << "Posição ja ocupada" << endl;
                            return -2;
                        } else {
                            if(jogador == 1){
                                if(confereBANCO()){
                                    return 5;
                                }
                                else {
                                    tab[i][j].conteudo = 'O';
                                }
                            }
                            else{
                                tab[i][j].conteudo = 'X';

                            }
                            return 0;
                        }
                    }
                }
            }
        }
        if (jogador == 1) {
            return 1;
        }
        cout<<tab[i][j].conteudo<<endl;
        cout<<tab[i][j].po<<endl;
        cerr << "A posição inserida não existe" << endl;
        return 2;
    }

    //converte int para char
    char intToChar(int num){
        return num;
    }

    //converte int para char valores pequenos
    char intToPchar(int num){
        return (num + '0');
    }

    void zeraVet(char* vet, int tam){
        for (int i = 0; i < tam; i++) {
            vet[i] = 0;
        }
    }


};


#endif //ARVOREDEDESISAO_ARVORE_H

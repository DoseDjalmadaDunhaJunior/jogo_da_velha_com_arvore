//
// Created by djalma on 28/01/2020.
//

#ifndef ARVOREDEDESISAO_ARVORE_H
#define ARVOREDEDESISAO_ARVORE_H
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Arvore {
public:
    Arvore(){
        zera();
        FILE *arq;
        char txt[10];
        existe();
        arq = fopen("velha", "r");
        //fprintf(arq, "%s", "oi");
        fscanf(arq,"%s", txt);
        //cout<<"salvou"<<endl;
        cout<<txt<<endl;
        fclose(arq);
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
            }
            //vez do computador
            else{
                cout<<"Minha vez"<<endl;
                if(erro != 0){
                    while(erro != 0){
                        int ver = aleatorio(65,73);
                        po = intToChar(ver);
                        erro = popula(po,1);
                    }
                }

            }
            cout << "===========================" << endl;
            a = confereJogo();
            vez++;
        }
        if(a == -1){
            cout<<"Parabens você ganhou"<<endl;
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
        opcoes();
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
    }

    //salva é para salvar o aprendizado do sistema
    void salva() {
        FILE *arq;
        arq = fopen("velha", "w");
        fprintf(arq, "%s", "oi");
        cout<<"salvou"<<endl;
        fclose(arq);
    }

    //uma garantia, para caso não exista um banco de dados ele cria um vazio, e caso exista não faz nada
    void existe(){
        FILE* arq;
        arq = fopen("velha", "r");
        if(!arq) {
            FILE* temp;
            temp = fopen("velha", "w");
            fprintf(temp, " ");
            fclose(temp);
            introducao();
        }
        else {
            fclose(arq);
        }
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

    /*
     * a função abaixo popula a matriz com as jogadas feitas e retorna um valor que quer dizer algo:
     * -1 = computador tentou jogar em uma posição ja ocupada
     * -2 = jogador tentou jogar em uma posição ja ocupada
     * 1 = computador jogou uma letra invalida
     * 2 = jogador jogou uma letra invalida
     * 0 = ok
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
                                tab[i][j].conteudo = 'O';
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

};


#endif //ARVOREDEDESISAO_ARVORE_H

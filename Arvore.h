//
// Created by djalma on 28/01/2020.
//

#ifndef ARVOREDEDESISAO_ARVORE_H
#define ARVOREDEDESISAO_ARVORE_H
#include <iostream>
using namespace std;

class Arvore {
public:
    Arvore(){
        zera();
        FILE *arq;
        arq = fopen("velha", "r");
        fprintf(arq, "%s", "oi");
        cout<<"salvou"<<endl;
        fclose(arq);
    }


private:

    struct tabuleiro{
        char conteudo = ' ';
        char po = ' ';
    };

    typedef struct tabuleiro tabuleiro;

    void opcoes(){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(tab[i][j].conteudo == ' '){
                    cout<<' '<<tab[i][j].po<<' ';
                }
                else{
                    cout<<' '<<tab[i][j].conteudo<<' ';
                }
            }
            puts("");
        }
    }

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

    void salva() {
        FILE *arq;
        arq = fopen("velha", "w");
        fprintf(arq, "%s", "oi");
        cout<<"salvou"<<endl;
        fclose(arq);
    }

    tabuleiro tab[3][3];

    int nao[500];

    int sim[500];
};


#endif //ARVOREDEDESISAO_ARVORE_H

#ifndef AVL_HPP_INCLUDED
#define AVL_HPP_INCLUDED
#include <iostream>
#include <string.h>
#include <cstring>
#include <new>
#include <stdlib.h>
#include <cstdio>
using namespace std;

typedef string TC;

class vet_string{

    public :

        TC *verb;
        int tam;
        FILE *arq;
        TC saida;

        vet_string(){

            this->tam=0;
            this->verb = NULL;

        }

        vet_string(TC _saida){

            this->tam=0;
            this->verb = NULL;
            this->saida = _saida;

        }

        void push(string _add){

            TC* verb_aux = new TC[tam+1];
            for (int i = 0; i < tam; i++)
            {
                verb_aux[i]=this->verb[i];
            }
            this->verb = new TC[tam+1];
            for (int i = 0; i < tam; i++)
            {
                this->verb[i]=verb_aux[i];
            }
            //this->verb=verb_aux;
            this->verb[tam] = _add;
            this->tam++;
            delete verb_aux;

        }

        void print(string chave,string tipo){


            this->arq = fopen(this->saida.c_str(), "a");

            fprintf(this->arq,"%s (%s)\n",chave.c_str(),tipo.c_str());
        
            for(int i=0; i<this->tam;i++){
                fprintf(this->arq,"%d. %s\n",i+1,this->verb[i].c_str());
            }

            fclose(this->arq);

        }

        int length(){

            return this->tam;

        }

        void clear(){

            this->tam=0;
            this->verb = NULL;

        }

        TC get(int _i){

            if(this->verb!=NULL){
                return this->verb[_i];
            } 
            else{
                return "";
            }

        }

        bool empty(){

            if(this->verb==NULL) {
                return true;
            }
            else{
                return false;
            }

        }

};

class TV
{

    public:
        vet_string *verb;
        TV(){

            this->verb = new vet_string();
        }
        TV(TC saida){

            this->verb = new vet_string(saida);
        }
        TV(TC init,TC saida){

            this->verb = new vet_string(saida);
            this->verb->push(init);
        }

};

class Noh { 

    public:

        TC chave; 
        TV *valor; 
        TC tipo;
        Noh *esq, *dir, *pai; 
        int h; 
    
        Noh(){

            this->valor = new TV();

        };

        Noh(string _tipo){

            this->valor = new TV();
            this->tipo=_tipo;
        };

        void print(){

            this->valor->verb->print(this->chave,this->tipo);

        };

};

class DicAVL { 

    public:
        Noh *raiz; 
        int qtd;
        DicAVL(){

            this->qtd =0;
            this->raiz=new Noh();

        };

    
};

void inicializar (DicAVL &D){
    D.raiz = NULL;
}
int get_altura(Noh *n){
    if (n==NULL)
        return 0;
    else
        return n->h;
}
int fatorBalanceamento(Noh *n){
    return abs(get_altura(n->esq) - get_altura(n->dir));
}
int maior(int a, int b){
    if(a > b) return a;
    else return b;
}

void RotacaoLL(DicAVL &D){

    Noh *raiz = D.raiz;
    Noh *no = new(std::nothrow) Noh();
    no = raiz->esq;
    raiz->esq = no->dir;
    if (no->dir!=NULL)
        no->dir->pai = raiz;
    if (raiz->pai!=NULL){
        if (no->esq!=NULL){
            if(raiz->pai->dir==raiz)
                raiz->pai->dir = no;//6
            else
                raiz->pai->esq = no;//CASO 2
        }
        else
            raiz->pai->dir = no;//caso 1
    }
    no->dir = raiz;
    no->pai = raiz->pai;
    raiz->pai = no;
    raiz->h = maior(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    no->h = maior(get_altura(no->esq), raiz->h) + 1;
    if(D.raiz->chave == raiz->chave){
        D.raiz=no;
    }
    raiz = no;
}
void RotacaoRR(DicAVL &D){
    //cout << "ROTAÇÃO RR NO " << D.raiz->chave << endl;
    Noh *raiz = D.raiz;
    Noh *no = new(std::nothrow) Noh();
    no = raiz->dir;
    raiz->dir = no->esq;
    if (no->esq!=NULL)
        no->esq->pai = raiz;
    no->esq = raiz;
    if (raiz->pai!=NULL){
        if (no->dir!=NULL){
            if (raiz->pai->esq==raiz)
                raiz->pai->esq=no;//5
            else
                raiz->pai->dir = no;//4
        }
        else
            raiz->pai->esq = no;//3
    }
    no->pai=raiz->pai;
    raiz->pai = no;
    raiz->h = maior(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    no->h = maior(get_altura(no->dir), get_altura(raiz)) + 1;
    if(strcmp(D.raiz->chave.c_str(),raiz->chave.c_str())==0){
        D.raiz=no;
    }
    raiz = no;
}
void RotacaoLR(DicAVL &D){
    DicAVL di = D;
    di.raiz = D.raiz->esq;
    RotacaoRR(di);
    RotacaoLL(D);
}
void RotacaoRL(DicAVL &D){
    DicAVL di = D;
    di.raiz = D.raiz->dir;
    RotacaoLL(di);
    RotacaoRR(D);
}
int balancear(DicAVL &D,TC c){
    if(D.raiz != NULL){
        if (strcmp(D.raiz->chave.c_str(),c.c_str())==0)
            return 1;
        int res;
        DicAVL di = D;
        if (strcmp(c.c_str(),D.raiz->chave.c_str())==-1){
            di.raiz = D.raiz->esq;
            if ((res=balancear(di, c))==1) {
                if(fatorBalanceamento(D.raiz)>=2){
                    if (strcmp(c.c_str(),D.raiz->esq->chave.c_str())==-1){
                        RotacaoLL(D);
                    }
                    else
                        RotacaoLR(D);
                }
            }
        }else {
            di.raiz = D.raiz->dir;
            if ((res=balancear(di, c))==1) {
                if(fatorBalanceamento(D.raiz)>=2){
                    if (strcmp(c.c_str(),D.raiz->dir->chave.c_str())==1){
                        RotacaoRR(D);
                    }
                    else
                        RotacaoRL(D);
                }
            }
        }
        D.raiz->h = maior(get_altura(D.raiz->esq), get_altura(D.raiz->dir)) + 1;
        return res;
    }
    else{
        return 1;
    }
}

Noh* inserir(DicAVL &D, TC c, TC _tipo, TV* v){
    D.qtd++;
    Noh *n = new(std::nothrow) Noh();
    if (n == NULL){
        cout << "Erro de alocacao!" << endl;
        return n;
    }
    n->chave = c;
    n->valor = v;
    n->h = 1;
    n->tipo = _tipo;
    n->esq = n->dir = NULL;
    if (D.raiz == NULL){
        D.raiz = n;
        n->pai = NULL;
        return n;
    }
    Noh *p = D.raiz;
    for (;;){
        if (strcmp(c.c_str(),p->chave.c_str())==-1){
            if (p->esq == NULL){
                p->esq = n;
                n->pai = p;
                break;
            }else
                p = p->esq;
        }
        if (strcmp(c.c_str(),p->chave.c_str())==1){
            if (p->dir == NULL){
                p->dir = n;
                n->pai = p;
                break;
            }
            else
                p = p->dir;
        }
        if (strcmp(c.c_str(),p->chave.c_str())==0){
            if(v->verb->verb!=NULL){
                p->valor->verb->push(v->verb->get(0));
            }
            D.qtd--;
            break;
        }
    }
    balancear(D,n->chave);
    return n;
}
Noh* procurar (DicAVL &D, TC c){
    if (D.raiz == NULL){
        return D.raiz;
    }
    Noh *p = D.raiz;
    while (p != NULL){
        if(strcmp(c.c_str(),p->chave.c_str())==0)
            return p;
        else if (strcmp(c.c_str(),p->chave.c_str())==1){
            p=p->dir;
        }
        else{
            p=p->esq;
        }
    }
    return NULL;
}
Noh* procuraMenor(Noh *p){
    Noh *n1 = p;
    Noh *n2 = p->esq;
    while (n2!=NULL){
        n1=n2;
        n2=n2->esq;
    }
    return n1;
}

int remove_AVL2(DicAVL &D,TC c){
    if (D.raiz==NULL){
        return 1;
    }
    int res;
    DicAVL di = D;
    if (strcmp(c.c_str(),D.raiz->chave.c_str())==-1){
        di.raiz=D.raiz->esq;
        if ((res=remove_AVL2(di, c))==1) {
            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->dir->esq)<=get_altura(D.raiz->dir->dir)){
                    RotacaoRR(D);
                }
                else
                    RotacaoRL(D);
            }
        }
    }else if (strcmp(c.c_str(),D.raiz->chave.c_str())==1){
        di.raiz=D.raiz->dir;
        if ((res=remove_AVL2(di, c))==1) {
            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->esq->dir) <= get_altura(D.raiz->esq->esq))
                    RotacaoLL(D);
                else
                    RotacaoLR(D);
            }
        }
    }else if (strcmp(c.c_str(),D.raiz->chave.c_str())==0){
        if ((D.raiz->esq==NULL) || (D.raiz->dir==NULL)){
            Noh *old = D.raiz;
            if (D.raiz->esq!=NULL){
                if (D.raiz->pai!=NULL){
                    if (D.raiz->pai->esq==D.raiz)
                        D.raiz->pai->esq = D.raiz->esq;
                    else
                        D.raiz->pai->dir = D.raiz->esq;
                }
                D.raiz->esq->pai = D.raiz->pai;
                D.raiz=D.raiz->esq;
            }
            else{
                if (D.raiz->pai!=NULL){
                    if (D.raiz->pai->esq==D.raiz){
                        D.raiz->pai->esq = D.raiz->dir;
                    }
                    else{
                        D.raiz->pai->dir = D.raiz->dir;
                    }
                }
                if (D.raiz->dir!=NULL){
                    D.raiz->dir->pai = D.raiz->pai;
                }
                D.raiz=D.raiz->dir;
            }
            delete old;
            //old=NULL;
        }else{//2 filhos
            Noh *temp = procuraMenor(D.raiz->dir);
            //D.raiz->chave = temp->chave;
            //D.raiz->valor = temp->valor;
            D.raiz->esq->pai = temp;
            if (temp->pai != D.raiz){
                if (temp->dir!=NULL)
                    temp->dir->pai = temp->pai;
                temp->pai->esq = temp->dir;
                D.raiz->dir->pai = temp;
                temp->dir=D.raiz->dir;
            }
            if (D.raiz->pai!=NULL){
                if (D.raiz->pai->esq==D.raiz)
                    D.raiz->pai->esq = temp;
                else
                    D.raiz->pai->dir = temp;
            }
            //temp->dir->pai = temp->pai;
            temp->pai = D.raiz->pai;
            temp->esq = D.raiz->esq;
            D.raiz = temp;
            di.raiz=D.raiz->dir;
            remove_AVL2(di,D.raiz->chave);
            D.raiz->h = maior(get_altura(D.raiz->esq), get_altura(D.raiz->dir)) + 1;

            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->esq->dir) <= get_altura(D.raiz->esq->esq))
                    RotacaoLL(D);
                else
                    RotacaoLR(D);
            }
        }
        return 1;
    }
    D.raiz->h = maior(get_altura(D.raiz->esq), get_altura(D.raiz->dir)) + 1;
    return res;
}

int remove_AVL(DicAVL &D,TC c){
    if (D.raiz==NULL){
        return 0;
    }
    int res;
    DicAVL di = D;
    if (strcmp(c.c_str(),D.raiz->chave.c_str())==-1){
        di.raiz=D.raiz->esq;
        if ((res=remove_AVL(di, c))==1) {
            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->dir->esq)<=get_altura(D.raiz->dir->dir)){
                    RotacaoRR(D);
                }
                else
                    RotacaoRL(D);
            }
        }
    }else if (strcmp(c.c_str(),D.raiz->chave.c_str())==1) {
        di.raiz=D.raiz->dir;
        if ((res=remove_AVL(di, c))==1) {
            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->esq->dir) <= get_altura(D.raiz->esq->esq))
                    RotacaoLL(D);
                else
                    RotacaoLR(D);
            }
        }
    }else if (strcmp(c.c_str(),D.raiz->chave.c_str())==0){
        if ((D.raiz->esq==NULL) || (D.raiz->dir==NULL)){
            Noh *old = D.raiz;
            if (D.raiz->esq!=NULL){
                if (D.raiz->pai!=NULL){
                    if (D.raiz->pai->esq==D.raiz)
                        D.raiz->pai->esq = D.raiz->esq;
                    else
                        D.raiz->pai->dir = D.raiz->esq;
                }
                D.raiz->esq->pai = D.raiz->pai;
                D.raiz=D.raiz->esq;
            }
            else{
                if (D.raiz->pai!=NULL){
                    if (D.raiz->pai->esq==D.raiz){
                        D.raiz->pai->esq = D.raiz->dir;
                    }
                    else{
                        D.raiz->pai->dir = D.raiz->dir;
                    }
                }
                if (D.raiz->dir!=NULL){
                    D.raiz->dir->pai = D.raiz->pai;
                }
                D.raiz=D.raiz->dir;
            }
            delete old;
            //old=NULL;
        }else{//2 filhos
            Noh *temp = procuraMenor(D.raiz->dir);
            //D.raiz->chave = temp->chave;
            //D.raiz->valor = temp->valor;
            D.raiz->esq->pai = temp;
            if (temp->pai != D.raiz){
                if (temp->dir!=NULL)
                    temp->dir->pai = temp->pai;
                temp->pai->esq = temp->dir;
                D.raiz->dir->pai = temp;
                temp->dir=D.raiz->dir;
            }
            if (D.raiz->pai!=NULL){
                if (D.raiz->pai->esq==D.raiz)
                    D.raiz->pai->esq = temp;
                else
                    D.raiz->pai->dir = temp;
            }
            temp->pai = D.raiz->pai;
            temp->esq = D.raiz->esq;
            D.raiz = temp;
            //temp=NULL;
            di.raiz=D.raiz->dir;
            remove_AVL2(di,D.raiz->chave);
            D.raiz->h = maior(get_altura(D.raiz->esq), get_altura(D.raiz->dir)) + 1;

            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->esq->dir) <= get_altura(D.raiz->esq->esq))
                    RotacaoLL(D);
                else
                    RotacaoLR(D);
            }
        }
        return 1;
    }
    D.raiz->h = maior(get_altura(D.raiz->esq), get_altura(D.raiz->dir)) + 1;
    return res;
}

void remover(DicAVL &D, Noh *n){
    if(D.raiz==NULL){
        cout << "Valor não existe!" <<endl;
        return;
    }else
        remove_AVL(D, n->chave);
}

void libera_no(Noh *n){
    if (n==NULL)
        return;
    libera_no(n->esq);
    libera_no(n->dir);
    delete[] n->valor->verb->verb;
    delete n->valor->verb;
    delete n->valor;
    delete n;
    n=NULL;
}

void terminar (DicAVL &D){
    libera_no(D.raiz);
    D.raiz=NULL;
}

void imprimir(Noh *a){

    if(a!=NULL){

        imprimir(a->esq);
        a->print();
        imprimir(a->dir);

    }

}

void imprimiDicionario(DicAVL &D,string saida){

    remove(saida.c_str());
    imprimir(D.raiz);

}

void imprimiDicionario2(DicAVL &D,string saida){

    imprimir(D.raiz);

}


Noh* atualizaDic(DicAVL &D, TC c, TC _tipo, TV* v){
    Noh *h = new Noh();
    h->chave = c;
    h->tipo = _tipo;
    h->valor = v;
    remover(D,h);
    return inserir(D,c,_tipo,v);
}

int remove1mais(DicAVL &D,Noh *a){

    if(a!=NULL){

        if(remove1mais(D,a->esq)==1){
            return 1;
        }
        if(remove1mais(D,a->dir)==1){
            return 1;
        }
        if(!a->valor->verb->empty()){
            remover(D,a);
            return 1;
        }
        return 0;

    }
    return 0;

}

void RemoveDicionario(DicAVL &D){

    for (int i = 0; i < D.qtd ; i++)
    {
        remove1mais(D,D.raiz);
    }
    

}



#endif // AVL_HPP_INCLUDED

#include "avl.hpp"
#include <typeinfo> 


using namespace std;




int main(int argc, char *argv[]){

    FILE *arq;
    string entrada,saida;
    entrada = argv[2];
    saida = argv[4];
    arq = fopen(entrada.c_str(),"r");
    char Linha[1000];
    char *token;
    char *result;
    DicAVL dic = DicAVL();
    string verbete;
    string tipo;
    string chave;

    if(arq==NULL){
        cout << "Problema ao abrir o arquivo" << endl;
        return 0;
    }
    else{

        inicializar(dic);

        while (!feof(arq)){

            result = fgets(Linha, 1000, arq);

            if(result){

                tipo = strtok(Linha," ");
                chave = strtok(NULL, "]");
                chave = chave.substr(1,chave.length()-1);
                token = strtok(NULL,"\n");
                TV *node;
                if(token != NULL){
                    verbete = token;
                    verbete = verbete.substr(1,verbete.length());
                    node = new TV(verbete,saida);
                }
                else{
                    node = new TV(saida);
                }
                verbete.clear();
                inserir(dic,chave,tipo,node);

            }


        }

    }
    imprimiDicionario(dic,saida);
    RemoveDicionario(dic);
    imprimiDicionario2(dic,saida);
    terminar(dic);

    fclose(arq);
    return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Limite de itens
#define LimiteItens 10

//Struct com o nome, o tipo e quantidade dos itens
typedef struct{
    char nome[30];
    char tipo[20];
    int quantidade;

}item;
//Função pra inserir os itens
void inserirItem(item *itens,int *quantItensTotal){
    int i, quantNovo;
    //Variavel i e quantNovo pra usar no for

    //Perguntando quantos itens o usario deseja
    printf("Informe quantos itens deseja inserir ");
    scanf("%d",&quantNovo);
    getchar();
        //Checando se não chegou no limite maximo de itens
        if (*quantItensTotal + quantNovo > LimiteItens) {
        printf("\nLimite maximo de %d itens atingido!\n", LimiteItens);
        return;
    }
     //For pro usuario informa o nome, o tipo e quantidade dos itens
     for(i=0;i<quantNovo;i++){
         printf("\nInformacoes do item %d\n",i+1);
         printf("Nome: ");
         fgets(itens[*quantItensTotal + i].nome, 30,stdin);
         itens[*quantItensTotal + i].nome[strcspn(itens[*quantItensTotal + i].nome,"\n")]='\0';

         printf("Tipo: ");
         fgets(itens[*quantItensTotal + i].tipo, 20,stdin);
         itens[*quantItensTotal + i].tipo[strcspn(itens[*quantItensTotal + i].tipo,"\n")]='\0';

         printf("Quantidade ");
         scanf("%d",&itens[*quantItensTotal + i].quantidade);
         getchar();
         printf("--------------------------------------------\n");
    }
    //Atualizando o valor de quantItensTotal
    *quantItensTotal += quantNovo;
    printf("Itens cadastrados com sucesso\n");

}
//Função pra remover um item
void remocaoItem(item *itens,int *quantItens){
    int i=0,pos=-1;
    char itemRemover[30];
    //Variavel i pro for e variavel pos pra mudar a struct
    //Variavel itemRemover mostrando qual item a ser removido

    //Checando se tem itens
    if (*quantItens==0){
        printf("Inventario vazio\n");
        return;
    }
    //Chamando a função listar item
    listarItens(itens,*quantItens);
    //Perguntando a usario qual item deseja remover
    printf("Qual item deseja remover: ");
    fgets(itemRemover,30,stdin);
    //Removendo o \n no final do fgets
    itemRemover[strcspn(itemRemover,"\n")]='\0';
    //Checando cada item ate encontrar o itemRemover
    for(i=0;i<*quantItens;i++){
        if(strcmp(itens[i].nome, itemRemover)==0){
            pos = i;
            break;
        }
    }
    //Caso não seja encontrado nenhum item
    if (pos == -1){
        printf("Valor %s nao encontrado\n", itemRemover);
        return;
    }

    //Deslocando os itens
    for(i=pos;i<*quantItens-1;i++){
        itens[i]=itens[i+1];
    }
    //Apagando o item não utilizado
    strcpy(itens[*quantItens -1].nome,"");
    strcpy(itens[*quantItens-1].tipo,"");
    itens[*quantItens-1].quantidade=0;
    //Reduzindo a quantidade de itens
    (*quantItens)--;

    printf("Item '%s' removido com sucesso!\n", itemRemover);
}
//Função pra listar itens
void listarItens(item *itens,int indice){
    int i=0;
    //Variavel para o for

    //Checando se tem itens
    if (indice==0){
    printf("Inventario vazio\n");
    return;
    }
    //Listando os itens
    for(i=0;i<indice;i++){
        printf("\nItem %d\n",i+1);
        printf("Nome: %s -> Tipo: %s -> quantidade: %d\n",itens[i].nome,itens[i].tipo,itens[i].quantidade);
        printf("--------------------------------------------\n");
    }
}
//Função pra buscar um item especificado pelo usuario
void buscarItem(item *itens, int *quantItens){
    int i=0;
    char itemBuscar[30];
    //Variavel i para for e itemBusca para buscar o item informado pelo usuario

    //Checando se tem itens
    if (*quantItens==0){
    printf("Inventario vazio\n");
    return;
    }
    //Perguntando ao usario qual item deseja buscar
    printf("Qual item deseja buscar?\n");
    //Removendo o \n no final do fgets
    fgets(itemBuscar,30,stdin);
    itemBuscar[strcspn(itemBuscar,"\n")]='\0';

    //Checando cada item ate encontrar o itemBuscar
    for(i=0;i<*quantItens;i++){
        if(strcmp(itens[i].nome,itemBuscar)==0){
            printf("Nome: %s -> Tipo: %s -> quantidade: %d\n",itens[i].nome,itens[i].tipo,itens[i].quantidade);
            return;
        }

    }
    //Caso o item não seja encontrado
    printf("Item nao encontrado\n");
}
//Função pra liberar memoria
void liberarMemoria(item *itens){
    free(itens);
    printf("Memoria liberada!\n");
}


int main()
{
    //Variavel opcao pro switch case e quantItenTotal pra mostrar a quantidade de itens
    int opcao, quantItensTotal=0;

    //Alocando memoria
    item *itens = (item *)calloc(10, sizeof(item));
    //Caso de erro ao alocar memoria
    if(itens==NULL){
        printf("Erro ao alocar memória com calloc!\n");
        return 1;
    }

    //while para repetir o codigo ate chegar ao limite ou o usuario sair
    while (1){
        //Informando as opções pro usuario
        printf("\nLIMITE DE ITENS: %d/%d\n", quantItensTotal, LimiteItens);
        printf("Informe oque deseja\n");
        printf("----------1.INSERIR ITEM----------\n");
        printf("----------2.Listar ITENS----------\n");
        printf("----------3.REMOVER ITEM----------\n");
        printf("----------4.BUSCAR ITEM-----------\n");
        printf("----------5.SAIR------------------\n");
        //scanf pro usuario digitar qual opção deseja
        scanf("%d",&opcao);
        getchar();
        //switch case pra chamar as funções
        switch(opcao){
        case 1:
            //chamando a função inserirItem
            inserirItem(itens,&quantItensTotal);
            break;
        case 2:
            //chamando a função listarItem
            listarItens(itens,quantItensTotal);
            break;
        case 3:
            //chamando a função remocaoItem
            remocaoItem(itens,&quantItensTotal);
            break;
        case 4:
            //chamando a função buscarItem
            buscarItem(itens,&quantItensTotal);
            break;
        case 5:
            //chamando a função liberarMemoria
            liberarMemoria(itens);
            return 0;
        }

        }






    return 0;
}



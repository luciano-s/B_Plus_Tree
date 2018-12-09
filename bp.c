#include "bp.h"

int search(FILE* f, int degree, int key, int root, int op){
    typedef struct node{
            int keys[degree-1];
            int index[degree];
            int key_qtd;
            int isleaf;
    }Node;
    Node tree;
    int pos = root-1, k;
    fseek(f,SEEK_SET*(pos),0);
    tree.isleaf = 0;

    while(!tree.isleaf){
        fread(&tree,sizeof(tree),1,f);
        k = 0;
        while(k < tree.key_qtd){
            if(op == 2)
                printf("\n\nChave atual: %d\n\n",tree.keys[k]);
            if(op == 3)
                printf("\n\nÍndice atual: %d\n\n",tree.index[k]);
            if(tree.keys[k] < key){
                pos = tree.index[k+1]-1;
            }else if(tree.keys[k] == key){
                pos = tree.index[k+1]-1;
                break;
            }else if(tree.keys[k] > key){
                pos = tree.index[k]-1;
                break;
            }
            ++k;
        }
        fseek(f,sizeof(tree)*pos,SEEK_SET);
    }

    if(key == tree.keys[k])
        return tree.index[k];
    else return 0;
}

void rangeSearch(FILE* f, int degree, int root, int key, int end, int op){
    typedef struct node{
            int keys[degree-1];
            int index[degree];
            int key_qtd;
            int isleaf;
    }Node;
    FILE* bin = fopen("data.dat","rb");
    fseek(bin,0,SEEK_END);
    int qtd_reg = ftell(bin)/sizeof(Data);
//    printf("qtd_reg = %d\n",qtd_reg);
    if(end > qtd_reg)end = qtd_reg-1;
    if(key > end || key <= 0 || end <= 0){
        printf("Intervalo inválido!\n");
        return;
    }

    while(search(f,degree,key,root,op) == 0){
        key++;
        if(key == qtd_reg || key > end){
            printf("Nenhuma chave no intervalo dado!");
            return;
        }
    }

    Node tree;
    int pos = root-1, k, cont=0;
    fseek(f,0,SEEK_SET);
    tree.isleaf = 0;

    while(!tree.isleaf){
        fread(&tree,sizeof(tree),1,f);
        k = 0;

        while(k < tree.key_qtd){
            if(tree.keys[k] < key){
                pos = tree.index[k+1]-1;
            }else if(tree.keys[k] == key){
                pos = tree.index[k+1]-1;
                break;
            }else if(tree.keys[k] > key){
                pos = tree.index[k]-1;
                break;
            }
            if(op == 2)
                printf("\n\nChave atual: %d\n\n",tree.keys[k]);
            if(op == 3)
                printf("\n\nÍndice atual: %d\n\n",tree.index[k]);

            ++k;
        }
        fseek(f,sizeof(tree)*pos,SEEK_SET);
    }
    int pos_bin = tree.index[k]-1;
    if(pos_bin == -1){
        printf("Nenhuma chave no intervalo dado!\n");
        return;
    }
    int pos_tree = tree.index[degree-1];
    int start = key;
    int aux = 1;
    int i ;
    while(start <= end){
        if(aux)i = k;
        else i = 0;
        start = tree.keys[0];
        for(; i < degree-1 && tree.keys[i] <= end; i++){
            pos_bin = tree.index[i]-1;
            if(pos_bin==-1)break;
            if(print_data(bin,pos_bin,end) == False)return;
            start = tree.keys[i];

            if(op == 2)
                printf("\n\nChave atual: %d\n\n",tree.keys[i]);
            if(op == 3)
                printf("\n\nÍndice atual: %d\n\n",tree.index[i]);
        }
        if(tree.index[degree-1]==0)return;
        fseek(f,sizeof(tree)*(tree.index[degree-1]-1),SEEK_SET);
        fread(&tree,sizeof(Node),1,f);
        aux = 0;
    }
    fclose(bin);
}

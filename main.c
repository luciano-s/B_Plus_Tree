#include "bp.h"
#include "file.h"


bool print_data(FILE* f, int pos, int limit){
    Data data;
    fseek(f,sizeof(Data),SEEK_END);
    int size = ftell(f);
    int size_atual;
    fseek(f,sizeof(Data)*pos,SEEK_SET);
    size_atual = ftell(f);
    if(size_atual > size)return False;
    fread(&data,sizeof(Data),1,f);
    if(data.key > limit)return False;
    print_out(&data,1,0);
    return True;
}

void getData(FILE* f, int pos){
    Data data;
    fseek(f,sizeof(Data)*pos,SEEK_SET);
    fread(&data,sizeof(Data),1,f);
    print_out(&data,1,0);
}

void menu(){
    int op = -1, ret;
    static int root, degree;
    static Txt1* arquivo;
    arquivo = (Txt1 *)malloc(sizeof(Txt1));
    static Data* data;
    data = (Data *)malloc(sizeof(Data));

    while(True){
        system("clear");
        printf("[0] - Sair\n");
        printf("[1] - Carregar novo arquivo de configuração\n");
        printf("[2] - Gerar novo arquivo de dados\n");
        printf("[3] - Carregar nova árvore\n");
        printf("[4] - Buscar um registro\n");
        printf("[5] - Buscar registros em um intervalo\n");
        printf("[6] - Listar dados\n");
        printf("[7] - Listar chaves e índices\n");
        fflush(stdin);
        printf("Insira o valor referente a opção: ");
        scanf("%d",&op);


        switch(op){
            case 0:exit(0);
            case 1:{
                degree = 2*fileTxt1(arquivo, &root);
                wait(1);
                break;
                }
            case 2:{
                system("clear");
                removeCh(arquivo->file1);
                printf("Abrindo arquivo %s\n",arquivo->file1);
                fileData(data,arquivo->file1);
                printf("Arquivo gerado com sucesso!\n");
                wait(1);
                break;
                }
            case 3:{
                fileTxt2(degree,arquivo->file2);
                printf("Arquivo carregado com sucesso!\n");
                wait(1);
                break;
                }
            case 4:{
                int opcao;
                FILE* f = fopen("tree.dat","rb");
                printf("1 - Imprimir registros\n2 - Imprimir chaves\n3 - Imprimir índice\n");
                scanf("%d",&opcao);
                printf("Insira  chave que deseja buscar: ");
                int chave;
                scanf("%d",&chave);breakline;
                ret = search(f,degree,chave,root,opcao);
                if(ret == 0){
                    printf("\nChave não encontrada\n");
                    wait(1);
                    break;
                }
                FILE* bin = fopen("data.dat","rb");
                getData(bin,ret-1);
                fclose(bin);
                printf("Pressione <ENTER> para voltar ao menu");
                setbuf(stdin,NULL);
                getchar();
                break;
                }
            case 5:{
                int ini, fim, opcao;
                FILE* f = fopen("tree.dat","rb");
                fflush(stdin);
                printf("1 - Imprimir registros\n2 - Imprimir chaves\n3 - Imprimir índice\n");
                scanf("%d",&opcao);
                fflush(stdin);
                printf("Insira o primeiro valor do intervalo: ");
                scanf("%d",&ini);
                breakline;
                printf("Insira o segundo valor do intervalo: ");
                scanf("%d",&fim);
                rangeSearch(f,degree,root,ini,fim,opcao);
                printf("Pressione <ENTER> para voltar ao menu");
                setbuf(stdin,NULL);
                getchar();
                break;
                }
            case 6:{
                FILE* f = fopen("data.dat","rb");
                readBin(f,0,0);
                fclose(f);
                printf("Pressione <ENTER> para voltar ao menu");
                setbuf(stdin,NULL);
                getchar();
                break;
                }
            case 7:{
                FILE* f = fopen("tree.dat","r");
                readBin(f,1,degree);
                printf("Pressione <ENTER> para voltar ao menu");
                setbuf(stdin,NULL);
                getchar();
                break;
                }
            default:printf("Opção Inválida!!\n");
        }
    }
}

int main(){
    //init();
    resetlog();
    menu();
    return 0;
}

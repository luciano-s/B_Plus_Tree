#include "file.h"
#include <stdlib.h>
#include <stdio.h>
#include "bp.h"


/** funcoes de proposito geral para manipulacao de arquivos **/

char* getFileName(){
    char *var = (char *)malloc(sizeof(char)*20);
    printf("Insira o nome do arquivo: ");
    setbuf(stdin,NULL);
    fgets(var,20,stdin);

    if(var == NULL){
        FILE* log = fopen("log.txt","at");
        fprintf(log,"Nome %s inválido!\n",var);
        fclose(log);
        printf("Erro!");
        exit(1);
    }
    puts(var);
    return var;
}


bool isFileValid(FILE* const f,const char* const name){
    FILE* log = fopen("log.txt","at");
    if(f == NULL){
        fprintf(log,"Erro arquivo %s!: %s\n",name,strerror(errno));
        fclose(log);
        return False;
    }
    fclose(log);
    return True;
}

/** fim **/



/** funcoes de manipulacao do arquivo texto 1 **/

 int fileTxt1(Txt1* const arquivo, int* root){
    char buffer[30], name[20];

    FILE *f;
    bool var = False;
    while(!var){
        system("clear");
        strcpy(name,getFileName());
        removeCh(name);
        f = fopen(name,"rt");
        if(f == NULL){
            printf("NULL\n");
        }
        if(isFileValid(f,name))
            var = True;
        else {
            printf("\n%s\n", strerror(errno));
            wait(1);
            var = False;
        }
    }
    fgets(buffer,30,f);
    fclose(f);
    //printf("Imprimindo variavel buffer: ");
    //fputs(buffer,stdout);
    breakline;

    setTxt1Elements(buffer,arquivo,30);
    printf("Arquivo lido com sucesso!\n");
    //print_out(arquivo,1);
    *root = arquivo->root_pos;
    return arquivo->degree;
 }


void setTxt1Elements(char const* const buff, Txt1* const file, int size){
    short i = 0, j = 0;
    int num_buff = 0;
    if(i > size)return;
    while(isNumber(buff[i])){
        //printf("num_buff(dentro do while) = %d\n",num_buff);
        num_buff *= 10;
        num_buff += parseInt(buff[i]);
        ++i;
    }
    //printf("num_buff = %d\n",num_buff);
    file->degree = num_buff;
    num_buff = 0;
    ++i;
    while(isNumber(buff[i])){
      //  printf("num_buff(dentro do while) = %d\n",num_buff);
        num_buff *= 10;
        num_buff += parseInt(buff[i]);

        ++i;
    }
    //printf("num_buff = %d\n",num_buff);
    file->root_pos = num_buff;
    ++i;
    while(buff[i] != ','){
        file->file2[j] = buff[i];
        ++j;++i;
    }++i;j = 0;
    while(buff[i]){
        file->file1[j] = buff[i];
            ++j;++i;
    }
}
/** fim **/

/** funcoes de maniulacao do arquivo texto 2 **/

void fileTxt2(const int degree, char* name){
    char buffer[80];
    typedef struct node{
            int keys[degree-1];
            int index[degree];
            int key_qtd;
            int isleaf;
    }Node;
    Node* arquivo = (Node *)malloc(sizeof(Node));

    FILE *f;
    bool var = False;
    system("clear");
    removeCh(name);

    f = fopen(name,"rt");
    if(isFileValid(f,name)){
        printf("Abrindo %s\n",name);
    }
    else {
        printf("\n%s\n", strerror(errno));
        wait(1);
        return;
    }
    FILE* bin = fopen("tree.dat","wb");
    if(!isFileValid(bin,"tree.dat")){
        printf("Erro: %s\n",strerror(errno));
        exit(1);
    }
    fseek(bin,SEEK_SET,0);
    while(True){
        setNull(buffer,1);
        if(!fgets(buffer,80,f))break;

        setTxt2Elements(buffer,arquivo,80, degree);

        setbuf(stdin,NULL);

        fwrite(arquivo,sizeof(Node),1,bin);
        if(feof(f))break;
    }
    fclose(f);
    fclose(bin);
}

void setTxt2Elements(char* const buff, void* ptr, const int size, const int degree){
    typedef struct node{
            int keys[degree-1];
            int index[degree];
            int index_qtd;
            int isleaf;
    }Node;

    Node* tree = (Node *)ptr;
    //setNull(tree,2,order);
    short i = 0, j = 0;
    long int num_buff = 0L;

    if(i >= size)return;

    //setbuf(stdin,NULL);
    //printf("BUFFER[%d]: %d\n",i,buff[i]);
    //getchar();
    if(isNumber(buff[i]))tree->index_qtd = parseInt(buff[i]);
    i+=2;
    //printf("index_qtd: %d\n",tree->index_qtd);

    //printf("BUFFER[%d]: %d\n",i,buff[i]);
    if(isNumber(buff[i]))tree->isleaf = parseInt(buff[i]);
    i+=2;
    //printf("isleaf: %d\n",tree->isleaf);
    //getchar();

    for(int j = 0; j < degree-1; j++){
    	num_buff = 0;
        while(isNumber(buff[i]) && i < size){
            num_buff *= 10;
            num_buff += parseInt(buff[i]);
            ++i;
        }
        i++;
        tree->keys[j] = num_buff;
    }

    for(int j = 0; j < degree; j++){
        num_buff = 0;
        while(isNumber(buff[i]) && i < size){
            num_buff *= 10;
            num_buff += parseInt(buff[i]);
            ++i;
        }
        i++;
        tree->index[j] = num_buff;
    }
}
/** fim **/


/** funcoes de leitura e escrita em arquivo binario **/

bool writeBinFile(Data* const data, FILE* f){
    if(fwrite(data,sizeof(data),1,f)) return True;
    FILE*log = fopen("log.txt","a");
    fprintf(log,"Erro ao escrever dados de %s no arquivo!\n",data->name);
    fclose(log);
    return False;
}

void readBin(FILE* f, int type, int degree){
    if(type == 0){
        Data data;
        setNull(&data,0);
        fseek(f,SEEK_SET,0);
        while(True){
            if(fread(&data,sizeof(Data),1,f)){
                print_out(&data,1,0);
            }
            if(feof(f))return;
        }

    }else if(type == 1){
        typedef struct node{
            int keys[degree-1];
            int index[degree];
            int index_qtd;
            int isleaf;
        }Node;
        Node tree;
        while(True){
            if(fread(&tree,sizeof(Node),1,f)){
                print_out(&tree,2,degree);
            }
            if(feof(f))return;
        }
    }
}

/** fim **/


/** funcoes de processamento da estrutura Data **/

void fileData(Data* const data, char* name){
    setNull(data,0);
    const int buff_size = 80;
    char buffer[buff_size];
    FILE *f;
    f = fopen(name,"rt");
    if(isFileValid(f,name) == False){
        printf("%s\n",strerror(errno));
        wait(1);
        return;
    }
    FILE* bin = fopen("data.dat","wb+");
    if(!isFileValid(bin,"data.dat")){
        printf("Erro: %s\n",strerror(errno));
        exit(1);
    }
    setNull(buffer,1);
    fgets(buffer,buff_size,f);
    while(True){/* - Loop p/ converter txt --> binario - */
        setDataElements(buffer,data,buff_size); /* coloca os dados na struct */
        fwrite(data,sizeof(Data),1,bin);
        setNull(buffer,1);
        setNull(data,0);
        fgets(buffer,buff_size,f);
        if(feof(f))break;
    }
    fclose(f);
    fclose(bin);
}

void setDataElements(char* const buff, Data* const data, const int size){
    setNull(data,0);
    short i = 0, j = 0;
    long int num_buff = 0L;

    if(i >= size)return;

    while(isNumber(buff[i]) && i < size){
   //     printf("num_buff(dentro do while) = %ld\n",num_buff);
        num_buff *= 10;
        num_buff += parseInt(buff[i]);
        ++i;
    }
//    printf("num_buff = %ld\n",num_buff);
    data->key = num_buff;
    num_buff = 0;
    ++i;

    while(isLetter(buff[i]) && i < size)data->UF[j++] = buff[i++];
    i++;
    data->UF[j] = '\0';
    j = 0;

    while(isNumber(buff[i]) && i < size){
//        printf("num_buff(dentro do while) = %ld\n",num_buff);
        num_buff *= 10;
        num_buff += parseInt(buff[i]);
        ++i;
    }
//    printf("num_buff = %ld\n",num_buff);
    i++;data->city_code = num_buff;
    num_buff = 0L;

    while(buff[i] != ','){
        data->name[j++] = buff[i++];
    }data->name[j] = '\0';
//    printf("Data->name: ");
  //  puts(data->name);
    //getchar();

    i++;
    while(isNumber(buff[i]) && i < size){
//        printf("num_buff(dentro do while) = %ld\n",num_buff);
        num_buff *= 10;
        num_buff += parseInt(buff[i]);
        ++i;
        if(buff[i] == ',')++i;
    }
//    printf("num_buff = %ld\n",num_buff);
    ++i;
    data->area = (double)num_buff;
}

/** fim **/

/** funcoes auxiliares **/

void print_out(void* ptr, int type, int degree){
    if(type == 0){
        Txt1* txt = (Txt1 *)ptr;
        printf("Grau: %d\n",txt->degree);
        printf("Posição raiz: %d\n",txt->root_pos);
        printf("Arquivo 1: %s\n",txt->file1);
        printf("Arquivo 2: %s",txt->file2);
    }else if(type == 1){
        Data* data = (Data *)ptr;
        data = (Data *)ptr;
        printf("ID: %d\n",data->key);
        printf("UF: %s\n",data->UF);
        printf("Código da cidade: %ld\n",data->city_code);
        printf("Cidade: %s\n",data->name);
        printf("Área: %lf\n",data->area);
    }else if(type == 2){
        typedef struct node{
            int keys[degree-1];
            int index[degree];
            int key_qtd;
            int isleaf;
        }Node;
        Node* str = (Node *)ptr;
        printf("Quantidade chaves: %d\n",str->key_qtd);
        printf("Folha: %d\n",str->isleaf);
        for(int i = 0; i < degree-1; i++){
            printf("Chave[%d]: %d\n",i,str->keys[i]);
        }
        for(int i = 0; i < degree; i++){
                printf("Index[%d]: %d\n",i,str->index[i]);
        }
    }
}

void resetlog(){
    FILE* log = fopen("log.txt","w");
    fclose(log);
}

void setNull(void* ptr, int type){
    if(type == 0){
        Data* d = (Data *)ptr;
        d->area = 0;
        d->city_code = -1;
        d->key = -1;
        for(int i = 0; i < 3;i++)d->UF[i] = '\0';
        for(int i = 0; i < 29;i++)d->name[i] = '\0';
    }else if(type == 1){
        char* str = (char *)ptr;
        for(int i = 0; i < 80; i++)str[i] = '\0';
    }else if(type == 2){
        char* str = (char *)ptr;
        for(int i = 0; i < 20; i++)str[i] = '\0';
    }
}

void wait(unsigned short int sec){
    size_t st, end, seconds;
    st = clock();
    while(seconds != sec){
        end = clock();
        seconds = (end-st)/CLOCKS_PER_SEC;
    }
}

/** fim **/

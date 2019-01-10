
#define TAM 256

typedef struct{
    char nome[TAM];
    char cpf[TAM];
    char ci[TAM];
    char endereco[TAM];
    char tel[TAM];
}TipoItem;

typedef struct{
    TipoItem item;
    struct TipoCelula *Prox;    // prox é um ponteiro para uma célula inteira
}TipoCelula;

typedef struct{
    TipoCelula *Primeiro , *Ultimo ;
    int Tamanho ;
}TipoLista;

bool testaCpfExiste(TipoLista *Lista, char ch[TAM]);

void FLVazia(TipoLista *Lista){
    Lista->Primeiro = (TipoCelula *) malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
    Lista->Tamanho = 0;
}

bool Vazia(TipoLista *Lista){
    return(Lista->Primeiro == Lista->Ultimo);
}

int Tamanho(TipoLista *Lista){
    return(Lista->Tamanho);
}

void cadastrarPassag(TipoLista *cad){
    TipoItem p;
    char k;
    printf("\nDeseja sair do cadastro de aluno? s/n: ");
    fflush(stdin);
    scanf("%c", &k);
    while(k != 's'){

    printf("\n\nCADASTRO DE PASSAGEIRO\n\n");
    printf("\nInforme o nome: ");
    lerString(p.nome);
    printf("\nInforme o CPF: ");
    lerString(p.cpf);
    printf("\nInforme o CI: ");
    lerString(p.ci);
    printf("\nInforme o endereco: ");
    lerString(p.endereco);
    printf("\nInforme o telefone: ");
    lerString(p.tel);

        if(Vazia(cad)){
            Insere(cad, p);
        }
        else if(!testaCpfExiste(cad, p.cpf)){
            Insere(cad, p);
        }
        else{
            printf("\nNao e possivel cadastrar passageiro. Este CPF ja esta sendo usado!\n");
        }
    printf("\nDeseja sair do cadastro de aluno? s/n: ");
    fflush(stdin);
    scanf("%c", &k);
    }
    if(!Vazia(cad)){
        gravarHD(cad);
    }
}

bool testaCpfExiste(TipoLista *Lista, char ch[TAM]){
    TipoCelula *t1, *t2; // ponteiros auxiliares

        t1 = Lista->Primeiro;
        t2 = Lista->Primeiro->Prox;

        while( (t2 != NULL) && (ch != t2->item.cpf) ){
            t1 = t1->Prox;
            t2 = t2->Prox;
        }

        // verifica se a chave pesquisada nao esta na lista
        if(t2 == NULL){
            printf("\nCPF EXISTE!\n");
            return true;
        }
        else{
            printf("\nCPF NAO EXISTE!\n");
            return false;
        }
}

void gravarHD(TipoLista *p){
    FILE *arq;
    TipoCelula *t1, *t2;

    if((arq = fopen("passageiro.dat", "wb")) == NULL){
        printf("\nERRO ao abrir o 'passageiro.txt'\n");
        exit(1);
    }
        t1 = p->Primeiro;
        t2 = p->Primeiro->Prox;

        while(t2 != NULL){
            t1 = t1->Prox;
            fwrite(&(t1->item), sizeof(TipoItem), 1, arq);
            t2 = t2->Prox;

        }
    fclose(arq);
}

void imprimePassag(TipoItem *p){
    printf("\nNOME: %s", p->nome);
    printf("\nCPF: %s", p->cpf);
    printf("\nCARTEIRA DE IDENTIDADE: %s", p->ci);
    printf("\nENDERECO: %s", p->endereco);
    printf("\nTELEFONE: %s\n", p->tel);
}

bool pesquisaPassageiroHD(){
    FILE *arq;
    char chave[TAM];
    int y = 0;
    TipoItem p,*k;
    printf("\nDigite o CPF ou NOME do passageiro que deseja pesquisar: ");
    lerString(chave);
    if((arq = fopen("passageiro.dat", "rb")) == NULL){
        printf("\nERRO ao abrir o 'passageiro.dat'\n");
        exit(1);
    }
    while(fread(&p, sizeof(TipoItem), 1, arq) == 1){
        if(strcmp(p.cpf,chave)==0){
            k = &p;
            imprimePassag(k);
            return true;
        }else if(strcmp(p.nome,chave)==0){
            k = &p;
            imprimePassag(k);
            y = 1;
        }
    }


    fclose(arq);
    if(y == 0)
    {
        return false;
    }
    return true;
}

int preencheLista(TipoLista *cad){
    FILE *arq;

    TipoItem p;
    if((arq = fopen("passageiro.dat", "rb")) == NULL){
        printf("\nNenhum passageiro cadastrado\n");
    return 0;
    }

    while(fread(&p, sizeof(TipoItem),1, arq) == 1){
        Insere(cad, p);
    }
    fclose(arq);
}



void InsereNoFim(TipoLista *Lista, TipoItem item){
    Lista->Ultimo->Prox = (TipoCelula *) malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->item = item;
    Lista->Ultimo->Prox = NULL;
    Lista->Tamanho++;
}

void Insere(TipoLista *Lista, TipoItem item){
    TipoCelula *t1, *t2; // ponteiros auxiliares

    if(Vazia(Lista))
        InsereNoFim(Lista, item);
    else{
        // se o valor da chave a ser iserido e maior que todas
        // as chaves presentes na lista, insere no fim
        if(atoi(item.cpf) > atoi(Lista->Ultimo->item.cpf))
            InsereNoFim(Lista, item);
        else{
            t1 = Lista->Primeiro;
            t2 = Lista->Primeiro->Prox;

            while(atoi(item.cpf) > atoi(t2->item.cpf)){
                t1 = t1->Prox;
                t2 = t2->Prox;
            }
            t1->Prox = (TipoCelula *) malloc(sizeof(TipoCelula));
            t1 = t1->Prox;
            t1->Prox = t2;
            t1->item = item;    // insere todo o item (a struct)
            Lista->Tamanho++;
        }
    }
}

bool Pesquisa(TipoLista *Lista, char ch[TAM], TipoItem *item){
    TipoCelula *t1, *t2; // ponteiros auxiliares
    int encontrado=0;
    if(Vazia(Lista)){
        printf("\nA lista esta vazia.\n");
        return false;
    }

    else{
        t1 = Lista->Primeiro;
        t2 = Lista->Primeiro->Prox;

        while(t2 != NULL){
            if((strcmp(t2->item.cpf,ch)==0) || (strcmp(t2->item.nome,ch)==0 ))
            {
                encontrado=1;
                printf("\nChave encontrada.\n");
                printf("\nNome do fulano.\n");
                imprimeString(t2->item.nome);
                printf("\cpf do fulano.\n");
                imprimeString(t2->item.cpf);

            }
            t1 = t1->Prox;
            t2 = t2->Prox;
        }

        // verifica se a chave pesquisada nao esta na lista
        if(encontrado == 0){
            printf("\nChave nao encontrada.\n");
            return false;
        }
        else
        {
            return true;
        }
   }
}

void Imprime(TipoLista *Lista){
    TipoCelula *temp = Lista->Primeiro->Prox;

    while ( temp != NULL ){
        printf("\nNome    :");
        imprimeString(temp->item.nome);
        printf("\n\nCPF   :");
        imprimeString(temp->item.cpf);
        printf("\nCARTEIRA DE IDENTIDADE:");
        imprimeString(temp->item.ci);
        printf("\nTELEFONE: ");
        imprimeString(temp->item.tel);
        printf("\nEndereco: ");
        imprimeString(temp->item.endereco);
        temp = temp->Prox;
    }
}


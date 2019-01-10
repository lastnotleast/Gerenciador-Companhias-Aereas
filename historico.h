#define TAM 256

typedef struct{
 int cpf[TAM],numParcelas,numVoo;
 float valorParcela;
}historico;

void cadastrarHistorico(TipoLista *cad){
    historico p;

    int n=0;
    bool k;
    int q=0;

    printf("\nDigite o cpf do passageiro :");
    lerString(p.cpf);
    k = testaCpfExiste(cad,p.cpf);
    if(k){
    do{
        if(n>0){
            printf("\nCodigo do voo nao exite, por favor digite novamente:");
        }
        printf("\nInforme o codigo do voo: ");
        scanf("%d",&p.numVoo);
        q = testaVooHD(p.numVoo);
        n++;
    }while(!q);

    printf("\nDigite o numero de parcelas :");
    scanf("%d",&p.numParcelas);
    printf("\nDigite o preco de parcelas :");
    scanf("%f",&p.valorParcela);
    gravarHistoricoHD(p);
    }
    else{
        printf("\nPassageiro nao existe!\n");
    }
}


void imprimirHistorico(historico p){
    printf("\nCpf do passageiro: ");
    imprimeString(p.cpf);
    printf("\nDigite o numero do voo:");
    printf("%d", p.numVoo);
    printf("\nDigite o numero de parcelas:");
    printf("%d", p.numParcelas);
    printf("\nDigite o preco de parcelas:");
    printf("%.2f", p.valorParcela);
}

void gravarHistoricoHD(historico p){
    FILE *arq;
    if((arq = fopen("historico.dat", "ab")) == NULL){
        printf("\nERRO ao abrir ou criar o arquivo\n");
        exit(1);
    }
    fwrite(&p, sizeof(historico), 1, arq);
    fclose(arq);
}

void lerHistoricoHD(){
    FILE *arq;
    historico p;
    if((arq = fopen("historico.dat", "rb")) == NULL){
        printf("\nERRO ao abrir o arquivo\n");
        exit(1);
    }
    while(fread(&p, sizeof(historico),1, arq)==1){
        imprimirHistorico(p);
    }
    fclose(arq);
}


void pesquisaHistoricoHD(){
    FILE *arq;
    FILE *arq2;
    historico p;
    TipoItem k;
    int numPesquisa;
    printf("\nDigite o numero do voo\n");
    scanf("%d",&numPesquisa);
    if((arq = fopen("historico.dat", "rb")) == NULL){
        printf("\nERRO ao abrir o arquivo\n");
        exit(1);
    }

    if((arq2 = fopen("passageiro.dat", "rb")) == NULL){
        printf("\nERRO ao abrir o 'passageiro.dat'\n");
        exit(1);
    }
    while(fread(&p, sizeof(historico),1, arq)==1){
        if(p.numVoo == numPesquisa){
            while(fread(&k, sizeof(TipoItem), 1, arq2) == 1){
                if(strcmp(k.cpf, p.cpf) == 0){
                    printf("\nNOME: %s", k.nome);
                    printf("\nCPF: %s\n", k.cpf);
                }
            }
            return NULL;
        }
    }
    fclose(arq2);
    fclose(arq);
}

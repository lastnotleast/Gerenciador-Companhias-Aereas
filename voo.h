typedef struct{
    int num_voo, maxPassag[50];
    float hora_part, hora_cheg, data_partida, data_chegada;
    //char hora_part[6], hora_cheg[6], data_partida[10], data_chegada[10],
    char cidOrigem[50], cidDestino[50], companhia[100];
    float valePassagem;
}tipoVoo;


int testaVooHD(int numPesquisa){
    FILE *arq;
    tipoVoo p;

    if((arq = fopen("voo.dat", "rb")) == NULL){
        return 0;
    }

    while(fread(&p, sizeof(tipoVoo),1, arq)==1){
        if(p.num_voo == numPesquisa)
        {
            fclose(arq);
            return 1;
        }
    }

    fclose(arq);
    return 0;
}


void cadastroVoos(){
    tipoVoo p;
    int q=0,z=0,n=0;
    fflush(stdin);
    do{
        if(n>0){
            printf("\nCodigo do voo ja exite, por favor digite novamente: ");
        }
        printf("\nInforme o codigo do voo: ");
        scanf("%d",&p.num_voo);
        q = testaVooHD(p.num_voo);
        n++;
    }while(q);
    printf("\nInforme o numero maximo de passageiros: ");
    lerString(p.maxPassag);
    do{
        if(z>0){
            printf("\nData e hora inaceitaveis, por favor digite novamente:");
        }
        printf("\nInforme a hora de partida: ");
        scanf("%f",&p.hora_part);
        printf("\nInforme a hora de chegada: ");
        scanf("%f",&p.hora_cheg);
        printf("\nInforme a data de partida: ");
        scanf("%f",&p.data_partida);
        printf("\nInforme a data de chegada: ");
        scanf("%f",&p.data_chegada);
        z++;
    }while(!(p.data_partida<p.data_chegada || (p.data_partida==p.data_chegada) && (p.hora_part<p.data_chegada)));
    printf("\nInforme a cidade de origem: ");
    lerString(p.cidOrigem);
    printf("\nInforme a cidade de destino: ");
    lerString(p.cidDestino);
    printf("\nInforme a companhia: ");
    lerString(p.companhia);
    printf("\nInforme o preco da passagem: ");
    scanf("%f",&p.valePassagem);
    gravarVooHD(p);
}

void imprimeVoos(tipoVoo p){
    printf("\nCodigo do voo: ");
    printf("%d",p.num_voo);
    printf("\nNumero maximo de passageiros: ");
    imprimeString(p.maxPassag);
    printf("\nHora de partida: ");
    printf("%.2f",p.hora_part);
    printf("\nHora de chegada: ");
    printf("%.2f",p.hora_cheg);
    printf("\nData de partida: ");
    printf("%.2f",p.data_partida);
    printf("\nData de chegada: ");
    printf("%.2f",p.data_chegada);
    printf("\nCidade de origem: ");
    imprimeString(p.cidOrigem);
    printf("\nCidade de destino: ");
    imprimeString(p.cidDestino);
    printf("\nCompanhia aerea: ");
    imprimeString(p.companhia);
    printf("\nPreco da passagem: ");
    printf("%.2f",p.valePassagem);
}


void gravarVooHD(tipoVoo p){
    FILE *arq;
    if((arq = fopen("voo.dat", "ab+")) == NULL){
        printf("\nERRO ao abrir ou criar o arquivo\n");
        exit(1);
    }
    fwrite(&p, sizeof(tipoVoo), 1, arq); // 1 = quantidade de vezes que vc salva a struct cliente (tam=1032)
    fclose(arq);
}

void lerVooHD(){
    FILE *arq;
    tipoVoo p;
    if((arq = fopen("voo.dat", "rb")) == NULL){
        printf("\nERRO ao abrir ou criar o arquivo\n");
        exit(1);
    }
    while(fread(&p, sizeof(tipoVoo),1, arq)==1){
        imprimeVoos(p);
    }
    fclose(arq);
}


void pesquisaVooHD(){
    FILE *arq;
    tipoVoo p;
    int numPesquisa;
    printf("\nInforme o codigo do voo: ");
    scanf("%d",&numPesquisa);

    if((arq = fopen("voo.dat", "rb")) == NULL){
        printf("\nERRO ao abrir ou criar o arquivo\n");
        exit(1);
    }

    while(fread(&p, sizeof(tipoVoo),1, arq)==1){
        if(p.num_voo == numPesquisa)
        {
            imprimeVoos(p);
            break;
        }
    }

    fclose(arq);
}


//void ordenaArquivosVoos()

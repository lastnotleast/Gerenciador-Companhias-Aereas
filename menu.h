
void menu(){
int n;
    char sair, *resultado;
    TipoItem *tempo;

    TipoLista *cad = (TipoLista*)malloc(sizeof(TipoLista));

    printf("\nDeseja sair do programa? s/n: ");
    scanf("%c", &sair);
    FLVazia(cad);
    preencheLista(cad);
    while(sair != 's'){
        printf("\n\nSelecione a opcao:\n\n1 - CADASTRAR passageiro\n2 - IMPRIMIR passageiros cadastrados\n3 - PROCURAR passageiro\n");
        printf("4 - CADASTRAR VOO\n5 - IMPRIMIR lista de passageiros de um VOO\n6 - IMPRIMIR os VOOS\n7 - PESQUISAR os VOOS\n");
        printf("8 - CADASTRAR PASSAGEIRO EM VOO\n\n");
        scanf("%d", &n);
        switch(n){
        case 1:
            cadastrarPassag(cad);
        break;
        case 2:
            Imprime(cad);
        break;
        case 3:
                pesquisaPassageiroHD();
        break;
        case 4:
            cadastroVoos();
        break;
        case 5:
            pesquisaHistoricoHD();
        break;
        case 6:
            lerVooHD();
        break;
        case 7:
            pesquisaVooHD();
        break;
        case 8:
            cadastrarHistorico(cad);
        break;
        default:
            printf("\nOpcao invalida!\n\n");
        }
        printf("\nDeseja sair do programa? s/n: ");
        fflush(stdin);
        scanf("%c", &sair);
        system("cls");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a estrutura de clientes ira apontar para a estrutura paises
//lista deve ser criada previamente, em tempo de compilação
//Nome do arquivo perguntas_Paises
/*
pergunta1 60
pergunta2 50
pergunta3 70
pergunta4 40
pergunta5 56
pergunta6 66
pergunta7 80
pergunta8 30
pergunta9 46
pergunta10 54
pergunta11 58
pergunta12 64
pergunta13 68
pergunta14 76
pergunta15 90
paisA 29
paisB 33
paisC 45
paisD 49
paisE 53
paisF 55
paisG 57
paisH 59
paisI 63
paisJ 65
paisK 67
paisL 69
paisM 75
paisN 79
paisO 89
paisP 101
*/

typedef struct listaPaises{
	char nome[30];
	int cod;
	struct listaPaises *next;
	struct listaClientes *cliente;
}listaPaises;

typedef struct listaClientes{
	char nome[50];
	char tipo;
	int codPlano;
	struct listaClientes *next;
}listaClientes;

typedef struct arvoreDecisao{
	char info[100];
	int cod;
	struct arvoreDecisao *casoSim;
	struct arvoreDecisao *casoNao;
}Arvore;

Arvore *criar_Raizes(Arvore *raiz);
Arvore *gerar_Arvore(Arvore *raiz, char infoRaiz[], int codArvore);
void printEmOrdem(Arvore *raiz);

listaPaises *criarElemento(char nomePais[50], int codPais);
void cadastrarCliente(listaPaises **listaTotal_Paises, Arvore *raizBase);
void encadear_listaPaises(listaPaises **listaTotal_Paises, listaPaises *elementoPaises);
void encadearClientes(listaPaises **listaTotal_Paises, listaClientes cliente, int codPais);
void gerar_ListaPaiseslista(listaPaises **listaTotal_Paises);
void listarPaises(listaPaises *listaTotal_Paises);
void listarEstrutura(listaPaises *listaTotal_Paises);
int buscaPais(Arvore *raiz);
int escolherDestino(int opInf);

void paisesVisitados(listaPaises *listaTotal_Paises);
void paisesNaoVisitados(listaPaises *listaTotal_Paises);
void clientesQueVisitaramUmPais(listaPaises *listaTotal_Paises, int codPais);
void paisesVisitadosPorDec_Ind(listaPaises *listaTotal_Paises, char tipoCliente);
int qtdVisitantesPorPlano(listaPaises *listaTotal_Paises, int tipoPlano, int codPais);
void paisMaisVisitados(listaPaises *listaTotal_Paises);
short existeClienteTipo(listaClientes *cliente, char tipoCliente);
void menuAgencia();
void menuRelatorios();


int main(){
	char opcao;
	int codPais;
	listaPaises *listaTotal_Paises = NULL;
	gerar_ListaPaiseslista(&listaTotal_Paises);
	Arvore *raizBase = NULL;
	raizBase = criar_Raizes(raizBase);

	do{
        menuAgencia();
        printf("Informe uma opcao: ");
        scanf(" %c", &opcao);
        system("cls");
        if(opcao == '1')
            cadastrarCliente(&listaTotal_Paises, raizBase);

        else if(opcao == '2'){
               system("cls");
            menuRelatorios();
            char opInfRel = 0;
            printf("Informe uma opcao: ");
            scanf(" %c", &opInfRel);
            system("cls");
            if(opInfRel == '1'){
                listarPaises(listaTotal_Paises);
                system("pause");
            }else if(opInfRel == '2'){
                fflush(stdin);
                printf("\n\n");
                char tipoCliente;
                printf("D-> Decidido\nI-> Indeciso\n");
                printf("Informe o tipo de plano: ");
                scanf(" %c", &tipoCliente);
                paisesVisitadosPorDec_Ind(listaTotal_Paises, tipoCliente);
                system("pause");
            }else if(opInfRel == '3'){
                system("cls");
                paisesVisitados(listaTotal_Paises);
                system("pause");
            }else if(opInfRel == '4'){
                system("cls");
                paisesNaoVisitados(listaTotal_Paises);
                system("pause");
            }else if(opInfRel == '5'){
                int cdPais;
                listarPaises(listaTotal_Paises);
                printf("Informe um pais: ");
                scanf(" %d", &cdPais);
                cdPais = escolherDestino(cdPais);
                clientesQueVisitaramUmPais(listaTotal_Paises, cdPais);
                system("pause");
            }else if(opInfRel == '6'){
                system("cls");
                paisMaisVisitados(listaTotal_Paises);
                system("pause");
            }else if(opInfRel == '7'){
                listarPaises(listaTotal_Paises);
                printf("Informe um pais: ");
                scanf(" %d", &codPais);
                codPais = escolherDestino(codPais);
                printf("\nO PAIS FOI VISITADO POR [%d] CLIENTES DO PLANO SIMPLES", qtdVisitantesPorPlano(listaTotal_Paises, 1, codPais));
                printf("\nO PAIS FOI VISITADO POR [%d] CLIENTES DO PLANO PREMIUM", qtdVisitantesPorPlano(listaTotal_Paises, 2, codPais));
                system("pause");
            }
        }//FIM else relatorios
        else if(opcao == 'e'){
            listarEstrutura(listaTotal_Paises);
            system("pause");
        }
        system("cls");
	}while(opcao != '0');//FIM laço infinito


	system("pause");
	return 0;
}//FIM main

listaPaises *criarElemento(char nomePais[50], int codPais){
	listaPaises *novo = (listaPaises*)malloc(sizeof(listaPaises));
	if(novo == NULL) exit(EXIT_FAILURE);

	novo->cod = codPais;
	strcpy(novo->nome, nomePais);
	novo->next = NULL;
	novo->cliente = NULL;
}//FIM function


void cadastrarCliente(listaPaises **listaTotal_Paises, Arvore *raizBase){
    char opcao;
    int codPais;
    listaClientes novoCliente;

    printf("=================== BEM VINDO A AGENCIA DE VIAGENS ASSUNCAO TURISMO ===================\n\n");
    fflush(stdin);

    printf("Digite seu nome!\n-> ");
    scanf("%[^\n]s", novoCliente.nome);
    system("cls");

    printf("Qual o plano da sua preferencia?\n(1)Padrao\t(2)Premium\n\nOpcao-> ");
    scanf(" %d", &novoCliente.codPlano);
    system("cls");

    printf("================ Atualmente possuimos roteiros de viagens para os seguintes destinos ================\n\n");
    listarPaises(*listaTotal_Paises);

    printf("\n\nJa possui um destino em mente?\n\n(s)Sim\t(n)Nao\nOpcao->");
    scanf(" %c", &opcao);
    if(opcao == 's'){
        printf("\nDigite o codigo correspondente ao pais desejado!\n\n");
        printf("Codigo do pais-> ");
        scanf("%d", &codPais);
        codPais = escolherDestino(codPais);
        novoCliente.tipo = 'D';		//Cliente decidido
    }
    else{
        printf("Iremos lhe ajudar!!!");
        system("cls");
        printf("===================== BEM VINDO A NOSSA ARVORE DE AUXILIO A DECISAO ====================\n\n");
        codPais = buscaPais(raizBase);
        novoCliente.tipo = 'I';		//Cliente indeciso
    }

    encadearClientes(listaTotal_Paises, novoCliente, codPais);
    system("cls");
}

void encadear_listaPaises(listaPaises **listaTotal_Paises, listaPaises *elementoPaises){
	if(*listaTotal_Paises == NULL){
		*listaTotal_Paises = elementoPaises;
	}else{
		elementoPaises->next = *listaTotal_Paises;
		*listaTotal_Paises = elementoPaises;
	}
}//FIM function

void gerar_ListaPaiseslista(listaPaises **listaTotal_Paises){
	FILE *ptrArquivo = fopen("perguntas_Paises.txt", "r");
	if(ptrArquivo == NULL) exit(EXIT_FAILURE);

	char nomePais[50] = {'\0'};
	unsigned short codPais;
	while(fscanf(ptrArquivo, "%d %[^\n]s", &codPais, nomePais) != EOF){
		if(codPais % 2){
			listaPaises *elemento = criarElemento(nomePais, codPais);
			encadear_listaPaises(listaTotal_Paises, elemento);
		}
	}
	fclose(ptrArquivo);
}//FIM function

Arvore *criar_Raizes(Arvore *raiz){
     char infoRaiz[99] = {'\0'};
     int codArvore;

     FILE *ptrArquivo = fopen("perguntas_Paises.txt", "r");
     if(ptrArquivo == NULL)
        exit(EXIT_FAILURE);

     while(fscanf(ptrArquivo, "%d %[^\n]s", &codArvore, infoRaiz) != EOF)
          raiz = gerar_Arvore(raiz, infoRaiz, codArvore);

     fclose(ptrArquivo);
     return (raiz);
     }

Arvore *gerar_Arvore(Arvore *raiz, char infoRaiz[], int codArvore){
    if(!raiz){
        raiz = (Arvore*)malloc(sizeof(Arvore));
        raiz->casoSim = NULL;
        raiz->casoNao = NULL;
        raiz->cod = codArvore;
        strcpy(raiz->info,infoRaiz);
    }
    else{
        if(raiz->cod < codArvore)
            raiz->casoSim = gerar_Arvore(raiz->casoSim, infoRaiz, codArvore);
        else
            raiz->casoNao = gerar_Arvore(raiz->casoNao, infoRaiz, codArvore);
    }
    return (raiz);
}//FIM function

int buscaPais(Arvore *raiz){
	if(!raiz->casoSim){
		printf("O pais selecionado para voce eh: [%s]\n",raiz->info);
		system("pause");
		system("cls");
		return raiz->cod;
	}
	char opcao;
	printf("%s\n", raiz->info);
	do{
		printf("\n(s)Sim;\t(n)Nao;\nInforme uma opcao: \n");
		scanf(" %c", &opcao);
		system("cls");
		if(opcao == 's')
			return buscaPais(raiz->casoSim);
		else if(opcao == 'n')
			return buscaPais(raiz->casoNao);
	}while(opcao != 'n' && opcao != 's');
}//FIM funcrion

void printEmOrdem(Arvore *raiz){
    //Percorre a arvore atÃ© o ultimo no a esquerda, depois printa esse no e percorre todos os seus nos a direta,
    //repetindo esse movimento para os nos a esquerda, anteriores
    if(!raiz)
        return;
    printEmOrdem(raiz->casoNao);
    printf("[%s]\t[%d]\n", raiz->info, raiz->cod);
    printEmOrdem(raiz->casoSim);
}

void listarPaises(listaPaises *listaTotal_Paises){
	short somador = 1;
	for(listaPaises *nodoAux = listaTotal_Paises; nodoAux != NULL; nodoAux = nodoAux->next)
        printf("%d -- %s\n", somador++, nodoAux->nome);
}//FIM function

void encadearClientes(listaPaises **listaTotal_Paises, listaClientes cliente, int codPais){
	listaPaises *paisAtual = *listaTotal_Paises;
	while(paisAtual->cod != codPais)
		paisAtual = paisAtual->next;

	listaClientes *novoCliente = (listaClientes*)malloc(sizeof(listaClientes));
			strcpy(novoCliente->nome,cliente.nome);
			novoCliente->tipo = cliente.tipo;
			novoCliente->codPlano = cliente.codPlano;
			novoCliente->next = NULL;

	//PrimeiroCliente
	if(!(paisAtual->cliente))
		paisAtual->cliente = novoCliente;

	else{
		listaClientes *clienteAtual = paisAtual->cliente;
		while(clienteAtual->next)
			clienteAtual = clienteAtual->next;
		clienteAtual->next = novoCliente;
	}
}

int escolherDestino(int opInf){
	short codPais = 0;
	if(opInf == 1) codPais = 91;
	else if(opInf == 2) codPais = 89;
	else if(opInf == 3) codPais = 77;
	else if(opInf == 4) codPais = 75;
	else if(opInf == 5) codPais = 69;
	else if(opInf == 6) codPais = 67;
	else if(opInf == 7) codPais = 65;
	else if(opInf == 8) codPais = 63;
	else if(opInf == 9) codPais = 59;
	else if(opInf == 10) codPais = 57;
	else if(opInf == 11) codPais = 55;
	else if(opInf == 12) codPais = 53;
	else if(opInf == 13) codPais = 47;
	else if(opInf == 14) codPais = 45;
	else if(opInf == 15) codPais = 31;
	else if(opInf == 16) codPais = 29;
	return codPais;
}//FIM function

void listarEstrutura(listaPaises *listaTotal_Paises){
    listaClientes *listaTotal_Clientes;
    if(!listaTotal_Paises)
        printf("0xE004 - Nao ha nenhum pais cadastrado");
    while(listaTotal_Paises){
    		printf("\n");
            printf("[%s]",listaTotal_Paises->nome);
        if(listaTotal_Paises->cliente){
                listaTotal_Clientes = listaTotal_Paises->cliente;
        while(listaTotal_Clientes){
            printf("  [%s]",listaTotal_Clientes->nome);
          listaTotal_Clientes = listaTotal_Clientes->next;}
       }
        listaTotal_Paises = listaTotal_Paises->next;
    }
    return;
}

void paisesVisitados(listaPaises *listaTotal_Paises){
	system("cls");
	printf("======== LISTA DE PAISES VISITADOS =========\n\n");
	while(listaTotal_Paises != NULL){
		if(listaTotal_Paises->cliente != NULL)
			printf("[%s]\n", listaTotal_Paises->nome);
		listaTotal_Paises = listaTotal_Paises->next;
	}
}//FIM function

void paisesNaoVisitados(listaPaises *listaTotal_Paises){
	system("cls");
	printf("======== LISTA DE PAISES NAO VISITADOS =========\n\n");
	while(listaTotal_Paises != NULL){
		if(listaTotal_Paises->cliente == NULL)
			printf("[%s]\n", listaTotal_Paises->nome);
		listaTotal_Paises = listaTotal_Paises->next;
	}
}//FIM function

void clientesQueVisitaramUmPais(listaPaises *listaTotal_Paises, int cdPais){
	listaClientes *listaTotal_Clientes;
	while(listaTotal_Paises->cod != cdPais)
		listaTotal_Paises = listaTotal_Paises->next;

	if(listaTotal_Paises->cliente != NULL){
		listaTotal_Clientes = listaTotal_Paises->cliente;
		while(listaTotal_Clientes){
			printf("[%s]\n", listaTotal_Clientes->nome);
			listaTotal_Clientes = listaTotal_Clientes->next;
		}
	}else return;

}//

void paisesVisitadosPorDec_Ind(listaPaises *listaTotal_Paises, char tipoCliente){
	system("cls");
	printf("======== LISTA DE PAISES VISITADOS POR CLIENTE =========\n\n");
	while(listaTotal_Paises){
        if(listaTotal_Paises->cliente){
            if(existeClienteTipo(listaTotal_Paises->cliente, tipoCliente))
                printf("[%s]\n", listaTotal_Paises->nome);
        }
        listaTotal_Paises = listaTotal_Paises->next;
	}
}//

short existeClienteTipo(listaClientes *cliente, char tipoCliente){
    while(cliente){
        if(cliente->tipo == tipoCliente)
            return 1;
        cliente = cliente->next;
    }
    return 0;
}

int qtdVisitantesPorPlano(listaPaises *listaTotal_Paises, int tipoPlano, int codPais){
    int qtdClientes = 0;
    while(listaTotal_Paises && listaTotal_Paises->cod != codPais){
            listaTotal_Paises = listaTotal_Paises->next;
          }
    if(!listaTotal_Paises || !listaTotal_Paises->cliente){
        if(!listaTotal_Paises)
            printf("O PAIS INFORMADO NAO ESTA CONTIDO NA LISTA DE PAISES DA AGENCIA\n");
        return 0;
    }
    listaClientes *listaTotal_Clientes = listaTotal_Paises->cliente;
    while(listaTotal_Clientes){
        if(listaTotal_Clientes->codPlano == tipoPlano)
            qtdClientes++;
        listaTotal_Clientes = listaTotal_Clientes->next;
    }
    return qtdClientes;
}//END function

void paisMaisVisitados(listaPaises *listaTotal_Paises){
    int nVisitas;
    int maior_nVisitas = 0;
    int codPaisMaisVisitado;
    listaClientes *listaTotal_Clientes;
    listaPaises *paisMaisVisitado = listaTotal_Paises;
    while(listaTotal_Paises){
        nVisitas = 0;
        if(listaTotal_Paises->cliente){
           listaTotal_Clientes = listaTotal_Paises->cliente;
           while(listaTotal_Clientes){
            nVisitas++;
            listaTotal_Clientes = listaTotal_Clientes->next;
           }
        }
        if(maior_nVisitas < nVisitas){
            maior_nVisitas = nVisitas;
            codPaisMaisVisitado = listaTotal_Paises->cod;
        }
        listaTotal_Paises = listaTotal_Paises->next;
    }
    while(paisMaisVisitado->cod != codPaisMaisVisitado)
        paisMaisVisitado = paisMaisVisitado->next;
    printf(" O PAIS MAIS VISITADO FOI - [%s]\n", paisMaisVisitado->nome);
}//END function

void menuAgencia(){
	system("cls");
	printf("=================== ASSUNCAO TURISMOS ==================\n\n");
	printf("1-> CADASTRAR NOVO CLIENTE\n");
	printf("2-> RELATORIOS DA AGENCIA\n");
	printf("0-> SAIR DO PROGRAMA\n");
	printf("\n========================================================\n\n");
}//END function

void menuRelatorios(){
	system("cls");
	printf("======================= RELATORIOS ======================\n\n");
	printf("1-> PAISES DISPONIVEIS\n");
	printf("2-> PAISES VISITADOS POR CLIENTES DECIDIDOS OU INDECISOS\n");
	printf("3-> PAISES VISITADOS\n");
	printf("4-> PAISES QUE AINDA NAO FORAM VISITADOS\n");
	printf("5-> LISTAGEM DE CLIENTES DADO UM DETERMINADO PAIS\n");
	printf("6-> PAIS MAIS VISITADO\n");
    printf("7-> VISITANTES DO PAIS POR PLANO CONTRATUAL\n");
	printf("\n========================================================\n\n");
}//END function


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>

typedef struct clienteLoja {
	int id;
	char *nome;
	char *endereco;
	char *telefone;
	float saldoDevedor;
}clienteLoja; 

typedef struct produtoLoja{
	char *nome;
	int codigo;
	float preco;
}produtoLoja;

struct vendas{
	int idCliente;
	int codigoProduto;
	int quantidadeProdutos;
};

typedef struct vendas vendas;
typedef struct tm tempo;

void menu ();
void cadastraCliente();
void cadastraProduto();
void alteraProduto();
void listarTodosClientes();
void listarClientesDevendo();
int contaLinhaCliente();
int contaLinhaProduto();
void venderFiado (vendas *v, tempo *t);
void fechaCaixa(vendas *v, tempo *t);
void listarVendas();
	
main (){
	
	vendas *v;
	v = calloc (100, 3*sizeof(int));
	
    tempo *t;
    t = calloc (100, 9*sizeof(int));
	
	setlocale(LC_ALL, "Portuguese");
	system("color f0");
	
	while (1){
		
		int opcao;
		
		printf ("-- -- -- CAIXA -- -- -- \n");
		printf ("Digite 1 para cadastrar clientes \n");
		printf ("Digite 2 para cadastrar produtos \n");
		printf ("Digite 3 para pagamento de clientes \n");
		printf ("Digite 4 para alterar produtos \n");
		printf ("Digite 5 para efetuar vendas \n");
		printf ("Digite 6 para listar todos os clientes \n");
		printf ("Digite 7 para listar clientes devendo \n");
		printf ("Digite 8 para listar vendas \n");
		printf ("Digite 9 para fechar o caixa \n");
		scanf ("%d", &opcao);
		
		switch (opcao){
		
			case 1:
				cadastraCliente();
				break;
			
			case 2:
				cadastraProduto();
				break;
			
			case 3:
				//clientePaga();
				break;
			
			case 4:
				//alteraProduto();
				break;
			
			case 5:
				venderFiado(v, t);
				break;
			
			case 6:
				listarTodosClientes();
				break;
			
			case 7:
				listarClientesDevendo();
				break;
			
			case 8:
				listarVendas();
				break;
			
			case 9:
				fechaCaixa(v, t);
				exit(0);
				break;
			
			default:
				system("cls");
				printf("\tOp��o Inv�lida \n\n");
				getch();
				break;		
	 
		system("pause>null");			
		}			
	}
}

void cadastraCliente(){
	
	clienteLoja cliente;   
    FILE *arq;
	
	cliente.id = 1+contaLinhaCliente();
    fflush(stdin);
    system("cls");
    cliente.nome = malloc(sizeof(25));
    printf("\tInsira o nome do cliente\n\n");
    gets(cliente.nome);
    fflush(stdin);
    cliente.endereco = malloc(sizeof(50));
    printf("\tInsira o endere�o do cliente\n\n");
    gets(cliente.endereco);
    fflush(stdin);
    cliente.telefone = malloc(sizeof(15));
    printf("\tInsira o telefone do cliente \n\n");
    gets(cliente.telefone);
    fflush(stdin);
    cliente.saldoDevedor = 0.0;
    
    arq = fopen("Clientes.txt","a");
	fprintf(arq,"%d;%s;%s;%s;%.2f;\n", cliente.id, cliente.nome, cliente.endereco, cliente.telefone, cliente.saldoDevedor);   
	fclose(arq);
    getch();
    system ("cls");
}


void cadastraProduto(){
	
	produtoLoja produto;
	FILE *arq;
	
    system("cls");
    produto.codigo = 1+contaLinhaProduto();
    fflush(stdin);
    produto.nome = malloc(sizeof(30));
    printf("\tInsira o nome do Produto\n\n");
    gets(produto.nome);
    fflush(stdin);
    printf("\tInsira o pre�o do Produto\n\n");
    scanf("%f",&produto.preco);
    fflush(stdin);
    getch();
           
    arq = fopen("Produtos.txt","a");  
	fprintf(arq, "%d;%s;%.2f;\n", produto.codigo, produto.nome, produto.preco);
	fclose(arq);
	getch();
	system("cls");
}

int contaLinhaCliente(){
	
	char ch;
	int linha=0;
	FILE *arq;
	
	arq = fopen("Clientes.txt", "r");
	if(arq == NULL)
		return linha;
	else
		while( (ch=fgetc(arq))!= EOF ){
			if(ch == '\n'){
				linha++;
		    }			
     	}
    return linha;
	fclose(arq);
}

int contaLinhaProduto(){
	
	char ch;
	int linha=0;
	FILE *arq;
	
	arq = fopen("Produtos.txt", "r");
	if(arq == NULL)
		return linha;
	else
		while( (ch=fgetc(arq))!= EOF ){
			if(ch == '\n'){
				linha++; 
		    }			
     	}
    return linha;
	fclose(arq);
}

void listarTodosClientes(){
	
	int id, i = 0, numero;
	char nome[30], endereco[50], telefone[20];
	float divida;
	FILE *arq;
	
	arq = fopen("Clientes.txt", "r");
	if(arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		system("cls");
	    numero = contaLinhaCliente();
    	while (i < numero){
			fscanf(arq, "%d; %[^;]; %[^;]; %[^;]; %f;" , &id, nome, endereco, telefone, &divida);	
			printf ("ID:%d  Nome:%s  Endereco:%s  Telefone:%s  D�vida:%.2f \n", id, nome, endereco, telefone, divida);
			i++;                          
		}
    }
    getch();
    system("cls");
}

void listarClientesDevendo(){
	
	char nome[50];
	float divida;
	int numero, i = 0, id;
	FILE *arq;
	
	arq = fopen("Clientes.txt", "r");
	if(arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
		system ("cls");
		numero = contaLinhaCliente();
    	while (i < numero){
			fscanf(arq, "%d; %[^;]; %*[^;]; %*[^;]; %f;" , &id, nome, &divida);	
			if(divida > 0)
			    printf("ID:%d  Nome:%s  D�vida:%.2f\n", id, nome, divida);
			i++;	    
		}
    }
	fclose (arq);
	getch();
	system ("cls");
}

void venderFiado (vendas *v, tempo *t){
	
	int i, contador = 0, idCliente, codigoProduto, quantidadeProdutos, linhasCliente, linhasProduto;
	
	system ("cls");
	
	for (i = 0; i < 100; i++){	
		if (v[i].codigoProduto != 0 || v[i].quantidadeProdutos != 0){
			contador++;
		}
	}
	linhasCliente = contaLinhaCliente();
	linhasProduto = contaLinhaProduto();
	
	printf ("Informe o ID do Cliente \n");
	scanf ("%d", &idCliente);
	if (idCliente > linhasCliente || idCliente <= 0){
		printf ("Cliente n�o cadastrado em nosso sistema \n");
	}else{
		printf ("Informe o C�digo do Produto \n");
		scanf ("%d", &codigoProduto);
		if (codigoProduto > linhasProduto || codigoProduto <= 0){
			printf ("Produto n�o cadastrado em nosso sistema \n");	
		}else{
	    	printf ("Informe a quantidade de Produtos \n");
			scanf ("%d", &quantidadeProdutos);
			if (quantidadeProdutos < 1){
				printf ("Quantidade inv�lida! \n");
			}else {
				v[contador].idCliente = idCliente;
				v[contador].codigoProduto = codigoProduto;
				v[contador].quantidadeProdutos = quantidadeProdutos;
				printf ("Venda cadastrada com sucesso! \n");
				time_t now = time(NULL);
				t = localtime(&now);
			}	
		}
	}
	getch();
	system ("cls");	
}

void fechaCaixa (vendas *v, *t){
	
	FILE * arq;
	char string[100];
	
	arq = fopen("arqBinario.bin","wb");
    
    snprintf (string, 100,"%d %d %d %.2d/%.2d/%d", v[0].idCliente, v[0].codigoProduto,
			 v[0].quantidadeProdutos, t[0]->tm_mday, t->tm_mon+1, t->tm_year+1900);
    
    printf ("%s", string);
	fwrite (string, 100, 8, arq);
	fclose (arq);
}

void listarVendas (){
	
	FILE * arq;
	char string[100];
	
	arq = fopen("arqBinario.bin","rb");
	fread(string, 100, 6,  arq);
	
	fclose (arq);
}

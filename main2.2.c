#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

void menu ();
void cadastraCliente();
void cadastraProduto();
void alteraProduto();
void listarTodosClientes();
void listarClientesDevendo();
int lerIdCliente ();
int lerCodigoProduto ();
int contaLinhaCliente();
int contaLinhaProduto();

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
	
main (){
	
	setlocale(LC_ALL, "Portuguese");
    system("color f0");
	
	menu();
 
	system("pause>null");			
}

void menu (){
		
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
			//efetuaVenda();
			break;
			
		case 6:
			listarTodosClientes();
			break;
		
		case 7:
			listarClientesDevendo();
			break;
		
		case 8:
			//listarVendas();
			break;
			
		case 9:
			exit(1);
			break;
		
		default:
			system("cls");
		    printf("\tOpção Inválida \n\n");
		    getch();
		    system("cls");
			menu();
			break;		
	}
}	
	
void cadastraCliente(){
	
	clienteLoja cliente;   
    FILE *arq;
	
	cliente.id = 1+lerIdCliente();
    fflush(stdin);
    system("cls");
    cliente.nome = malloc(sizeof(25));
    printf("\tInsira o nome do cliente\n\n");
    gets(cliente.nome);
    fflush(stdin);
    cliente.endereco = malloc(sizeof(50));
    printf("\tInsira o endereço do cliente\n\n");
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
    menu();
}


void cadastraProduto(){
	
	produtoLoja produto;
	FILE *arq;
	
    system("cls");
    produto.codigo = 1+lerCodigoProduto();
    fflush(stdin);
    produto.nome = malloc(sizeof(30));
    printf("\tInsira o nome do Produto\n\n");
    gets(produto.nome);
    fflush(stdin);
    printf("\tInsira o preço do Produto\n\n");
    scanf("%f",&produto.preco);
    fflush(stdin);
    getch();
           
    arq = fopen("Produtos.txt","a");  
	fprintf(arq, "%d;%s;%.2f;\n", produto.codigo, produto.nome, produto.preco);
	fclose(arq);
	getch();
	system("cls");
    menu();
}

int lerIdCliente (){

	FILE *arq;
	int i, numero, idCliente = 0;
           
    arq = fopen("Clientes.txt","r");
    
    if(arq == NULL){
		return idCliente;
	}       
	else{
		numero = contaLinhaCliente();
    	for (i = 0; i < numero; i++){
    		fscanf (arq,"%d;%*s", &idCliente);
    		}		
	}
	fclose(arq);
	return (int)idCliente;
}

int lerCodigoProduto (){

	FILE *arq;
	int i, numero, codigoProduto = 0;
           
    arq = fopen("Produtos.txt","r");
    
    if(arq == NULL){
		return codigoProduto;
	}       
	else{
		numero = contaLinhaProduto();
    	for (i = 0; i < numero; i++){
    		fscanf (arq,"%d;%*s", &codigoProduto);
    		}		
	}
	fclose(arq);
	return (int)codigoProduto;
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
	char nome[50], *endereco, telefone[20], string[1000];
	float divida;
	FILE *arq;
	
	arq = fopen("Clientes.txt", "r");
	if(arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		system("cls");
	    numero = contaLinhaCliente();
    	while (i < numero){
			fscanf(arq, "%d;%s" , &id, string);
			endereco = malloc (sizeof(string));
			sscanf (string,"%[^;]; %[^;]; %[^;]; %f", nome, endereco, telefone, &divida);
			printf ("ID:%d  Nome:%s  Endereco:%s  Telefone:%s  Dívida:%.2f \n", id, nome, endereco, telefone, divida);
			i++;
		}
    }
    getch();
    system("cls");
	menu();
}

void listarClientesDevendo(){
	
	char string [1000], nome[50];
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
			fscanf(arq, "%d;%s" , &id, string);	
			sscanf (string,"%[^;]; %*[^;]; %*[^;]; %f", nome, &divida);
			if(divida > 0)
			    printf("ID:%d  Nome:%s  Dívida:%.2f\n", id, nome, divida);
			i++;	    
		}
    }
	fclose (arq);
	getch();
	system ("cls");
	menu();
}

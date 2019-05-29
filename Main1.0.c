#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

void menu ();
void cadastraCliente();
void cadastraProduto();
void alteraProduto();
int lerIdCliente ();


typedef struct clienteLoja {
	int id;
	char *nome;
	char *endereco;
	char *telefone;
	float saldoDevedor;
}clienteLoja; 
	
	
main (){
	
	setlocale(LC_ALL, "Portuguese");
    system("color f0");
	
	menu();
 
	system("pause>null");			
}

void menu (){
		
	int opcao;
	
	printf ("Digite 1 para cadastrar clientes \n");
	printf ("Digite 2 para cadastrar produtos \n");
	printf ("Digite 3 para pagamento de clientes \n");
	printf ("Digite 4 para alterar produtos \n");
	printf ("Digite 5 para efetuar vendas \n");
	printf ("Digite 6 para listar clientes \n");
	printf ("Digite 7 para listar vendas \n");
	printf ("Digite 8 para fechar o caixa \n");
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
			//listarCliente();
			break;
		
		case 7:
			//listarVendas();
			break;
		
		case 8:
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
    
    FILE *arq;
           
    arq = fopen("Clientes.txt","a");
           
    if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		getch();
	}       
	else{
    	fprintf(arq, "%d;%s;%s;%s;%.2f;\n", cliente.id, cliente.nome, cliente.endereco, cliente.telefone, cliente.saldoDevedor);
	}     
	
	fclose(arq);
    getch();
    system ("cls");
    menu();
}


void cadastraProduto(){
	
	typedef struct produtoLoja{
		char *nome;
		int codigo;
		float preco;
	} produtoLoja;
	
	produtoLoja produto;
	
    system("cls");
    fflush(stdin);
    produto.nome = malloc(sizeof(30));
    printf("\tInsira o nome do Produto\n\n");
    gets(produto.nome);
    fflush(stdin);
    printf("\tInsira o codigo do Produto\n\n");
    scanf("%d",&produto.codigo);
    fflush(stdin);
    printf("\tInsira o preço do Produto\n\n");
    scanf("%f",&produto.preco);
    fflush(stdin);
    getch();

    FILE *arq;
           
    arq = fopen("Produtos.txt","a");
           
    if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}       
	else{
    	fprintf(arq, "%s;"  "%d;"  "%.2f;", produto.nome, produto.codigo, produto.preco);
    	fprintf  (arq, "\n");
	}     
   		fclose(arq);
        menu();
}

int lerIdCliente (){
	
	char linha[50];
	char ch;
	FILE *arq;
	int i, numero, idCliente;
           
    arq = fopen("Clientes.txt","r");
    
    if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
	}       
	else{
		numero = contaLinha();
    		for (i = 0; i < numero; i++){
    			fscanf (arq,"%d;%*s", &idCliente);
    		}		
	}
	fclose(arq);
	return (int)idCliente;
}

int contaLinha(){
	
	char ch;
	int linha=0;
	FILE *arq;
	
	arq = fopen("Clientes.txt", "r");
	if(arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while( (ch=fgetc(arq))!= EOF ){
			if(ch == '\n'){
				linha++;
		    }			
     	}
    return (int)linha;
	fclose(arq);
}


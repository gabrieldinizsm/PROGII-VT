#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <string.h>

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

void menu ();
void cadastraCliente();
void cadastraProduto();
void alteraProduto();
void listarTodosClientes();
void listarClientesDevendo();
int contaLinhaCliente();
int contaLinhaProduto();
void venderFiado (vendas *v);
void fechaCaixa(vendas *v);
void listarVendas();
	
main (){
	
	vendas *v;
	v = calloc (100, 3*sizeof(int));
	
	setlocale(LC_ALL, "Portuguese");
	system("color f0");
	
	while (1){
		
		int opcao, idProduto;
		char novoPreco[10];
		
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
				/*printf ("Digite o ID do Produto a ser alterado \n");
				scanf ("%d", &idProduto);
				printf ("Digite o novo preço do Produto \n");
				scanf ("%s", novoPreco);
				editFile ("Produtos.txt",";",idProduto,2,novoPreco);*/
				alteraProduto();
				break;
			
			case 5:
				venderFiado(v);
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
				fechaCaixa(v);
				exit(0);
				break;
			
			default:
				system("cls");
				printf("\tOpção Inválida \n\n");
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
    printf("\tInsira o preço do Produto\n\n");
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
		while((ch=fgetc(arq))!= EOF ){
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
		while((ch=fgetc(arq))!= EOF ){
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
			printf ("ID:%d  Nome:%s  Endereco:%s  Telefone:%s  Dívida:%.2f \n", id, nome, endereco, telefone, divida);
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
			    printf("ID:%d  Nome:%s  Dívida:%.2f\n", id, nome, divida);
			i++;	    
		}
    }
	fclose (arq);
	getch();
	system ("cls");
}

void venderFiado (vendas *v){
	
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
		printf ("Cliente não cadastrado em nosso sistema \n");
	}else{
		printf ("Informe o Código do Produto \n");
		scanf ("%d", &codigoProduto);
		if (codigoProduto > linhasProduto || codigoProduto <= 0){
			printf ("Produto não cadastrado em nosso sistema \n");	
		}else{
	    	printf ("Informe a quantidade de Produtos \n");
			scanf ("%d", &quantidadeProdutos);
			if (quantidadeProdutos < 1){
				printf ("Quantidade inválida! \n");
			}else{
				v[contador].idCliente = idCliente;
				v[contador].codigoProduto = codigoProduto;
				v[contador].quantidadeProdutos = quantidadeProdutos;
				printf ("Venda cadastrada com sucesso! \n");
			}	
		}
	}
	getch();
	system ("cls");	
}

void fechaCaixa (vendas *v){
	
	FILE * arq;
	char string[100];
	int i;
	
	time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    //string = malloc (3*sizeof(v));
	
	arq = fopen("arqBinario.bin","ab");
    
    for (i = 0; i < 100; i++){
    	if (v[i].codigoProduto == 0 || v[i].quantidadeProdutos == 0){
    		fclose (arq);
    		break;
		}
    	snprintf (string, 3*sizeof(v),"%d %d %d %.2d/%.2d/%d", v[i].idCliente, v[i].codigoProduto,
				 v[i].quantidadeProdutos, t->tm_mday, t->tm_mon+1, t->tm_year+1900);
   		printf ("%s \n", string);
		fwrite (string, sizeof(string), 1, arq);
	}
	fclose (arq);
	free (v);
}

void listarVendas (){
	
	FILE * arq;
    char string[100];
	int i;

	arq = fopen("arqBinario.bin","rb");
	while (!feof(arq)){
		fread(string, 100, 1, arq);
		printf ("%s \n", string);
	}
	getch();
	fclose (arq);
	system ("cls");
}

int editFile(char path[],char delim[],int id,int pos, char newVal[]){
	
  const int MAX_ID = 10;
  const int MAX_BUFFER = 500;
  char res[MAX_BUFFER];
  int foundId = 0;
  int err=0;

  FILE *fp;
  fp = fopen(path,"r");
  if(fp==NULL){
    printf("erro de acesso ao arquivo \"%s\" : ",path);
    printf("%s\n", strerror(errno));
    return 0;
  }
  FILE *ftemp;
  char tempPath[MAX_BUFFER];
  strcpy(tempPath,path);
  strcat(tempPath,".tmp");
  ftemp = fopen(tempPath,"w");
  if(fp==NULL){
    printf("Erro de criação de arquivo temporário\n");
    printf("%s\n", strerror(errno));
    return 0;
  }

  while(fgets(res,MAX_BUFFER,fp)!=NULL){
    int i=0;
    int found = 0;
    char str[MAX_BUFFER];
    char *tempstr = calloc(MAX_BUFFER+1, sizeof(char));
    char *basestr = calloc(MAX_BUFFER+1, sizeof(char));
    strcpy(basestr,res);

    // o primeiro token é o ID
    char *token = strtok(basestr, delim);

    if(strtol(token,NULL,MAX_ID) == id){
      foundId = 1;

      while(token != NULL) {
        // se não chegou na posição correta, use o valor antigo
        if(i!=pos){ 
          strcat(tempstr,token);     
        }else{ // se chegou, salve o novo valor
          strcat(tempstr,newVal);  
          found = 1;
        }
        i++;
        token = strtok(NULL, delim);
        // adicionar delimitador entre os valores
        if(token) strcat(tempstr,delim);
      }

      if(!found){
        printf("posicao %d nao encontrada no id %d\n",pos,id);
        err=1;
      }
    }
    
    // salva valores no arquivo temporário
    if(found)
      fputs(tempstr,ftemp);
    else
      fputs(res,ftemp);
  }
  if(!foundId){
    printf("id: %d não encontrado\n",id);
    err = 1;
  }
  fclose(fp);
  fclose(ftemp);

  if (!err){
    int ret = remove(path);
    printf ("%d \n", ret);
    if(ret !=0){
      printf("erro ao deletar o arquivo \"%s\" : ",path);
      printf("%s\n", strerror(errno));
      err = 1;
    }
    rename(tempPath, path);
    return 1;
 }else{
    remove(tempPath);
    return 0;
  }
}

void alteraProduto (){
	
	int idProduto, linhaProduto, produtoAlterado;
	char novoPreco[10];
	
	printf ("Digite o ID do Produto a ser alterado \n");
	scanf ("%d", &idProduto);
	linhaProduto = contaLinhaProduto();
	if (idProduto > linhaProduto || idProduto <= 0){
		printf ("ID inválido ou não cadastrado em nossa base \n");
	}else{
		printf ("Digite o novo preço do Produto \n");
		scanf ("%s", novoPreco);
		produtoAlterado = editFile ("Produtos.txt",";",idProduto,2,novoPreco);
		if (produtoAlterado == 1){
			printf ("Produto alterado com sucesso \n");
		}else{
			printf ("Houve um erro nessa transação, tente novamente mais tarde \n");
		}
	}
	getch();
	system ("cls");
}

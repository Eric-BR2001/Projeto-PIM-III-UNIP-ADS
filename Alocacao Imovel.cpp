#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


FILE* AbreArquivo(char modo, char caminho[30]){
    FILE *arquivo;
    switch(modo){
        case 'g':
            arquivo = fopen(caminho,"wt");
            break;
        case 'l':
            arquivo = fopen(caminho,"rt");
            break;
        case 'a':
            arquivo = fopen(caminho,"a");
            break;
    }
    if(arquivo==NULL){     
        printf("Nao foi possivel abrir o arquivo");
        exit(0);
    }
    return arquivo;
}

void FecharArquivo(FILE *arquivo){
    fclose(arquivo);
}

void SubstUnderline(char valorsubst[100]){
          int aux;
          for(aux = 0; aux < strlen(valorsubst); aux++) {
                if(valorsubst[aux] == '_') {
                       valorsubst[aux] = ' ';
                }
           }
}

void SubstEspaco(char valorsubst[100]){
          int aux;
          for(aux = 0; aux < strlen(valorsubst); aux++) {
                if(valorsubst[aux] == ' ') {
                       valorsubst[aux] = '_';
                }
           } 
}


void sair(){
    printf("\n\n ########## OBRIGADO. TENHA UM BOM DIA ##########\n\n");
}




void CadastrarClientes(int idcliente, char nome[30], char rg[15], char cpf[15], char endereco[100], char datanascimento[15]){
    FILE *arquivo;
    arquivo = AbreArquivo('a', "clientes.txt");
    fprintf(arquivo, "\n%d %s %s %s %s %s", idcliente, nome, rg, cpf, endereco, datanascimento);
    FecharArquivo(arquivo);
}

void ListarClientes(){
    FILE *arquivo; int idcliente; char nome[30]; char rg[15]; char cpf[15]; char endereco[100]; char datanascimento[15];
 
    arquivo = AbreArquivo('l',"clientes.txt");
    printf("\n\t Codigo :: Nome :: Rg :: CPF :: Endereco :: Data de Nascimento \n");

    while(!feof(arquivo)){
        fscanf(arquivo,"%d %s %s %s %s %s %s", &idcliente, &nome, &rg, &cpf, &endereco, &datanascimento);
        SubstUnderline(nome);SubstUnderline(rg);SubstUnderline(cpf);
        SubstUnderline(endereco);SubstUnderline(datanascimento);
        printf("\n\t  %d :: %s :: %s :: %s :: %s :: %s \n", idcliente, nome, rg, cpf, endereco, datanascimento);
    }
    FecharArquivo(arquivo);
}

void SelecaoClientesMovimentacao(){
    FILE *arquivo; int idcliente; char nome[30]; char rg[15]; char cpf[15]; char endereco[100]; char datanascimento[15];
 
    arquivo = AbreArquivo('l',"clientes.txt");
    printf("\n\t Codigo :: Nome :: CPF \n");

    while(!feof(arquivo)){
        fscanf(arquivo,"%d %s %s %s %s %s", &idcliente, &nome, &rg, &cpf, &endereco, &datanascimento);
        SubstUnderline(nome);SubstUnderline(rg);SubstUnderline(cpf);
        SubstUnderline(endereco);SubstUnderline(datanascimento);
        printf("\n\t  %d :: %s :: %s \n", idcliente, nome, cpf);
    }
    FecharArquivo(arquivo);
}


void CadastrarImovel(int idImovel, char construtora[50], char modelo[50], char avaliacao[10], int idclassf){
    FILE *arquivo;
    arquivo = AbreArquivo('a', "imoveis.txt");
    fprintf(arquivo, "\n%d %s %s %s %d", idImovel, construtora, modelo, avaliacao, idclassf);
    FecharArquivo(arquivo);
}

void ListarImoveis(){
    FILE *arquivo; int idImovel; char construtora[50]; char modelo[50]; char avaliacao[10]; int idclassf;

    arquivo = AbreArquivo('l',"imoveis.txt");
    printf("\n\t Codigo :: Construtora :: Modelo :: Avaliacao :: Codigo de Classificacao\n");

    while(!feof(arquivo)){
        fscanf(arquivo,"%d %s %s %s %d", &idImovel, &construtora, &modelo, &avaliacao, &idclassf);
        SubstUnderline(construtora);SubstUnderline(modelo);SubstUnderline(avaliacao);
        printf("\n\t  %d :: %s :: %s :: %s :: %d\n", idImovel, construtora, modelo, avaliacao, idclassf);
    }
    FecharArquivo(arquivo);
}

void SelecaoImovelMovimentacao(){
    FILE *arquivo; FILE *arquivorel; int idImovel; char construtora[50]; char modelo[50]; char avaliacao[10]; 
    int idclassf; int idclassfRel1; char descclassf[300]; float preco;

    arquivo = AbreArquivo('l',"imoveis.txt");
    printf("\n\t Codigo :: Construtora :: Modelo :: Avaliacao :: Codigo de Classificacao\n");
    
    while(!feof(arquivo)){
        fscanf(arquivo,"%d %s %s %s %d", &idImovel, &construtora, &modelo, &avaliacao, &idclassf);
        SubstUnderline(construtora);SubstUnderline(modelo);SubstUnderline(avaliacao);
        printf("\n\t  %d :: %s :: %s :: %s :: %d\n", idImovel, construtora, modelo, avaliacao, idclassf);
        arquivorel = AbreArquivo('l',"classificacaoimoveis.txt");
        while(!feof(arquivorel)){
            fscanf(arquivorel,"%d %s %f", &idclassfRel1, &descclassf, &preco);
            if(idclassfRel1 == idclassf){
                              SubstUnderline(descclassf);
                              printf("\n\t\t  Desc.: %s :: Diaria de R$ %0.2f\n", descclassf, preco);
                            break;
             }                  
        }
        FecharArquivo(arquivorel);
    }
    FecharArquivo(arquivo);     
}




void CadastrarClassificacao(int idclassf, char descclassf[300], float preco){
    FILE *arquivo;
    arquivo = AbreArquivo('a', "classificacaoimoveis.txt");
    fprintf(arquivo, "\n%d %s %f", idclassf, descclassf, preco);
    FecharArquivo(arquivo);
}

void ListarClassificacao()
{
    FILE *arquivo; int idclassf; char descclassf[300]; float preco;

    arquivo = AbreArquivo('l',"classificacaoimoveis.txt");
    printf("\n\t Codigo :: Descricao :: Preco\n");

    while(!feof(arquivo)){
        fscanf(arquivo,"%d %s %f", &idclassf, &descclassf, &preco);
        SubstUnderline(descclassf);
        printf("\n\t  %d :: %s :: Diaria de R$ %0.2f\n", idclassf, descclassf, preco);
    }
    FecharArquivo(arquivo);
}



void CadastrarMovimentacao(int idlocacao, int idcliente, int idImovel, char dataretirada[15], char dataentrega[15], int diasalocado){
    FILE *arquivo;
    arquivo = AbreArquivo('a', "movimentacaolocacao.txt");
    fprintf(arquivo, "\n%d %d %d %s %s %d", idlocacao, idcliente, idImovel, dataretirada, dataentrega, diasalocado);
    FecharArquivo(arquivo);
}

void ListarMovimentacao()
{
    FILE *arquivo; FILE *arquivorelC; FILE *arquivorelV; FILE *arquivorelCl;
    int idlocacao; int idcliente; int idImovel; char dataretirada[15]; char dataentrega[15]; int diasalocado;

    int idclienteRel; int idImovelRel; int idclassfRel;

    char nome[30]; char rg[15]; char cpf[15]; char endereco[100]; char datanascimento[15];

    char construtora[50]; char modelo[50]; char avaliacao[10];

    int idclassf; char descclassf[300]; float preco;

    arquivo = AbreArquivo('l',"movimentacaolocacao.txt");
    printf("\n\t Codigo :: Retirada :: Entrega :: Dias Alocado :: Preco \n");
    
    while(!feof(arquivo)){
        fscanf(arquivo,"%d %d %d %s %s %d %f", &idlocacao, &idcliente, &idImovel, &dataretirada, &dataentrega, &diasalocado);
        SubstUnderline(dataretirada);SubstUnderline(dataentrega);
        printf("\n\t  %d :: %s :: %s :: %d Dias \n", idlocacao, dataretirada, dataentrega, diasalocado);
        
        arquivorelC = AbreArquivo('l',"clientes.txt");
        while(!feof(arquivorelC)){
                fscanf(arquivorelC,"%d %s %s %s %s %s %s", &idclienteRel, &nome, &rg, &cpf, &endereco, &datanascimento);
                if(idclienteRel == idcliente){
                              SubstUnderline(nome);SubstUnderline(cpf);
                              printf("\n\t\tCliente: %s - CPF: %s \n", nome, cpf);
                            break;
                }               
        }
        FecharArquivo(arquivorelC);
        

        arquivorelV = AbreArquivo('l',"imoveis.txt");
        while(!feof(arquivorelV)){
                fscanf(arquivorelV,"%d %s %s %s %d", &idImovelRel, &construtora, &modelo, &avaliacao, &idclassf);
                if(idImovelRel == idImovel){
                              SubstUnderline(construtora);SubstUnderline(modelo);SubstUnderline(avaliacao);
                              printf("\n\t\tImovel: %s %s %s\n", construtora, modelo, avaliacao);
                              break;
                }               
        }
        FecharArquivo(arquivorelV);

        arquivorelCl = AbreArquivo('l',"classificacaoimoveis.txt");
        while(!feof(arquivorelCl)){
                fscanf(arquivorelCl,"%d %s %f", &idclassfRel, &descclassf, &preco);
                if(idclassfRel == idclassf){
                              SubstUnderline(descclassf);
                              printf("\n\t\t%s Diaria de R$ %0.2f\n", descclassf, preco); 
                              break;
                }     
                
                
        SubstUnderline(descclassf);
                 
        }
        FecharArquivo(arquivorelCl);
        
     
        
    }
    FecharArquivo(arquivo); 
}

void BuscarMovimentacaoCliente(int idclienteBusca){
     
    FILE *arquivo; FILE *arquivorelC; FILE *arquivorelV; FILE *arquivorelCl;
    
    int idlocacao; int idcliente; int idImovel; char dataretirada[15]; char dataentrega[15]; int diasalocado; 

    int idclienteRel; int idImovelRel; int idclassfRel; 

    char nome[30]; char rg[15]; char cpf[15]; char endereco[100]; char datanascimento[15];

    char construtora[50]; char modelo[50]; char avaliacao[10];

    int idclassf; char descclassf[300]; float preco;
    float subtotal;
    float total = 0;

    arquivo = AbreArquivo('l',"movimentacaolocacao.txt");
    printf("\n\t Codigo :: Retirada :: Entrega :: Dias Alocado :: Preco \n");
    
    while(!feof(arquivo)){
         fscanf(arquivo,"%d %d %d %s %s %d", &idlocacao, &idcliente, &idImovel, &dataretirada, &dataentrega, &diasalocado);
         SubstUnderline(dataretirada);SubstUnderline(dataentrega);
         
         if(idclienteBusca == idcliente){
                                
                    printf("\n\t  %d :: %s :: %s :: %d Dias \n", idlocacao, dataretirada, dataentrega, diasalocado);
                    

                    arquivorelC = AbreArquivo('l',"clientes.txt");
                    while(!feof(arquivorelC)){
                            fscanf(arquivorelC,"%d %s %s %s %s %s %s", &idclienteRel, &nome, &rg, &cpf, &endereco, &datanascimento);
                            if(idclienteRel == idcliente){
                                          SubstUnderline(nome);SubstUnderline(cpf);
                                          printf("\n\t\tCliente: %s - CPF: %s \n", nome, cpf);
                                        break;
                            }               
                    }
                    FecharArquivo(arquivorelC);
                    

                    arquivorelV = AbreArquivo('l',"imoveis.txt");
                    while(!feof(arquivorelV)){
                            fscanf(arquivorelV,"%d %s %s %s %d", &idImovelRel, &construtora, &modelo, &avaliacao, &idclassf);
                            if(idImovelRel == idImovel){
                                          SubstUnderline(construtora);SubstUnderline(modelo);SubstUnderline(avaliacao);
                                          printf("\n\t\tImovel: %s %s %s\n", construtora, modelo, avaliacao);
                                          break;
                            }               
                    }
                    FecharArquivo(arquivorelV);
                    
                    arquivorelCl = AbreArquivo('l',"classificacaoimoveis.txt");
                    while(!feof(arquivorelCl)){
                            fscanf(arquivorelCl,"%d %s %f", &idclassfRel, &descclassf, &preco);
                            if(idclassfRel == idclassf){
                                          subtotal = (preco*diasalocado);
                                          total = total + subtotal; 
                                          SubstUnderline(descclassf);
                                          printf("\n\t\tDiaria de R$ %0.2f X %d dias = SubTotal R$ %0.2f\n", preco, diasalocado, subtotal); 
                                          break;
                            }     
                            
                            
                    SubstUnderline(descclassf);
                             
                    }
                    FecharArquivo(arquivorelCl);
        
        
        }
    }
    
    if(total > 0){
          printf("\n\n\t VALOR TOTAL DE LOCACAO R$ %0.2f ---------------------------------------------------------- \t\n\n", total);
    }else{
          
          printf("\n\t\t----- CLIENTE NAO POSSUI LOCACAO OU NAO ESTA CADASTRADO -----\t\t\n");
    }
    
    FecharArquivo(arquivo); 
}


int main()
{

    int idcliente; char nome[30]; char rg[15]; char cpf[15]; char endereco[100]; char datanascimento[15];
    

    int idclassf; char descclassf[300]; float preco;
    

    int idImovel; char construtora[50]; char modelo[50]; char avaliacao[10];
    

    int idlocacao; char dataretirada[15]; char dataentrega[15]; int diasalocado; 
    int idclienteBusca;
    int menuprimario;
    int menusecundario;
   
    do
    {
        system("cls || clear");
        printf("\n\n\t ########## MENU PRINCIPAL ##########\t\n\n");
        printf("\t-> 1 .::. Cadastro de Clientes\n");
        printf("\t-> 2 .::. Cadastro de Classificacao de Imoveis\n");
        printf("\t-> 3 .::. Cadastro de Imoveis\n");
        printf("\t-> 4 .::. Movimentacao de Locacao\n");
        printf("\t-> 0 .::. Sair\n");
                                              
        printf("\n\tDIGITE UM OPCAO: ");
        scanf("%d", &menuprimario);

        system("cls || clear");

        switch(menuprimario)
        {
            case 1:


			    do
    				{
                         system("cls || clear");
                         
                         printf("\n\n\t########## LISTA DE CLIENTES CADASTRADOS ########## \t\n\n");
           
                         ListarClientes();
                         
       				     printf("\n\n\t ########## LISTAGEM CONCLUIDA ##########\n\n");
                                     printf("\t-> 1 .::. Cadastrar Novo Cliente\n");
                                     printf("\t-> 0 .::. Voltar Menu Principal\n");
                                     printf("\n\tDIGITE UM OPCAO: ");
				                     scanf("%d", &menusecundario);

                     switch(menusecundario)
				     {
                       case 1:  
                                      printf("\n\n\t########## CADASTRO DE CLIENTES ########## \t\n\n");
                                              printf("\n\tDIGITE O CODIGO (so numeros sem espacos): ");
                                              scanf("%d", &idcliente);
                                              fflush(stdin);
                                              
                                              printf("\n\tDIGITE O NOME: ");
                                              fgets(nome,30,stdin);
                                              nome[strlen(nome) - 1] = '\0';
                                              SubstEspaco(nome);
                                              
                                              printf("\n\tDIGITE O RG (so numeros sem espacos): ");
                                              fgets(rg,15,stdin);
                                              rg[strlen(rg) - 1] = '\0';
                                              SubstEspaco(rg);
                                              
                                              printf("\n\tDIGITE O CPF (so numeros sem espacos): ");
                                              fgets(cpf,15,stdin);
                                              cpf[strlen(cpf) - 1] = '\0';
                                              SubstEspaco(cpf);
                                              
                                              printf("\n\tDIGITE O ENDERECO: ");
                                              fgets(endereco,100,stdin);
                                              endereco[strlen(endereco) - 1] = '\0';
                                              SubstEspaco(endereco);
                                              
                                              printf("\n\tDIGITE A DATA DE NASCIMENTO (formato dia/mes/ano): ");
                                              scanf("%s", &datanascimento);
                                              SubstEspaco(datanascimento);
                                              fflush(stdin);
                                              
                                              
                                              CadastrarClientes(idcliente, nome, rg, cpf, endereco, datanascimento);
                                              printf("\n\n\t########## SUCESSO ########## \t\n\n");
                                              system("pause");
					case 0:
                                break;
					default:
                			    system("cls || clear");
                                printf("\n\n\t ########## OPCAO INVALIDA. TENTE NOVAMENTE ##########\t\n\n");
                                system("pause");

				     }
				
				}while(menusecundario != 0);

                break;


            case 2:

    
    			    do
        				{
                             system("cls || clear");
                             
                             printf("\n\n\t########## LISTA DE CLASSIFICACAO DE IMOVEIS ########## \t\n\n");
               
                             ListarClassificacao();
                             
           				     printf("\n\n\t ########## LISTAGEM CONCLUIDA ##########\n\n");
                                         printf("\t-> 1 .::. Cadastrar Nova Classificacao\n");
                                         printf("\t-> 0 .::. Voltar Menu Principal\n");
                                         printf("\n\tDIGITE UM OPCAO: ");
    				                     scanf("%d", &menusecundario);
    
                         switch(menusecundario)
    				     {
                           case 1:      
                                          printf("\n\n\t########## CADASTRO CLASSIFICACAO DE IMOVEIS ########## \t\n\n");
                                                  printf("\n\tDIGITE O CODIGO (so numeros sem espacos): ");
                                                  scanf("%d", &idclassf);
                                                  fflush(stdin);
                                                  
                                                  printf("\n\tDIGITE A DESCRICAO: ");
                                                  fgets(descclassf,300,stdin);
                                                  descclassf[strlen(descclassf) - 1] = '\0';
                                                  SubstEspaco(descclassf);
                                                  
                                                  printf("\n\tDIGITE O PRECO: ");
                                                  scanf("%f", &preco);
                                                  fflush(stdin);
                                                  
                                                  CadastrarClassificacao(idclassf, descclassf, preco);
                                                  printf("\n\n\t########## SUCESSO ########## \t\n\n");
                                                  system("pause");
                                                  
                                                  	
    
    					case 0:
                                break;
    					default:   
                			    system("cls || clear");
                                printf("\n\n\t ########## OPCAO INVALIDA. TENTE NOVAMENTE ##########\t\n\n");
                                system("pause");
    
    				     }
    				
    				}while(menusecundario != 0);
    
                    break;



            case 3:

    
    			    do
        				{
                             system("cls || clear");
                             
                             printf("\n\n\t########## LISTA DE IMOVEIS CADASTRADOS ########## \t\n\n");
               
                             ListarImoveis();
                             
           				     printf("\n\n\t ########## LISTAGEM CONCLUIDA ##########\n\n");
                                         printf("\t-> 1 .::. Cadastrar Novo Imovel\n");
                                         printf("\t-> 0 .::. Voltar Menu Principal\n");
                                         printf("\n\tDIGITE UM OPCAO: ");
    				                     scanf("%d", &menusecundario);
    
                         switch(menusecundario)
    				     {
                           case 1: 
    
                                          printf("\n\n\t########## CADASTRO DE IMOVEIS ########## \t\n\n");
                                                  printf("\n\tDIGITE O CODIGO (so numeros sem espacos): ");
                                                  scanf("%d", &idImovel);
                                                  fflush(stdin);
                                                  
                                                  printf("\n\tDIGITE A CONSTRUTORA: ");
                                                  fgets(construtora,50,stdin);
                                                  construtora[strlen(construtora) - 1] = '\0';
                                                  SubstEspaco(construtora);
                                                  
                                                  printf("\n\tDIGITE O MODELO: ");
                                                  fgets(modelo,50,stdin);
                                                  modelo[strlen(modelo) - 1] = '\0';
                                                  SubstEspaco(modelo);
                                                  
                                                  printf("\n\tDIGITE A AVALIACAO DA CASA(1-10): ");
                                                  fgets(avaliacao,6,stdin);
                                                  avaliacao[strlen(avaliacao) - 1] = '\0';
                                                  SubstEspaco(avaliacao);
                                                  
                                                  printf("\n\n\t----- CLASSIFICACOES CADASTRADAS NO SISTEMA -----");
                                                  ListarClassificacao();
                                                  printf("\n\t----- USE OS CODIGOS ACIMA PARA INFORMAR ABAIXO -----\t\n");
                                                  
                                                  printf("\n\tDIGITE O CODIGO DE CLASSIFICACAO: ");
                                                  scanf("%d", &idclassf);
                                                  fflush(stdin);
                                                  
                                                  CadastrarImovel(idImovel, construtora, modelo, avaliacao, idclassf);
                                                  printf("\n\n\t########## SUCESSO ########## \t\n\n");
                                                  system("pause");
                                                  
                                                  	
    
    					case 0:
                                break;
    					default:
                			    system("cls || clear");
                                printf("\n\n\t ########## OPCAO INVALIDA. TENTE NOVAMENTE ##########\t\n\n");
                                system("pause");
    
    				     }
    				
    				}while(menusecundario != 0);
    
                    break;

	        case 4:


			    do
    				{
                         system("cls || clear");
                         
                         printf("\n\n\t########## LISTA DE LOCACOES ########## \t\n\n");
           
                         ListarMovimentacao();
                         
       				     printf("\n\n\t ########## LISTAGEM CONCLUIDA ##########\n\n");
                                     printf("\t-> 1 .::. Cadastrar Nova Locacao\n");
                                     printf("\t-> 2 .::. Buscar Locacoes por Cliente\n");
                                     printf("\t-> 0 .::. Voltar Menu Principal\n");
                                     printf("\n\tDIGITE UM OPCAO: ");
				                     scanf("%d", &menusecundario);

                     switch(menusecundario)
				     {
                       case 2:
                                     system("cls || clear");
                                     printf("\n\n\t########## BUSCAR LOCACOES POR CLIENTE ########## \t\n\n");
                                              
                                              printf("\n\n\t----- CLIENTES CADASTRADOS NO SISTEMA -----");
                                              SelecaoClientesMovimentacao();
                                              printf("\n\t----- USE OS CODIGOS ACIMA PARA INFORMAR ABAIXO -----\t\n");
                                              printf("\n\tDIGITE O CODIGO DO CLIENTE: ");
                                              scanf("%d", &idclienteBusca);
                                              fflush(stdin);
                                                            
                                                            BuscarMovimentacaoCliente(idclienteBusca);
                                                            
                                              system("pause");
                                              break;
                                                           

                       
                       case 1:

                                      printf("\n\n\t########## CADASTRO DE LOCACOES ########## \t\n\n");
                                              printf("\n\tDIGITE O CODIGO (so numeros sem espacos): ");
                                              scanf("%d", &idlocacao);
                                              fflush(stdin);
                                              
                                              printf("\n\n\t----- CLIENTES CADASTRADOS NO SISTEMA -----");
                                                  SelecaoClientesMovimentacao();
                                              printf("\n\t----- USE OS CODIGOS ACIMA PARA INFORMAR ABAIXO -----\t\n");
                                              printf("\n\tDIGITE O CODIGO DO CLIENTE: ");
                                              scanf("%d", &idcliente);
                                              fflush(stdin);
                                              
                                              printf("\n\n\t----- IMOVEIS CADASTRADOS NO SISTEMA COM PRECO -----");
                                                  SelecaoImovelMovimentacao();
                                              printf("\n\t----- USE OS CODIGOS ACIMA PARA INFORMAR ABAIXO -----\t\n");
                                              printf("\n\tDIGITE O CODIGO DO IMOVEL: ");
                                              scanf("%d", &idImovel);
                                              fflush(stdin);
                                              
                                              printf("\n\tDIGITE A DATA DE RETIRADA (formato dia/mes/ano): ");
                                              scanf("%s", &dataretirada);
                                              SubstEspaco(dataretirada);
                                              fflush(stdin);
                                              
                                              printf("\n\tDIGITE A DATA DE ENTREGA (formato dia/mes/ano): ");
                                              scanf("%s", &dataentrega);
                                              SubstEspaco(dataentrega);
                                              fflush(stdin);
                                              
                                              printf("\n\tDIGITE QUANTOS DIAS DE LOCACAO: ");
                                              scanf("%d", &diasalocado);
                                              fflush(stdin);
                                                                                                
                                              
                                              CadastrarMovimentacao(idlocacao, idcliente, idImovel, dataretirada, dataentrega, diasalocado);
                                              printf("\n\n\t########## SUCESSO ########## \t\n\n");
                                              system("pause");
					case 0:
                                break;
					default:
                			    system("cls || clear");
                                printf("\n\n\t ########## OPCAO INVALIDA. TENTE NOVAMENTE ##########\t\n\n");
                                system("pause");

				     }
				
				}while(menusecundario != 0);

                break;



            case 0:

		         system("cls || clear");
                 sair();
                 break;

           default:
    			    system("cls || clear");
                    printf("\n\n\t ########## OPCAO INVALIDA. TENTE NOVAMENTE ##########\t\n\n");
                    system("pause");

        }

    }while(menuprimario != 0);
    
    exit(0);	
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> //biblioteca para utilizar as funções de validação no cadastro


void m_principal(char apelido[50]); // protótipo da função para não gerar erro de compilação

void desenhar_linha(int tamanho){
	int i;
	printf("\n");
	for (i = 0; i < tamanho; i++){
		printf("=");
	}
	printf("\n");
}

typedef struct {
	char tipo [20];
	char titulo [100];
} Filme;

// Retorna 1 se o nome for valido (apenas letras e espacos), ou 0 se for invalido.
int validar_nome(char nome[]){
	int i;
	if(strlen(nome) < 2) return 0;  //se o nome for muito curto reprova
	
	for (i= 0; nome[i] != '\0'; i++){
        // isalpha verifica se é letra, isspace verifica se é espaço
        if (!isalpha(nome[i]) && !isspace(nome[i])){
			return 0;
		}
	}
	return 1;
}

// Retorna 1 se o e-mail tiver o formato basico correto (seunome@gmail.com)
int validar_email(char email[]){
	char *arroba = strchr(email, '@'); //procura o arroba
	
	if (arroba == NULL){
		return 0; //são encontrou o arroba
	}
	char *ponto = strchr(arroba, '.'); //procura o ponto depois do arroba
	if(ponto == NULL){
		return 0; //não encontrou '.' depois do arroba
	}
	
	return 1; //Aprovado
}


void cadastro(){
	FILE *arquivo;
	
	int opcao_voltar;
	char nome[51], email[151], senha[11], apelido[51], sim[11];
	
	arquivo = fopen("usuarios.txt", "a");
	
	if (arquivo == NULL){
		printf("Erro ao abrir o arquivo de usuarios!\n");
		return;
	}
	
	printf("\nDeseja mesmo continuar?\n");
	printf("\n[1] - Sim, quero me cadastrar\n");
	printf("[2] - Não, voltar ao menu\n");
	printf("\nDigite a opçao: ");
	scanf("%d", &opcao_voltar);
	
	if (opcao_voltar == 2){
		return;
	}
	
	fflush(stdin); //Limpeza do teclado do enter digitado no menu 
	
	do{
        printf("Digite seu nome: ");
		fgets(nome, 51, stdin);
		nome[strcspn(nome, "\n")] = '\0'; // Limpa o Enter do nome
		fflush(stdin); //Joga fora qualquer letra extra que passar de 50
		
		if(validar_nome(nome) == 0){
			printf("\nNome invalido! Nao utilize numeros, simbolos, e digite pelo menos 2 letras.\n");
		}
	} while (validar_nome(nome) == 0);
	
	do{
        printf("Digite um e-mail valido: (ex: seunome@gmail.com): ");
		fgets(email, 151, stdin);
		email[strcspn(email, "\n")] = '\0'; //Limpa o Enter do email
		fflush(stdin);//Joga fora qualquer coisa que passar de 150
		
		if(validar_email(email) == 0){
			printf("\nE-mail invalido! Formato incorreto. 'Dica:seunome@gmail.com' \n\n");
		}
	} while(validar_email(email) == 0);
	
	
	printf("Digite uma senha (ate 10 digitos): ");
	fgets(senha, 11, stdin);
	senha[strcspn(senha, "\n")] = '\0'; //Limpa o Enter da senha
	fflush(stdin); //Joga fora qualquer coisa que passar de 10
	
	
	printf("Digite um apelido (como podemos te chamar): ");
	fgets(apelido, 51, stdin);
	apelido[strcspn(apelido, "\n")] = '\0'; //Limpa o Enter do apelido
	fflush(stdin); //Joga fora qualquer coisa que passar de 50
	
	fprintf(arquivo, "%s|%s|%s|%s\n", nome, email, senha, apelido); //utilizando um pipe para o programa separar as informações com um pipe ("|")
	
	fclose(arquivo);
	
	printf("\nUsuario(a), cadastrado(a) com sucesso!\n");
	
	printf("\nDigite sim para voltar ao menu inicial: ");
	scanf(" %[^\n]", sim);
}

void login(){
	FILE *arquivo; 
	char login_email[151], login_senha[11];
	char nome_txt[51], email_txt[151], senha_txt[11], apelido_txt[51];
	int opcao_voltar2, logado = 0; //variável para verificar se deu certo
	
	arquivo = fopen("usuarios.txt", "r"); //abrindo o aquivo como leitura para verificar se há cadastro
	if (arquivo == NULL){
		printf("Nenhum usuario cadastrado ainda!\n");
		return;
	}
	
	printf("\nDeseja mesmo continuar?\n");
	printf("\n[1] - Sim, quero fazer login\n");
	printf("[2] - Não, voltar ao menu\n");
	printf("\nDigite a opçao: ");
	scanf("%d", &opcao_voltar2);
	
	if (opcao_voltar2 == 2){
		return;
	}
	
	printf("\n--- LOGIN FEItv ---\n");
	
	printf("\nE-mail: ");
	scanf(" %[^\n]", login_email);
	
	printf("Senha: ");
	scanf(" %[^\n]", login_senha);
	
	while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|\n]\n", nome_txt, email_txt, senha_txt, apelido_txt) == 4){     //o módulo diferenciado serve para fazer a leitura correta das informações com o separador pipe 
		if(strcmp(login_email, email_txt) == 0 && strcmp(login_senha, senha_txt) == 0){     //comparando o que foi digitado com as informações do arquivo
			logado = 1;
			printf("\nBem vindo(a) de volta %s!\n ", apelido_txt);
			break; //achando o usuario para de procurar no arquivo
		}
	}
	if(logado == 0){
		printf("\nE-mail ou senha incorretos!\n");
		login();
	}
	
	fclose(arquivo);
		
	if (logado == 1){
		m_principal(apelido_txt);
	}
}

void m_inicial(){
	int inicial;
	do{
		desenhar_linha(30);
		printf("\nSeja bem vindo(a) ao FEItv!\n");
		desenhar_linha(30);
		printf("\nO que deseja fazer hoje?\n");
		printf("\n[1] - Cadastrar usuario\n");
		printf("[2] - Fazer login\n");
		printf("[3] - Sair do programa\n");
	
		printf("\nDigite uma opcao: ");
		scanf("%d", &inicial);
		
		if(inicial == 1){
			cadastro();
		}
		
		else if(inicial == 2){
			login();
		}
	} while (inicial != 3);
}

void curtir_video(char apelido[], char tipo [], char titulo[]){
	char nome_arquivo[100];
	FILE *arquivo_fav;
	
	// cria o nome do arquivo personalizado (ex: gusta_favoritos)
	sprintf(nome_arquivo, "%s_curtidos.txt", apelido);
	
	arquivo_fav = fopen(nome_arquivo, "a");
	
	if (arquivo_fav != NULL){
		fprintf(arquivo_fav, "%s|%s\n", tipo, titulo);
		fclose(arquivo_fav);
		printf("\n-> '%s' adicionado aos curtidos com Sucesso!\n", titulo);
	} else {
        printf("\n-> Erro ao criar o arquivo de favoritos.\n");
	}
}

void mostrar_catalogo(char apelido[50]){
	FILE *arquivo_catalogo;
	
	char tipo[20], titulo[100], genero[50], classificacao[10], temps[10], eps[10], sinopse[600];
	
	arquivo_catalogo = fopen("catalogo.txt", "r");
	
	if(arquivo_catalogo == NULL){
		printf("\nO catalogo não esta disponivel!\n");
		return;
	}
	
	system("cls");
	desenhar_linha(30);
	printf("\n     --- CATALOGO FEItv ---\n");
	desenhar_linha(30);
	printf("\n");
	
	// Lê a linha inteira do arquivo e separa cada variavel toda vez que encontrar o caractere pipe ('|').
	// O comando %[^|] orienta o fscanf a ler todos os caracteres seguidos ate esbarrar em um '|'.
	// O ultimo %[^\n]\n le o resto da sinopse ate o Enter e pula para a proxima linha do arquivo.
	while(fscanf(arquivo_catalogo, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", tipo, titulo, genero, classificacao, temps, eps, sinopse) == 7){   
		printf("[%s] | %s\n", tipo, titulo);
	}
	desenhar_linha(30);
	printf("\nPressione ENTER para voltar ao menu... ");
	
	fflush(stdin);
	getchar();
	
	fclose(arquivo_catalogo);
}

void buscar_informacoes(char apelido[50]){
	FILE *arquivo_catalogo;
	
	char tipo[20], titulo[100], genero[50], classificacao[10], temps[10], eps[10], sinopse[600];
	char filme[101];
	int encontrou = 0, i = 0, contador = 0, curtir;
	
	arquivo_catalogo = fopen("catalogo.txt", "r");
	
	fflush(stdin);
	
	printf("\nDigite qual obra deseja descobrir mais informaçoes: ");
	fgets(filme, 101, stdin);
	filme[strcspn(filme, "\n")] = '\0'; // Limpa o enter do filme
	fflush(stdin); //Joga fora tudo o que passar de 100

	
	
	while(fscanf(arquivo_catalogo, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]\n", tipo, titulo, genero, classificacao, temps, eps, sinopse) == 7){
		if(stricmp(titulo, filme) == 0){
			encontrou = 1;
			//system("cls");
			
			desenhar_linha(60);
			printf("\n                  --- DETALHES DA OBRA ---\n");
			desenhar_linha(60);
			printf("\nTitulo: %s\n", titulo);
			printf("Tipo: %s\n", tipo);
			printf("Genero: %s\n", genero);
			printf("Classificacao: %s anos\n", classificacao);
			
			if(stricmp(tipo, "Serie") == 0){      //so imprime no terminal temporada e episodios se for série 
				printf("Temporada(s): %s\n", temps);
				printf("Episodios: %s\n", eps);
			}
			
			
			printf("Sinopse: ");  //sinopse com sistema de quebra de linha para experiência do usuáro
			
			while(sinopse[i] != '\0'){
				if(contador >= 45 && sinopse[i] == ' '){
					printf("\n");
					contador = 0;
				} else {
					printf("%c", sinopse[i]);
					contador++;
				}
				i++;
			}
			printf("\n");
			
			desenhar_linha(60);
			
			printf("\nDeseja adiconar '%s' aos curtidos?\n", titulo);
			printf("\n[1] - Sim\n");
			printf("[2] - Não, retornar ao menu principal\n");
			printf("\nDigite sua opçao: ");
			scanf("%d", &curtir);
			
			if (curtir == 1){
				curtir_video(apelido, tipo, titulo);
			}
			
			printf("\nPressione ENTER para voltar ao menu...\n");
			getchar(); // Segura a tela ate o usuario apertar Enter
			break; // ja achou o filme não precisa mais percorrer o arquivo 
		}
	}
	
	if (encontrou == 0){
		printf("\nDesculpe não encontramos '%s' no nosso catalogo.\n", filme);
	}
	
	fclose(arquivo_catalogo);
}

void listar_curtidos (char apelido[]){
	FILE *arquivo;
	char nome_arquivo[100];
	
	sprintf(nome_arquivo, "%s_curtidos.txt", apelido);
	
	arquivo = fopen(nome_arquivo, "r");
	
	if (arquivo == NULL){
		printf("\nVoce ainda não curtiu nenhum video!\n");
		printf("\nPressione ENTER para voltar...\n");
		fflush(stdin);
		getchar();
		return;
	}
	
	//magica memoria RAM(Heap)
	Filme *lista = NULL; //vetor elastico
	int total_filmes = 0;
	char tipo_temp[20], titulo_temp[100];
	
	// le o arquivo linha por linha e estica o vetor com realloc
	while(fscanf(arquivo, "%[^|]|%[^\n]\n", tipo_temp, titulo_temp) == 2){
		lista = (Filme *) realloc(lista, (total_filmes + 1) * sizeof(Filme));
		strcpy(lista[total_filmes].tipo, tipo_temp);
		strcpy(lista[total_filmes].titulo, titulo_temp);
		total_filmes++;
	}
	
	fclose(arquivo);
	
	if (total_filmes == 0){
		printf("\nSua lista de curtidas está vazia!\n");
		free(lista); //pegando o espaço utilizao na RAM para outras funções, pois ja terminou de utilizar
		return;
	}
	
	int opcao;
	system("cls");
	desenhar_linha(40);
	printf("\n        MEUS VÍDEOS CURTIDOS        \n");
	desenhar_linha(40);
	
	//imprime a lista numerada
	int i;
	for (i = 0; i < total_filmes; i++){
		printf("[%d] - %s (%s)\n", i + 1, lista[i].titulo, lista[i].tipo);
	}
	
	desenhar_linha(40);
	
	printf("\n[1] - Descurtir video\n");
	printf("[2] - Voltar ao menu principal\n");
	printf("\nDigite sua opcao: ");
	scanf("%d", &opcao);
	
	if (opcao == 1){
		int num_remover;
		printf("\nDigite o numero do video que deseja descurtir: ");
		scanf("%d", &num_remover);
		
		if(num_remover >= 1 && num_remover <= total_filmes){   //verificando se o numero digitado é valido
			arquivo = fopen(nome_arquivo, "w"); //apaga o conteúdo do arquivo
			
			//grava tudo dn exceto o filme descurtido
			for (i = 0; i < total_filmes; i++){        
				if(i != (num_remover - 1)){          // O -1 é porque o vetor comeca no indice 0
				      fprintf(arquivo, "%s|%s\n", lista[i].tipo, lista[i].titulo);
				  }
			}
			
			fclose(arquivo);
			printf("\n-> '%s', removido da lsita de curtidos!\n", lista[num_remover - 1].titulo);
		} else{
			printf("\n-> Numero invalido!\n");
		}
	} 
	
	free(lista);
	fflush(stdin);
	printf("Pressione ENTER para retornar ao menu...");
	getchar();
}

void m_principal(char apelido[50]){
	int principal;
	
	do{
		printf("\nQual a boa de hoje?\n");
	
		printf("\n[1] - Mostrar Catalogo\n");
		printf("[2] - Buscar Informações\n");
		printf("[3] - Videos Curtidos\n");
		printf("[4] - Acessar Favoritos\n");
		printf("[5] - Sair do Programa\n");
		
		printf("\nDigite uma opçao: ");
		scanf("%d", &principal);
		
		if(principal == 1){
			mostrar_catalogo(apelido);
		}
		
		else if(principal == 2){
			buscar_informacoes(apelido);
		}
		
		else if(principal == 3){
			listar_curtidos(apelido);
		}
	} 
	while(principal != 5);
	
	printf("\nSaindo da sua conta...\n");
	printf("Retornando ao menu inicial.\n");
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	
	m_inicial();
	
	system("pause");	
	return 0;
}

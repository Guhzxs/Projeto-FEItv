#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//int c;
//void limpar(while (c == '\n' && c == EOF)); End of File
// return;
void m_principal(char apelido[50]); // protótipo da função para não gerar erro de compilação

void desenhar_linha(int tamanho){
	int i;
	printf("\n");
	for (i = 0; i < tamanho; i++){
		printf("=");
	}
	printf("\n");
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
	
	printf("Digite seu nome: ");
	fgets(nome, 51, stdin);
	nome[strcspn(nome, "\n")] = '\0'; // Limpa o Enter do nome
	fflush(stdin); //Joga fora qualquer letra extra que passar de 50
	
	printf("Digite um e-mail valido: (ex: seunome@gmail.com): ");
	fgets(email, 151, stdin);
	email[strcspn(email, "\n")] = '\0'; //Limpa o Enter do email
	fflush(stdin);//Joga fora qualquer coisa que passar de 150
	
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

void mostrar_catalogo(){
	FILE *arquivo_catalogo;
	
	char tipo[20], titulo[100], genero[50], classificacao[10], temps[10], eps[10], sinopse[600];
	
	arquivo_catalogo = fopen("catalogo.txt", "r");
	
	if(arquivo_catalogo == NULL){
		printf("\nO catalogo não esta disponivel!\n");
		return;
	}
	
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
	fclose(arquivo_catalogo);
}

//void buscar_informacoes(){
	//FILE *arquivo_catalogo
	
	//char tipo[20], titulo[100], genero[50], classificacao[10], temps[10], eps[10], sinopse[600];
	//char filme[101];
	//int encontrou = 0;
	
	//arquivo_catalogo = fopen("catalogo.txt", "r");
	
	//printf("Digite qual filme deseja descobrir mais informaçoes: ");
	//fgets(filme, 101, stdin);
	//filme[strcspn(filme, "\n")] = '\0'; // Limpa o enter do filme
	//fflush(stdin); //Joga fora tudo o que passar de 100
	
//}

void m_principal(char apelido[50]){
	int principal;
	
	do{
		printf("\nQual a boa de hoje?\n");
	
		printf("\n[1] - Mostrar Catalogo\n");
		printf("[2] - Buscar Informações\n");
		printf("[3] - Acessar Favoritos\n");
		printf("[4] - Sair do programa\n");
		
		printf("\nDigite uma opçao: ");
		scanf("%d", &principal);
		
		if(principal == 1){
			mostrar_catalogo();
		}
		
		else if(principal == 2){
			//buscar_informacoes();
		}
	} 
	while(principal != 4);
	
	printf("\nSaindo da sua conta...\n");
	printf("Retornando ao menu inicial.\n");
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	
	m_inicial();
	
	system("pause");	
	return 0;
}

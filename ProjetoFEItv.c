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

// STRUCTS
// Agrupamento de variaveis para melhor organizacao da memoria
typedef struct {
	char tipo [20];
	char titulo [100];
} Filme;

typedef struct {
	char playlist[50];
	char tipo [20];
	char titulo[100];
} Favorito;

typedef struct {
	char tipo[20];
	char titulo[100];
	char genero[50];
	char classificacao[10];
	char temps[10];
	char eps[10];
	char sinopse[600];
} Obra;

//função de validação 
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
		return 0; //não encontrou o arroba
	}
	char *ponto = strchr(arroba, '.'); //procura o ponto depois do arroba
	if(ponto == NULL){
		return 0; //não encontrou '.' depois do arroba
	}
	
	return 1; //Aprovado
}

//funções de autenticação 
void cadastro(){
	FILE *arquivo;
	
	int opcao_voltar;
	char nome[51], email[151], senha[11], apelido[51];
	
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
		nome[strcspn(nome, "\n")] = '\0'; // strcspn localiza e remove o '\n' gerado pelo fgets
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
	
	fprintf(arquivo, "%s|%s|%s|%s\n", nome, email, senha, apelido); // Persistencia de Dados: gravando com separador Pipe (|) para facilitar a leitura futura
	
	fclose(arquivo);
	
	printf("\nUsuario(a), cadastrado(a) com sucesso!\n");
	
}

void login(){
	FILE *arquivo; 
	char login_email[151], login_senha[11];
	char nome_txt[51], email_txt[151], senha_txt[11], apelido_txt[51];
	int opcao_voltar2, logado = 0; //variável para verificar se deu certo
	
	arquivo = fopen("usuarios.txt", "r"); //abrindo o aquivo como leitura para verificar se há cadastro
	if (arquivo == NULL){
		printf("\nNenhum usuario cadastrado ainda!\n");
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
	
	printf("\n---LOGIN FEItv---\n");
	
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
		login(); // Chamada recursiva em caso de falha
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
		desenhar_linha(30);
	
		printf("\nDigite uma opcao: ");
		scanf("%d", &inicial);
		getchar();
		
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
	
	// // Geracao de arquivo personalizado baseada no nickname do usuario atual
	sprintf(nome_arquivo, "%s_curtidos.txt", apelido);
	
	// trava de segurança
	int ja_curtiu = 0;
	FILE *verifica_curtidos = fopen(nome_arquivo, "r");
	
	if (verifica_curtidos != NULL){
		char tipo_temp[20], titulo_temp[100];
		
		// varre o arquivo lendo apenas as 2 informações tipo e titulo
		while(fscanf(verifica_curtidos, " %[^|]|%[^\n]\n", tipo_temp, titulo_temp) == 2){
			
			// Se o titulo do arquivo for igual ao titulo que ele quer curtir, aciona a trava!
			if(stricmp(titulo_temp, titulo) == 0){
				ja_curtiu = 1;
				break;
			}
		}
		fclose(verifica_curtidos);
	}
	
	if (ja_curtiu == 1){
		printf("\n-> Voce ja curtiu a obra '%s'!\n", titulo);
	} 
	else{
		arquivo_fav = fopen(nome_arquivo, "a");
		
		if (arquivo_fav != NULL){
			fprintf(arquivo_fav, "%s|%s\n", tipo, titulo);
			fclose(arquivo_fav);
			printf("\n-> '%s' adicionado aos curtidos com Sucesso!\n", titulo);
		} else {
	        printf("\n-> Erro ao criar o arquivo de curtidos.\n");
		}
	}
}

void mostrar_catalogo(char apelido[50]){
	FILE *arquivo_catalogo;
	
	Obra item;
	
	arquivo_catalogo = fopen("catalogo.txt", "r");
	
	if(arquivo_catalogo == NULL){
		printf("\nO catalogo não esta disponivel!\n");
		return;
	}
	
	system("cls");
	desenhar_linha(30);
	printf("\n     ---CATALOGO FEItv---\n");
	desenhar_linha(30);
	printf("\n");
	
	// Lê a linha inteira do arquivo e separa cada variavel toda vez que encontrar o caractere pipe ('|').
	// O comando %[^|] orienta o fscanf a ler todos os caracteres seguidos ate esbarrar em um '|'.
	// O ultimo %[^\n]\n le o resto da sinopse ate o Enter e pula para a proxima linha do arquivo.
	while(fscanf(arquivo_catalogo, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", item.tipo, item.titulo, item.genero, item.classificacao, item.temps, item.eps, item.sinopse) == 7){   
		printf("[%s] | %s\n", item.tipo, item.titulo);
	}
	desenhar_linha(30);
	printf("\nPressione ENTER para voltar ao menu... ");
	
	fflush(stdin);
	getchar();
	
	fclose(arquivo_catalogo);
}

void buscar_informacoes(char apelido[50]){
	FILE *arquivo_catalogo;
	
	Obra item;
	char filme[101];
	int curtir;
	
	while(1){
		int encontrou = 0, i = 0, contador = 0;
		
		fflush(stdin);
		printf("\nDigite qual obra deseja descobrir mais informaçoes (ou '0' para sair): ");
		fgets(filme, 101, stdin);
		filme[strcspn(filme, "\n")] = '\0'; // Limpa o enter do filme
		fflush(stdin); //Joga fora tudo o que passar de 100
		
		if(strcmp(filme, "0") == 0){
			break; // Quebra o laco e volta para o m_principal
		}
		
		arquivo_catalogo = fopen("catalogo.txt", "r");
		if(arquivo_catalogo == NULL){
			printf("\nO catalogo nao esta disponivel no momento!\n");
			break;
		}
		
		while(fscanf(arquivo_catalogo, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]\n", item.tipo, item.titulo, item.genero, item.classificacao, item.temps, item.eps, item.sinopse) == 7){
			// stricmp: Compara ignorando diferencas entre maiusculas e minusculas
			if(stricmp(item.titulo, filme) == 0){
				encontrou = 1;
				
				desenhar_linha(60);
				printf("\n                  ---DETALHES DA OBRA---\n");
				desenhar_linha(60);
				printf("\nTitulo: %s\n", item.titulo);
				printf("Tipo: %s\n", item.tipo);
				printf("Genero: %s\n", item.genero);
				printf("Classificacao: %s anos\n", item.classificacao);
				
				if(stricmp(item.tipo, "Serie") == 0){      //so imprime no terminal temporada e episodios se for série 
					printf("Temporada(s): %s\n", item.temps);
					printf("Episodios: %s\n", item.eps);
				}
				
				
				printf("Sinopse: ");  //sinopse com sistema de quebra de linha para experiência do usuáro
				
				// Lógica de UI: Algoritmo manual de Word Wrap (Quebra de linha) para a sinopse
				while(item.sinopse[i] != '\0'){
					if(contador >= 45 && item.sinopse[i] == ' '){
						printf("\n");
						contador = 0;
					} else {
						printf("%c", item.sinopse[i]);
						contador++;
					}
					i++;
				}
				printf("\n");
				
				desenhar_linha(60);
				
				printf("\nDeseja adiconar '%s' aos curtidos?\n", item.titulo);
				printf("\n[1] - Sim\n");
				printf("[2] - Não\n");
				printf("\nDigite sua opçao: ");
				scanf("%d", &curtir);
				
				if (curtir == 1){
					curtir_video(apelido, item.tipo, item.titulo);
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
	
}

void listar_curtidos (char apelido[]){
	FILE *arquivo;
	char nome_arquivo[100];
	int i, opcao;
	
	sprintf(nome_arquivo, "%s_curtidos.txt", apelido);
	
	arquivo = fopen(nome_arquivo, "r");
	
	if (arquivo == NULL){
		printf("\nVoce ainda não curtiu nenhum video!\n");
		printf("\nPressione ENTER para voltar...\n");
		fflush(stdin);
		getchar();
		return;
	}
	
	//Alocacao Dinamica na Memoria RAM (Heap) usando realloc para criar um vetor elastico
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
	
	
	desenhar_linha(40);
	printf("\n      ---MEUS VÍDEOS CURTIDOS---       \n");
	desenhar_linha(40);
	printf("\n");
	
	//imprime a lista numerada
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
		
		while(1){
			printf("\nDigite o numero do video que deseja descurtir (ou '0' para salvar e sair): ");
			// Verifica se o scanf conseguiu ler exatamente 1 numero inteiro.
			// Se nao conseguiu (porque a pessoa digitou letras), entramos no erro.
			if (scanf("%d", &num_remover) != 1) {
				printf("\n-> Entrada invalida! Por favor, digite apenas o NUMERO do video.\n");
				fflush(stdin); 
				continue; 
			}
			
			fflush(stdin); 
			
			if(num_remover == 0){
				printf("\n-> Processo de 'Remocao' terminado!\n");
				break;
			}
			
			if(num_remover >= 1 && num_remover <= total_filmes){   //verificando se o numero digitado é valido
				arquivo = fopen(nome_arquivo, "w"); //apaga o conteúdo do arquivo
				
				// Lógica de Exclusao: Grava tudo na base de dados novamente, executando o filtro do item a ser removido
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
		
	} 
	
	free(lista);
	fflush(stdin);
}

void gerenciar_favoritos(char apelido[]){
	int opcao;
	char nome_arquivo[100];
	
	sprintf(nome_arquivo, "%s_favoritos.txt", apelido);
	
	do {
	
		desenhar_linha(40);
		printf("\n           ---PLAYLISTS---      \n");
		desenhar_linha(40);
		
		printf("\n[1] - Criar Playlist\n");
		printf("[2] - Visualizar minhas Playlists\n");
		printf("[3] - Editar Playlists\n");
		printf("[4] - Voltar ao menu principal\n");
		
		desenhar_linha(40);
		
		printf("\nDigite sua opçao: ");
		scanf("%d", &opcao);
		fflush(stdin);
		
		if(opcao == 1){
			char nome_playlist[50], filme_buscado[100];
			
			
			printf("\nDigite o nome da nova playlist: ");
			fgets(nome_playlist, 50, stdin);
			nome_playlist[strcspn(nome_playlist, "\n")] = '\0';
			fflush(stdin);
			
			mostrar_catalogo(apelido);
			
			while(1){
				int encontrou = 0;
				
				printf("\nDigite o nome do filme/serie para adicionar a '%s'(ou '0' para salvar e sair): ", nome_playlist);
				fgets(filme_buscado, 100, stdin);
				filme_buscado[strcspn(filme_buscado, "\n")] = '\0';
				fflush(stdin);
				
				if(strcmp(filme_buscado, "0") == 0){
					printf("\n-> Criacao da playlist concluida!\n\n");
					break; // Sai do loop infinito
				}
				
				//abrindo o catalogo para achar o filme 
				FILE *arquivo_catalogo = fopen("catalogo.txt", "r");
				
				if (arquivo_catalogo != NULL){
					Obra item_c;
					
					while(fscanf(arquivo_catalogo, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", item_c.tipo, item_c.titulo, item_c.genero, item_c.classificacao, item_c.temps, item_c.eps, item_c.sinopse) == 7){
						
						//se o titulo do catalogo for igual ao filme buscado 
						if(stricmp(item_c.titulo, filme_buscado) == 0){
							encontrou = 1;
							char nome_arquivo[100];
							sprintf(nome_arquivo, "%s_favoritos.txt", apelido);
							
							int ja_existe = 0;
							FILE *verifica_fav = fopen(nome_arquivo, "r");
							
							if(verifica_fav != NULL){
								char p_temp[50], tipo_temp[20], tit_temp[100];
								
								while(fscanf(verifica_fav, " %[^|]|%[^|]|%[^\n]\n", p_temp, tipo_temp, tit_temp) == 3){
									if(stricmp(p_temp, nome_playlist) == 0 && stricmp(tit_temp, item_c.titulo) == 0){
										ja_existe = 1;
										break;
									}
								}
								fclose(verifica_fav);
							}
							
							if (ja_existe == 1){
								printf("\n-> A obra '%s' ja esta na playlist '%s'!\n", item_c.titulo, nome_playlist);
							}
							else{
								FILE *arquivo_fav;
								
								arquivo_fav = fopen(nome_arquivo, "a");
							
								if(arquivo_fav != NULL){
									fprintf(arquivo_fav, "%s|%s|%s\n", nome_playlist, item_c.tipo, item_c.titulo);
									
									fclose(arquivo_fav);
									printf("\n-> '%s' adicionado a playlist '%s' com sucesso!\n", item_c.titulo, nome_playlist);
								}
								else {
									printf("\n-> Erro ao salvar na playlist!\n");
								}
							}
							
							
							break; //achou e salvou
						}
					}
					fclose(arquivo_catalogo);
				}
				if (encontrou == 0){
					printf("\nObra nao encontrada no catalogo!\n");
				}
			}
			
			system("pause");
		}
		
		else if(opcao == 2){
			FILE *arquivo_fav;
			char nome_arquivo[100];
			
			sprintf(nome_arquivo, "%s_favoritos.txt", apelido);
			arquivo_fav = fopen(nome_arquivo, "r");
			
			if(arquivo_fav == NULL){
				printf("\nVoce ainda nao tem nenhuma playlist!\n");
				system("pause");
				continue; //interrompe a rodada e volta para o topo do menu
			}
			
			Favorito *lista = NULL;
			
			int total_fav = 0, i, j;
			
			char play_tmp[50], tipo_tmp[20], titulo_tmp[100];
			
			while(fscanf(arquivo_fav, " %[^|]|%[^|]|%[^\n]\n", play_tmp, tipo_tmp, titulo_tmp) == 3){
				lista = (Favorito *) realloc(lista, (total_fav + 1) * sizeof(Favorito));
				strcpy(lista[total_fav].playlist, play_tmp);
				strcpy(lista[total_fav].tipo, tipo_tmp);
				strcpy(lista[total_fav].titulo, titulo_tmp);
				total_fav++;
			}
			fclose(arquivo_fav);
			
			if(total_fav == 0){
				printf("\nSuas playlists estao vazias!\n");
				free(lista);
				system("pause");
				continue;
			}
			
			desenhar_linha(50);
			printf("\n             ---MINHAS PLAYLISTS---            \n");
			desenhar_linha(50);
			
			for(i = 0; i < total_fav; i++){
				int ja_imprimiu = 0;
				
				for(j = 0; j < i; j++){
					if(stricmp(lista[i].playlist, lista[j].playlist) == 0){
						ja_imprimiu = 1;
						break;
						
					}
				}
				// Se ainda não imprimiu, mostra na tela!
				if(ja_imprimiu == 0){
					printf("\n-> %s\n", lista[i].playlist);
				}
			}
			desenhar_linha(50);
			
			while(1){
				char escolha[50];
				
				printf("\nDigite o nome da playlist que deseja visualizar (ou '0' para voltar): ");
				fgets(escolha, 50, stdin);
				escolha[strcspn(escolha, "\n")] = '\0';
				fflush(stdin);
				
				if(stricmp(escolha, "0") == 0){
					break; 
				}
				
				int achou = 0;
				
				for(i = 0; i < total_fav; i++){
					if(stricmp(lista[i].playlist, escolha) == 0){
						achou = 1;
						break;
					}
				}
				
				if (achou == 0){
					printf("\nNenhuma playlist com esse nome foi encontrada!\n");
				}
				else{
					desenhar_linha(50);
					printf("\n  --- Playlist '%s' ---\n", escolha);
					desenhar_linha(50);
					
					
					//faz uma varredura na RAM procurando os filmes que pertencem a playlist digitada 
					for(i = 0; i < total_fav; i++){
						if(stricmp(lista[i].playlist, escolha) == 0){
							printf("\n- %s (%s)\n", lista[i].titulo, lista[i].tipo);
							achou = 1;
						}
					}
					desenhar_linha(50);
					printf("\nPressione ENTER para pesquisar outra playlist...");
					fflush(stdin);
					getchar();
				}
			}
			
			free(lista); //liberando a RAM
			printf("\n");
		}
		
		else if(opcao == 3){
			FILE *arquivo_fav;
			char nome_arquivo[100];
			
			sprintf(nome_arquivo, "%s_favoritos.txt", apelido);
			arquivo_fav = fopen(nome_arquivo, "r");
			
			
			if(arquivo_fav == NULL){
				printf("\nVoce ainda nao tem nenhuma playlist para editar!\n");
				system("pause");
				continue; 
			}
			
			// Puxa tudo para a RAM para listar os nomes disponiveis
			Favorito *lista = NULL;
			int total_fav = 0, i, j;
			char play_temp[50], tipo_temp[20], titulo_temp[100];
			
			while(fscanf(arquivo_fav, " %[^|]|%[^|]|%[^\n]\n", play_temp, tipo_temp, titulo_temp) == 3){
				lista = (Favorito *) realloc(lista, (total_fav + 1) * sizeof(Favorito));
				strcpy(lista[total_fav].playlist, play_temp);
				strcpy(lista[total_fav].tipo, tipo_temp);
				strcpy(lista[total_fav].titulo, titulo_temp);
				total_fav++;
			}
			fclose(arquivo_fav);
			
			if(total_fav == 0){
				printf("\nSuas playlists estao vazias!\n");
				free(lista);
				system("pause");
				continue;
			}
			
			desenhar_linha(50);
			printf("\n            ---MINHAS PLAYLISTS---            \n");
			desenhar_linha(50);
			
			for(i = 0; i < total_fav; i++){
				int ja_imprimiu = 0;
				for(j = 0; j < i; j++){
					if(stricmp(lista[i].playlist, lista[j].playlist) == 0){
						ja_imprimiu = 1;
						break;
					}
				}
				if(ja_imprimiu == 0){
					printf("\n-> %s\n", lista[i].playlist);
				}
			}
			desenhar_linha(50);
			
			int op_editar;
			char nome_playlist[50];
			
			printf("\nDigite o nome da playlist que deseja editar: ");
			fgets(nome_playlist, 50, stdin);
			nome_playlist[strcspn(nome_playlist, "\n")] = '\0'; // Limpa o enter
			fflush(stdin);
			
			if(strcmp(nome_playlist, "0") == 0){
				free(lista);
				continue; // Volta pro menu de playlists
			}
			
			//validacao: verifica se o nome digitado realmente existe na RAM!
			int existe = 0;
			for(i = 0; i < total_fav; i++){
				if(stricmp(lista[i].playlist, nome_playlist) == 0){
					existe = 1;
					break;
				}
			}
			
			free(lista); 
			
			// Se o cara inventou um nome que não tava na tela, barra ele!
			if(existe == 0){
				printf("\n-> Playlist nao encontrada! Cancelando edicao...\n");
				system("pause");
				continue;
			}
			
			do{
				// sub menu de edição
				desenhar_linha(40);
				printf("\n  ---Editando '%s'---\n", nome_playlist);
				desenhar_linha(40);
				printf("\n[1] - Adicionar filme/serie\n");
				printf("[2] - Remover filme/serie\n");
				printf("[3] - Excluir playlist inteira\n");
				printf("[4] - Cancelar / Voltar\n");
				desenhar_linha(40);
				printf("\nDigite sua opcao: ");
				scanf("%d", &op_editar);
				fflush(stdin);
				
				if (op_editar == 1){
					char filme_buscado[100];
					
					mostrar_catalogo(apelido);
					
					while(1){
						int encontrou = 0;
						
						printf("\nDigite o nome do filme/serie para adicionar a '%s' (ou '0' para salvar e sair): ", nome_playlist);
						fgets(filme_buscado, 100, stdin);
						filme_buscado[strcspn(filme_buscado, "\n")] = '\0';
						fflush(stdin);
						
						if(strcmp(filme_buscado, "0") == 0){
							printf("\nFinalizando adicoes...\n\n");
							break; 
						}
						
						//abrindo o catalogo para achar o filme 
						FILE *arquivo_catalogo = fopen("catalogo.txt", "r");
						
						if (arquivo_catalogo != NULL){
							Obra item_c;
							
							while(fscanf(arquivo_catalogo, " %[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", item_c.tipo, item_c.titulo, item_c.genero, item_c.classificacao, item_c.temps, item_c.eps, item_c.sinopse) == 7){
								
								//se o titulo do catalogo for igual ao filme buscado 
								if(stricmp(item_c.titulo, filme_buscado) == 0){
									encontrou = 1;
									
									char nome_arquivo[100];
									sprintf(nome_arquivo, "%s_favoritos.txt", apelido);
									
									int ja_existe = 0;
									FILE *verifica_fav = fopen(nome_arquivo, "r");
									
									if(verifica_fav != NULL){
										char p_temp[50], tipo_temp[20], tit_temp[100];
										
										while(fscanf(verifica_fav, " %[^|]|%[^|]|%[^\n]\n", p_temp, tipo_temp, tit_temp) == 3){
											if(stricmp(p_temp, nome_playlist) == 0 && stricmp(tit_temp, item_c.titulo) == 0){
												ja_existe = 1;
												break;
											}
										}
										fclose(verifica_fav);
									}
									
									if (ja_existe == 1){
										printf("\n-> A obra '%s' ja esta na playlist '%s'!\n", item_c.titulo, nome_playlist);
									}
									else{
										FILE *arquivo_fav;
										arquivo_fav = fopen(nome_arquivo, "a");
									
										if(arquivo_fav != NULL){
											fprintf(arquivo_fav, "%s|%s|%s\n", nome_playlist, item_c.tipo, item_c.titulo);
											
											fclose(arquivo_fav);
											printf("\n-> '%s' adicionado a playlist '%s' com sucesso!\n", item_c.titulo, nome_playlist);
										}
										else {
											printf("\n-> Erro ao salvar na playlist!\n");
										}
									}
									
									
									break; //achou e salvou
								}
							}
							fclose(arquivo_catalogo);
						}
						if (encontrou == 0){
							printf("\nObra nao encontrada no catalogo!");
						}
					}
					
					system("pause");
				}
				else if(op_editar == 2){
					FILE *arquivo;
					char nome_arquivo[100];
					
					sprintf(nome_arquivo, "%s_favoritos.txt", apelido);
					
					arquivo = fopen(nome_arquivo, "r");
					
					if(arquivo == NULL){
						printf("\nVoce ainda nao criou nenhuma playlist!\n");
						printf("\nPressione ENTER para voltar...\n");
						fflush(stdin);
						getchar();
						break;
					}
					
					Favorito *lista = NULL;
					int total_fav = 0;
					char play_temp[50], tipo_temp[20], titulo_temp[100];
					
					while(fscanf(arquivo, " %[^|]|%[^|]|%[^\n]\n", play_temp, tipo_temp, titulo_temp) == 3){
						lista = (Favorito *) realloc(lista, (total_fav + 1) * sizeof(Favorito));
						
						strcpy(lista[total_fav].playlist, play_temp);
						strcpy(lista[total_fav].tipo, tipo_temp);
						strcpy(lista[total_fav].titulo, titulo_temp);
						
						total_fav++;
					}
					fclose(arquivo);
					
					//mostrando o conteudo da playlist 
					desenhar_linha(50);
					printf("\n  ---Filmes na playlist '%s'---\n", nome_playlist);
					desenhar_linha(50);
					
					int j, tem_filme = 0;
					for(j = 0; j < total_fav; j++){
						if(stricmp(lista[j].playlist, nome_playlist) == 0){
							printf("\n-> %s\n", lista[j].titulo);
							tem_filme = 1;
						}
					}
					desenhar_linha(50);
					
					if(tem_filme == 0){
						printf("\nEsta playlist esta vazia!\n");
						free(lista);
						system("pause");
						break;
					}
					
					char filme_remover[100];
					
					while(1){
						printf("\nDigite o nome do filme/serie para remover (ou '0' para salvar e sair): ");
						fgets(filme_remover, 100, stdin);
						filme_remover[strcspn(filme_remover, "\n")] = '\0';
						fflush(stdin);
						
						if(strcmp(filme_remover, "0") == 0)break; //para parar as remocoes
						
						int achei_lista = 0;
						
						for(j = 0; j < total_fav; j++){
							if(stricmp(lista[j].titulo, filme_remover) == 0 && stricmp(lista[j].playlist, nome_playlist) == 0){   // Se o nome bater e for da playlist que estamos editando
								strcpy(lista[j].titulo, "Apagado");
								printf("\n-> '%s' selecionado para remocao!\n", filme_remover);
								achei_lista = 1;
								break;
							}
						}
						
						if (achei_lista == 0){
							printf("\nFilme nao encontrado nesta playlist!\n");
						}
						
					}
					arquivo = fopen(nome_arquivo, "w");
						
					for (j = 0; j < total_fav; j++){
						if(stricmp(lista[j].titulo, "Apagado") != 0){
							fprintf(arquivo, "%s|%s|%s\n", lista[j].playlist, lista[j].tipo, lista[j].titulo);
						}
					}
					fclose(arquivo);
					free(lista);
					printf("\nAlteracoes na playlist '%s' salvas com sucesso!\n\n", nome_playlist);
						
					system("pause");
						
				}
				else if(op_editar == 3){
					FILE *arquivo;
					char nome_arquivo[100];
					
					sprintf(nome_arquivo, "%s_favoritos.txt", apelido);
					
					arquivo = fopen(nome_arquivo, "r");
					
					if(arquivo == NULL){
						printf("\nVoce ainda nao criou nenhuma playlist!\n");
						printf("\nPressione ENTER para voltar...\n");
						fflush(stdin);
						getchar();
						break;
					}
					//magica memoria RAM(Heap)
					Favorito *lista = NULL;
					int total_fav = 0;
					char play_temp[50], tipo_temp[20], titulo_temp[100];
					
					while(fscanf(arquivo, " %[^|]|%[^|]|%[^\n]\n", play_temp, tipo_temp, titulo_temp) == 3){
						lista = (Favorito *) realloc(lista, (total_fav + 1)* sizeof(Favorito));
						
						strcpy(lista[total_fav].playlist, play_temp);
						strcpy(lista[total_fav].tipo, tipo_temp);
						strcpy(lista[total_fav].titulo, titulo_temp);
						
						total_fav++;
						
					}
					fclose(arquivo);
					
					arquivo = fopen(nome_arquivo, "w"); //apaga o conteúdo do arquivo
					
					int i;
					
					//grava tudo dnv exceto a playlist removida
					for (i = 0; i < total_fav; i++){
						      
					  	if (stricmp(lista[i].playlist, nome_playlist) != 0){
							fprintf(arquivo, "%s|%s|%s\n", lista[i].playlist, lista[i].tipo, lista[i].titulo);
						}
					}
						
						fclose(arquivo);
						free(lista);
						printf("\n-> Playlist '%s', excluida com sucesso!\n", nome_playlist);
						
						system("pause");
						break;
				}
			} while (op_editar != 4);
		}
	} while (opcao != 4);
}

void m_principal(char apelido[50]){
	int principal;
	
	do{
		desenhar_linha(40);
		printf("\n              --FEItv--\n");
		desenhar_linha(40);
		printf("\nQual a boa de hoje?\n");
	
		printf("\n[1] - Mostrar Catalogo\n");
		printf("[2] - Buscar Informações\n");
		printf("[3] - Obras Curtidas\n");
		printf("[4] - Acessar Favoritos\n");
		printf("[5] - Sair do Programa\n");
		
		desenhar_linha(40);
		
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
		else if(principal == 4){
			gerenciar_favoritos(apelido);
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

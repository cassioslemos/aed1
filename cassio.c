#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct variaveis{
	int i,op,npessoas;
}VARIAVEIS;
	
typedef struct agenda{
	char nome[40];
	char numero[16];
}AGENDA;	

void incluir (void *pBuffer){
	VARIAVEIS *v;
	AGENDA *pessoa;
	void *pBuffer2;
	v=pBuffer;
	v->npessoas++;
	pBuffer=realloc(pBuffer,sizeof(AGENDA));
	pBuffer2=pBuffer;
	for(v->i=0;v->i<v->npessoas;v->i++){
		pBuffer2++;
	}
	pessoa=pBuffer2;	
	printf("Nome: ");
	getchar();
	fgets(pessoa->nome,40,stdin);
	pessoa->nome[strcspn(pessoa->nome,"/n")]=0;
	printf("Telefone: ");
	fgets(pessoa->numero,16,stdin);
	pessoa->numero[strcspn(pessoa->numero,"/n")]=0;
}

void menu (void *pBuffer){
	VARIAVEIS *p;
	p=pBuffer;
	while(1){
		printf("Menu:\n\n");
		printf("1- Incluir pessoa\n");
		printf("2- Apagar pessoa\n");
		printf("3- Buscar pessoa\n");
		printf("0- Sair do programa\n\n");
		printf("Opcao: ");
		scanf("%d",&p->op);
		switch(p->op){
			case 1:
			incluir(pBuffer);
			break;
			case 2:
			printf("teste2");
			break;
			case 3:
			printf("teste3");
			break;
			case 0:
			exit(1);
			break;
			default:
			printf("Comando invalido\n\n");
			break;
		}
	}
}

int main()
{
	void *pBuffer;
	pBuffer=malloc(sizeof(VARIAVEIS));
	if(pBuffer==NULL){
			printf("Erro!");
			exit(1);
	}
	menu(pBuffer);
	return 0;
}

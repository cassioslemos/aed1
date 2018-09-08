#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct variaveis{
	int i,i2,op,npessoas, teste, tamBuffer;
	char nome[40];
}VARIAVEIS;

typedef struct agenda{
	char nome[40];
	char numero[16];
}AGENDA;

void* incluir (void *pBuffer){
	VARIAVEIS *v;
	AGENDA *pessoa;
	void *pBuffer2;

	v=pBuffer;
	v->npessoas = v->npessoas+1;
	v->tamBuffer = v->tamBuffer+sizeof(AGENDA);
	pBuffer=realloc(pBuffer,v->tamBuffer);
	v=pBuffer;

	pBuffer2 = pBuffer;
	pBuffer2 = pBuffer2 + sizeof(VARIAVEIS);
	pBuffer2 = pBuffer2 + sizeof(AGENDA)*(v->npessoas-1);
	pessoa = pBuffer2;

	printf("\nNome: ");
	getchar();
	fgets(pessoa->nome,40,stdin);
	pessoa->nome[strcspn(pessoa->nome,"\n")]=0;
	printf("Telefone: ");
	fgets(pessoa->numero,16,stdin);
	pessoa->numero[strcspn(pessoa->numero,"\n")]=0;
	printf("\n");

	return pBuffer;

}

void* excluir (void *pBuffer){
    VARIAVEIS *v;
    AGENDA *pessoa, *prox;

    v=pBuffer;
    pessoa = pBuffer + sizeof(VARIAVEIS);
    v->teste = 1; // verdadeiro

    if(v->npessoas == 0){
    	printf("\nAgenda vazia!\n\n");
    	return pBuffer;
    }

    while(v->teste){ // enquanto for verdadeiro
    	printf("\nDigite o nome que deseja excluir: ");
    	getchar();
   		fgets(v->nome,40,stdin);
    	v->nome[strcspn(v->nome,"\n")]=0;

	    for(v->i=0;v->i < v->npessoas;v->i++){
	    	if((strcmp(v->nome, pessoa[v->i].nome)) == 0){
	    		v->npessoas = v->npessoas-1;
	    		for(v->i2 = v->i; v->i2 < v->npessoas; v->i2++){
	    			pessoa[v->i2] = pessoa[v->i2 +1];
	    		}

	    		v->tamBuffer = v->tamBuffer - sizeof(AGENDA);
	    		pBuffer = realloc(pBuffer, v->tamBuffer);
	    		v->teste = 0;
	    		printf("\nContato excluido com sucesso!\n\n");
	    		break;
	    	}

	    }

	    if(v->teste){
	    	printf("\nPessoa nao encontrada!\nVoce deseja tentar novamente: (1) Sim   (0) Nao\n");
	    	scanf("%d", &v->teste);
	    	printf("\n");
	    }
	}

	return pBuffer;
}

void buscar (void *pBuffer){
    VARIAVEIS *v;
    AGENDA *contato;
    v=pBuffer;
    contato=pBuffer+sizeof(VARIAVEIS);
    v->teste=1;
    if (v->npessoas == 0){
        printf("\nAgenda Vazia!\n\n");
    }
    else {
        printf("\nInforme um nome: ");
        getchar();
        fgets(v->nome,40,stdin);
        v->nome[strcspn(v->nome,"\n")] = 0;
        for(v->i=0; v->i < v->npessoas; v->i++, contato++){
            if(strcmp(v->nome,contato->nome) == 0){
                v->teste=0;
                printf("\nNome: %s\nTelefone: %s\n\n", contato->nome, contato->numero);
                break;
            }
        }
        if (v->teste){
            printf("\nPessoa nao encontrada!\n\n");
        }
    }
}

void listar (void *pBuffer){
    VARIAVEIS *v;
    AGENDA *contato;
    v=pBuffer;
    contato=pBuffer+sizeof(VARIAVEIS);
    if(v->npessoas == 0){
        printf("\nAgenda vazia!\n\n");
    }
    else{
        printf("\n");
        for(v->i = 0; v->i < v->npessoas; v->i++){
            printf("Nome: %s \nTelefone: %s\n\n", contato->nome, contato->numero);
            contato++;
        }
    }
}

void menu (void *pBuffer){
	VARIAVEIS *p;
	p=pBuffer;
	while(1){
		printf("Menu:\n\n");
		printf("1- Incluir pessoa\n");
        printf("2- Apagar pessoa\n");
		printf("3- Buscar pessoa\n");
		printf("4- Listar pessoas\n");
		printf("0- Sair do programa\n\n");
		printf("Opcao: ");
		scanf("%d",&p->op);
		switch(p->op){
			case 1:
			pBuffer = incluir(pBuffer);
			break;
			case 2:
			pBuffer = excluir(pBuffer);
			break;
			case 3:
			buscar(pBuffer);
			break;
			case 4:
			listar(pBuffer);
			break;
			case 0:
            free(pBuffer);
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
	VARIAVEIS *p;
	pBuffer=malloc(sizeof(VARIAVEIS));
	if(pBuffer==NULL){
			printf("Erro!");
			exit(1);
	}
	p=pBuffer;
	p->npessoas=0;
	p->tamBuffer = sizeof(VARIAVEIS);
	menu(pBuffer);
	return 0;
}


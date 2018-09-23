#include <stdio.h>
#include <stdlib.h>
 
//#define TAMANHO 300


typedef struct _Endereco Endereco;

struct _Endereco{
	char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

 
int main(int argc, char** argv)
{
    FILE *entrada1,*saida,*saida2;
   // char buffer[TAMANHO];
    int qtd, x=0;
 
     Endereco e;


//    srandom(427);

    if(argc != 4)
    {
        fprintf(stderr,"Erro na chamada do comando.\n");
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
        return 1;
    }
 
    entrada1 = fopen(argv[1],"rb");
    if(!entrada1)
    {
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }


    
 
    saida = fopen(argv[2],"wb");
    if(!saida)
    {
        fclose(entrada1);
        fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
        return 1;
    }
 
     
 	saida2 = fopen(argv[3],"wb");
    if(!saida2)
    {
        fclose(entrada1);
        fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[3]);
        return 1;
    }
 


    qtd = fread(&e,1,sizeof(Endereco),entrada1);
    while(qtd > 0)
    {
	int test = rand() %10;

	if(test % 2 ==0){ 
	   fwrite(&(e),1,sizeof(e),saida);
	}else{
	   fwrite(&(e),1,sizeof(e),saida2);
	}

        qtd = fread(&e,1,sizeof(Endereco),entrada1);
	x++;
    }
 












    fclose(entrada1);
    fclose(saida);
    return 0;
}

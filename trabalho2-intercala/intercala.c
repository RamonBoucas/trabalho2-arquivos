 #include <stdio.h>
#include <string.h>
 
#define TAMANHO 4096
 
typedef struct _Endereco Endereco;
 
struct _Endereco
{
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
    FILE *entrada1,*entrada2 ,*saida;
    char buffer[TAMANHO];
    int qtd1,qtd2;
    Endereco e1,e2;
 
    if(argc != 4)
    {
        fprintf(stderr,"Erro na chamada do comando.\n");
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM]  [ARQUIVO ORIGEM2]  [ARQUIVO DESTINO].\n", argv[0]);
        return 1;
    }
 
    entrada1 = fopen(argv[1],"rb");
    if(!entrada1)
    {
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }
 

    entrada2 = fopen(argv[2],"rb");
    if(!entrada2)
    {
    	fclose(entrada1);
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[2]);
        return 1;
    }


    saida = fopen(argv[3],"wb");
    if(!saida)
    {
        fclose(entrada1);
        fclose(entrada2);
        fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[3]);
        return 1;
    }
 
    qtd1 = fread(&(e1),1,sizeof(Endereco),entrada1);
    qtd2 = fread(&(e2),1,sizeof(Endereco),entrada2);

    int x =0;

    while((qtd1>0) && (qtd2>0)){

    	if(strncmp(e1.cep,e2.cep,8) < 0){

    		fwrite(&(e1),1,sizeof(e1),saida);
    		qtd1 = fread(&(e1),1,sizeof(Endereco),entrada1);

    	}else{

    		fwrite(&(e2),1,sizeof(e2),saida);
    		qtd2 = fread(&(e2),1,sizeof(Endereco),entrada2);

    	}

    	x++;
    }

    if(qtd1 <= 0){
        // significa que o cabeçote leu todo o arquivo 1
        while(qtd2 >0) {
            fwrite(&(e2),1,sizeof(e2),saida);
            qtd2 = fread(&(e2),1,sizeof(Endereco),entrada2);
        }

    }else if(qtd2 <= 0){
        // significa que o cabeçote leu todo o arquivo 2
        while(qtd1 > 0) {
            fwrite(&(e1),1,sizeof(e1),saida);
            qtd1 = fread(&(e1),1,sizeof(Endereco),entrada1);
        }

    }

    fclose(entrada1);
    fclose(entrada2);
    fclose(saida);
    return 0;
}
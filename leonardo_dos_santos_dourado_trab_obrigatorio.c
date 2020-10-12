#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"leonardo_dos_santos_dourado_trab_obrigatorio_biblioteca.h" //Arquivo de bibliotecas
#define HEADER_SIZE 3 //Header SIZE
#define FRAME_SIZE 4

// O arquivo leonardo_dos_santos_dourado_trab_obrigatorio_biblioteca.h contém as funções chamadas pela função principal main().

int main() {
    int header_info[HEADER_SIZE];
    int *matrix=NULL;
    int **matrix_aux=NULL;
    int **matrix_residue=NULL;
    int header_size=1;
    int i=0;
    int j=0;
    char file_dir[200];
    strcpy(file_dir,".\\");
    char filename[55];
    strcpy(filename,"Quadros.txt");
    FILE *file;
    file=fopen(strcat(file_dir,filename),"r");
    sad **sad_array=NULL;
    int op=0;
    char aux;

    if(file==NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    if(read_header(header_info,file,HEADER_SIZE)!=0)
    {
        printf("Erro!\n");
        return 1;
    }

    for(i=0;i<HEADER_SIZE;i++)
    {
        header_size*=header_info[i];
    }

    if((matrix = (int *) malloc(header_size*sizeof(int)))==NULL)
    {
        printf("Erro ao alocar a variavel matrix na mem%cria!",162);
        return 1;
    }

    if(read_matrix(matrix,header_info[0],header_info[1],header_info[2],HEADER_SIZE,file))
    {
        printf("Erro!\n");
        return 1;
    }

    if((matrix_aux = (int **) malloc(header_info[0]*sizeof(int *)))==NULL)
    {
        printf("Erro ao alocar a variavel matrix_aux na mem%cria!",162);
        return 1;
    }

    for(j=0;j<header_info[1];j++)
    {
        if((matrix_aux[j] = (int *) malloc(header_info[1]*sizeof(int)))==NULL)
        {
            printf("Erro ao alocar a variavel matrix_aux[%d] na mem%cria!",j,162);
            return 1;
        }
    }

    j=0;

    if((matrix_residue = (int **) malloc(header_info[0]*sizeof(int *)))==NULL)
    {
        printf("Erro ao alocar a variavel matrix_residue na mem%cria!",162);
        return 1;
    }

    for(j=0;j<header_info[1];j++)
    {
        if((matrix_residue[j] = (int *) malloc(header_info[1]*sizeof(int)))==NULL)
        {
            printf("Erro ao alocar a variavel matrix_residue[%d] na mem%cria!",j,162);
            return 1;
        }
    }

    j=0;

    if((sad_array=(sad **) malloc(sizeof(sad *)*(header_info[0]/2)))==NULL)
    {
        printf("Erro ao alocar a variavel sad_array na mem%cria!",162);
        return 1;
    }

    for(j=0;j<(header_info[1]-1);j++)
    {
        if((sad_array[j]=(sad *) malloc(sizeof(sad)*(header_info[1]/2)))==NULL)
        {
            printf("Erro ao alocar a variavel sad_array[%d] na mem%cria!",j,162);
            return 1;
        }
    }

    j=0;

    if(calculate_sad(matrix,matrix_aux,header_info,sad_array,FRAME_SIZE)!=0)
    {
        printf("Erro!\n");
    }

    while(1==1)
    {
        system("cls");
        printf("+------------------------------------------------------------------+\n");
        printf("|\t1- Exibir valores do MOV                                   |\n");
        printf("|\t2- Exibir matriz de res%cduos                               |\n",161);
        printf("|\t3- Sair                                                    |\n");
        printf("+------------------------------------------------------------------+\n");
        printf("\tSelecione uma das op%c%ces: ",135,228);
        scanf("%d",&op);

        switch(op)
        {
            case 1:
                {
                    printf("\n\nValores do MOV: SAD\n\n[i,j]\n");
                    for(i=0;i<(header_info[0]/2);i++)
                    {
                        for(j=0;j<(header_info[1]/2);j++)
                        {
                            printf("[%d,%d]=%d\n",sad_array[i][j].i,sad_array[i][j].j,sad_array[i][j].value);
                        }
                    }
                    printf("\n");

                    i=0;
                    j=0;
                    getchar();
                    scanf("%c",&aux);
                    continue;
                }
            case 2:
                {
                    if(calculate_residue(matrix,matrix_residue,header_info,sad_array)!=0)
                    {
                        printf("Erro!\n");
                    }

                    printf("\n\nMatriz de Res%cduos.\n\n",161);

                    for(i=0;i<header_info[0];i++)
                    {
                        for(j=0;j<header_info[1];j++)
                        {
                            printf("%d\t",matrix_residue[i][j]);
                        }
                        printf("\n");
                    }
                    i=0;
                    j=0;
                    getchar();
                    scanf("%c",&aux);
                    continue;
                }
            case 3:
                {
                    return 0;
                }
            default:
                {
                    printf("Op%c%co inv%clida!\n",135,198,160);
                    getchar();
                    scanf("%c",&aux);
                    continue;
                }
        }

    }

    free(matrix);
    free(matrix_aux);
    free(sad_array);
    free(matrix_residue);
    fclose(file);
    return 0;
}

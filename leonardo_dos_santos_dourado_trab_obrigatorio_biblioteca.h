#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct sad_var
{
    int i;
    int j;
    int value;
} sad;

int read_matrix(int *matrix,int d_x,int d_y,int n_matrix,int header_size,FILE *file);
int read_header(int *arr_header,FILE *file,int header_size);
int calculate_sad(int *matrix,int **matrix_aux,int *arr_header,sad **sad_array,int frame_size);
int get_lower_value(int **matrix_aux,int *arr_header);
int get_position_of_value(int **matrix_aux,int *arr_header,int input_value,sad *sad_array_);
int calculate_residue(int *matrix,int **matrix_residue,int *arr_header,sad **sad_array);

//Esta função lê no cabeçalho do arquivo o número de linhas e colunas e o tamanho do quadro do arquivo
int read_header(int *arr_header,FILE *file,int header_size)
{
    int header[header_size];
    int i=0;

        for(i=0;i<header_size;i++)
        {
            fscanf(file,"%d",&header[i]);

            if(feof(file))
            {
                printf("Fim do arquivo antes do final esperado!\n");
                return 1;
            }
            arr_header[i]=header[i];
        }

    return 0;
}

//Esta função lê os dados do arquivo e carrega na matriz 3d
int read_matrix(int *matrix,int d_x,int d_y,int n_matrix,int header_size,FILE *file)
{
    int i=0;
    int j=0;
    int k=0;

    for(k=0;k<n_matrix;k++)
    {
        for(i=0;i<d_x;i++)
        {
            for(j=0;j<d_y;j++)
            {
                fscanf(file,"%d",(matrix++));
                if(feof(file))
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

// Esta função calcula a SAD
int calculate_sad(int *matrix,int **matrix_aux,int *arr_header,sad **sad_array,int frame_size)
{
    int i=0;
    int j=0;
    int k=0;
    int x=0;
    int y=0;
    int z=0;
    int f0[frame_size];
    int f1[frame_size];
    int a=0;
    int b=0;
    sad *sad_array_aux=NULL;
    sad sad_array_temp;

    for(z=1;z<arr_header[2];z++)
    {
        for(x=0;x<(arr_header[0]);x+=2)
        {
            for(y=0;y<(arr_header[1]);y+=2)
            {

                f1[0]=*(matrix+(x*arr_header[1])+(y)+(arr_header[1]*arr_header[0]*(1)));
                f1[1]=*(matrix+(x*arr_header[1])+((y+1))+(arr_header[1]*arr_header[0]*(1)));
                f1[2]=*(matrix+((x+1)*arr_header[1])+(y)+(arr_header[1]*arr_header[0]*(1)));
                f1[3]=*(matrix+((x+1)*arr_header[1])+((y+1))+(arr_header[1]*arr_header[0]*(1)));

                for(k=1;k<arr_header[2];k++)
                {
                    for(i=0;i<(arr_header[0]-1);i++)
                    {
                        for(j=0;j<(arr_header[1]-1);j++)
                        {
                            f0[0]=*(matrix+(i*arr_header[1])+(j)+(arr_header[1]*arr_header[0]*(k-1)));
                            f0[1]=*(matrix+(i*arr_header[1])+((j+1))+(arr_header[1]*arr_header[0]*(k-1)));
                            f0[2]=*(matrix+((i+1)*arr_header[1])+(j)+(arr_header[1]*arr_header[0]*(k-1)));
                            f0[3]=*(matrix+((i+1)*arr_header[1])+((j+1))+(arr_header[1]*arr_header[0]*(k-1)));
                            matrix_aux[i][j]=abs(f1[0]-f0[0])+abs(f1[1]-f0[1])+abs(f1[2]-f0[2])+abs(f1[3]-f0[3]);
                        }
                    }
                    sad_array_aux=(*sad_array+(i*arr_header[1])+(j));
                    get_position_of_value(matrix_aux,arr_header,get_lower_value(matrix_aux,arr_header),sad_array_aux);
                    sad_array_temp=*sad_array_aux;
                    sad_array[a][b]=sad_array_temp;
                    sad_array[a][b].value=get_lower_value(matrix_aux,arr_header);
                }
                b++;
                if(b==(arr_header[1]/2))
                {
                    b=0;
                }
            }
            a++;
            if(a==(arr_header[0]/2))
            {
                a=0;
            }
        }
    }

    return 0;
}

//Esta função calcula o resíduo
int calculate_residue(int *matrix,int **matrix_residue,int *arr_header,sad **sad_array)
{
    int i=0;
    int j=0;
    int f1[4]={0,0,0,0};
    int v0[4]={0,0,0,0};
    int x=0;
    int y=0;
    int k=0;
    int p=0;
    int q=0;

    for(k=1;k<arr_header[2];k++)
    {
        for(i=0;i<(arr_header[0]);i+=2)
        {
            for(j=0;j<(arr_header[1]);j+=2)
            {
                f1[0]=*(matrix+(i*arr_header[1])+(j)+(arr_header[1]*arr_header[0]*(1)));
                f1[1]=*(matrix+(i*arr_header[1])+((j+1))+(arr_header[1]*arr_header[0]*(1)));
                f1[2]=*(matrix+((i+1)*arr_header[1])+(j)+(arr_header[1]*arr_header[0]*(1)));
                f1[3]=*(matrix+((i+1)*arr_header[1])+((j+1))+(arr_header[1]*arr_header[0]*(1)));

                v0[0]=*(matrix+(sad_array[p][q].i*arr_header[1])+(sad_array[p][q].j)+(arr_header[1]*arr_header[0]*(k-1)));
                v0[1]=*(matrix+(sad_array[p][q].i*arr_header[1])+((sad_array[p][q].j+1))+(arr_header[1]*arr_header[0]*(k-1)));
                v0[2]=*(matrix+((sad_array[p][q].i+1)*arr_header[1])+(sad_array[p][q].j)+(arr_header[1]*arr_header[0]*(k-1)));
                v0[3]=*(matrix+((sad_array[p][q].i+1)*arr_header[1])+((sad_array[p][q].j+1))+(arr_header[1]*arr_header[0]*(k-1)));

                matrix_residue[x][y]=(f1[0]-v0[0]);
                matrix_residue[x][y+1]=(f1[1]-v0[1]);
                matrix_residue[x+1][y]=(f1[2]-v0[2]);
                matrix_residue[x+1][y+1]=(f1[3]-v0[3]);

                y+=2;
                q++;
                if(y==(arr_header[1]))
                {
                    y=0;
                }
                if(q==5)
                {
                    p++;
                }
                if(q==((arr_header[1])/2))
                {
                    q=0;
                }
            }
            x+=2;

            if(p==(arr_header[0])/2)
            {
                p=0;
            }
        }
    }

    return 0;
}

//Esta função retorna o menor valor de uma matriz
int get_lower_value(int **matrix_aux,int *arr_header)
{
    int i=0;
    int j=0;
    int matrix_minor_value=0;

    matrix_minor_value=matrix_aux[i][j];

    for(i=0;i<(arr_header[0]-1);i++)
    {
        for(j=0;j<(arr_header[1]-1);j++)
        {
            if(matrix_aux[i][j]<matrix_minor_value)
            {
                matrix_minor_value=matrix_aux[i][j];
            }
        }
    }
    return matrix_minor_value;
}

//Esta função retorna a posição de um valor na matriz
int get_position_of_value(int **matrix_aux,int *arr_header,int input_value,sad *sad_array_)
{
    int i=0;
    int j=0;
    sad *sad_array;
    sad_array = sad_array_;

    for(i=0;i<(arr_header[0]-1);i++)
    {
        for(j=0;j<(arr_header[1]-1);j++)
        {
            if(matrix_aux[i][j]==input_value)
            {
                (*sad_array).i=i;
                (*sad_array).j=j;

                return 0;
            }
        }
    }
    printf("Nao %c igual a nenhum valor do array!\n",130);

    return 1;
}


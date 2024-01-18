#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void error_msg()
{
    printf("--------------------- Helper para o usuário --------------------------------");
    printf("Compile o codigo : gcc list_img.c user.c -o img \n");
    printf("Rode e insira as imagens a serem adicionadas as listas: img image_name.pgm image_name.pgm ... \n");
    printf("Aviso: arquivos com extensões diferentes de .pgm não são ac  \n");
    printf("-----------------------------------------------------------------------------");
}

void user_options(){
     printf("----------------------------------------------------\n");
    printf("      Operacoes possiveis para as imagens da lista: \n");
    printf("----------------------------------------------------\n");

    printf(" - Remover elemento da lista [1] \n");
    printf(" - Mostrar os elemento da lista em ordem alfabetica [2]\n");
    printf(" - Realizar o limiar das imagens [3] \n");
    printf("- Realizar a inversao das imagens [4] \n");
    printf("- Realizar o espelhamento vertical [5]\n");
    printf("- Realizar o espelhamento horizontal [6]  \n");
    printf("- Sair [0] \n");

}

int main(int argc, char *argv[])
{
    // verifica se foram passados argumentos necessários para o programa ser utilizado
    if (argc < 2)
    {
        error_msg();
        return 1;
    }

    // cria uma lista para armazenar os nomes das imagens
    dynamic_list image_list = create_list();

    /* percorre a lista das imagens e faz a verificação se elas possuem a extensão .pgm 

    Se for .pgm elas são inseridas e já se utilizam da função de inserir o elemento ordenado

    */

    for (int i = 1; i < argc; i++)
    {
        if (end_in_pgm(argv[i]) == 1)
        {
            add_element(image_list, argv[i]);
        }
        else
        {
            error_msg();
            return 1;
        }
    }

    // após a inserção delas mostra a lista com as imagens inseridas 
    printf("Lista das imagens inseridas: \n");
    show_list(image_list);

    // função de opções para o usuário
    user_options();
   
    int operacao;
    scanf("%d", &operacao);

    // tag com os finais dos arquivos conforme as opções 
    char *tag_operations[] = {"_limiar", "_invertido", "_espelhado_vertical", "_espelhado_horizontal"};

    // switch para cada opção 
    switch (operacao)
    {
        // Sair do programa 
    case 0:
        printf("Programa finalizado!");
        break;
        return 0;

    case 1:
        // Remoção dos elementos 
        /*
        recebe o nome da imagem a ser removida e utiliza a função de remove -> passando a lista e o elemento em questão 
        * Depois de remover o elemento a lista é retornada para o usuário 
        */
        printf("Qual elemento será removido? ");
        char item_a_ser_removido[100];
        scanf("%s", &item_a_ser_removido);
        remove_key(image_list, item_a_ser_removido);
        printf("Lista Atual: \n");
        show_list(image_list);
        break;

    case 2:
        // mostrar as imagens inseridas 
        printf("Lista das imagens inseridas: ");
        show_list(image_list);
        break;

    case 3:
    // limiarização das imagens 
    /*
    Abre o arquivo da imagem passada 
    Aplica o filtro de limiarização na imagem e salva em um novo arquivo -> aplica o valor de limiar passado pelo usuário 
    Concatena o nome da imagem com a tag especifica e depois escreve a imagem limiarizada 
    depois se libera a memória da imagem
    */
        for (int i = 1; i < argc; i++)
        {
            FILE *pgm = fopen(argv[i], "r");
            if (pgm != NULL)
            {
                image_data image = read_img(pgm);
                printf("Valor limiar: ");
                int valor_limiar;
                scanf("%d", &valor_limiar);
                limiar(&image, valor_limiar);
                char *final_name = strtok(argv[i], ".");
                strcat(final_name, tag_operations[0]);
                strcat(final_name, ".pgm");
                write_img(final_name, &image);

                free_img(&image);
                fclose(pgm);
                printf("Download realizado!")
            }

            else
            {
                printf("Falha na leitura do arquivo.\n");
            }
        }
        break;
    case 4:
    // inversão da imagem
    /*
    Abre o arquivo da imagem passada
    Inverte os valores das cores -> como a imagem pgm são de tons de branco e preto eles são invertidos 
    Concatena o nome da imagem com a tag especificada e depois escreve a imagem invertida
    depois se libera a memoria da imagem
    */
        for (int i = 1; i < argc; i++)
        {
            FILE *pgm = fopen(argv[i], "r");
            if (pgm != NULL)
            {
                image_data image = read_img(pgm);
                fclose(pgm);

                char *final_name = strtok(argv[i], ".");
                strcat(final_name, tag_operations[1]);
                strcat(final_name, ".pgm");

                image_data inverted_img = invert_img(&image);
                write_inverted_img(final_name, &inverted_img, &image);

                free_img(&image);
                free_inverted_img(&inverted_img);
                printf("Download realizado!")
            }
            else
            {
                printf("Arquivo não lido!.\n");
            }
        }
        break;
    case 5:
    // espelhamento vertical 
    /*
    Abre o arquivo da imagem passada
    Espelha as linhas da imagem para baixo
    Concatena o nome da imagem com a tag especificada e depois escreve a imagem espelhada verticalmente 
    depois se libera a memoria da imagem
    */
        for (int i = 1; i < argc; i++)
        {
            FILE *pgm = fopen(argv[i], "r");
            if (pgm != NULL)
            {
                image_data image = read_img(pgm);

                vertical_mirror_img(&image);
                char *final_name = strtok(argv[i], ".");
                strcat(final_name, tag_operations[2]);
                strcat(final_name, ".pgm");
                write_img(final_name, &image);

                free_img(&image);
                fclose(pgm);
                printf("Download realizado!")
            }

            else
            {
                printf("Falha na leitura do arquivo.\n");
            }
        }
        break;
    case 6:
    // espelhamento horizontal 
    /*
    Abre o arquivo da imagem passada
    Espelha as colunas da imagem 
    Concatena o nome da imagem com a tag especificada e depois escreve a imagem espelhada horizontalmente
    depois se libera a memoria da imagem
    */
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *pgm = fopen(argv[i], "r");
            if (pgm != NULL)
            {
                image_data image = read_img(pgm);

                horizontal_mirror_img(&image);

                char *final_name = strtok(argv[i], ".");
                strcat(final_name, tag_operations[3]);
                strcat(final_name, ".pgm");
                write_img(final_name, &image);

                free_img(&image);
                fclose(pgm);
                printf("Download realizado!")
            }

            else
            {
                printf("Falha na leitura do arquivo.\n");
            }
        }
    }
    break;
    default:
        printf("Opção invalida!");
    }
    //libera a memória da lista 
    free_list(image_list);
}

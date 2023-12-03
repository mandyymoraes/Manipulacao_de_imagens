#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// função que cria a lista dinamica 
dynamic_list create_list()
{
    // alocação da memória da estrutura da lista criada
    dynamic_list img_list = malloc(sizeof(struct Dynamic_list));
    if (img_list == NULL)
    {
        printf("A lista passada foi retornada como NULL");
        abort();
    }
    img_list->start = NULL;
    return img_list;
}

// insere os elementos passados já na ordem alfabetica
void add_element(dynamic_list lista, char *elemento)
{
    // aloca memória para todos os elementos inseridos e verifica se eles não são nulos
    list_element novo_elemento = malloc(sizeof(list_element));
    // verifica se o elemento não é vazio
    if (novo_elemento == NULL)
    {
        printf("Elemento com valor NULL\n");
        return;
    }

    // o elemento a ser criado tem como valor atribuido a cópia do conteúdo do parametro que vai ser inserido
    novo_elemento->value = strdup(elemento);
    // assim que ele é inserido seu proximo elemento é atribuido como NULL
    novo_elemento->next_value = NULL;


    /* Inserção no inicio da lista -> quando a lista está vazia e o elemento passado vai ser o primeiro a ser inserido 
    é feita a identificação do começo dela ( se o inicio da lista está vazio, logicamente ele será o primeiro elemento
    a ser inserido)
    
     Além disso há a ordenação dos elementos pela ordem alfabética -> pela strcmp se a string ao ser comparada com as outras
     strings da lista retornar uma valor > 0 (ela é "menor" ou seja, vem antes da palavra comparada)
     
     Assim, como o elemento virá antes da string já inserida, ela é mudada de lugar para se inserir o elemento em questão
     no seu devido lugar
    */
    if (lista->start == NULL || strcmp(lista->start->value, elemento) > 0)
    {
        
        novo_elemento->next_value = lista->start;
        lista->start = novo_elemento;
    }
    else
    {
        /*Inserção depois do inicio da lista 
            Se o retorno da strcmp for < 0 ( ela é "maior" ou seja, vem depois da palavra comparada)
            Assim é feita uma iteração até o final da lista (condição de parada sendo o retorno > 0, que indica que a palavra
            passada é "menor" que a string já inserida, assim podendo inserir a string na colocação correta)
        */
       
        list_element atual = lista->start;
        while (atual->next_value != NULL && strcmp(atual->next_value->value, elemento) < 0)
        {
            atual = atual->next_value;
        }

        novo_elemento->next_value = atual->next_value;
        atual->next_value = novo_elemento;
    }
}

// função que percorre e mostra os elementos da lista
void show_list(dynamic_list lista)
{
    // verificação se a lista possue elementos 
    if (empty_list(lista))
    {
        printf("Lista NULL.\n");
        return;
    }

    // percorre a lista até o seu final, mostrando o valor atual e depois passando para o proximo elemento
    list_element atual = lista->start;
    while (atual != NULL)
    {
        printf(" '%s', ", atual->value);
        atual = atual->next_value;
    }
    printf("\n");
}

// verificação se a lista não é NULL -> evitar possiveis acessos indevidos de memória
bool empty_list(dynamic_list lista)
{
    return (lista->start == NULL);
}

// remove a string passada 
void remove_key(dynamic_list lista, char *string)
{
    if (lista == NULL || lista->start == NULL)
    {
        printf("Lista NULL ou sem nenhum elemento\n");
        return;
    }

    list_element atual = lista->start;
    list_element anterior = NULL;

    /*
    Itera até o final da lista e utiliza da strcmp para comparação, se o valor retornado = 0 (string é uma comparação exata)
    assim ela é removida

    - Se o elemento a ser removido estiver no inicio da lista, é indicado para a variavel start que ela se inicia no proximo 
    elemento
    
    - Se o elemento estiver após o primeiro elemento é feita a transformação de que, o ponteiro do proximo elemento do elemento
    anterior ao retirado é redirecionado ao proximo elemento que era referenciado pelo elemento removido

    - Depois há a liberação da memória do valor do elemento e da sua estrutura

    */
    while (atual != NULL)
    {
        if (strcmp(atual->value, string) == 0)
        {
            printf("A imagem %s foi removida da lista \n", string);

            if (anterior == NULL)
            {
                lista->start = atual->next_value;
            }
            else
            {
                anterior->next_value = atual->next_value;
            }

            free(atual->value);
            free(atual);

            return; 
        }

        // Se a string não for encontrada a lista continua inalterada

        anterior = atual;
        atual = atual->next_value;
    }

    printf("String não encontrada na lista\n");
}

/* liberação da memória da estrutura da lista e de seus elementos

    - mesma sintaxe da função show_list -> lista é percorrida até o final e a memória dos seus elementos é liberada
*/
void free_list(dynamic_list lista)
{
    list_element atual = lista->start;
    list_element proximo;

    while (atual != NULL)
    {
        proximo = atual->next_value;
        free(atual->value);
        free(atual);
        atual = proximo;
    }

    free(lista);
}

//--------------------- Manipulação da imagem ----------------------------------------

int end_in_pgm(char *entrada)
{
    // o interesse a ser comparado é a porção após o ".", assim ele é separado para ser utilizado como delimitador
    char *ponto = strchr(entrada, '.');

    if (ponto != NULL)
    {
        // Comparar a parte após o ponto com "pgm"
        if (strcmp(ponto + 1, "pgm") == 0)
        {
            return 1; // Retorna 1 se a extensão for "pgm"
        }
    }

    return 0; // Retorna 0 se a extensão não for "pgm"
}


image_data read_img(FILE *img_file)
{
    // leitura da imagem
    image_data image; // declara a imagem

    // recebe os valores da altura, largura e tons de cinza da imagem
    char ver[5];
    fscanf(img_file, "%s", ver);

    fscanf(img_file, "%d ", &image.height);
    fscanf(img_file, "%d ", &image.width);
    fscanf(img_file, "%d ", &image.gray_scale);

    // aloca memoria para os pixels da imagem se baseando na largura dela

    image.pixel = malloc(image.height * image.width * sizeof(int));

    // valida se o valor dos pixels é diferente de nulo para assim realizar a função
    if (image.pixel != NULL)
    {

        // percorre toda a imagem pela altura e largura
        for (int i = 0; i < image.height; i++)
        {
            for (int j = 0; j < image.width; j++)
            {
                // le o pixel da imagem, se baseia no endereço da coluna do pixel multiplicado pela largura da imagem para assim a cada iteração percorrer
                // toda a linha e a soma do valor j se aplica para passar para a linha de baixo na proxima iteração
                fscanf(img_file, "%d ", &image.pixel[i * image.width + j]);
            }
        }
    }
    else
    {
        printf("Memoria nao alocada!\n");
        exit(EXIT_FAILURE);
    }
    return image;
}


void free_img(image_data *image)
{
    /*
    Percorre a imagem liberando a memória do conteúdo de seus pixels
    */
    if (image->pixel != NULL)
    {
        free(image->pixel);
        image->pixel = NULL;
    }
}

void limiar(image_data *image, int limiar)
{

    // verifica se o valor dos pixels é diferente de nulo
    if (image->pixel != NULL)
    {
        // percorre a imagem pela largura e altura dela
        for (int i = 0; i < image->height; i++)
        {
            for (int j = 0; j < image->width; j++)
            {
                // se o valor do pixel a ser analisado no caso se mostra a mesma logica da função de leitura
                // é pego a o valor da linha em questão e se multiplica pelo valor da largura e se soma com o valor da coluna para analisar os outros pixels subsequentes na iteração
                // se o valor do pixel for menor que o valor do limiar em questão o pixel troca seu valor para 0 -> representando o inverso da cor
                if (image->pixel[i * image->width + j] < limiar)
                {
                    image->pixel[i * image->width + j] = 0;
                    // se não for menor que o limiar o pixel vira a tonalidade de cinza passada para a imagem
                }
                else
                {
                    image->pixel[i * image->width + j] = image->gray_scale;
                }
            }
        }
    }
    else
    {
        printf("Imagem retornada como NULL");
    }
}

// "escreve" a imagem passada -> cria um arquivo e atribui os valores dos pixels e caracteristicas da imagem nele
void write_img(char *arq_name, image_data *image)
{
    // abre o arquivo passado (string criada com as tags) -> e escreve os valores da imagem já modificada
    /*
        escreve os elementos da imagem .pgm (altura, largura e tonalidades de cinza)
        percorre a imagem inteira e escreve o valor dos pixels já modificados 
    */
    FILE *fp = fopen(arq_name, "w");
    if (fp != NULL)
    {
        if (image->pixel != NULL)
        {
            fprintf(fp, "P2\n");
            fprintf(fp, "%d %d\n", image->height, image->width);
            fprintf(fp, "%d\n", image->gray_scale);
            for (int i = 0; i < image->height; i++)
            {
                for (int j = 0; j < image->width; j++)
                {
                    fprintf(fp, "%d ", image->pixel[i * image->width + j]);
                }
                fprintf(fp, "\n");
            }
        }
        else
        {
            printf("Imagem retornada NULL\n");
        }
        fclose(fp);
    }
    else
    {
        printf("Arquivo de saida eh NULL\n");
    }
}

// inverte os valores de uma imagem passada
image_data invert_img(image_data *image)
{
    // declara uma outra imagem para ser a imagem invertida
    image_data inverted_img;
    // recebe o valor de altura largura e cinza da imagem a ser invertida como os valores da imagem que foi passada para ser invertida
    inverted_img.height = image->height;
    inverted_img.width = image->width;
    inverted_img.gray_scale = image->gray_scale;
    // aloca a memoria para a imagem criada
    inverted_img.pixel = malloc(image->height * image->width * sizeof(int));
    // verifica se seu valor não é nulo para iniciar a operação
    if (inverted_img.pixel != NULL)
    {
        // percorre toda a imagem pela largura e altura
        for (int i = 0; i < image->height; i++)
        {
            for (int j = 0; j < image->width; j++)
            {
                // o pixel da imagem a ser invertida (linha * largura da imagem + coluna que está sendo percorrida -> permite que conforme as interações outras colunas sejão lidas)
                // ele é igual ao valor de cinza passado para a imagem inicial - o pixel correspondente na imagem dada
                // permite que o valor seja invertido -> se o pixel for branco ele será 0 -> então ele será tirado do cinza - e assim ficara preto
                // e se o pixel for preto ele será tirado do valor de cinza -> assim ficando branco
                inverted_img.pixel[i * image->width + j] = image->gray_scale - image->pixel[i * image->width + j];
            }
        }
    }
    else
    {
        printf("Memoria nao alocada!\n");
        exit(EXIT_FAILURE);
    }
    return inverted_img;
}

// percorre a imagem invertida liberando a memória do seu conteudo
void free_inverted_img(image_data *inverted_img)
{
    if (inverted_img->pixel != NULL)
    {
        free(inverted_img->pixel);
        inverted_img->pixel = NULL;
    }
}

// "escreve" a imagem invertida, atribuindo os valores dos pixels correspondentes
void write_inverted_img(char *arq_name, image_data *inverted_img, image_data *image)
{
    // escreve o arquivo com o nome passado
    FILE *ii = fopen(arq_name, "w");
    // verifica se ele não é nulo
    if (ii != NULL)
    {
        if (image->pixel != NULL)
        {
            // escreve as caracteristicas da imagem
            fprintf(ii, "P2\n");
            // escreve a altura e largura da imagem
            fprintf(ii, "%d %d\n", inverted_img->height, inverted_img->width);
            // escreve as tonalidades de cinza
            fprintf(ii, "%d\n", inverted_img->gray_scale);
            // percorre a imagem e escreve os valores de cada pixel
            for (int i = 0; i < inverted_img->height; i++)
            {
                for (int j = 0; j < inverted_img->width; j++)
                {
                    // escreve no arquivo os pixels invertidos
                    fprintf(ii, "%d ", inverted_img->pixel[i * inverted_img->width + j]);
                }
                // finaliza a imagem com um /n
                fprintf(ii, "\n");
            }
        }
        else
        {
            printf("Imagem retornada NULL\n");
        }
        fclose(ii);
    }
    else
    {
        printf("Erro na criacao da imagem invertida\n");
    }
}

void vertical_mirror_img(image_data *image)
{
    if (image->pixel != NULL)
    {
        // percorre a imagem -> no espelhamento vertical se percorre até a sua metade apenas por conta da troca dos pixels posteriormente
        for (int i = 0; i < image->height / 2; i++)
        {
            for (int j = 0; j < image->width; j++)
            {
                /*
                A imagem é separada em indices superiores e inferiores que são correspondentes,
                assim os indices são trocados para executar o espelhamento
                */
                int indice_superior = i * image->width + j;
                int indice_inferior = (image->height - 1 - i) * image->width + j;

                // Troca os pixels nas linhas opostas
                int temp = image->pixel[indice_superior];
                image->pixel[indice_superior] = image->pixel[indice_inferior];
                image->pixel[indice_inferior] = temp;
            }
        }
    }
    else
    {
        printf("Imagem retornada como NULL");
    }
}

// inverter horizontalmente uma imagem
void horizontal_mirror_img(image_data *image)
{

    if (image->pixel != NULL)
    {
        // percorre a imagem pela altura e largura /2 dela -> se divide a largura por 2 por conta que ela será invertida horizontalmente 
        for (int i = 0; i < image->height; i++)
        {
            for (int j = 0; j < image->width / 2; j++)
            {
                // atribui os pixels correspondentes com a esquerda e a direita da imagem
                int indice_esquerda = i * image->width + j;
                int indice_direita = i * image->width + (image->width - 1 - j);

                // realiza a troca dos pixels correspondentes com uso de auxiliar para inverter os valores 
                int temp = image->pixel[indice_esquerda];
                image->pixel[indice_esquerda] = image->pixel[indice_direita];
                image->pixel[indice_direita] = temp;
            }
        }
    }
    else
    {
        printf("Imagem retornada como NULL");
    }
}

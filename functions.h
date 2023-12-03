#include <stdbool.h>

// ------------- Declaração dos Structs  ------------------

//Struct para a estrutura dos elementos da lista dinamica -> referencia o valor do elemento e o seu referenciamento para o próximo elemento da lista
struct List_element {
    char *value;
    struct List_element *next_value;
};

typedef struct List_element *list_element;

// struct da lista em si -> obtem o começo e o indice de final dela
struct Dynamic_list {
    list_element start;
    int end_position;

};

typedef struct Dynamic_list *dynamic_list;

// struct que cria a estrutura da imagem -> largura, altura, tonalidade e conteúdo dos seus pixels
typedef struct {
    int height, width; 
    int gray_scale; 
    int *pixel;  
} image_data;


//------------------------Funções de manipulação de listas dinamicas ----------------------------------
// função que cria a lista
dynamic_list create_list();

// verifica se a lista tem espaço para inserir elementos 
bool full_list(dynamic_list lista);

// insere os elementos passados e já os ordena em ordem alfabética 
void add_element(dynamic_list lista, char *elemento);

// percorre e mostra os elementos da lista 
void show_list(dynamic_list lista);

// verifica se a lista não tem nenhum elemento
bool empty_list(dynamic_list lista);

// pesquisa e remove da lista a string passada 
void remove_key(dynamic_list lista, char *string);

// libera a memória da estrutura da lista 
void free_list(dynamic_list lista);

//------------------------------------------------------------------

// ------------------- Funções com relação a manipulação das imagens ----------------------

// verifica a extensão da imagem passada
int end_in_pgm(char *string);

// função e leitura da imagem e do conteudo dela 
image_data read_img(FILE *img_file);

// função que realiza a operação de limiar 
void limiar(image_data *img, int valor_limiar);

// função que escreve os pixels da imagem
void write_img(char *img_name, image_data *img);

// função que realiza a operação de inverter a imagem
image_data invert_img(image_data *img);

//função que escreve os pixels das imagens invertidas
void write_inverted_img(char *img_name, image_data *inverted_image, image_data *original_image);

// função que realiza o espelhamento vertical
void vertical_mirror_img(image_data *img);

// função que realiza o espelhamento horizontal
void horizontal_mirror_img(image_data *img);

// libera a memória da imagem
void free_img(image_data *img);

// libera a memória da imagem invertida
void free_inverted_img(image_data *inverted_image);



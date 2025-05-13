#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) {
  for (int i = 0 ; i < 9 ; i++) {
    for (int j = 0 ; j < 9 ; j++) {
      if (n->sudo[i][j] != 0) {
        int num = n->sudo[i][j];
        n->sudo[i][j] = 0;

        // Verificar fila y columna
        for (int k = 0 ; k < 9 ; k++) {
          if (n->sudo[i][k] == num || n->sudo[k][j] == num) {
            n->sudo[i][j] = num;
            return 0;
          }
        }

        // Verificar subcuadrícula de 3x3
        for (int k = 0 ; k < 9 ; k += 3) {
          for (int l = 0 ; l < 9 ; l += 3) {
            int test[10] = {0};
            for (int m = k ; m < k + 3 ; m++) {
              for (int p = l ; p < l + 3 ; p++) {
                if (n->sudo[m][p] != 0) { // Usar m y p en lugar de k y l
                  if (test[n->sudo[m][p]] == 1) return 0;
                  test[n->sudo[m][p]] = 1;
                }
              }
            }
          }
        }

        n->sudo[i][j] = num; // Restaurar el valor original
      }
    }
  }

  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
     for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) { 
                for (int num = 1; num <= 9; num++) { 
                    n->sudo[i][j] = num;
                    Node* new_node = copy(n);
                    if (is_valid(new_node)) { 
                        pushBack(list, new_node); 
                    } else {
                        free(new_node); 
                    }
                }
                n->sudo[i][j] = 0; 
                return list;
            }
        }
    }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
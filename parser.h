#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct array {
  int count_vert;
  int count_facets;
  double *vertexes;
  unsigned int *facets;
  double max_vert;
} array_data;

int array(array_data *obj, char *filepath);
int index1(array_data *obj, char *filepath);
int allocate_memory(array_data *obj, char *filepath);
int count_facetes_token(char *str);

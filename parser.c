#include "parser.h"

// int main() {
//   array_data obj = {0, 0, 0, 0, 0};
//   allocate_memory(&obj, "heart.obj");
//   array(&obj, "heart.obj");
//   index1(&obj, "heart.obj");
//   for (int i = 0; i <= obj.count_vert - 1; i++) {
//     printf("%f, ", obj.vertexes[i]);
//   }
//   printf("\n\n");
//   for (int i = 0; i <= obj.count_facets - 1; i++) {
//     printf("%d, ", obj.facets[i]);
//   }
// }

int allocate_memory(array_data *obj, char *filepath) {
  int err = 0;
  FILE *file;
  char str[512];
  if ((file = fopen(filepath, "r")) != NULL) {
    while (fgets(str, 256, file) != NULL) {
      if ((str[0] == 'v') && str[1] == ' ') {
        obj->count_vert += 3;
      } else if ((str[0] == 'f') && str[1] == ' ') {
        obj->count_facets += count_facetes_token(str);
      }
    }
    obj->count_facets *= 2;
  } else {
    printf("He удалось открыть файл");
    err = 1;
  }
  return err;
}

int count_facetes_token(char *str) {
  int result = 0;
  for (int i = 0; str[i]; i++) {
    if (str[i] == ' ' && str[i + 1] <= '9' && str[i + 1] >= '0') result += 1;
  }
  return result;
}

int array(array_data *obj, char *filepath) {
  int err = 0;
  FILE *file;
  char str[512];
  int num = 0;
  if ((obj->vertexes = calloc(obj->count_vert, sizeof(double))) != NULL) {
    if ((file = fopen(filepath, "r")) != NULL) {
      while (fgets(str, 256, file) != NULL) {
        if ((str[0] == 'v') && str[1] == ' ') {
          for (int i = 0; str[i]; i++) {
            char buf[10] = "\0";
            int k = 0;
            while ((str[i] <= '9' && str[i] >= '0') || str[i] == '-' ||
                   str[i] == '.') {
              buf[k] = str[i];
              k++;
              i++;
            }
            char *tmp;
            if (*buf != 0) {
              obj->vertexes[num] = strtod(buf, &tmp);
              if (fabs(obj->vertexes[num]) > obj->max_vert)
                obj->max_vert = fabs(obj->vertexes[num]);
              num++;
            }
            *buf = 0;
          }
        }
      }
      fclose(file);
    } else {
      printf("%s, ", "File doesn't exist");
      err = 1;
    }
  } else {
    err = 1;
  }
  return err;
}

int index1(array_data *obj, char *filepath) {
  int err = 0;
  FILE *file;
  char str[512];
  int first = -1;
  int index_num = 0;
  if ((obj->facets = calloc(obj->count_facets, sizeof(int))) != NULL) {
    if ((file = fopen(filepath, "r")) != NULL) {
      while (fgets(str, 256, file) != NULL) {
        int check = 0;
        if ((str[0] == 'f') && str[1] == ' ') {
          for (int i = 1; str[i]; i++) {
            char buf[10] = "\0";
            int k = 0;
            if (str[i - 1] == ' ' && str[i] >= '0' && str[i] <= '9') {
              while (str[i] <= '9' && str[i] >= '0') {
                buf[k] = str[i];
                k++;
                i++;
              }
            }
            char *tmp;
            int number = strtod(buf, &tmp) - 1;
            if (*buf != 0) {
              if (check == 0) {
                if (first != -1) {
                  obj->facets[index_num] = first;
                  index_num++;
                }
                first = number;
              } else {
                obj->facets[index_num] = number;
                index_num++;
              }
              obj->facets[index_num] = number;
              index_num++;
              check = 1;
            }
          }
        }
      }
      obj->facets[index_num] = first;
      fclose(file);
    } else {
      printf("%s, ", "File doesn't exist");
      err = 1;
    }
  } else {
    err = 1;
  }
  return err;
}

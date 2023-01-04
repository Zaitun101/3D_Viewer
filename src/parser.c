#include "parser.h"

// int main() {
//   // array_data obj = {0, 0, 0, 0, 0};
//   // allocate_memory(&obj, "../obj/cube.obj");
//   // array(&obj, "../obj/cube.obj");
//   // index1(&obj, "../obj/cube.obj");
//   // for (int i = 0; i <= obj.count_vert - 1; i++) {
//   //   printf("%f, ", obj.vertexes[i]);
//   // }
//   // printf("\n\n");
//   // for (int i = 0; i <= obj.count_facets - 1; i++) {
//   //   printf("%d, ", obj.facets[i]);
//   // }
//   // free(obj.facets);
//   // free(obj.vertexes);
//   int test_array[60] = {0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3,
//                         2, 2, 0, 0, 1, 1, 3, 3, 0, 2, 7, 7, 6, 6, 2,
//                         2, 3, 3, 7, 7, 2, 4, 6, 6, 7, 7, 4, 4, 7, 7,
//                         5, 5, 4, 0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 0};
//   char *file_path = "../obj/cube.obj";
//   array_data obj = {0, 0, 0, 0, 0};
//   allocate_memory(&obj, file_path);
//   index1(&obj, file_path);
//   printf("%d", obj.count_facets);
//   for (int i = 0; i < obj.count_facets; i++) {
//     printf("%d - %d \n", obj.facets[i], test_array[i]);
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
    fclose(file);
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
  obj->max_vert = 0;
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
            if (*buf != 0) {
              obj->vertexes[num] = atof(buf);
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
  change_scale(obj, 1 / obj->max_vert, 1);
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
            int number = atof(buf) - 1;
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

void change_scale(array_data *obj, double scale, double prev_scale) {
  for (int i = 0; i < obj->count_vert; i++) {
    obj->vertexes[i] /= prev_scale;
    obj->vertexes[i] *= scale;
  }
}

void move_obj(array_data *obj, double xPos, double prev_xPos, double yPos,
              double prev_yPos, double zPos, double prev_zPos) {
  int k = 0;
  for (int i = 0; i <= obj->count_vert; i++) {
    if (k == 0) {
      obj->vertexes[i] -= prev_xPos;
      obj->vertexes[i] += xPos;
    } else if (k == 1) {
      obj->vertexes[i] -= prev_yPos;
      obj->vertexes[i] += yPos;
    } else if (k == 2) {
      obj->vertexes[i] -= prev_zPos;
      obj->vertexes[i] += zPos;
    }
    k++;
    if (k == 3) k = 0;
  }
}

void rot_x(array_data *obj, double x_rot) {
  for (int i = 0; i < obj->count_vert; i += 3) {
    double temp_y = obj->vertexes[i + 1];
    double temp_z = obj->vertexes[i + 2];
    obj->vertexes[i + 1] = cos(x_rot) * temp_y - sin(x_rot) * temp_z;
    obj->vertexes[i + 2] = sin(x_rot) * temp_y + cos(x_rot) * temp_z;
  }
}

void rot_y(array_data *obj, double y_rot) {
  for (int i = 0; i < obj->count_vert; i += 3) {
    double temp_x = obj->vertexes[i];
    double temp_z = obj->vertexes[i + 2];

    obj->vertexes[i] = cos(y_rot) * temp_x + sin(y_rot) * temp_z;
    obj->vertexes[i + 2] = -sin(y_rot) * temp_x + cos(y_rot) * temp_z;
  }
}

void rot_z(array_data *obj, double z_rot) {
  for (int i = 0; i < obj->count_vert; i += 3) {
    double temp_x = obj->vertexes[i];
    double temp_y = obj->vertexes[i + 1];

    obj->vertexes[i] = cos(z_rot) * temp_x - sin(z_rot) * temp_y;
    obj->vertexes[i + 1] = sin(z_rot) * temp_x + cos(z_rot) * temp_y;
  }
}

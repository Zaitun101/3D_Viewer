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
void change_scale(array_data *obj, double scale, double prev_scale);
void move_obj(array_data *obj, double xPos, double prev_xPos, double yPos,
              double prev_yPos, double zPos, double prev_zPos);
void rot_x(array_data *obj, double x_rot);
void rot_y(array_data *obj, double y_rot);
void rot_z(array_data *obj, double z_rotvoid);
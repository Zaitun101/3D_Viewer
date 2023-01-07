// Copyright [2022] <Smithjan>
#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./parser.h"

START_TEST(allocate) {
  char *file_path = "../obj/cube.obj";
  array_data obj = {0, 0, 0, 0, 0};
  int err = allocate_memory(&obj, file_path);
  ck_assert_int_eq(obj.count_vert, 24);
  ck_assert_int_eq(obj.count_facets, 60);
  ck_assert_int_eq(err, 0);
  err = allocate_memory(&obj, "../file_not_exist");
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(vertexes) {
  double test_array[24] = {0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
                           1.000000, 0.000000, 1.000000, 0.000000, 0.000000,
                           1.000000, 1.000000, 1.000000, 0.000000, 0.000000,
                           1.000000, 0.000000, 1.000000, 1.000000, 1.000000,
                           0.000000, 1.000000, 1.000000, 1.000000};
  char *file_path = "../obj/cube.obj";
  array_data obj = {0, 0, 0, 0, 0};
  allocate_memory(&obj, file_path);
  array(&obj, file_path);
  for (int i = 0; i < obj.count_vert; i++) {
    ck_assert_double_eq(obj.vertexes[i], test_array[i]);
  }
  free(obj.vertexes);
}
END_TEST

START_TEST(indexes) {
  double test_array[60] = {0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3,
                           2, 2, 0, 0, 1, 1, 3, 3, 0, 2, 7, 7, 6, 6, 2,
                           2, 3, 3, 7, 7, 2, 4, 6, 6, 7, 7, 4, 4, 7, 7,
                           5, 5, 4, 0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 0};
  char *file_path = "../obj/cube.obj";
  array_data obj = {0, 0, 0, 0, 0};
  allocate_memory(&obj, file_path);
  index1(&obj, file_path);
  for (int i = 0; i < obj.count_facets; i++) {
    ck_assert_int_eq(obj.facets[i], test_array[i]);
  }
  free(obj.facets);
}
END_TEST

START_TEST(scale) {
  double test_array[24] = {0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
                           1.000000, 0.000000, 1.000000, 0.000000, 0.000000,
                           1.000000, 1.000000, 1.000000, 0.000000, 0.000000,
                           1.000000, 0.000000, 1.000000, 1.000000, 1.000000,
                           0.000000, 1.000000, 1.000000, 1.000000};
  char *file_path = "../obj/cube.obj";
  array_data obj = {0, 0, 0, 0, 0};
  allocate_memory(&obj, file_path);
  array(&obj, file_path);
  index1(&obj, file_path);
  change_scale(&obj, 2, 1);
  for (int i = 0; i < obj.count_vert; i++) {
    ck_assert_double_eq(obj.vertexes[i], test_array[i] * 2);
  }
  free(obj.vertexes);
  free(obj.facets);
}
END_TEST

START_TEST(move) {
  double test_array[24] = {0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
                           1.000000, 0.000000, 1.000000, 0.000000, 0.000000,
                           1.000000, 1.000000, 1.000000, 0.000000, 0.000000,
                           1.000000, 0.000000, 1.000000, 1.000000, 1.000000,
                           0.000000, 1.000000, 1.000000, 1.000000};
  char *file_path = "../obj/cube.obj";
  array_data obj = {0, 0, 0, 0, 0};
  allocate_memory(&obj, file_path);
  array(&obj, file_path);
  index1(&obj, file_path);
  move_obj(&obj, 2, 1, 2, 1, 2, 1);
  for (int i = 0; i < obj.count_vert; i++) {
    ck_assert_double_eq(obj.vertexes[i], test_array[i] + 1);
  }
  free(obj.vertexes);
  free(obj.facets);
}
END_TEST

START_TEST(rotate) {
  double test_array[24] = {0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
                           1.000000, 0.000000, 1.000000, 0.000000, 0.000000,
                           1.000000, 1.000000, 1.000000, 0.000000, 0.000000,
                           1.000000, 0.000000, 1.000000, 1.000000, 1.000000,
                           0.000000, 1.000000, 1.000000, 1.000000};
  char *file_path = "../obj/cube.obj";
  array_data obj = {0, 0, 0, 0, 0};
  allocate_memory(&obj, file_path);
  array(&obj, file_path);
  index1(&obj, file_path);
  for (int i = 0; i < 24; i += 3) {
    double temp_y = test_array[i + 1];
    double temp_z = test_array[i + 2];
    test_array[i + 1] = cos(2) * temp_y - sin(2) * temp_z;
    test_array[i + 2] = sin(2) * temp_y + cos(2) * temp_z;
  }
  rot_x(&obj, 2);
  for (int i = 0; i < obj.count_vert; i++) {
    ck_assert_double_eq(obj.vertexes[i], test_array[i]);
  }
  for (int i = 0; i < 24; i += 3) {
    double temp_x = test_array[i];
    double temp_z = test_array[i + 2];
    test_array[i] = cos(2) * temp_x + sin(2) * temp_z;
    test_array[i + 2] = -sin(2) * temp_x + cos(2) * temp_z;
  }
  rot_y(&obj, 2);
  for (int i = 0; i < obj.count_vert; i++) {
    ck_assert_double_eq(obj.vertexes[i], test_array[i]);
  }

  for (int i = 0; i < 24; i += 3) {
    double temp_x = test_array[i];
    double temp_y = test_array[i + 1];

    test_array[i] = cos(2) * temp_x - sin(2) * temp_y;
    test_array[i + 1] = sin(2) * temp_x + cos(2) * temp_y;
  }
  rot_z(&obj, 2);
  for (int i = 0; i < obj.count_vert; i++) {
    ck_assert_double_eq(obj.vertexes[i], test_array[i]);
  }
  free(obj.vertexes);
  free(obj.facets);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, allocate);
  tcase_add_test(tc1_1, vertexes);
  tcase_add_test(tc1_1, indexes);
  tcase_add_test(tc1_1, scale);
  tcase_add_test(tc1_1, move);
  tcase_add_test(tc1_1, rotate);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}

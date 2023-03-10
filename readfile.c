#include "readfile.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int readobj(char* file_name, obj_t* obj) {
  int err = -1;
  FILE* file;
  file = fopen(file_name, "r");
  if (file) {
    obj->count_of_facets = 0;
    obj->count_of_vertexes = 0;
    char ch = ' ';
    int cur_index = 0;
    const char* space = " ";
    const char* slash = "/";
    char *temp_str, *token, *str1, *str2, *subtoken, *saveptr2;
    int* temp_indexes = NULL;
    int i = 0, j = 0, p = 0, v_count = 0, dots = 0;

    while (1) {
      char buf[255] = "";
      fgets(buf, 254, file);
      if (feof(file)) break;
      if (buf[0] == 'v') {
        obj->count_of_vertexes++;
      } else if (buf[0] == 'f') {
        obj->count_of_facets++;
        for (j = 1, str1 = buf + 2;; j++, str1 = NULL) {
          token = strtok_r(str1, space, &temp_str);
          if (token == NULL || (!strcmp(token, "\n"))) break;
          for (str2 = token, v_count = 0;; str2 = NULL) {
            subtoken = strtok_r(str2, slash, &saveptr2);
            if (subtoken == NULL) break;
            if (v_count == 0) {
              dots++;
            }
            v_count++;
          }
        }
      }
    }
    if (obj->vertexes =
            (double*)calloc(obj->count_of_vertexes * 3, sizeof(double))) {
      if (obj->polygons = (int*)calloc(dots * 2, sizeof(int))) {
        fseek(file, 0, SEEK_SET);
        i = 0, j = 0, p = 0, v_count = 0;
        int temp_cur = 0, temp_f = 0, temp_ind = 0;
        while (1) {
          char buf[255] = "";
          fgets(buf, 254, file);
          if (feof(file)) break;
          if (buf[0] == 'v') {
            sscanf(buf, "%c %lf %lf %lf", &ch, &obj->vertexes[i++],
                   &obj->vertexes[i++], &obj->vertexes[i++]);
          } else if (buf[0] == 'f') {
            for (temp_ind = 0, j = 1, str1 = buf + 2;;
                 j++, str1 = NULL, temp_ind++) {
              token = strtok_r(str1, space, &temp_str);
              if (token == NULL || (!strcmp(token, "\n"))) {
                obj->polygons[p++] = temp_f;
                break;
              }

              for (str2 = token, v_count = 0;; str2 = NULL, v_count++) {
                subtoken = strtok_r(str2, slash, &saveptr2);
                if (subtoken == NULL) {
                  break;
                } else if (v_count == 0) {
                  cur_index = atoi(subtoken);
                  obj->polygons[p++] = cur_index;
                  if (temp_ind == 0) {
                    temp_f = cur_index;
                  } else {
                    obj->polygons[p++] = cur_index;
                  }
                }
              }
            }
          }

          err = dots;
        }
      } else {
        free(obj->vertexes);
        err = -1;
      }
    } else {
      err = -1;
    }
    fclose(file);
  }

  return err;
}

int main() {
  obj_t obj;
  char* filename_buf = "cat.obj";

  printf("%s\n", filename_buf);
  int err = readobj(filename_buf, &obj);
  if (err != -1) {
    for (int i = 0, k = 1; i < err; k++, i++) {
      printf("%d ", obj.polygons[i]);
      if (k == 6) printf("\n");
    }

    printf("Lines: %d\nCount of vertexes: %d\nCount of polygons: %d\n", err,
           obj.count_of_vertexes, obj.count_of_facets);
    free(obj.polygons);
    free(obj.vertexes);
  }
  return 0;
}
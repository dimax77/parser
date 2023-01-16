#include "readfile.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int readobj(char* file_name, obj_t* obj) {
  int err = 1;
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
          if (token == NULL) break;
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
    if (temp_indexes = (int*)calloc(dots, sizeof(int))) {
      if (obj->vertexes =
              (double*)calloc(obj->count_of_vertexes * 3, sizeof(double))) {
        if (obj->polygons = (int*)calloc(dots * 2, sizeof(int))) {
          fseek(file, 0, SEEK_SET);
          i = 0, j = 0, p = 0, v_count = 0;

          while (1) {
            char buf[255] = "";
            fgets(buf, 254, file);
            if (feof(file)) break;
            if (buf[0] == 'v') {
              sscanf(buf, "%c %lf %lf %lf", &ch, &obj->vertexes[i++],
                     &obj->vertexes[i++], &obj->vertexes[i++]);
            } else if (buf[0] == 'f') {
              for (j = 1, str1 = buf + 2;; j++, str1 = NULL) {
                token = strtok_r(str1, space, &temp_str);
                if (token == NULL) break;
                for (str2 = token, v_count = 0;; str2 = NULL, v_count++) {
                  subtoken = strtok_r(str2, slash, &saveptr2);
                  if (subtoken == NULL) break;
                  if (v_count == 0) {
                    cur_index = atoi(subtoken);
                    temp_indexes[p++] = cur_index;
                  }
                }
              }
            }

            err = 0;
          }

          
        } else {
          free(obj->vertexes);
          free(temp_indexes);
          err = 1;
        }
      } else {
        err = 1;
        free(temp_indexes);
      }
    } else {
      err = 1;
    }
    fclose(file);
    if (!err) free(temp_indexes);
  }

  return err;
}

int main() {
  obj_t obj;
  char* filename_buf = "cat.obj";

  printf("%s\n", filename_buf);
  int err = readobj(filename_buf, &obj);
  if (!err) {
    printf("Count of vertexes: %d\nCount of polygons: %d\n",
           obj.count_of_vertexes, obj.count_of_facets);
    for (int i = 0; i < 3 * obj.count_of_facets; i++) {
      // printf("%d\n", obj.polygons[i]);
    }
    free(obj.polygons);
    free(obj.vertexes);
  }
  return 0;
}
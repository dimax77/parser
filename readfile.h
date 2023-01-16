#ifndef READFILE_H
#define READFILE_H

typedef struct obj {
  int count_of_vertexes;
  int count_of_facets;
  double* vertexes;
  int* polygons;
} obj_t;

int readobj(char* file_name, obj_t*);

#endif
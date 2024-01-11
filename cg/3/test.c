#include <GL/glut.h>
#include <stdio.h>
int main(){
  typedef struct {
    float *vertices;
    int num_vertices;
  } model;
  
  model vertices;
  model uvs;
  model normals;
  char *filename="piramid.obj";
  loadOBJ(*filename,vertices,uvs,normals);
  printf(uvs);
}

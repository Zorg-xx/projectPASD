# include <stdio.h>
# include <stdlib.h>

int main(void){

  char* buff=malloc(sizeof(char)*255);
  int i =0;
  FILE *file;
  file=fopen("graphes/G_10_SOMMETS","r");

  while(fgets(buff,255,file)){
    printf("i=%d  %s",i++,buff);
  }
  free(buff);
  fclose(file);
  return 0;
}

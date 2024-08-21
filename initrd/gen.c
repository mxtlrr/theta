// Yay, usermode dev time

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <string.h>
#include <dirent.h>

#define FILE_ENDING 0xf9b6
typedef struct {
  char name[64];           // File name
  char buf[8192];          // File contents
  unsigned short ending;
  int size;
} file_t;


#define INITRD_MAGIC 0x99
typedef struct {
  unsigned char magic;
  file_t files[256];   // Every single file available on the initrd
} initrd_t;

int main(int argc, char** argv){
  if(argc == 1){
    fprintf(stderr, "usage: gen-initrd [folder]/\n");
    return 2;
  }

  char* folder = argv[1];
  file_t files[256];
  int counter = 0;

  struct dirent* de;
  DIR* dr = opendir(folder);
  if(!dr){
    fprintf(stderr, "Couldn't open %s.\n", folder);
    return 5;
  }

  while((de = readdir(dr)) != NULL && (counter != 256 || counter <= 256)){
    if((strcmp(de->d_name, ".") == 0) || (strcmp(de->d_name, "..") == 0));
    else {
      // Open de->d_name, get size and buffer and everything
      char buffer[50] = {0};
      strcat(buffer, folder);
      strcat(buffer, de->d_name);
      FILE* fp = fopen(buffer, "rb");
      fseek(fp, 0, SEEK_END);
      files[counter].size = ftell(fp);
      fseek(fp, 0, SEEK_SET);

      // Read file into buffer
      char* buff = malloc(files[counter].size);
      if(!buff){
        fprintf(stderr, "Can't malloc for file %s\n", de->d_name);
        return 4;
      }

      fread(buff, files[counter].size, 1, fp);

      // Copy buffer to files
      memcpy(files[counter].buf, buff, files[counter].size);
      files[counter].ending = FILE_ENDING;

      // Copy name aswell
      strncpy(files[counter].name, de->d_name, strlen(de->d_name));
      fclose(fp);
    }
    counter++;
  }

  // Now add each file to the initrd
  FILE* fp = fopen("initrd.img", "wb");
  fprintf(fp, "%c%c", INITRD_MAGIC >> 8,
                      INITRD_MAGIC & 0xff); // Write magic data to the
                                            // beginning

  for(int i = 0; i < 256; i++){
    if(files[i].name[0] == 0) break;
    printf("Adding %s to initrd...", files[i].name);

    fprintf(fp, "%s", files[i].name); // Name
    for(int j = 0; j < files[i].size; j++)
      fprintf(fp, "%c", files[i].buf[j]);
    
    // Add ending to file
    fprintf(fp, "%c%c", FILE_ENDING >> 8, FILE_ENDING & 0xff);
    printf("done!\n");
  }

  // Goodbye.
  fclose(fp);
  return 0;
}
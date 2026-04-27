#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str;
    // TODO: 在这里添加你的代码
  switch (e_type) {
        case ET_REL:   // 1: 可重定位文件（.o）
            type_str = "Relocatable";
            break;
        case ET_EXEC:  // 2: 可执行文件
            type_str = "Executable";
            break;
        case ET_DYN:   // 3: 共享库 / PIE
            type_str = "Shared Object/PIE";
            break;
        case ET_CORE:  // 4: Core 文件
            type_str = "Core";
            break;
        default:
            type_str = "Unknown";
            break;
    }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;

  // TODO: 在这里添加你的代码
  // FILE* stream;

  // stream = fopen(filepath[0], "rb");
  // if (stream == NULL) {
  //   perror("fopen filepath[0] failed");
  //   return 1;
  // }
  // fread(&ehdr, sizeof(Elf64_Ehdr), 1, stream);

  // print_elf_type(ehdr.e_type);
  // fclose(stream);

  // stream = fopen(filepath[1], "rb");
  // if (stream == NULL) {
  //   perror("fopen filepath[0] failed");
  //   return 1;
  // }
  // fread(&ehdr, sizeof(Elf64_Ehdr), 1, stream);

  // print_elf_type(ehdr.e_type);
  // fclose(stream);

  fd = open(filepath[0], O_RDONLY);

  if( fd == -1) {
    perror("open filepath[0] failed");
    return 1;
  }
  
  ssize_t n = read(fd, &ehdr, sizeof(ehdr));
  if (n < 0) {
      perror("read");
      close(fd);
      return 1;
  }
  if ((size_t)n != sizeof(ehdr)) {
      fprintf(stderr, "ELF header too short\n");
      close(fd);
      return 1;
  }
  print_elf_type(ehdr.e_type);
  close(fd);


  fd = open(filepath[1], O_RDONLY);

  if( fd == -1) {
    perror("open filepath[0] failed");
    return 1;
  }
  
  n = read(fd, &ehdr, sizeof(ehdr));
  if (n < 0) {
      perror("read");
      close(fd);
      return 1;
  }
  if ((size_t)n != sizeof(ehdr)) {
      fprintf(stderr, "ELF header too short\n");
      close(fd);
      return 1;
  }
    if (ehdr.e_type == ET_EXEC) {
      print_elf_type(ET_DYN);
    } else {
      print_elf_type(ehdr.e_type);
    }
  close(fd);

  return 0;
}

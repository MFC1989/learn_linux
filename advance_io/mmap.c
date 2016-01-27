#include <stdio.h>
#include <ctype.h>
#include <sys/mman.h> /*mmap munmap*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
												
int main(int argc, char *argv[])		
{
    int fd;
    char *buf;
    off_t len;
    struct stat sb;
    
  //  puts(argv[1]);
    fd = open("/tmp/file_mmap", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    if (fstat(fd, &sb) == -1)
    {
        perror("fstat");
        return 1;
    }
 
    buf = mmap(0, sb.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); //好像只能映射tmp文件夹和/home/user里的文件。其他地方的会报错。
    if (buf == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }
 
    if (close(fd) == -1)
    {
        perror("close");
        return 1;
    }
 
    for (len = 0; len < sb.st_size; ++len)
    {
        buf[len] = toupper(buf[len]);
        putchar(buf[len]);
    }
 
    if (munmap(buf, sb.st_size) == -1)
    {
        perror("munmap");
        return 1;
    }
    return 0;
}


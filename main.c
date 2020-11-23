#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main() {
    struct stat s;
    DIR * d = opendir(".");
    struct dirent *entry = readdir(d);
    int dir_size = 0;
    
    printf("Statistics for directory: %s\n", entry->d_name);

    while(entry) {
        if (entry->d_type == DT_REG) {
            stat(entry->d_name, &s);
            dir_size += s.st_size;
        }
        entry = readdir(d);
    }

    printf("Total Directory Size: %d Bytes\n", dir_size);

    rewinddir(d);

    printf("Directories:\n");
    entry = readdir(d);

    while(entry) {
        if (entry->d_type == DT_DIR) {
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    rewinddir(d);

    printf("Regular files:\n");
    entry = readdir(d);

    while(entry) {
        if (entry->d_type == DT_REG) {
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    closedir(d);
}

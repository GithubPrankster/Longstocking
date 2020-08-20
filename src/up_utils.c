#include <stdio.h>
#include <stdlib.h>
#include "up_utils.h"

char* up_file(const char* path)
{
    FILE* fp = fopen(path, "r");
    if(!fp){
        printf("[Up] ERROR: Could not open file %s.\n", path);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size_t sz = ftell(fp);
    rewind(fp);
    
    char *buf = calloc(sizeof(char), sz);
    if(!buf){
        printf("[Up] ERROR: Could not allocate for file %s.\n", path);
        fclose(fp);
        return NULL;
    }
    
    fread(buf, sz, sizeof(char), fp);
    if(!buf){
        printf("[Up] ERROR: Could not load file %s.\n", path);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return buf;
}

char* up_file_bin(const char* path)
{
    FILE* fp = fopen(path, "rb");
    if(!fp){
        printf("[Up] ERROR: Could not open file %s.\n", path);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size_t sz = ftell(fp);
    rewind(fp);
    
    char *buf = calloc(sizeof(char), sz);
    if(!buf){
        printf("[Up] ERROR: Could not allocate for file %s.\n", path);
        fclose(fp);
        return NULL;
    }
    
    fread(buf, sz, sizeof(char), fp);
    if(!buf){
        printf("[Up] ERROR: Could not load file %s.\n", path);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return buf;
}
//
// Created by zeph on 12/25/16.
//
// got it from: https://techoverflow.net/blog/2013/08/21/a-simple-mmap-readonly-example/

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>
#include <iostream>

size_t getFilesize(const char* filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

int main(int argc, char** argv) {
    std::cout << "argv[0]: " << argv[0] << std::endl;
    std::cout << "argv[1]: " << argv[1] << std::endl;

    size_t filesize = getFilesize(argv[1]);
    std::cout << "filesize(" << argv[1] << ") = " << filesize << std::endl;
    //Open file
    int fd = open(argv[1], O_RDONLY, 0);
    assert(fd != -1);
    //Execute mmap
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(mmappedData != MAP_FAILED);
    //Write the mmapped data to stdout (= FD #1)
    write(1, mmappedData, filesize);
    //Cleanup
    int rc = munmap(mmappedData, filesize);
    assert(rc == 0);
    close(fd);

    return 0;
}
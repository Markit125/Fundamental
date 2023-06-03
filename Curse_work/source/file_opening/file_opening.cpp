#include "file_opening.h"


std::ifstream open_file(std::string &filename) {

    std::ifstream file;
    file.open(filename);

    if (!file.is_open() || !file) {
        throw std::runtime_error("File doesn't exists!");
    }

    return file;
}
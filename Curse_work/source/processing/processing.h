#ifndef PROCESSING_H
#define PROCESSING_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "../file_opening/file_opening.h"
#include "../data/database/database.h"
#include "../logger/source/logger/complete/complete_logger.h"
#include "../memory/2/source/memory/memory.h"


int process_file(std::string &filename, allocating::memory *allocator, logging::logger *logger);

int validate(std::string &string);


#endif
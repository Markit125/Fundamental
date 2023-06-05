#ifndef PROCESSING_H
#define PROCESSING_H

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include "../file_opening/file_opening.h"
#include "../data/database/database.h"
#include "../logger/source/logger/complete/complete_logger.h"
#include "../memory/2/source/memory/memory.h"


int process_file(database *&db, std::stringstream &in_stream, std::stringstream &out_stream, logging::logger *logger);

int validate(std::string &string);


#endif
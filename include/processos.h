#ifndef PROCESSOS_H  
#define PROCESSOS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void multiplicarMatrizesProcessos(std::vector<std::vector<int>>& matriz1, std::vector<std::vector<int>>& matriz2, int nprocessos);

#endif
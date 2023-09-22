#ifndef THREADS_H  
#define THREADS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

void multiplicarMatrizesThread(std::vector<std::vector<int>>& matriz1, std::vector<std::vector<int>>& matriz2, int elementosPorThread);

#endif

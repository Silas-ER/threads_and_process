#ifndef PROGAUXILIAR_H  
#define PROGAUXILIAR_H

#include <vector>
#include <string>

void exportaMatriz(const std::vector<std::vector<int>>& matriz, const std::string& nomeArquivo);
void geraMatrizes(int l1, int c1, int l2, int c2);

#endif
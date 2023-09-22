#include <iostream>
#include <vector>
#include <cstdlib>  
#include <ctime>    
#include <fstream>
#include <string> 

void exportaMatriz(const std::vector<std::vector<int>>& matriz, const std::string& nomeArquivo){
  std::ofstream arquivo(nomeArquivo);
  if(arquivo.is_open()){
    for (const auto& linha : matriz) {
      for (int valor : linha) {
        arquivo << valor << " ";
      }
      arquivo << "\n"; 
    }
    arquivo.close();
  }else{
    std::cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << std::endl;
  }
}

void geraMatrizes(int l1, int c1, int l2, int c2){
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  int min = 1;
  int max = 100;
  int numeroAleatorio;
  
  std::vector<std::vector<int>> matriz1;
  for (int i = 0; i < l1; i++) {
    matriz1.push_back(std::vector<int>());
    for (int j = 0; j < c1; j++) {
      numeroAleatorio = min + std::rand() % (max - min + 1);
      matriz1[i].push_back(numeroAleatorio);
    }
  }

  std::vector<std::vector<int>> matriz2;
  for (int i = 0; i < l2; i++) {
    matriz2.push_back(std::vector<int>());
    for (int j = 0; j < c2; j++) {
      numeroAleatorio = min + std::rand() % (max - min + 1);
      matriz2[i].push_back(numeroAleatorio);
    }
  }
  exportaMatriz(matriz1, "assets/matrizesIniciais/matriz1.txt");
  exportaMatriz(matriz2, "assets/matrizesIniciais/matriz2.txt");
}
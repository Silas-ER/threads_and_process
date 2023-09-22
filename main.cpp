#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "include/progAuxiliar.h"
#include "include/sequencial.h"
#include "include/threads.h"
#include "include/processos.h"

void lerMatriz(const std::string& nomeArquivo, std::vector<std::vector<int>>& matriz) {
  //variavel de arquivo
  std::ifstream arquivo(nomeArquivo);
  
  //verificação se os arquivos estão abrindo corretamente
  if (!arquivo.is_open()) {
    std::cerr << "Não foi possível o arquivo de matriz." << std::endl;
    return;
  }

  //leitura dos arquivos e armazenamento nas matrizes
  std::string linha;
  while (std::getline(arquivo, linha)) {
    std::vector<int> linhaMatriz;
    std::istringstream iss(linha);
    int valor;
      while (iss >> valor) {
        linhaMatriz.push_back(valor);
      }
      matriz.push_back(linhaMatriz);
    }
  arquivo.close();
}

bool verificaTamanhos(const int n1, const int m2){
  if (n1 != m2) {
    std::cerr << "As dimensões das matrizes não são compatíveis para multiplicação." << std::endl;
    return false;
  }else{
    return true;
  }
}

int main(){
  //dimensões matriciais
  int m1 = 3200;
  int n1 = 3200;
  int m2 = 3200; 
  int n2 = 3200; 
  int P;

  P = (n1*m2)/6;
  
  //verificar se pode ser multiplicada
  if (!verificaTamanhos(n1, m2)) {
    return 1;
  }
  
  //chamada da função geradora de matrizes
  geraMatrizes(n1, m1, n2, m2);

  //localização dos arquivos das matrizes
  std::string mat1 = "assets/matrizesIniciais/matriz1.txt";
  std::string mat2 = "assets/matrizesIniciais/matriz2.txt";

  //criação e atribuição de matrizes
  std::vector<std::vector<int>> matriz1;
  std::vector<std::vector<int>> matriz2;  
  lerMatriz(mat1, matriz1);
  lerMatriz(mat2, matriz2);

  //passar matrizes e o valor de P para os calculos
  multiplicarMatrizesSequencial(matriz1, matriz2);
  multiplicarMatrizesProcessos(matriz1, matriz2, P);
  multiplicarMatrizesThread(matriz1, matriz2, P);
  return 0;
}

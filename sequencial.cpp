#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void multiplicarMatrizesSequencial(
    const std::vector<std::vector<int>> &matriz1,
    const std::vector<std::vector<int>> &matriz2) {
  // coleta das dimensões da matriz
  int m1 = matriz1.size();
  int n1 = matriz1[0].size();
  int m2 = matriz2.size();
  int n2 = matriz2[0].size();

  // verificação se a matriz é apta para o calculo de multiplicação
  if (n1 != m2) {
    std::cerr
        << "Erro: As matrizes não podem ser multiplicadas. O número de colunas "
           "da matriz1 deve ser igual ao número de linhas da matriz2."
        << std::endl;
    return;
  }

  // criação da matriz resultado inicializada com 0s.
  std::vector<std::vector<int>> resultado(m1, std::vector<int>(n2, 0));

  // atribuição do local onde o arquivo resultado será armazenado
  std::string nomeArquivoResultado =
      "assets/exercicios/resultadosSequencial/matrizResultado" +
      std::to_string(m1) + "x" + std::to_string(n2) + "Sequencial.txt";

  // iniciando o tempo de contagem da multiplicação
  auto inicio = std::chrono::high_resolution_clock::now();

  // multiplicação das matrizes
  for (int i = 0; i < m1; ++i) {
    for (int j = 0; j < n2; ++j) {
      for (int k = 0; k < n1; ++k) {
        resultado[i][j] += matriz1[i][k] * matriz2[k][j];
      }
    }
  }

  // fim da contagem de tempo e calculo do total em segundos
  auto fim = std::chrono::high_resolution_clock::now();
  auto duracao_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
  double duracao_s = static_cast<double>(duracao_ms.count()) / 1000.0;

  // atribuição e verificação se o arquivo de resultado está sendo aberto e
  // depois a escrita conforme solicitado
  std::ofstream arquivoResultado(nomeArquivoResultado);
  if (!arquivoResultado.is_open()) {
    std::cerr << "Não foi possível abrir o arquivo para escrita." << std::endl;
    return;
  }

  arquivoResultado << m1 << " " << n2 << std::endl;

  for (int i = 0; i < m1; ++i) {
    for (int j = 0; j < n2; ++j) {
      arquivoResultado << "c" << i + 1 << j + 1 << " " << resultado[i][j]
                       << std::endl;
    }
  }

  arquivoResultado << duracao_ms.count() << "ms" << std::endl;
  arquivoResultado << duracao_s << "s" << std::endl;
  arquivoResultado.close();
}
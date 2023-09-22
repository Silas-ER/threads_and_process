#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

void multiplicarMatrizesProcessos(std::vector<std::vector<int>> &matriz1,
                                  std::vector<std::vector<int>> &matriz2,
                                  int elementosPorProcesso) {

  int qntProcessos =
      (matriz1.size() * matriz2[0].size()) / elementosPorProcesso;
  int currentIndex = 0;

  if (qntProcessos < 1) {
    qntProcessos = 1;
  }

  std::vector<double> temposProcessosMs(qntProcessos, 0.0);
  std::vector<double> temposProcessosS(qntProcessos, 0.0);

  for (int i = 0; i < qntProcessos; i++) {
    int startIndex = currentIndex;
    int endIndex = currentIndex + elementosPorProcesso;

    pid_t pid = fork();

    if (pid == 0) {
      auto start_time_processo = std::chrono::high_resolution_clock::now();
      std::vector<std::pair<std::string, int>> resultados;

      for (int index = startIndex; index < endIndex; index++) {
        int row = index / matriz2.size();
        int col = index % matriz2.size();
        int result = 0;

        for (int k = 0; k < matriz1.size(); k++) {
          result += matriz1[row][k] * matriz2[k][col];
        }
        std::string posicao =
            "c" + std::to_string(row + 1) + std::to_string(col + 1);
        resultados.emplace_back(posicao, result);
      }

      auto end_time_processo = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> elapsed_processo =
          end_time_processo - start_time_processo;

      temposProcessosS[i] = elapsed_processo.count();
      temposProcessosMs[i] = elapsed_processo.count() / 1000;

      std::string fileName =
          "assets/exercicios/resultadosProcessos/resultado_processo_" +
          std::to_string(matriz1.size()) + "x" +
          std::to_string(matriz2[0].size()) + "_" + std::to_string(i) + ".txt";
      std::ofstream resultFile(fileName);

      if (resultFile.is_open()) {
        // Escreva o tamanho total da matriz.
        resultFile << matriz1[0].size() << " " << matriz2[0].size()
                   << std::endl;

        // Escreva os resultados com posições e valores.
        for (const auto &resultado : resultados) {
          resultFile << resultado.first << " " << resultado.second << std::endl;
        }

        // Escreva o tempo do processo.
        resultFile << elapsed_processo.count() << "seg" << std::endl;
        resultFile << elapsed_processo.count() * 1000.0 << "ms" << std::endl;
        resultFile.close();
      } else {
        std::cerr << "Erro ao abrir o arquivo de resultado do processo."
                  << std::endl;
      }
      exit(0);
    } else if (pid < 0) {
      std::cerr << "Erro ao criar processo." << std::endl;
      return;
    }
    currentIndex = endIndex;
  }

  for (int i = 0; i < qntProcessos; i++) {
    int status;
    wait(&status);
  }

  double tempoTotals = 0.0;
  double tempoTotalms = 0.0;
  for (int i = 0; i < qntProcessos; i++) {
    tempoTotals += temposProcessosS[i];
    tempoTotalms += temposProcessosMs[i];
  }

  std::string fileTimeName =
      "assets/exercicios/resultadosProcessos/Tempo_total_processos_" +
      std::to_string(matriz1.size()) + "x" + std::to_string(matriz2[0].size()) +
      ".txt";
  std::ofstream tempoTotalFile(fileTimeName);
  if (tempoTotalFile.is_open()) {
    tempoTotalFile << "Tempo total de todas os processos: " << tempoTotals
                   << " segundos" << std::endl;
    tempoTotalFile << "Tempo total de todas os processos: " << tempoTotalms
                   << "ms" << std::endl;
    tempoTotalFile.close();
  } else {
    std::cerr
        << "Não foi possível abrir o arquivo para armazenar o tempo total."
        << std::endl;
  }
}

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void multiplicarMatrizesThread(std::vector<std::vector<int>> &matriz1,
                               std::vector<std::vector<int>> &matriz2,
                               int elementosPorThread) {
  int m1 = matriz1.size();
  int n1 = matriz1[0].size();
  int m2 = matriz2.size();
  int n2 = matriz2[0].size();

  int qntThreads = (m1 * n2) / elementosPorThread;
  int currentIndex = 0;

  if (qntThreads < 1) {
    qntThreads = 1;
  }

  std::vector<double> temposThreadsMs(qntThreads, 0.0);
  std::vector<double> temposThreadsS(qntThreads, 0.0);

  std::vector<std::ofstream> resultFiles(qntThreads);
  for (int i = 0; i < qntThreads; i++) {
    std::string fileName =
        "assets/exercicios/resultadosThreads/resultado_thread_" + std::to_string(n1) + "x" +
        std::to_string(m2) + "_" + std::to_string(i) + ".txt";
    resultFiles[i].open(fileName);
    if (!resultFiles[i].is_open()) {
      std::cerr << "Erro ao criar arquivo de resultado para a thread " << i
                << std::endl;
      return;
    }

    resultFiles[i] << m1 << " " << n2 << std::endl;
  }

  std::vector<std::thread> threads;
  for (int i = 0; i < qntThreads; i++) {
    int startIndex = currentIndex;
    int endIndex = currentIndex + elementosPorThread;

    if (i == qntThreads - 1) {
      endIndex = m1 * n2; // Para a última thread, pegue o restante dos elementos.
    }

    threads.emplace_back(
        [&](int i, int startIndex, int endIndex) {
          auto start_time_thread = std::chrono::high_resolution_clock::now();
          for (int index = startIndex; index < endIndex; index++) {
            int row = index / n2;
            int col = index % n2;

            int result = 0;
            for (int k = 0; k < n1; k++) {
              result += matriz1[row][k] * matriz2[k][col];
            }

            resultFiles[i] << "c" << row + 1 << col + 1 << " " << result
                           << std::endl;
          }
          auto end_time_thread = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> elapsed_thread =
              end_time_thread - start_time_thread;
          resultFiles[i] << elapsed_thread.count() << "s" << std::endl;
          resultFiles[i] << elapsed_thread.count() * 1000 << "ms" << std::endl;
          temposThreadsS[i] = elapsed_thread.count();
          temposThreadsMs[i] = elapsed_thread.count() * 1000;
        },
        i, startIndex, endIndex);

    currentIndex = endIndex;
  }

  for (auto &thread : threads) {
    thread.join();
  }

  for (int i = 0; i < qntThreads; i++) {
    resultFiles[i].close();
  }

  double tempoTotalS = 0.0;
  double tempoTotalMs = 0.0;
  for (int i = 0; i < qntThreads; i++) {
    tempoTotalS += temposThreadsS[i];
    tempoTotalMs += temposThreadsMs[i];
  }

  std::string fileTimeName = "assets/exercicios/resultadosThreads/Tempo_total_threads_" +
                             std::to_string(n1) + "x" + std::to_string(m2) + ".txt";
  std::ofstream tempoTotalFile(fileTimeName);
  if (tempoTotalFile.is_open()) {
    tempoTotalFile << "Tempo total de todas as threads em segundos: " << tempoTotalS
                   << std::endl;
    tempoTotalFile << "Tempo total de todas as threads em milissegundos: " << tempoTotalMs
                   << std::endl;
    tempoTotalFile.close();
  } else {
    std::cerr
        << "Não foi possível abrir o arquivo para armazenar o tempo total."
        << std::endl;
  }
}

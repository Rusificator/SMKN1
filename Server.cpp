#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct Employee {
    string name;
    int projects_completed;
    int overtime_hours;
    int efficiency;
    int initiatives;
} E;

long current_request_size = 0;
const string shutdown_signal = "SHUTDOWN";

int main() {
    setlocale(LC_ALL, "rus");
    const string request_file = "C:/REQUEST.txt";
    cout << "Сервер запущен и работает..." << endl;
    cout << "Ожидание запросов. Для завершения работы введите 'exit' в клиенте." << endl;

    while (true) {
        ifstream fRequest(request_file);
        fRequest.seekg(0, ios::end);
        
        if (fRequest.tellg() > current_request_size) {
            fRequest.seekg(current_request_size, ios::beg);
            getline(fRequest, E.name);
            current_request_size = fRequest.tellg();
            fRequest.close();

            // Проверка сигнала завершения работы
            if (E.name == shutdown_signal) {
                cout << "Получен сигнал завершения работы от клиента." << endl;
                cout << "Завершение работы сервера." << endl;
                break;
            }

            string data_file = "C:/" + E.name + ".txt";
            ifstream fData(data_file);
            if (fData.is_open()) {
                fData >> E.projects_completed;
                fData >> E.overtime_hours;
                fData >> E.efficiency;
                fData >> E.initiatives;
                fData.close();

                int total_score = E.projects_completed + E.overtime_hours + 
                                E.efficiency + E.initiatives;
                string answer;

                if (E.projects_completed < 2) {
                    answer = "NO_BONUS";
                } else if (total_score >= 40) {
                    answer = "HIGH_BONUS";
                } else if (total_score >= 25) {
                    answer = "MEDIUM_BONUS";
                } else {
                    answer = "STANDARD_BONUS";
                }

                ofstream fAnswer(data_file, ios::app);
                fAnswer << endl << answer;
                fAnswer.close();

                cout << "Обработан сотрудник: " << E.name 
                     << " Результат: " << answer << endl;
            }
        } else {
            fRequest.close();
            Sleep(1000);
        }
    }
    
    // Очистка перед завершением
    cout << "Сервер завершил работу." << endl;
    return 0;
}

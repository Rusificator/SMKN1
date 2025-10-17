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

int main() {
    setlocale(LC_ALL, "rus");
    const string request_file = "C:/REQUEST.txt";
    const string shutdown_signal = "SHUTDOWN";

    while (true) {
        // Простой ввод через cin
        cout << "Введите имя сотрудника (или 'exit' для завершения работы сервера): ";
        cin >> E.name;
        
        if (E.name == "exit" || E.name == "esc") {
            cout << "Отправка сигнала завершения серверу..." << endl;
            
            // Отправляем сигнал завершения серверу
            ofstream fRequest(request_file, ios::app);
            fRequest << shutdown_signal << endl;
            fRequest.close();
            
            cout << "Завершение работы клиента." << endl;
            break;
        }
        
        cout << "Введите количество завершенных проектов: ";
        cin >> E.projects_completed;
        
        cout << "Введите количество сверхурочных часов: ";
        cin >> E.overtime_hours;
        
        cout << "Введите показатель эффективности (0-10): ";
        cin >> E.efficiency;
        
        cout << "Введите количество инициатив: ";
        cin >> E.initiatives;
        // Создание файла с данными 
        string data_file = "C:/" + E.name + ".txt";
        ofstream fData(data_file);
        fData << E.projects_completed << endl
              << E.overtime_hours << endl
              << E.efficiency << endl
              << E.initiatives;
        fData.close();

        // Добавление запроса в файл запросов
        ofstream fRequest(request_file, ios::app);
        fRequest << E.name << endl;
        fRequest.close();

        Sleep(2000); // Ожидание обработки сервером

        // Чтение ответа от сервера
        ifstream fAnswer(data_file);
        string line, last_line;
        while (getline(fAnswer, line)) {
            if (!line.empty()) {
                last_line = line;
            }
        }
        fAnswer.close();

        // Вывод результата
        cout << "Результат для сотрудника " << E.name << ": ";
        if (last_line == "NO_BONUS") {
            cout << "Премия не назначена" << endl;
        } else if (last_line == "STANDARD_BONUS") {
            cout << "Стандартная премия" << endl;
        } else if (last_line == "MEDIUM_BONUS") {
            cout << "Средняя премия" << endl;
        } else if (last_line == "HIGH_BONUS") {
            cout << "Высокая премия" << endl;
        }
        cout << "-----------------------" << endl;
    }
    return 0;
}

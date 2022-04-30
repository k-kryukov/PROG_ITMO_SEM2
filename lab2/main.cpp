#include "headers.hpp"

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::string content;
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    ExcCur ec;

    while (1) {
        download_data(content);
        json js = json::parse(content);
        update_data(js, ec);
        output_data("out.txt", js, ec);

        content.clear();
        Sleep(sleep_time);
    }
    
    return 0;
}
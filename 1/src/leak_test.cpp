#include <iostream>

int main() {
    std::cout << "Создаю утечку памяти..." << std::endl;
    int* arr = new int[1000];  // огромная утечка!
    // Забудем delete[]
    return 0;
}
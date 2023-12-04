#include <iostream>
#include <vector>
#include <future>
#include <deque>

std::vector<std::vector<int>> processChannel(std::deque<int>& channel) {
    std::vector<std::vector<int>> result;

    while (!channel.empty()) {
        int count = channel.front();
        channel.pop_front();

        std::vector<int> subArray;
        for (int i = 0; i < count; ++i) {
            subArray.push_back(channel.front());
            channel.pop_front();
        }

        result.push_back(subArray);
    }

    return result;
}

int main() {
    std::deque<int> channel = { 3, 4, 0, 2, 1, 2, 2, 4, 5 };

    // Используем асинхронность для обработки канала
    std::future<std::vector<std::vector<int>>> resultFuture = std::async(std::launch::async, processChannel, std::ref(channel));

    // Ждем завершения асинхронной операции и получаем результат
    std::vector<std::vector<int>> result = resultFuture.get();

    // Выводим результат
    for (const auto& subArray : result) {
        std::cout << "[ ";
        for (int num : subArray) {
            std::cout << num << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}

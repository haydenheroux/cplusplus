#include <cmath>
#include <iostream>

int prompt_for(std::string prompt) {
    std::cout << prompt << "? ";

    int n;
    std::cin >> n;
    return n;
}

int sum_vertically(int digits, int index) {
    int sum = 0;

    for (int digit = 0; digit < digits; digit++) {
        sum += pow(10, digit) * (1 + digit + 3 * index);
    }

    return sum;
}

int sum_horizontally(int digits, int index) {
    int sum = 0;

    for (int digit = 0; digit < digits; digit++) {
        sum += pow(10, digit) * (1 + 3 * digit + index);
    }

    return sum;
}

int reverse_number(int number) {
    int reversed_number = 0;

    while (number != 0) {
        reversed_number *= 10;
        reversed_number += number % 10;
        number /= 10;
    }

    return reversed_number;
}

int main() {
    int digits = prompt_for("digits");
    int index = prompt_for("index");

    // TODO Sum vertically or horizontally depending on argument
    std::cout << reverse_number(sum_vertically(digits, index));

    return 0;
}

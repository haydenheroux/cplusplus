#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

std::vector<std::string> get_lines(std::istream& lines) {
    std::vector<std::string> result;

    std::string line;

    while (std::getline(lines, line)) {
        result.push_back(line);
    }

    return result;
}

std::vector<std::string> tokenize(std::string& str, char delim) {
    std::vector<std::string> result;

    std::stringstream stream{str};

    std::string token;

    while (std::getline(stream, token, delim)) {
        result.push_back(token);
    }

    return result;
}

struct entry {
    unsigned int odometer_miles;
    double gallons_filled;
    bool full;
};

std::unique_ptr<struct entry> to_entry(std::string& str) {
    std::vector<std::string> tokens = tokenize(str, ',');

    if (tokens.size() != 3) {
        return nullptr;
    }

    auto entry = std::make_unique<struct entry>();

    entry->odometer_miles = std::stoi(tokens[0]);
    entry->gallons_filled = std::stof(tokens[1]);
    entry->full = std::stoi(tokens[2]) != 0;

    return entry;
}

enum state {
    UNKNOWN,
    FULL,
    NOT_FULL
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "incorrect number of arguments!" << std::endl;
        return 1;
    }

    std::filesystem::path path{argv[1]};

    std::ifstream csv_file{path};

    auto lines = get_lines(csv_file);

    std::cout << "started parsing!" << std::endl;

    enum state previous_state = UNKNOWN;

    unsigned int initial_miles = 0;
    double gallons = 0;

    for (auto line : lines) {
        auto entry = to_entry(line);

        if (entry == nullptr) {
            std::cerr << "failed to parse!" << std::endl;
            continue;
        }

        enum state state;

        switch (previous_state) {
            case UNKNOWN:
            case NOT_FULL:
                if (entry->full) {
                    state = FULL;
                }
                break;
            case FULL:
                if (entry->full == false) {
                    state = NOT_FULL;
                }
                break;
        }

        switch (state) {
            case UNKNOWN:
                break;
            case NOT_FULL:
                gallons += entry->gallons_filled;
                break;
            case FULL: {
                switch (previous_state) {
                    case UNKNOWN:
                        initial_miles = entry->odometer_miles;
                        break;
                    case NOT_FULL: {
                        gallons += entry->gallons_filled;

                        unsigned int final_miles = entry->odometer_miles;
                        unsigned int miles_travelled = final_miles - initial_miles;

                        std::cout << "miles travelled: " << miles_travelled << std::endl;
                        std::cout << "gallons used: " << gallons << std::endl;
                        std::cout << "miles per gallon: " << miles_travelled / gallons << std::endl;
                        break;
                    }
                    case FULL:
                      break;
                    }
                break;
            }
        }

        previous_state = state;
    }

    std::cout << "done parsing!" << std::endl;

    return 0;
}

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <optional>

struct options {
    std::filesystem::path backlight_directory;
    double brightness_percent;
};

std::optional<options> parse_args(int argc, char** argv) {
    options options;

    if (argc != 3) {
        return std::nullopt;
    }

    std::string directory = argv[1];
    options.backlight_directory = std::filesystem::path{directory};

    double percent = std::stof(argv[2]);
    percent = std::clamp(percent, 0.0, 1.0);
    options.brightness_percent = percent;

    return options;
}

double read_float(std::filesystem::path& path) {
    std::string s;

    std::ifstream file{path};

    std::getline(file, s);

    return std::stof(s);
}

void write_int(std::filesystem::path& path, int n) {
    std::ofstream file{path};

    file << n;
}

int main(int argc, char** argv) {
    auto options = parse_args(argc, argv);

    if (!options) {
        return 1;
    }

    std::filesystem::path max_brightness_file = options->backlight_directory/"max_brightness";
    double max_brightness = read_float(max_brightness_file);

    int brightness = options->brightness_percent * max_brightness;

    std::filesystem::path brightness_file = options->backlight_directory/"brightness";
    write_int(brightness_file, brightness);

    return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " -o<options>" << " <string>" << " <filename>" << std::endl;
        return 1;
    }

    // grep without options

    if (argc == 3) {
        std::string search = argv[1];
        std::string file = argv[2];

        std::string line;
        int lines = 0;

        // open file

        std::ifstream iFile(file);
        
        // iterate over file looking for lines containing search

        while (std::getline(iFile, line)) {
            lines++;
            if (line.find(search) != std::string::npos) {
                std::cout << line << std::endl;
            }
        }
        std::cout << std::endl;

        iFile.close();
    }
    
    // grep with options

    if (argc == 4) {
        std::string options = argv[1];
        std::string search = argv[2];
        std::string file = argv[3];
    
        std::string line;
        int lines = 0;
        int occurs = 0;

        // options
        bool l = false;
        bool o = false;
        bool r = false;
        bool i = false;

        // check for options

        if (options.substr(0, 2) != "-o") {
            std::cerr << "Usage: " << argv[0] << " -o<options>" << " <string>" << " <filename>" << std::endl;
            return 1;
        }

        for (int x = 2; x < options.length(); x++) {
            if (options[x] == 'l') {
                l = true;
            }
            if (options[x] == 'o') {
                o = true;
            }
            if (options[x] == 'r') {
                r = true;
            }
            if (options[x] == 'i') {
                i = true;
            }
        }

        if (i) {
            std::transform(search.begin(), search.end(), search.begin(), ::tolower);
        }

        std::ifstream iFile(file);

        if (!iFile) {
            std::cerr << "Error oppening file" << std::endl << std::endl;
            return 1;
        }

        if (r) {
            while (std::getline(iFile, line)) {
                lines++;

                std::string temp_line = line;
                if (i) {
                    std::transform(temp_line.begin(), temp_line.end(), temp_line.begin(), ::tolower);
                }

                if (temp_line.find(search) != std::string::npos) {
                    occurs++;
                }
                else {
                    if (l) {
                        std::cout << lines << ":    ";
                    }
                    std::cout << line << std::endl;
                }
            }
        }
        else {
            while (std::getline(iFile, line)) {
                lines++;

                std::string temp_line = line;
                if (i) {
                    std::transform(temp_line.begin(), temp_line.end(), temp_line.begin(), ::tolower);
                }

                if (temp_line.find(search) != std::string::npos) {
                    if (l) {
                        std::cout << lines << ":    ";
                    }
                    std::cout << line << std::endl;
                    occurs++;
                }
            }
        }
        
        std::cout << std::endl;

        if (o) {
            std::cout << "Occurrences of lines containing \"" << search << "\": " << occurs << std::endl;
        }

        iFile.close();
    }

    return 0;
}
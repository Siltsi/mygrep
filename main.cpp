#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <vector>

// function for getting file's size
std::streampos file_size(std::string& file) {

    std::ifstream input_file(file, std::ios::binary);

    // couldn't open file
    if (!input_file) {
        return -1;
    }

    // couldn't get file size
    input_file.seekg(0, std::ios::end);
    std::streampos size = input_file.tellg();

    input_file.close();

    return size;
}

// grep function
int grep(std::string& options, std::string& search, std::string& file) {

    // standard grep
    if (options == "" && search == "" && file == "") {
        //vector containing all positions for search
        std::vector<int> pos;

        std::cout << "Give a string from which to search for: ";
        std::string str;
        getline(std::cin, str);
        
        std::cout << "Give search string: ";
        std::string search;
        getline(std::cin, search);
        std::cout << std::endl;

        // parse all positions for search in str 
        for (int x = 0; x <= str.length() - search.length(); x++) {
            if (str.substr(x, search.length()) == search) {
                pos.push_back(x);
            }
        }

        // outputs
        if (pos.size() == 0) {
            std::cout << "\"" << search << "\" NOT found in \"" << str << "\"" << std::endl;
        }
        else {
            std::cout << "\"" << search << "\" found in \"" << str << "\" ";
            if (pos.size() == 1) {
                std::cout << "in position ";
            }
            else {
                std::cout << "in positions ";
            }

            std::cout << pos[0];
            for (int x = 1; x < pos.size(); x++) {
                std::cout << ", ";
                std::cout << pos[x];
            }
            std::cout << std::endl << std::endl;
        }
        return 0;
    }

    // grep with a file
    else {

        // get file size
        if (file_size(file) == -1) {
            std::cerr << "An exception occurred. Exception Nr. -1 Could not find out the size of file \""
                << file << "\"" << std::endl << std::endl;
            return 1;
        }

        // variables
        std::string line;
        int line_number = 0;
        int occurs = 0;

        // option variables
        bool l = false;
        bool o = false;
        bool r = false;
        bool i = false;

        if (options != "") {
            // check syntax
            if (options.substr(0, 2) != "-o") {
                std::cerr << "Usage: .\\mygrep.exe <options> <string> <filename>" << std::endl << std::endl;
                return 1;
            }

            // parse for options
            for (int x = 2; x < options.length(); x++) {
                if (options[x] == 'l') {
                    l = true;
                }
                else if (options[x] == 'o') {
                    o = true;
                }
                else if (options[x] == 'r') {
                    r = true;
                }
                else if (options[x] == 'i') {
                    i = true;
                }
                else {
                    std::cerr << "Correct syntax for <options> is \"-o\"<options>." << std::endl;
                    std::cerr << "Available options are \"i\", \"l\", \"r\" and \"o\"." << std::endl << std::endl;
                    return 1;
                }
            }
        }

        // if "i" option, ignore case for search
        if (i) {
            std::transform(search.begin(), search.end(), search.begin(), ::tolower);
        }

        std::ifstream iFile(file);

        // reverse "r" option parse
        if (r) {
            // iterate over file's lines one by one
            while (std::getline(iFile, line)) {
                line_number++;

                std::string temp_line = line;
                // set temp_line to lower case for ignore case parse if option "i"
                if (i) {
                    std::transform(temp_line.begin(), temp_line.end(), temp_line.begin(), ::tolower);
                }

                // find if search is on the line
                if (temp_line.find(search) != std::string::npos) {
                }
                // output line if it doesn't contain search
                else {
                    // print line number if option "l"
                    if (l) {
                        std::cout << line_number << ":    ";
                    }
                    occurs++;
                    std::cout << line << std::endl;
                }
            }
        }
        // nonreverse parse
        else {
            // iterate over file's lines one by one
            while (std::getline(iFile, line)) {
                line_number++;

                std::string temp_line = line;
                // set temp_line to lower case for ignore case parse if option "i"
                if (i) {
                    std::transform(temp_line.begin(), temp_line.end(), temp_line.begin(), ::tolower);
                }

                // find if search is on the line
                if (temp_line.find(search) != std::string::npos) {
                    // print line number if option "l"
                    if (l) {
                        std::cout << line_number << ":    ";
                    }

                    std::cout << line << std::endl;
                    occurs++;
                }
            }
        }

        std::cout << std::endl;

        // output occurances if option "o"
        if (o) {
            std::cout << "Occurrences of lines containing \"" << search << "\": " << occurs << std::endl << std::endl;
        }

        iFile.close();
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    std::string options;
    std::string search;
    std::string file;

    // determine what to pass to grep function

    //standard grep
    if (argc == 1) {
        search = "";
        file = "";
        options = "";
    }
    // grep with file
    else if (argc == 3) {
        search = argv[1];
        file = argv[2];
        options = "";
    }
    // grep with file and options
    else if (argc == 4) {
        options = argv[1];
        search = argv[2];
        file = argv[3];  
    }
    else {
        std::cerr << "Usage: .\\mygrep.exe <options> <string> <filename>" << std::endl << std::endl;
        return 1;
    }


    // use grep function
    if (grep(options, search, file) == 1) {
        return 1;
    }
    return 0;
}
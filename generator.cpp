/***
 * copy.cpp
 *
 * Copy the file named argv[1] to a new file named in argv[2] or stdout.
 *
 ***/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc == 1 || std::string("--help") == argv[1]) {
        std::cerr << argv[0] << " old-file [new-file]]" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Open input and output files
    // XXX std::cerr << argv[1] << std::endl;
    std::ifstream in(argv[1], std::ios::in | std::ios::binary);
    if (argc > 2) {
        // XXX std::cerr << argv[2] << std::endl;
        std::ofstream out(argv[2],
                          std::ios::out | std::ios::binary | std::ios::trunc);

        // copy of input to output file
        out << in.rdbuf();
        out.flush();
        if (out && in) {
            exit(EXIT_SUCCESS);
        }
    } else {
        // copy file contents to cout
        std::cout << in.rdbuf();
        std::cout << std::endl;

        if (std::cout && in) {
            exit(EXIT_SUCCESS);
        }
    }

    exit(EXIT_FAILURE);
}

#include <iostream>

#include <miscellaneous.hpp>
#include <version.h>

// Function to return how many digits are in an int
int Djinni::Miscellaneous::digit_num(int x)
{
    int digs = 0;
    if (x < 0) {
        digs++;
    }
    while (x) {
        x /= 10;
        digs++;
    }
    return digs;
}

// Print the help text for argument '--help'
void Djinni::Miscellaneous::print_help()
{
    std::cout << "Djinni - Text Editor " << VERSION_STRING << '\n';
    std::cout << "usage: djinni [file]		Edit some file" << '\n';
    std::cout << "   or: djinni [--help | --version]" << '\n';
    std::cout << '\n';
    std::cout << "Arguments:" << '\n';
    std::cout << "--help:			Show this message" << '\n';
    std::cout << "--version:		Show the version number" << '\n';
    std::cout << '\n';
    std::cout << "Key in Djinni:" << '\n';
    std::cout << "<ctrl>B: 			Quit Djinni" << '\n';
    std::cout << "<ctrl>S:			Save current file" << '\n';
    std::cout << "<ctrl>D:			Open shell" << '\n';
}

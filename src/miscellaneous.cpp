#include <miscellaneous.hpp>

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

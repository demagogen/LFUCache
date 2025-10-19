#include "utils.h"

bool check_input(std::string_view error_message)
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cout << error_message << std::endl;

        return false;
    }

    return true;
}

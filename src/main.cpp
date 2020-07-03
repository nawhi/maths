#include <iostream>
#include <fstream>
#include <matrix.h>

/**
 * Read a comma-separated line of integers into a vector.
 * @param line the raw string to read
 * @return a vector containing all comma-separated integers
 *         on the line
 */
std::vector<int> parse_line(const std::string& line)
{
    std::stringstream ss(line);
    std::vector<int> res;
    int i;
    while (ss >> i)
    {
        res.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    return res;
}

/**
 * @param filename path to a csv style file containing a 4x4 
 *                 matrix of ints. Each row should be separated
 *                 by a newline and each entry by a comma
 * @return a 4x4 Matrix of ints with the matrix described
 *         in the csv file
 */
Matrix<int, 4> read_csv(const std::string& filename)
{
    std::ifstream fs(filename);
    if (!fs.good())
        throw std::runtime_error("Open failed");
    std::vector<std::vector<int>> v;
    for (std::string line; std::getline(fs, line); )
        v.push_back(parse_line(line));

    std::cout << "Matrix is:" << std::endl;
    for (const auto& i: v)
    {
        for (const auto& j: i)
            std::cout << j << ",";
        std::cout << std::endl;
    }
    return Matrix<int, 4>(v);
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cerr << "Specify a file to parse" << std::endl;
        return EXIT_FAILURE;
    }

    auto filename = argv[1];
    try
    {
        auto mx = read_csv(filename);
        std::cout << mx << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "read failed: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

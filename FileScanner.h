#ifndef FILESCANNER_H
#define FILESCANNER_H

#include <queue>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <istream>
#include <sstream>
#include <iterator>
#include <tuple>

class FileScanner
{
public:
    std::vector<std::tuple<int, int, int>> processCmd();
};

#endif //FILESCANNER_H
#include "FileScanner.h"

std::vector<std::tuple<int, int, int>> FileScanner::processCmd()
{
    std::string input1, input2;
    std::cout << "Input init file name." << std::endl;
    std::cin >> input1;
    std::cout << "Input commands file." << std::endl;
    std::cin >> input2;
    std::vector<std::tuple<int, int, int>> initVector;
    try
    {
        std::string tempString;
        std::ifstream initFile(input1);
        if (initFile.is_open())
        {
            std::vector<std::string> tempVector;
            while (initFile.peek() != EOF)
            {
                std::getline(initFile, tempString);
                tempVector.push_back(tempString);
            }
            initFile.close();
            std::ifstream cmdFile(input2);
            if (cmdFile.is_open())
            {
                while (cmdFile.peek() != EOF)
                {
                    std::getline(cmdFile, tempString);
                    tempVector.push_back(tempString);
                }
            }
            cmdFile.close();
            for (int a = 0; a < 3; a++)
            {
                std::istringstream iss(tempVector[a]);
                std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                    std::istream_iterator<std::string>());
                if (a == 0)
                {
                    for (int i = 0; i < tokens.size(); i += 2)
                    {
                        std::tuple<int, int, int> temp = 
                            std::make_tuple(-2, std::stoi(tokens[i]), std::stoi(tokens[i+1]));
                        initVector.push_back(temp);
                    }
                }
                else if (a == 1)
                {
                    for (int i = 0; i < tokens.size(); i += 3)
                    {
                        std::tuple<int, int, int> temp = 
                            std::make_tuple(std::stoi(tokens[i]), std::stoi(tokens[i+1]), std::stoi(tokens[i+2]));
                        initVector.push_back(temp);
                    }
                }
                else if (a == 2)
                {
                    for (int i = 0; i < tokens.size(); i += 2)
                    {
                        std::tuple<int, int, int> temp = 
                            std::make_tuple(-3, std::stoi(tokens[i]), std::stoi(tokens[i+1]));
                        initVector.push_back(temp);
                    }
                }
            }
        }
    }
    catch(std::exception& e)
    {
        std::cout << "File Error: Cannot Open" << std::endl;
    }
    return initVector;
}
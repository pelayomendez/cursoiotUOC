#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
  std::ifstream input("texto.txt");
  std::string file_content((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
  std::cout << file_content << std::endl;
  return 0;
}
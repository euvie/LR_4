#include <Analyzer.hpp>
#include <iostream>
#include <boost/filesystem.hpp>

int main(int argc, char* argv[]) {
  boost::filesystem::path path_to_ftp;
  if (argc == 1){
    path_to_ftp = boost::filesystem::current_path();
  }
  else if (argc == 2){
    path_to_ftp = argv[1];
  }
  else {
    throw std::runtime_error("Too many arguments");
  }
  Analyzer test(path_to_ftp);
  test.analyze_directory(path_to_ftp, std::cout);
  test.show_information(std::cout);
  return 0;
}
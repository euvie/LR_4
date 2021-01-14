// Copyright 2020 euvie

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <boost/filesystem.hpp>
#include <vector>

class Analyzer{

 public:

  Analyzer(const boost::filesystem::path path);
  void analyze_directory(const boost::filesystem::path &p, std::ostream &out);
  bool right_filename(const boost::filesystem::path &p);
  std::string broker_name(const boost::filesystem::path &ps);
  std::string what_account(std::string &s);
  std::string what_date(std::string &s);
  void full_vector(std::string broker, std::string account, std::string data);
  bool documents_list(boost::filesystem::path p, std::ostream &out);
  void show_information(std::ostream &out);


 private:
  boost::filesystem::path path_to_FTP;
  const std::string extention = ".txt";
  const size_t filename_size = 29;

  std::vector<std::string> _broker;
  std::vector<std::string> _account;
  std::vector<long int> _files;
  std::vector<long int> _lastdate;
};


#endif // INCLUDE_HEADER_HPP_
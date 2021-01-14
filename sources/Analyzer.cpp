// Copyright 2020 euvie

#include <Analyzer.hpp>
#include <iostream>

using namespace boost::filesystem; //using namespace

Analyzer::Analyzer(const boost::filesystem::path path):
    path_to_FTP(path)

{
  if(!is_directory(path_to_FTP))
  {
    throw std::runtime_error("Not a direcotry");
  }
  if(!exists(path_to_FTP))
  {
    throw std::runtime_error("Directory doesn't exist");
  }
  if(is_symlink(path_to_FTP))
  {
    path_to_FTP = read_symlink(path);
  }
}

void Analyzer::analyze_directory(const boost::filesystem::path &p,
                                 std::ostream &out) {
  for (const directory_entry& x : directory_iterator{p}) {
    if (is_directory(x.path())) {
      analyze_directory(x.path(), out);
    }
    else if (right_filename(x.path())) {
      documents_list(x.path(), out);
    }
  }
}

bool Analyzer::right_filename(const boost::filesystem::path &p) {
  if (p.extension() == extention && p.filename().size()
                                    == filename_size) {
    return true;
  } else
    return false;
}

std::string Analyzer::broker_name(const boost::filesystem::path &p) {
  return p.parent_path().filename().string();
}

std::string Analyzer::what_account(std::string &s) {
  std::string account = s.substr(8,8);
  return account;
}

std::string Analyzer::what_date(std::string &s) {
  std::string date = s.substr(17,8);
  return date;
}

void Analyzer::full_vector(std::string broker,
                           std::string account, std::string data) {
  std::vector<std::string>::iterator it = std::find(_account.begin(),
                                                    _account.end(),
                                                    account);
  std::vector<std::string>::difference_type index = std::distance
      (_account.begin(), it);
  if(_account.size() == (size_t) index) {
    _account.push_back(account);
    _broker.push_back(broker);
    _files.push_back(1);
    _lastdate.push_back(std::stoi(data));
  }else if (_broker[index] == broker){
    ++_files[index];
    if (_lastdate[index] > std::stoi(data)){
      _lastdate[index] = _lastdate[index];
    }
    else
    {
      _lastdate[index] = std::stoi(data);
    }
  }
}

bool Analyzer::documents_list(path p, std::ostream &out) {
  if(right_filename(p)) {
    std::string file_name = p.filename().string();
    std::string account = what_account(file_name);
    std::string data = what_date(file_name);
    std::string broker = broker_name(p);

    if (account.size() == 0 || data.size() == 0 || broker.size() == 0)
      return false;
    out<<broker<<" "<<file_name<<std::endl;
    full_vector(broker, account, data);
    return true;
  }
  else
    return false;
}

void Analyzer::show_information(std::ostream &out){
  for (size_t i = 0; i < _account.size(); ++i){
    out << "broker:" << _broker[i] << " account:" << _account[i] <<
        " files:" << _files[i] << " lastdate:" << _lastdate[i] << std::endl;
  }
}

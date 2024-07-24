#include <algorithm>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct City;
static std::vector<City> data{};
static std::vector<std::string> city_names{};
static size_t city_count = 0;

static std::map<std::string, City *> data_mmc;

struct City {
  size_t count;
  double min = 400000.0, max = -400000.0, sum = 0.0;
  void set(double n) {
    if (n > max) {
      max = n;
    }
    if (n < min) {
      min = n;
    }
    sum += n;
    count += 1;
  }
};

template <class p_K> class QVector {
public:
  QVector(std::initializer_list<p_K *> pqK) : _pqK(pqK) {}
  QVector() : _pqK(new std::vector<p_K *>(sizeof(p_K *), 0)) {}

  p_K *operator[](size_t idx) { return _pqK[idx]; }

  std::vector<p_K *> _pqK;
};

void PrintCity(const std::pair<std::string, City *> &city) {
  std::cout << city.first << ": ("
            << "sum: " << (city.second)->sum << ", "
            << "min: " << (city.second)->min << ", "
            << "max: " << (city.second)->max << ")" << std::endl;
}

void PrintMap(const std::map<std::string, City *> &m) {
  for (auto &k : m) {
    PrintCity(k);
  }
}

void split_string(const std::string &str, std::string &city_name,
                  double &value) {
  const std::string delim = ";";
  std::string::size_type loc = str.find(delim);

  if (loc == std::string::npos)
    return;

  city_name = str.substr(0, loc);
  value = std::stod(str.substr(loc + 1, str.length() - 1));
}

void read_file(const std::string &file_name) {
  std::ifstream file;
  file.open(file_name);

  std::string line = "";

  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::string city_name = "";
      double value = 0.0;
      split_string(line, city_name, value);

      if (data_mmc.find(city_name) == data_mmc.end()) {
        City *cc;
        cc->set(value);
        data_mmc[city_name] = cc;
        delete cc;
      } else {
        (data_mmc[city_name])->set(value);
      }
    }
  }
}

static const std::string file_name = "measurements.txt";

int main(int argc, char *argv[]) {
  read_file(file_name);
  PrintMap(data_mmc);
  return 0;
}

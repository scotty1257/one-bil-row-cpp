#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

struct City;
static std::vector<City *> data{};
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
        City *cc = new City();
        cc->set(value);
        data_mmc[city_name] = cc;
      } else {
        (data_mmc[city_name])->set(value);
      }

      // std::vector<std::string>::iterator city_find =
      //     std::find(city_names.begin(), city_names.end(), city_name);

      // The city does not exist in the Data Array
      // if (city_find == std::end(city_names)) {
      //   City *city = new City();
      //   city->set(value);
      //   data.push_back(city);
      //
      // } else { // The city is IN the data array
      //   bool city_in_place = false;
      //   size_t k = 0;
      //
      //   for (k = 0; k < data.size(); k++) {
      //     if (data[k]->name == city_name) {
      //       city_in_place = true;
      //       data[k]->set(city_name, value);
      //     }
      //   }
      // }
    }
  }
}

static const std::string file_name = "../measurements/my_brc.txt";

int main(int argc, char *argv[]) {
  read_file(file_name);

  // std::for_each(data.begin(), data.end(),
  //               [](const City* cc) { PrintCity(cc); });
  PrintMap(data_mmc);
  return 0;
}

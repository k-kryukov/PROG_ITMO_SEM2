#define _CRT_SECURE_NO_WARNINGS
#define CURL_STATICLIB
#include <curl\curl.h>
#include <string>
#include <fstream>
#include "json/single_include/nlohmann/json.hpp"
#include <iostream>
#include <map>
#include <algorithm>
#include <ctime>

#define DEBUG true

typedef nlohmann::json json;

const unsigned int sleep_time = 10000;

class ExcCur {
public:
    std::unordered_map<std::string, double> cur_price;
    std::unordered_map<std::string, double> average;
    std::unordered_map<std::string, double> median;
    std::unordered_map<std::string, std::vector<double>> sequence;

    ExcCur() = default;
    ~ExcCur() = default;

    void add(std::string name, double price) {
        cur_price[name] = price;
        average[name] = (average[name] * sequence[name].size() + price) / (sequence[name].size() + 1);
        sequence[name].push_back(price);

        auto middle = sequence[name].begin() + sequence[name].size() / 2;
        std::nth_element(sequence[name].begin(), middle, sequence[name].end());
        median[name] = *middle;
    }
};

void output_data(std::string file_name, json const& js, ExcCur& ec);
void update_data(json const& json, ExcCur& ec);
void download_data(std::string& content);
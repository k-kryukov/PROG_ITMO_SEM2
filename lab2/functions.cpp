#include "headers.hpp"

static size_t writer(char* ptr, size_t size, size_t nmemb, std::string* data) {
    if (data) {

        data->append(ptr, size * nmemb);
        return size * nmemb;
    }

    return 0;
}

void download_data(std::string& content) {
    CURL* curl_handle = curl_easy_init();
    CURLcode response;

    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &content);

        curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");

        response = curl_easy_perform(curl_handle);
    }

    curl_easy_cleanup(curl_handle);
}

void update_data(json const& json, ExcCur& ec) {
    for (auto it = json["Valute"].begin(); it != json["Valute"].end(); ++it) {
        std::string name = it.value()["Name"].dump();
        std::string price = it.value()["Value"].dump();
        std::string nominal = it.value()["Nominal"].dump();

        ec.add(name, stod(price) / stoi(nominal));
    }
}

void output_data(std::string file_name, json const& js, ExcCur& ec) {
    std::ofstream fout(file_name);
    fout.precision(4);
    time_t cur_time = time(NULL);
    fout << ctime(&cur_time) << "_____________" << "\n\n";

    for (auto x : ec.cur_price)
        fout << x.first << " -> " << ec.cur_price[x.first]
        << " RUB (AV: " << ec.average[x.first] << ", MED: "
        << ec.median[x.first] << ")" << "\n\n";

    /*for (auto x = js["Valute"].begin(); x != js["Valute"].end(); ++x) {
        auto cur_obj = x.value();
        double real_value = stod(cur_obj["Value"].dump()) / stoi(cur_obj["Nominal"].dump());
        fout << cur_obj["Name"].dump() << " -> " << real_value << " RUB " << "(AV:  endl;
    }*/
}
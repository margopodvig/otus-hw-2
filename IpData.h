#ifndef IPDATA_H
#define IPDATA_H

#include <cstdint>
#include <iostream>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

namespace IpFilter {

struct IpAddress {
  IpAddress() = default;
  constexpr IpAddress(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4)
      : n1(a1), n2(a2), n3(a3), n4(a4) {}
  uint8_t n1;
  uint8_t n2;
  uint8_t n3;
  uint8_t n4;
  static IpAddress parseFromString(const std::string& str);
};

std::ostream& operator<<(std::ostream& os, const IpAddress& address);

constexpr bool operator<(const IpAddress& address, const IpAddress& address1) {
  return std::make_tuple(address.n1, address.n2, address.n3, address.n4) <
         std::make_tuple(address1.n1, address1.n2, address1.n3, address1.n4);
}

constexpr bool operator==(const IpAddress& address, const IpAddress& address1) {
  return address.n1 == address1.n1 && address.n2 == address1.n2 &&
         address.n3 == address1.n3 && address.n4 == address1.n4;
}

constexpr bool operator>(const IpAddress& address, const IpAddress& address1) {
  return !(address < address1) && !(address == address1);
}

void printByConditions(const std::vector<IpFilter::IpAddress>& addresses);
void printGreaterSort(std::vector<IpFilter::IpAddress>& addresses);

template <typename CharT, typename Traits>
static std::vector<IpFilter::IpAddress> startRead(
    std::basic_istream<CharT, Traits>& input) {
  std::string str;
  std::vector<IpFilter::IpAddress> result;
  std::regex regex("\\\t");
  while (std::getline(input, str)) {
    std::vector<std::string> input_line(
        std::sregex_token_iterator(str.begin(), str.end(), regex, -1),
        std::sregex_token_iterator());
    if (input_line.front().size() < 1) {
      continue;
    }

    auto ip = input_line.front();
    result.push_back(IpFilter::IpAddress::parseFromString(ip));
  }

  return result;
}

}  // namespace IpFilter

#endif  // IPDATA_H

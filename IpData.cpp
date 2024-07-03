#include "IpData.h"

#include <sstream>
#include <string>

namespace {

void printVector(const std::vector<IpFilter::IpAddress> &addresses) {
  for (const auto &data : addresses) {
    std::cout << data << std::endl;
  }
}

void printTrueConditions(
    const std::vector<IpFilter::IpAddress> &addresses,
    std::function<bool(const IpFilter::IpAddress &address)> condition) {
  std::vector<IpFilter::IpAddress> result;
  for (const auto &address : addresses) {
    if (condition(address)) {
      result.emplace_back(address);
    }
  }

  printVector(result);
}

}  // namespace

namespace IpFilter {

IpAddress IpAddress::parseFromString(const std::string &str) {
  IpAddress address;
  std::string number;
  std::stringstream ss(number);
  std::regex regex("\\.");
  std::vector<std::string> result(
      std::sregex_token_iterator(str.begin(), str.end(), regex, -1),
      std::sregex_token_iterator());
  if (result.size() < 4) {
    throw std::logic_error("error str need by xx.xx.xx.xx");
  }

  address.n1 = static_cast<uint8_t>(std::stoi(result[0]));
  address.n2 = static_cast<uint8_t>(std::stoi(result[1]));
  address.n3 = static_cast<uint8_t>(std::stoi(result[2]));
  address.n4 = static_cast<uint8_t>(std::stoi(result[3]));
  return address;
}

std::ostream &operator<<(std::ostream &os, const IpAddress &address) {
  return os << static_cast<int>(address.n1) << "."
            << static_cast<int>(address.n2) << "."
            << static_cast<int>(address.n3) << "."
            << static_cast<int>(address.n4);
}

void printByConditions(const std::vector<IpAddress> &addresses) {
  printTrueConditions(addresses, [](const IpFilter::IpAddress address) {
    return address.n1 == 1;
  });
  printTrueConditions(addresses, [](const IpFilter::IpAddress address) {
    return address.n1 == 46 && address.n2 == 70;
  });
  printTrueConditions(addresses, [](const IpFilter::IpAddress address) {
    return address.n1 == 46 || address.n2 == 46 || address.n3 == 46 ||
           address.n4 == 46;
  });
}

void printGreaterSort(std::vector<IpAddress> &addresses) {
  std::sort(addresses.begin(), addresses.end(), std::greater<>());
  printVector(addresses);
}

}  // namespace IpFilter

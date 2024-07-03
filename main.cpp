#include <iostream>

#include "IpData.h"

int main() {
  auto ip_datas = IpFilter::startRead(std::cin);
  IpFilter::printGreaterSort(ip_datas);
  IpFilter::printByConditions(ip_datas);
  return 0;
}

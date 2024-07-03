
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "../IpData.h"

TEST(IpFilter, Test_INPUT) {
  std::string input(
      "1.2.3.4 \t 5.6.7.8 \t 1.1.1.1 \n"
      "2.2.1.4 \t 5.6.7.8 \t 1.1.1.1 \n"
      "3.2.0.4 \t 5.6.7.8 \t 1.1.1.1 \n"
      "3.1.3.4 \t 5.6.7.8 \t 1.1.1.1 \n"
      "0.1.3.4 \t 5.6.7.8 \t 1.1.1.1");

  std::vector<IpFilter::IpAddress> epected_output{
      {1, 2, 3, 4}, {2, 2, 1, 4}, {3, 2, 0, 4}, {3, 1, 3, 4}, {0, 1, 3, 4}};
  std::istringstream stream(input);
  ASSERT_EQ(IpFilter::startRead(stream), epected_output);
}

TEST(IpFilter, Test_INPUT1) {
  std::string input("1.2.3.4 \t 5.6.7.8 \t 1.1.1.1 \n");
  std::vector<IpFilter::IpAddress> epected_output{{1, 2, 3, 4}};
  std::istringstream stream(input);
  ASSERT_EQ(IpFilter::startRead(stream), epected_output);
}

TEST(IpFilter, Test_INPUT2) {
  std::string input("1.2.3.4 \t 5.6.7.8 \t 1.1.1.1 \n 2.3.1.1");
  std::vector<IpFilter::IpAddress> epected_output{{1, 2, 3, 4}, {2, 3, 1, 1}};
  std::istringstream stream(input);
  ASSERT_EQ(IpFilter::startRead(stream), epected_output);
}

TEST(IpFilter, Test_Sort) {
  std::string input(
      "1.2.3.4 \t 5.6.7.8 \t 1.1.1.1 \n "
      "1.2.3.2 \t 4.3.2.1 \t 1.1.1.1");
  std::vector<IpFilter::IpAddress> epected_output{{1, 2, 3, 4}, {1, 2, 3, 2}};
  std::istringstream stream(input);
  auto result = IpFilter::startRead(stream);
  IpFilter::printGreaterSort(result);
  ASSERT_EQ(result, epected_output);
}

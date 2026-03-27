// File: test/exceptions_test_84.cpp

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include "yaml-cpp/exceptions.h"

namespace {

template <typename T>
struct HasKeyNotFoundWithKey {
 private:
  template <typename U>
  static auto test(int)
      -> decltype(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(std::declval<U>()),
                  std::true_type{});

  template <typename>
  static auto test(...) -> std::false_type;

 public:
  static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
std::string ExpectedMessageFor(const T& key) {
  std::stringstream ss;
  ss << key;
  return std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + ss.str();
}

class ExceptionsTest_84 : public ::testing::Test {};

}  // namespace

TEST_F(ExceptionsTest_84, SFINAE_AllowsNumericTypes_84) {
  static_assert(HasKeyNotFoundWithKey<int>::value, "int should be enabled");
  static_assert(HasKeyNotFoundWithKey<unsigned>::value,
                "unsigned should be enabled");
  static_assert(HasKeyNotFoundWithKey<long long>::value,
                "long long should be enabled");
  static_assert(HasKeyNotFoundWithKey<double>::value,
                "double should be enabled");
}

TEST_F(ExceptionsTest_84, SFINAE_RejectsNonNumericTypes_84) {
  static_assert(!HasKeyNotFoundWithKey<std::string>::value,
                "std::string should be disabled");
  static_assert(!HasKeyNotFoundWithKey<const char*>::value,
                "const char* should be disabled");
}

TEST_F(ExceptionsTest_84, FormatsMessageForInt_84) {
  const int key = 7;
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, ExpectedMessageFor(key));
}

TEST_F(ExceptionsTest_84, FormatsMessageForNegativeInt_84) {
  const int key = -123;
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, ExpectedMessageFor(key));
}

TEST_F(ExceptionsTest_84, FormatsMessageForZero_84) {
  const int key = 0;
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, ExpectedMessageFor(key));
}

TEST_F(ExceptionsTest_84, FormatsMessageForUnsignedMax_84) {
  const unsigned key = std::numeric_limits<unsigned>::max();
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, ExpectedMessageFor(key));
}

TEST_F(ExceptionsTest_84, FormatsMessageForLongLongMinAndMax_84) {
  const long long min_key = std::numeric_limits<long long>::min();
  const long long max_key = std::numeric_limits<long long>::max();

  EXPECT_EQ(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(min_key),
            ExpectedMessageFor(min_key));
  EXPECT_EQ(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(max_key),
            ExpectedMessageFor(max_key));
}

TEST_F(ExceptionsTest_84, FormatsMessageForDouble_84) {
  const double key = 3.141592653589793;
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, ExpectedMessageFor(key));
}

TEST_F(ExceptionsTest_84, FormatsMessageForDoubleInfinity_84) {
  const double key = std::numeric_limits<double>::infinity();
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  EXPECT_EQ(msg, ExpectedMessageFor(key));
}

TEST_F(ExceptionsTest_84, FormatsMessageForDoubleNaN_84) {
  const double key = std::numeric_limits<double>::quiet_NaN();
  const std::string msg = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
  // Streaming NaN is implementation-defined in spelling, so generate expected
  // using the same streaming approach.
  EXPECT_EQ(msg, ExpectedMessageFor(key));
}

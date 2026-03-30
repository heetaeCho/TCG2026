// TEST_ID: 88
#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include <yaml-cpp/exceptions.h>

// Detection idiom: can we call YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(T)?
template <typename T, typename = void>
struct IsBadSubscriptWithKeyInvocable : std::false_type {};

template <typename T>
struct IsBadSubscriptWithKeyInvocable<
    T,
    std::void_t<decltype(YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(std::declval<const T&>()))>>
    : std::true_type {};

class ExceptionMsgTest_88 : public ::testing::Test {
protected:
  template <typename T>
  static std::string ExpectedFor(const T& key) {
    std::stringstream ss;
    ss << key;  // expected key formatting uses ostream insertion
    return YAML::ErrorMsg::BAD_SUBSCRIPT + std::string(" (key: \"") + ss.str() + "\")";
  }
};

TEST_F(ExceptionMsgTest_88, SFINAE_AllowsNumericTypes_88) {
  static_assert(IsBadSubscriptWithKeyInvocable<int>::value, "int should be invocable");
  static_assert(IsBadSubscriptWithKeyInvocable<unsigned>::value, "unsigned should be invocable");
  static_assert(IsBadSubscriptWithKeyInvocable<long long>::value, "long long should be invocable");
  static_assert(IsBadSubscriptWithKeyInvocable<double>::value, "double should be invocable");
}

TEST_F(ExceptionMsgTest_88, SFINAE_RejectsNonNumericTypes_88) {
  static_assert(!IsBadSubscriptWithKeyInvocable<std::string>::value,
                "std::string should not be invocable");
  static_assert(!IsBadSubscriptWithKeyInvocable<const char*>::value,
                "const char* should not be invocable");
  static_assert(!IsBadSubscriptWithKeyInvocable<void*>::value, "void* should not be invocable");
}

TEST_F(ExceptionMsgTest_88, FormatsMessageForPositiveIntegerKey_88) {
  const int key = 123;

  std::string result;
  EXPECT_NO_THROW({ result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key); });

  EXPECT_EQ(result, ExpectedFor(key));
  EXPECT_NE(result.find(YAML::ErrorMsg::BAD_SUBSCRIPT), std::string::npos);
  EXPECT_NE(result.find("key:"), std::string::npos);
}

TEST_F(ExceptionMsgTest_88, FormatsMessageForZeroKey_88) {
  const int key = 0;

  std::string result;
  EXPECT_NO_THROW({ result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key); });

  EXPECT_EQ(result, ExpectedFor(key));
}

TEST_F(ExceptionMsgTest_88, FormatsMessageForNegativeIntegerKey_88) {
  const int key = -456;

  std::string result;
  EXPECT_NO_THROW({ result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key); });

  EXPECT_EQ(result, ExpectedFor(key));
}

TEST_F(ExceptionMsgTest_88, FormatsMessageForUint64MaxKey_88) {
  const std::uint64_t key = std::numeric_limits<std::uint64_t>::max();

  std::string result;
  EXPECT_NO_THROW({ result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key); });

  EXPECT_EQ(result, ExpectedFor(key));
}

TEST_F(ExceptionMsgTest_88, FormatsMessageForFloatingPointKey_88) {
  const double key = 3.141592653589793;

  std::string result;
  EXPECT_NO_THROW({ result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key); });

  EXPECT_EQ(result, ExpectedFor(key));
}

TEST_F(ExceptionMsgTest_88, ReturnsNonEmptyString_88) {
  const int key = 7;
  const std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  EXPECT_FALSE(result.empty());
}

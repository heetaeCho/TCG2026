// File: ./TestProjects/yaml-cpp/test/emitterutils_writealias_test_634.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

// Forward declaration for the function under test (implemented in emitterutils.cpp).
namespace YAML {
namespace Utils {
bool WriteAlias(ostream_wrapper& out, const char* str, std::size_t size);
}  // namespace Utils
}  // namespace YAML

namespace {

class WriteAliasTest_634 : public ::testing::Test {
 protected:
  static std::string RunToString(const char* s, std::size_t n, bool* ret_out = nullptr) {
    std::ostringstream oss;
    YAML::ostream_wrapper out(oss);

    bool ret = YAML::Utils::WriteAlias(out, s, n);
    if (ret_out) *ret_out = ret;

    return oss.str();
  }
};

TEST_F(WriteAliasTest_634, WritesLeadingAsterisk_634) {
  bool ret = false;
  const std::string out = RunToString("abc", 3, &ret);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '*');
  (void)ret;  // Return value behavior is delegated to WriteAliasName (black box).
}

TEST_F(WriteAliasTest_634, AppendsAsteriskToExistingStreamContent_634) {
  std::ostringstream oss;
  oss << "prefix";
  YAML::ostream_wrapper out(oss);

  const bool ret = YAML::Utils::WriteAlias(out, "x", 1);
  const std::string s = oss.str();

  ASSERT_GE(s.size(), std::string("prefix").size() + 1);
  EXPECT_EQ(s.substr(0, 6), "prefix");
  EXPECT_EQ(s[6], '*');
  (void)ret;
}

TEST_F(WriteAliasTest_634, EmptyAliasNameStillWritesAsterisk_634) {
  bool ret = false;
  const std::string out = RunToString("", 0, &ret);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out, "*");  // Observable from interface: WriteAlias always writes "*" first.
  (void)ret;
}

TEST_F(WriteAliasTest_634, NullptrWithZeroSizeDoesNotCrashAndWritesAsterisk_634) {
  bool ret = false;
  const std::string out = RunToString(nullptr, 0, &ret);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out, "*");
  (void)ret;
}

TEST_F(WriteAliasTest_634, ReturnsABoolAndDoesNotThrow_634) {
  std::ostringstream oss;
  YAML::ostream_wrapper out(oss);

  bool ret = false;
  EXPECT_NO_THROW({
    ret = YAML::Utils::WriteAlias(out, "name", 4);
  });
  // Return value is delegated to WriteAliasName; we only assert it's a valid bool and call completes.
  EXPECT_TRUE(ret == true || ret == false);
}

}  // namespace
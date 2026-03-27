// File: ./TestProjects/yaml-cpp/test/write_anchor_test_635.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

// Forward declaration (keep tests based on the provided interface).
namespace YAML {
namespace Utils {
bool WriteAnchor(ostream_wrapper& out, const char* str, std::size_t size);
}  // namespace Utils
}  // namespace YAML

namespace {

class WriteAnchorTest_635 : public ::testing::Test {
 protected:
  std::ostringstream oss_;
  YAML::ostream_wrapper out_{oss_};
};

TEST_F(WriteAnchorTest_635, WritesAmpersandPrefixForNonEmptyInput_635) {
  const char* name = "anchor";
  const std::size_t size = 6;

  (void)YAML::Utils::WriteAnchor(out_, name, size);

  const std::string produced = oss_.str();
  ASSERT_FALSE(produced.empty());
  EXPECT_EQ(produced.front(), '&');
}

TEST_F(WriteAnchorTest_635, WritesAmpersandPrefixForEmptySize_635) {
  const char* name = "anchor";
  const std::size_t size = 0;

  (void)YAML::Utils::WriteAnchor(out_, name, size);

  const std::string produced = oss_.str();
  ASSERT_FALSE(produced.empty());
  EXPECT_EQ(produced.front(), '&');
}

TEST_F(WriteAnchorTest_635, AppendsOnMultipleCalls_635) {
  (void)YAML::Utils::WriteAnchor(out_, "a", 1);
  (void)YAML::Utils::WriteAnchor(out_, "b", 1);

  const std::string produced = oss_.str();
  // Observable behavior: each call writes an '&' prefix.
  // We don't assume anything about the alias-name formatting beyond the visible prefix.
  ASSERT_GE(produced.size(), 2u);
  EXPECT_EQ(produced[0], '&');

  // Find the second prefix somewhere after the first character.
  // This avoids inferring how alias names are written (length/content).
  const std::size_t second = produced.find('&', 1);
  EXPECT_NE(second, std::string::npos);
}

TEST_F(WriteAnchorTest_635, ReturnsAStableValueForSameInputs_635) {
  // We don't assume true/false; just that repeated calls with the same inputs
  // (and the same observable write pattern) return the same boolean.
  std::ostringstream oss2;
  YAML::ostream_wrapper out2(oss2);

  const char* name = "same";
  const std::size_t size = 4;

  const bool r1 = YAML::Utils::WriteAnchor(out_, name, size);
  const bool r2 = YAML::Utils::WriteAnchor(out2, name, size);

  EXPECT_EQ(r1, r2);

  const std::string p1 = oss_.str();
  const std::string p2 = oss2.str();
  ASSERT_FALSE(p1.empty());
  ASSERT_FALSE(p2.empty());
  EXPECT_EQ(p1.front(), '&');
  EXPECT_EQ(p2.front(), '&');
}

TEST_F(WriteAnchorTest_635, HandlesSizeSmallerThanCStringLengthWithoutCrashing_635) {
  // Boundary-style input: size truncates the provided C-string view.
  // We only verify observable prefix write and that the call completes.
  const char* name = "truncated";
  const std::size_t size = 3;

  (void)YAML::Utils::WriteAnchor(out_, name, size);

  const std::string produced = oss_.str();
  ASSERT_FALSE(produced.empty());
  EXPECT_EQ(produced.front(), '&');
}

}  // namespace
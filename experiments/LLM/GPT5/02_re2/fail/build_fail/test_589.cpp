// File: pcre_constructor_string_option_test_589.cc
#include <gtest/gtest.h>
#include "re2/util/pcre.h"

namespace {

// Minimal fixture for naming consistency and future extension.
class PCREConstructStringOptionTest_589 : public ::testing::Test {};

TEST_F(PCREConstructStringOptionTest_589, ConstructsWithNormalPattern_589) {
  // Arrange
  std::string pattern = "abc";
  re2::Option option{};  // Do not assume specifics of Option; value-init only.

  // Act & Assert: Constructor should succeed without throwing.
  EXPECT_NO_THROW({
    re2::PCRE re(pattern, option);
  });
}

TEST_F(PCREConstructStringOptionTest_589, StoresGivenPatternForObservation_589) {
  // This test validates only via public API: pattern() must reflect input.
  // No inference about internals—just observable behavior.
  std::string pattern = "(foo|bar)";
  re2::Option option{};

  re2::PCRE re(pattern, option);

  // Observation through the public accessor declared in the header.
  // If pattern() is part of the interface, it's fair to compare values.
  EXPECT_EQ(re.pattern(), pattern);
}

TEST_F(PCREConstructStringOptionTest_589, ConstructsWithEmptyPattern_589) {
  // Boundary condition: empty pattern is accepted by the interface.
  std::string empty_pattern;
  re2::Option option{};

  EXPECT_NO_THROW({
    re2::PCRE re(empty_pattern, option);
  });

  re2::PCRE re(empty_pattern, option);
  EXPECT_EQ(re.pattern(), empty_pattern);
}

TEST_F(PCREConstructStringOptionTest_589, ConstructsWithLargePattern_589) {
  // Boundary-ish condition: a long pattern string.
  // We don't assert performance or internals—only that construction and
  // pattern() reflection are observable and consistent.
  std::string big_pattern(10000, 'a');  // 10k 'a's
  re2::Option option{};

  EXPECT_NO_THROW({
    re2::PCRE re(big_pattern, option);
  });

  re2::PCRE re(big_pattern, option);
  EXPECT_EQ(re.pattern(), big_pattern);
}

}  // namespace

// TEST_ID 794
// Unit tests for Exiv2::DataValue::read(const std::string&)
// File under test: ./TestProjects/exiv2/src/value.cpp

#include <gtest/gtest.h>

#include <string>

// Prefer the public Exiv2 header path if available in the build; otherwise the project may
// provide it as a local include. Adjust include path if your build system differs.
#include "exiv2/value.hpp"

namespace {

class DataValueReadStringTest_794 : public ::testing::Test {
 protected:
  static Exiv2::TypeId AnyTypeId() {
    // Avoid depending on specific enum constants; any valid TypeId should work for parsing
    // a whitespace-separated list of integers through read(std::string).
    return static_cast<Exiv2::TypeId>(0);
  }

  static Exiv2::DataValue MakeValue() { return Exiv2::DataValue(AnyTypeId()); }
};

TEST_F(DataValueReadStringTest_794, ReadSpaceSeparatedIntegersStoresValuesAndReturns0_794) {
  auto dv = MakeValue();

  const int rc = dv.read(std::string("1 2 3"));
  EXPECT_EQ(0, rc);

  ASSERT_EQ(3u, dv.value_.size());
  EXPECT_EQ(1, dv.value_[0]);
  EXPECT_EQ(2, dv.value_[1]);
  EXPECT_EQ(3, dv.value_[2]);
}

TEST_F(DataValueReadStringTest_794, ReadEmptyStringReturns0AndClearsValues_794) {
  auto dv = MakeValue();

  // Seed with some data first.
  ASSERT_EQ(0, dv.read(std::string("9 8")));
  ASSERT_EQ(2u, dv.value_.size());

  const int rc = dv.read(std::string(""));
  EXPECT_EQ(0, rc);
  EXPECT_TRUE(dv.value_.empty());
}

TEST_F(DataValueReadStringTest_794, ReadWithTrailingWhitespaceReturns0AndParsesAllIntegers_794) {
  auto dv = MakeValue();

  const int rc = dv.read(std::string("10 20 30   \n\t"));
  EXPECT_EQ(0, rc);

  ASSERT_EQ(3u, dv.value_.size());
  EXPECT_EQ(10, dv.value_[0]);
  EXPECT_EQ(20, dv.value_[1]);
  EXPECT_EQ(30, dv.value_[2]);
}

TEST_F(DataValueReadStringTest_794, ReadLargeIntegerWithinIntRangeParsesSuccessfully_794) {
  auto dv = MakeValue();

  const int rc = dv.read(std::string("1000000"));
  EXPECT_EQ(0, rc);

  ASSERT_EQ(1u, dv.value_.size());
  EXPECT_EQ(1000000, dv.value_[0]);
}

TEST_F(DataValueReadStringTest_794, ReadWithNonNumericTokenReturns1AndDoesNotModifyExisting_794) {
  auto dv = MakeValue();

  ASSERT_EQ(0, dv.read(std::string("7 6 5")));
  const auto before = dv.value_;

  const int rc = dv.read(std::string("1 a 3"));
  EXPECT_EQ(1, rc);

  // On error, observable behavior: previous parsed values remain unchanged.
  EXPECT_EQ(before, dv.value_);
}

TEST_F(DataValueReadStringTest_794, ReadWithNumericThenGarbageSuffixReturns1AndDoesNotModifyExisting_794) {
  auto dv = MakeValue();

  ASSERT_EQ(0, dv.read(std::string("42")));
  const auto before = dv.value_;

  // "2x" leaves a non-numeric trailing character in the stream; parsing should fail.
  const int rc = dv.read(std::string("1 2x 3"));
  EXPECT_EQ(1, rc);

  EXPECT_EQ(before, dv.value_);
}

}  // namespace
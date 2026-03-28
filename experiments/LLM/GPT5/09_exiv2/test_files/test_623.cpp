// =================================================================================================
// Unit tests for fujimn_int.cpp (printFujiDigitalZoom)
// TEST_ID: 623
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

// Include the implementation file to access the internal-linkage (static) helper.
// This keeps the function under test as a true black box while still allowing calls.
#include "TestProjects/exiv2/src/fujimn_int.cpp"

namespace {

using Exiv2::TypeId;
using Exiv2::Value;

class FujiMnIntTest_623 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeValueFromString(TypeId type, const std::string& s) {
    auto v = Exiv2::Value::create(type);
    // Observable API: populate via Value::read(string). (No assumptions about internals.)
    v->read(s);
    return v;
  }

  static std::string streamValueOnly(const Value& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  }

  static std::string streamFloatDefault(float f) {
    std::ostringstream oss;
    oss << f;
    return oss.str();
  }
};

TEST_F(FujiMnIntTest_623, UnsignedLongSize4_PrintsComputedPrefixAndParenthesizedValue_623) {
  // Arrange: unsignedLong with 4 components
  auto v = makeValueFromString(Exiv2::unsignedLong, "8 16 24 32");
  ASSERT_EQ(v->typeId(), Exiv2::unsignedLong);
  ASSERT_EQ(v->size(), 4U);

  const auto expected_prefix = streamFloatDefault(v->toFloat() / 8.0f);
  const auto expected_value_str = streamValueOnly(*v);
  const auto expected_suffix = "(" + expected_value_str + ")";

  // Act
  std::ostringstream os;
  auto& ret = Exiv2::Internal::printFujiDigitalZoom(os, *v, nullptr);

  // Assert: returns same stream and prints prefix + "(value)"
  EXPECT_EQ(&ret, &os);
  const std::string out = os.str();

  // Must end with "(<value>)"
  ASSERT_GE(out.size(), expected_suffix.size());
  EXPECT_EQ(out.substr(out.size() - expected_suffix.size()), expected_suffix);

  // Must contain the computed prefix before the '('
  const auto pos_paren = out.find('(');
  ASSERT_NE(pos_paren, std::string::npos);
  EXPECT_NE(out.substr(0, pos_paren).find(expected_prefix), std::string::npos);
}

TEST_F(FujiMnIntTest_623, UnsignedLongSizeNot4_PrintsOnlyParenthesizedValue_623) {
  // Arrange: unsignedLong but not size 4
  auto v = makeValueFromString(Exiv2::unsignedLong, "8 16 24");
  ASSERT_EQ(v->typeId(), Exiv2::unsignedLong);
  ASSERT_NE(v->size(), 4U);

  const auto expected_value_str = streamValueOnly(*v);
  const auto expected_out = "(" + expected_value_str + ")";

  // Act
  std::ostringstream os;
  Exiv2::Internal::printFujiDigitalZoom(os, *v, nullptr);

  // Assert: only "(value)" (no numeric prefix)
  EXPECT_EQ(os.str(), expected_out);
}

TEST_F(FujiMnIntTest_623, NonUnsignedLongSize4_PrintsOnlyParenthesizedValue_623) {
  // Arrange: not unsignedLong but size 4
  auto v = makeValueFromString(Exiv2::unsignedShort, "8 16 24 32");
  ASSERT_NE(v->typeId(), Exiv2::unsignedLong);
  ASSERT_EQ(v->size(), 4U);

  const auto expected_value_str = streamValueOnly(*v);
  const auto expected_out = "(" + expected_value_str + ")";

  // Act
  std::ostringstream os;
  Exiv2::Internal::printFujiDigitalZoom(os, *v, nullptr);

  // Assert
  EXPECT_EQ(os.str(), expected_out);
}

TEST_F(FujiMnIntTest_623, ReturnsStreamReference_AllowsChaining_623) {
  // Arrange
  auto v = makeValueFromString(Exiv2::unsignedLong, "8 16 24 32");
  ASSERT_EQ(v->typeId(), Exiv2::unsignedLong);
  ASSERT_EQ(v->size(), 4U);

  // Act
  std::ostringstream os;
  auto& ret = Exiv2::Internal::printFujiDigitalZoom(os, *v, nullptr);
  ret << "X";

  // Assert: chaining worked
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
  EXPECT_EQ(os.str().back(), 'X');
}

}  // namespace
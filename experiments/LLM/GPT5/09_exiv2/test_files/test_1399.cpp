// =================================================================================================
// TEST_ID: 1399
// File: test_tags_int_print0x9101_1399.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "tags_int.hpp"   // Exiv2::Internal::print0x9101
#include "value.hpp"      // Exiv2::Value, Exiv2::TypeId

namespace {

using Exiv2::Internal::print0x9101;

// Helper: build a Value that yields the provided integers via count()/toInt64(i).
static Exiv2::Value::UniquePtr makeSignedLongValueFromInts(const std::vector<long long>& ints) {
  // Use a numeric type that supports toInt64. signedLong is widely supported in Exiv2.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
  EXPECT_TRUE(static_cast<bool>(v));

  // Many Exiv2 numeric Value implementations parse space-separated numbers via read().
  // This is a public API of Value; we only rely on observable behavior of print0x9101.
  std::ostringstream ss;
  for (size_t i = 0; i < ints.size(); ++i) {
    if (i) ss << ' ';
    ss << ints[i];
  }
  // If parsing fails in a given build configuration, v may remain empty; tests that rely
  // on it will fail and reveal mismatch with the actual Value parsing behavior.
  v->read(ss.str());
  return v;
}

class TagsIntPrint0x9101Test_1399 : public ::testing::Test {};

}  // namespace

TEST_F(TagsIntPrint0x9101Test_1399, ReturnsSameStreamReference_1399) {
  auto v = makeSignedLongValueFromInts({1});
  std::ostringstream os;

  std::ostream& ret = print0x9101(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(TagsIntPrint0x9101Test_1399, EmptyValueProducesEmptyOutput_1399) {
  auto v = makeSignedLongValueFromInts({});
  std::ostringstream os;

  print0x9101(os, *v, nullptr);

  EXPECT_TRUE(os.str().empty());
}

TEST_F(TagsIntPrint0x9101Test_1399, ZeroProducesNoOutput_1399) {
  auto v = makeSignedLongValueFromInts({0});
  std::ostringstream os;

  print0x9101(os, *v, nullptr);

  EXPECT_EQ(os.str(), "");
}

TEST_F(TagsIntPrint0x9101Test_1399, KnownMappingsProduceExpectedTokens_1399) {
  auto v = makeSignedLongValueFromInts({1, 2, 3, 4, 5, 6});
  std::ostringstream os;

  print0x9101(os, *v, nullptr);

  // Concatenated without separators per the observable stream output.
  EXPECT_EQ(os.str(), "YCbCrRGB");
}

TEST_F(TagsIntPrint0x9101Test_1399, UnknownPositiveValueIsParenthesized_1399) {
  auto v = makeSignedLongValueFromInts({7});
  std::ostringstream os;

  print0x9101(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(7)");
}

TEST_F(TagsIntPrint0x9101Test_1399, NegativeValueIsParenthesized_1399) {
  auto v = makeSignedLongValueFromInts({-1});
  std::ostringstream os;

  print0x9101(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(-1)");
}

TEST_F(TagsIntPrint0x9101Test_1399, MixedValuesConcatenateInOrder_1399) {
  auto v = makeSignedLongValueFromInts({0, 1, 7, 2, -3, 6});
  std::ostringstream os;

  print0x9101(os, *v, nullptr);

  // 0 => nothing, 1 => Y, 7 => (7), 2 => Cb, -3 => (-3), 6 => B
  EXPECT_EQ(os.str(), "Y(7)Cb(-3)B");
}

TEST_F(TagsIntPrint0x9101Test_1399, LargeInt64ValueIsParenthesized_1399) {
  const long long kLarge = 9223372036854775807LL;  // max int64_t
  auto v = makeSignedLongValueFromInts({kLarge});
  std::ostringstream os;

  print0x9101(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(9223372036854775807)");
}
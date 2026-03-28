// =================================================================================================
// TEST_ID: 1588
// File: test_sonymn_int_printWhiteBalanceFineTune_1588.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <sstream>
#include <string>

// Exiv2 headers (adjust include paths if your test target already exposes these)
#include "exiv2/exif.hpp"
#include "sonymn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::Value;
using Exiv2::TypeId;

// Helper: render the function output to string.
static std::string Render(SonyMakerNote& mn, const Value& v, const ExifData* ed = nullptr) {
  std::ostringstream os;
  mn.printWhiteBalanceFineTune(os, v, ed);
  return os.str();
}

class SonyMnWhiteBalanceFineTuneTest_1588 : public ::testing::Test {
 protected:
  SonyMakerNote mn_;
  ExifData exif_;
};

}  // namespace

// Normal operation: when count == 1 and typeId == unsignedLong, it prints a signed 32-bit integer
// derived from the value's first uint32.
TEST_F(SonyMnWhiteBalanceFineTuneTest_1588, PrintsSignedInt32ForSingleUnsignedLong_1588) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0U, v->count());

  ASSERT_EQ(0, v->read("123"));  // one item
  ASSERT_EQ(1U, v->count());
  ASSERT_EQ(Exiv2::unsignedLong, v->typeId());

  const std::string out = Render(mn_, *v, &exif_);
  EXPECT_EQ("123", out);
}

// Boundary: value == 0 should print "0" (still normal path).
TEST_F(SonyMnWhiteBalanceFineTuneTest_1588, PrintsZeroForSingleUnsignedLongZero_1588) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  ASSERT_EQ(0, v->read("0"));
  ASSERT_EQ(1U, v->count());
  ASSERT_EQ(Exiv2::unsignedLong, v->typeId());

  const std::string out = Render(mn_, *v, nullptr);  // ExifData* unused by interface
  EXPECT_EQ("0", out);
}

// Boundary: max uint32 should wrap to int32(-1) when casted to int32_t, observable as "-1".
TEST_F(SonyMnWhiteBalanceFineTuneTest_1588, PrintsMinusOneForUint32Max_1588) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  // 4294967295 == UINT32_MAX
  ASSERT_EQ(0, v->read("4294967295"));
  ASSERT_EQ(1U, v->count());
  ASSERT_EQ(Exiv2::unsignedLong, v->typeId());

  const std::string out = Render(mn_, *v, &exif_);
  EXPECT_EQ("-1", out);
}

// Error/exceptional (observable): if count != 1, it prints "(<value>)".
// Use two items to force count != 1.
TEST_F(SonyMnWhiteBalanceFineTuneTest_1588, WrapsInParensWhenCountNotOne_1588) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  ASSERT_EQ(0, v->read("1 2"));  // two items
  ASSERT_EQ(2U, v->count());

  const std::string expected_inner = v->toString();
  const std::string out = Render(mn_, *v, &exif_);

  EXPECT_EQ("(" + expected_inner + ")", out);
}

// Error/exceptional (observable): if typeId != unsignedLong, it prints "(<value>)".
TEST_F(SonyMnWhiteBalanceFineTuneTest_1588, WrapsInParensWhenTypeIsNotUnsignedLong_1588) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
  ASSERT_NE(v.get(), nullptr);

  ASSERT_EQ(0, v->read("42"));
  ASSERT_EQ(1U, v->count());
  ASSERT_NE(Exiv2::unsignedLong, v->typeId());

  const std::string expected_inner = v->toString();
  const std::string out = Render(mn_, *v, &exif_);

  EXPECT_EQ("(" + expected_inner + ")", out);
}

// Boundary/error: empty value (count == 0) should take the "(<value>)" path.
TEST_F(SonyMnWhiteBalanceFineTuneTest_1588, WrapsInParensWhenValueIsEmpty_1588) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  // Do not read anything -> count() == 0
  ASSERT_EQ(0U, v->count());
  ASSERT_EQ(Exiv2::unsignedLong, v->typeId());

  const std::string expected_inner = v->toString();
  const std::string out = Render(mn_, *v, &exif_);

  EXPECT_EQ("(" + expected_inner + ")", out);
}

// Verification: function must return the same ostream it was given (supports chaining).
TEST_F(SonyMnWhiteBalanceFineTuneTest_1588, ReturnsSameOstreamReference_1588) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  ASSERT_EQ(0, v->read("7"));
  std::ostringstream os;

  std::ostream& ret = mn_.printWhiteBalanceFineTune(os, *v, &exif_);
  EXPECT_EQ(&os, &ret);

  // Also ensure content was written.
  EXPECT_EQ("7", os.str());
}
// =================================================================================================
// TestProjects/exiv2/src/value_test_830.cpp
//
// Unit tests for Exiv2::XmpValue::xmpStruct() based strictly on the public interface.
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

namespace {

// Fixture dedicated to TEST_ID 830
class XmpValueTest_830 : public ::testing::Test {
 protected:
  Exiv2::XmpValue value_;
};

TEST_F(XmpValueTest_830, DefaultXmpStructIsXsNone_830) {
  // Observable behavior: default-constructed XmpValue reports its current struct type.
  EXPECT_EQ(Exiv2::XmpValue::xsNone, value_.xmpStruct());
}

TEST_F(XmpValueTest_830, XmpStructCallableOnConstObject_830) {
  const Exiv2::XmpValue& cref = value_;
  EXPECT_EQ(Exiv2::XmpValue::xsNone, cref.xmpStruct());
}

TEST_F(XmpValueTest_830, SetXmpStructXsNoneIsReflectedByGetter_830) {
  // Using only known enumerator from the provided interface snippet.
  value_.setXmpStruct(Exiv2::XmpValue::xsNone);
  EXPECT_EQ(Exiv2::XmpValue::xsNone, value_.xmpStruct());
}

TEST_F(XmpValueTest_830, SetXmpStructIsIdempotentForSameValue_830) {
  value_.setXmpStruct(Exiv2::XmpValue::xsNone);
  const auto first = value_.xmpStruct();

  value_.setXmpStruct(Exiv2::XmpValue::xsNone);
  const auto second = value_.xmpStruct();

  EXPECT_EQ(first, second);
  EXPECT_EQ(Exiv2::XmpValue::xsNone, second);
}

}  // namespace
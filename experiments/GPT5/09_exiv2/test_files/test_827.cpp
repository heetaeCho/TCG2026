// File: test_xmpvalue_setxmpstruct_827.cpp

#include <gtest/gtest.h>

#include "exiv2/value.hpp"

namespace {

class XmpValueTest_827 : public ::testing::Test {
 protected:
  Exiv2::XmpValue value_;
};

TEST_F(XmpValueTest_827, DefaultXmpStructIsNone_827) {
  EXPECT_EQ(Exiv2::XmpValue::xsNone, value_.xmpStruct());
}

TEST_F(XmpValueTest_827, SetXmpStructToNoneKeepsNone_827) {
  value_.setXmpStruct(Exiv2::XmpValue::xsNone);
  EXPECT_EQ(Exiv2::XmpValue::xsNone, value_.xmpStruct());
}

TEST_F(XmpValueTest_827, SetXmpStructToNonDefaultIsObservableViaGetter_827) {
  // We intentionally avoid assuming any specific non-xsNone enumerators exist.
  // Using a non-default underlying value keeps this test black-box.
  const auto nonDefault = static_cast<Exiv2::XmpValue::XmpStruct>(1);

  value_.setXmpStruct(nonDefault);
  EXPECT_EQ(nonDefault, value_.xmpStruct());
}

TEST_F(XmpValueTest_827, SetXmpStructOverwritesPreviousValue_827) {
  const auto first = static_cast<Exiv2::XmpValue::XmpStruct>(1);
  const auto second = static_cast<Exiv2::XmpValue::XmpStruct>(2);

  value_.setXmpStruct(first);
  EXPECT_EQ(first, value_.xmpStruct());

  value_.setXmpStruct(second);
  EXPECT_EQ(second, value_.xmpStruct());
}

TEST_F(XmpValueTest_827, SetXmpStructDoesNotChangeXmpArrayType_827) {
  const auto before = value_.xmpArrayType();

  value_.setXmpStruct(static_cast<Exiv2::XmpValue::XmpStruct>(1));

  const auto after = value_.xmpArrayType();
  EXPECT_EQ(before, after);
}

TEST_F(XmpValueTest_827, SetXmpStructAcceptsArbitraryEnumValue_827) {
  // Boundary-ish: use a large underlying value without assuming validity.
  const auto large = static_cast<Exiv2::XmpValue::XmpStruct>(0x7fffffff);

  value_.setXmpStruct(large);
  EXPECT_EQ(large, value_.xmpStruct());
}

}  // namespace
// File: test_xmpvalue_setxmparraytype_826.cpp

#include <gtest/gtest.h>

#include "exiv2/value.hpp"

namespace {

class XmpValueTest_826 : public ::testing::Test {};

TEST_F(XmpValueTest_826, DefaultXmpArrayTypeIsNone_826) {
  Exiv2::XmpValue v;
  EXPECT_EQ(Exiv2::xaNone, v.xmpArrayType());
}

TEST_F(XmpValueTest_826, SetXmpArrayTypeToSeqUpdatesGetter_826) {
  Exiv2::XmpValue v;

  v.setXmpArrayType(Exiv2::xaSeq);

  EXPECT_EQ(Exiv2::xaSeq, v.xmpArrayType());
}

TEST_F(XmpValueTest_826, SetXmpArrayTypeToBagUpdatesGetter_826) {
  Exiv2::XmpValue v;

  v.setXmpArrayType(Exiv2::xaBag);

  EXPECT_EQ(Exiv2::xaBag, v.xmpArrayType());
}

TEST_F(XmpValueTest_826, SetXmpArrayTypeToAltUpdatesGetter_826) {
  Exiv2::XmpValue v;

  v.setXmpArrayType(Exiv2::xaAlt);

  EXPECT_EQ(Exiv2::xaAlt, v.xmpArrayType());
}

TEST_F(XmpValueTest_826, SetXmpArrayTypeBackToNoneUpdatesGetter_826) {
  Exiv2::XmpValue v;

  v.setXmpArrayType(Exiv2::xaSeq);
  ASSERT_EQ(Exiv2::xaSeq, v.xmpArrayType());

  v.setXmpArrayType(Exiv2::xaNone);
  EXPECT_EQ(Exiv2::xaNone, v.xmpArrayType());
}

TEST_F(XmpValueTest_826, SetXmpArrayTypeSameValueIsStable_826) {
  Exiv2::XmpValue v;

  v.setXmpArrayType(Exiv2::xaBag);
  ASSERT_EQ(Exiv2::xaBag, v.xmpArrayType());

  // Boundary-ish: set to same value again; observable behavior should remain stable.
  v.setXmpArrayType(Exiv2::xaBag);
  EXPECT_EQ(Exiv2::xaBag, v.xmpArrayType());
}

}  // namespace
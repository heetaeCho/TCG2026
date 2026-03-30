// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for Exiv2::XmpValue::xmpArrayType(TypeId)
// File under test: ./TestProjects/exiv2/src/value.cpp

#include <gtest/gtest.h>

#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

// NOTE: The function under test is (per provided snippet) a member function:
//   Exiv2::XmpValue::XmpArrayType Exiv2::XmpValue::xmpArrayType(Exiv2::TypeId typeId);
//
// We treat it as a black box and validate observable return values only.

class XmpValueTest_829 : public ::testing::Test {
 protected:
  Exiv2::XmpValue v_;
};

TEST_F(XmpValueTest_829, ReturnsAltForXmpAlt_829) {
  const auto xa = v_.xmpArrayType(Exiv2::xmpAlt);
  EXPECT_EQ(Exiv2::XmpValue::xaAlt, xa);
}

TEST_F(XmpValueTest_829, ReturnsBagForXmpBag_829) {
  const auto xa = v_.xmpArrayType(Exiv2::xmpBag);
  EXPECT_EQ(Exiv2::XmpValue::xaBag, xa);
}

TEST_F(XmpValueTest_829, ReturnsSeqForXmpSeq_829) {
  const auto xa = v_.xmpArrayType(Exiv2::xmpSeq);
  EXPECT_EQ(Exiv2::XmpValue::xaSeq, xa);
}

TEST_F(XmpValueTest_829, ReturnsNoneForNonXmpArrayType_Text_829) {
  // Boundary/negative case: a nearby XMP-ish but not array container type.
  const auto xa = v_.xmpArrayType(Exiv2::xmpText);
  EXPECT_EQ(Exiv2::XmpValue::xaNone, xa);
}

TEST_F(XmpValueTest_829, ReturnsNoneForInvalidTypeId_829) {
  // Error-ish case (observable): invalid enum value should map to default.
  const auto xa = v_.xmpArrayType(Exiv2::invalidTypeId);
  EXPECT_EQ(Exiv2::XmpValue::xaNone, xa);
}

TEST_F(XmpValueTest_829, ReturnsNoneForTypicalNonXmpType_AsciiString_829) {
  const auto xa = v_.xmpArrayType(Exiv2::asciiString);
  EXPECT_EQ(Exiv2::XmpValue::xaNone, xa);
}

TEST_F(XmpValueTest_829, ReturnsNoneForBoundaryEnumValues_FirstAndLast_829) {
  // Boundary conditions: lowest and highest defined values in TypeId enum.
  const auto xa_first = v_.xmpArrayType(Exiv2::unsignedByte);
  const auto xa_last = v_.xmpArrayType(Exiv2::lastTypeId);

  EXPECT_EQ(Exiv2::XmpValue::xaNone, xa_first);
  EXPECT_EQ(Exiv2::XmpValue::xaNone, xa_last);
}

TEST_F(XmpValueTest_829, SameInputIsDeterministic_829) {
  // Normal operation: repeated calls with same input produce same output.
  const auto xa1 = v_.xmpArrayType(Exiv2::xmpBag);
  const auto xa2 = v_.xmpArrayType(Exiv2::xmpBag);
  EXPECT_EQ(xa1, xa2);
  EXPECT_EQ(Exiv2::XmpValue::xaBag, xa1);
}

}  // namespace
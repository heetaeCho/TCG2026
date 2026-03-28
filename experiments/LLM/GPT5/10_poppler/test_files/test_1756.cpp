// StructElement_isBorderStyleName_tests_1756.cc
#include <gtest/gtest.h>

#include "Object.h"

// NOTE:
// isBorderStyleName(...) has internal linkage (static) in StructElement.cc.
// To test it as a black box via its public signature, we include the .cc so the
// function is in this translation unit.
#include "StructElement.cc"

namespace {

Object MakeNameObj(const char *name) {
  // Poppler Object supports creating a Name object via ObjType + string.
  // We do not infer internal logic; we only use the public constructor.
  return Object(objName, name);
}

} // namespace

class StructElementIsBorderStyleNameTest_1756 : public ::testing::Test {};

// Normal operation: accepted border style names should return true.
TEST_F(StructElementIsBorderStyleNameTest_1756, ReturnsTrueForKnownStyleNames_1756) {
  const char *kNames[] = {"None",  "Hidden", "Dotted", "Dashed", "Solid",
                          "Double", "Groove", "Ridge",  "Inset",  "Outset"};

  for (const char *name : kNames) {
    Object o = MakeNameObj(name);
    EXPECT_TRUE(isBorderStyleName(&o)) << "Expected true for name: " << name;
  }
}

// Boundary/negative: unknown name should return false.
TEST_F(StructElementIsBorderStyleNameTest_1756, ReturnsFalseForUnknownName_1756) {
  Object o = MakeNameObj("UnknownStyle");
  EXPECT_FALSE(isBorderStyleName(&o));
}

// Boundary: case sensitivity and exact match behavior.
TEST_F(StructElementIsBorderStyleNameTest_1756, ReturnsFalseForCaseOrWhitespaceVariants_1756) {
  Object lower = MakeNameObj("none");
  EXPECT_FALSE(isBorderStyleName(&lower));

  Object trailingSpace = MakeNameObj("Solid ");
  EXPECT_FALSE(isBorderStyleName(&trailingSpace));

  Object leadingSpace = MakeNameObj(" Solid");
  EXPECT_FALSE(isBorderStyleName(&leadingSpace));

  Object empty = MakeNameObj("");
  EXPECT_FALSE(isBorderStyleName(&empty));
}

// Exceptional/error-like (observable): non-Name Objects should return false (and not crash).
TEST_F(StructElementIsBorderStyleNameTest_1756, ReturnsFalseForNonNameObjects_1756) {
  Object nullObj = Object::null();
  EXPECT_FALSE(isBorderStyleName(&nullObj));

  Object intObj(1);
  EXPECT_FALSE(isBorderStyleName(&intObj));

  Object boolObj(true);
  EXPECT_FALSE(isBorderStyleName(&boolObj));

  Object realObj(3.14);
  EXPECT_FALSE(isBorderStyleName(&realObj));

  // A string object should not be treated as a name.
  Object strObj(std::string("Solid"));
  EXPECT_FALSE(isBorderStyleName(&strObj));
}
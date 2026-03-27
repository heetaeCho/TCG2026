// File: StructElement_isPlacementName_tests_1754.cc

#include <gtest/gtest.h>

#include "Object.h"

// Include the implementation file to access the TU-local static helper.
// This keeps the test black-box with respect to behavior (no reimplementation),
// while still allowing direct invocation of the function under test.
#include "StructElement.cc"

namespace {

Object MakeNameObj(const char *name) {
  // Rely on Poppler's public Object constructor taking ObjType + name string.
  // ObjType is defined by Poppler (via Object.h).
  return Object(objName, name);
}

} // namespace

TEST(PlacementNameTest_1754, ReturnsTrueForKnownPlacementNames_1754)
{
  Object block = MakeNameObj("Block");
  Object inl = MakeNameObj("Inline");
  Object before = MakeNameObj("Before");
  Object start = MakeNameObj("Start");
  Object end = MakeNameObj("End");

  EXPECT_TRUE(isPlacementName(&block));
  EXPECT_TRUE(isPlacementName(&inl));
  EXPECT_TRUE(isPlacementName(&before));
  EXPECT_TRUE(isPlacementName(&start));
  EXPECT_TRUE(isPlacementName(&end));
}

TEST(PlacementNameTest_1754, ReturnsFalseForOtherNameValues_1754)
{
  Object empty = MakeNameObj("");
  Object other1 = MakeNameObj("Blocks");
  Object other2 = MakeNameObj("block");   // case-sensitive check
  Object other3 = MakeNameObj("INLINE");  // case-sensitive check
  Object other4 = MakeNameObj("After");
  Object other5 = MakeNameObj("Middle");
  Object other6 = MakeNameObj(" Start");  // leading space
  Object other7 = MakeNameObj("End ");    // trailing space

  EXPECT_FALSE(isPlacementName(&empty));
  EXPECT_FALSE(isPlacementName(&other1));
  EXPECT_FALSE(isPlacementName(&other2));
  EXPECT_FALSE(isPlacementName(&other3));
  EXPECT_FALSE(isPlacementName(&other4));
  EXPECT_FALSE(isPlacementName(&other5));
  EXPECT_FALSE(isPlacementName(&other6));
  EXPECT_FALSE(isPlacementName(&other7));
}

TEST(PlacementNameTest_1754, ReturnsFalseForNonNameObjects_1754)
{
  Object b(true);
  Object i(123);
  Object r(3.25);
  Object n = Object::null();
  Object e = Object::error();
  Object eof = Object::eof();

  EXPECT_FALSE(isPlacementName(&b));
  EXPECT_FALSE(isPlacementName(&i));
  EXPECT_FALSE(isPlacementName(&r));
  EXPECT_FALSE(isPlacementName(&n));
  EXPECT_FALSE(isPlacementName(&e));
  EXPECT_FALSE(isPlacementName(&eof));
}

TEST(PlacementNameTest_1754, IsStableAcrossRepeatedCalls_1754)
{
  Object ok = MakeNameObj("Inline");
  Object bad = MakeNameObj("InlineX");

  EXPECT_TRUE(isPlacementName(&ok));
  EXPECT_TRUE(isPlacementName(&ok));   // repeat
  EXPECT_FALSE(isPlacementName(&bad));
  EXPECT_FALSE(isPlacementName(&bad)); // repeat
}

TEST(PlacementNameTest_1754, HandlesLongNameStringAsNonMatch_1754)
{
  std::string longName(4096, 'A');
  Object longObj(objName, std::string_view(longName));

  EXPECT_FALSE(isPlacementName(&longObj));
}
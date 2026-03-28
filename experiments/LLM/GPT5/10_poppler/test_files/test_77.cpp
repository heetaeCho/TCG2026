// TEST_ID: 77
//
// Unit tests for Object::isName()
// File under test: ./TestProjects/poppler/poppler/Object.h
//
// Notes:
// - We treat Object as a black box and only verify observable behavior via the public API.
// - isName() uses an internal CHECK_NOT_DEAD guard; we avoid constructing "dead" objects
//   since that state is not constructible/observable from the public interface provided here.

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "poppler/Object.h"
#include "poppler/GooString.h"

namespace {

class ObjectIsNameTest_77 : public ::testing::Test {
protected:
  // Helper to create a name Object using the public constructor (ObjType + string_view)
  static Object MakeName(const char *s) { return Object(objName, s); }
};

TEST_F(ObjectIsNameTest_77, DefaultConstructedIsNotName_77) {
  Object o;
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, NullFactoryIsNotName_77) {
  Object o = Object::null();
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, EofFactoryIsNotName_77) {
  Object o = Object::eof();
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, ErrorFactoryIsNotName_77) {
  Object o = Object::error();
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, NameConstructedWithNonEmptyStringIsName_77) {
  Object o = MakeName("Type");
  EXPECT_TRUE(o.isName());
}

TEST_F(ObjectIsNameTest_77, NameConstructedWithEmptyStringIsName_77) {
  Object o = MakeName("");
  EXPECT_TRUE(o.isName());
}

TEST_F(ObjectIsNameTest_77, NameConstructionWithWhitespaceIsStillName_77) {
  Object o = MakeName("  ");
  EXPECT_TRUE(o.isName());
}

TEST_F(ObjectIsNameTest_77, BoolIsNotName_77) {
  Object o(true);
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, IntIsNotName_77) {
  Object o(123);
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, RealIsNotName_77) {
  Object o(3.14159);
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, Int64IsNotName_77) {
  Object o(static_cast<long long>(1234567890123LL));
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, StringFromStdStringIsNotName_77) {
  Object o(std::string("hello"));
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, StringFromGooStringIsNotName_77) {
  auto gs = std::make_unique<GooString>("hello");
  Object o(std::move(gs));
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, CmdIsNotName_77) {
  Object o(objCmd, "q");
  EXPECT_FALSE(o.isName());
}

TEST_F(ObjectIsNameTest_77, MoveConstructedNamePreservesIsNameTrue_77) {
  Object src = MakeName("Moved");
  Object dst(std::move(src));
  EXPECT_TRUE(dst.isName());
}

TEST_F(ObjectIsNameTest_77, MoveAssignedNamePreservesIsNameTrue_77) {
  Object src = MakeName("Assigned");
  Object dst; // starts as objNone
  dst = std::move(src);
  EXPECT_TRUE(dst.isName());
}

TEST_F(ObjectIsNameTest_77, SetToNullMakesObjectNotName_77) {
  Object o = MakeName("WillBecomeNull");
  ASSERT_TRUE(o.isName());
  o.setToNull();
  EXPECT_FALSE(o.isName());
}

// Boundary-ish: verify that using an explicit ObjType that is NOT objName reports false.
TEST_F(ObjectIsNameTest_77, ExplicitNonNameObjTypeReportsFalse_77) {
  Object o(objString, "not-a-name");
  EXPECT_FALSE(o.isName());
}

// Optional consistency check: if getType() is available, it should align with isName()
// without assuming any internal mapping beyond the enum values exposed.
TEST_F(ObjectIsNameTest_77, IsNameAlignsWithGetTypeForNameAndNonName_77) {
  Object nameObj = MakeName("Align");
  EXPECT_TRUE(nameObj.isName());
  EXPECT_EQ(nameObj.getType(), objName);

  Object nonNameObj(0); // int
  EXPECT_FALSE(nonNameObj.isName());
  EXPECT_NE(nonNameObj.getType(), objName);
}

} // namespace
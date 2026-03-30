// TEST_ID: 70
// File: Object_getType_test_70.cpp
//
// Unit tests for poppler::Object::getType()
// Constraints respected:
// - Treat Object as black box (no internal logic assumptions).
// - Use only public interface.
// - No private state access.
// - Focus on observable behavior via getType() and public constructors/factories.

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "poppler/Object.h"

// Poppler uses GooString; forward usage is via header includes.
// If Object.h already includes GooString definition, this compiles as-is.
// Otherwise, the build system should include the proper Poppler headers.
#include "goo/GooString.h"

namespace {

// Keep tests isolated and minimal: only verify the observable type returned by getType().
class ObjectGetTypeTest_70 : public ::testing::Test {};

TEST_F(ObjectGetTypeTest_70, DefaultConstructedIsNone_70) {
  Object obj;
  EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectGetTypeTest_70, BoolConstructorSetsTypeBool_70) {
  Object objTrue(true);
  Object objFalse(false);
  EXPECT_EQ(objTrue.getType(), objBool);
  EXPECT_EQ(objFalse.getType(), objBool);
}

TEST_F(ObjectGetTypeTest_70, IntConstructorSetsTypeInt_70) {
  Object obj0(0);
  Object objNeg(-1);
  Object objMax(std::numeric_limits<int>::max());
  Object objMin(std::numeric_limits<int>::min());

  EXPECT_EQ(obj0.getType(), objInt);
  EXPECT_EQ(objNeg.getType(), objInt);
  EXPECT_EQ(objMax.getType(), objInt);
  EXPECT_EQ(objMin.getType(), objInt);
}

TEST_F(ObjectGetTypeTest_70, DoubleConstructorSetsTypeReal_70) {
  Object obj0(0.0);
  Object objPi(3.14159);
  Object objNeg(-2.5);

  EXPECT_EQ(obj0.getType(), objReal);
  EXPECT_EQ(objPi.getType(), objReal);
  EXPECT_EQ(objNeg.getType(), objReal);
}

TEST_F(ObjectGetTypeTest_70, Int64ConstructorSetsTypeInt64_70) {
  Object obj0(static_cast<long long>(0));
  Object objBig(static_cast<long long>(std::numeric_limits<long long>::max()));
  Object objSmall(static_cast<long long>(std::numeric_limits<long long>::min()));

  EXPECT_EQ(obj0.getType(), objInt64);
  EXPECT_EQ(objBig.getType(), objInt64);
  EXPECT_EQ(objSmall.getType(), objInt64);
}

TEST_F(ObjectGetTypeTest_70, UniquePtrGooStringConstructorSetsTypeString_70) {
  auto gs = std::make_unique<GooString>("hello");
  Object obj(std::move(gs));
  EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectGetTypeTest_70, RvalueStdStringConstructorSetsTypeString_70) {
  std::string s = "world";
  Object obj(std::move(s));
  EXPECT_EQ(obj.getType(), objString);
}

TEST_F(ObjectGetTypeTest_70, TypeAndStringViewConstructorCanSetName_70) {
  // This uses the public ctor: Object(ObjType typeA, std::string_view v)
  Object obj(objName, std::string_view("MyName"));
  EXPECT_EQ(obj.getType(), objName);
}

TEST_F(ObjectGetTypeTest_70, TypeAndStringViewConstructorCanSetCmd_70) {
  Object obj(objCmd, std::string_view("q"));
  EXPECT_EQ(obj.getType(), objCmd);
}

TEST_F(ObjectGetTypeTest_70, TypeAndStringViewConstructorCanSetHexString_70) {
  Object obj(objHexString, std::string_view("0A0B0C"));
  EXPECT_EQ(obj.getType(), objHexString);
}

TEST_F(ObjectGetTypeTest_70, StaticFactoriesReturnExpectedTypes_70) {
  const Object n = Object::null();
  const Object e = Object::eof();
  const Object err = Object::error();

  EXPECT_EQ(n.getType(), objNull);
  EXPECT_EQ(e.getType(), objEOF);
  EXPECT_EQ(err.getType(), objError);
}

TEST_F(ObjectGetTypeTest_70, MoveConstructionPreservesObservableType_70) {
  Object src(true);
  ASSERT_EQ(src.getType(), objBool);

  Object moved(std::move(src));
  EXPECT_EQ(moved.getType(), objBool);

  // We do NOT assert anything about src after move beyond being safe to call getType()
  // (if calling getType() after move is supported). To stay conservative, we only
  // ensure it doesn't crash by calling it in a death-test-free manner.
  (void)src.getType();
}

TEST_F(ObjectGetTypeTest_70, MoveAssignmentPreservesObservableType_70) {
  Object a(123);
  Object b(false);

  ASSERT_EQ(a.getType(), objInt);
  ASSERT_EQ(b.getType(), objBool);

  a = std::move(b);
  EXPECT_EQ(a.getType(), objBool);

  // As above, avoid assuming moved-from state beyond being destructible/callable.
  (void)b.getType();
}

TEST_F(ObjectGetTypeTest_70, SetToNullChangesTypeToNull_70) {
  Object obj(42);
  ASSERT_EQ(obj.getType(), objInt);

  obj.setToNull();
  EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectGetTypeTest_70, GetTypeCallableOnConstObject_70) {
  const Object obj(7);
  EXPECT_EQ(obj.getType(), objInt);
}

}  // namespace
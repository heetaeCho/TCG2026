// TEST_ID is 82
// Unit tests for poppler::Object::isRef()
//
// File under test: ./TestProjects/poppler/poppler/Object.h
//
// Notes:
// - We treat Object as a black box and only test observable behavior via public API.
// - This test suite focuses on Object::isRef().
// - In this provided interface, there is no clearly constructible public API shown to
//   create an objRef instance directly. Therefore, we thoroughly test the "false"
//   cases for many public constructors/static factories, and we add death tests for
//   CHECK_NOT_DEAD behavior via moved-from objects (commonly marked "dead").
//
// If your build exposes a public way to create a ref Object (e.g., Object(Ref),
// Object::makeRef(...), or similar), add a positive test that expects isRef()==true.

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "poppler/Object.h"
#include "poppler/goo/GooString.h"

namespace {

class ObjectIsRefTest_82 : public ::testing::Test {};

TEST_F(ObjectIsRefTest_82, DefaultConstructedIsNotRef_82) {
  Object obj;
  EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectIsRefTest_82, BoolConstructedIsNotRef_82) {
  Object objTrue(true);
  Object objFalse(false);
  EXPECT_FALSE(objTrue.isRef());
  EXPECT_FALSE(objFalse.isRef());
}

TEST_F(ObjectIsRefTest_82, IntConstructedIsNotRef_82) {
  Object obj0(0);
  Object objNeg(-1);
  Object objBig(123456789);
  EXPECT_FALSE(obj0.isRef());
  EXPECT_FALSE(objNeg.isRef());
  EXPECT_FALSE(objBig.isRef());
}

TEST_F(ObjectIsRefTest_82, Int64ConstructedIsNotRef_82) {
  Object obj0(static_cast<long long>(0));
  Object objNeg(static_cast<long long>(-1));
  Object objBig(static_cast<long long>(1) << 40);
  EXPECT_FALSE(obj0.isRef());
  EXPECT_FALSE(objNeg.isRef());
  EXPECT_FALSE(objBig.isRef());
}

TEST_F(ObjectIsRefTest_82, RealConstructedIsNotRef_82) {
  Object obj0(0.0);
  Object objPi(3.1415926535);
  Object objNeg(-2.5);
  EXPECT_FALSE(obj0.isRef());
  EXPECT_FALSE(objPi.isRef());
  EXPECT_FALSE(objNeg.isRef());
}

TEST_F(ObjectIsRefTest_82, StdStringConstructedIsNotRef_82) {
  Object empty(std::string{});
  Object hello(std::string{"hello"});
  EXPECT_FALSE(empty.isRef());
  EXPECT_FALSE(hello.isRef());
}

TEST_F(ObjectIsRefTest_82, GooStringConstructedIsNotRef_82) {
  auto gsEmpty = std::make_unique<GooString>("");
  auto gsHello = std::make_unique<GooString>("hello");
  Object empty(std::move(gsEmpty));
  Object hello(std::move(gsHello));
  EXPECT_FALSE(empty.isRef());
  EXPECT_FALSE(hello.isRef());
}

TEST_F(ObjectIsRefTest_82, StaticFactoriesAreNotRef_82) {
  Object n = Object::null();
  Object e = Object::eof();
  Object err = Object::error();

  EXPECT_FALSE(n.isRef());
  EXPECT_FALSE(e.isRef());
  EXPECT_FALSE(err.isRef());
}

TEST_F(ObjectIsRefTest_82, SetToNullMakesNotRef_82) {
  Object obj(123);
  ASSERT_FALSE(obj.isRef());
  obj.setToNull();
  EXPECT_FALSE(obj.isRef());
}

TEST_F(ObjectIsRefTest_82, MoveConstructedDestinationPreservesCallableIsRef_82) {
  Object src(42);
  Object dst(std::move(src));
  // We only assert that calling isRef() on the destination is valid and returns false here.
  EXPECT_FALSE(dst.isRef());
}

TEST_F(ObjectIsRefTest_82, MoveAssignedDestinationPreservesCallableIsRef_82) {
  Object src(42);
  Object dst(true);
  dst = std::move(src);
  EXPECT_FALSE(dst.isRef());
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ObjectIsRefTest_82, CallingIsRefOnMovedFromObjectDies_82) {
  Object src(42);
  Object dst(std::move(src));

  // CHECK_NOT_DEAD suggests moved-from objects may be marked "dead".
  // If the implementation does not mark moved-from objects as dead, this test may fail.
  // In that case, remove/adjust this death test based on your project's semantics.
  ASSERT_DEATH({ (void)src.isRef(); }, "");
}

TEST_F(ObjectIsRefTest_82, CallingIsRefAfterMoveAssignmentOnSourceDies_82) {
  Object src(42);
  Object dst(true);
  dst = std::move(src);

  ASSERT_DEATH({ (void)src.isRef(); }, "");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
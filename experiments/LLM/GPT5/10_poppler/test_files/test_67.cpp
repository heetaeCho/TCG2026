// TEST_ID: 67
//
// Unit tests for poppler::Object (Object.h)
//
// Constraints honored:
// - Treat Object as a black box (no private access, no internal logic re-implementation).
// - Use only public interface and observable behavior (return values, type predicates).
// - No mocking needed (no external collaborators in the provided interface).

#include <gtest/gtest.h>

#include <limits>
#include <string>
#include <utility>

#include "poppler/Object.h"

namespace {

class ObjectTest_67 : public ::testing::Test {};

// ---- Construction & basic type predicates ----

TEST_F(ObjectTest_67, DefaultConstructorCreatesNone_67) {
  Object obj;
  EXPECT_TRUE(obj.isNone());
}

TEST_F(ObjectTest_67, NullFactoryCreatesNull_67) {
  Object obj = Object::null();
  EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_67, EofFactoryCreatesEOF_67) {
  Object obj = Object::eof();
  EXPECT_TRUE(obj.isEOF());
}

TEST_F(ObjectTest_67, ErrorFactoryCreatesError_67) {
  Object obj = Object::error();
  EXPECT_TRUE(obj.isError());
}

TEST_F(ObjectTest_67, BoolConstructorSetsBoolAndValue_67) {
  Object t(true);
  Object f(false);

  EXPECT_TRUE(t.isBool());
  EXPECT_TRUE(f.isBool());

  EXPECT_TRUE(t.getBool());
  EXPECT_FALSE(f.getBool());
}

TEST_F(ObjectTest_67, IntConstructorSetsIntAndValue_67) {
  Object a(0);
  Object b(-123);
  Object c(std::numeric_limits<int>::max());

  EXPECT_TRUE(a.isInt());
  EXPECT_TRUE(b.isInt());
  EXPECT_TRUE(c.isInt());

  EXPECT_EQ(a.getInt(), 0);
  EXPECT_EQ(b.getInt(), -123);
  EXPECT_EQ(c.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_67, RealConstructorSetsRealAndValue_67) {
  const double v = 3.141592653589793;
  Object obj(v);

  EXPECT_TRUE(obj.isReal());
  EXPECT_DOUBLE_EQ(obj.getReal(), v);
}

TEST_F(ObjectTest_67, Int64ConstructorSetsInt64AndValue_67) {
  const long long v = (std::numeric_limits<long long>::max)();
  Object obj(v);

  EXPECT_TRUE(obj.isInt64());
  EXPECT_EQ(obj.getInt64(), v);
}

TEST_F(ObjectTest_67, StringRvalueConstructorCreatesString_67) {
  std::string s = "hello";
  Object obj(std::move(s));

  EXPECT_TRUE(obj.isString());
  ASSERT_NE(obj.getString(), nullptr);
  EXPECT_EQ(obj.getString()->toStr(), "hello");
}

// ---- Name/Cmd construction via (ObjType, string_view) ----

TEST_F(ObjectTest_67, NameTypeConstructorAndNameQueries_67) {
  Object nameObj(objName, "MyName");

  EXPECT_TRUE(nameObj.isName());
  EXPECT_TRUE(nameObj.isName("MyName"));
  EXPECT_FALSE(nameObj.isName("OtherName"));

  ASSERT_NE(nameObj.getName(), nullptr);
  EXPECT_STREQ(nameObj.getName(), "MyName");
  EXPECT_EQ(nameObj.getNameString(), "MyName");
}

TEST_F(ObjectTest_67, CmdTypeConstructorAndCmdQueries_67) {
  Object cmdObj(objCmd, "q");

  EXPECT_TRUE(cmdObj.isCmd());
  EXPECT_TRUE(cmdObj.isCmd("q"));
  EXPECT_FALSE(cmdObj.isCmd("Q"));

  ASSERT_NE(cmdObj.getCmd(), nullptr);
  EXPECT_STREQ(cmdObj.getCmd(), "q");
}

// ---- Numeric helpers ----

TEST_F(ObjectTest_67, IsNumAndGetNumWorkForInt_67) {
  Object obj(42);

  EXPECT_TRUE(obj.isNum());

  bool ok = false;
  const double n = obj.getNum(&ok);
  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(n, 42.0);

  EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_67, IsNumAndGetNumWorkForReal_67) {
  Object obj(2.5);

  EXPECT_TRUE(obj.isNum());

  bool ok = false;
  const double n = obj.getNum(&ok);
  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(n, 2.5);

  EXPECT_DOUBLE_EQ(obj.getNum(), 2.5);
}

TEST_F(ObjectTest_67, GetNumWithDefaultValueReturnsSelfForNumbers_67) {
  Object objInt(7);
  Object objReal(7.25);

  EXPECT_DOUBLE_EQ(objInt.getNumWithDefaultValue(-1.0), 7.0);
  EXPECT_DOUBLE_EQ(objReal.getNumWithDefaultValue(-1.0), 7.25);
}

TEST_F(ObjectTest_67, GetNumWithDefaultValueReturnsDefaultForNonNumbers_67) {
  Object obj = Object::null();

  // Observable behavior: API suggests a safe fallback for non-numeric types.
  EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(123.0), 123.0);

  bool ok = true;
  (void)obj.getNum(&ok);
  EXPECT_FALSE(ok);
}

// ---- setToNull boundary / state transition ----

TEST_F(ObjectTest_67, SetToNullTurnsObjectIntoNull_67) {
  Object obj(123);
  ASSERT_TRUE(obj.isInt());

  obj.setToNull();
  EXPECT_TRUE(obj.isNull());
}

// ---- Move operations & lifetime safety ----

TEST_F(ObjectTest_67, MoveConstructorPreservesObservableValue_67) {
  Object src(true);
  ASSERT_TRUE(src.isBool());

  Object dst(std::move(src));
  EXPECT_TRUE(dst.isBool());
  EXPECT_TRUE(dst.getBool());

  // Moved-from object must remain destructible and usable for safe operations.
  src.setToNull();
  EXPECT_TRUE(src.isNull());
}

TEST_F(ObjectTest_67, MoveAssignmentPreservesObservableValue_67) {
  Object src(99);
  Object dst = Object::null();

  ASSERT_TRUE(src.isInt());
  ASSERT_TRUE(dst.isNull());

  dst = std::move(src);

  EXPECT_TRUE(dst.isInt());
  EXPECT_EQ(dst.getInt(), 99);

  // Moved-from remains valid for further operations.
  src.setToNull();
  EXPECT_TRUE(src.isNull());
}

TEST_F(ObjectTest_67, DestructionIsSafeForVariousObjects_67) {
  // This test is about ensuring no crashes/exceptions during destruction
  // across a few representative object kinds.
  {
    Object a;                 // none
    Object b(true);           // bool
    Object c(1);              // int
    Object d(1.0);            // real
    Object e(Object::null()); // null
    Object f(objName, "N");   // name
    Object g(objCmd, "q");    // cmd
    Object h(std::string("s")); // string
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h;
  }
  SUCCEED();
}

} // namespace
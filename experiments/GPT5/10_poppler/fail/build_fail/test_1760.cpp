// File: StructElement_isNumber_tests_1760.cc
#include <gtest/gtest.h>

#include "Object.h"

// NOTE:
// isNumber is a file-local (static) helper in StructElement.cc.
// To test it without re-implementing or altering production code,
// we include the .cc here so the test TU can see the static symbol.
#include "StructElement.cc"

namespace {

class StructElementIsNumberTest_1760 : public ::testing::Test {};

TEST_F(StructElementIsNumberTest_1760, ReturnsSameAsObjectIsNum_ForCommonObjectTypes_1760)
{
  Object intObj(42);
  EXPECT_EQ(isNumber(&intObj), intObj.isNum());

  Object realObj(3.14159);
  EXPECT_EQ(isNumber(&realObj), realObj.isNum());

  Object boolObj(true);
  EXPECT_EQ(isNumber(&boolObj), boolObj.isNum());

  Object nullObj = Object::null();
  EXPECT_EQ(isNumber(&nullObj), nullObj.isNum());

  Object eofObj = Object::eof();
  EXPECT_EQ(isNumber(&eofObj), eofObj.isNum());

  Object errObj = Object::error();
  EXPECT_EQ(isNumber(&errObj), errObj.isNum());
}

TEST_F(StructElementIsNumberTest_1760, ReturnsSameAsObjectIsNum_ForLargeAndNegativeIntegers_1760)
{
  Object negIntObj(-1);
  EXPECT_EQ(isNumber(&negIntObj), negIntObj.isNum());

  Object bigInt64Obj(static_cast<long long>(9223372036854775807LL)); // LLONG_MAX
  EXPECT_EQ(isNumber(&bigInt64Obj), bigInt64Obj.isNum());

  Object smallInt64Obj(static_cast<long long>(-9223372036854775807LL - 1LL)); // LLONG_MIN
  EXPECT_EQ(isNumber(&smallInt64Obj), smallInt64Obj.isNum());
}

TEST_F(StructElementIsNumberTest_1760, ReturnsSameAsObjectIsNum_AfterMoveAssignment_1760)
{
  Object src(123);
  Object dst = Object::null();

  dst = std::move(src);

  // We don't assume what "moved-from" means; we only verify the wrapper
  // matches the observable Object::isNum() on the current object state.
  EXPECT_EQ(isNumber(&dst), dst.isNum());
}

#if GTEST_HAS_DEATH_TEST
TEST_F(StructElementIsNumberTest_1760, DeathOnNullPointer_1760)
{
  // isNumber dereferences the pointer; passing nullptr is an observable error case.
  EXPECT_DEATH({ (void)isNumber(nullptr); }, "");
}
#endif

} // namespace
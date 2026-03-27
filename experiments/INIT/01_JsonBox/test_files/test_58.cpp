// File: tests/ValueGetBooleanTest_58.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueGetBooleanTest_58 : public ::testing::Test {};

// If you want to directly check the EMPTY_BOOL constant:
namespace JsonBox {
  extern const bool EMPTY_BOOL; // Defined in Value.cpp as const _Bool ... = false
}

// 1) Normal operation: boolean values are returned as-is.
TEST_F(ValueGetBooleanTest_58, BooleanTrue_ReturnsTrue_58) {
  Value v(true);
  EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueGetBooleanTest_58, BooleanFalse_ReturnsFalse_58) {
  Value v(false);
  EXPECT_FALSE(v.getBoolean());
}

// 2) Delegation/contract: getBoolean() must match tryGetBoolean(false) for any type.
//    We don't assume conversion rules — we only assert the observable equality.
TEST_F(ValueGetBooleanTest_58, NonBooleanInputs_MatchesTryGetBooleanFalse_58) {
  // Integer
  Value vint(123);
  EXPECT_EQ(vint.getBoolean(), vint.tryGetBoolean(false));

  // Double
  Value vdouble(3.14);
  EXPECT_EQ(vdouble.getBoolean(), vdouble.tryGetBoolean(false));

  // String
  Value vstr(std::string("hello"));
  EXPECT_EQ(vstr.getBoolean(), vstr.tryGetBoolean(false));

  // Object
  Value::Object obj;
  obj["k"] = Value(1);
  Value vobj(obj);
  EXPECT_EQ(vobj.getBoolean(), vobj.tryGetBoolean(false));

  // Array
  Value::Array arr;
  arr.push_back(Value("x"));
  Value varr(arr);
  EXPECT_EQ(varr.getBoolean(), varr.tryGetBoolean(false));

  // Null (default-constructed)
  Value vnull;
  EXPECT_EQ(vnull.getBoolean(), vnull.tryGetBoolean(false));
}

// 3) Boundary/consistency: calling getBoolean() should not change the value's type.
TEST_F(ValueGetBooleanTest_58, GetBoolean_DoesNotChangeType_58) {
  Value vtrue(true);
  auto before_true = vtrue.getType();
  (void)vtrue.getBoolean();
  EXPECT_EQ(before_true, vtrue.getType());

  Value vint(0);
  auto before_int = vint.getType();
  (void)vint.getBoolean();
  EXPECT_EQ(before_int, vint.getType());

  Value vstr("t");
  auto before_str = vstr.getType();
  (void)vstr.getBoolean();
  EXPECT_EQ(before_str, vstr.getType());
}

// 4) Sanity: the EMPTY_BOOL default used by getBoolean() is false (from the TU defining it).
TEST_F(ValueGetBooleanTest_58, EmptyBoolConstant_IsFalse_58) {
  EXPECT_FALSE(JsonBox::EMPTY_BOOL);
}

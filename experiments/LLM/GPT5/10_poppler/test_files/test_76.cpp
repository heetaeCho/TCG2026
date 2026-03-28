// TEST_ID: 76
// Unit tests for Object::isHexString()
// File: poppler/Object.h

#include <gtest/gtest.h>

#include "poppler/Object.h"

class ObjectIsHexStringTest_76 : public ::testing::Test {};

// Normal operation: default-constructed Object should not be a hex string.
TEST_F(ObjectIsHexStringTest_76, DefaultConstructedIsNotHexString_76) {
  Object obj;
  EXPECT_FALSE(obj.isHexString());
}

// Normal operation: Object constructed as objHexString should report true.
TEST_F(ObjectIsHexStringTest_76, ConstructedHexStringReportsTrue_76) {
  Object obj(objHexString, std::string_view("ABCD"));
  EXPECT_TRUE(obj.isHexString());
}

// Boundary: empty payload should still be treated as hex string if type is objHexString.
TEST_F(ObjectIsHexStringTest_76, EmptyHexStringPayloadStillReportsTrue_76) {
  Object obj(objHexString, std::string_view(""));
  EXPECT_TRUE(obj.isHexString());
}

// Boundary: large payload should not change type-based classification.
TEST_F(ObjectIsHexStringTest_76, LargeHexStringPayloadStillReportsTrue_76) {
  std::string big(4096, 'A');
  Object obj(objHexString, std::string_view(big));
  EXPECT_TRUE(obj.isHexString());
}

// Type discrimination: regular string is not a hex string.
TEST_F(ObjectIsHexStringTest_76, RegularStringIsNotHexString_76) {
  Object obj(std::string("ABCD"));
  EXPECT_FALSE(obj.isHexString());
}

// Type discrimination: name/cmd-like types are not hex strings (using ObjType constructor).
TEST_F(ObjectIsHexStringTest_76, NameTypeIsNotHexString_76) {
  Object obj(objName, std::string_view("Name"));
  EXPECT_FALSE(obj.isHexString());
}

// Type discrimination: null object should not be hex string.
TEST_F(ObjectIsHexStringTest_76, NullObjectIsNotHexString_76) {
  Object obj = Object::null();
  EXPECT_FALSE(obj.isHexString());
}

// Type discrimination: error object should not be hex string.
TEST_F(ObjectIsHexStringTest_76, ErrorObjectIsNotHexString_76) {
  Object obj = Object::error();
  EXPECT_FALSE(obj.isHexString());
}

// Boundary/robustness: moved-from hex string object should remain safe to query.
// (We only assert it doesn't crash and returns a boolean; behavior is otherwise unspecified.)
TEST_F(ObjectIsHexStringTest_76, MovedFromObjectIsSafeToQuery_76) {
  Object src(objHexString, std::string_view("ABCD"));
  Object dst(std::move(src));
  (void)dst.isHexString();  // should be safe

  // moved-from object: observable requirement is only that calling doesn't crash
  (void)src.isHexString();
}
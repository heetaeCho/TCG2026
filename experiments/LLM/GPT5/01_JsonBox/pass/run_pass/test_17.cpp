// File: Value_AssignCString_Test_17.cpp
#include <gtest/gtest.h>
#include <map>
#include <vector>
#include <string>
#include "JsonBox/Value.h"

using namespace JsonBox;

//
// TEST_ID: 17
//

// Normal: assigning from const char* sets value to string and stores content
TEST(ValueAssignCStringTest_17, AssignCString_SetsToStringAndStoresContent_17) {
    Value v(123); // start from non-string type
    v = "hello";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(std::string("hello"), v.getString());
}

// Boundary: assigning an empty C-string results in empty string
TEST(ValueAssignCStringTest_17, AssignCString_EmptyString_17) {
    Value v; // default (null)
    v = "";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(std::string(), v.getString());
}

// Normal: re-assigning from const char* overwrites previous string content
TEST(ValueAssignCStringTest_17, AssignCString_OverwritesPreviousString_17) {
    Value v("old");
    v = "new";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(std::string("new"), v.getString());
}

// Normal: return value is a reference to *this, enabling chaining
TEST(ValueAssignCStringTest_17, AssignCString_ReturnsSelfReference_17) {
    Value v;
    Value& r = (v = "abc");
    EXPECT_EQ(&v, &r);              // returned reference is the same object
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(std::string("abc"), v.getString());
}

// Normal: chained assignments behave as expected across multiple Values
TEST(ValueAssignCStringTest_17, AssignCString_ChainingAcrossValues_17) {
    Value a, b;
    a = (b = "x");                  // uses Value=Value after b="x"
    EXPECT_TRUE(a.isString());
    EXPECT_TRUE(b.isString());
    EXPECT_EQ(std::string("x"), a.getString());
    EXPECT_EQ(std::string("x"), b.getString());
}

// Boundary: non-ASCII/UTF-8 bytes via const char* are preserved
TEST(ValueAssignCStringTest_17, AssignCString_PreservesUTF8_17) {
    Value v;
    const char* utf8 = u8"한글🙂";
    v = utf8;
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(std::string(utf8), v.getString());
}

// Type-overwrite cases: object → assign const char*, becomes string
TEST(ValueAssignCStringTest_17, AssignCString_OverwritesFromObject_17) {
    JsonBox::Object obj; // empty object
    Value v(obj);
    v = "obj->str";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(std::string("obj->str"), v.getString());
}

// Type-overwrite cases: array → assign const char*, becomes string
TEST(ValueAssignCStringTest_17, AssignCString_OverwritesFromArray_17) {
    JsonBox::Array arr; // empty array
    Value v(arr);
    v = "arr->str";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(std::string("arr->str"), v.getString());
}

// Type-overwrite cases: boolean/double → assign const char*, becomes string
TEST(ValueAssignCStringTest_17, AssignCString_OverwritesFromScalarTypes_17) {
    Value vb(true);
    vb = "true->str";
    EXPECT_TRUE(vb.isString());
    EXPECT_EQ(std::string("true->str"), vb.getString());

    Value vd(3.14);
    vd = "dbl->str";
    EXPECT_TRUE(vd.isString());
    EXPECT_EQ(std::string("dbl->str"), vd.getString());
}

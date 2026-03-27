// File: Value_OperatorCString_Tests_30.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueOperatorCStringTest_30 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure the Value under test starts as an object so key access is valid,
        // relying only on the public interface.
        v_.setObject(Object{});
    }
    Value v_;
};

// Verifies that operator[](const char*) returns the same reference as operator[](std::string).
TEST_F(ValueOperatorCStringTest_30, DelegatesToStringOverload_SameReference_30) {
    Value& via_cstr  = v_["alpha"];
    Value& via_str   = v_[std::string("alpha")];
    EXPECT_EQ(&via_cstr, &via_str);
}

// Write using const char* key, read back using std::string key.
TEST_F(ValueOperatorCStringTest_30, WriteViaCString_ReadViaString_30) {
    v_["num"] = 42;
    ASSERT_TRUE(v_[std::string("num")].isInteger());
    EXPECT_EQ(42, v_[std::string("num")].getInteger());
}

// Write using std::string key, read back using const char* key.
TEST_F(ValueOperatorCStringTest_30, WriteViaString_ReadViaCString_30) {
    v_[std::string("greet")] = "hello";
    ASSERT_TRUE(v_["greet"].isString());
    EXPECT_EQ(std::string("hello"), v_["greet"].getString());
}

// Boundary: empty-string key should behave consistently across overloads.
TEST_F(ValueOperatorCStringTest_30, EmptyKeyConsistency_30) {
    v_[""] = true;
    ASSERT_TRUE(v_[std::string("")].isBoolean());
    EXPECT_TRUE(v_[std::string("")].getBoolean());
}

// Keys with punctuation/spaces should map identically across overloads.
TEST_F(ValueOperatorCStringTest_30, SpecialCharsKeyConsistency_30) {
    const char* k = "a b.c-d_123";
    v_[k] = 3.14;
    ASSERT_TRUE(v_[std::string(k)].isDouble());
    EXPECT_DOUBLE_EQ(3.14, v_[std::string(k)].getDouble());
}

// Repeated access through both overloads keeps aliasing to the same element.
TEST_F(ValueOperatorCStringTest_30, AliasingAcrossOverloads_30) {
    Value& r1 = v_["same"];
    r1 = 7;
    Value& r2 = v_[std::string("same")];
    EXPECT_EQ(&r1, &r2);
    ASSERT_TRUE(r2.isInteger());
    EXPECT_EQ(7, r2.getInteger());
}

#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueOperatorLessEqualTest_26 : public ::testing::Test {
protected:
    // Helper that asserts the definition of <= matches (< || ==)
    void ExpectLeDefinition(const Value& a, const Value& b) {
        bool le  = (a <= b);
        bool def = (a < b) || (a == b);
        EXPECT_EQ(le, def);
    }
};

// Integers: less / equal / greater
TEST_F(ValueOperatorLessEqualTest_26, IntPairsRespectDefinition_26) {
    ExpectLeDefinition(Value(1), Value(2));   // less
    ExpectLeDefinition(Value(5), Value(5));   // equal
    ExpectLeDefinition(Value(10), Value(3));  // greater
}

// Doubles: less / equal / greater (including fractional)
TEST_F(ValueOperatorLessEqualTest_26, DoublePairsRespectDefinition_26) {
    ExpectLeDefinition(Value(1.5), Value(2.5));   // less
    ExpectLeDefinition(Value(3.0), Value(3.0));   // equal
    ExpectLeDefinition(Value(7.1), Value(7.0));   // greater
}

// Strings: different and equal
TEST_F(ValueOperatorLessEqualTest_26, StringPairsRespectDefinition_26) {
    ExpectLeDefinition(Value("apple"), Value("banana")); // different
    ExpectLeDefinition(Value("test"),  Value("test"));   // equal
    ExpectLeDefinition(Value("zoo"),   Value("ant"));    // different
}

// Booleans: all combinations
TEST_F(ValueOperatorLessEqualTest_26, BooleanPairsRespectDefinition_26) {
    ExpectLeDefinition(Value(false), Value(false));
    ExpectLeDefinition(Value(false), Value(true));
    ExpectLeDefinition(Value(true),  Value(false));
    ExpectLeDefinition(Value(true),  Value(true));
}

// Arrays: empty vs non-empty, and equal arrays
TEST_F(ValueOperatorLessEqualTest_26, ArrayPairsRespectDefinition_26) {
    Array a0;                      // []
    Array a1 = { Value(1) };       // [1]
    Array a2 = { Value(1), Value(2) }; // [1,2]
    ExpectLeDefinition(Value(a0), Value(a1));
    ExpectLeDefinition(Value(a1), Value(a1)); // equal
    ExpectLeDefinition(Value(a2), Value(a1));
}

// Objects: different keys / values, and equal objects
TEST_F(ValueOperatorLessEqualTest_26, ObjectPairsRespectDefinition_26) {
    Object o1; o1["a"] = Value(1);
    Object o2; o2["a"] = Value(2);
    Object o3; o3["b"] = Value(1);
    ExpectLeDefinition(Value(o1), Value(o2));
    ExpectLeDefinition(Value(o1), Value(o1)); // equal
    ExpectLeDefinition(Value(o3), Value(o1)); // different shapes
}

// Mixed types: ensure <= matches (< || ==) without assuming cross-type ordering
TEST_F(ValueOperatorLessEqualTest_26, MixedTypePairsRespectDefinition_26) {
    ExpectLeDefinition(Value(5),        Value("5"));
    ExpectLeDefinition(Value("10"),     Value(10));
    ExpectLeDefinition(Value(true),     Value(1));
    ExpectLeDefinition(Value(3.14),     Value(false));
    ExpectLeDefinition(Value(Array{}),  Value(Object{}));
}

// Null and self-comparison: reflexive behavior via definition
TEST_F(ValueOperatorLessEqualTest_26, NullAndSelfComparisonRespectDefinition_26) {
    Value n;                 // default-constructed (NULL)
    ExpectLeDefinition(n, n);
    Value s("x");
    ExpectLeDefinition(s, s);
    Value i(0);
    ExpectLeDefinition(i, i);
}

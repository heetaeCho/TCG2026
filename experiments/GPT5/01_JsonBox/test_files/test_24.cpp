// File: ValueNotEqualTest_24.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

namespace {

// Helper to assert the != operator mirrors the logical negation of == for a pair.
void ExpectNegationConsistency(const Value& a, const Value& b) {
    EXPECT_EQ(a != b, !(a == b));
}

} // namespace

// Verifies basic reflexive property: a value is not unequal to itself.
TEST(ValueNotEqualTest_24, SelfIsNotUnequal_24) {
    Value v_null;                 // default-constructed (null)
    Value v_str("hello");
    Value v_int(42);
    Value v_double(3.14);
    Value v_bool_true(true);

    EXPECT_FALSE(v_null != v_null);
    EXPECT_FALSE(v_str != v_str);
    EXPECT_FALSE(v_int != v_int);
    EXPECT_FALSE(v_double != v_double);
    EXPECT_FALSE(v_bool_true != v_bool_true);
}

// Ensures operator!= is the exact logical negation of operator== for same-type pairs.
TEST(ValueNotEqualTest_24, NegationConsistency_SameTypePairs_24) {
    ExpectNegationConsistency(Value("a"), Value("a"));
    ExpectNegationConsistency(Value("a"), Value("b"));

    ExpectNegationConsistency(Value(1), Value(1));
    ExpectNegationConsistency(Value(1), Value(2));

    ExpectNegationConsistency(Value(1.0), Value(1.0));
    ExpectNegationConsistency(Value(1.0), Value(2.0));

    ExpectNegationConsistency(Value(true), Value(true));
    ExpectNegationConsistency(Value(true), Value(false));

    Value n1, n2; // both null
    ExpectNegationConsistency(n1, n2);
}

// Ensures operator!= is the logical negation of operator== across different types.
TEST(ValueNotEqualTest_24, NegationConsistency_DifferentTypes_24) {
    ExpectNegationConsistency(Value("1"), Value(1));
    ExpectNegationConsistency(Value(0), Value(false));
    ExpectNegationConsistency(Value(3.0), Value("3"));
    ExpectNegationConsistency(Value(), Value("null"));
}

// Copy construction: copied values compare equal, so != should be false.
TEST(ValueNotEqualTest_24, CopyConstructedValuesAreNotUnequal_24) {
    Value original("copy-me");
    Value copy(original);
    EXPECT_FALSE(copy != original);
    ExpectNegationConsistency(copy, original);
}

// Boundary: empty containers and empty string should not be unequal to identical values.
TEST(ValueNotEqualTest_24, EmptyStringArrayObjectNotUnequal_24) {
    // Empty string
    Value s1(std::string()), s2(std::string());
    EXPECT_FALSE(s1 != s2);
    ExpectNegationConsistency(s1, s2);

    // Empty array
    Array arr1, arr2;
    Value a1(arr1), a2(arr2);
    EXPECT_FALSE(a1 != a2);
    ExpectNegationConsistency(a1, a2);

    // Empty object
    Object o1, o2;
    Value v1(o1), v2(o2);
    EXPECT_FALSE(v1 != v2);
    ExpectNegationConsistency(v1, v2);
}

// Arrays: same contents vs. different contents.
TEST(ValueNotEqualTest_24, ArrayInequalityByContents_24) {
    Array arr_equal_l{ Value(1), Value(2) };
    Array arr_equal_r{ Value(1), Value(2) };
    Value v_equal_l(arr_equal_l), v_equal_r(arr_equal_r);

    EXPECT_FALSE(v_equal_l != v_equal_r); // identical arrays → not unequal
    ExpectNegationConsistency(v_equal_l, v_equal_r);

    Array arr_diff{ Value(1), Value(3) };
    Value v_diff(arr_diff);

    EXPECT_TRUE(v_equal_l != v_diff);     // different element → unequal
    ExpectNegationConsistency(v_equal_l, v_diff);
}

// Objects: same key/values vs. different key or value.
TEST(ValueNotEqualTest_24, ObjectInequalityByMembers_24) {
    Object o_left;    o_left["k1"] = Value(1);  o_left["k2"] = Value("v");
    Object o_right;   o_right["k1"] = Value(1); o_right["k2"] = Value("v");

    Value v_left(o_left), v_right(o_right);

    EXPECT_FALSE(v_left != v_right); // identical objects → not unequal
    ExpectNegationConsistency(v_left, v_right);

    Object o_changed = o_right; o_changed["k2"] = Value("vv");
    Value v_changed(o_changed);

    EXPECT_TRUE(v_left != v_changed); // changed value → unequal
    ExpectNegationConsistency(v_left, v_changed);

    Object o_extra = o_right; o_extra["k3"] = Value(true);
    Value v_extra(o_extra);

    EXPECT_TRUE(v_left != v_extra); // extra key → unequal
    ExpectNegationConsistency(v_left, v_extra);
}

// Sanity check: mixed comparisons with null.
TEST(ValueNotEqualTest_24, NullComparisons_24) {
    Value n;                // null
    Value s("x");
    Value i(0);
    Value b(false);

    EXPECT_TRUE(n != s);
    EXPECT_TRUE(n != i);
    EXPECT_TRUE(n != b);

    // null vs null → not unequal
    Value n2;
    EXPECT_FALSE(n != n2);
    ExpectNegationConsistency(n, n2);
}

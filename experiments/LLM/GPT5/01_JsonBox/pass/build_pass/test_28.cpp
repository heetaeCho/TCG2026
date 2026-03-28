// File: ValueOperatorGeTest_28.cpp

#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueOperatorGeTest_28 : public ::testing::Test {
protected:
    // Verifies relationships that must hold from the public interface POV.
    static void ExpectGeConsistency(const Value& lhs, const Value& rhs) {
        // >= must equal ( > || == )
        bool expect_disjunction = (lhs > rhs) || (lhs == rhs);
        EXPECT_EQ(lhs >= rhs, expect_disjunction);

        // Optional cross-check with < (still via public API)
        EXPECT_EQ(lhs >= rhs, !(lhs < rhs));
    }
};

// --- Self comparison cases ---

TEST_F(ValueOperatorGeTest_28, SelfComparison_IntegerIsGE_28) {
    Value v(42);
    EXPECT_TRUE(v >= v);
    ExpectGeConsistency(v, v);
}

TEST_F(ValueOperatorGeTest_28, SelfComparison_StringIsGE_28) {
    Value v(std::string("json"));
    EXPECT_TRUE(v >= v);
    ExpectGeConsistency(v, v);
}

TEST_F(ValueOperatorGeTest_28, SelfComparison_BooleanIsGE_28) {
    Value t(true);
    Value f(false);
    EXPECT_TRUE(t >= t);
    EXPECT_TRUE(f >= f);
    ExpectGeConsistency(t, t);
    ExpectGeConsistency(f, f);
}

TEST_F(ValueOperatorGeTest_28, SelfComparison_NullIsGE_28) {
    Value n; // default-constructed null
    EXPECT_TRUE(n >= n);
    ExpectGeConsistency(n, n);
}

// --- Numeric comparisons ---

TEST_F(ValueOperatorGeTest_28, IntegerGreaterThanInteger_28) {
    Value a(10), b(5);
    EXPECT_TRUE(a >= b);
    ExpectGeConsistency(a, b);
}

TEST_F(ValueOperatorGeTest_28, IntegerLessThanInteger_28) {
    Value a(3), b(7);
    EXPECT_FALSE(a >= b);
    ExpectGeConsistency(a, b);
}

TEST_F(ValueOperatorGeTest_28, IntegerEqualInteger_28) {
    Value a(5), b(5);
    EXPECT_TRUE(a >= b);
    ExpectGeConsistency(a, b);
}

TEST_F(ValueOperatorGeTest_28, DoubleAndInteger_EqualNumericValue_28) {
    Value a(3), b(3.0);
    // We don't assert cross-type rules beyond >= identity; we just check the relation definition.
    ExpectGeConsistency(a, b);
    ExpectGeConsistency(b, a);
}

TEST_F(ValueOperatorGeTest_28, DoubleAndInteger_MixedOrder_28) {
    Value a(2), b(2.9);
    ExpectGeConsistency(a, b);
    ExpectGeConsistency(b, a);
}

// --- String comparisons ---

TEST_F(ValueOperatorGeTest_28, StringGreaterThanString_28) {
    Value a(std::string("b")), b_(std::string("a"));
    EXPECT_TRUE(a >= b_);
    ExpectGeConsistency(a, b_);
}

TEST_F(ValueOperatorGeTest_28, StringLessThanString_28) {
    Value a(std::string("apple")), b_(std::string("banana"));
    EXPECT_FALSE(a >= b_);
    ExpectGeConsistency(a, b_);
}

TEST_F(ValueOperatorGeTest_28, StringEqualString_28) {
    Value a(std::string("same")), b_(std::string("same"));
    EXPECT_TRUE(a >= b_);
    ExpectGeConsistency(a, b_);
}

// --- Boolean comparisons ---

TEST_F(ValueOperatorGeTest_28, BoolOrderings_28) {
    Value t(true), f(false);
    ExpectGeConsistency(t, f);
    ExpectGeConsistency(f, t);
    ExpectGeConsistency(t, t);
    ExpectGeConsistency(f, f);
}

// --- Null vs others (boundary-ish cross-type checks) ---

TEST_F(ValueOperatorGeTest_28, NullVsNull_28) {
    Value n1, n2;
    ExpectGeConsistency(n1, n2);
}

TEST_F(ValueOperatorGeTest_28, NullVsInteger_28) {
    Value n, i(0);
    ExpectGeConsistency(n, i);
    ExpectGeConsistency(i, n);
}

TEST_F(ValueOperatorGeTest_28, NullVsString_28) {
    Value n, s(std::string(""));
    ExpectGeConsistency(n, s);
    ExpectGeConsistency(s, n);
}

// --- Arrays and Objects (constructed through public API) ---

TEST_F(ValueOperatorGeTest_28, ArrayComparisons_EmptyAndNonEmpty_28) {
    Array emptyArr;
    Array oneElemArr{ Value(1) };
    Value aEmpty(emptyArr), aOne(oneElemArr);

    ExpectGeConsistency(aEmpty, aEmpty);
    ExpectGeConsistency(aOne, aOne);
    ExpectGeConsistency(aEmpty, aOne);
    ExpectGeConsistency(aOne, aEmpty);
}

TEST_F(ValueOperatorGeTest_28, ObjectComparisons_EmptyAndKeyed_28) {
    Object oEmpty;
    Object oKeyed; oKeyed["k"] = Value(1);

    Value vEmpty(oEmpty), vKeyed(oKeyed);

    ExpectGeConsistency(vEmpty, vEmpty);
    ExpectGeConsistency(vKeyed, vKeyed);
    ExpectGeConsistency(vEmpty, vKeyed);
    ExpectGeConsistency(vKeyed, vEmpty);
}

// --- Mixed-type sanity sweep (no assumptions beyond interface) ---

TEST_F(ValueOperatorGeTest_28, MixedTypeSweep_28) {
    Value vi(7);
    Value vd(7.5);
    Value vs(std::string("7"));
    Value vb(true);
    Value vn; // null

    ExpectGeConsistency(vi, vd);
    ExpectGeConsistency(vd, vi);
    ExpectGeConsistency(vi, vs);
    ExpectGeConsistency(vs, vi);
    ExpectGeConsistency(vb, vn);
    ExpectGeConsistency(vn, vb);
}

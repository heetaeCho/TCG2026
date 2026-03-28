// File: ValueOperatorGreaterTest_27.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueOperatorGreaterTest_27 : public ::testing::Test {
protected:
  // Small helper to assert the public, observable relationship
  // between > and <= as implemented in Value.cpp.
  void ExpectConsistentWithNotLE(const Value& lhs, const Value& rhs) {
    EXPECT_EQ(lhs > rhs, !(lhs <= rhs));
  }
};

// --- Normal operation with same-type values ---

TEST_F(ValueOperatorGreaterTest_27, SelfComparisonIsFalse_27) {
  Value v1(42);
  Value v2("hello");
  Value v3(true);
  Value v4; // null

  EXPECT_FALSE(v1 > v1);
  EXPECT_FALSE(v2 > v2);
  EXPECT_FALSE(v3 > v3);
  EXPECT_FALSE(v4 > v4);
}

TEST_F(ValueOperatorGreaterTest_27, Integers_EquivalentToNotLE_27) {
  Value a1(2), b1(1);
  Value a2(1), b2(2);
  Value a3(5), b3(5);

  ExpectConsistentWithNotLE(a1, b1);
  ExpectConsistentWithNotLE(a2, b2);
  ExpectConsistentWithNotLE(a3, b3);
}

TEST_F(ValueOperatorGreaterTest_27, Doubles_EquivalentToNotLE_27) {
  Value a1(3.14), b1(2.71);
  Value a2(-1.0), b2(-2.0);
  Value a3(1.0), b3(1.0);

  ExpectConsistentWithNotLE(a1, b1);
  ExpectConsistentWithNotLE(a2, b2);
  ExpectConsistentWithNotLE(a3, b3);
}

TEST_F(ValueOperatorGreaterTest_27, Strings_EquivalentToNotLE_27) {
  Value a1(std::string("b")), b1(std::string("a"));
  Value a2(std::string("a")), b2(std::string("b"));
  Value a3(std::string("same")), b3(std::string("same"));
  Value a4(std::string("")), b4(std::string("x"));

  ExpectConsistentWithNotLE(a1, b1);
  ExpectConsistentWithNotLE(a2, b2);
  ExpectConsistentWithNotLE(a3, b3);
  ExpectConsistentWithNotLE(a4, b4);
}

TEST_F(ValueOperatorGreaterTest_27, Booleans_EquivalentToNotLE_27) {
  Value t(true), f(false);

  ExpectConsistentWithNotLE(t, f);
  ExpectConsistentWithNotLE(f, t);
  ExpectConsistentWithNotLE(t, t);
  ExpectConsistentWithNotLE(f, f);
}

// --- Boundary / edge scenarios ---

TEST_F(ValueOperatorGreaterTest_27, NullAgainstVarious_EquivalentToNotLE_27) {
  Value n;                 // null
  Value i(0);
  Value s(std::string(""));
  Value d(0.0);
  Value b(false);

  ExpectConsistentWithNotLE(n, n);
  ExpectConsistentWithNotLE(n, i);
  ExpectConsistentWithNotLE(n, s);
  ExpectConsistentWithNotLE(n, d);
  ExpectConsistentWithNotLE(n, b);

  ExpectConsistentWithNotLE(i, n);
  ExpectConsistentWithNotLE(s, n);
  ExpectConsistentWithNotLE(d, n);
  ExpectConsistentWithNotLE(b, n);
}

// --- Cross-type comparisons (no assumptions about ordering; only the relation to <=) ---

TEST_F(ValueOperatorGreaterTest_27, IntVsDouble_EquivalentToNotLE_27) {
  Value a1(1), b1(1.0);
  Value a2(2), b2(1.5);
  Value a3(-3), b3(-3.0);

  ExpectConsistentWithNotLE(a1, b1);
  ExpectConsistentWithNotLE(a2, b2);
  ExpectConsistentWithNotLE(a3, b3);

  ExpectConsistentWithNotLE(b1, a1);
  ExpectConsistentWithNotLE(b2, a2);
  ExpectConsistentWithNotLE(b3, a3);
}

TEST_F(ValueOperatorGreaterTest_27, ArraysAndObjects_EquivalentToNotLE_27) {
  Array arrEmpty;
  Array arrTwo; arrTwo.push_back(Value(1)); arrTwo.push_back(Value(2));

  Object objEmpty;
  Object objA; objA["a"] = Value(1);

  Value vaEmpty(arrEmpty), vaTwo(arrTwo);
  Value voEmpty(objEmpty), voA(objA);

  // Same-type comparisons
  ExpectConsistentWithNotLE(vaTwo, vaEmpty);
  ExpectConsistentWithNotLE(vaEmpty, vaTwo);
  ExpectConsistentWithNotLE(voA, voEmpty);
  ExpectConsistentWithNotLE(voEmpty, voA);

  // Cross-type comparisons
  ExpectConsistentWithNotLE(vaEmpty, voEmpty);
  ExpectConsistentWithNotLE(voEmpty, vaEmpty);
}

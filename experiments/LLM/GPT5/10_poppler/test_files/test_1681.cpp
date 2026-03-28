// Attribute_getType_tests_1681.cpp
#include <gtest/gtest.h>

#include "StructElement.h" // poppler::Attribute (path relative to poppler build includes)

// NOTE:
// - These tests treat Attribute as a black box and only validate observable behavior via the
//   public interface (constructor + getType/isOk).
// - We avoid relying on any private state or internal parsing logic.
// - We use enum casts to avoid depending on specific enumerator names.

class AttributeTest_1681 : public ::testing::Test {
protected:
  // Helper to create an Attribute with a given (possibly cast) Type and a nullptr value.
  static Attribute MakeAttr(Attribute::Type t) { return Attribute(t, nullptr); }
};

TEST_F(AttributeTest_1681, GetTypeReturnsConstructorTypeZero_1681) {
  const auto t0 = static_cast<Attribute::Type>(0);
  Attribute attr = MakeAttr(t0);

  EXPECT_EQ(attr.getType(), t0);
}

TEST_F(AttributeTest_1681, GetTypeReturnsConstructorTypeOne_1681) {
  const auto t1 = static_cast<Attribute::Type>(1);
  Attribute attr = MakeAttr(t1);

  EXPECT_EQ(attr.getType(), t1);
}

TEST_F(AttributeTest_1681, GetTypeHandlesLargeUnderlyingValue_1681) {
  // Boundary-style: use a large underlying integer cast to the enum type.
  // We only assert that getType returns exactly what was provided to the constructor.
  const auto tLarge = static_cast<Attribute::Type>(0x7fffffff);
  Attribute attr = MakeAttr(tLarge);

  EXPECT_EQ(attr.getType(), tLarge);
}

TEST_F(AttributeTest_1681, GetTypeCallableEvenWithNullValuePointer_1681) {
  // Exceptional/boundary-ish: nullptr Object* passed to constructor.
  // We don't assume success/failure semantics; we only verify observable calls do not crash
  // and getType remains callable.
  const auto t0 = static_cast<Attribute::Type>(0);
  Attribute attr(t0, nullptr);

  (void)attr.isOk(); // Observable API; no expectation on the value.
  EXPECT_EQ(attr.getType(), t0);
}

TEST_F(AttributeTest_1681, GetTypeStableAcrossMultipleCalls_1681) {
  const auto t1 = static_cast<Attribute::Type>(1);
  Attribute attr = MakeAttr(t1);

  const auto first = attr.getType();
  const auto second = attr.getType();
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, t1);
}
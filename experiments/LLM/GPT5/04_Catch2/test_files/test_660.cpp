// File: tests/catch_clara_boundflagrefbase_test.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Use the interface under test exactly as provided.
#include "catch2/internal/catch_clara.hpp"

namespace {
using ::testing::NiceMock;

namespace C = Catch::Clara::Detail;

// We don't re-implement any internal logic. We only need a concrete type to
// instantiate, so we mock the *external* collaborator method (setFlag).
// This allows constructing an object and calling isFlag() without assuming
// anything about setFlag's behavior.
class MockBoundFlagRefBase : public C::BoundFlagRefBase {
public:
  MOCK_METHOD(C::ParserResult, setFlag, (bool flag), (override));
};
}  // namespace

// ---- Tests ----

// Verifies: isFlag() returns true for a concrete instance.
// Black-box criterion: only checks the public return value.
TEST(BoundFlagRefBaseTest_660, IsFlagReturnsTrue_660) {
  NiceMock<MockBoundFlagRefBase> ref;
  EXPECT_TRUE(ref.isFlag());
}

// Verifies: isFlag() is const-correct and callable on a const reference.
// Black-box criterion: checks the observable return value via const access.
TEST(BoundFlagRefBaseTest_660, IsFlagConstQualifiedReturnsTrue_660) {
  NiceMock<MockBoundFlagRefBase> ref;
  const C::BoundFlagRefBase& cref = ref;
  EXPECT_TRUE(cref.isFlag());
}

// Verifies: isFlag() remains true when accessed polymorphically through the
// base (BoundRef). This ensures correct virtual override behavior without
// inspecting internals.
TEST(BoundFlagRefBaseTest_660, IsFlagTrueThroughBasePolymorphism_660) {
  NiceMock<MockBoundFlagRefBase> ref;
  // Access through the base interface only (no internal state access).
  C::BoundRef& base = static_cast<C::BoundRef&>(ref);
  EXPECT_TRUE(base.isFlag());
}

// Verifies: Multiple instances consistently report flag behavior.
// Black-box criterion: repeated observable behavior, no internal assumptions.
TEST(BoundFlagRefBaseTest_660, MultipleInstancesAllReturnTrue_660) {
  NiceMock<MockBoundFlagRefBase> a;
  NiceMock<MockBoundFlagRefBase> b;
  NiceMock<MockBoundFlagRefBase> c;

  EXPECT_TRUE(a.isFlag());
  EXPECT_TRUE(b.isFlag());
  EXPECT_TRUE(c.isFlag());
}

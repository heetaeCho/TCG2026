// File: unique_ptr_bool_tests_29.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_unique_ptr.hpp"

namespace cd = Catch::Detail;

struct Base { virtual ~Base() = default; };
struct Derived : Base {};

// Helper to observe destruction without touching internal state
struct Tracked {
  static int dtor_count;
  ~Tracked() { ++dtor_count; }
};
int Tracked::dtor_count = 0;

class UniquePtrBoolTest_29 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(UniquePtrBoolTest_29, DefaultConstructed_IsFalse_29) {
  cd::unique_ptr<Base> p;
  EXPECT_FALSE(static_cast<bool>(p));
}

TEST_F(UniquePtrBoolTest_29, ConstructWithRawPtr_IsTrue_29) {
  cd::unique_ptr<Base> p(new Base);
  EXPECT_TRUE(static_cast<bool>(p));
}

TEST_F(UniquePtrBoolTest_29, ResetToNull_MakesFalse_29) {
  cd::unique_ptr<Base> p(new Base);
  ASSERT_TRUE(static_cast<bool>(p));
  p.reset(nullptr);
  EXPECT_FALSE(static_cast<bool>(p));
}

TEST_F(UniquePtrBoolTest_29, Release_ReturnsRawAndMakesFalse_29) {
  cd::unique_ptr<Base> p(new Base);
  Base* raw = p.release();
  ASSERT_NE(raw, nullptr);
  EXPECT_FALSE(static_cast<bool>(p));
  delete raw; // we took ownership
}

// --- Move semantics affecting truthiness ---

TEST_F(UniquePtrBoolTest_29, MoveConstructor_TransfersTruthiness_29) {
  cd::unique_ptr<Base> src(new Base);
  ASSERT_TRUE(static_cast<bool>(src));

  cd::unique_ptr<Base> dst(std::move(src));
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(static_cast<bool>(dst));
}

TEST_F(UniquePtrBoolTest_29, MoveAssignment_TransfersTruthiness_29) {
  cd::unique_ptr<Base> src(new Base);
  cd::unique_ptr<Base> dst;
  ASSERT_TRUE(static_cast<bool>(src));
  ASSERT_FALSE(static_cast<bool>(dst));

  dst = std::move(src);
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(static_cast<bool>(dst));
}

// --- Cross-type move (Derived -> Base) ---

TEST_F(UniquePtrBoolTest_29, TemplatedMove_FromDerivedToBase_UpdatesTruthiness_29) {
  cd::unique_ptr<Derived> d(new Derived);
  ASSERT_TRUE(static_cast<bool>(d));

  cd::unique_ptr<Base> b(std::move(d));
  EXPECT_FALSE(static_cast<bool>(d));
  EXPECT_TRUE(static_cast<bool>(b));
}

// --- Boundary / const correctness & null edge cases ---

TEST_F(UniquePtrBoolTest_29, ConstUniquePtr_BoolIsUsable_29) {
  const cd::unique_ptr<Base> p(new Base);
  EXPECT_TRUE(static_cast<bool>(p));
}

TEST_F(UniquePtrBoolTest_29, ReleaseOnNull_ReturnsNull_AndRemainsFalse_29) {
  cd::unique_ptr<Base> p; // null
  Base* raw = p.release();
  EXPECT_EQ(raw, nullptr);
  EXPECT_FALSE(static_cast<bool>(p));
}

// --- Observable destruction behavior (external side-effect) ---

TEST_F(UniquePtrBoolTest_29, DestructorCalledWhenOwning_GuardsAgainstDoubleDeleteOnRelease_29) {
  Tracked::dtor_count = 0;
  {
    cd::unique_ptr<Tracked> p(new Tracked);
    EXPECT_TRUE(static_cast<bool>(p));

    // After release, unique_ptr should be empty and not destroy the object
    Tracked* raw = p.release();
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(Tracked::dtor_count, 0);

    // We delete manually; exactly one destruction should occur
    delete raw;
    EXPECT_EQ(Tracked::dtor_count, 1);
  }
  // Exiting scope with empty unique_ptr should not change count
  EXPECT_EQ(Tracked::dtor_count, 1);
}

// File: charclass_empty_test_146.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::CharClass;

namespace {

// Simple RAII wrapper to ensure Delete() is called via public API.
struct CCHandle {
  CharClass* ptr{nullptr};
  explicit CCHandle(CharClass* p) : ptr(p) {}
  ~CCHandle() { if (ptr) ptr->Delete(); }
  // Non-copyable
  CCHandle(const CCHandle&) = delete;
  CCHandle& operator=(const CCHandle&) = delete;
  // Movable
  CCHandle(CCHandle&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
  CCHandle& operator=(CCHandle&& other) noexcept {
    if (this != &other) {
      if (ptr) ptr->Delete();
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }
};

class CharClassTest_146 : public ::testing::Test {};

}  // namespace

// --- Normal operation ---

TEST_F(CharClassTest_146, NewReturnsNonNull_146) {
  CCHandle cc0(CharClass::New(/*maxranges=*/0));
  EXPECT_NE(cc0.ptr, nullptr);

  CCHandle cc1(CharClass::New(/*maxranges=*/1));
  EXPECT_NE(cc1.ptr, nullptr);
}

TEST_F(CharClassTest_146, SizeAndEmptyAgreeOnFreshInstance_146) {
  CCHandle cc(CharClass::New(/*maxranges=*/1));
  ASSERT_NE(cc.ptr, nullptr);

  // Observable relation only: size()==0 <=> empty()==true
  EXPECT_EQ(cc.ptr->size() == 0, cc.ptr->empty());
}

TEST_F(CharClassTest_146, BeginEqualsEndWhenEmpty_146) {
  CCHandle cc(CharClass::New(/*maxranges=*/2));
  ASSERT_NE(cc.ptr, nullptr);

  if (cc.ptr->empty()) {
    EXPECT_EQ(cc.ptr->begin(), cc.ptr->end());
  } else {
    // If a fresh instance is not empty in this implementation,
    // we still exercise the iterators (no assumptions).
    EXPECT_NE(cc.ptr->begin(), cc.ptr->end());
  }
}

// --- Boundary conditions ---

TEST_F(CharClassTest_146, EmptyTogglesWithNegate_146) {
  CCHandle cc(CharClass::New(/*maxranges=*/0));
  ASSERT_NE(cc.ptr, nullptr);

  CCHandle neg(cc.ptr->Negate());
  ASSERT_NE(neg.ptr, nullptr);

  // Without assuming initial content, verify Negate flips "emptiness".
  EXPECT_NE(cc.ptr->empty(), neg.ptr->empty());

  // Also verify size/empty consistency holds on negated result.
  EXPECT_EQ(neg.ptr->size() == 0, neg.ptr->empty());
}

TEST_F(CharClassTest_146, DoubleNegateRestoresEmptiness_146) {
  CCHandle cc(CharClass::New(/*maxranges=*/4));
  ASSERT_NE(cc.ptr, nullptr);

  const bool original_empty = cc.ptr->empty();

  CCHandle neg1(cc.ptr->Negate());
  ASSERT_NE(neg1.ptr, nullptr);
  CCHandle neg2(neg1.ptr->Negate());
  ASSERT_NE(neg2.ptr, nullptr);

  // After two negations, observable emptiness should match original.
  EXPECT_EQ(original_empty, neg2.ptr->empty());
}

// --- Exceptional / lifecycle behavior (observable) ---

TEST_F(CharClassTest_146, DeleteIsIdempotentViaRAII_146) {
  // We only test that calling Delete() through RAII does not crash or leak per observable behavior.
  // The RAII wrapper deletes on scope exit. Moving should not double-delete.
  CCHandle a(CharClass::New(/*maxranges=*/1));
  ASSERT_NE(a.ptr, nullptr);
  // Move it around; only one Delete() should occur.
  CCHandle b(std::move(a));
  EXPECT_EQ(a.ptr, nullptr);
  EXPECT_NE(b.ptr, nullptr);
  // Scope end: b deletes once. (No explicit assertions possible beyond not crashing.)
}


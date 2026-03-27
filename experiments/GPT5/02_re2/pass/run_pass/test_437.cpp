// File: dfa_state_eq_test_437.cc

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Include the partial implementation to access the public interface/type.
#include "re2/dfa.cc"

using re2::DFA;
using State = re2::DFA::State;  // Brings 'State' into scope for macros like DeadState/FullMatchState.

namespace {

// Helper: initialize a State's observable fields used by operator==.
void SetState(State* s, const std::vector<int>& inst, uint32_t flag) {
  s->flag_ = flag;
  if (inst.empty()) {
    s->inst_ = nullptr;
    s->ninst_ = 0;
    return;
  }
  int* buf = new int[inst.size()];
  std::copy(inst.begin(), inst.end(), buf);
  s->inst_ = buf;
  s->ninst_ = static_cast<int>(inst.size());
}

// Helper: release buffer assigned by SetState.
void FreeState(State* s) {
  if (s->ninst_ > 0 && s->inst_ != nullptr) {
    delete[] s->inst_;
  }
  s->inst_ = nullptr;
  s->ninst_ = 0;
}

}  // namespace

class DFAStateEqTest_437 : public ::testing::Test {};

// Self-comparison must be true due to &a == &b fast path.
TEST_F(DFAStateEqTest_437, SelfEquality_437) {
  State a{};
  SetState(&a, {1, 2, 3}, /*flag=*/7u);
  EXPECT_TRUE(a == a);
  FreeState(&a);
}

// Different objects with identical flag and identical inst_ sequence compare equal.
TEST_F(DFAStateEqTest_437, EqualByContent_SameFlagAndInst_437) {
  State a{}, b{};
  SetState(&a, {10, 20}, 42u);
  SetState(&b, {10, 20}, 42u);
  ASSERT_NE(&a, &b);  // Sanity: distinct instances.
  EXPECT_TRUE(a == b);
  FreeState(&a);
  FreeState(&b);
}

// Different flags with identical instruction sequences compare not equal.
TEST_F(DFAStateEqTest_437, NotEqual_WhenFlagsDiffer_437) {
  State a{}, b{};
  SetState(&a, {10, 20}, 1u);
  SetState(&b, {10, 20}, 2u);
  EXPECT_FALSE(a == b);
  FreeState(&a);
  FreeState(&b);
}

// Same flag but different instruction lengths compare not equal.
TEST_F(DFAStateEqTest_437, NotEqual_WhenInstLengthDiffers_437) {
  State a{}, b{};
  SetState(&a, {1, 2}, 5u);
  SetState(&b, {1, 2, 3}, 5u);
  EXPECT_FALSE(a == b);
  FreeState(&a);
  FreeState(&b);
}

// Same flag and length but differing instruction content compare not equal.
TEST_F(DFAStateEqTest_437, NotEqual_WhenInstContentDiffers_437) {
  State a{}, b{};
  SetState(&a, {1, 2, 3}, 5u);
  SetState(&b, {1, 99, 3}, 5u);
  EXPECT_FALSE(a == b);
  FreeState(&a);
  FreeState(&b);
}

// Zero-length instruction arrays with same flag compare equal.
TEST_F(DFAStateEqTest_437, Equal_WithEmptyInstAndSameFlag_437) {
  State a{}, b{};
  SetState(&a, {}, 123u);
  SetState(&b, {}, 123u);
  EXPECT_TRUE(a == b);
  FreeState(&a);
  FreeState(&b);
}

// Validate exposed constants/macros without dereferencing sentinel pointers.
TEST_F(DFAStateEqTest_437, SpecialConstantsAndPointers_AreDistinct_437) {
  State dummy{};
  // Pointers should be non-null and distinct from each other and from real objects.
  EXPECT_NE(DeadState, nullptr);
  EXPECT_NE(FullMatchState, nullptr);
  EXPECT_NE(DeadState, FullMatchState);
  EXPECT_NE(DeadState, &dummy);
  EXPECT_NE(FullMatchState, &dummy);

  // Integer markers have expected observable values.
  EXPECT_EQ(MatchSep, -2);
  EXPECT_EQ(Mark, -1);
}

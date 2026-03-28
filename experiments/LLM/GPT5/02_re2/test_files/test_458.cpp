// File: prog_possible_match_range_test_458.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SaveArg;
using ::testing::SetArgPointee;

namespace re2 {

// ---- Minimal declarations to interact with the compiled implementation ----
// We only declare what we need from Prog/DFA to test the public behavior.

class DFA {
public:
  virtual ~DFA() = default;
  // The method that Prog::PossibleMatchRange is expected to call.
  virtual bool PossibleMatchRange(std::string* min, std::string* max, int maxlen) {
    // Default stub (won't be used when mocked).
    return false;
  }
};

class Prog {
public:
  enum MatchKind { kFirstMatch = 0, kLongestMatch = 1, kFullMatch = 2, kManyMatch = 3 };

  // Implemented in the production .cc (provided in the prompt).
  bool PossibleMatchRange(std::string* min, std::string* max, int maxlen);

  // We provide the out-of-line definition for GetDFA in this test file to
  // return our test double. (Access control doesn't affect ODR/linkage.)
  DFA* GetDFA(MatchKind kind);
};

// ---- Test double wiring -----------------------------------------------------

// A Google Mock for DFA that allows us to verify interactions.
class MockDFA : public DFA {
public:
  MOCK_METHOD(bool, PossibleMatchRange, (std::string* min, std::string* max, int maxlen), (override));
};

// Global hooks used by our GetDFA override to return the current mock and
// to capture the requested MatchKind.
static MockDFA* g_mock_dfa_458 = nullptr;
static Prog::MatchKind g_last_kind_458 = Prog::kFirstMatch;

// Definition of Prog::GetDFA that the production Prog::PossibleMatchRange will call.
DFA* Prog::GetDFA(Prog::MatchKind kind) {
  g_last_kind_458 = kind;
  return g_mock_dfa_458;
}

}  // namespace re2

// ---- Test Fixture -----------------------------------------------------------

class ProgPossibleMatchRangeTest_458 : public ::testing::Test {
protected:
  void SetUp() override {
    ASSERT_EQ(re2::g_mock_dfa_458, nullptr) << "Mock DFA should be null before each test.";
    mock_ = new re2::MockDFA();
    re2::g_mock_dfa_458 = mock_;
    re2::g_last_kind_458 = re2::Prog::kFirstMatch;  // reset capture
  }

  void TearDown() override {
    delete mock_;
    re2::g_mock_dfa_458 = nullptr;
  }

  re2::MockDFA* mock_ = nullptr;
};

// ---- Tests ------------------------------------------------------------------

// Verifies that Prog::PossibleMatchRange delegates to DFA::PossibleMatchRange,
// forwards pointers and maxlen, and returns the DFA result.
TEST_F(ProgPossibleMatchRangeTest_458, DelegatesAndPropagatesReturn_458) {
  re2::Prog prog;

  std::string min = "a";
  std::string max = "z";
  const int kMaxLen = 123;

  // Ensure the DFA method is called with the very same addresses and value.
  // Also mutate the outputs to check they propagate through the call.
  EXPECT_CALL(*mock_, PossibleMatchRange(&min, &max, kMaxLen))
      .WillOnce(DoAll(
          SetArgPointee<0>(std::string("min_out")),
          SetArgPointee<1>(std::string("max_out")),
          Return(true)));

  bool ok = prog.PossibleMatchRange(&min, &max, kMaxLen);
  EXPECT_TRUE(ok);
  EXPECT_EQ(min, "min_out");
  EXPECT_EQ(max, "max_out");
}

// Verifies that a 'false' result from DFA::PossibleMatchRange is propagated.
TEST_F(ProgPossibleMatchRangeTest_458, ReturnsFalseWhenDfaReturnsFalse_458) {
  re2::Prog prog;

  std::string min, max;
  EXPECT_CALL(*mock_, PossibleMatchRange(&min, &max, 10)).WillOnce(Return(false));

  EXPECT_FALSE(prog.PossibleMatchRange(&min, &max, 10));
}

// Boundary: maxlen == 0 is forwarded as-is.
TEST_F(ProgPossibleMatchRangeTest_458, ForwardsZeroMaxLenBoundary_458) {
  re2::Prog prog;

  std::string min, max;
  int captured_len = -1;

  EXPECT_CALL(*mock_, PossibleMatchRange(&min, &max, _))
      .WillOnce(DoAll(SaveArg<2>(&captured_len), Return(true)));

  EXPECT_TRUE(prog.PossibleMatchRange(&min, &max, 0));
  EXPECT_EQ(captured_len, 0);
}

// Boundary: large maxlen is forwarded unchanged.
TEST_F(ProgPossibleMatchRangeTest_458, ForwardsLargeMaxLenBoundary_458) {
  re2::Prog prog;

  std::string min, max;
  int captured_len = -1;
  const int kLarge = std::numeric_limits<int>::max();

  EXPECT_CALL(*mock_, PossibleMatchRange(&min, &max, _))
      .WillOnce(DoAll(SaveArg<2>(&captured_len), Return(true)));

  EXPECT_TRUE(prog.PossibleMatchRange(&min, &max, kLarge));
  EXPECT_EQ(captured_len, kLarge);
}

// Verifies that Prog::PossibleMatchRange specifically requests the LongestMatch DFA.
TEST_F(ProgPossibleMatchRangeTest_458, UsesLongestMatchDFA_458) {
  re2::Prog prog;

  std::string min, max;
  EXPECT_CALL(*mock_, PossibleMatchRange(&min, &max, 1)).WillOnce(Return(true));

  EXPECT_TRUE(prog.PossibleMatchRange(&min, &max, 1));
  EXPECT_EQ(re2::g_last_kind_458, re2::Prog::kLongestMatch);
}

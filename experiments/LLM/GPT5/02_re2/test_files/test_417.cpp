// File: prog_build_shiftdfa_test_417.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <string>

// Include the implementation directly to access the internal-linkage function.
#include "re2/prog.cc"

namespace {

class BuildShiftDFATest_417 : public ::testing::Test {
protected:
  static constexpr int kAlphabetSize = 256;

  static bool ArraysEqual(const uint64_t* lhs, const uint64_t* rhs) {
    for (int i = 0; i < kAlphabetSize; ++i) {
      if (lhs[i] != rhs[i]) return false;
    }
    return true;
  }

  static bool AnyEntryDiffers(const uint64_t* lhs, const uint64_t* rhs) {
    for (int i = 0; i < kAlphabetSize; ++i) {
      if (lhs[i] != rhs[i]) return true;
    }
    return false;
  }
};

// [Normal] Determinism: same input -> identical DFA
TEST_F(BuildShiftDFATest_417, DeterministicSameInputSameOutput_417) {
  uint64_t* dfa1 = re2::BuildShiftDFA("re2");
  uint64_t* dfa2 = re2::BuildShiftDFA("re2");

  ASSERT_NE(dfa1, nullptr);
  ASSERT_NE(dfa2, nullptr);
  EXPECT_TRUE(ArraysEqual(dfa1, dfa2));

  delete[] dfa1;
  delete[] dfa2;
}

// [Boundary] Empty prefix: all entries should be equal (and non-zero due to a common final-state marker)
TEST_F(BuildShiftDFATest_417, EmptyPrefix_AllEntriesEqualAndNonZero_417) {
  uint64_t* dfa = re2::BuildShiftDFA("");
  ASSERT_NE(dfa, nullptr);

  uint64_t first = dfa[0];
  // All 256 entries equal to each other
  for (int i = 1; i < kAlphabetSize; ++i) {
    EXPECT_EQ(dfa[i], first) << "Mismatch at byte " << i;
  }
  // And not all-zero
  EXPECT_NE(first, 0u);

  delete[] dfa;
}

// [Behavior] Duplicated characters in prefix do not change the result (due to unique-ing)
TEST_F(BuildShiftDFATest_417, DuplicateCharactersInPrefix_DoNotChangeResult_417) {
  uint64_t* dfa_single = re2::BuildShiftDFA("a");
  uint64_t* dfa_dupes  = re2::BuildShiftDFA("aaa");

  ASSERT_NE(dfa_single, nullptr);
  ASSERT_NE(dfa_dupes, nullptr);
  EXPECT_TRUE(ArraysEqual(dfa_single, dfa_dupes));

  delete[] dfa_single;
  delete[] dfa_dupes;
}

// [Behavior] Case-insensitive effect on transitions makes mixed-case prefixes equivalent
TEST_F(BuildShiftDFATest_417, MixedCasePrefix_EquivalentToLowercase_417) {
  uint64_t* dfa_lower = re2::BuildShiftDFA("abc");
  uint64_t* dfa_mixed = re2::BuildShiftDFA("AbC");

  ASSERT_NE(dfa_lower, nullptr);
  ASSERT_NE(dfa_mixed, nullptr);
  EXPECT_TRUE(ArraysEqual(dfa_lower, dfa_mixed));

  delete[] dfa_lower;
  delete[] dfa_mixed;
}

// [Behavior] Distinct prefixes (simple disjoint cases) generally produce different DFAs
TEST_F(BuildShiftDFATest_417, DifferentPrefixes_UsuallyProduceDifferentTables_417) {
  uint64_t* dfa_a = re2::BuildShiftDFA("a");
  uint64_t* dfa_b = re2::BuildShiftDFA("b");

  ASSERT_NE(dfa_a, nullptr);
  ASSERT_NE(dfa_b, nullptr);
  // Expect at least one entry to differ
  EXPECT_TRUE(AnyEntryDiffers(dfa_a, dfa_b));

  delete[] dfa_a;
  delete[] dfa_b;
}

// [Invariant] For any prefix, all entries share a common non-zero bit (final-state marker)
// This checks a stable, externally observable invariant without decoding internals.
TEST_F(BuildShiftDFATest_417, CommonFinalMarkerBit_IsPresentAcrossAllEntries_417) {
  uint64_t* dfa = re2::BuildShiftDFA("AbCdEfG");
  ASSERT_NE(dfa, nullptr);

  uint64_t common = dfa[0];
  for (int i = 1; i < kAlphabetSize; ++i) {
    common &= dfa[i];
  }
  EXPECT_NE(common, 0u) << "Expected a common non-zero bit across all 256 entries.";

  delete[] dfa;
}

// [Spot check] For a letter present in the prefix, upper/lower DFA entries are identical
TEST_F(BuildShiftDFATest_417, CaseFolding_UpperLowerEntriesEqualForLetters_417) {
  uint64_t* dfa = re2::BuildShiftDFA("a");
  ASSERT_NE(dfa, nullptr);

  // For the letter 'a', confirm that table rows for 'a' and 'A' are identical.
  EXPECT_EQ(dfa[static_cast<unsigned>('a')], dfa[static_cast<unsigned>('A')]);

  delete[] dfa;
}

}  // namespace

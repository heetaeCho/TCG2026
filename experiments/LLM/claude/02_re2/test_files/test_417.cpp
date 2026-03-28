#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <string>

// We need to access the BuildShiftDFA function and kShiftDFAFinal.
// Since BuildShiftDFA is a static function in prog.cc, we need to include it
// or declare it. Given the constraints, we'll try to access it through the
// re2 namespace. Since it's static, we may need to include the source file
// or use a workaround.

// For testing a static function, we include the source file directly.
// This is a common technique for unit testing static/internal functions.

namespace re2 {
extern const size_t kShiftDFAFinal;
// We need to declare or access BuildShiftDFA. Since it's static in prog.cc,
// we'll need to either make it accessible or include the file.
// For the purpose of these tests, let's assume we can access it.
// In practice, you might need to adjust the build to expose this function.
static uint64_t* BuildShiftDFA(std::string prefix);
}

// If direct access isn't possible, we'd include the .cc file:
// #include "re2/prog.cc"

// Helper to safely delete DFA arrays
class ShiftDFADeleter {
public:
    explicit ShiftDFADeleter(uint64_t* dfa) : dfa_(dfa) {}
    ~ShiftDFADeleter() { delete[] dfa_; }
    uint64_t* get() const { return dfa_; }
private:
    uint64_t* dfa_;
};

class BuildShiftDFATest_417 : public ::testing::Test {
protected:
    static constexpr size_t kFinal = 9;
};

// Test that BuildShiftDFA returns a non-null pointer for a simple single-character prefix
TEST_F(BuildShiftDFATest_417, SingleCharReturnsNonNull_417) {
    uint64_t* dfa = re2::BuildShiftDFA("a");
    ASSERT_NE(dfa, nullptr);
    delete[] dfa;
}

// Test that BuildShiftDFA returns a non-null pointer for a multi-character prefix
TEST_F(BuildShiftDFATest_417, MultiCharReturnsNonNull_417) {
    uint64_t* dfa = re2::BuildShiftDFA("hello");
    ASSERT_NE(dfa, nullptr);
    delete[] dfa;
}

// Test that the final state marker is set for all 256 byte values
TEST_F(BuildShiftDFATest_417, FinalStateMarkerSetForAllBytes_417) {
    uint64_t* dfa = re2::BuildShiftDFA("ab");
    ASSERT_NE(dfa, nullptr);
    
    // For every byte value, the final state position (kShiftDFAFinal * 6)
    // should have kShiftDFAFinal * 6 encoded at bit position (kShiftDFAFinal * 6)
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    
    for (int b = 0; b < 256; ++b) {
        EXPECT_EQ(dfa[b] & final_mask, final_mask)
            << "Final state marker not set for byte " << b;
    }
    delete[] dfa;
}

// Test that non-prefix bytes only have the final state marker (and possibly state 0 transition)
TEST_F(BuildShiftDFATest_417, NonPrefixBytesHaveMinimalTransitions_417) {
    uint64_t* dfa = re2::BuildShiftDFA("xyz");
    ASSERT_NE(dfa, nullptr);
    
    // Byte 'a' is not in "xyz", so its DFA entry should only have the final state marker
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    EXPECT_EQ(dfa['a'], final_mask);
    
    delete[] dfa;
}

// Test case-insensitive behavior: lowercase letters should also set uppercase entries
TEST_F(BuildShiftDFATest_417, CaseInsensitiveLowercaseSetsUppercase_417) {
    uint64_t* dfa = re2::BuildShiftDFA("a");
    ASSERT_NE(dfa, nullptr);
    
    // The lowercase 'a' entry and uppercase 'A' entry should have the same
    // transition information (at least the part contributed by the prefix)
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    
    // Both should have more than just the final mask since 'a' is in the prefix
    EXPECT_NE(dfa['a'], final_mask);
    // 'A' should also have transitions copied from 'a'
    EXPECT_NE(dfa['A'], final_mask);
    
    // The non-final-state bits should be the same for 'a' and 'A'
    EXPECT_EQ(dfa['a'] & ~final_mask, dfa['A'] & ~final_mask);
    
    delete[] dfa;
}

// Test with prefix at maximum supported length (kShiftDFAFinal = 9)
TEST_F(BuildShiftDFATest_417, MaxLengthPrefix_417) {
    // kShiftDFAFinal is 9, so the prefix can be up to 9 characters
    uint64_t* dfa = re2::BuildShiftDFA("abcdefghi");
    ASSERT_NE(dfa, nullptr);
    
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    for (int b = 0; b < 256; ++b) {
        EXPECT_EQ(dfa[b] & final_mask, final_mask)
            << "Final state marker not set for byte " << b;
    }
    
    delete[] dfa;
}

// Test with a prefix of length 1
TEST_F(BuildShiftDFATest_417, PrefixLengthOne_417) {
    uint64_t* dfa = re2::BuildShiftDFA("z");
    ASSERT_NE(dfa, nullptr);
    
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    
    // 'z' should have non-trivial transition at position 0
    // Since the prefix is "z", after seeing 'z' we should go to the final state
    // The transition from state 0 on 'z' should be to the final state
    uint64_t z_entry = dfa['z'];
    EXPECT_NE(z_entry, final_mask);
    
    // 'Z' should mirror 'z' due to case-insensitive handling
    EXPECT_EQ(dfa['z'] & ~final_mask, dfa['Z'] & ~final_mask);
    
    delete[] dfa;
}

// Test with repeated characters in prefix
TEST_F(BuildShiftDFATest_417, RepeatedCharactersInPrefix_417) {
    uint64_t* dfa = re2::BuildShiftDFA("aaa");
    ASSERT_NE(dfa, nullptr);
    
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    
    // 'a' should have transitions for all 3 positions
    EXPECT_NE(dfa['a'], final_mask);
    
    // A byte not in the prefix should only have final mask
    EXPECT_EQ(dfa['b'], final_mask);
    
    delete[] dfa;
}

// Test with prefix containing non-alphabetic characters
TEST_F(BuildShiftDFATest_417, NonAlphabeticCharacters_417) {
    uint64_t* dfa = re2::BuildShiftDFA("123");
    ASSERT_NE(dfa, nullptr);
    
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    
    // '1', '2', '3' should have transitions
    EXPECT_NE(dfa['1'], final_mask);
    EXPECT_NE(dfa['2'], final_mask);
    EXPECT_NE(dfa['3'], final_mask);
    
    // Non-prefix alphabetic bytes should only have final mask
    EXPECT_EQ(dfa['a'], final_mask);
    
    delete[] dfa;
}

// Test that uppercase characters in prefix don't trigger reverse case mapping
TEST_F(BuildShiftDFATest_417, UppercaseInPrefixNoReverseCaseMapping_417) {
    uint64_t* dfa = re2::BuildShiftDFA("A");
    ASSERT_NE(dfa, nullptr);
    
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    
    // 'A' is uppercase, so the case mapping (a-z -> A-Z) shouldn't apply here
    // 'A' should have transitions since it's in the prefix
    EXPECT_NE(dfa['A'], final_mask);
    
    // 'a' should only have the final mask since 'A' is not lowercase
    // (the case mapping only goes from lowercase to uppercase, not vice versa)
    EXPECT_EQ(dfa['a'], final_mask);
    
    delete[] dfa;
}

// Test with mixed case prefix
TEST_F(BuildShiftDFATest_417, MixedCasePrefix_417) {
    uint64_t* dfa = re2::BuildShiftDFA("aB");
    ASSERT_NE(dfa, nullptr);
    
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    
    // 'a' is lowercase, so 'A' should get its transitions too
    EXPECT_EQ(dfa['a'] & ~final_mask, dfa['A'] & ~final_mask);
    
    // 'B' is uppercase, so 'b' should NOT get B's transitions
    // 'B' should have transitions, but 'b' should only have final mask
    EXPECT_NE(dfa['B'], final_mask);
    EXPECT_EQ(dfa['b'], final_mask);
    
    delete[] dfa;
}

// Test that the DFA array has 256 entries (implicitly verified by accessing all indices)
TEST_F(BuildShiftDFATest_417, AllByteValuesAccessible_417) {
    uint64_t* dfa = re2::BuildShiftDFA("test");
    ASSERT_NE(dfa, nullptr);
    
    // Access all 256 entries without crashing
    uint64_t sum = 0;
    for (int i = 0; i < 256; ++i) {
        sum += dfa[i];
    }
    // sum should be non-zero since at least final state markers are set
    EXPECT_NE(sum, 0u);
    
    delete[] dfa;
}

// Test prefix with length 2 - verify state transitions make sense
TEST_F(BuildShiftDFATest_417, PrefixLengthTwo_417) {
    uint64_t* dfa = re2::BuildShiftDFA("ab");
    ASSERT_NE(dfa, nullptr);
    
    uint64_t final_mask = static_cast<uint64_t>(kFinal * 6) << (kFinal * 6);
    
    // 'a' and 'b' should both have non-trivial entries
    EXPECT_NE(dfa['a'], final_mask);
    EXPECT_NE(dfa['b'], final_mask);
    
    // 'c' should only have the final state marker
    EXPECT_EQ(dfa['c'], final_mask);
    
    delete[] dfa;
}

// Test that transitions are encoded in 6-bit fields
TEST_F(BuildShiftDFATest_417, TransitionsEncodedIn6BitFields_417) {
    uint64_t* dfa = re2::BuildShiftDFA("ab");
    ASSERT_NE(dfa, nullptr);
    
    // Each state transition is encoded in a 6-bit field at position (state * 6)
    // For state 0, the transition is in bits [0, 5]
    // The value should be a multiple of 6 (since dnext * 6 is stored)
    uint64_t state0_transition_a = dfa['a'] & 0x3F; // lowest 6 bits
    EXPECT_EQ(state0_transition_a % 6, 0u);
    
    delete[] dfa;
}

// File: pcre_fullinfo_test_187.cc
#include <gtest/gtest.h>

// Forward declarations matching the interface under test.
// We do NOT rely on or inspect any internal state.
struct pcre;
struct pcre_extra;

// Function under test (declared, not defined here).
int pcre_fullinfo(const pcre*, const pcre_extra*, int, void*);

// Test fixture (empty; kept for naming consistency/extension).
class PCREFullInfoTest_187 : public ::testing::Test {};

// --- Normal operation: callable and returns an int (observable: return value 0) ---
TEST_F(PCREFullInfoTest_187, ReturnsZeroWithNullArgs_187) {
  int rc = pcre_fullinfo(nullptr, nullptr, /*what=*/0, /*where=*/nullptr);
  EXPECT_EQ(rc, 0);
}

// --- Normal operation: with non-null out pointer (observable: return value 0) ---
TEST_F(PCREFullInfoTest_187, ReturnsZeroWithOutPointerProvided_187) {
  int out_value = -123;  // sentinel, only to ensure the call is safe with a pointer
  int rc = pcre_fullinfo(nullptr, nullptr, /*what=*/0, &out_value);
  EXPECT_EQ(rc, 0);
}

// --- Boundary conditions: negative 'what' code ---
TEST_F(PCREFullInfoTest_187, ReturnsZeroWithNegativeWhat_187) {
  int rc = pcre_fullinfo(nullptr, nullptr, /*what=*/-1, /*where=*/nullptr);
  EXPECT_EQ(rc, 0);
}

// --- Boundary conditions: large 'what' code ---
TEST_F(PCREFullInfoTest_187, ReturnsZeroWithLargeWhat_187) {
  int rc = pcre_fullinfo(nullptr, nullptr, /*what=*/0x7fffffff, /*where=*/nullptr);
  EXPECT_EQ(rc, 0);
}

// --- Robustness: different 'what' values that might correspond to known constants ---
// (We pass raw ints to avoid relying on macro visibility.)
TEST_F(PCREFullInfoTest_187, ReturnsZeroAcrossRepresentativeWhatValues_187) {
  const int candidates[] = {0, 1, 2, 3, 10, 100};
  for (int what : candidates) {
    EXPECT_EQ(pcre_fullinfo(nullptr, nullptr, what, nullptr), 0) << "what=" << what;
  }
}

// --- Observable side effects: ensure the function does not modify the output buffer ---
// (This is observable behavior through the public interface.)
TEST_F(PCREFullInfoTest_187, DoesNotModifyOutputBuffer_187) {
  // Use multiple types to ensure the function doesn't write to them (observable effect).
  int out_int = 42;
  long long out_ll = 99;
  void* out_ptr = reinterpret_cast<void*>(0xDEADBEEF);

  EXPECT_EQ(pcre_fullinfo(nullptr, nullptr, 0, &out_int), 0);
  EXPECT_EQ(out_int, 42);  // unchanged

  EXPECT_EQ(pcre_fullinfo(nullptr, nullptr, 0, &out_ll), 0);
  EXPECT_EQ(out_ll, 99);   // unchanged

  EXPECT_EQ(pcre_fullinfo(nullptr, nullptr, 0, &out_ptr), 0);
  EXPECT_EQ(out_ptr, reinterpret_cast<void*>(0xDEADBEEF));  // unchanged
}

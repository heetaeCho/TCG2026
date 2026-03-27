// File: re2_fuzzer_test_386.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <string>

// Include the unit under test.
#include "re2/fuzzing/re2_fuzzer.cc"  // Path as given in the prompt

using ::re2::RE2;

// ---- Test double for the external collaborator --------------------------------
// We provide a test double for the free function `TestOneInput` that the fuzzer calls.
// This lets us observe whether it was invoked and with what parameters, without
// altering the fuzzer logic itself.

namespace {
struct CapturedCall {
  std::string pattern;
  RE2::Options options;       // observed only via public getters
  RE2::Anchor anchor;
  std::string text;
};

static std::vector<CapturedCall> g_calls;

}  // namespace

// Signature inferred from the call site in the fuzzer.
void TestOneInput(const std::string& pattern,
                  const RE2::Options& options,
                  RE2::Anchor anchor,
                  const std::string& text) {
  g_calls.push_back(CapturedCall{pattern, options, anchor, text});
}

// ---- Test fixture --------------------------------------------------------------
class RE2FuzzerTest_386 : public ::testing::Test {
 protected:
  void SetUp() override { g_calls.clear(); }
  void TearDown() override { g_calls.clear(); }
};

// ---- Tests --------------------------------------------------------------------

// [Boundary] size == 0 should return 0 and not call TestOneInput.
TEST_F(RE2FuzzerTest_386, ReturnsZero_WhenSizeIsZero_386) {
  int rc = LLVMFuzzerTestOneInput(nullptr, 0);
  EXPECT_EQ(rc, 0);
  EXPECT_TRUE(g_calls.empty()) << "TestOneInput must not be called for size==0";
}

// [Boundary] size > 4096 should return 0 and not call TestOneInput.
TEST_F(RE2FuzzerTest_386, ReturnsZero_WhenSizeExceedsMax_386) {
  std::vector<uint8_t> data(4097, 0xAB);
  int rc = LLVMFuzzerTestOneInput(data.data(), data.size());
  EXPECT_EQ(rc, 0);
  EXPECT_TRUE(g_calls.empty()) << "TestOneInput must not be called for size>4096";
}

// [Boundary] size == 4096 is within bounds → TestOneInput should be invoked once.
TEST_F(RE2FuzzerTest_386, InvokesTestOneInput_WhenSizeEqualsMax_386) {
  std::vector<uint8_t> data(4096, 0x11);
  int rc = LLVMFuzzerTestOneInput(data.data(), data.size());
  EXPECT_EQ(rc, 0);
  ASSERT_EQ(g_calls.size(), 1u) << "Expected exactly one call to TestOneInput";

  const CapturedCall& c = g_calls.front();

  // Anchor must be one of the allowed enum values.
  EXPECT_TRUE(c.anchor == RE2::UNANCHORED ||
              c.anchor == RE2::ANCHOR_START ||
              c.anchor == RE2::ANCHOR_BOTH);

  // Pattern/text lengths must respect the 999 cap used by the fuzzer.
  EXPECT_LE(c.pattern.size(), 999u);
  EXPECT_LE(c.text.size(), 999u);

  // Options contain some fixed settings set by the fuzzer (observable via getters).
  EXPECT_FALSE(c.options.log_errors()) << "Fuzzer forces log_errors(false)";
  EXPECT_EQ(c.options.max_mem(), static_cast<int64_t>(64) << 20)
      << "Fuzzer sets max_mem to 64<<20";
}

// [Normal] Any in-bounds size (e.g., 32) should cause exactly one call.
TEST_F(RE2FuzzerTest_386, InvokesTestOneInput_WithValidParams_WhenSizeInBounds_386) {
  std::vector<uint8_t> data(32, 0x7E);
  int rc = LLVMFuzzerTestOneInput(data.data(), data.size());
  EXPECT_EQ(rc, 0);
  ASSERT_EQ(g_calls.size(), 1u);

  const CapturedCall& c = g_calls.front();

  // Verify anchor is a valid enum value chosen from the provided array.
  EXPECT_TRUE(c.anchor == RE2::UNANCHORED ||
              c.anchor == RE2::ANCHOR_START ||
              c.anchor == RE2::ANCHOR_BOTH);

  // String sizes must not exceed 999 per the interface used.
  EXPECT_LE(c.pattern.size(), 999u);
  EXPECT_LE(c.text.size(), 999u);

  // Fixed, observable options set by the fuzzer.
  EXPECT_FALSE(c.options.log_errors());
  EXPECT_EQ(c.options.max_mem(), static_cast<int64_t>(64) << 20);
}

// [Negative interaction] Ensure no call occurs for both early-return cases.
TEST_F(RE2FuzzerTest_386, DoesNotInvokeTestOneInput_ForEarlyReturnSizes_386) {
  // size == 0
  (void)LLVMFuzzerTestOneInput(nullptr, 0);
  // size > 4096
  std::vector<uint8_t> big(5000, 0x00);
  (void)LLVMFuzzerTestOneInput(big.data(), big.size());

  EXPECT_TRUE(g_calls.empty()) << "TestOneInput must not be called on early returns";
}

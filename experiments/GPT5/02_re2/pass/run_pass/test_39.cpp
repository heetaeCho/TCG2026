// File: re2_options_getter_test_39.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

// Compile-time check: options() returns a const reference to RE2::Options.
static_assert(std::is_same<decltype(std::declval<const re2::RE2>().options()),
                           const re2::RE2::Options&>::value,
              "RE2::options() must return const RE2::Options&");

// Fixture kept minimal; no reliance on internal state or specific option fields.
class RE2OptionsTest_39 : public ::testing::Test {};

// [Normal operation] Calling options() multiple times returns the same reference for a given instance.
TEST_F(RE2OptionsTest_39, ConsistentReference_39) {
  re2::RE2 re("ab");
  const re2::RE2::Options* first = &re.options();
  const re2::RE2::Options* second = &re.options();

  // Observable behavior: the address of the returned reference should be stable per instance.
  EXPECT_EQ(first, second);
}

// [Boundary-ish] The reference remains stable even after exercising other public methods.
// (We do not assume any internal effects; just call a couple of public APIs.)
TEST_F(RE2OptionsTest_39, ReferenceStableAcrossCalls_39) {
  re2::RE2 re("(ab)+");
  const re2::RE2::Options* before = &re.options();

  // Exercise some unrelated public calls; we assert nothing about their outcomes.
  // We avoid inspecting internal state; only ensure options() remains callable and stable.
  (void)re.pattern();             // Access another getter.
  (void)re.NumberOfCapturingGroups();  // Another public method.

  const re2::RE2::Options* after = &re.options();
  EXPECT_EQ(before, after);
}

// [Exceptional/error case] Even if the pattern might be invalid, options() should be callable
// and return a reference (address is non-null). We do not assert on ok()/error_code() values.
TEST_F(RE2OptionsTest_39, OptionsAccessibleWithPotentiallyInvalidPattern_39) {
  re2::RE2 re("(");  // This may be an invalid regex in many engines; treat RE2 as a black box.

  const re2::RE2::Options* opts_addr = &re.options();
  // We can only assert that we receive a reference (i.e., we can take its address).
  // Since it's a reference, the pointer we take should be non-null.
  ASSERT_NE(opts_addr, nullptr);

  // And it should remain stable across repeated calls.
  EXPECT_EQ(opts_addr, &re.options());
}

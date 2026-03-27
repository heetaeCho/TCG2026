// File: ./TestProjects/re2/util/pcre_options_stack_limit_test_179.cc

#include "gtest/gtest.h"
#include "TestProjects/re2/util/pcre.h"

using re2::PCRE_Options;

// Verifies default-observable behavior only via the public API.
// No assumptions about internal state beyond what can be read back through
// stack_limit(), and no reimplementation of logic.

// Normal operation: default-constructed object reports a stack limit.
// (Based on provided interface snippet, expected default is 0.)
TEST(PCRE_OptionsTest_179, DefaultStackLimitIsZero_179) {
  PCRE_Options opts;
  EXPECT_EQ(0, opts.stack_limit());
}

// Normal operation: setting a positive stack limit is observable via getter.
TEST(PCRE_OptionsTest_179, SetStackLimitPositive_179) {
  PCRE_Options opts;
  const int kValue = 12345;
  opts.set_stack_limit(kValue);
  EXPECT_EQ(kValue, opts.stack_limit());
}

// Boundary condition: setting stack limit to zero is observable via getter.
TEST(PCRE_OptionsTest_179, SetStackLimitZero_179) {
  PCRE_Options opts;
  opts.set_stack_limit(0);
  EXPECT_EQ(0, opts.stack_limit());
}

// Edge input (no inference about validation): if a negative value is set,
// we only assert that the getter reflects the most recent public input.
// This avoids assuming clamping/validation that isn't specified.
TEST(PCRE_OptionsTest_179, SetStackLimitNegative_179) {
  PCRE_Options opts;
  opts.set_stack_limit(-1);
  EXPECT_EQ(-1, opts.stack_limit());
}

// State update behavior: the most recent set should be reflected by the getter.
TEST(PCRE_OptionsTest_179, SetStackLimitOverridesPrevious_179) {
  PCRE_Options opts;
  opts.set_stack_limit(10);
  EXPECT_EQ(10, opts.stack_limit());
  opts.set_stack_limit(20);
  EXPECT_EQ(20, opts.stack_limit());
}

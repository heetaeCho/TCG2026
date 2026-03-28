// File: ninja_main_test_164.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// We want to test the behavior of the `main` function in ninja.cc, but we
// cannot replace the test runner's main. So we:
//   1. Provide a stub for the external collaborator `real_main`.
//   2. Include ninja.cc while renaming its `main` to `ninja_main_entry_164`.
//   3. Call `ninja_main_entry_164` directly from our tests.

namespace {

// --- Test double for real_main (external collaborator) ------------------

// Track calls to real_main so we can verify interactions.
static int g_real_main_called_count = 0;
static int g_last_real_main_argc = -1;
static char** g_last_real_main_argv = nullptr;
static int g_real_main_return_value = 0;

// Stub implementation of real_main used only for tests.
// This is allowed by the constraints: we are mocking an external collaborator.
int real_main(int argc, char** argv) {
  ++g_real_main_called_count;
  g_last_real_main_argc = argc;
  g_last_real_main_argv = argv;
  return g_real_main_return_value;
}

// --- Pull in the production code with renamed main ----------------------

// Rename the production `main` symbol so it doesn't conflict with gtest.
#define main ninja_main_entry_164
#include "ninja.cc"
#undef main

// --- Test fixture -------------------------------------------------------

class NinjaMainTest_164 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_real_main_called_count = 0;
    g_last_real_main_argc = -1;
    g_last_real_main_argv = nullptr;
    g_real_main_return_value = 0;
  }
};

}  // namespace

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

// Verifies that the ninja main entry forwards argc/argv to real_main and
// that real_main is called exactly once.
TEST_F(NinjaMainTest_164, CallsRealMainWithSameArguments_164) {
  char arg0[] = "ninja";
  char arg1[] = "-f";
  char* argv[] = {arg0, arg1, nullptr};
  int argc = 2;

  int result = ninja_main_entry_164(argc, argv);

  // External interaction: real_main must be called once with same args.
  EXPECT_EQ(1, g_real_main_called_count);
  EXPECT_EQ(argc, g_last_real_main_argc);
  EXPECT_EQ(argv, g_last_real_main_argv);

  // For the non-MSVC branch, reaching the end of main without explicit
  // return yields 0; verify that we observe this behavior.
  EXPECT_EQ(0, result);
}

// Verifies that the return value of real_main is *not* propagated by main
// on the non-MSVC path (it should always return 0 in that branch).
TEST_F(NinjaMainTest_164, IgnoresRealMainReturnValue_164) {
  char arg0[] = "ninja";
  char* argv[] = {arg0, nullptr};
  int argc = 1;

  // Make the stub real_main return a non-zero value.
  g_real_main_return_value = 123;

  int result = ninja_main_entry_164(argc, argv);

  EXPECT_EQ(1, g_real_main_called_count);
  // Even though real_main returned 123, main should still result in 0
  // for the non-MSVC branch.
  EXPECT_EQ(0, result);
}

// Verifies behavior at a boundary condition: argc == 0 and argv == nullptr
// are still forwarded to real_main without crashing, and main still returns 0.
TEST_F(NinjaMainTest_164, HandlesZeroArgcAndNullArgv_164) {
  int argc = 0;
  char** argv = nullptr;

  int result = ninja_main_entry_164(argc, argv);

  EXPECT_EQ(1, g_real_main_called_count);
  EXPECT_EQ(0, g_last_real_main_argc);
  EXPECT_EQ(nullptr, g_last_real_main_argv);
  EXPECT_EQ(0, result);
}

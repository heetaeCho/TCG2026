// File: option_manager_parse_test_51.cc

#include <gtest/gtest.h>
#include <cstdlib>  // For EXIT_SUCCESS, EXIT_FAILURE

#include "glomap/controllers/option_manager.h"

// We only test observable behavior via the public interface (Parse).
// Internal state (desc_, options_*, etc.) is not accessed.

class OptionManagerParseTest_51 : public ::testing::Test {
 protected:
  void SetUp() override {
    // We don't assume anything about add_project_options other than
    // that it constructs a usable OptionManager instance.
    option_manager_ = std::make_unique<glomap::OptionManager>(false);
  }

  std::unique_ptr<glomap::OptionManager> option_manager_;
};

// Normal operation: no CLI options given.
// Expectation: Parse returns normally and does NOT call exit.
TEST_F(OptionManagerParseTest_51, ParseWithProgramNameOnly_DoesNotExit_51) {
  char arg0[] = "glomap_program";
  char* argv[] = {arg0};
  const int argc = 1;

  // If Parse() calls exit(), the test process would terminate and this test
  // would fail. Successful return means "normal operation".
  option_manager_->Parse(argc, argv);

  SUCCEED();
}

// Boundary condition / special behavior: "--help" option.
// Expectation: Parse prints usage information and exits with EXIT_SUCCESS.
TEST_F(OptionManagerParseTest_51, HelpOptionPrintsUsageAndExitsSuccess_51) {
  // Use ASSERT_EXIT so that calling exit() does not terminate the whole test
  // process. The code inside the lambda runs in a subprocess.
  ASSERT_EXIT(
      []() {
        glomap::OptionManager manager(false);

        char arg0[] = "glomap_program";
        char arg1[] = "--help";
        char* argv[] = {arg0, arg1};
        const int argc = 2;

        manager.Parse(argc, argv);
      }(),
      ::testing::ExitedWithCode(EXIT_SUCCESS),
      // We don't rely on the exact formatting of *desc_, only on the
      // constant prefix message that is written to std::cout.
      "The following options can be specified via command-line:");
}

// Error / exceptional behavior:
// Pass an unknown option so that command-line parsing fails.
// Expectation: Parse logs an error and exits with EXIT_FAILURE.
TEST_F(OptionManagerParseTest_51, UnknownOptionCausesErrorAndExitFailure_51) {
  ASSERT_EXIT(
      []() {
        glomap::OptionManager manager(false);

        char arg0[] = "glomap_program";
        char arg1[] = "--this_option_is_not_defined";
        char* argv[] = {arg0, arg1};
        const int argc = 2;

        manager.Parse(argc, argv);
      }(),
      ::testing::ExitedWithCode(EXIT_FAILURE),
      // The implementation logs an error with this prefix; we only match
      // the stable part of the message, not the specific exception text.
      "Failed to parse options");
}

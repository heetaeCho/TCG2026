// File: glomap_main_test_89.cc

#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

// The production code defines this in ./TestProjects/glomap/glomap/glomap.cc
// We just declare it here and treat it as a black box.
extern int main(int argc, char** argv);

class GlomapMainTest_89 : public ::testing::Test {
 protected:
  // Helper to call main() while capturing std::cout output.
  int CallMainCapturingStdout_89(int argc, char** argv, std::string* captured_output) {
    // Backup original buffer.
    std::streambuf* const old_buf = std::cout.rdbuf();
    std::ostringstream oss;
    std::cout.rdbuf(oss.rdbuf());

    int result = main(argc, argv);

    // Restore original buffer.
    std::cout.rdbuf(old_buf);

    if (captured_output) {
      *captured_output = oss.str();
    }
    return result;
  }
};

// Unknown command: should print an error message and return EXIT_FAILURE.
TEST_F(GlomapMainTest_89, UnknownCommandPrintsErrorAndReturnsFailure_89) {
  char program[] = "glomap";
  char cmd[] = "unknown_command_89";
  char* argv[] = {program, cmd};
  int argc = 2;

  std::string output;
  int result = CallMainCapturingStdout_89(argc, argv, &output);

  EXPECT_EQ(result, EXIT_FAILURE);

  // Check that the output contains the expected error message parts.
  EXPECT_NE(output.find("Command"), std::string::npos);
  EXPECT_NE(output.find("not recognized"), std::string::npos);
  EXPECT_NE(output.find("glomap help"), std::string::npos);
}

// "help" command: should *not* go through the "not recognized" branch.
TEST_F(GlomapMainTest_89, HelpCommandDoesNotPrintUnknownCommandMessage_89) {
  char program[] = "glomap";
  char cmd[] = "help";
  char* argv[] = {program, cmd};
  int argc = 2;

  std::string output;
  (void)CallMainCapturingStdout_89(argc, argv, &output);

  // The specific return value is determined by ShowHelp, which is treated
  // as a black box, so we only verify that the "unknown command" message
  // was not printed here.
  EXPECT_EQ(output.find("not recognized"), std::string::npos);
}

// "-h" option: should behave like help and not print the unknown-command message.
TEST_F(GlomapMainTest_89, ShortHelpOptionDoesNotPrintUnknownCommandMessage_89) {
  char program[] = "glomap";
  char cmd[] = "-h";
  char* argv[] = {program, cmd};
  int argc = 2;

  std::string output;
  (void)CallMainCapturingStdout_89(argc, argv, &output);

  EXPECT_EQ(output.find("not recognized"), std::string::npos);
}

// "--help" option: should also avoid the unknown-command message.
TEST_F(GlomapMainTest_89, LongHelpOptionDoesNotPrintUnknownCommandMessage_89) {
  char program[] = "glomap";
  char cmd[] = "--help";
  char* argv[] = {program, cmd};
  int argc = 2;

  std::string output;
  (void)CallMainCapturingStdout_89(argc, argv, &output);

  EXPECT_EQ(output.find("not recognized"), std::string::npos);
}

// Boundary condition: argc == 1 (no subcommand passed).
// This should call the help logic, and in particular must not print
// the "command not recognized" error branch.
TEST_F(GlomapMainTest_89, NoArgumentsShowsHelpWithoutUnknownCommandMessage_89) {
  char program[] = "glomap";
  char* argv[] = {program};
  int argc = 1;

  std::string output;
  (void)CallMainCapturingStdout_89(argc, argv, &output);

  EXPECT_EQ(output.find("not recognized"), std::string::npos);
}

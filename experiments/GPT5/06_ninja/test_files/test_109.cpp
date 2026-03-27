// File: msvc_helper_main_win32_test_109.cc

#include <string>
#include <stdexcept>
#include <cstdarg>

#include "gtest/gtest.h"

#include "clparser.h"
#include "msvc_helper.h"

// MSVCHelperMain is the function under test.
int MSVCHelperMain(int argc, char** argv);

// -----------------------------------------------------------------------------
// Test doubles / fakes for external collaborators
// -----------------------------------------------------------------------------

// We treat these as external collaborators, not the code under test, so
// providing simple fakes is allowed by the prompt constraints.

namespace {

using std::string;

// ==== Fatal() fake ===========================================================

struct FatalException : public std::runtime_error {
  explicit FatalException(const std::string& msg)
      : std::runtime_error(msg) {}
};

static std::string g_fatal_message;

void Fatal(const char* msg, ...) {
  char buffer[1024];
  va_list ap;
  va_start(ap, msg);
#if defined(_MSC_VER)
  vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, msg, ap);
#else
  vsnprintf(buffer, sizeof(buffer), msg, ap);
#endif
  va_end(ap);
  g_fatal_message = buffer;
  throw FatalException(g_fatal_message);
}

// ==== GetCommandLineA() fake =================================================

// The function under test uses GetCommandLineA() directly, so we provide a
// controllable fake implementation.

static std::string g_fake_command_line;

char* GetCommandLineA() {
  // Return a pointer to internal storage; MSVCHelperMain does not attempt to
  // free this pointer, it just scans it.
  return const_cast<char*>(g_fake_command_line.c_str());
}

// Helper to configure the fake command line in tests.
void SetFakeCommandLine(const std::string& cmdline) {
  g_fake_command_line = cmdline;
}

// ==== ReadFile() + PushPathIntoEnvironment() fakes ===========================

static int g_read_file_result = 0;
static std::string g_read_file_contents;
static std::string g_read_file_error;
static int g_read_file_call_count = 0;
static std::string g_last_pushed_env;

int ReadFile(const std::string& path,
             std::string* contents,
             std::string* err) {
  ++g_read_file_call_count;
  if (g_read_file_result == 0) {
    if (contents)
      *contents = g_read_file_contents;
    if (err)
      err->clear();
  } else {
    if (err)
      *err = g_read_file_error;
  }
  return g_read_file_result;
}

void PushPathIntoEnvironment(const std::string& env) {
  g_last_pushed_env = env;
}

// ==== CLWrapper fake =========================================================

static int g_clwrapper_run_call_count = 0;
static std::string g_clwrapper_last_command;
static std::string g_clwrapper_configured_output;
static int g_clwrapper_configured_exit_code = 0;
static void* g_clwrapper_last_env_block = nullptr;

// Provide method definitions matching msvc_helper.h; we are not re-implementing
// the real logic, only supplying a controllable stub for tests.
int CLWrapper::Run(const std::string& command, std::string* output) {
  ++g_clwrapper_run_call_count;
  g_clwrapper_last_command = command;
  if (output)
    *output = g_clwrapper_configured_output;
  return g_clwrapper_configured_exit_code;
}

void CLWrapper::SetEnvBlock(void* env_block) {
  g_clwrapper_last_env_block = env_block;
  env_block_ = env_block;
}

// ==== CLParser fake ==========================================================

static bool g_clparser_should_succeed = true;
static std::string g_clparser_filtered_output;
static std::string g_clparser_error_message;
static std::string g_clparser_last_input;
static std::string g_clparser_last_deps_prefix;
static int g_clparser_parse_call_count = 0;

bool CLParser::Parse(const std::string& output,
                     const std::string& deps_prefix,
                     std::string* filtered_output,
                     std::string* err) {
  ++g_clparser_parse_call_count;
  g_clparser_last_input = output;
  g_clparser_last_deps_prefix = deps_prefix;

  if (!g_clparser_should_succeed) {
    if (err)
      *err = g_clparser_error_message;
    return false;
  }

  if (filtered_output)
    *filtered_output = g_clparser_filtered_output;
  if (err)
    err->clear();
  return true;
}

// ==== WriteDepFileOrDie fake ================================================

static int g_write_depfile_call_count = 0;
static std::string g_last_depfile_path;

void WriteDepFileOrDie(const std::string& path, const CLParser& /*parser*/) {
  ++g_write_depfile_call_count;
  g_last_depfile_path = path;
}

// ==== Test fixture ===========================================================

struct MSVCHelperMainTest_109 : public ::testing::Test {
  void SetUp() override {
    g_fatal_message.clear();

    g_fake_command_line.clear();

    g_read_file_result = 0;
    g_read_file_contents.clear();
    g_read_file_error.clear();
    g_read_file_call_count = 0;
    g_last_pushed_env.clear();

    g_clwrapper_run_call_count = 0;
    g_clwrapper_last_command.clear();
    g_clwrapper_configured_output.clear();
    g_clwrapper_configured_exit_code = 0;
    g_clwrapper_last_env_block = nullptr;

    g_clparser_should_succeed = true;
    g_clparser_filtered_output.clear();
    g_clparser_error_message.clear();
    g_clparser_last_input.clear();
    g_clparser_last_deps_prefix.clear();
    g_clparser_parse_call_count = 0;

    g_write_depfile_call_count = 0;
    g_last_depfile_path.clear();
  }
};

}  // namespace

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

// 1) Normal behavior: "-h" help option should call Usage() internally and
//    return 0 without touching the rest of the pipeline.
TEST_F(MSVCHelperMainTest_109, HelpOptionReturnsZero_109) {
  // Even though the help path returns before command parsing, configure a
  // benign command line to be safe.
  SetFakeCommandLine("msvc_helper_main_win32 -t msvc -- cl.exe /c foo.cc");

  char* argv[] = {
      const_cast<char*>("msvc_helper_main_win32"),
      const_cast<char*>("-h"),
      nullptr};
  int argc = 2;

  int exit_code = MSVCHelperMain(argc, argv);

  EXPECT_EQ(0, exit_code);
  // No external collaborators should be involved.
  EXPECT_EQ(0, g_read_file_call_count);
  EXPECT_EQ(0, g_clwrapper_run_call_count);
  EXPECT_EQ(0, g_clparser_parse_call_count);
  EXPECT_EQ(0, g_write_depfile_call_count);
}

// 2) Error behavior: if the process command line does not contain " -- ",
//    MSVCHelperMain should call Fatal() with the expected message.
TEST_F(MSVCHelperMainTest_109, MissingCommandSeparatorCallsFatal_109) {
  // Command line with no " -- " separator.
  SetFakeCommandLine("msvc_helper_main_win32 -t msvc");

  char* argv[] = {
      const_cast<char*>("msvc_helper_main_win32"),
      nullptr};
  int argc = 1;

  EXPECT_THROW(
      {
        try {
          (void)MSVCHelperMain(argc, argv);
        } catch (const FatalException& ex) {
          // Verify that the error message mentions the expected text.
          EXPECT_NE(std::string::npos,
                    g_fatal_message.find(
                        "expected command line to end with \" -- command args\""));
          throw;
        }
      },
      FatalException);
}

// 3) Error behavior: if an env file is specified with -e but ReadFile()
//    fails (non-zero return), MSVCHelperMain should call Fatal() with a
//    message that includes the filename and error string.
TEST_F(MSVCHelperMainTest_109, EnvFileReadErrorTriggersFatal_109) {
  SetFakeCommandLine("msvc_helper_main_win32 -t msvc -- cl.exe /c foo.cc");

  // Configure ReadFile() to fail.
  g_read_file_result = 1;
  g_read_file_error = "disk error";

  char* argv[] = {
      const_cast<char*>("msvc_helper_main_win32"),
      const_cast<char*>("-e"),
      const_cast<char*>("envfile.txt"),
      nullptr};
  int argc = 3;

  EXPECT_THROW(
      {
        try {
          (void)MSVCHelperMain(argc, argv);
        } catch (const FatalException& ex) {
          // The formatted message should mention the file name and error.
          EXPECT_NE(std::string::npos,
                    g_fatal_message.find("couldn't open envfile.txt"));
          EXPECT_NE(std::string::npos,
                    g_fatal_message.find("disk error"));
          throw;
        }
      },
      FatalException);

  EXPECT_EQ(1, g_read_file_call_count);
  // No CL invocation should have happened because Fatal() aborts earlier.
  EXPECT_EQ(0, g_clwrapper_run_call_count);
}

// 4) Normal behavior: successful CL run with -o (deps file) and -p (deps
//    prefix).  CL output should be passed to CLParser, and on success a
//    depfile should be written, returning the CL exit code.
TEST_F(MSVCHelperMainTest_109, SuccessfulRunWithDepsFile_109) {
  // Command line with separator and some dummy command.
  SetFakeCommandLine(
      "msvc_helper_main_win32 -t msvc -- cl.exe /c foo.cc");

  // Configure CLWrapper fake.
  g_clwrapper_configured_output = "raw compiler output";
  g_clwrapper_configured_exit_code = 42;

  // Configure CLParser fake to succeed and emit filtered output.
  g_clparser_should_succeed = true;
  g_clparser_filtered_output = "filtered compiler output";

  char* argv[] = {
      const_cast<char*>("msvc_helper_main_win32"),
      const_cast<char*>("-o"),
      const_cast<char*>("out.d"),
      const_cast<char*>("-p"),
      const_cast<char*>("prefix: "),
      nullptr};
  int argc = 5;

  int exit_code = MSVCHelperMain(argc, argv);

  // Exit code from MSVCHelperMain should propagate CLWrapper's exit code.
  EXPECT_EQ(42, exit_code);

  // Verify CLWrapper::Run was called with the command part after " -- ".
  EXPECT_EQ(1, g_clwrapper_run_call_count);
  EXPECT_EQ(std::string("cl.exe /c foo.cc"), g_clwrapper_last_command);

  // Verify CLParser::Parse was called with CL output and deps prefix.
  EXPECT_EQ(1, g_clparser_parse_call_count);
  EXPECT_EQ(std::string("raw compiler output"), g_clparser_last_input);
  EXPECT_EQ(std::string("prefix: "), g_clparser_last_deps_prefix);

  // Verify that a depfile was written to the requested path.
  EXPECT_EQ(1, g_write_depfile_call_count);
  EXPECT_EQ(std::string("out.d"), g_last_depfile_path);

  // No env file given -> no env block should have been set.
  EXPECT_EQ(nullptr, g_clwrapper_last_env_block);
  EXPECT_EQ(0, g_read_file_call_count);
}

// 5) Error behavior: when CLParser::Parse() fails for the deps output,
//    MSVCHelperMain should call Fatal() with the parser error.
TEST_F(MSVCHelperMainTest_109, ParserFailureTriggersFatal_109) {
  SetFakeCommandLine(
      "msvc_helper_main_win32 -t msvc -- cl.exe /c foo.cc");

  // CLWrapper still runs successfully and produces output.
  g_clwrapper_configured_output = "raw compiler output";
  g_clwrapper_configured_exit_code = 0;

  // Configure CLParser fake to fail.
  g_clparser_should_succeed = false;
  g_clparser_error_message = "parse error from CLParser";

  char* argv[] = {
      const_cast<char*>("msvc_helper_main_win32"),
      const_cast<char*>("-o"),
      const_cast<char*>("out.d"),
      nullptr};
  int argc = 3;

  EXPECT_THROW(
      {
        try {
          (void)MSVCHelperMain(argc, argv);
        } catch (const FatalException& ex) {
          // Fatal should contain the parser's error message.
          EXPECT_NE(std::string::npos,
                    g_fatal_message.find("parse error from CLParser"));
          throw;
        }
      },
      FatalException);

  // We must have invoked CL before the parser failure.
  EXPECT_EQ(1, g_clwrapper_run_call_count);
  EXPECT_EQ(1, g_clparser_parse_call_count);
  // Depfile should not be written after a parse failure.
  EXPECT_EQ(0, g_write_depfile_call_count);
}

// 6) Boundary behavior: when CL produces an empty output string and there is
//    no deps file requested, MSVCHelperMain should simply return the exit code
//    without touching CLParser or depfile writing.
TEST_F(MSVCHelperMainTest_109, EmptyOutputReturnsExitCodeWithoutDeps_109) {
  SetFakeCommandLine(
      "msvc_helper_main_win32 -t msvc -- cl.exe /c foo.cc");

  // CLWrapper returns empty output.
  g_clwrapper_configured_output.clear();
  g_clwrapper_configured_exit_code = 7;

  char* argv[] = {
      const_cast<char*>("msvc_helper_main_win32"),
      nullptr};
  int argc = 1;

  int exit_code = MSVCHelperMain(argc, argv);

  EXPECT_EQ(7, exit_code);

  EXPECT_EQ(1, g_clwrapper_run_call_count);
  EXPECT_EQ(0, g_clparser_parse_call_count);
  EXPECT_EQ(0, g_write_depfile_call_count);
}

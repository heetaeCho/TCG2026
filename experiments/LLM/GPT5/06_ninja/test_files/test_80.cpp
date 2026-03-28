// File: ./TestProjects/ninja/tests/version_test_80.cc

#include <gtest/gtest.h>
#include <cstdarg>
#include <cstdio>
#include <string>

using std::string;

// We will include the real implementation of CheckNinjaVersion from version.cc,
// but redirect its external dependencies (ParseVersion, Warning, Fatal) to
// test doubles using macros.

// Forward declarations for our test doubles.
void TestParseVersion(const string& version, int* major, int* minor);
void TestWarning(const char* msg, ...);
void TestFatal(const char* msg, ...);

// Redirect the collaborators to our test doubles for this translation unit.
#define ParseVersion TestParseVersion
#define Warning      TestWarning
#define Fatal        TestFatal

// Include the actual implementation under test.
#include "TestProjects/ninja/src/version.cc"

#undef ParseVersion
#undef Warning
#undef Fatal

// If you have the header, you can include it instead of extern.
// #include "TestProjects/ninja/src/version.h"
extern const char* kNinjaVersion;  // from version.cc / version.h

// -------- Test double state & implementations --------

struct ParseScenario {
  int bin_major = 0;
  int bin_minor = 0;
  int file_major = 0;
  int file_minor = 0;
};

struct TestState {
  ParseScenario scenario;
  int parse_call_count = 0;

  bool warning_called = false;
  string warning_message;

  bool fatal_called = false;
  string fatal_message;
};

static TestState g_state;

static void ResetTestState() {
  g_state = TestState();  // reset all fields
}

void TestParseVersion(const string& /*version*/, int* major, int* minor) {
  // We don't re-implement real ParseVersion. Instead, we just feed values
  // according to the preconfigured test scenario and the call order.
  if (g_state.parse_call_count == 0) {
    *major = g_state.scenario.bin_major;
    *minor = g_state.scenario.bin_minor;
  } else {
    *major = g_state.scenario.file_major;
    *minor = g_state.scenario.file_minor;
  }
  ++g_state.parse_call_count;
}

static string FormatVarArgMessage(const char* fmt, va_list ap) {
  char buffer[1024];
  vsnprintf(buffer, sizeof(buffer), fmt, ap);
  return string(buffer);
}

void TestWarning(const char* msg, ...) {
  g_state.warning_called = true;
  va_list ap;
  va_start(ap, msg);
  g_state.warning_message = FormatVarArgMessage(msg, ap);
  va_end(ap);
}

void TestFatal(const char* msg, ...) {
  g_state.fatal_called = true;
  va_list ap;
  va_start(ap, msg);
  g_state.fatal_message = FormatVarArgMessage(msg, ap);
  va_end(ap);
}

// -------- Test fixture --------

class CheckNinjaVersionTest_80 : public ::testing::Test {
protected:
  void SetUp() override {
    ResetTestState();
  }
};

// -------- Tests --------

// Case: binary and file versions are the same -> no Warning, no Fatal.
TEST_F(CheckNinjaVersionTest_80, VersionsCompatible_NoWarningOrFatal_80) {
  g_state.scenario.bin_major  = 1;
  g_state.scenario.bin_minor  = 2;
  g_state.scenario.file_major = 1;
  g_state.scenario.file_minor = 2;

  CheckNinjaVersion("1.2");

  EXPECT_EQ(2, g_state.parse_call_count);  // both versions parsed
  EXPECT_FALSE(g_state.warning_called);
  EXPECT_FALSE(g_state.fatal_called);
}

// Case: binary major > file major -> Warning only, no Fatal.
TEST_F(CheckNinjaVersionTest_80, OlderBuildFileVersion_EmitsWarningOnly_80) {
  g_state.scenario.bin_major  = 2;
  g_state.scenario.bin_minor  = 0;
  g_state.scenario.file_major = 1;
  g_state.scenario.file_minor = 5;

  const string file_version = "1.5";
  CheckNinjaVersion(file_version);

  EXPECT_EQ(2, g_state.parse_call_count);
  EXPECT_TRUE(g_state.warning_called);
  EXPECT_FALSE(g_state.fatal_called);

  // Message should mention both the binary version and the file version.
  EXPECT_NE(g_state.warning_message.find("ninja executable version"), string::npos);
  EXPECT_NE(g_state.warning_message.find(kNinjaVersion), string::npos);
  EXPECT_NE(g_state.warning_message.find(file_version), string::npos);
}

// Case: same major, but binary minor < file minor -> Fatal.
TEST_F(CheckNinjaVersionTest_80, NewerBuildFileMinorVersion_EmitsFatal_80) {
  g_state.scenario.bin_major  = 1;
  g_state.scenario.bin_minor  = 1;
  g_state.scenario.file_major = 1;
  g_state.scenario.file_minor = 2;

  const string file_version = "1.2";
  CheckNinjaVersion(file_version);

  EXPECT_EQ(2, g_state.parse_call_count);
  EXPECT_FALSE(g_state.warning_called);
  EXPECT_TRUE(g_state.fatal_called);

  EXPECT_NE(g_state.fatal_message.find("incompatible"), string::npos);
  EXPECT_NE(g_state.fatal_message.find(kNinjaVersion), string::npos);
  EXPECT_NE(g_state.fatal_message.find(file_version), string::npos);
}

// Case: binary major < file major -> Fatal.
TEST_F(CheckNinjaVersionTest_80, NewerBuildFileMajorVersion_EmitsFatal_80) {
  g_state.scenario.bin_major  = 1;
  g_state.scenario.bin_minor  = 9;
  g_state.scenario.file_major = 2;
  g_state.scenario.file_minor = 0;

  const string file_version = "2.0";
  CheckNinjaVersion(file_version);

  EXPECT_EQ(2, g_state.parse_call_count);
  EXPECT_FALSE(g_state.warning_called);
  EXPECT_TRUE(g_state.fatal_called);

  EXPECT_NE(g_state.fatal_message.find("incompatible"), string::npos);
  EXPECT_NE(g_state.fatal_message.find(kNinjaVersion), string::npos);
  EXPECT_NE(g_state.fatal_message.find(file_version), string::npos);
}

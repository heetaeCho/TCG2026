// File: pdfsig_print_version_usage_test_2683.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <cstring>

using ::testing::HasSubstr;
using ::testing::Not;

// ---- Test double for printUsage (external collaborator) ----
// pdfsig.cc calls:
//   printUsage("pdfsig", "<PDF-file> [<output-file>]", argDesc);
// We intercept that call here to verify it happens (or not) and with what parameters.
extern "C++" {

// Forward declare ArgDesc (actual definition comes from parseargs.h included by pdfsig.cc).
struct ArgDesc;

static bool g_printUsage_called_2683 = false;
static std::string g_printUsage_prog_2683;
static std::string g_printUsage_args_2683;
static const ArgDesc* g_printUsage_argDescPtr_2683 = nullptr;

// Match the expected signature used by Poppler utils.
void printUsage(const char* program, const char* otherArgs, const ArgDesc* argDesc)
{
  g_printUsage_called_2683 = true;
  g_printUsage_prog_2683 = program ? program : "";
  g_printUsage_args_2683 = otherArgs ? otherArgs : "";
  g_printUsage_argDescPtr_2683 = argDesc;

  // Emit a marker so stderr capture can confirm it was reached.
  std::fprintf(stderr, "USAGE_STUB_2683\n");
}

} // extern "C++"

// ---- Include the implementation under test ----
// print_version_usage is a static function in pdfsig.cc; to test it as a black box,
// we compile it into this test translation unit via include.
// pdfsig.cc may define a main(); rename it to avoid collision with gtest main.
#define main pdfsig_main_2683
#include "TestProjects/poppler/utils/pdfsig.cc"
#undef main

namespace {

class PdfsigPrintVersionUsageTest_2683 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_printUsage_called_2683 = false;
    g_printUsage_prog_2683.clear();
    g_printUsage_args_2683.clear();
    g_printUsage_argDescPtr_2683 = nullptr;
  }
};

TEST_F(PdfsigPrintVersionUsageTest_2683, UsageFalse_PrintsVersionAndCopyrights_NoUsage_2683)
{
  testing::internal::CaptureStderr();
  print_version_usage(false);
  const std::string out = testing::internal::GetCapturedStderr();

  EXPECT_THAT(out, HasSubstr("pdfsig version "));
  // These come from pdfsig.cc globals and should be printed unconditionally.
  EXPECT_THAT(out, HasSubstr(popplerCopyright));
  EXPECT_THAT(out, HasSubstr(xpdfCopyright));

  EXPECT_FALSE(g_printUsage_called_2683);
  EXPECT_THAT(out, Not(HasSubstr("USAGE_STUB_2683")));
}

TEST_F(PdfsigPrintVersionUsageTest_2683, UsageTrue_PrintsUsageAndPassesExpectedArgs_2683)
{
  testing::internal::CaptureStderr();
  print_version_usage(true);
  const std::string out = testing::internal::GetCapturedStderr();

  EXPECT_THAT(out, HasSubstr("pdfsig version "));
  EXPECT_THAT(out, HasSubstr(popplerCopyright));
  EXPECT_THAT(out, HasSubstr(xpdfCopyright));

  EXPECT_TRUE(g_printUsage_called_2683);
  EXPECT_EQ(g_printUsage_prog_2683, "pdfsig");
  EXPECT_EQ(g_printUsage_args_2683, "<PDF-file> [<output-file>]");
  // Should pass the same argDesc table that pdfsig.cc uses.
  EXPECT_EQ(g_printUsage_argDescPtr_2683, ::argDesc);

  EXPECT_THAT(out, HasSubstr("USAGE_STUB_2683"));
}

TEST_F(PdfsigPrintVersionUsageTest_2683, Boundary_CalledMultipleTimes_TogglesUsageBehavior_2683)
{
  // First call with usage=true
  testing::internal::CaptureStderr();
  print_version_usage(true);
  std::string out1 = testing::internal::GetCapturedStderr();
  EXPECT_TRUE(g_printUsage_called_2683);
  EXPECT_THAT(out1, HasSubstr("USAGE_STUB_2683"));

  // Reset stub observation and call with usage=false
  g_printUsage_called_2683 = false;
  g_printUsage_prog_2683.clear();
  g_printUsage_args_2683.clear();
  g_printUsage_argDescPtr_2683 = nullptr;

  testing::internal::CaptureStderr();
  print_version_usage(false);
  std::string out2 = testing::internal::GetCapturedStderr();

  EXPECT_FALSE(g_printUsage_called_2683);
  EXPECT_THAT(out2, Not(HasSubstr("USAGE_STUB_2683")));
  EXPECT_THAT(out2, HasSubstr("pdfsig version "));
}

}  // namespace
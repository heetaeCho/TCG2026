// File: util/posix_logger_test.cc
#include "util/posix_logger.h"
#include "leveldb/env.h"

#include <cstdio>
#include <cstdarg>
#include <string>
#include <vector>
#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::HasSubstr;

namespace leveldb {
namespace {

// Small helper to call Logv with varargs without re-implementing any logic.
static void Logf(Logger* logger, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  logger->Logv(fmt, ap);
  va_end(ap);
}

// Read the entire contents of a FILE* from the beginning (observable state).
static std::string ReadAll(FILE* fp) {
  ASSERT_NE(fp, nullptr);
  fflush(fp);
  long cur = ftell(fp);
  ASSERT_NE(cur, -1);
  ASSERT_EQ(fseek(fp, 0, SEEK_SET), 0);

  std::string out;
  char buf[4096];
  size_t n;
  while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
    out.append(buf, n);
  }

  // Return to original position (best effort).
  (void)fseek(fp, cur, SEEK_SET);
  return out;
}

class PosixLoggerTest_494 : public ::testing::Test {};

// --- Constructor behavior ---

// Verifies the precondition enforced by the constructor (assert on nullptr).
TEST_F(PosixLoggerTest_494, ConstructorNullFile_Death_494) {
#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-core.NullDereference)
        PosixLogger logger(nullptr);
        (void)logger;
      },
      "");
#else
  GTEST_SKIP() << "Death tests not supported on this platform/toolchain.";
#endif
}

// --- Logv behavior (observable via file effects) ---

// Normal case: a formatted message appears in the output stream.
TEST_F(PosixLoggerTest_494, Logv_WritesFormattedMessage_494) {
  std::FILE* fp = tmpfile();
  ASSERT_NE(fp, nullptr);

  PosixLogger logger(fp);
  Logf(&logger, "alpha %d %s", 7, "beta");

  std::string content = ReadAll(fp);
  // We don't assume anything about prefixes/suffixes (timestamps, newlines).
  // We only assert that the formatted substring is present.
  EXPECT_THAT(content, HasSubstr("alpha 7 beta"));

  std::fclose(fp);
}

// Multiple calls should result in additional data being written (append).
TEST_F(PosixLoggerTest_494, Logv_AppendsOnMultipleCalls_494) {
  std::FILE* fp = tmpfile();
  ASSERT_NE(fp, nullptr);

  PosixLogger logger(fp);
  Logf(&logger, "first");
  Logf(&logger, "second");

  std::string content = ReadAll(fp);
  auto first_pos = content.find("first");
  auto second_pos = content.find("second");

  EXPECT_NE(first_pos, std::string::npos);
  EXPECT_NE(second_pos, std::string::npos);
  // The second message should appear after the first.
  EXPECT_LT(first_pos, second_pos);

  std::fclose(fp);
}

// Boundary-like case: logging an empty format string should still be safe,
// and cause some observable write (file size should not shrink).
TEST_F(PosixLoggerTest_494, Logv_EmptyFormatStringSafe_494) {
  std::FILE* fp = tmpfile();
  ASSERT_NE(fp, nullptr);

  PosixLogger logger(fp);

  std::string before = ReadAll(fp);
  Logf(&logger, "");  // No assumptions on exact content added.
  std::string after = ReadAll(fp);

  // We only check that something (even a newline or timestamp) may have been written.
  // If the implementation chooses to write nothing for an empty format, this still
  // must not crash; in that case, sizes may be equal. Assert no crash and allow both.
  // To keep the test objective, require non-decreasing size.
  EXPECT_GE(after.size(), before.size());

  std::fclose(fp);
}

// Stress-like boundary: a long formatted message. We do not assume complete
// retention beyond verifying that some portion is observable in the sink.
TEST_F(PosixLoggerTest_494, Logv_LongMessageContainsSubstring_494) {
  std::FILE* fp = tmpfile();
  ASSERT_NE(fp, nullptr);

  // Build a long string payload.
  std::string payload(8192, 'X');
  PosixLogger logger(fp);
  Logf(&logger, "%s", payload.c_str());

  std::string content = ReadAll(fp);
  // Assert that at least a recognizable portion is present. We avoid asserting on
  // exact length or full content to not infer buffering/truncation policy.
  EXPECT_THAT(content, HasSubstr("XXXXX"));  // A short, clear substring.

  std::fclose(fp);
}

}  // namespace
}  // namespace leveldb

// windows_logger_test.cc
#include "util/windows_logger.h"   // Class under test
#include "leveldb/env.h"           // Base Logger interface
#include <gtest/gtest.h>

#include <cstdarg>
#include <cstdio>
#include <memory>

// Helper that exercises the virtual Logv through the Logger interface
static void CallLogv(leveldb::Logger* logger, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  logger->Logv(fmt, ap);  // Observable behavior: must not crash
  va_end(ap);
}

class WindowsLoggerTest_495 : public ::testing::Test {};

// Normal operation: constructing with a valid FILE* must not crash.
TEST_F(WindowsLoggerTest_495, ConstructWithValidFile_DoesNotCrash_495) {
  std::FILE* fp = std::tmpfile();  // valid FILE*, may be nullptr if OS forbids
  ASSERT_NE(fp, nullptr) << "std::tmpfile() returned nullptr; environment issue";

  // Construction should succeed and not crash.
  leveldb::WindowsLogger logger(fp);

  // No further assertions; we only verify observable behavior: no crash.
  SUCCEED();
}

// Boundary/exceptional behavior: constructing with nullptr should trigger an assert.
// Skip in release builds where asserts are compiled out.
TEST_F(WindowsLoggerTest_495, ConstructWithNullFile_TriggersAssert_495) {
#ifdef NDEBUG
  GTEST_SKIP() << "Assertions are disabled (NDEBUG defined); skipping death test.";
#else
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-core.NullDereference)
        leveldb::WindowsLogger logger(nullptr);
        (void)logger;  // suppress unused warning
      },
      "");  // We don't depend on the exact assert message.
#endif
}

// Verification of external interaction via base-class API: calling Logv via Logger*
// should be accepted and not crash (polymorphism works).
TEST_F(WindowsLoggerTest_495, LogvThroughBasePointer_DoesNotCrash_495) {
  std::FILE* fp = std::tmpfile();
  ASSERT_NE(fp, nullptr) << "std::tmpfile() returned nullptr; environment issue";

  // Use base-class pointer to validate virtual dispatch works with the interface.
  std::unique_ptr<leveldb::Logger> logger(new leveldb::WindowsLogger(fp));

  // We cannot assert on output; we only ensure the call is accepted and does not crash.
  CallLogv(logger.get(), "%s %d", "answer", 42);

  SUCCEED();
}

// File: db/c_options_set_info_log_test.cc

#include <gtest/gtest.h>

extern "C" {
// Forward declarations from the C API we are testing.
struct leveldb_options_t;
struct leveldb_logger_t;
void leveldb_options_set_info_log(leveldb_options_t* opt, leveldb_logger_t* l);
}

// ---- Minimal interface-only declarations based on the prompt ----
// We do NOT re-implement any logic; these mirror the provided interfaces
// so the tests can construct inputs and observe public, visible effects.

namespace leveldb {
struct Logger { virtual ~Logger() = default; };
struct Options {
  // Only the field we need to observe for this API
  Logger* info_log = nullptr;
};
}  // namespace leveldb

struct leveldb_options_t { leveldb::Options rep; };
struct leveldb_logger_t { leveldb::Logger* rep; };

// A tiny helper to create a logger wrapper around a concrete Logger pointer.
static leveldb_logger_t MakeLogger(leveldb::Logger* p) {
  leveldb_logger_t l{};
  l.rep = p;
  return l;
}

// Test fixture
class OptionsSetInfoLogTest_259 : public ::testing::Test {
protected:
  leveldb_options_t opt_{};  // starts with rep.info_log == nullptr
};

// Normal operation: sets a non-null logger
TEST_F(OptionsSetInfoLogTest_259, SetsNonNullLogger_259) {
  leveldb::Logger real_logger;
  auto logger = MakeLogger(&real_logger);

  ASSERT_EQ(opt_.rep.info_log, nullptr) << "Precondition: info_log should start null";

  leveldb_options_set_info_log(&opt_, &logger);

  EXPECT_EQ(opt_.rep.info_log, &real_logger)
      << "info_log must point to the provided logger's rep";
}

// Boundary: passing nullptr logger clears the field to nullptr
TEST_F(OptionsSetInfoLogTest_259, SetsNullWhenLoggerIsNull_259) {
  leveldb::Logger real_logger;
  auto logger = MakeLogger(&real_logger);
  // First set to a valid logger
  leveldb_options_set_info_log(&opt_, &logger);
  ASSERT_NE(opt_.rep.info_log, nullptr) << "Precondition: set to non-null first";

  // Now pass nullptr to clear
  leveldb_options_set_info_log(&opt_, nullptr);

  EXPECT_EQ(opt_.rep.info_log, nullptr)
      << "info_log must become nullptr when nullptr logger is provided";
}

// Overwrite behavior: subsequent call replaces the existing pointer
TEST_F(OptionsSetInfoLogTest_259, OverwritesExistingLogger_259) {
  leveldb::Logger first_logger;
  leveldb::Logger second_logger;
  auto logger1 = MakeLogger(&first_logger);
  auto logger2 = MakeLogger(&second_logger);

  leveldb_options_set_info_log(&opt_, &logger1);
  ASSERT_EQ(opt_.rep.info_log, &first_logger) << "Precondition: set to first";

  leveldb_options_set_info_log(&opt_, &logger2);

  EXPECT_EQ(opt_.rep.info_log, &second_logger)
      << "info_log must be overwritten to the new logger";
}

// Idempotency: setting the same logger twice leaves the pointer unchanged
TEST_F(OptionsSetInfoLogTest_259, SettingSameLoggerTwiceIsStable_259) {
  leveldb::Logger logger_inst;
  auto logger = MakeLogger(&logger_inst);

  leveldb_options_set_info_log(&opt_, &logger);
  auto* before = opt_.rep.info_log;

  leveldb_options_set_info_log(&opt_, &logger);
  auto* after = opt_.rep.info_log;

  EXPECT_EQ(before, after)
      << "Setting the same logger again should leave info_log unchanged";
}

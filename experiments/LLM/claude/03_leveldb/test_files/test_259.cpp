#include "gtest/gtest.h"

// Include necessary headers
#include "leveldb/options.h"

// We need the C API structures. Since they are defined in db/c.cc,
// we replicate the struct definitions here for testing purposes.
// These match the known/inferred dependencies.

namespace leveldb {
class Logger;
}

struct leveldb_options_t {
  leveldb::Options rep;
};

struct leveldb_logger_t {
  leveldb::Logger* rep;
};

// Declaration of the function under test (defined in db/c.cc)
extern "C" {
void leveldb_options_set_info_log(leveldb_options_t* opt, leveldb_logger_t* l);
}

class LeveldbOptionsSetInfoLogTest_259 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that passing a nullptr logger sets info_log to nullptr
TEST_F(LeveldbOptionsSetInfoLogTest_259, SetInfoLogWithNullLogger_259) {
  // First, ensure info_log starts as nullptr (default)
  EXPECT_EQ(opt_->rep.info_log, nullptr);

  // Set with nullptr logger
  leveldb_options_set_info_log(opt_, nullptr);

  EXPECT_EQ(opt_->rep.info_log, nullptr);
}

// Test that passing a non-null logger sets info_log to logger's rep
TEST_F(LeveldbOptionsSetInfoLogTest_259, SetInfoLogWithValidLogger_259) {
  // Create a fake logger pointer (we don't need a real Logger, just an address)
  int dummy;
  leveldb::Logger* fake_logger = reinterpret_cast<leveldb::Logger*>(&dummy);

  leveldb_logger_t logger_wrapper;
  logger_wrapper.rep = fake_logger;

  leveldb_options_set_info_log(opt_, &logger_wrapper);

  EXPECT_EQ(opt_->rep.info_log, fake_logger);
}

// Test that setting a logger and then setting nullptr clears info_log
TEST_F(LeveldbOptionsSetInfoLogTest_259, SetInfoLogThenClearWithNull_259) {
  int dummy;
  leveldb::Logger* fake_logger = reinterpret_cast<leveldb::Logger*>(&dummy);

  leveldb_logger_t logger_wrapper;
  logger_wrapper.rep = fake_logger;

  // Set a valid logger
  leveldb_options_set_info_log(opt_, &logger_wrapper);
  EXPECT_EQ(opt_->rep.info_log, fake_logger);

  // Clear by passing nullptr
  leveldb_options_set_info_log(opt_, nullptr);
  EXPECT_EQ(opt_->rep.info_log, nullptr);
}

// Test that passing a logger with rep == nullptr sets info_log to nullptr
TEST_F(LeveldbOptionsSetInfoLogTest_259, SetInfoLogWithLoggerHavingNullRep_259) {
  leveldb_logger_t logger_wrapper;
  logger_wrapper.rep = nullptr;

  // logger_wrapper is non-null, but its rep is nullptr
  // The function checks (l ? l->rep : nullptr), so l is non-null -> info_log = l->rep = nullptr
  leveldb_options_set_info_log(opt_, &logger_wrapper);

  EXPECT_EQ(opt_->rep.info_log, nullptr);
}

// Test overwriting one logger with another
TEST_F(LeveldbOptionsSetInfoLogTest_259, OverwriteInfoLogWithDifferentLogger_259) {
  int dummy1, dummy2;
  leveldb::Logger* fake_logger1 = reinterpret_cast<leveldb::Logger*>(&dummy1);
  leveldb::Logger* fake_logger2 = reinterpret_cast<leveldb::Logger*>(&dummy2);

  leveldb_logger_t logger_wrapper1;
  logger_wrapper1.rep = fake_logger1;

  leveldb_logger_t logger_wrapper2;
  logger_wrapper2.rep = fake_logger2;

  // Set first logger
  leveldb_options_set_info_log(opt_, &logger_wrapper1);
  EXPECT_EQ(opt_->rep.info_log, fake_logger1);

  // Overwrite with second logger
  leveldb_options_set_info_log(opt_, &logger_wrapper2);
  EXPECT_EQ(opt_->rep.info_log, fake_logger2);
  EXPECT_NE(opt_->rep.info_log, fake_logger1);
}

// Test setting the same logger twice is idempotent
TEST_F(LeveldbOptionsSetInfoLogTest_259, SetSameLoggerTwice_259) {
  int dummy;
  leveldb::Logger* fake_logger = reinterpret_cast<leveldb::Logger*>(&dummy);

  leveldb_logger_t logger_wrapper;
  logger_wrapper.rep = fake_logger;

  leveldb_options_set_info_log(opt_, &logger_wrapper);
  EXPECT_EQ(opt_->rep.info_log, fake_logger);

  leveldb_options_set_info_log(opt_, &logger_wrapper);
  EXPECT_EQ(opt_->rep.info_log, fake_logger);
}

// Test default value of info_log is nullptr before any call
TEST_F(LeveldbOptionsSetInfoLogTest_259, DefaultInfoLogIsNull_259) {
  EXPECT_EQ(opt_->rep.info_log, nullptr);
}

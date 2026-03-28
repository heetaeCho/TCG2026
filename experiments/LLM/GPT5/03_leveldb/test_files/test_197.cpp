// File: db/dumpfile_test_197.cc

#include "gtest/gtest.h"
#include <string>

// Forward declarations for the unit under test and its dependencies.
#include "db/filename.h"     // for leveldb::FileType enum
#include "leveldb/status.h"  // for leveldb::Status
#include "leveldb/env.h"     // for leveldb::Env, leveldb::WritableFile

namespace leveldb {
// Forward-declare the function under test.
Status DumpFile(Env* env, const std::string& fname, WritableFile* dst);
}

// ---- Test doubles for external collaborators (free functions) ----
// We provide *stub* implementations to observe calls & control returns.
// These are external collaborators, so substituting them is allowed by the rules.

namespace {

using namespace leveldb;

// Simple no-op WritableFile for passing through to DumpFile/Dump*.
class DummyWritableFile : public WritableFile {
 public:
  ~DummyWritableFile() override = default;
};

// Simple no-op Env for passing through to DumpFile/Dump*.
class DummyEnv : public Env {
 public:
  ~DummyEnv() override = default;
};

// Global knobs & probes (scoped to this TU) to observe collaborator usage.
static int g_guess_calls = 0;
static FileType g_guess_type_to_set = kLogFile;
static bool g_guess_return = true;

static int g_dump_log_calls = 0;
static int g_dump_desc_calls = 0;
static int g_dump_table_calls = 0;

static Status g_dump_log_status = Status::OK();
static Status g_dump_desc_status = Status::OK();
static Status g_dump_table_status = Status::OK();

static Env* g_last_env = nullptr;
static std::string g_last_fname;
static WritableFile* g_last_dst = nullptr;

void ResetProbes() {
  g_guess_calls = 0;
  g_dump_log_calls = 0;
  g_dump_desc_calls = 0;
  g_dump_table_calls = 0;
  g_last_env = nullptr;
  g_last_fname.clear();
  g_last_dst = nullptr;
  g_guess_type_to_set = kLogFile;
  g_guess_return = true;
  g_dump_log_status = Status::OK();
  g_dump_desc_status = Status::OK();
  g_dump_table_status = Status::OK();
}

// ---- Stubbed external collaborators used by DumpFile ----
namespace leveldb {

bool GuessType(const std::string& fname, FileType* type) {
  ++g_guess_calls;
  if (type) *type = g_guess_type_to_set;
  // Also capture the last seen fname, since DumpFile forwards it to Dump*.
  g_last_fname = fname;
  return g_guess_return;
}

Status DumpLog(Env* env, const std::string& fname, WritableFile* dst) {
  ++g_dump_log_calls;
  g_last_env = env;
  g_last_fname = fname;
  g_last_dst = dst;
  return g_dump_log_status;
}

Status DumpDescriptor(Env* env, const std::string& fname, WritableFile* dst) {
  ++g_dump_desc_calls;
  g_last_env = env;
  g_last_fname = fname;
  g_last_dst = dst;
  return g_dump_desc_status;
}

Status DumpTable(Env* env, const std::string& fname, WritableFile* dst) {
  ++g_dump_table_calls;
  g_last_env = env;
  g_last_fname = fname;
  g_last_dst = dst;
  return g_dump_table_status;
}

}  // namespace leveldb

// ---- Test fixture ----
class DumpFileTest_197 : public ::testing::Test {
 protected:
  void SetUp() override { ResetProbes(); }
  DummyEnv env_;
  DummyWritableFile out_;
};

}  // namespace

// ---------------------- TESTS ----------------------

// 1) Normal operation: kLogFile → forwards to DumpLog and returns its Status.
TEST_F(DumpFileTest_197, ForwardsToDumpLogAndPropagatesStatus_197) {
  using namespace leveldb;
  g_guess_type_to_set = kLogFile;
  g_dump_log_status = Status::NotSupported("log status");

  const std::string fname = "any.log";
  Status s = DumpFile(&env_, fname, &out_);

  EXPECT_EQ(g_guess_calls, 1);
  EXPECT_EQ(g_dump_log_calls, 1);
  EXPECT_EQ(g_dump_desc_calls, 0);
  EXPECT_EQ(g_dump_table_calls, 0);

  // Verifies the exact parameters were forwarded.
  EXPECT_EQ(g_last_env, &env_);
  EXPECT_EQ(g_last_fname, fname);
  EXPECT_EQ(g_last_dst, &out_);

  // Returns exactly what DumpLog returned.
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotSupportedError());
}

// 2) Normal operation: kDescriptorFile → forwards to DumpDescriptor and returns its Status.
TEST_F(DumpFileTest_197, ForwardsToDumpDescriptorAndPropagatesStatus_197) {
  using namespace leveldb;
  g_guess_type_to_set = kDescriptorFile;
  g_dump_desc_status = Status::Corruption("descriptor status");

  const std::string fname = "MANIFEST-000001";
  Status s = DumpFile(&env_, fname, &out_);

  EXPECT_EQ(g_guess_calls, 1);
  EXPECT_EQ(g_dump_log_calls, 0);
  EXPECT_EQ(g_dump_desc_calls, 1);
  EXPECT_EQ(g_dump_table_calls, 0);

  EXPECT_EQ(g_last_env, &env_);
  EXPECT_EQ(g_last_fname, fname);
  EXPECT_EQ(g_last_dst, &out_);

  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

// 3) Normal operation: kTableFile → forwards to DumpTable and returns its Status.
TEST_F(DumpFileTest_197, ForwardsToDumpTableAndPropagatesStatus_197) {
  using namespace leveldb;
  g_guess_type_to_set = kTableFile;
  g_dump_table_status = Status::OK();

  const std::string fname = "000123.ldb";
  Status s = DumpFile(&env_, fname, &out_);

  EXPECT_EQ(g_guess_calls, 1);
  EXPECT_EQ(g_dump_log_calls, 0);
  EXPECT_EQ(g_dump_desc_calls, 0);
  EXPECT_EQ(g_dump_table_calls, 1);

  EXPECT_EQ(g_last_env, &env_);
  EXPECT_EQ(g_last_fname, fname);
  EXPECT_EQ(g_last_dst, &out_);

  EXPECT_TRUE(s.ok());
}

// 4) Boundary/error: GuessType returns false → InvalidArgument: "<fname>: unknown file type".
TEST_F(DumpFileTest_197, UnknownFileTypeReturnsInvalidArgument_197) {
  using namespace leveldb;
  g_guess_return = false;  // Force GuessType failure.

  const std::string fname = "mystery.file";
  Status s = DumpFile(&env_, fname, &out_);

  EXPECT_EQ(g_guess_calls, 1);
  EXPECT_EQ(g_dump_log_calls, 0);
  EXPECT_EQ(g_dump_desc_calls, 0);
  EXPECT_EQ(g_dump_table_calls, 0);

  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
  // Optional: Message should mention fname and reason. We check for substrings without asserting exact text.
  std::string msg = s.ToString();
  EXPECT_NE(msg.find("unknown file type"), std::string::npos);
  EXPECT_NE(msg.find(fname), std::string::npos);
}

// 5) Boundary/error: Non-dumpable file type → InvalidArgument: "<fname>: not a dump-able file type".
TEST_F(DumpFileTest_197, NonDumpableFileTypeReturnsInvalidArgument_197) {
  using namespace leveldb;
  g_guess_return = true;
  g_guess_type_to_set = kDBLockFile;  // Known type but not dump-able by DumpFile's switch.

  const std::string fname = "LOCK";
  Status s = DumpFile(&env_, fname, &out_);

  EXPECT_EQ(g_guess_calls, 1);
  EXPECT_EQ(g_dump_log_calls, 0);
  EXPECT_EQ(g_dump_desc_calls, 0);
  EXPECT_EQ(g_dump_table_calls, 0);

  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
  std::string msg = s.ToString();
  EXPECT_NE(msg.find("not a dump-able file type"), std::string::npos);
  EXPECT_NE(msg.find(fname), std::string::npos);
}

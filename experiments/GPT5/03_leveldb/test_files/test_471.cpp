// read_file_to_string_test_471.cc
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace leveldb {

// Minimal mocks for the collaborators used by ReadFileToString.
class MockSequentialFile : public SequentialFile {
 public:
  MOCK_METHOD(Status, Read, (size_t n, Slice* result, char* scratch), (override));
  MOCK_METHOD(Status, Skip, (uint64_t n), (override));
  // Virtual destructor exists in the interface; default is fine.
  ~MockSequentialFile() override = default;
};

class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile, (const std::string& fname, SequentialFile** result), (override));
  // Other virtuals are irrelevant for these tests.
  ~MockEnv() override = default;
};

class ReadFileToStringTest_471 : public ::testing::Test {};

// --- Normal operation: reads multiple fragments and stops at EOF (empty fragment) ---
TEST_F(ReadFileToStringTest_471, ReadsWholeFileInChunks_471) {
  MockEnv env;
  auto* mock_file = new MockSequentialFile;

  const std::string kName = "path/to/file.dat";

  // Env returns our mock file and OK.
  EXPECT_CALL(env, NewSequentialFile(kName, _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  // 1st read -> "hello "
  EXPECT_CALL(*mock_file, Read(_, _, _))
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        static const char* kChunk1 = "hello ";
        *out = Slice(kChunk1, 6);
        return Status::OK();
      }))
  // 2nd read -> "world"
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        static const char* kChunk2 = "world";
        *out = Slice(kChunk2, 5);
        return Status::OK();
      }))
  // 3rd read -> EOF: empty fragment with OK
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        *out = Slice("", 0);
        return Status::OK();
      }));

  std::string data = "pre-filled that should be cleared";
  Status s = ReadFileToString(&env, kName, &data);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data, "hello world");
}

// --- Error before opening: NewSequentialFile failure propagates, data cleared ---
TEST_F(ReadFileToStringTest_471, NewSequentialFileFailure_471) {
  MockEnv env;
  const std::string kName = "missing/file.dat";

  EXPECT_CALL(env, NewSequentialFile(kName, _))
      .WillOnce(Return(Status::IOError("open failed")));

  std::string data = "garbage";
  Status s = ReadFileToString(&env, kName, &data);

  EXPECT_TRUE(s.IsIOError());
  EXPECT_EQ(data, "");  // must be cleared even on failure
}

// --- Error during reading: earlier bytes kept, final status is the error ---
TEST_F(ReadFileToStringTest_471, ReadErrorMidway_471) {
  MockEnv env;
  auto* mock_file = new MockSequentialFile;
  const std::string kName = "partial.dat";

  EXPECT_CALL(env, NewSequentialFile(kName, _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  // 1st read OK -> "part"
  EXPECT_CALL(*mock_file, Read(_, _, _))
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        static const char* kChunk = "part";
        *out = Slice(kChunk, 4);
        return Status::OK();
      }))
  // 2nd read fails -> IOError (no append on this iteration)
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        // Ensure we don't accidentally append anything on error.
        *out = Slice("", 0);
        return Status::IOError("disk read error");
      }));

  std::string data;
  Status s = ReadFileToString(&env, kName, &data);

  EXPECT_TRUE(s.IsIOError());
  EXPECT_EQ(data, "part");  // bytes read before the error remain
}

// --- Empty file: first read returns empty fragment with OK; result is empty string ---
TEST_F(ReadFileToStringTest_471, EmptyFileReturnsEmptyString_471) {
  MockEnv env;
  auto* mock_file = new MockSequentialFile;
  const std::string kName = "empty.dat";

  EXPECT_CALL(env, NewSequentialFile(kName, _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Read(_, _, _))
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        *out = Slice("", 0);  // EOF immediately
        return Status::OK();
      }));

  std::string data = "will be cleared then stay empty";
  Status s = ReadFileToString(&env, kName, &data);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data, "");
}

// --- Multiple small fragments: accumulates all then stops at EOF ---
TEST_F(ReadFileToStringTest_471, AccumulatesMultipleFragmentsUntilEof_471) {
  MockEnv env;
  auto* mock_file = new MockSequentialFile;
  const std::string kName = "tiny_chunks.dat";

  EXPECT_CALL(env, NewSequentialFile(kName, _))
      .WillOnce(DoAll(SetArgPointee<1>(mock_file), Return(Status::OK())));

  EXPECT_CALL(*mock_file, Read(_, _, _))
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        static const char* c1 = "a";
        *out = Slice(c1, 1);
        return Status::OK();
      }))
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        static const char* c2 = "b";
        *out = Slice(c2, 1);
        return Status::OK();
      }))
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        static const char* c3 = "c";
        *out = Slice(c3, 1);
        return Status::OK();
      }))
      .WillOnce(Invoke([](size_t, Slice* out, char*) {
        *out = Slice("", 0);  // EOF
        return Status::OK();
      }));

  std::string data;
  Status s = ReadFileToString(&env, kName, &data);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(data, "abc");
}

}  // namespace leveldb

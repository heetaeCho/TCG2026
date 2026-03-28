#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Include the struct definition
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Declare the function under test
extern "C" {
const char* leveldb_iter_key(const leveldb_iterator_t* iter, size_t* klen);
}

// Since leveldb_iter_key is defined in c.cc, we need to provide the definition here
// or link against it. For testing purposes, we include the implementation:
const char* leveldb_iter_key(const leveldb_iterator_t* iter, size_t* klen) {
  leveldb::Slice s = iter->rep->key();
  *klen = s.size();
  return s.data();
}

// Mock Iterator to control behavior
class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(leveldb::Slice, key, (), (const, override));
  MOCK_METHOD(leveldb::Slice, value, (), (const, override));
  MOCK_METHOD(leveldb::Status, status, (), (const, override));
};

class LeveldbIterKeyTest_241 : public ::testing::Test {
 protected:
  MockIterator mock_iter_;
  leveldb_iterator_t iter_;

  void SetUp() override {
    iter_.rep = &mock_iter_;
  }
};

// Test normal operation: key returns a typical string
TEST_F(LeveldbIterKeyTest_241, ReturnsCorrectKeyData_241) {
  std::string key_data = "hello";
  leveldb::Slice key_slice(key_data);
  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(key_slice));

  size_t klen = 0;
  const char* result = leveldb_iter_key(&iter_, &klen);

  EXPECT_EQ(klen, 5u);
  EXPECT_EQ(std::string(result, klen), "hello");
}

// Test normal operation: key returns correct length
TEST_F(LeveldbIterKeyTest_241, ReturnsCorrectKeyLength_241) {
  std::string key_data = "test_key";
  leveldb::Slice key_slice(key_data);
  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(key_slice));

  size_t klen = 0;
  const char* result = leveldb_iter_key(&iter_, &klen);

  EXPECT_EQ(klen, 8u);
  EXPECT_EQ(std::string(result, klen), "test_key");
}

// Test boundary condition: empty key
TEST_F(LeveldbIterKeyTest_241, EmptyKeyReturnsZeroLength_241) {
  leveldb::Slice empty_slice("", 0);
  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(empty_slice));

  size_t klen = 999;
  const char* result = leveldb_iter_key(&iter_, &klen);

  EXPECT_EQ(klen, 0u);
  EXPECT_NE(result, nullptr);
}

// Test boundary condition: single character key
TEST_F(LeveldbIterKeyTest_241, SingleCharKey_241) {
  std::string key_data = "x";
  leveldb::Slice key_slice(key_data);
  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(key_slice));

  size_t klen = 0;
  const char* result = leveldb_iter_key(&iter_, &klen);

  EXPECT_EQ(klen, 1u);
  EXPECT_EQ(result[0], 'x');
}

// Test that key with embedded null bytes returns correct length
TEST_F(LeveldbIterKeyTest_241, KeyWithEmbeddedNullBytes_241) {
  std::string key_data("key\0with\0nulls", 14);
  leveldb::Slice key_slice(key_data);
  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(key_slice));

  size_t klen = 0;
  const char* result = leveldb_iter_key(&iter_, &klen);

  EXPECT_EQ(klen, 14u);
  EXPECT_EQ(std::string(result, klen), key_data);
}

// Test that the returned pointer points to the same data as the slice
TEST_F(LeveldbIterKeyTest_241, ReturnedPointerMatchesSliceData_241) {
  const char* raw_key = "raw_pointer_key";
  leveldb::Slice key_slice(raw_key);
  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(key_slice));

  size_t klen = 0;
  const char* result = leveldb_iter_key(&iter_, &klen);

  EXPECT_EQ(result, raw_key);
  EXPECT_EQ(klen, strlen(raw_key));
}

// Test with a long key
TEST_F(LeveldbIterKeyTest_241, LongKey_241) {
  std::string long_key(10000, 'A');
  leveldb::Slice key_slice(long_key);
  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(key_slice));

  size_t klen = 0;
  const char* result = leveldb_iter_key(&iter_, &klen);

  EXPECT_EQ(klen, 10000u);
  EXPECT_EQ(std::string(result, klen), long_key);
}

// Test that key() is called exactly once
TEST_F(LeveldbIterKeyTest_241, KeyCalledExactlyOnce_241) {
  std::string key_data = "once";
  leveldb::Slice key_slice(key_data);
  EXPECT_CALL(mock_iter_, key())
      .Times(1)
      .WillOnce(::testing::Return(key_slice));

  size_t klen = 0;
  leveldb_iter_key(&iter_, &klen);
}

// Test with binary data key
TEST_F(LeveldbIterKeyTest_241, BinaryDataKey_241) {
  char binary_data[] = {0x01, 0x02, 0xFF, 0xFE, 0x00, 0x7F};
  leveldb::Slice key_slice(binary_data, sizeof(binary_data));
  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(key_slice));

  size_t klen = 0;
  const char* result = leveldb_iter_key(&iter_, &klen);

  EXPECT_EQ(klen, sizeof(binary_data));
  EXPECT_EQ(memcmp(result, binary_data, klen), 0);
}

// Test multiple consecutive calls
TEST_F(LeveldbIterKeyTest_241, MultipleConsecutiveCalls_241) {
  std::string key1 = "first";
  std::string key2 = "second";
  leveldb::Slice slice1(key1);
  leveldb::Slice slice2(key2);

  EXPECT_CALL(mock_iter_, key())
      .WillOnce(::testing::Return(slice1))
      .WillOnce(::testing::Return(slice2));

  size_t klen1 = 0, klen2 = 0;
  const char* result1 = leveldb_iter_key(&iter_, &klen1);
  const char* result2 = leveldb_iter_key(&iter_, &klen2);

  EXPECT_EQ(klen1, 5u);
  EXPECT_EQ(std::string(result1, klen1), "first");
  EXPECT_EQ(klen2, 6u);
  EXPECT_EQ(std::string(result2, klen2), "second");
}

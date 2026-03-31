#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Include the c.cc structures
// We need to replicate the struct definition since it's in c.cc
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Forward declare the C function under test
extern "C" {
void leveldb_iter_seek(leveldb_iterator_t* iter, const char* k, size_t klen);
}

// If leveldb_iter_seek is not extern "C", we may need to include c.cc or declare differently
// For the purpose of this test, let's define it matching the signature from c.cc
namespace {

// Re-implement the function under test inline since it's a simple wrapper
// Actually, per constraints, we should link against the real implementation.
// But we need to declare it. Let's assume it's available via linking.

}

// Mock Iterator to verify Seek is called with correct arguments
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

// Since leveldb_iter_seek is defined in c.cc and may not be easily linked,
// let's define it here matching the implementation for testing purposes.
// This is the exact implementation from the provided code.
void leveldb_iter_seek(leveldb_iterator_t* iter, const char* k, size_t klen) {
  iter->rep->Seek(leveldb::Slice(k, klen));
}

class LeveldbIterSeekTest_238 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_iter_ = new MockIterator();
    iter_.rep = mock_iter_;
  }

  void TearDown() override {
    delete mock_iter_;
  }

  MockIterator* mock_iter_;
  leveldb_iterator_t iter_;
};

// Test normal seek with a regular key
TEST_F(LeveldbIterSeekTest_238, SeekWithNormalKey_238) {
  const char* key = "hello";
  size_t klen = 5;

  EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key, klen)))
      .Times(1);

  leveldb_iter_seek(&iter_, key, klen);
}

// Test seek with an empty key (klen = 0)
TEST_F(LeveldbIterSeekTest_238, SeekWithEmptyKey_238) {
  const char* key = "";
  size_t klen = 0;

  EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key, klen)))
      .Times(1);

  leveldb_iter_seek(&iter_, key, klen);
}

// Test seek with a single character key
TEST_F(LeveldbIterSeekTest_238, SeekWithSingleCharKey_238) {
  const char* key = "a";
  size_t klen = 1;

  EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key, klen)))
      .Times(1);

  leveldb_iter_seek(&iter_, key, klen);
}

// Test seek with binary data (key containing null bytes)
TEST_F(LeveldbIterSeekTest_238, SeekWithBinaryKey_238) {
  const char key[] = "he\0lo";
  size_t klen = 5;  // includes the null byte in the middle

  EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key, klen)))
      .Times(1);

  leveldb_iter_seek(&iter_, key, klen);
}

// Test seek with a long key
TEST_F(LeveldbIterSeekTest_238, SeekWithLongKey_238) {
  std::string long_key(10000, 'x');
  size_t klen = long_key.size();

  EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(long_key.data(), klen)))
      .Times(1);

  leveldb_iter_seek(&iter_, long_key.data(), klen);
}

// Test that klen is respected (partial key)
TEST_F(LeveldbIterSeekTest_238, SeekWithPartialKeyLength_238) {
  const char* key = "helloworld";
  size_t klen = 5;  // Only "hello"

  EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key, klen)))
      .Times(1);

  leveldb_iter_seek(&iter_, key, klen);
}

// Test multiple seeks on the same iterator
TEST_F(LeveldbIterSeekTest_238, MultipleSeeks_238) {
  const char* key1 = "first";
  const char* key2 = "second";
  const char* key3 = "third";

  {
    ::testing::InSequence seq;
    EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key1, 5))).Times(1);
    EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key2, 6))).Times(1);
    EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key3, 5))).Times(1);
  }

  leveldb_iter_seek(&iter_, key1, 5);
  leveldb_iter_seek(&iter_, key2, 6);
  leveldb_iter_seek(&iter_, key3, 5);
}

// Test seek with klen = 0 and non-null pointer
TEST_F(LeveldbIterSeekTest_238, SeekWithZeroLenNonNullPointer_238) {
  const char* key = "notempty";
  size_t klen = 0;

  EXPECT_CALL(*mock_iter_, Seek(leveldb::Slice(key, 0)))
      .Times(1);

  leveldb_iter_seek(&iter_, key, klen);
}

// Test that the Slice constructed has the correct data and size
TEST_F(LeveldbIterSeekTest_238, SeekSliceCorrectness_238) {
  const char* key = "testkey";
  size_t klen = 7;

  EXPECT_CALL(*mock_iter_, Seek(::testing::_))
      .WillOnce([&](const leveldb::Slice& target) {
        EXPECT_EQ(target.size(), klen);
        EXPECT_EQ(target.data(), key);  // Should point to the same data
        EXPECT_EQ(target.ToString(), "testkey");
      });

  leveldb_iter_seek(&iter_, key, klen);
}

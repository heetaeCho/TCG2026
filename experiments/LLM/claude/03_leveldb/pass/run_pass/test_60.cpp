#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test fixture for LookupKey tests
class LookupKeyTest_60 : public ::testing::Test {
 protected:
};

// Test basic construction with a simple key and sequence number
TEST_F(LookupKeyTest_60, BasicConstruction_60) {
  LookupKey key(Slice("hello"), 100);
  // Key should be constructible without error
  Slice memtable = key.memtable_key();
  Slice internal = key.internal_key();
  Slice user = key.user_key();
  
  // user_key should return the original user key
  EXPECT_EQ(user.ToString(), "hello");
}

// Test that user_key returns the correct key for various inputs
TEST_F(LookupKeyTest_60, UserKeyReturnsCorrectValue_60) {
  LookupKey key(Slice("testkey"), 500);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), "testkey");
}

// Test with sequence number 0
TEST_F(LookupKeyTest_60, SequenceNumberZero_60) {
  LookupKey key(Slice("abc"), 0);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), "abc");
}

// Test with maximum sequence number
TEST_F(LookupKeyTest_60, MaxSequenceNumber_60) {
  // Max sequence number is (1 << 56) - 1 based on leveldb's format
  SequenceNumber max_seq = (static_cast<uint64_t>(1) << 56) - 1;
  LookupKey key(Slice("maxseq"), max_seq);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), "maxseq");
}

// Test with an empty key
TEST_F(LookupKeyTest_60, EmptyKey_60) {
  LookupKey key(Slice(""), 42);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), "");
}

// Test with a single character key
TEST_F(LookupKeyTest_60, SingleCharKey_60) {
  LookupKey key(Slice("x"), 1);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), "x");
}

// Test that internal_key contains the user key
TEST_F(LookupKeyTest_60, InternalKeyContainsUserKey_60) {
  LookupKey key(Slice("mykey"), 100);
  Slice internal = key.internal_key();
  Slice user = key.user_key();
  
  // internal_key should be user_key + 8 bytes (sequence + type tag)
  EXPECT_EQ(internal.size(), user.size() + 8);
  // The first part of internal key should match user key
  EXPECT_EQ(Slice(internal.data(), user.size()).ToString(), "mykey");
}

// Test that memtable_key is larger than internal_key (has length prefix)
TEST_F(LookupKeyTest_60, MemtableKeyLargerThanInternalKey_60) {
  LookupKey key(Slice("mykey"), 100);
  Slice memtable = key.memtable_key();
  Slice internal = key.internal_key();
  
  // memtable_key should be longer because it includes a varint length prefix
  EXPECT_GT(memtable.size(), internal.size());
}

// Test with a large key that exceeds the internal space_ buffer (200 bytes)
TEST_F(LookupKeyTest_60, LargeKeyExceedsInternalBuffer_60) {
  // Create a key larger than 200 bytes to force heap allocation
  std::string large_key(300, 'A');
  LookupKey key(Slice(large_key), 999);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), large_key);
}

// Test with a key exactly at the boundary of the internal buffer
TEST_F(LookupKeyTest_60, KeyAtBufferBoundary_60) {
  // space_ is 200 bytes, need room for varint length + key + 8 bytes tag
  // A key of ~190 bytes should be close to the boundary
  std::string boundary_key(185, 'B');
  LookupKey key(Slice(boundary_key), 50);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), boundary_key);
}

// Test with key containing binary data (null bytes)
TEST_F(LookupKeyTest_60, KeyWithBinaryData_60) {
  std::string binary_key("he\0llo", 6);
  LookupKey key(Slice(binary_key), 77);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), binary_key);
  EXPECT_EQ(user.size(), 6);
}

// Test that internal_key size is always user_key size + 8
TEST_F(LookupKeyTest_60, InternalKeySizeRelation_60) {
  std::string test_key("relation_test");
  LookupKey key(Slice(test_key), 12345);
  Slice internal = key.internal_key();
  Slice user = key.user_key();
  EXPECT_EQ(internal.size(), user.size() + 8);
}

// Test multiple LookupKey objects can coexist
TEST_F(LookupKeyTest_60, MultipleLookupKeys_60) {
  LookupKey key1(Slice("first"), 1);
  LookupKey key2(Slice("second"), 2);
  LookupKey key3(Slice("third"), 3);
  
  EXPECT_EQ(key1.user_key().ToString(), "first");
  EXPECT_EQ(key2.user_key().ToString(), "second");
  EXPECT_EQ(key3.user_key().ToString(), "third");
}

// Test with sequence number 1
TEST_F(LookupKeyTest_60, SequenceNumberOne_60) {
  LookupKey key(Slice("seq1"), 1);
  Slice user = key.user_key();
  EXPECT_EQ(user.ToString(), "seq1");
}

// Test destruction doesn't crash for small key (uses space_)
TEST_F(LookupKeyTest_60, DestructionSmallKey_60) {
  {
    LookupKey key(Slice("small"), 10);
    EXPECT_EQ(key.user_key().ToString(), "small");
  }
  // If we get here, destruction was successful
}

// Test destruction doesn't crash for large key (uses heap)
TEST_F(LookupKeyTest_60, DestructionLargeKey_60) {
  {
    std::string large_key(500, 'Z');
    LookupKey key(Slice(large_key), 10);
    EXPECT_EQ(key.user_key().ToString(), large_key);
  }
  // If we get here, destruction was successful
}

}  // namespace leveldb

#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

class LookupKeyTest_58 : public ::testing::Test {
 protected:
};

// Test that LookupKey can be constructed with a simple user key and sequence number
TEST_F(LookupKeyTest_58, ConstructWithSimpleKey_58) {
  Slice user_key("hello");
  SequenceNumber seq = 100;
  LookupKey key(user_key, seq);

  // internal_key should not be empty
  Slice ik = key.internal_key();
  EXPECT_GT(ik.size(), 0u);
}

// Test that internal_key contains the user key as a prefix
TEST_F(LookupKeyTest_58, InternalKeyContainsUserKey_58) {
  Slice user_key("testkey");
  SequenceNumber seq = 500;
  LookupKey key(user_key, seq);

  Slice ik = key.internal_key();
  // internal_key = user_key + 8 bytes (sequence number + type packed)
  EXPECT_EQ(ik.size(), user_key.size() + 8);
  // The first part of internal_key should be the user key
  EXPECT_EQ(Slice(ik.data(), user_key.size()).ToString(), user_key.ToString());
}

// Test that user_key returns the original user key
TEST_F(LookupKeyTest_58, UserKeyReturnsOriginal_58) {
  Slice user_key("mykey");
  SequenceNumber seq = 42;
  LookupKey key(user_key, seq);

  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), "mykey");
}

// Test that memtable_key includes the length prefix before internal_key
TEST_F(LookupKeyTest_58, MemtableKeyIncludesLengthPrefix_58) {
  Slice user_key("abc");
  SequenceNumber seq = 1;
  LookupKey key(user_key, seq);

  Slice mk = key.memtable_key();
  Slice ik = key.internal_key();
  // memtable_key should be longer than internal_key (has varint length prefix)
  EXPECT_GT(mk.size(), ik.size());
}

// Test with empty user key
TEST_F(LookupKeyTest_58, EmptyUserKey_58) {
  Slice user_key("");
  SequenceNumber seq = 0;
  LookupKey key(user_key, seq);

  Slice ik = key.internal_key();
  // internal_key should be 8 bytes (just the tag, no user key bytes)
  EXPECT_EQ(ik.size(), 8u);

  Slice uk = key.user_key();
  EXPECT_EQ(uk.size(), 0u);
  EXPECT_EQ(uk.ToString(), "");
}

// Test with maximum sequence number
TEST_F(LookupKeyTest_58, MaxSequenceNumber_58) {
  Slice user_key("key");
  SequenceNumber seq = (1ull << 56) - 1;  // max valid sequence number
  LookupKey key(user_key, seq);

  Slice ik = key.internal_key();
  EXPECT_EQ(ik.size(), user_key.size() + 8);

  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), "key");
}

// Test with sequence number 0
TEST_F(LookupKeyTest_58, ZeroSequenceNumber_58) {
  Slice user_key("zerokey");
  SequenceNumber seq = 0;
  LookupKey key(user_key, seq);

  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), "zerokey");

  Slice ik = key.internal_key();
  EXPECT_EQ(ik.size(), 7u + 8u);
}

// Test with a long user key (exceeding the internal space_ buffer of 200 bytes)
TEST_F(LookupKeyTest_58, LongUserKey_58) {
  std::string long_key(300, 'x');
  Slice user_key(long_key);
  SequenceNumber seq = 12345;
  LookupKey key(user_key, seq);

  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), long_key);

  Slice ik = key.internal_key();
  EXPECT_EQ(ik.size(), long_key.size() + 8);
}

// Test that different sequence numbers produce different internal keys
TEST_F(LookupKeyTest_58, DifferentSequencesProduceDifferentInternalKeys_58) {
  Slice user_key("samekey");
  LookupKey key1(user_key, 100);
  LookupKey key2(user_key, 200);

  Slice ik1 = key1.internal_key();
  Slice ik2 = key2.internal_key();

  EXPECT_EQ(ik1.size(), ik2.size());
  EXPECT_NE(ik1.ToString(), ik2.ToString());
}

// Test that different user keys produce different internal keys
TEST_F(LookupKeyTest_58, DifferentUserKeysProduceDifferentInternalKeys_58) {
  SequenceNumber seq = 50;
  LookupKey key1(Slice("alpha"), seq);
  LookupKey key2(Slice("beta"), seq);

  Slice ik1 = key1.internal_key();
  Slice ik2 = key2.internal_key();

  EXPECT_NE(ik1.ToString(), ik2.ToString());
}

// Test with a key exactly at the space_ buffer boundary (~200 bytes)
TEST_F(LookupKeyTest_58, KeyAtBufferBoundary_58) {
  // space_ is 200 bytes. The memtable key includes varint length prefix + user_key + 8 bytes tag
  // For a key of size ~190, total should be around 190 + 8 + varint(~2) = 200
  std::string boundary_key(190, 'b');
  Slice user_key(boundary_key);
  SequenceNumber seq = 999;
  LookupKey key(user_key, seq);

  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), boundary_key);

  Slice ik = key.internal_key();
  EXPECT_EQ(ik.size(), boundary_key.size() + 8);
}

// Test with single character user key
TEST_F(LookupKeyTest_58, SingleCharUserKey_58) {
  Slice user_key("a");
  SequenceNumber seq = 1;
  LookupKey key(user_key, seq);

  Slice uk = key.user_key();
  EXPECT_EQ(uk.ToString(), "a");
  EXPECT_EQ(uk.size(), 1u);

  Slice ik = key.internal_key();
  EXPECT_EQ(ik.size(), 9u);  // 1 + 8
}

// Test consistency: calling internal_key multiple times returns the same result
TEST_F(LookupKeyTest_58, InternalKeyConsistency_58) {
  Slice user_key("consistent");
  SequenceNumber seq = 777;
  LookupKey key(user_key, seq);

  Slice ik1 = key.internal_key();
  Slice ik2 = key.internal_key();

  EXPECT_EQ(ik1.ToString(), ik2.ToString());
  EXPECT_EQ(ik1.data(), ik2.data());
  EXPECT_EQ(ik1.size(), ik2.size());
}

// Test consistency: calling user_key multiple times returns the same result
TEST_F(LookupKeyTest_58, UserKeyConsistency_58) {
  Slice user_key("stable");
  SequenceNumber seq = 10;
  LookupKey key(user_key, seq);

  Slice uk1 = key.user_key();
  Slice uk2 = key.user_key();

  EXPECT_EQ(uk1.ToString(), uk2.ToString());
}

// Test consistency: calling memtable_key multiple times returns the same result
TEST_F(LookupKeyTest_58, MemtableKeyConsistency_58) {
  Slice user_key("memtest");
  SequenceNumber seq = 55;
  LookupKey key(user_key, seq);

  Slice mk1 = key.memtable_key();
  Slice mk2 = key.memtable_key();

  EXPECT_EQ(mk1.ToString(), mk2.ToString());
  EXPECT_EQ(mk1.data(), mk2.data());
}

// Test with binary data in user key
TEST_F(LookupKeyTest_58, BinaryUserKey_58) {
  std::string binary_key;
  binary_key.push_back('\0');
  binary_key.push_back('\x01');
  binary_key.push_back('\xff');
  binary_key.push_back('\x80');

  Slice user_key(binary_key);
  SequenceNumber seq = 100;
  LookupKey key(user_key, seq);

  Slice uk = key.user_key();
  EXPECT_EQ(uk.size(), 4u);
  EXPECT_EQ(uk.ToString(), binary_key);

  Slice ik = key.internal_key();
  EXPECT_EQ(ik.size(), 12u);  // 4 + 8
}

}  // namespace leveldb

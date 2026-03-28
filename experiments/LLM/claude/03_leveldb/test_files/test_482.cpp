#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include <string>
#include <cstring>

namespace leveldb {

// Helper to decode varint32 from a buffer
static const char* DecodeVarint32(const char* p, const char* limit, uint32_t* value) {
  if (p < limit) {
    uint32_t result = *(reinterpret_cast<const uint8_t*>(p));
    if ((result & 128) == 0) {
      *value = result;
      return p + 1;
    }
  }
  // Multi-byte varint decoding
  uint32_t result = 0;
  for (uint32_t shift = 0; shift <= 28 && p < limit; shift += 7) {
    uint32_t byte = *(reinterpret_cast<const uint8_t*>(p));
    p++;
    if (byte & 128) {
      result |= ((byte & 127) << shift);
    } else {
      result |= (byte << shift);
      *value = result;
      return p;
    }
  }
  return nullptr;
}

static uint64_t DecodeFixed64(const char* ptr) {
  uint64_t result = 0;
  std::memcpy(&result, ptr, sizeof(result));
  return result;
}

class LookupKeyTest_482 : public ::testing::Test {
 protected:
};

// Test basic construction with a simple key
TEST_F(LookupKeyTest_482, BasicConstruction_482) {
  std::string key = "hello";
  SequenceNumber seq = 100;
  LookupKey lookup(key, seq);

  // Verify that the returned slices are non-empty
  Slice memtable = lookup.memtable_key();
  Slice internal = lookup.internal_key();
  Slice user = lookup.user_key();

  EXPECT_FALSE(memtable.empty());
  EXPECT_FALSE(internal.empty());
  EXPECT_FALSE(user.empty());
}

// Test that user_key() returns the original user key
TEST_F(LookupKeyTest_482, UserKeyMatchesInput_482) {
  std::string key = "testkey";
  SequenceNumber seq = 42;
  LookupKey lookup(key, seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.ToString(), key);
}

// Test that internal_key() has the right size (user_key + 8 bytes for seq+type)
TEST_F(LookupKeyTest_482, InternalKeySize_482) {
  std::string key = "mykey";
  SequenceNumber seq = 500;
  LookupKey lookup(key, seq);

  Slice internal = lookup.internal_key();
  EXPECT_EQ(internal.size(), key.size() + 8);
}

// Test that internal_key starts with the user key
TEST_F(LookupKeyTest_482, InternalKeyStartsWithUserKey_482) {
  std::string key = "prefix";
  SequenceNumber seq = 1;
  LookupKey lookup(key, seq);

  Slice internal = lookup.internal_key();
  EXPECT_TRUE(internal.starts_with(Slice(key)));
}

// Test that memtable_key() includes the varint length prefix + internal key
TEST_F(LookupKeyTest_482, MemtableKeyIncludesLengthPrefix_482) {
  std::string key = "abcdef";
  SequenceNumber seq = 200;
  LookupKey lookup(key, seq);

  Slice memtable = lookup.memtable_key();
  Slice internal = lookup.internal_key();

  // memtable_key should be larger than internal_key (has varint prefix)
  EXPECT_GT(memtable.size(), internal.size());

  // Decode the varint32 from the memtable key
  uint32_t decoded_len = 0;
  const char* p = DecodeVarint32(memtable.data(), memtable.data() + memtable.size(), &decoded_len);
  ASSERT_NE(p, nullptr);

  // The decoded length should be user_key.size() + 8
  EXPECT_EQ(decoded_len, key.size() + 8);
}

// Test with empty user key
TEST_F(LookupKeyTest_482, EmptyUserKey_482) {
  std::string key = "";
  SequenceNumber seq = 0;
  LookupKey lookup(key, seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.size(), 0u);
  EXPECT_EQ(user.ToString(), "");

  Slice internal = lookup.internal_key();
  EXPECT_EQ(internal.size(), 8u);  // Just the 8-byte trailer
}

// Test with sequence number 0
TEST_F(LookupKeyTest_482, SequenceNumberZero_482) {
  std::string key = "key";
  SequenceNumber seq = 0;
  LookupKey lookup(key, seq);

  Slice internal = lookup.internal_key();
  EXPECT_EQ(internal.size(), key.size() + 8);

  // The last 8 bytes should encode (seq << 8) | kValueTypeForSeek
  uint64_t tag = DecodeFixed64(internal.data() + key.size());
  // kValueTypeForSeek is kTypeValue which is 1
  EXPECT_EQ(tag, (static_cast<uint64_t>(0) << 8) | 1);
}

// Test with maximum sequence number
TEST_F(LookupKeyTest_482, MaxSequenceNumber_482) {
  std::string key = "maxseq";
  // Max sequence number is (1 << 56) - 1 since sequence is 56 bits
  SequenceNumber seq = (static_cast<uint64_t>(1) << 56) - 1;
  LookupKey lookup(key, seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.ToString(), key);

  Slice internal = lookup.internal_key();
  uint64_t tag = DecodeFixed64(internal.data() + key.size());
  uint64_t expected = (seq << 8) | static_cast<uint64_t>(kValueTypeForSeek);
  EXPECT_EQ(tag, expected);
}

// Test with a key that's small enough to use the stack-allocated space_
TEST_F(LookupKeyTest_482, SmallKeyUsesStackBuffer_482) {
  // space_ is 200 bytes, needed = usize + 13, so usize <= 187 uses stack
  std::string key(100, 'x');
  SequenceNumber seq = 12345;
  LookupKey lookup(key, seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.ToString(), key);
  EXPECT_EQ(user.size(), 100u);
}

// Test with a key that's large enough to require heap allocation
TEST_F(LookupKeyTest_482, LargeKeyUsesHeapAllocation_482) {
  // space_ is 200 bytes, needed = usize + 13, so usize > 187 uses heap
  std::string key(300, 'y');
  SequenceNumber seq = 99999;
  LookupKey lookup(key, seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.ToString(), key);
  EXPECT_EQ(user.size(), 300u);

  Slice internal = lookup.internal_key();
  EXPECT_EQ(internal.size(), 300u + 8u);
}

// Test boundary: key size exactly at the threshold
TEST_F(LookupKeyTest_482, BoundaryKeySize_482) {
  // needed = usize + 13 <= 200 => usize <= 187
  std::string key(187, 'z');
  SequenceNumber seq = 1;
  LookupKey lookup(key, seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.ToString(), key);

  // Now test usize = 188, which needs 201 > 200, so heap
  std::string key2(188, 'w');
  LookupKey lookup2(key2, seq);

  Slice user2 = lookup2.user_key();
  EXPECT_EQ(user2.ToString(), key2);
}

// Test with single character key
TEST_F(LookupKeyTest_482, SingleCharKey_482) {
  std::string key = "a";
  SequenceNumber seq = 7;
  LookupKey lookup(key, seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.ToString(), "a");
  EXPECT_EQ(user.size(), 1u);
}

// Test with binary data in key
TEST_F(LookupKeyTest_482, BinaryDataInKey_482) {
  std::string key;
  key.push_back('\0');
  key.push_back('\x01');
  key.push_back('\xff');
  key.push_back('\x80');
  SequenceNumber seq = 50;
  LookupKey lookup(Slice(key), seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.size(), 4u);
  EXPECT_EQ(user.ToString(), key);
}

// Test that the sequence and type are properly packed in the internal key trailer
TEST_F(LookupKeyTest_482, SequenceAndTypePacking_482) {
  std::string key = "seqtest";
  SequenceNumber seq = 12345678;
  LookupKey lookup(key, seq);

  Slice internal = lookup.internal_key();
  uint64_t tag = DecodeFixed64(internal.data() + key.size());

  // PackSequenceAndType packs as (seq << 8) | type
  // kValueTypeForSeek = kTypeValue = 1
  uint64_t expected = (static_cast<uint64_t>(seq) << 8) | 1;
  EXPECT_EQ(tag, expected);
}

// Test relationship between memtable_key, internal_key, and user_key
TEST_F(LookupKeyTest_482, KeyRelationships_482) {
  std::string key = "reltest";
  SequenceNumber seq = 999;
  LookupKey lookup(key, seq);

  Slice memtable = lookup.memtable_key();
  Slice internal = lookup.internal_key();
  Slice user = lookup.user_key();

  // user_key should be a prefix of internal_key
  EXPECT_TRUE(internal.starts_with(user));

  // internal_key = user_key + 8 byte tag
  EXPECT_EQ(internal.size(), user.size() + 8);

  // memtable_key should end at the same point as internal_key
  // memtable starts with varint, then internal_key
  // So memtable.data() + (memtable.size() - internal.size()) should point to internal.data()
  EXPECT_EQ(memtable.data() + memtable.size(), internal.data() + internal.size());
}

// Test with Slice constructed from const char*
TEST_F(LookupKeyTest_482, SliceFromCharPointer_482) {
  const char* key = "charptr";
  SequenceNumber seq = 77;
  LookupKey lookup(Slice(key), seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.ToString(), "charptr");
}

// Test with a very large key to ensure heap allocation works correctly
TEST_F(LookupKeyTest_482, VeryLargeKey_482) {
  std::string key(10000, 'A');
  SequenceNumber seq = 1000000;
  LookupKey lookup(key, seq);

  Slice user = lookup.user_key();
  EXPECT_EQ(user.size(), 10000u);
  EXPECT_EQ(user.ToString(), key);

  Slice internal = lookup.internal_key();
  EXPECT_EQ(internal.size(), 10008u);
}

}  // namespace leveldb

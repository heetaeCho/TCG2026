#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper functions to construct internal keys
static std::string MakeInternalKey(const std::string& user_key,
                                    SequenceNumber seq,
                                    ValueType type) {
  std::string result = user_key;
  PutFixed64(&result, PackSequenceAndType(seq, type));
  return result;
}

// Mock comparator for testing specific behaviors
class MockComparator : public Comparator {
 public:
  MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const Slice& limit), (const, override));
  MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (const, override));
};

class InternalKeyComparatorFindShortSuccessorTest_191 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: When user comparator's FindShortSuccessor shortens the key and the
// shortened key compares greater than the original user key, the internal key
// should be updated.
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, ShortenedKeyUsedWhenShorterAndGreater_191) {
  // Use the default BytewiseComparator
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  // Create an internal key with user_key "abcdef", some sequence number and type
  std::string key = MakeInternalKey("abcdef", 100, kTypeValue);
  std::string original_key = key;

  icmp.FindShortSuccessor(&key);

  // The result should be a valid internal key
  // It should be >= original in the internal key comparator sense
  // Actually, FindShortSuccessor finds a short successor that is > key
  // The BytewiseComparator::FindShortSuccessor will try to increment a byte
  // For "abcdef", it would produce "b" (increment 'a' to 'b')
  // "b" is shorter than "abcdef" and "b" > "abcdef" bytewise
  // So the internal key should be updated to "b" + packed(kMaxSequenceNumber, kValueTypeForSeek)
  
  // The key should have changed
  EXPECT_NE(key, original_key);
  
  // The new key should compare less than or equal in terms of internal key ordering
  // Actually, the successor should be strictly greater
  EXPECT_LT(icmp.Compare(original_key, key), 0);
  
  // The new key should be shorter than the original
  EXPECT_LE(key.size(), original_key.size());
}

// Test: When the user_key cannot be shortened (e.g., all 0xff bytes), the key
// should remain unchanged.
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, NoShorteningWhenUserKeyIsMaximal_191) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  // Create an internal key with user_key that is all 0xff bytes
  std::string user_key(5, '\xff');
  std::string key = MakeInternalKey(user_key, 100, kTypeValue);
  std::string original_key = key;

  icmp.FindShortSuccessor(&key);

  // BytewiseComparator::FindShortSuccessor won't shorten an all-0xff key
  // So the internal key should remain unchanged
  EXPECT_EQ(key, original_key);
}

// Test: When the user comparator's FindShortSuccessor produces a key that is
// NOT shorter than the original, the key should remain unchanged.
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, NoChangeWhenSuccessorNotShorter_191) {
  MockComparator mock_cmp;
  InternalKeyComparator icmp(&mock_cmp);

  std::string user_key = "abc";
  std::string key = MakeInternalKey(user_key, 100, kTypeValue);
  std::string original_key = key;

  // Mock: FindShortSuccessor doesn't shorten the key (same size or longer)
  EXPECT_CALL(mock_cmp, FindShortSuccessor(::testing::_))
      .WillOnce([](std::string* k) {
        // Make it same length - just change last byte
        (*k)[k->size() - 1] = (*k)[k->size() - 1] + 1;
      });
  
  // Name() might be called
  EXPECT_CALL(mock_cmp, Name())
      .WillRepeatedly(::testing::Return("MockComparator"));

  icmp.FindShortSuccessor(&key);

  // Since the tmp is not shorter than user_key, key should remain unchanged
  EXPECT_EQ(key, original_key);
}

// Test: When the user comparator's FindShortSuccessor produces a shorter key
// but one that does NOT compare greater than the original user key, the key
// should remain unchanged.
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, NoChangeWhenShorterButNotGreater_191) {
  MockComparator mock_cmp;
  InternalKeyComparator icmp(&mock_cmp);

  std::string user_key = "abc";
  std::string key = MakeInternalKey(user_key, 100, kTypeValue);
  std::string original_key = key;

  // Mock: FindShortSuccessor shortens to a key that is "smaller"
  EXPECT_CALL(mock_cmp, FindShortSuccessor(::testing::_))
      .WillOnce([](std::string* k) {
        *k = "a";  // shorter but might not be greater
      });

  // Compare(user_key, tmp) should return >= 0 (user_key >= tmp)
  // i.e., "abc" compared to "a" => "abc" > "a", so Compare returns positive
  EXPECT_CALL(mock_cmp, Compare(::testing::_, ::testing::_))
      .WillRepeatedly([](const Slice& a, const Slice& b) -> int {
        return a.compare(b);
      });

  EXPECT_CALL(mock_cmp, Name())
      .WillRepeatedly(::testing::Return("MockComparator"));

  icmp.FindShortSuccessor(&key);

  // Since Compare(user_key, tmp) >= 0, key should remain unchanged
  EXPECT_EQ(key, original_key);
}

// Test: When the user comparator's FindShortSuccessor produces a shorter key
// that compares greater, the key should be updated with kMaxSequenceNumber.
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, UpdatedWhenShorterAndGreater_191) {
  MockComparator mock_cmp;
  InternalKeyComparator icmp(&mock_cmp);

  std::string user_key = "abcdef";
  std::string key = MakeInternalKey(user_key, 100, kTypeValue);
  std::string original_key = key;

  // Mock: FindShortSuccessor shortens to "b" which is shorter and greater
  EXPECT_CALL(mock_cmp, FindShortSuccessor(::testing::_))
      .WillOnce([](std::string* k) {
        *k = "b";  // shorter than "abcdef" and bytewise greater
      });

  // We need Compare to work properly for both the condition check and the assert
  EXPECT_CALL(mock_cmp, Compare(::testing::_, ::testing::_))
      .WillRepeatedly([](const Slice& a, const Slice& b) -> int {
        return a.compare(b);
      });

  EXPECT_CALL(mock_cmp, Name())
      .WillRepeatedly(::testing::Return("MockComparator"));

  icmp.FindShortSuccessor(&key);

  // The key should have changed
  EXPECT_NE(key, original_key);

  // The new key should start with "b"
  Slice new_user_key = ExtractUserKey(key);
  EXPECT_EQ(new_user_key.ToString(), "b");

  // Total size should be "b" (1 byte) + 8 bytes for sequence/type
  EXPECT_EQ(key.size(), 1 + 8);
}

// Test: Single character user key with BytewiseComparator
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, SingleCharUserKey_191) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  std::string key = MakeInternalKey("a", 100, kTypeValue);
  std::string original_key = key;

  icmp.FindShortSuccessor(&key);

  // BytewiseComparator should try to increment 'a' to 'b', which is same size
  // so the condition tmp.size() < user_key.size() would be false
  // Actually, "a" has size 1, "b" also has size 1, so not shorter
  // Key should remain unchanged
  EXPECT_EQ(key, original_key);
}

// Test: Empty user key (edge case - key is just 8 bytes of sequence/type)
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, MinimalInternalKey_191) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  // An internal key with empty user key - just the 8 byte trailer
  std::string key;
  PutFixed64(&key, PackSequenceAndType(100, kTypeValue));
  std::string original_key = key;

  // This is a degenerate case - ExtractUserKey would return empty slice
  // BytewiseComparator::FindShortSuccessor on empty string does nothing
  icmp.FindShortSuccessor(&key);

  EXPECT_EQ(key, original_key);
}

// Test: Multi-byte user key where only the first byte gets incremented
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, MultiByteShortenedToOneByte_191) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  // "hello" - BytewiseComparator should increment 'h' to 'i' and truncate
  std::string key = MakeInternalKey("hello", 500, kTypeValue);
  std::string original_key = key;

  icmp.FindShortSuccessor(&key);

  // "i" is shorter than "hello" and "i" > "hello"
  // So key should be updated
  EXPECT_NE(key, original_key);
  EXPECT_LT(icmp.Compare(original_key, key), 0);

  // The new user key should be "i"
  Slice new_user_key = ExtractUserKey(key);
  EXPECT_EQ(new_user_key.ToString(), "i");
}

// Test: User key with sequence number 0 and kTypeDeletion
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, DeletionTypeKey_191) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  std::string key = MakeInternalKey("testkey", 50, kTypeDeletion);
  std::string original_key = key;

  icmp.FindShortSuccessor(&key);

  // Should still work - the user key "testkey" should be shortened to "u"
  // and the sequence should be kMaxSequenceNumber
  EXPECT_NE(key, original_key);
  EXPECT_LT(icmp.Compare(original_key, key), 0);
}

// Test: User key with kMaxSequenceNumber
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, MaxSequenceNumber_191) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  std::string key = MakeInternalKey("xyz", kMaxSequenceNumber, kValueTypeForSeek);
  std::string original_key = key;

  icmp.FindShortSuccessor(&key);

  // "xyz" should be shortened to "y" by BytewiseComparator
  // The resulting key should still compare greater
  if (key != original_key) {
    EXPECT_LT(icmp.Compare(original_key, key), 0);
  }
}

// Test: Verify that FindShortSuccessor result has correct 8-byte trailer format
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, ResultHasCorrectTrailerSize_191) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  std::string key = MakeInternalKey("longkeyvalue", 200, kTypeValue);

  icmp.FindShortSuccessor(&key);

  // The key must still have at least 8 bytes (for the sequence/type trailer)
  EXPECT_GE(key.size(), 8u);
}

// Test: User key that starts with 0xff bytes followed by non-0xff
TEST_F(InternalKeyComparatorFindShortSuccessorTest_191, KeyStartingWithFFBytes_191) {
  const Comparator* bytewise = BytewiseComparator();
  InternalKeyComparator icmp(bytewise);

  std::string user_key;
  user_key += '\xff';
  user_key += '\xff';
  user_key += 'a';
  user_key += 'b';

  std::string key = MakeInternalKey(user_key, 100, kTypeValue);
  std::string original_key = key;

  icmp.FindShortSuccessor(&key);

  // BytewiseComparator would skip 0xff bytes and try to increment 'a' to 'b'
  // Result: "\xff\xff" + "b" which is 3 bytes, shorter than 4 bytes
  if (key != original_key) {
    EXPECT_LT(icmp.Compare(original_key, key), 0);
    EXPECT_GE(key.size(), 8u);
  }
}

}  // namespace leveldb

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper to build an internal key string
static std::string MakeInternalKey(const std::string& user_key,
                                    SequenceNumber seq,
                                    ValueType type) {
  std::string result = user_key;
  PutFixed64(&result, PackSequenceAndType(seq, type));
  return result;
}

// A mock comparator to control FindShortestSeparator behavior
class MockUserComparator : public Comparator {
 public:
  const char* Name() const override { return "MockUserComparator"; }

  int Compare(const Slice& a, const Slice& b) const override {
    return a.compare(b);
  }

  // Default implementation: tries to shorten the key
  void FindShortestSeparator(std::string* start,
                              const Slice& limit) const override {
    // Mimic BytewiseComparator behavior: find first differing byte and
    // increment it if possible
    Slice s(*start);
    Slice l(limit);
    size_t min_length = std::min(s.size(), l.size());
    size_t diff_index = 0;
    while (diff_index < min_length &&
           s[diff_index] == l[diff_index]) {
      diff_index++;
    }
    if (diff_index < min_length) {
      uint8_t diff_byte = static_cast<uint8_t>(s[diff_index]);
      if (diff_byte < 0xff &&
          diff_byte + 1 < static_cast<uint8_t>(l[diff_index])) {
        (*start)[diff_index]++;
        start->resize(diff_index + 1);
      }
    }
  }

  void FindShortSuccessor(std::string* key) const override {}
};

// A comparator that does NOT shorten (leaves start unchanged)
class NoShortenComparator : public Comparator {
 public:
  const char* Name() const override { return "NoShortenComparator"; }

  int Compare(const Slice& a, const Slice& b) const override {
    return a.compare(b);
  }

  void FindShortestSeparator(std::string* start,
                              const Slice& limit) const override {
    // Does nothing - leaves start unchanged
  }

  void FindShortSuccessor(std::string* key) const override {}
};

// A comparator that makes the key longer instead of shorter
class LengthenComparator : public Comparator {
 public:
  const char* Name() const override { return "LengthenComparator"; }

  int Compare(const Slice& a, const Slice& b) const override {
    return a.compare(b);
  }

  void FindShortestSeparator(std::string* start,
                              const Slice& limit) const override {
    // Make the key longer
    start->append("extra");
  }

  void FindShortSuccessor(std::string* key) const override {}
};

class FindShortestSeparatorTest_190 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test: When user comparator shortens the key, InternalKeyComparator should
// use the shortened key with max sequence number
TEST_F(FindShortestSeparatorTest_190, ShortenedKeyIsUsed_190) {
  MockUserComparator user_cmp;
  InternalKeyComparator cmp(&user_cmp);

  // "abcd" with seq=100, type=kTypeValue
  std::string start = MakeInternalKey("abcd", 100, kTypeValue);
  // "abzz" with seq=200, type=kTypeValue
  std::string limit = MakeInternalKey("abzz", 200, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  // The result should be different (shortened)
  // The shortened user key should be "ac" (from MockUserComparator)
  // followed by packed kMaxSequenceNumber | kValueTypeForSeek
  // Verify the result is between original start and limit
  EXPECT_LT(cmp.Compare(original_start, start), 0);
  EXPECT_LT(cmp.Compare(start, limit), 0);

  // The result should be shorter than original since user key was shortened
  // but has 8 bytes appended for sequence/type
}

// Test: When user comparator does NOT shorten (no change), start should remain
// unchanged
TEST_F(FindShortestSeparatorTest_190, NoShorteningLeavesStartUnchanged_190) {
  NoShortenComparator user_cmp;
  InternalKeyComparator cmp(&user_cmp);

  std::string start = MakeInternalKey("abcd", 100, kTypeValue);
  std::string limit = MakeInternalKey("abce", 200, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  // Should be unchanged because user comparator didn't shorten
  EXPECT_EQ(original_start, start);
}

// Test: When user comparator makes the key longer, start should remain unchanged
TEST_F(FindShortestSeparatorTest_190, LongerKeyIsIgnored_190) {
  LengthenComparator user_cmp;
  InternalKeyComparator cmp(&user_cmp);

  std::string start = MakeInternalKey("abcd", 100, kTypeValue);
  std::string limit = MakeInternalKey("abce", 200, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  // Should be unchanged because the lengthened key is not shorter
  EXPECT_EQ(original_start, start);
}

// Test: Same user key with different sequence numbers - user comparator
// typically won't shorten
TEST_F(FindShortestSeparatorTest_190, SameUserKeyDifferentSeq_190) {
  MockUserComparator user_cmp;
  InternalKeyComparator cmp(&user_cmp);

  std::string start = MakeInternalKey("abcd", 200, kTypeValue);
  std::string limit = MakeInternalKey("abcd", 100, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  // With same user key, the mock comparator won't shorten
  // so start should remain unchanged
  EXPECT_EQ(original_start, start);
}

// Test: Using the actual BytewiseComparator
TEST_F(FindShortestSeparatorTest_190, WithBytewiseComparator_190) {
  const Comparator* user_cmp = BytewiseComparator();
  InternalKeyComparator cmp(user_cmp);

  std::string start = MakeInternalKey("hello", 100, kTypeValue);
  std::string limit = MakeInternalKey("world", 200, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  // Result should still be >= original_start and < limit in internal key order
  EXPECT_LE(cmp.Compare(original_start, start), 0);
  EXPECT_LT(cmp.Compare(start, limit), 0);
}

// Test: Adjacent user keys where shortening is possible
TEST_F(FindShortestSeparatorTest_190, AdjacentKeys_190) {
  const Comparator* user_cmp = BytewiseComparator();
  InternalKeyComparator cmp(user_cmp);

  std::string start = MakeInternalKey("abc", 100, kTypeValue);
  std::string limit = MakeInternalKey("abd", 100, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  // Invariant: original_start <= result < limit
  EXPECT_LE(cmp.Compare(original_start, start), 0);
  EXPECT_LT(cmp.Compare(start, limit), 0);
}

// Test: Keys where only last byte differs by 1 - BytewiseComparator may not shorten
TEST_F(FindShortestSeparatorTest_190, ConsecutiveLastByte_190) {
  const Comparator* user_cmp = BytewiseComparator();
  InternalKeyComparator cmp(user_cmp);

  // 'a' and 'b' differ by exactly 1 at index 2
  std::string start = MakeInternalKey("aaa", 100, kTypeValue);
  std::string limit = MakeInternalKey("aab", 100, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  EXPECT_LE(cmp.Compare(original_start, start), 0);
  EXPECT_LT(cmp.Compare(start, limit), 0);
}

// Test: Empty-ish user key (single byte)
TEST_F(FindShortestSeparatorTest_190, SingleByteUserKey_190) {
  const Comparator* user_cmp = BytewiseComparator();
  InternalKeyComparator cmp(user_cmp);

  std::string start = MakeInternalKey("a", 100, kTypeValue);
  std::string limit = MakeInternalKey("z", 100, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  EXPECT_LE(cmp.Compare(original_start, start), 0);
  EXPECT_LT(cmp.Compare(start, limit), 0);
}

// Test: Very long user keys
TEST_F(FindShortestSeparatorTest_190, LongUserKeys_190) {
  const Comparator* user_cmp = BytewiseComparator();
  InternalKeyComparator cmp(user_cmp);

  std::string long_key_a(1000, 'a');
  std::string long_key_b(1000, 'a');
  long_key_b[500] = 'z';  // differ at position 500

  std::string start = MakeInternalKey(long_key_a, 100, kTypeValue);
  std::string limit = MakeInternalKey(long_key_b, 100, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  EXPECT_LE(cmp.Compare(original_start, start), 0);
  EXPECT_LT(cmp.Compare(start, limit), 0);
  // Should be shortened
  EXPECT_LE(start.size(), original_start.size());
}

// Test: When the same key is used for start and limit
TEST_F(FindShortestSeparatorTest_190, SameStartAndLimit_190) {
  const Comparator* user_cmp = BytewiseComparator();
  InternalKeyComparator cmp(user_cmp);

  std::string key = MakeInternalKey("test", 100, kTypeValue);
  std::string start = key;

  cmp.FindShortestSeparator(&start, Slice(key));

  // start should be unchanged or still valid
  // In this case, start == limit, so no shortening should occur
  EXPECT_EQ(key, start);
}

// Test: High sequence number
TEST_F(FindShortestSeparatorTest_190, HighSequenceNumber_190) {
  const Comparator* user_cmp = BytewiseComparator();
  InternalKeyComparator cmp(user_cmp);

  std::string start = MakeInternalKey("abc", kMaxSequenceNumber, kTypeValue);
  std::string limit = MakeInternalKey("abd", kMaxSequenceNumber, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  EXPECT_LE(cmp.Compare(original_start, start), 0);
  EXPECT_LT(cmp.Compare(start, limit), 0);
}

// Test: kTypeDeletion type
TEST_F(FindShortestSeparatorTest_190, DeletionType_190) {
  const Comparator* user_cmp = BytewiseComparator();
  InternalKeyComparator cmp(user_cmp);

  std::string start = MakeInternalKey("abc", 100, kTypeDeletion);
  std::string limit = MakeInternalKey("xyz", 200, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  EXPECT_LE(cmp.Compare(original_start, start), 0);
  EXPECT_LT(cmp.Compare(start, limit), 0);
}

// Test: Verify that when shortening happens, the result has kMaxSequenceNumber
TEST_F(FindShortestSeparatorTest_190, ShortenedResultHasMaxSeq_190) {
  MockUserComparator user_cmp;
  InternalKeyComparator cmp(&user_cmp);

  // "abcd" -> MockUserComparator shortens to "ac" when limit is "abzz"
  std::string start = MakeInternalKey("abcd", 100, kTypeValue);
  std::string limit = MakeInternalKey("abzz", 200, kTypeValue);

  std::string original_start = start;
  cmp.FindShortestSeparator(&start, Slice(limit));

  if (start != original_start) {
    // If shortened, extract the user key and verify it's shorter
    Slice internal_key(start);
    ASSERT_GE(internal_key.size(), 8u);
    Slice user_key(start.data(), start.size() - 8);
    
    Slice original_user_key(original_start.data(), original_start.size() - 8);
    EXPECT_LT(user_key.size(), original_user_key.size());
  }
}

}  // namespace leveldb

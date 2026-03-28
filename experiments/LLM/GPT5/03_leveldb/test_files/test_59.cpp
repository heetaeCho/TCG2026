// File: db/lookupkey_user_key_test_59.cc

#include "db/dbformat.h"         // leveldb::LookupKey, leveldb::SequenceNumber
#include "leveldb/slice.h"       // leveldb::Slice
#include <gtest/gtest.h>

#include <cstring>   // std::memcmp
#include <limits>
#include <string>
#include <vector>

using leveldb::LookupKey;
using leveldb::SequenceNumber;
using leveldb::Slice;

namespace {

class LookupKeyTest_59 : public ::testing::Test {
protected:
  static std::string MakeString(size_t n, char start = 'a') {
    std::string s;
    s.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      s.push_back(static_cast<char>(start + (i % 26)));
    }
    return s;
  }

  static void ExpectSliceBytesEqual(const Slice& a, const Slice& b) {
    ASSERT_EQ(a.size(), b.size());
    ASSERT_EQ(0, std::memcmp(a.data(), b.data(), a.size()));
  }
};

} // namespace

// Normal operation: user_key() should equal the key passed to the constructor.
TEST_F(LookupKeyTest_59, UserKey_ReturnsOriginalKey_59) {
  const std::string key = "hello";
  const Slice input(key);
  const SequenceNumber seq = 123;
  LookupKey lk(input, seq);

  Slice actual = lk.user_key();
  ExpectSliceBytesEqual(actual, input);
}

// Boundary: empty user key should be handled and returned as empty.
TEST_F(LookupKeyTest_59, UserKey_EmptyKey_59) {
  const std::string key; // empty
  const Slice input(key);
  const SequenceNumber seq = 0;
  LookupKey lk(input, seq);

  Slice actual = lk.user_key();
  EXPECT_EQ(actual.size(), 0u);
  // For completeness, also verify byte equality against the empty input Slice.
  ExpectSliceBytesEqual(actual, input);
}

// Boundary/content: user key containing embedded NUL bytes should be preserved.
TEST_F(LookupKeyTest_59, UserKey_WithEmbeddedNulls_59) {
  const char raw[] = {'a', '\0', 'b', '\0', 'c'};
  const Slice input(raw, sizeof(raw));
  const SequenceNumber seq = 999;
  LookupKey lk(input, seq);

  Slice actual = lk.user_key();
  ExpectSliceBytesEqual(actual, input);
}

// Boundary/size: very long user key should be returned intact.
TEST_F(LookupKeyTest_59, UserKey_LongKey_59) {
  // Use a size larger than small-stack buffers one might expect; treat as black box.
  const std::string key = LookupKeyTest_59::MakeString(1000);
  const Slice input(key);
  const SequenceNumber seq = 42;
  LookupKey lk(input, seq);

  Slice actual = lk.user_key();
  ExpectSliceBytesEqual(actual, input);
}

// Observable independence: user_key() should not depend on the sequence number argument.
TEST_F(LookupKeyTest_59, UserKey_IndependentOfSequence_59) {
  const std::string key = "stable-user-key";
  const Slice input(key);

  const SequenceNumber seqs[] = {
      0,
      1,
      static_cast<SequenceNumber>(123456789),
      std::numeric_limits<SequenceNumber>::max()
  };

  // Build multiple LookupKey instances with different sequences and ensure user_key() matches input for all.
  for (SequenceNumber s : seqs) {
    LookupKey lk(input, s);
    Slice actual = lk.user_key();
    ExpectSliceBytesEqual(actual, input);
  }
}

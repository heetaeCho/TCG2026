// File: db/dbformat_append_internal_key_test.cc
#include "db/dbformat.h"    // ParsedInternalKey, ValueType
#include "db/dbformat.cc"   // AppendInternalKey (if it's not in a header)
#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <string>
#include <limits>
#include <cstring>

using leveldb::AppendInternalKey;
using leveldb::ParsedInternalKey;
using leveldb::Slice;
using leveldb::ValueType;
using leveldb::SequenceNumber;

namespace {

class AppendInternalKeyTest_185 : public ::testing::Test {
 protected:
  static std::string Last8(const std::string& s) {
    EXPECT_GE(s.size(), static_cast<size_t>(8));
    return s.substr(s.size() - 8);
  }
};

TEST_F(AppendInternalKeyTest_185, AppendsUserKeyAnd8ByteTag_185) {
  std::string out;
  const std::string user = "abc";
  ParsedInternalKey pik(Slice(user), static_cast<SequenceNumber>(123), static_cast<ValueType>(1));

  AppendInternalKey(&out, pik);

  ASSERT_EQ(out.size(), user.size() + 8u) << "Should append user key plus 8-byte tag";
  EXPECT_EQ(out.substr(0, user.size()), user) << "User key bytes should be preserved verbatim at the start";
}

TEST_F(AppendInternalKeyTest_185, AppendsToExistingBuffer_185) {
  std::string out = "prefix";
  const std::string user = "x";
  ParsedInternalKey pik(Slice(user), static_cast<SequenceNumber>(7), static_cast<ValueType>(0));

  AppendInternalKey(&out, pik);

  ASSERT_EQ(out.size(), std::string("prefix").size() + user.size() + 8u);
  EXPECT_EQ(out.substr(0, 6), "prefix") << "Existing contents must be preserved";
  EXPECT_EQ(out.substr(6, user.size()), user) << "User key should be appended after existing bytes";
}

TEST_F(AppendInternalKeyTest_185, EmptyUserKeyStillAppends8Bytes_185) {
  std::string out = "p";
  const std::string user = "";
  ParsedInternalKey pik(Slice(user), static_cast<SequenceNumber>(0), static_cast<ValueType>(0));

  const size_t before = out.size();
  AppendInternalKey(&out, pik);

  ASSERT_EQ(out.size(), before + 8u) << "Even with empty user key, an 8-byte tag should be appended";
  EXPECT_EQ(out[0], 'p') << "Pre-existing data should remain intact";
}

TEST_F(AppendInternalKeyTest_185, DifferentSequenceProducesDifferentTag_185) {
  std::string a, b;
  const std::string user = "k";
  ValueType type = static_cast<ValueType>(1);

  ParsedInternalKey pik1(Slice(user), static_cast<SequenceNumber>(1), type);
  ParsedInternalKey pik2(Slice(user), static_cast<SequenceNumber>(2), type);

  AppendInternalKey(&a, pik1);
  AppendInternalKey(&b, pik2);

  ASSERT_EQ(a.substr(0, user.size()), user);
  ASSERT_EQ(b.substr(0, user.size()), user);
  ASSERT_EQ(a.size(), user.size() + 8u);
  ASSERT_EQ(b.size(), user.size() + 8u);

  // Only assert that the 8-byte tails differ when sequence differs
  EXPECT_NE(Last8(a), Last8(b)) << "Changing sequence should change the tag bytes";
}

TEST_F(AppendInternalKeyTest_185, DifferentTypeProducesDifferentTag_185) {
  std::string a, b;
  const std::string user = "key123";
  SequenceNumber seq = static_cast<SequenceNumber>(42);

  ParsedInternalKey pikA(Slice(user), seq, static_cast<ValueType>(0));
  ParsedInternalKey pikB(Slice(user), seq, static_cast<ValueType>(1));

  AppendInternalKey(&a, pikA);
  AppendInternalKey(&b, pikB);

  ASSERT_EQ(a.substr(0, user.size()), user);
  ASSERT_EQ(b.substr(0, user.size()), user);
  ASSERT_EQ(a.size(), user.size() + 8u);
  ASSERT_EQ(b.size(), user.size() + 8u);

  EXPECT_NE(Last8(a), Last8(b)) << "Changing type should change the tag bytes";
}

TEST_F(AppendInternalKeyTest_185, DeterministicForSameInputs_185) {
  std::string a, b;
  const std::string user = "deterministic";
  SequenceNumber seq = static_cast<SequenceNumber>(999);
  ValueType type = static_cast<ValueType>(1);

  ParsedInternalKey p1(Slice(user), seq, type);
  ParsedInternalKey p2(Slice(user), seq, type);

  AppendInternalKey(&a, p1);
  AppendInternalKey(&b, p2);

  EXPECT_EQ(a, b) << "Same inputs should yield identical output bytes";
}

TEST_F(AppendInternalKeyTest_185, LargeSequenceNumberStillProduces8ByteTag_185) {
  std::string out;
  const std::string user = "U";
  // Use a very large sequence number (boundary-ish), without asserting on encoding
  SequenceNumber large = std::numeric_limits<SequenceNumber>::max();

  ParsedInternalKey pik(Slice(user), large, static_cast<ValueType>(1));
  AppendInternalKey(&out, pik);

  ASSERT_EQ(out.size(), user.size() + 8u);
  EXPECT_EQ(out.substr(0, user.size()), user) << "User key bytes should be preserved";
  // We don't assert the actual bytes of the tag—just that 8 bytes are present.
}

}  // namespace

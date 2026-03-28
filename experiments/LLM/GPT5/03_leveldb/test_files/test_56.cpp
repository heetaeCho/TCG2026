#include "db/dbformat.h"
#include "gtest/gtest.h"
#include <string>

namespace leveldb {

class ParseInternalKeyTest_56 : public ::testing::Test {};

// Utility: build an internal key = user_key + 8-byte trailer filled with the same byte `b`.
// Using the same byte for all 8 bytes avoids depending on endianness:
// - The low 8 bits (type) extracted via num & 0xff will equal `b` regardless of endianness.
// - We avoid asserting specific sequence values except when trailer is all zeros.
static std::string MakeInternalKeyWithUniformTrailer(const std::string& user, uint8_t b) {
  std::string s = user;
  s.append(8, static_cast<char>(b));
  return s;
}

// Normal case: valid deletion type (c=0) with non-empty user key; sequence should be 0 when trailer is all zeros.
TEST_F(ParseInternalKeyTest_56, ParsesDeletionTypeWithUserKey_56) {
  const std::string user = "user-key";
  const std::string raw = MakeInternalKeyWithUniformTrailer(user, /*b=*/0);
  ParsedInternalKey pik;
  const bool ok = ParseInternalKey(Slice(raw), &pik);

  EXPECT_TRUE(ok);
  EXPECT_EQ(pik.type, kTypeDeletion);
  EXPECT_EQ(pik.sequence, static_cast<SequenceNumber>(0));  // trailer all zeros -> sequence==0
  EXPECT_EQ(pik.user_key.ToString(), user);
}

// Normal case: valid value type (c=1) returns true and preserves user key.
TEST_F(ParseInternalKeyTest_56, ParsesValueTypeReturnsTrue_56) {
  const std::string user = "v";
  const std::string raw = MakeInternalKeyWithUniformTrailer(user, /*b=*/1); // c=1
  ParsedInternalKey pik;
  const bool ok = ParseInternalKey(Slice(raw), &pik);

  EXPECT_TRUE(ok);
  EXPECT_EQ(pik.type, kTypeValue);
  // We do not assert a particular sequence value here (trailer not all zeros).
  EXPECT_EQ(pik.user_key.ToString(), user);
}

// Boundary: exactly 8 bytes (no user key) with deletion type should still parse.
TEST_F(ParseInternalKeyTest_56, ExactlyEightBytesNoUserKey_56) {
  const std::string raw(8, '\0');  // user_key.size()==0, trailer all zeros
  ParsedInternalKey pik;
  const bool ok = ParseInternalKey(Slice(raw), &pik);

  EXPECT_TRUE(ok);
  EXPECT_EQ(pik.type, kTypeDeletion);
  EXPECT_EQ(pik.sequence, static_cast<SequenceNumber>(0));
  EXPECT_TRUE(pik.user_key.empty());
}

// Boundary: input shorter than 8 bytes must fail and must not modify the output parameter.
TEST_F(ParseInternalKeyTest_56, TooShortReturnsFalseAndDoesNotModifyResult_56) {
  ParsedInternalKey pik_before;
  pik_before.user_key = Slice("keep", 4);
  pik_before.sequence = static_cast<SequenceNumber>(123);
  pik_before.type = kTypeValue;

  ParsedInternalKey pik_after = pik_before;

  const std::string raw_too_short = "short"; // 5 bytes
  const bool ok = ParseInternalKey(Slice(raw_too_short), &pik_after);

  EXPECT_FALSE(ok);
  // Verify unchanged
  EXPECT_EQ(pik_after.user_key.ToString(), pik_before.user_key.ToString());
  EXPECT_EQ(pik_after.sequence, pik_before.sequence);
  EXPECT_EQ(pik_after.type, pik_before.type);
}

// Error/exceptional (observable): invalid type (> kTypeValue) -> returns false,
// but fields are assigned based on parsed bytes (observable via result).
TEST_F(ParseInternalKeyTest_56, InvalidTypeReturnsFalseButOutputsAreSet_56) {
  const std::string user = "invalid-type";
  // c=2 (not allowed since kTypeValue==1)
  const std::string raw = MakeInternalKeyWithUniformTrailer(user, /*b=*/2);
  ParsedInternalKey pik;
  const bool ok = ParseInternalKey(Slice(raw), &pik);

  EXPECT_FALSE(ok);
  // Type reflects what was parsed (even if invalid)
  EXPECT_EQ(static_cast<uint8_t>(pik.type), static_cast<uint8_t>(2));
  EXPECT_EQ(pik.user_key.ToString(), user);
  // No assertion on sequence since it depends on full 64-bit value and endianness.
}

// Large user key boundary: ensure user key is preserved; trailer zeros -> deterministic sequence==0.
TEST_F(ParseInternalKeyTest_56, LargeUserKeyPreserved_56) {
  const std::string user(1024, 'A');  // large prefix
  const std::string raw = MakeInternalKeyWithUniformTrailer(user, /*b=*/0);
  ParsedInternalKey pik;
  const bool ok = ParseInternalKey(Slice(raw), &pik);

  EXPECT_TRUE(ok);
  EXPECT_EQ(pik.type, kTypeDeletion);
  EXPECT_EQ(pik.sequence, static_cast<SequenceNumber>(0));
  EXPECT_EQ(pik.user_key.size(), user.size());
  EXPECT_EQ(pik.user_key.ToString(), user);
}

}  // namespace leveldb

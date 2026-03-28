// File: dbformat_pack_sequence_and_type_test.cc

#include "gtest/gtest.h"
#include "db/dbformat.h"

// Include the .cc to access the internal-linkage (static) function in this TU.
// This does NOT re-implement logic; it compiles the real implementation into the test TU.
#include "db/dbformat.cc"

using leveldb::SequenceNumber;
using leveldb::ValueType;
using leveldb::kMaxSequenceNumber;
using leveldb::kValueTypeForSeek;

class PackSequenceAndTypeTest_184 : public ::testing::Test {
protected:
  // Utility to skip death tests when asserts are compiled out.
  void SkipIfNoAsserts() {
#ifdef NDEBUG
    GTEST_SKIP() << "Assertions are disabled in release builds (NDEBUG defined).";
#endif
  }
};

// Normal operation: seq=0 packs into the high 56 bits as zero; low 8 bits carry the type.
TEST_F(PackSequenceAndTypeTest_184, PacksZeroSequence_LowByteIsType_184) {
  const SequenceNumber seq = 0;
  const ValueType t = kValueTypeForSeek;

  const uint64_t packed = leveldb::PackSequenceAndType(seq, t);

  // Observable effects without mirroring implementation:
  // - Low byte should equal the type.
  // - Upper bits (sequence) should be zero.
  EXPECT_EQ(static_cast<uint8_t>(packed & 0xFFu), static_cast<uint8_t>(t));
  EXPECT_EQ(packed >> 8, 0u);
}

// Boundary: maximum allowed sequence number should be preserved in the upper bits.
TEST_F(PackSequenceAndTypeTest_184, PacksMaxSequence_UpperBitsMatch_184) {
  const SequenceNumber seq = kMaxSequenceNumber;
  const ValueType t = kValueTypeForSeek;

  const uint64_t packed = leveldb::PackSequenceAndType(seq, t);

  // Upper bits should equal the max sequence; low byte should equal the type.
  EXPECT_EQ(packed >> 8, static_cast<uint64_t>(seq));
  EXPECT_EQ(static_cast<uint8_t>(packed & 0xFFu), static_cast<uint8_t>(t));
}

// Sanity: changing sequence affects upper bits but not the low-byte type indicator.
TEST_F(PackSequenceAndTypeTest_184, DifferentSequencesChangeUpperBitsOnly_184) {
  const SequenceNumber seq1 = 1;
  const SequenceNumber seq2 = 12345;
  const ValueType t = kValueTypeForSeek;

  const uint64_t p1 = leveldb::PackSequenceAndType(seq1, t);
  const uint64_t p2 = leveldb::PackSequenceAndType(seq2, t);

  // Low byte (type) remains the same.
  EXPECT_EQ(static_cast<uint8_t>(p1 & 0xFFu), static_cast<uint8_t>(t));
  EXPECT_EQ(static_cast<uint8_t>(p2 & 0xFFu), static_cast<uint8_t>(t));

  // Upper bits differ because sequences differ.
  EXPECT_NE(p1 >> 8, p2 >> 8);
}

// Error case: seq > kMaxSequenceNumber should hit the assert (death in debug builds).
TEST_F(PackSequenceAndTypeTest_184, SeqAboveMax_TriggersAssert_184) {
  SkipIfNoAsserts();

  const SequenceNumber too_large_seq = static_cast<SequenceNumber>(kMaxSequenceNumber + 1);
  const ValueType t = kValueTypeForSeek;

  // Use a regex that matches generic assertion failures.
  ASSERT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-deadcode.DeadStores)
        auto _ = leveldb::PackSequenceAndType(too_large_seq, t);
      },
      ".*");
}

// Error case: t > kValueTypeForSeek should hit the assert (death in debug builds).
TEST_F(PackSequenceAndTypeTest_184, TypeAboveForSeek_TriggersAssert_184) {
  SkipIfNoAsserts();

  const ValueType invalid_type = static_cast<ValueType>(static_cast<int>(kValueTypeForSeek) + 1);
  const SequenceNumber seq = 0;

  ASSERT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-deadcode.DeadStores)
        auto _ = leveldb::PackSequenceAndType(seq, invalid_type);
      },
      ".*");
}

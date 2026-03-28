// File: level_file_num_iterator_value_test_142.cc

#include <gtest/gtest.h>
#include "db/dbformat.h"        // InternalKeyComparator, BytewiseComparator
#include "db/version_edit.h"    // FileMetaData
#include "leveldb/slice.h"
#include "leveldb/iterator.h"

// Forward-declare the nested iterator type we are testing.
namespace leveldb {
class Version {
 public:
  class LevelFileNumIterator;  // defined in db/version_set.cc
};
}  // namespace leveldb

using namespace leveldb;

namespace {

// Simple helper to decode little-endian fixed64 from a raw 8-byte ptr
static uint64_t DecodeFixed64LE(const char* p) {
  // Decode as little endian without relying on LevelDB internals in test
  uint64_t r = 0;
  for (int i = 7; i >= 0; --i) {
    r = (r << 8) | static_cast<unsigned char>(p[i]);
  }
  return r;
}

class LevelFileNumIteratorTest_142 : public ::testing::Test {
protected:
  InternalKeyComparator icmp_{BytewiseComparator()};

  // Keep ownership to delete FileMetaData pointers after tests
  std::vector<std::unique_ptr<FileMetaData>> owned_;
  std::vector<FileMetaData*> files_;

  FileMetaData* AddFile(uint64_t number, uint64_t file_size) {
    auto f = std::make_unique<FileMetaData>();
    f->number = number;
    f->file_size = file_size;
    files_.push_back(f.get());
    owned_.push_back(std::move(f));
    return files_.back();
  }
};

} // namespace

// Normal operation: value() encodes {number, file_size} in-order (16 bytes)
TEST_F(LevelFileNumIteratorTest_142, ValueEncodesNumberAndSize_142) {
  AddFile(/*number=*/17, /*file_size=*/4096);
  AddFile(/*number=*/23, /*file_size=*/8192);

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());

  Slice v = it.value();
  ASSERT_EQ(v.size(), 16u);

  uint64_t enc_number = DecodeFixed64LE(v.data());
  uint64_t enc_size   = DecodeFixed64LE(v.data() + 8);

  EXPECT_EQ(enc_number, 17u);
  EXPECT_EQ(enc_size,   4096u);
}

// Iteration updates: Next() moves to next file and value() reflects it
TEST_F(LevelFileNumIteratorTest_142, NextUpdatesValue_142) {
  AddFile(100, 1);
  AddFile(200, 2);
  AddFile(300, 3);

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());

  // First
  {
    Slice v = it.value();
    ASSERT_EQ(v.size(), 16u);
    EXPECT_EQ(DecodeFixed64LE(v.data()), 100u);
    EXPECT_EQ(DecodeFixed64LE(v.data()+8), 1u);
  }

  // Second
  it.Next();
  ASSERT_TRUE(it.Valid());
  {
    Slice v = it.value();
    ASSERT_EQ(v.size(), 16u);
    EXPECT_EQ(DecodeFixed64LE(v.data()), 200u);
    EXPECT_EQ(DecodeFixed64LE(v.data()+8), 2u);
  }

  // Third
  it.Next();
  ASSERT_TRUE(it.Valid());
  {
    Slice v = it.value();
    ASSERT_EQ(v.size(), 16u);
    EXPECT_EQ(DecodeFixed64LE(v.data()), 300u);
    EXPECT_EQ(DecodeFixed64LE(v.data()+8), 3u);
  }
}

// Boundary values: zero and maximum 64-bit numbers are preserved
TEST_F(LevelFileNumIteratorTest_142, BoundaryValues_ZeroAndMax_142) {
  const uint64_t kZero = 0ull;
  const uint64_t kMax  = ~0ull;

  AddFile(kZero, kMax);
  AddFile(kMax, kZero);

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());

  // First entry: number = 0, file_size = max
  {
    Slice v = it.value();
    ASSERT_EQ(v.size(), 16u);
    EXPECT_EQ(DecodeFixed64LE(v.data()), kZero);
    EXPECT_EQ(DecodeFixed64LE(v.data()+8), kMax);
  }

  // Second entry: number = max, file_size = 0
  it.Next();
  ASSERT_TRUE(it.Valid());
  {
    Slice v = it.value();
    ASSERT_EQ(v.size(), 16u);
    EXPECT_EQ(DecodeFixed64LE(v.data()), kMax);
    EXPECT_EQ(DecodeFixed64LE(v.data()+8), kZero);
  }
}

// SeekToLast + Prev: moving backwards updates the encoded pair accordingly
TEST_F(LevelFileNumIteratorTest_142, SeekToLastAndPrev_142) {
  AddFile(10, 111);
  AddFile(20, 222);
  AddFile(30, 333);

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());

  // Last
  {
    Slice v = it.value();
    ASSERT_EQ(v.size(), 16u);
    EXPECT_EQ(DecodeFixed64LE(v.data()), 30u);
    EXPECT_EQ(DecodeFixed64LE(v.data()+8), 333u);
  }

  // Prev
  it.Prev();
  ASSERT_TRUE(it.Valid());
  {
    Slice v = it.value();
    ASSERT_EQ(v.size(), 16u);
    EXPECT_EQ(DecodeFixed64LE(v.data()), 20u);
    EXPECT_EQ(DecodeFixed64LE(v.data()+8), 222u);
  }
}

// Empty input: iterator should be invalid; value() should not be called
TEST_F(LevelFileNumIteratorTest_142, EmptyList_NotValid_142) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  EXPECT_FALSE(it.Valid());

  it.SeekToLast();
  EXPECT_FALSE(it.Valid());
}

// Error/exceptional (observable): calling value() when !Valid() should assert.
// Use death test if supported (assert(Valid()) in value()).
TEST_F(LevelFileNumIteratorTest_142, ValueOnInvalidAsserts_142) {
  // Build with at least one file so constructor path is normal.
  AddFile(1, 1);

  Version::LevelFileNumIterator it(icmp_, &files_);
  // Do not seek; constructor sets index to flist->size(), so !Valid() is expected.

#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH_IF_SUPPORTED(
      [&](){
        // NOLINTNEXTLINE(clang-analyzer-core.CallAndMessage)
        (void)it.value();
      }(),
      ".*");  // Pattern not strict; just verify an assertion/abort occurs.
#else
  GTEST_SKIP() << "Death tests not supported on this platform/config.";
#endif
}

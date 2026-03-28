// File: block_iter_seek_test_413.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <cstring>

#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// The class under test lives in table/block.cc. Include the public factory or
// the header that exposes Block/Iter as appropriate in your build. If Iter is
// internal, we exercise it through Block's NewIterator factory (typical in LevelDB).
#include "table/block.h"    // Adjust include path to your repo layout

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

// --------------------------- Test Utilities ---------------------------

// Minimal varint32 encoding used by LevelDB block entries.
static void PutVarint32(std::string& dst, uint32_t v) {
  unsigned char buf[5];
  int len = 0;
  while (v >= 128) {
    buf[len++] = static_cast<unsigned char>(v | 0x80);
    v >>= 7;
  }
  buf[len++] = static_cast<unsigned char>(v);
  dst.append(reinterpret_cast<char*>(buf), len);
}

static void PutFixed32(std::string& dst, uint32_t v) {
  char buf[4];
  buf[0] = static_cast<char>(v & 0xff);
  buf[1] = static_cast<char>((v >> 8) & 0xff);
  buf[2] = static_cast<char>((v >> 16) & 0xff);
  buf[3] = static_cast<char>((v >> 24) & 0xff);
  dst.append(buf, 4);
}

// Build a very simple block:
//  - No prefix compression (shared=0 for every entry)
//  - One restart point at offset 0
//  - Keys must be provided in sorted order for the default comparator
static std::string BuildSimpleBlock(
    const std::vector<std::pair<std::string, std::string>>& kvs) {
  std::string block;

  // Entries
  for (const auto& kv : kvs) {
    const std::string& key = kv.first;
    const std::string& val = kv.second;
    const uint32_t shared = 0;
    const uint32_t non_shared = static_cast<uint32_t>(key.size());
    const uint32_t value_length = static_cast<uint32_t>(val.size());

    PutVarint32(block, shared);
    PutVarint32(block, non_shared);
    PutVarint32(block, value_length);
    block.append(key.data(), key.size());
    block.append(val.data(), val.size());
  }

  // Restart array: a single restart at offset 0
  const uint32_t restart0 = 0;
  std::string trailer;
  PutFixed32(trailer, restart0);
  PutFixed32(trailer, 1);  // num_restarts
  block += trailer;

  return block;
}

// Corrupted block that will force the mid-key check in Seek() to detect
// shared!=0 at a restart and trigger CorruptionError().
static std::string BuildCorruptedSharedAtRestartBlock() {
  std::string block;

  // Intentionally craft an entry at the only restart offset where shared != 0.
  // (shared=1, non_shared=3, value_length=1) -> violates Seek's expectation.
  PutVarint32(block, 1);   // shared (must be 0 at a restart) -> corruption
  PutVarint32(block, 3);   // non_shared
  PutVarint32(block, 1);   // value_length
  block.append("abc", 3);
  block.append("v", 1);

  // Restart array: the only restart points at offset 0
  PutFixed32(block, 0);
  PutFixed32(block, 1);  // num_restarts

  return block;
}

// A strict mock comparator as an external collaborator.
class MockComparator : public leveldb::Comparator {
 public:
  MOCK_METHOD(int, Compare, (const leveldb::Slice&, const leveldb::Slice&), (const, override));
  MOCK_METHOD(const char*, Name, (), (const, override));
  // The following two are not used by Block::Iter::Seek but must exist.
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

// Helper to create a Block and iterator from raw contents.
static std::unique_ptr<leveldb::Iterator> MakeIter(
    const leveldb::Comparator* cmp,
    const std::string& contents) {
  leveldb::BlockContents bc;
  bc.data = leveldb::Slice(contents);
  bc.cachable = false;
  bc.heap_allocated = false;
  leveldb::Block block(bc);
  return std::unique_ptr<leveldb::Iterator>(block.NewIterator(cmp));
}

}  // namespace

// ------------------------------ Tests ---------------------------------

// Basic seek to first key when target < first.
TEST(BlockIterSeekTest_413, Seek_TargetBeforeFirst_YieldsFirst_413) {
  StrictMock<MockComparator> cmp;

  // Default bytewise comparator semantics:
  EXPECT_CALL(cmp, Name()).WillRepeatedly(Return("test-cmp"));
  EXPECT_CALL(cmp, Compare(_, _)).WillRepeatedly([](const leveldb::Slice& a,
                                                    const leveldb::Slice& b) {
    // Compare lexicographically like the default comparator.
    const int r = a.compare(b);
    return r < 0 ? -1 : (r > 0 ? 1 : 0);
  });

  auto contents = BuildSimpleBlock({
      {"b", "1"},
      {"d", "2"},
      {"f", "3"},
  });
  auto it = MakeIter(&cmp, contents);

  it->Seek(leveldb::Slice("a"));  // target before "b"
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "b");
  EXPECT_EQ(it->value().ToString(), "1");
  EXPECT_TRUE(it->status().ok());
}

// Seek exactly to an existing key.
TEST(BlockIterSeekTest_413, Seek_ExactHit_PositionsOnKey_413) {
  StrictMock<MockComparator> cmp;
  EXPECT_CALL(cmp, Name()).WillRepeatedly(Return("test-cmp"));
  EXPECT_CALL(cmp, Compare(_, _)).WillRepeatedly([](const leveldb::Slice& a,
                                                    const leveldb::Slice& b) {
    const int r = a.compare(b);
    return r < 0 ? -1 : (r > 0 ? 1 : 0);
  });

  auto contents = BuildSimpleBlock({
      {"apple",  "x"},
      {"banana", "y"},
      {"carrot", "z"},
  });
  auto it = MakeIter(&cmp, contents);

  it->Seek(leveldb::Slice("banana"));
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "banana");
  EXPECT_EQ(it->value().ToString(), "y");
  EXPECT_TRUE(it->status().ok());

  // Idempotency: seeking again to the same key should keep us there.
  it->Seek(leveldb::Slice("banana"));
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "banana");
  EXPECT_EQ(it->value().ToString(), "y");
  EXPECT_TRUE(it->status().ok());
}

// Seek to the smallest key >= target (in-between).
TEST(BlockIterSeekTest_413, Seek_InBetween_YieldsCeilKey_413) {
  StrictMock<MockComparator> cmp;
  EXPECT_CALL(cmp, Name()).WillRepeatedly(Return("test-cmp"));
  EXPECT_CALL(cmp, Compare(_, _)).WillRepeatedly([](const leveldb::Slice& a,
                                                    const leveldb::Slice& b) {
    const int r = a.compare(b);
    return r < 0 ? -1 : (r > 0 ? 1 : 0);
  });

  auto contents = BuildSimpleBlock({
      {"aa", "v1"},
      {"bb", "v2"},
      {"cc", "v3"},
  });
  auto it = MakeIter(&cmp, contents);

  it->Seek(leveldb::Slice("b"));  // between "aa" and "bb"
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "bb");
  EXPECT_EQ(it->value().ToString(), "v2");
  EXPECT_TRUE(it->status().ok());
}

// Seek past the last key -> iterator should become invalid.
TEST(BlockIterSeekTest_413, Seek_AfterLast_MakesIteratorInvalid_413) {
  StrictMock<MockComparator> cmp;
  EXPECT_CALL(cmp, Name()).WillRepeatedly(Return("test-cmp"));
  EXPECT_CALL(cmp, Compare(_, _)).WillRepeatedly([](const leveldb::Slice& a,
                                                    const leveldb::Slice& b) {
    const int r = a.compare(b);
    return r < 0 ? -1 : (r > 0 ? 1 : 0);
  });

  auto contents = BuildSimpleBlock({
      {"k1", "a"},
      {"k2", "b"},
  });
  auto it = MakeIter(&cmp, contents);

  it->Seek(leveldb::Slice("k3"));  // strictly greater than last
  EXPECT_FALSE(it->Valid());
  // Status should still be OK; end-of-block is not an error.
  EXPECT_TRUE(it->status().ok());
}

// Corruption path: if the restart entry reports shared != 0,
// Seek() must signal corruption and leave the iterator invalid.
TEST(BlockIterSeekTest_413, Seek_CorruptRestart_SharedNotZero_SignalsCorruption_413) {
  StrictMock<MockComparator> cmp;
  EXPECT_CALL(cmp, Name()).WillRepeatedly(Return("test-cmp"));
  // Compare may never even be called if corruption is detected early,
  // so allow any count.
  EXPECT_CALL(cmp, Compare(_, _)).Times(testing::AnyNumber())
      .WillRepeatedly([](const leveldb::Slice& a, const leveldb::Slice& b) {
        const int r = a.compare(b);
        return r < 0 ? -1 : (r > 0 ? 1 : 0);
      });

  auto contents = BuildCorruptedSharedAtRestartBlock();
  auto it = MakeIter(&cmp, contents);

  it->Seek(leveldb::Slice("anything"));
  EXPECT_FALSE(it->Valid());
  EXPECT_FALSE(it->status().ok());  // must report an error status
}


// File: block_iter_prev_test_412.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <vector>

#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "table/block.h"

// NOTE:
// - We do NOT peek at or modify any private/internal state.
// - We only use the public iterator interface: Valid(), key(), value(),
//   SeekToFirst(), SeekToLast(), Next(), Prev(), status().
// - We generate a tiny, valid block payload externally for testing observable behavior.

namespace leveldb {
namespace {

// ---- Small helpers to construct a minimal block payload for tests ----
// These helpers are *not* re-implementations of class logic; they only
// build test data in the publicly documented block format (varint fields,
// restart array, etc.) so we can exercise the public iterator API.

static void PutVarint32(std::string& dst, uint32_t v) {
  // Standard varint32 encoding.
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
  // Little-endian fixed32
  unsigned char buf[4];
  buf[0] = static_cast<unsigned char>(v & 0xff);
  buf[1] = static_cast<unsigned char>((v >> 8) & 0xff);
  buf[2] = static_cast<unsigned char>((v >> 16) & 0xff);
  buf[3] = static_cast<unsigned char>((v >> 24) & 0xff);
  dst.append(reinterpret_cast<char*>(buf), 4);
}

// Append one entry (key, value) that starts a restart point (shared=0).
static void AppendStandaloneEntry(std::string& block,
                                  const Slice& key,
                                  const Slice& value) {
  const uint32_t shared = 0;
  const uint32_t non_shared = static_cast<uint32_t>(key.size());
  const uint32_t value_len = static_cast<uint32_t>(value.size());
  PutVarint32(block, shared);
  PutVarint32(block, non_shared);
  PutVarint32(block, value_len);
  block.append(key.data(), key.size());
  block.append(value.data(), value.size());
}

// Build a simple block with N standalone restart entries.
// Returns the finished block contents and fills restarts_offset & num_restarts.
static std::string BuildBlockWithStandaloneEntries(
    const std::vector<std::pair<Slice, Slice>>& kvs,
    uint32_t* restarts_offset,
    uint32_t* num_restarts) {
  std::string block;

  // Remember offsets of each entry (each is a restart point).
  std::vector<uint32_t> restart_offsets;
  restart_offsets.reserve(kvs.size());

  for (const auto& kv : kvs) {
    restart_offsets.push_back(static_cast<uint32_t>(block.size()));
    AppendStandaloneEntry(block, kv.first, kv.second);
  }

  // Restart array begins here.
  *restarts_offset = static_cast<uint32_t>(block.size());
  for (uint32_t off : restart_offsets) {
    PutFixed32(block, off);
  }

  // Number of restarts.
  *num_restarts = static_cast<uint32_t>(restart_offsets.size());
  PutFixed32(block, *num_restarts);

  return block;
}

// A tiny shim to construct an Iter directly.
// The production Block usually constructs Iter internally,
// but Iter's constructor is public in the provided interface.
static std::unique_ptr<Iterator> NewIterOverRawBlockBytes(
    const Comparator* cmp,
    const std::string& raw) {
  // The footer layout we produced is:
  //   [ ... data ... ][restart0][restart1]...[restartN-1][num_restarts (u32)]
  // However, Block::Iter's constructor in the prompt takes:
  //   (comparator, data_ptr, restarts_offset, num_restarts)
  // where 'restarts_offset' is the offset *to the first restart entry array*.
  //
  // We already computed 'restarts_offset' and 'num_restarts' while building.
  // To avoid duplicating that computation here (and to keep creation simple),
  // rebuild once with helpers and capture the offsets directly.

  // Recompute offsets by parsing the tail: last 4 bytes = num_restarts.
  ASSERT_GE(raw.size(), 4u);
  const size_t n = raw.size();
  const uint32_t num_restarts =
      static_cast<uint8_t>(raw[n - 4]) |
      (static_cast<uint8_t>(raw[n - 3]) << 8) |
      (static_cast<uint8_t>(raw[n - 2]) << 16) |
      (static_cast<uint8_t>(raw[n - 1]) << 24);

  ASSERT_GE(n, 4u + num_restarts * 4u);
  const uint32_t restarts_offset =
      static_cast<uint32_t>(n - 4u /*num*/ - num_restarts * 4u /*array*/);

  // Construct Iter over provided bytes.
  // NOTE: Block::Iter is nested, but the "table/block.h" typically exposes a
  // Block::Iter-compatible Iterator via Block::NewIterator. Given the prompt's
  // public constructor for Iter(comparator, data, restarts, num_restarts),
  // we use it directly as the iterator. If your environment exposes only
  // Block::NewIterator, switch to that instead.
  return std::unique_ptr<Iterator>(
      new Block::Iter(cmp, raw.data(), restarts_offset, num_restarts));
}

class BlockIterPrevTest_412 : public ::testing::Test {
 protected:
  const Comparator* cmp() const { return BytewiseComparator(); }
};

//
// -------------------- TESTS --------------------
//

TEST_F(BlockIterPrevTest_412, PrevOnInvalidDies_412) {
  // Fresh iterator starts invalid (current_ == restarts_), so Prev() must DCHECK/ASSERT.
  uint32_t restarts_off = 0, num_restarts = 0;
  // Build an *empty* block: just a restart array of size 0 and num_restarts=0.
  std::string raw;
  restarts_off = 0;
  PutFixed32(raw, 0 /*num_restarts*/);

  // Iter over empty data: Valid() should be false immediately.
  std::unique_ptr<Iterator> it(
      new Block::Iter(cmp(), raw.data(), restarts_off, num_restarts));
  ASSERT_FALSE(it->Valid());

#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH(it->Prev(), ".*");  // Asserts Valid()
#endif
}

TEST_F(BlockIterPrevTest_412, PrevFromSecondMovesToFirst_412) {
  // Build a block with two independent restart entries: ("a"->"1"), ("b"->"2").
  uint32_t restarts_off = 0, num_restarts = 0;
  std::string raw = BuildBlockWithStandaloneEntries(
      { {Slice("a"), Slice("1")}, {Slice("b"), Slice("2")} },
      &restarts_off, &num_restarts);

  // Create iterator over the raw block bytes.
  auto it = std::unique_ptr<Iterator>(
      new Block::Iter(cmp(), raw.data(), restarts_off, num_restarts));

  // Seek to first: at ("a","1").
  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "a");
  EXPECT_EQ(it->value().ToString(), "1");

  // Move to second entry ("b","2").
  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "b");
  EXPECT_EQ(it->value().ToString(), "2");

  // Now Prev() should move back to ("a","1").
  it->Prev();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "a");
  EXPECT_EQ(it->value().ToString(), "1");

  // Sanity: status remains OK (no observable error).
  EXPECT_TRUE(it->status().ok());
}

TEST_F(BlockIterPrevTest_412, PrevFromFirstBecomesInvalid_412) {
  // Single entry block: Prev() from first should make iterator invalid.
  uint32_t restarts_off = 0, num_restarts = 0;
  std::string raw = BuildBlockWithStandaloneEntries(
      { {Slice("k"), Slice("v")} },
      &restarts_off, &num_restarts);

  auto it = std::unique_ptr<Iterator>(
      new Block::Iter(cmp(), raw.data(), restarts_off, num_restarts));

  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "k");
  EXPECT_EQ(it->value().ToString(), "v");

  // Stepping back from the first entry should invalidate the iterator.
  it->Prev();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

}  // namespace
}  // namespace leveldb

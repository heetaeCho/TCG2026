// File: table/block_constructor_test_491.cc
#include <gtest/gtest.h>

#include "table/format.h"  // leveldb::BlockContents
#include "table/block.h"   // leveldb::Block
#include "leveldb/slice.h" // leveldb::Slice

using namespace leveldb;

// Helper to build a buffer with a uint32_t (little-endian) restart count
// stored in the last 4 bytes. The rest of the bytes are zeroed.
static std::string MakeBufferWithRestartCount(size_t total_size, uint32_t restarts) {
  std::string buf(total_size, '\0');
  if (total_size >= 4) {
    // Write little-endian at the end (standard LevelDB encoding)
    size_t o = total_size - 4;
    buf[o + 0] = static_cast<char>(restarts & 0xFF);
    buf[o + 1] = static_cast<char>((restarts >> 8) & 0xFF);
    buf[o + 2] = static_cast<char>((restarts >> 16) & 0xFF);
    buf[o + 3] = static_cast<char>((restarts >> 24) & 0xFF);
  }
  return buf;
}

// ---------- Normal operation ----------

TEST(BlockConstructorTest_491, KeepsSizeForValidMinimalBlockWithZeroRestarts_491) {
  // Minimal valid block: size == 4 bytes, restart count == 0
  std::string data = MakeBufferWithRestartCount(/*total_size=*/4, /*restarts=*/0);
  BlockContents contents{Slice(data), /*cachable=*/true, /*heap_allocated=*/false};

  Block b(contents);

  // Observable behavior: size() should reflect the provided size for a valid block
  EXPECT_EQ(b.size(), 4u);
}

TEST(BlockConstructorTest_491, KeepsSizeWhenRestartsAtMaxAllowed_491) {
  // total_size = 12 bytes -> max_restarts_allowed = (12 - 4) / 4 = 2
  // Set restarts = 2 (exactly the max)
  std::string data = MakeBufferWithRestartCount(/*total_size=*/12, /*restarts=*/2);
  BlockContents contents{Slice(data), /*cachable=*/true, /*heap_allocated=*/true};

  Block b(contents);

  EXPECT_EQ(b.size(), 12u);
}

// ---------- Boundary conditions ----------

TEST(BlockConstructorTest_491, SizeLessThan4BytesIsMarkedError_491) {
  // Any size < 4 should be marked as error -> observable via size() == 0
  for (size_t sz : {0u, 1u, 2u, 3u}) {
    std::string data(sz, '\0');
    BlockContents contents{Slice(data), /*cachable=*/false, /*heap_allocated=*/false};
    Block b(contents);
    EXPECT_EQ(b.size(), 0u) << "Expected error marker (size==0) for sz=" << sz;
  }
}

TEST(BlockConstructorTest_491, Exactly4BytesWithOneRestartIsInvalid_491) {
  // total_size = 4 => max_restarts_allowed = 0
  // restarts = 1 > 0 -> invalid -> size() becomes 0
  std::string data = MakeBufferWithRestartCount(/*total_size=*/4, /*restarts=*/1);
  BlockContents contents{Slice(data), /*cachable=*/true, /*heap_allocated=*/false};

  Block b(contents);

  EXPECT_EQ(b.size(), 0u);
}

// ---------- Exceptional/error-like inputs (observable) ----------

TEST(BlockConstructorTest_491, ExceedsMaxAllowedRestartsMarksError_491) {
  // total_size = 12 -> max_restarts_allowed = 2
  // restarts = 3 -> should be invalid -> size() becomes 0
  std::string data = MakeBufferWithRestartCount(/*total_size=*/12, /*restarts=*/3);
  BlockContents contents{Slice(data), /*cachable=*/false, /*heap_allocated=*/true};

  Block b(contents);

  EXPECT_EQ(b.size(), 0u);
}

TEST(BlockConstructorTest_491, HugeRestartCountMarksError_491) {
  // Use a very large restart count that should exceed any max allowed.
  // total_size = 8 -> max_restarts_allowed = (8 - 4) / 4 = 1
  // restarts = 0xFFFFFFFF -> invalid -> size() becomes 0
  std::string data = MakeBufferWithRestartCount(/*total_size=*/8, /*restarts=*/0xFFFFFFFFu);
  BlockContents contents{Slice(data), /*cachable=*/true, /*heap_allocated=*/false};

  Block b(contents);

  EXPECT_EQ(b.size(), 0u);
}

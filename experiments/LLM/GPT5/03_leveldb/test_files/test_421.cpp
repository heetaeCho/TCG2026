// File: table/delete_cached_block_test_421.cc

#include <gtest/gtest.h>
#include <string>

// --- Minimal stubs to compile the test ------------------------------------
// We only provide the *minimal* surface needed by the function signature.
// No internal logic is reimplemented or assumed.

namespace leveldb {

// Minimal Slice stub (interface-only surface for parameter passing)
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  explicit Slice(const char* s) : data_(s), size_(s ? ::strlen(s) : 0) {}
  explicit Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
 private:
  const char* data_;
  size_t size_;
};

// Minimal Block stub to observe deletion via destructor side-effect
class Block {
 public:
  static int destroyed_count;
  virtual ~Block() { ++destroyed_count; }
};
int Block::destroyed_count = 0;

}  // namespace leveldb

// Include the implementation under test so the internal-linkage function
// (static in table.cc) is available in this translation unit.
#include "table/table.cc"

// --- Test Fixture -----------------------------------------------------------

class DeleteCachedBlockTest_421 : public ::testing::Test {
 protected:
  void SetUp() override { leveldb::Block::destroyed_count = 0; }
};

// --- Tests ------------------------------------------------------------------

// [421] Normal operation: deleting a non-null Block* invokes its destructor.
TEST_F(DeleteCachedBlockTest_421, DeletesNonNullBlock_421) {
  using namespace leveldb;

  Block* b = new Block();
  EXPECT_EQ(0, Block::destroyed_count);

  Slice any_key("key");
  DeleteCachedBlock(any_key, reinterpret_cast<void*>(b));

  EXPECT_EQ(1, Block::destroyed_count) << "Block destructor should be called exactly once.";
}

// [421] Boundary: passing nullptr must be safe (no crash, no destructor call).
TEST_F(DeleteCachedBlockTest_421, SafeOnNullPointer_421) {
  using namespace leveldb;

  EXPECT_EQ(0, Block::destroyed_count);

  Slice any_key;  // empty slice is fine
  DeleteCachedBlock(any_key, nullptr);

  EXPECT_EQ(0, Block::destroyed_count) << "Deleting nullptr should have no effect.";
}

// [421] Verifies the Slice parameter is ignored (behavior identical for any key).
TEST_F(DeleteCachedBlockTest_421, IgnoresSliceParameter_421) {
  using namespace leveldb;

  // Call with one key
  Block* b1 = new Block();
  Slice key1("first");
  DeleteCachedBlock(key1, reinterpret_cast<void*>(b1));

  // Call with a completely different key
  Block* b2 = new Block();
  std::string different_key = "totally_different_key";
  Slice key2(different_key);
  DeleteCachedBlock(key2, reinterpret_cast<void*>(b2));

  EXPECT_EQ(2, Block::destroyed_count)
      << "Both blocks should be destroyed regardless of the Slice value.";
}

// File: get_file_iterator_test_144.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <string>

#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

// Forward decls to avoid depending on the real Iterator in tests.
// We only need a concrete type to hand back through GetFileIterator.
namespace leveldb {
class Iterator {
 public:
  virtual ~Iterator() = default;
  virtual Status status() const { return Status::OK(); }  // observable in tests
};

// The function under test
Iterator* GetFileIterator(void* arg, const ReadOptions& options, const Slice& file_value);

// Test-double: a minimal stand-in for TableCache that records the last call.
// We keep the same name and namespace so the reinterpret_cast in GetFileIterator
// will work without modifying production code.
class TableCache {
 public:
  struct Call {
    bool called = false;
    ReadOptions options{};
    uint64_t file_number = 0;
    uint64_t file_size = 0;
  };

  explicit TableCache(Iterator* to_return = nullptr) : to_return_(to_return) {}

  // Signature matches the overload used by GetFileIterator in the provided snippet.
  Iterator* NewIterator(const ReadOptions& options, uint64_t file_number, uint64_t file_size) {
    last_.called = true;
    last_.options = options;
    last_.file_number = file_number;
    last_.file_size = file_size;
    return to_return_;
  }

  const Call& last() const { return last_; }
  void set_return_iterator(Iterator* it) { to_return_ = it; }

 private:
  Iterator* to_return_;
  Call last_{};
};

// A very small concrete Iterator we can return from our TableCache double.
class DummyIterator final : public Iterator {
 public:
  explicit DummyIterator(Status st = Status::OK()) : st_(std::move(st)) {}
  Status status() const override { return st_; }
 private:
  Status st_;
};
}  // namespace leveldb

using namespace leveldb;

// Helpers (test-only) to craft the 16-byte value expected by GetFileIterator.
// This does NOT re-implement any production logic; it only prepares inputs.
static inline void EncodeFixed64LE(uint64_t v, char* out) {
  for (int i = 0; i < 8; ++i) { out[i] = static_cast<char>(v & 0xffU); v >>= 8; }
}
static inline Slice MakeFileValue(uint64_t file_number, uint64_t file_size, std::string* backing) {
  backing->assign(16, '\0');
  EncodeFixed64LE(file_number, &(*backing)[0]);
  EncodeFixed64LE(file_size,  &(*backing)[8]);
  return Slice(*backing);
}

class GetFileIteratorTest_144 : public ::testing::Test {};

// 1) Error path: if file_value.size() != 16, returns an error iterator with Corruption status.
TEST_F(GetFileIteratorTest_144, ReturnsErrorIteratorOnUnexpectedValueSize_144) {
  // Arrange
  std::string backing = "short";  // size != 16
  Slice bad_value(backing);
  ReadOptions ro;
  TableCache unused_cache;  // will not be used because size check fails

  // Act
  Iterator* it = GetFileIterator(static_cast<void*>(&unused_cache), ro, bad_value);

  // Assert (observable behavior only)
  ASSERT_NE(it, nullptr);
  Status st = it->status();
  EXPECT_TRUE(st.IsCorruption());
  // The message should mention the reason (from the provided snippet).
  EXPECT_NE(st.ToString().find("FileReader invoked with unexpected value"), std::string::npos);
}

// 2) Success path: forwards decoded file_number and file_size to TableCache::NewIterator,
//    and returns the exact iterator produced by the cache.
TEST_F(GetFileIteratorTest_144, ForwardsParametersAndReturnsCacheIterator_144) {
  // Arrange
  const uint64_t kFileNumber = 123456789ULL;
  const uint64_t kFileSize   = 987654321ULL;

  std::string backing;
  Slice ok_value = MakeFileValue(kFileNumber, kFileSize, &backing);

  ReadOptions ro;
  ro.verify_checksums = true;
  ro.fill_cache = false;

  DummyIterator expected_iter;     // what our TableCache will return
  TableCache cache(&expected_iter);

  // Act
  Iterator* it = GetFileIterator(static_cast<void*>(&cache), ro, ok_value);

  // Assert: returned pointer is exactly what TableCache produced.
  EXPECT_EQ(it, &expected_iter);

  // Assert: observable interaction – TableCache was called with decoded params.
  const auto& call = cache.last();
  ASSERT_TRUE(call.called);
  EXPECT_EQ(call.file_number, kFileNumber);
  EXPECT_EQ(call.file_size,   kFileSize);

  // ReadOptions is passed through by value; verify key fields preserved.
  EXPECT_TRUE(call.options.verify_checksums);
  EXPECT_FALSE(call.options.fill_cache);
}

// 3) Boundary: file_number/file_size at extremes still forwarded correctly (e.g., 0 and max).
TEST_F(GetFileIteratorTest_144, ForwardsBoundaryValues_ZeroAndMax_144) {
  // Arrange
  const uint64_t kFileNumber = 0ULL;
  const uint64_t kFileSize   = std::numeric_limits<uint64_t>::max();

  std::string backing;
  Slice ok_value = MakeFileValue(kFileNumber, kFileSize, &backing);

  ReadOptions ro;
  DummyIterator expected_iter;
  TableCache cache(&expected_iter);

  // Act
  Iterator* it = GetFileIterator(static_cast<void*>(&cache), ro, ok_value);

  // Assert
  EXPECT_EQ(it, &expected_iter);
  const auto& call = cache.last();
  ASSERT_TRUE(call.called);
  EXPECT_EQ(call.file_number, kFileNumber);
  EXPECT_EQ(call.file_size,   kFileSize);
}

// File: table_approximate_offset_of_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "leveldb/options.h"
#include "leveldb/iterator.h"
#include "leveldb/table.h"
#include "table/format.h"

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::Invoke;

// ------------------------------
// Test‑only mock for the index iterator
// ------------------------------
namespace {

class MockIterator : public leveldb::Iterator {
public:
  MOCK_METHOD(bool, Valid, (), (override, const));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(const leveldb::Slice, value, (), (override, const));
  // Unused virtuals kept to satisfy interface
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(const leveldb::Slice, key, (), (override, const));
  MOCK_METHOD(const leveldb::Status, status, (), (override, const));
};

// A tiny handle encoder helper (uses only public API; no internal logic)
static leveldb::Slice EncodeHandle(uint64_t offset, uint64_t size, std::string* out) {
  leveldb::BlockHandle h;
  h.set_offset(offset);
  h.set_size(size);
  h.EncodeTo(out);                // public API
  return leveldb::Slice(*out);    // safe: BlockHandle::DecodeFrom will consume this
}

} // namespace

// ------------------------------
// Test fixture
// ------------------------------
class TableApproximateOffsetOfTest_424 : public ::testing::Test {
protected:
  // Test wiring points (replace TODOs with your project helpers)

  // TODO(you): Return a fresh Table* whose index block iterator is the one
  //            provided by `index_iter`. The function should also set the
  //            metaindex_handle.offset() to `metaindex_offset`.
  //
  // Expected behavior:
  // - When Table::ApproximateOffsetOf(..) creates the index iterator, it
  //   must get `index_iter` (so we can control Valid()/value()).
  // - metaindex_handle.offset() must return `metaindex_offset`.
  //
  // You can implement this by using your existing testing peer/builder
  // that constructs a tiny in-memory Table and injects a custom index iterator.
  leveldb::Table* MakeTableWithIndexIterator(MockIterator* index_iter,
                                             uint64_t metaindex_offset) {
    // ---- BEGIN PROJECT-SPECIFIC SEAM ----
    // Replace this with your existing helper (e.g., TableTestPeer::Make(...))
    // or a tiny builder that wires index_iter into the Table.
    // For now, we make this explicit so the compile unit is clear.
    (void)index_iter;
    (void)metaindex_offset;
    return nullptr;  // <-- Replace with concrete Table*
    // ---- END PROJECT-SPECIFIC SEAM ----
  }

  // TODO(you): Clean up Table* created by MakeTableWithIndexIterator.
  void DestroyTable(leveldb::Table* t) {
    // Replace with your project’s cleanup if needed
    delete t;
  }
};

// ------------------------------
// Tests
// ------------------------------

TEST_F(TableApproximateOffsetOfTest_424, ReturnsDecodedHandleOffset_WhenIndexValidAndDecodes_424) {
  // Arrange
  MockIterator* mock_iter = new MockIterator();

  // Expect Seek is called with the given key (observable interaction)
  const leveldb::Slice seek_key("k1");
  EXPECT_CALL(*mock_iter, Seek(seek_key));

  // Valid index entry
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(true));

  // Provide a value Slice that decodes to a BlockHandle whose offset is 12345
  std::string encoded;
  auto value_slice = EncodeHandle(/*offset=*/12345u, /*size=*/111u, &encoded);
  EXPECT_CALL(*mock_iter, value()).WillOnce(Return(value_slice));

  // metaindex fallback offset (should NOT be used in this test)
  const uint64_t metaindex_fallback = 999u;

  // Build a Table that will use our mock iterator for the index block
  leveldb::Table* table = MakeTableWithIndexIterator(mock_iter, metaindex_fallback);
  ASSERT_NE(table, nullptr) << "Test seam not wired: provide a Table with injected index iterator.";

  // Act
  uint64_t got = table->ApproximateOffsetOf(seek_key);

  // Assert
  EXPECT_EQ(got, 12345u);

  // Cleanup
  DestroyTable(table);
}

TEST_F(TableApproximateOffsetOfTest_424, FallsBackToMetaindexOffset_WhenIndexInvalid_424) {
  // Arrange
  MockIterator* mock_iter = new MockIterator();

  const leveldb::Slice seek_key("zzz");
  EXPECT_CALL(*mock_iter, Seek(seek_key));
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(false));

  // metaindex fallback offset SHOULD be returned
  const uint64_t metaindex_fallback = 54321u;

  leveldb::Table* table = MakeTableWithIndexIterator(mock_iter, metaindex_fallback);
  ASSERT_NE(table, nullptr) << "Test seam not wired: provide a Table with injected index iterator.";

  // Act
  uint64_t got = table->ApproximateOffsetOf(seek_key);

  // Assert
  EXPECT_EQ(got, metaindex_fallback);

  // Cleanup
  DestroyTable(table);
}

TEST_F(TableApproximateOffsetOfTest_424, FallsBackToMetaindexOffset_WhenDecodeFails_424) {
  // Arrange
  MockIterator* mock_iter = new MockIterator();

  const leveldb::Slice seek_key("mid");
  EXPECT_CALL(*mock_iter, Seek(seek_key));
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(Return(true));

  // Make DecodeFrom fail by returning an obviously invalid/empty slice
  EXPECT_CALL(*mock_iter, value()).WillOnce(Return(leveldb::Slice()));

  const uint64_t metaindex_fallback = 777u;

  leveldb::Table* table = MakeTableWithIndexIterator(mock_iter, metaindex_fallback);
  ASSERT_NE(table, nullptr) << "Test seam not wired: provide a Table with injected index iterator.";

  // Act
  uint64_t got = table->ApproximateOffsetOf(seek_key);

  // Assert
  EXPECT_EQ(got, metaindex_fallback);

  // Cleanup
  DestroyTable(table);
}

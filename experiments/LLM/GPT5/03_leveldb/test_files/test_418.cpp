// File: table_rep_dtor_test_418.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Minimal forward declarations to match the interface we exercise.
// We are NOT re-implementing internal logic—only creating enough surface
// to let us observe destructor-triggered interactions.
namespace leveldb {

// External collaborators we only need as polymorphic bases so that
// deleting through these pointers calls our test-double destructors.
class FilterBlockReader {
public:
  virtual ~FilterBlockReader() = default;
};

class Block {
public:
  virtual ~Block() = default;
};

// The nested Rep we are testing (public members per the provided interface).
class Table {
public:
  struct Rep {
    // Public per the known/inferred dependency block.
    // We only touch the members we need for observable behavior.
    FilterBlockReader* filter = nullptr;
    const char*        filter_data = nullptr;
    Block*             index_block = nullptr;

    ~Rep(); // Implemented in table/table.cc: deletes filter, filter_data[], index_block
  };
};

}  // namespace leveldb

// ---------- Test doubles to observe deletions ----------
namespace {

class TestFilterBlockReader : public leveldb::FilterBlockReader {
public:
  explicit TestFilterBlockReader(bool* destroyed_flag) : destroyed_flag_(destroyed_flag) {}
  ~TestFilterBlockReader() override {
    if (destroyed_flag_) *destroyed_flag_ = true;
  }
private:
  bool* destroyed_flag_;
};

class TestBlock : public leveldb::Block {
public:
  explicit TestBlock(bool* destroyed_flag) : destroyed_flag_(destroyed_flag) {}
  ~TestBlock() override {
    if (destroyed_flag_) *destroyed_flag_ = true;
  }
private:
  bool* destroyed_flag_;
};

}  // namespace

// ---------- Tests ----------

TEST(TableRepDestructor_418, DeletesFilterAndIndexBlock_418) {
  using leveldb::Table;

  bool filter_deleted = false;
  bool block_deleted  = false;

  // Allocate Rep dynamically so its destructor runs via `delete`.
  auto* rep = new Table::Rep();

  // Install test doubles to observe deletion.
  rep->filter      = new TestFilterBlockReader(&filter_deleted);
  rep->index_block = new TestBlock(&block_deleted);

  // Give filter_data a real allocation; we can’t directly assert delete[],
  // but this ensures the destructor tolerates non-null array memory.
  rep->filter_data = new char[7]{'f','i','l','t','e','r','\0'};

  // Act: Destroy the Rep.
  delete rep;

  // Assert: both collaborators were deleted.
  EXPECT_TRUE(filter_deleted);
  EXPECT_TRUE(block_deleted);
}

TEST(TableRepDestructor_418, HandlesNullMembers_418) {
  using leveldb::Table;

  // All members left null; deleting should be safe (no crash).
  auto* rep = new Table::Rep();
  // No assignments -> all nullptr by default (per our default-initialized members).
  // Act & Assert: Delete should not crash.
  EXPECT_NO_THROW(delete rep);
}

TEST(TableRepDestructor_418, DeletesOnlyPresentPointers_418) {
  using leveldb::Table;

  bool filter_deleted = false;
  bool block_deleted  = false;

  auto* rep = new Table::Rep();

  // Provide only the filter; leave index_block as nullptr.
  rep->filter = new TestFilterBlockReader(&filter_deleted);
  rep->index_block = nullptr;

  // Also set filter_data to ensure non-null array is tolerated.
  rep->filter_data = new char[1]{'\0'};

  delete rep;

  // The filter must be deleted; index_block was nullptr, so its flag stays false.
  EXPECT_TRUE(filter_deleted);
  EXPECT_FALSE(block_deleted);
}

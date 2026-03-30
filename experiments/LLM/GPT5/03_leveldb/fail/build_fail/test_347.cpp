// delete_entry_test_347.cc
#include <gtest/gtest.h>
#include <memory>
#include <string>

//
// Minimal stubs to satisfy the interface used by DeleteEntry.
// We only provide what's necessary to compile and observe destructor side effects.
//
namespace leveldb {

class RandomAccessFile {
public:
  virtual ~RandomAccessFile() = default;
};

class Table {
public:
  virtual ~Table() = default;
};

class Slice {
public:
  Slice() = default;
  explicit Slice(const std::string&) {}
};

} // namespace leveldb

// Include the implementation under test so the internal-linkage (static) symbol is visible here.
#include "db/table_cache.cc"  // contains: struct TableAndFile and static void DeleteEntry(...)

namespace {

using namespace leveldb;

// Test helpers: objects that flip a flag when destroyed.
class FlaggedRAF : public RandomAccessFile {
public:
  explicit FlaggedRAF(bool* flag) : flag_(flag) {}
  ~FlaggedRAF() override { if (flag_) *flag_ = true; }
private:
  bool* flag_;
};

class FlaggedTable : public Table {
public:
  explicit FlaggedTable(bool* flag) : flag_(flag) {}
  ~FlaggedTable() override { if (flag_) *flag_ = true; }
private:
  bool* flag_;
};

// ---------------------- TESTS ----------------------

TEST(DeleteEntryTest_347, DeletesBothMembers_347) {
  bool file_deleted = false;
  bool table_deleted = false;

  auto* tf = new TableAndFile;
  tf->file = new FlaggedRAF(&file_deleted);
  tf->table = new FlaggedTable(&table_deleted);

  // Key should be irrelevant to deletion behavior; use any non-empty slice.
  DeleteEntry(Slice("unused-key"), tf);

  EXPECT_TRUE(file_deleted)  << "RandomAccessFile should be deleted";
  EXPECT_TRUE(table_deleted) << "Table should be deleted";
  // We don't assert on 'tf' itself; its deallocation is not directly observable here.
}

TEST(DeleteEntryTest_347, HandlesNullTableOnlyFileDeleted_347) {
  bool file_deleted = false;

  auto* tf = new TableAndFile;
  tf->file = new FlaggedRAF(&file_deleted);
  tf->table = nullptr;

  DeleteEntry(Slice("ignored"), tf);

  EXPECT_TRUE(file_deleted)  << "RandomAccessFile should be deleted when table is nullptr";
  // No crash expected with table == nullptr.
}

TEST(DeleteEntryTest_347, HandlesNullFileOnlyTableDeleted_347) {
  bool table_deleted = false;

  auto* tf = new TableAndFile;
  tf->file = nullptr;
  tf->table = new FlaggedTable(&table_deleted);

  DeleteEntry(Slice("ignored"), tf);

  EXPECT_TRUE(table_deleted) << "Table should be deleted when file is nullptr";
  // No crash expected with file == nullptr.
}

TEST(DeleteEntryTest_347, HandlesBothNull_347) {
  auto* tf = new TableAndFile;
  tf->file = nullptr;
  tf->table = nullptr;

  // Should not crash even if both pointers are null.
  DeleteEntry(Slice("ignored"), tf);

  SUCCEED();
}

} // namespace

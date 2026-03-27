// File: db/db_impl_test_internal_iterator_304.cc

#include "db/db_impl.h"

#include "gtest/gtest.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"

#include <memory>
#include <string>

using leveldb::DBImpl;
using leveldb::Env;
using leveldb::Iterator;
using leveldb::Options;
using leveldb::Slice;

class DBImplInternalIterTest_304 : public ::testing::Test {
protected:
  void SetUp() override {
    Options options;
    // Keep options minimal; treat DBImpl as a black box.
    // We only need a valid dbname path for construction.
    dbname_ = testing::TempDir() + "dbimpl_internal_iter_test_304";
    // Ensure the directory exists so any filesystem usage is safe.
    Env::Default()->CreateDir(dbname_);
    db_.reset(new DBImpl(options, dbname_));
  }

  void TearDown() override {
    // Best-effort cleanup; ignore errors to keep test black-box.
    // Files may not exist if DBImpl didn't create any.
    Env::Default()->DeleteDir(dbname_);
  }

  std::unique_ptr<DBImpl> db_;
  std::string dbname_;
};

// [304] Basic: returns a non-null iterator pointer
TEST_F(DBImplInternalIterTest_304, ReturnsNonNull_304) {
  Iterator* it = db_->TEST_NewInternalIterator();
  ASSERT_NE(it, nullptr) << "TEST_NewInternalIterator should return a non-null iterator";
  delete it;
}

// [304] Empty state: SeekToFirst yields invalid iterator
TEST_F(DBImplInternalIterTest_304, EmptyIteratorIsInvalidAfterSeekToFirst_304) {
  std::unique_ptr<Iterator> it(db_->TEST_NewInternalIterator());
  ASSERT_NE(it.get(), nullptr);

  it->SeekToFirst();
  EXPECT_FALSE(it->Valid()) << "On an empty DB, iterator should be invalid after SeekToFirst()";
}

// [304] Empty state: common navigation methods are safe and keep iterator invalid
TEST_F(DBImplInternalIterTest_304, NavigationOnEmptyKeepsInvalid_304) {
  std::unique_ptr<Iterator> it(db_->TEST_NewInternalIterator());
  ASSERT_NE(it.get(), nullptr);

  // Attempt various moves and seeks on an assumed-empty structure.
  it->Seek(Slice("key"));
  EXPECT_FALSE(it->Valid()) << "Seek on empty should not become valid";

  it->Next();
  EXPECT_FALSE(it->Valid()) << "Next on empty should remain invalid";

  it->Prev();
  EXPECT_FALSE(it->Valid()) << "Prev on empty should remain invalid";
}

// [304] Multiple calls: iterators are distinct instances
TEST_F(DBImplInternalIterTest_304, MultipleCallsReturnDistinctInstances_304) {
  std::unique_ptr<Iterator> it1(db_->TEST_NewInternalIterator());
  std::unique_ptr<Iterator> it2(db_->TEST_NewInternalIterator());

  ASSERT_NE(it1.get(), nullptr);
  ASSERT_NE(it2.get(), nullptr);
  EXPECT_NE(it1.get(), it2.get()) << "Each call should return a distinct iterator instance";
}

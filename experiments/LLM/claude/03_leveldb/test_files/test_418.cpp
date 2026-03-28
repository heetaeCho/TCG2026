#include "gtest/gtest.h"
#include "leveldb/table.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/iterator.h"
#include "leveldb/filter_policy.h"
#include "table/filter_block.h"
#include "table/block.h"
#include "table/format.h"
#include "util/coding.h"

#include <string>
#include <vector>
#include <cstring>

namespace leveldb {

// Helper: build a small valid SSTable in memory so we can open it via Table::Open
class TableTestHelper {
 public:
  // Write a simple table with some key-value pairs to a file
  static Status BuildTable(Env* env, const std::string& fname,
                           const std::vector<std::pair<std::string, std::string>>& kvs,
                           const Options& options) {
    WritableFile* wfile;
    Status s = env->NewWritableFile(fname, &wfile);
    if (!s.ok()) return s;

    TableBuilder builder(options, wfile);
    for (const auto& kv : kvs) {
      builder.Add(kv.first, kv.second);
    }
    s = builder.Finish();
    if (s.ok()) {
      s = wfile->Close();
    }
    delete wfile;
    return s;
  }
};

class TableTest_418 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    fname_ = testing::TempDir() + "/table_test_418.sst";
  }

  void TearDown() override {
    env_->RemoveFile(fname_);
  }

  Env* env_;
  std::string fname_;
  Options options_;
};

// Test that Table::Open succeeds with a valid table file
TEST_F(TableTest_418, OpenValidTable_418) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  Status s = Table::Open(options_, rfile, file_size, &table);
  ASSERT_TRUE(s.ok());
  ASSERT_NE(table, nullptr);

  delete table;
}

// Test that Table::Open fails with an empty file (size 0)
TEST_F(TableTest_418, OpenEmptyFileFails_418) {
  WritableFile* wfile;
  ASSERT_TRUE(env_->NewWritableFile(fname_, &wfile).ok());
  ASSERT_TRUE(wfile->Close().ok());
  delete wfile;

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  Status s = Table::Open(options_, rfile, 0, &table);
  EXPECT_FALSE(s.ok());
  // table should remain nullptr on failure
  delete table;  // safe even if nullptr
}

// Test that Table::Open fails with a file that is too small to hold footer
TEST_F(TableTest_418, OpenTooSmallFileFails_418) {
  WritableFile* wfile;
  ASSERT_TRUE(env_->NewWritableFile(fname_, &wfile).ok());
  // Write some garbage that's smaller than a footer
  std::string garbage(10, 'x');
  ASSERT_TRUE(wfile->Append(garbage).ok());
  ASSERT_TRUE(wfile->Close().ok());
  delete wfile;

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  Status s = Table::Open(options_, rfile, 10, &table);
  EXPECT_FALSE(s.ok());
  delete table;
}

// Test NewIterator returns a valid iterator that can iterate over all entries
TEST_F(TableTest_418, NewIteratorBasic_418) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
      {"ccc", "val_c"},
  };
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  ASSERT_TRUE(Table::Open(options_, rfile, file_size, &table).ok());

  ReadOptions ropts;
  Iterator* iter = table->NewIterator(ropts);
  ASSERT_NE(iter, nullptr);

  // Iterate forward and verify
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    EXPECT_EQ(iter->key().ToString(), kvs[count].first);
    EXPECT_EQ(iter->value().ToString(), kvs[count].second);
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 3);
  EXPECT_TRUE(iter->status().ok());

  delete iter;
  delete table;
}

// Test NewIterator on an empty table
TEST_F(TableTest_418, NewIteratorEmptyTable_418) {
  std::vector<std::pair<std::string, std::string>> kvs;
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  ASSERT_TRUE(Table::Open(options_, rfile, file_size, &table).ok());

  ReadOptions ropts;
  Iterator* iter = table->NewIterator(ropts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete table;
}

// Test Seek functionality via the iterator
TEST_F(TableTest_418, IteratorSeek_418) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"apple", "1"},
      {"banana", "2"},
      {"cherry", "3"},
      {"date", "4"},
      {"elderberry", "5"},
  };
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  ASSERT_TRUE(Table::Open(options_, rfile, file_size, &table).ok());

  ReadOptions ropts;
  Iterator* iter = table->NewIterator(ropts);

  // Seek to existing key
  iter->Seek("cherry");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "cherry");
  EXPECT_EQ(iter->value().ToString(), "3");

  // Seek to key between existing keys
  iter->Seek("cat");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "cherry");

  // Seek past all keys
  iter->Seek("zzz");
  EXPECT_FALSE(iter->Valid());

  // Seek before all keys
  iter->Seek("a");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "apple");

  delete iter;
  delete table;
}

// Test SeekToLast and Prev
TEST_F(TableTest_418, IteratorSeekToLastAndPrev_418) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "v1"},
      {"key2", "v2"},
      {"key3", "v3"},
  };
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  ASSERT_TRUE(Table::Open(options_, rfile, file_size, &table).ok());

  ReadOptions ropts;
  Iterator* iter = table->NewIterator(ropts);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key3");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete table;
}

// Test ApproximateOffsetOf for various keys
TEST_F(TableTest_418, ApproximateOffsetOf_418) {
  std::vector<std::pair<std::string, std::string>> kvs;
  // Create a table with some entries
  for (int i = 0; i < 100; i++) {
    char key[32];
    snprintf(key, sizeof(key), "key%06d", i);
    char val[100];
    snprintf(val, sizeof(val), "value%06d_padding_to_make_it_bigger", i);
    kvs.push_back({std::string(key), std::string(val)});
  }
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  ASSERT_TRUE(Table::Open(options_, rfile, file_size, &table).ok());

  // Offset for a key before the first entry should be 0 or small
  uint64_t offset_before = table->ApproximateOffsetOf("a");
  EXPECT_LE(offset_before, file_size);

  // Offset for a key after all entries should be close to file size
  uint64_t offset_after = table->ApproximateOffsetOf("z");
  EXPECT_LE(offset_after, file_size);

  // Offsets should be non-decreasing
  uint64_t offset_mid = table->ApproximateOffsetOf("key000050");
  EXPECT_GE(offset_mid, offset_before);
  EXPECT_LE(offset_mid, offset_after);

  delete table;
}

// Test with a single key-value pair
TEST_F(TableTest_418, SingleEntry_418) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"only_key", "only_value"},
  };
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  ASSERT_TRUE(Table::Open(options_, rfile, file_size, &table).ok());

  ReadOptions ropts;
  Iterator* iter = table->NewIterator(ropts);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "only_key");
  EXPECT_EQ(iter->value().ToString(), "only_value");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "only_key");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete table;
}

// Test with filter policy (bloom filter)
TEST_F(TableTest_418, OpenWithFilterPolicy_418) {
  const FilterPolicy* policy = NewBloomFilterPolicy(10);
  options_.filter_policy = policy;

  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "1"},
      {"beta", "2"},
      {"gamma", "3"},
  };
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  ASSERT_TRUE(Table::Open(options_, rfile, file_size, &table).ok());

  ReadOptions ropts;
  Iterator* iter = table->NewIterator(ropts);

  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 3);

  delete iter;
  delete table;
  delete policy;
}

// Test that corrupted data in the file causes Open to fail
TEST_F(TableTest_418, OpenCorruptedFile_418) {
  // First build a valid table
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
  };
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  // Now corrupt the file by overwriting footer area
  std::string corrupted_fname = fname_ + ".corrupt";
  {
    RandomAccessFile* rfile;
    ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

    // Read the entire file
    std::string contents(file_size, '\0');
    Slice result;
    ASSERT_TRUE(rfile->Read(0, file_size, &result, &contents[0]).ok());
    delete rfile;

    // Corrupt the last few bytes (footer area)
    for (size_t i = 0; i < std::min<size_t>(48, contents.size()); i++) {
      contents[contents.size() - 1 - i] = 0xFF;
    }

    WritableFile* wfile;
    ASSERT_TRUE(env_->NewWritableFile(corrupted_fname, &wfile).ok());
    ASSERT_TRUE(wfile->Append(Slice(contents)).ok());
    ASSERT_TRUE(wfile->Close().ok());
    delete wfile;
  }

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(corrupted_fname, &rfile).ok());

  Table* table = nullptr;
  Status s = Table::Open(options_, rfile, file_size, &table);
  // With corrupted footer, Open should fail
  EXPECT_FALSE(s.ok());
  if (table == nullptr) {
    delete rfile;
  } else {
    delete table;
  }

  env_->RemoveFile(corrupted_fname);
}

// Test InternalGet via the public interface (if accessible)
// Table::InternalGet is used internally but we test observable behavior through iteration
TEST_F(TableTest_418, LargeNumberOfEntries_418) {
  std::vector<std::pair<std::string, std::string>> kvs;
  for (int i = 0; i < 1000; i++) {
    char key[32], val[32];
    snprintf(key, sizeof(key), "k%06d", i);
    snprintf(val, sizeof(val), "v%06d", i);
    kvs.push_back({std::string(key), std::string(val)});
  }
  ASSERT_TRUE(TableTestHelper::BuildTable(env_, fname_, kvs, options_).ok());

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname_, &file_size).ok());

  RandomAccessFile* rfile;
  ASSERT_TRUE(env_->NewRandomAccessFile(fname_, &rfile).ok());

  Table* table = nullptr;
  ASSERT_TRUE(Table::Open(options_, rfile, file_size, &table).ok());

  ReadOptions ropts;
  Iterator* iter = table->NewIterator(ropts);

  // Count all entries
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 1000);
  EXPECT_TRUE(iter->status().ok());

  // Verify random seeks
  iter->Seek("k000500");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "k000500");
  EXPECT_EQ(iter->value().ToString(), "v000500");

  delete iter;
  delete table;
}

}  // namespace leveldb

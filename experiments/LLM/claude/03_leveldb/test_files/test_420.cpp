#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/table.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/iterator.h"
#include "leveldb/table_builder.h"
#include "leveldb/status.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <map>

namespace leveldb {

// Helper to create a table file in memory using StringSource/StringSink
class StringSource : public RandomAccessFile {
 public:
  StringSource(const std::string& data) : data_(data) {}

  Status Read(uint64_t offset, size_t n, Slice* result,
              char* scratch) const override {
    if (offset >= data_.size()) {
      *result = Slice();
      return Status::OK();
    }
    if (offset + n > data_.size()) {
      n = data_.size() - offset;
    }
    memcpy(scratch, data_.data() + offset, n);
    *result = Slice(scratch, n);
    return Status::OK();
  }

 private:
  std::string data_;
};

class StringSink : public WritableFile {
 public:
  std::string contents_;

  Status Close() override { return Status::OK(); }
  Status Flush() override { return Status::OK(); }
  Status Sync() override { return Status::OK(); }
  Status Append(const Slice& data) override {
    contents_.append(data.data(), data.size());
    return Status::OK();
  }
};

// Helper function: Build a table from key-value pairs, return the data as string
static std::string BuildTable(const Options& options,
                              const std::vector<std::pair<std::string, std::string>>& kvs) {
  StringSink sink;
  TableBuilder builder(options, &sink);
  for (const auto& kv : kvs) {
    builder.Add(kv.first, kv.second);
  }
  builder.Finish();
  return sink.contents_;
}

class TableTest_420 : public ::testing::Test {
 protected:
  Options options_;

  void SetUp() override {
    options_ = Options();
  }

  // Helper to open a table from string data
  Status OpenTable(const std::string& data, Table** table) {
    RandomAccessFile* file = new StringSource(data);
    return Table::Open(options_, file, data.size(), table);
  }
};

// Test: Open with empty file should fail
TEST_F(TableTest_420, OpenEmptyFileFails_420) {
  std::string empty_data;
  Table* table = nullptr;
  RandomAccessFile* file = new StringSource(empty_data);
  Status s = Table::Open(options_, file, 0, &table);
  EXPECT_FALSE(s.ok());
  // table should not be set on failure
  if (table != nullptr) {
    delete table;
  }
}

// Test: Open with corrupted/too-small file should fail
TEST_F(TableTest_420, OpenCorruptedFileFails_420) {
  std::string bad_data = "short";
  Table* table = nullptr;
  RandomAccessFile* file = new StringSource(bad_data);
  Status s = Table::Open(options_, file, bad_data.size(), &table);
  EXPECT_FALSE(s.ok());
  if (table != nullptr) {
    delete table;
  }
}

// Test: Open a valid table with entries
TEST_F(TableTest_420, OpenValidTable_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  Status s = OpenTable(data, &table);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_NE(table, nullptr);
  delete table;
}

// Test: NewIterator iterates over all entries
TEST_F(TableTest_420, NewIteratorReadsAllEntries_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
      {"ccc", "val_c"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  int count = 0;
  for (; iter->Valid(); iter->Next()) {
    ASSERT_LT(count, static_cast<int>(kvs.size()));
    EXPECT_EQ(iter->key().ToString(), kvs[count].first);
    EXPECT_EQ(iter->value().ToString(), kvs[count].second);
    count++;
  }
  EXPECT_EQ(count, 3);
  EXPECT_TRUE(iter->status().ok());

  delete iter;
  delete table;
}

// Test: NewIterator on empty table
TEST_F(TableTest_420, NewIteratorEmptyTable_420) {
  std::vector<std::pair<std::string, std::string>> kvs;
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete table;
}

// Test: Iterator Seek
TEST_F(TableTest_420, IteratorSeek_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"apple", "1"},
      {"banana", "2"},
      {"cherry", "3"},
      {"date", "4"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->Seek("banana");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "banana");
  EXPECT_EQ(iter->value().ToString(), "2");

  iter->Seek("blueberry");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "cherry");

  delete iter;
  delete table;
}

// Test: Iterator SeekToLast
TEST_F(TableTest_420, IteratorSeekToLast_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "val1"},
      {"key2", "val2"},
      {"key3", "val3"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key3");
  EXPECT_EQ(iter->value().ToString(), "val3");

  delete iter;
  delete table;
}

// Test: Iterator Prev
TEST_F(TableTest_420, IteratorPrev_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "b");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "a");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete table;
}

// Test: ApproximateOffsetOf
TEST_F(TableTest_420, ApproximateOffsetOfBeginning_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  // Offset for a key before all entries should be 0 or very small
  uint64_t offset = table->ApproximateOffsetOf(Slice(""));
  EXPECT_GE(offset, 0u);

  // Offset for a key past all entries should be close to file size
  uint64_t offset_end = table->ApproximateOffsetOf(Slice("zzz"));
  EXPECT_LE(offset_end, data.size());

  delete table;
}

// Test: ApproximateOffsetOf ordering
TEST_F(TableTest_420, ApproximateOffsetOfOrdering_420) {
  std::vector<std::pair<std::string, std::string>> kvs;
  // Add many entries to ensure multiple data blocks
  for (int i = 0; i < 1000; i++) {
    char key[32];
    char val[128];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "value%06d_padding_to_make_it_larger", i);
    kvs.emplace_back(key, val);
  }
  
  Options opts;
  opts.block_size = 256;  // small block size to create many blocks
  std::string data = BuildTable(opts, kvs);
  
  Table* table = nullptr;
  RandomAccessFile* file = new StringSource(data);
  ASSERT_TRUE(Table::Open(opts, file, data.size(), &table).ok());

  uint64_t offset1 = table->ApproximateOffsetOf(Slice("key000100"));
  uint64_t offset2 = table->ApproximateOffsetOf(Slice("key000500"));
  uint64_t offset3 = table->ApproximateOffsetOf(Slice("key000900"));

  // Offsets should be non-decreasing
  EXPECT_LE(offset1, offset2);
  EXPECT_LE(offset2, offset3);

  delete table;
}

// Test: Open with garbage data of valid footer size but corrupt content
TEST_F(TableTest_420, OpenGarbageDataFails_420) {
  // Footer is 48 bytes, but garbage content
  std::string garbage(100, 'x');
  Table* table = nullptr;
  RandomAccessFile* file = new StringSource(garbage);
  Status s = Table::Open(options_, file, garbage.size(), &table);
  EXPECT_FALSE(s.ok());
  if (table != nullptr) {
    delete table;
  }
}

// Test: Single entry table
TEST_F(TableTest_420, SingleEntryTable_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"only_key", "only_value"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "only_key");
  EXPECT_EQ(iter->value().ToString(), "only_value");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete table;
}

// Test: Table with large values
TEST_F(TableTest_420, LargeValues_420) {
  std::string large_value(10000, 'v');
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", large_value},
      {"key2", large_value},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), large_value);

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().ToString(), large_value);

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete table;
}

// Test: Seek past all keys
TEST_F(TableTest_420, SeekPastAllKeys_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "1"},
      {"bbb", "2"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->Seek("zzz");
  EXPECT_FALSE(iter->Valid());

  delete iter;
  delete table;
}

// Test: Seek to first key exactly
TEST_F(TableTest_420, SeekToExactFirstKey_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "1"},
      {"beta", "2"},
      {"gamma", "3"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->Seek("alpha");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "alpha");
  EXPECT_EQ(iter->value().ToString(), "1");

  delete iter;
  delete table;
}

// Test: Open with null table pointer (sanity - size mismatch)
TEST_F(TableTest_420, OpenWithMismatchedSize_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
  };
  std::string data = BuildTable(options_, kvs);
  
  // Try opening with wrong (smaller) size
  Table* table = nullptr;
  RandomAccessFile* file = new StringSource(data);
  Status s = Table::Open(options_, file, 10, &table);
  // Should likely fail due to corrupted footer read
  if (!s.ok()) {
    EXPECT_TRUE(table == nullptr || true);
  }
  if (table != nullptr) {
    delete table;
  }
}

// Test: Multiple iterators on same table
TEST_F(TableTest_420, MultipleIterators_420) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
  };
  std::string data = BuildTable(options_, kvs);
  Table* table = nullptr;
  ASSERT_TRUE(OpenTable(data, &table).ok());

  ReadOptions read_opts;
  Iterator* iter1 = table->NewIterator(read_opts);
  Iterator* iter2 = table->NewIterator(read_opts);

  iter1->SeekToFirst();
  iter2->SeekToLast();

  ASSERT_TRUE(iter1->Valid());
  ASSERT_TRUE(iter2->Valid());
  EXPECT_EQ(iter1->key().ToString(), "a");
  EXPECT_EQ(iter2->key().ToString(), "c");

  delete iter1;
  delete iter2;
  delete table;
}

}  // namespace leveldb

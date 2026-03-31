#include "gtest/gtest.h"
#include "leveldb/table.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "table/block.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper to build a simple valid SSTable in memory
class TableTestHelper {
 public:
  // Build a minimal valid table with the given key-value pairs
  static std::string BuildTable(const Options& options,
                                const std::vector<std::pair<std::string, std::string>>& kvs) {
    std::string result;
    WritableFile* wfile = nullptr;
    Env::Default()->NewWritableFile("/dev/null", &wfile);  // dummy, we use StringSink
    // We'll use TableBuilder via the public API
    // But since we need a string, we use a custom approach
    // Actually, let's use the test utilities pattern
    return result;
  }
};

// We'll use a StringSource that implements RandomAccessFile for testing
class StringSource : public RandomAccessFile {
 public:
  StringSource(const std::string& contents)
      : contents_(contents) {}

  Status Read(uint64_t offset, size_t n, Slice* result,
              char* scratch) const override {
    if (offset >= contents_.size()) {
      *result = Slice();
      return Status::OK();
    }
    if (offset + n > contents_.size()) {
      n = contents_.size() - offset;
    }
    std::memcpy(scratch, contents_.data() + offset, n);
    *result = Slice(scratch, n);
    return Status::OK();
  }

  std::string GetName() const override { return "[string]"; }

 private:
  std::string contents_;
};

// StringSink that implements WritableFile
class StringSink : public WritableFile {
 public:
  explicit StringSink(std::string* dst) : dst_(dst) {}

  Status Close() override { return Status::OK(); }
  Status Flush() override { return Status::OK(); }
  Status Sync() override { return Status::OK(); }
  Status Append(const Slice& data) override {
    dst_->append(data.data(), data.size());
    return Status::OK();
  }
  std::string GetName() const override { return "[string]"; }

 private:
  std::string* dst_;
};

}  // namespace leveldb

// Need TableBuilder to create test tables
#include "leveldb/table_builder.h"

namespace leveldb {

class TableTest_423 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = Options();
    options_.compression = kNoCompression;
  }

  // Build an SSTable from key-value pairs and return a Table*
  Table* BuildAndOpenTable(
      const std::vector<std::pair<std::string, std::string>>& kvs) {
    std::string table_data;
    StringSink sink(&table_data);
    TableBuilder builder(options_, &sink);
    for (const auto& kv : kvs) {
      builder.Add(kv.first, kv.second);
    }
    Status s = builder.Finish();
    EXPECT_TRUE(s.ok()) << s.ToString();

    table_contents_.push_back(table_data);
    StringSource* source = new StringSource(table_contents_.back());
    sources_.push_back(source);

    Table* table = nullptr;
    s = Table::Open(options_, source, table_data.size(), &table);
    EXPECT_TRUE(s.ok()) << s.ToString();
    tables_.push_back(table);
    return table;
  }

  void TearDown() override {
    for (auto* t : tables_) {
      delete t;
    }
    // sources are owned by callers via RandomAccessFile*, but Table doesn't
    // take ownership in all implementations. We'll be careful.
    // Actually Table::Open doesn't take ownership of the file, so we delete.
    // But Table may still reference the file in its destructor... 
    // Let's not delete sources here; they need to outlive the table.
    // Actually, in the standard leveldb, Table does NOT own the file.
    // But the table's destructor doesn't close/delete the file.
    // The sources are allocated with new, so we should delete after tables.
    for (auto* s : sources_) {
      delete s;
    }
  }

  Options options_;
  std::vector<Table*> tables_;
  std::vector<StringSource*> sources_;
  std::vector<std::string> table_contents_;
};

// Test: Open a table successfully with valid data
TEST_F(TableTest_423, OpenValidTable_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);
}

// Test: Open with zero-size file should fail
TEST_F(TableTest_423, OpenEmptyFileFails_423) {
  std::string empty_data;
  StringSource* source = new StringSource(empty_data);
  Table* table = nullptr;
  Status s = Table::Open(options_, source, 0, &table);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(table, nullptr);
  delete source;
}

// Test: Open with truncated/corrupt data should fail
TEST_F(TableTest_423, OpenCorruptDataFails_423) {
  std::string corrupt_data = "this is not a valid sstable";
  StringSource* source = new StringSource(corrupt_data);
  Table* table = nullptr;
  Status s = Table::Open(options_, source, corrupt_data.size(), &table);
  EXPECT_FALSE(s.ok());
  EXPECT_EQ(table, nullptr);
  delete source;
}

// Test: NewIterator returns a valid iterator
TEST_F(TableTest_423, NewIteratorReturnsValidIterator_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"aaa", "val_a"},
      {"bbb", "val_b"},
      {"ccc", "val_c"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test: Iterate over all entries and verify them
TEST_F(TableTest_423, IterateAllEntries_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
      {"key2", "value2"},
      {"key3", "value3"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

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
}

// Test: SeekToLast and iterate backward
TEST_F(TableTest_423, IterateBackward_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"alpha", "1"},
      {"beta", "2"},
      {"gamma", "3"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "gamma");
  EXPECT_EQ(iter->value().ToString(), "3");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "beta");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "alpha");

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Seek to a specific key
TEST_F(TableTest_423, SeekToSpecificKey_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"apple", "1"},
      {"banana", "2"},
      {"cherry", "3"},
      {"date", "4"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->Seek("banana");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "banana");
  EXPECT_EQ(iter->value().ToString(), "2");
  delete iter;
}

// Test: Seek to a key that doesn't exist (should land on next key)
TEST_F(TableTest_423, SeekToNonExistentKey_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"c", "3"},
      {"e", "5"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "c");
  delete iter;
}

// Test: Seek past the last key
TEST_F(TableTest_423, SeekPastEnd_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->Seek("z");
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test: Empty table iteration
TEST_F(TableTest_423, EmptyTableIteration_423) {
  std::vector<std::pair<std::string, std::string>> kvs;
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: ApproximateOffsetOf returns reasonable values
TEST_F(TableTest_423, ApproximateOffsetOf_423) {
  std::vector<std::pair<std::string, std::string>> kvs;
  // Create enough entries to potentially span multiple blocks
  for (int i = 0; i < 100; i++) {
    char key[32];
    char val[128];
    std::snprintf(key, sizeof(key), "key%06d", i);
    std::snprintf(val, sizeof(val), "value%06d_padding_to_make_it_longer", i);
    kvs.emplace_back(key, val);
  }
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  // Offset of first key should be small (near start)
  uint64_t offset_start = table->ApproximateOffsetOf("key000000");
  // Offset of last key should be larger
  uint64_t offset_end = table->ApproximateOffsetOf("key000099");
  // Offset past all keys should be at or near end
  uint64_t offset_past = table->ApproximateOffsetOf("key999999");

  EXPECT_LE(offset_start, offset_end);
  EXPECT_LE(offset_end, offset_past);
}

// Test: ApproximateOffsetOf for key before all entries
TEST_F(TableTest_423, ApproximateOffsetOfBeforeAll_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"bbb", "val1"},
      {"ccc", "val2"},
      {"ddd", "val3"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  uint64_t offset = table->ApproximateOffsetOf("aaa");
  // Should be at or near 0
  EXPECT_EQ(offset, 0u);
}

// Test: Single entry table
TEST_F(TableTest_423, SingleEntryTable_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"only_key", "only_value"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "only_key");
  EXPECT_EQ(iter->value().ToString(), "only_value");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Multiple iterators on the same table
TEST_F(TableTest_423, MultipleIterators_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "1"},
      {"b", "2"},
      {"c", "3"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter1 = table->NewIterator(read_opts);
  Iterator* iter2 = table->NewIterator(read_opts);
  ASSERT_NE(iter1, nullptr);
  ASSERT_NE(iter2, nullptr);

  iter1->SeekToFirst();
  iter2->SeekToLast();

  ASSERT_TRUE(iter1->Valid());
  ASSERT_TRUE(iter2->Valid());
  EXPECT_EQ(iter1->key().ToString(), "a");
  EXPECT_EQ(iter2->key().ToString(), "c");

  delete iter1;
  delete iter2;
}

// Test: Large number of entries
TEST_F(TableTest_423, LargeNumberOfEntries_423) {
  std::vector<std::pair<std::string, std::string>> kvs;
  const int N = 1000;
  for (int i = 0; i < N; i++) {
    char key[32];
    char val[32];
    std::snprintf(key, sizeof(key), "k%08d", i);
    std::snprintf(val, sizeof(val), "v%08d", i);
    kvs.emplace_back(key, val);
  }
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    ASSERT_LT(count, N);
    EXPECT_EQ(iter->key().ToString(), kvs[count].first);
    EXPECT_EQ(iter->value().ToString(), kvs[count].second);
    count++;
  }
  EXPECT_EQ(count, N);
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test: Open with file size mismatch (too large)
TEST_F(TableTest_423, OpenWithWrongFileSize_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "val1"},
  };
  std::string table_data;
  StringSink sink(&table_data);
  TableBuilder builder(options_, &sink);
  for (const auto& kv : kvs) {
    builder.Add(kv.first, kv.second);
  }
  ASSERT_TRUE(builder.Finish().ok());

  // Try opening with a size much larger than actual data
  StringSource* source = new StringSource(table_data);
  Table* table = nullptr;
  Status s = Table::Open(options_, source, table_data.size() + 10000, &table);
  // This may or may not succeed depending on implementation
  // but we test the behavior doesn't crash
  if (table != nullptr) {
    delete table;
  }
  delete source;
}

// Test: ReadOptions with verify_checksums
TEST_F(TableTest_423, IterateWithVerifyChecksums_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
      {"key2", "value2"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  read_opts.verify_checksums = true;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test: ReadOptions with fill_cache = false
TEST_F(TableTest_423, IterateWithoutFillCache_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", "value1"},
      {"key2", "value2"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  read_opts.fill_cache = false;
  Iterator* iter = table->NewIterator(read_opts);
  ASSERT_NE(iter, nullptr);

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, 2);
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

// Test: Seek to exact boundary keys
TEST_F(TableTest_423, SeekToFirstAndLastKeys_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"first", "1"},
      {"middle", "2"},
      {"last", "3"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  // Seek to first key exactly
  iter->Seek("first");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "first");

  // Seek to last key exactly
  iter->Seek("last");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "last");

  // Next should go to end (since "middle" < "last" in sort order... wait "last" < "middle")
  // Actually: "first" < "last" < "middle" in bytewise order
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "middle");

  iter->Next();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test: Values with empty strings
TEST_F(TableTest_423, EmptyValues_423) {
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"key1", ""},
      {"key2", ""},
      {"key3", "notempty"},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key1");
  EXPECT_EQ(iter->value().ToString(), "");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key2");
  EXPECT_EQ(iter->value().ToString(), "");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), "key3");
  EXPECT_EQ(iter->value().ToString(), "notempty");

  delete iter;
}

// Test: Large keys and values
TEST_F(TableTest_423, LargeKeysAndValues_423) {
  std::string large_key(1000, 'k');
  std::string large_value(10000, 'v');
  std::vector<std::pair<std::string, std::string>> kvs = {
      {large_key, large_value},
  };
  Table* table = BuildAndOpenTable(kvs);
  ASSERT_NE(table, nullptr);

  ReadOptions read_opts;
  Iterator* iter = table->NewIterator(read_opts);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ(iter->key().ToString(), large_key);
  EXPECT_EQ(iter->value().ToString(), large_value);

  iter->Next();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

}  // namespace leveldb

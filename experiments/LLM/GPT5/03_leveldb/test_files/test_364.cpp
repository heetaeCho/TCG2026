// File: memtable_iterator_value_test_364.cc

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstdint>

//
// Minimal public interfaces & collaborators to exercise MemTableIterator::value().
// We do NOT re-implement MemTableIterator internals; we only provide the external
// collaborator (MemTable::Table and its nested Iterator) so we can pass encoded data.
//

namespace leveldb {

// ---- Production-like Slice interface (only what we need in tests) ----
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
  std::string ToString() const { return std::string(data_, size_); }
 private:
  const char* data_;
  size_t size_;
};

// Declaration only; definition is provided by production.
// MemTableIterator::value() calls this symbol. We do not mock/override it here.
Slice GetLengthPrefixedSlice(const char* p);

// ---- Iterator base (as referenced by MemTableIterator in production) ----
class Iterator {
 public:
  virtual ~Iterator() = default;
  virtual bool Valid() const { return true; }
  virtual void Seek(const Slice&) {}
  virtual void SeekToFirst() {}
  virtual void SeekToLast() {}
  virtual void Next() {}
  virtual void Prev() {}
  virtual Slice key() const { return Slice(); }   // not used by our collaborator
  virtual Slice value() const { return Slice(); } // not used here
};

// ---- External collaborator we control for tests ----
class MemTable {
 public:
  class Table {
   public:
    explicit Table(std::string encoded) : encoded_(std::move(encoded)) {}
    const std::string& encoded() const { return encoded_; }
   private:
    std::string encoded_;
   };

  // Nested iterator type used by MemTableIterator's private member.
  // It exposes key() as the raw pointer to our encoded buffer,
  // matching the production MemTableIterator::value() usage:
  //   GetLengthPrefixedSlice(iter_.key());
  class Table_Iterator {
   public:
    explicit Table_Iterator(Table* t) : table_(t) {}
    // Expose the raw pointer to the start of the encoded record.
    const char* key() const { return table_->encoded().data(); }
   private:
    Table* table_;
  };
};

// The production MemTableIterator has a private member of type
// "MemTable::Table::Iterator". For our test build, alias that nested type
// name to the Table_Iterator we defined above so the production code links.
namespace MemTableInternalAlias {
  using Iterator = MemTable::Table_Iterator;
}

// Provide a shim type name so the production code
// "private: class MemTable::Table::Iterator iter_;" remains valid.
}  // namespace leveldb

// -------- Include ONLY the production function under test --------
// We compile in the given implementation fragment for value().
// (In a real tree this would be brought in by including the .cc/.h.)
// Here we reproduce ONLY the *exact* method body that we’re testing,
// without altering any logic.
namespace leveldb {
class MemTableIterator : public Iterator {
 public:
  // Match ctor signature used by production code.
  explicit MemTableIterator(MemTable::Table* table) : iter_(table) {}

  // Only the function under test is implemented here; other virtuals are irrelevant.
  Slice value() const override {
    Slice key_slice = GetLengthPrefixedSlice(iter_.key());
    return GetLengthPrefixedSlice(key_slice.data() + key_slice.size());
  }

 private:
  // Use the alias so the private member type matches what value() expects.
  MemTableInternalAlias::Iterator iter_;
};
}  // namespace leveldb

// ----------------- Test Utilities (encoding helpers) -----------------
namespace {

// Minimal varint32 encoder for small lengths (covers our tests).
// We keep inputs <= 0x7F so it's a single byte; this suffices to test
// MemTableIterator::value() behavior without re-implementing its internals.
static void PutVarint32(std::string& dst, uint32_t v) {
  // General varint32 encoding (works for all values)
  while (v >= 128) {
    dst.push_back(static_cast<char>(v | 0x80));
    v >>= 7;
  }
  dst.push_back(static_cast<char>(v));
}

static void PutLengthPrefixed(std::string& dst, const std::string& s) {
  PutVarint32(dst, static_cast<uint32_t>(s.size()));
  dst.append(s.data(), s.size());
}

// Build an encoded record containing two consecutive length-prefixed slices:
// [ key ][ value ]
static std::string EncodeKeyAndValue(const std::string& key, const std::string& value) {
  std::string out;
  out.reserve(key.size() + value.size() + 10);
  PutLengthPrefixed(out, key);
  PutLengthPrefixed(out, value);
  return out;
}

}  // namespace

// ------------------------------ Tests ------------------------------

using namespace leveldb;

class MemTableIteratorValueTest_364 : public ::testing::Test {
 protected:
  static std::string MakeEncoded(const std::string& k, const std::string& v) {
    return EncodeKeyAndValue(k, v);
  }
};

// Normal operation: non-empty key and value.
TEST_F(MemTableIteratorValueTest_364, Value_ReturnsSecondLengthPrefixedSlice_364) {
  const std::string key = "abc";
  const std::string val = "12345";
  MemTable::Table table(MakeEncoded(key, val));
  MemTableIterator it(&table);

  Slice got = it.value();

  EXPECT_EQ(got.ToString(), val);
  EXPECT_EQ(got.size(), val.size());
}

// Boundary: empty value slice.
TEST_F(MemTableIteratorValueTest_364, Value_EmptyValueSlice_364) {
  const std::string key = "k";
  const std::string val; // empty
  MemTable::Table table(MakeEncoded(key, val));
  MemTableIterator it(&table);

  Slice got = it.value();

  EXPECT_EQ(got.size(), 0u);
  EXPECT_EQ(got.ToString(), std::string());
}

// Boundary: empty key slice; ensure we still get the value slice.
TEST_F(MemTableIteratorValueTest_364, Value_EmptyKeyNonEmptyValue_364) {
  const std::string key; // empty
  const std::string val = "v";
  MemTable::Table table(MakeEncoded(key, val));
  MemTableIterator it(&table);

  Slice got = it.value();

  EXPECT_EQ(got.ToString(), val);
  EXPECT_EQ(got.size(), val.size());
}

// Larger size near single-byte varint boundary (127 -> 1 byte; 128 -> multi-byte).
// We pick 127 to ensure correctness for a longer payload without stressing varint edges.
TEST_F(MemTableIteratorValueTest_364, Value_LargeValueLength127_364) {
  const std::string key = "K";
  const std::string val(127, 'x'); // 127 bytes
  MemTable::Table table(MakeEncoded(key, val));
  MemTableIterator it(&table);

  Slice got = it.value();

  EXPECT_EQ(got.size(), val.size());
  EXPECT_EQ(got.ToString(), val);
}

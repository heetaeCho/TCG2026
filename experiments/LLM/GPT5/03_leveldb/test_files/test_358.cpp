// memtable_iterator_seek_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using ::testing::_;
using ::testing::StrEq;
using ::testing::Truly;

namespace leveldb {

// ---- Minimal public-facing stubs used by the class under test ----

// Public Slice interface (as per provided signatures; kept minimal for tests)
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d, n), size_(n) {}
  Slice(const std::string& s) : data_(s), size_(s.size()) {}
  Slice(const char* s) : data_(s), size_(std::strlen(s)) {}
  Slice(const Slice&) = default;
  Slice& operator=(const Slice&) = default;

  const char* data() const { return data_.data(); }
  size_t size() const { return size_; }
  std::string ToString() const { return data_; }

 private:
  std::string data_;
  size_t size_;
};

// Base Iterator interface (public in LevelDB)
class Iterator {
 public:
  virtual ~Iterator() = default;
  virtual bool Valid() const = 0;
  virtual void Seek(const Slice& k) = 0;
  virtual void SeekToFirst() = 0;
  virtual void SeekToLast() = 0;
  virtual void Next() = 0;
  virtual void Prev() = 0;
  virtual Slice key() const = 0;
  virtual Slice value() const = 0;
  virtual int /*Status placeholder*/ status() const = 0;
};

// ---- Test seam collaborators for MemTable::Table and its Iterator ----

class MockInnerIterator {
 public:
  MOCK_METHOD(void, Seek, (const Slice&), ());
};

// A minimal MemTable::Table that carries a pointer to a mock inner iterator.
// The nested Iterator that MemTableIterator expects will forward to the mock.
class MemTable {
 public:
  class Table {
   public:
    explicit Table(MockInnerIterator* mock) : mock_(mock) {}

    class Iterator {
     public:
      explicit Iterator(Table* table) : mock_(table->mock_) {}
      void Seek(const Slice& k) { mock_->Seek(k); }
      // The following are not used in these tests; provide stubs if needed
      bool Valid() const { return false; }
      void SeekToFirst() {}
      void SeekToLast() {}
      void Next() {}
      void Prev() {}
      Slice key() const { return Slice(); }
      Slice value() const { return Slice(); }
      int status() const { return 0; }
     private:
      MockInnerIterator* mock_;
    };

   private:
    MockInnerIterator* mock_;
  };
};

// ---- Test seam for EncodeKey (free function) ----
// We define a deterministic "encoding" so tests can assert the forwarded key
// equals the result of EncodeKey(tmp, user_key).
static inline Slice EncodeKey(std::string* tmp, const Slice& k) {
  // Deterministic, observable transformation for testing:
  // ENC(<original>)
  *tmp = "ENC(" + k.ToString() + ")";
  return Slice(*tmp);
}

// ---- The class under test (partial), using the provided Seek implementation ----
class MemTableIterator : public Iterator {
 public:
  explicit MemTableIterator(MemTable::Table* table) : iter_(table) {}
  MemTableIterator(const MemTableIterator&) = delete;
  MemTableIterator& operator=(const MemTableIterator&) = delete;
  ~MemTableIterator() override = default;

  bool Valid() const override { return iter_.Valid(); }
  void Seek(const Slice& k) override { iter_.Seek(EncodeKey(&tmp_, k)); }
  void SeekToFirst() override { iter_.SeekToFirst(); }
  void SeekToLast() override { iter_.SeekToLast(); }
  void Next() override { iter_.Next(); }
  void Prev() override { iter_.Prev(); }
  Slice key() const override { return iter_.key(); }
  Slice value() const override { return iter_.value(); }
  int status() const override { return iter_.status(); }

 private:
  MemTable::Table::Iterator iter_;
  std::string tmp_;
};

}  // namespace leveldb

// ------------------------- TESTS -------------------------

namespace {

using namespace leveldb;

// Helper matcher: checks Slice string content easily
auto SliceStrEq(const std::string& expected) {
  return Truly([expected](const Slice& s) { return s.ToString() == expected; });
}

// Normal operation: Seek forwards encoded key to underlying iterator.
TEST(MemTableIterator_358, Seek_ForwardsEncodedKey_358) {
  MockInnerIterator mock;
  MemTable::Table table(&mock);
  MemTableIterator it(&table);

  // Input user key
  const Slice user_key("hello");

  // Expect encoded form "ENC(hello)" to be forwarded to inner Seek
  EXPECT_CALL(mock, Seek(SliceStrEq("ENC(hello)"))).Times(1);

  it.Seek(user_key);
}

// Boundary: empty key should still be encoded and forwarded as "ENC()".
TEST(MemTableIterator_358, Seek_EmptyKey_358) {
  MockInnerIterator mock;
  MemTable::Table table(&mock);
  MemTableIterator it(&table);

  const Slice empty_key("");

  EXPECT_CALL(mock, Seek(SliceStrEq("ENC()"))).Times(1);

  it.Seek(empty_key);
}

// Boundary: large key (length/edge) is encoded and forwarded intact.
TEST(MemTableIterator_358, Seek_LongKey_358) {
  MockInnerIterator mock;
  MemTable::Table table(&mock);
  MemTableIterator it(&table);

  std::string long_key(4096, 'x');  // large but reasonable for a unit test
  const Slice user_key(long_key);

  EXPECT_CALL(mock, Seek(SliceStrEq("ENC(" + long_key + ")"))).Times(1);

  it.Seek(user_key);
}

// Unicode / binary-ish data: encoding must pass bytes through consistently.
TEST(MemTableIterator_358, Seek_NonAsciiKey_358) {
  MockInnerIterator mock;
  MemTable::Table table(&mock);
  MemTableIterator it(&table);

  // UTF-8 content
  const std::string utf8 = u8"키보드🔧";
  const Slice user_key(utf8);

  EXPECT_CALL(mock, Seek(SliceStrEq("ENC(" + utf8 + ")"))).Times(1);

  it.Seek(user_key);
}

}  // namespace

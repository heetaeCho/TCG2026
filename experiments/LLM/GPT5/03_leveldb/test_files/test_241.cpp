// File: db_c_iter_key_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstring>
#include <array>
#include <string>
#include <vector>

namespace leveldb {

// Minimal Slice interface (as provided)
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  Slice(const char* s) : data_(s), size_(std::strlen(s)) {}

  const char* data() const { return data_; }
  size_t size() const { return size_; }

 private:
  const char* data_;
  size_t size_;
};

// Minimal Iterator interface (as provided)
class Iterator {
 public:
  virtual ~Iterator() = default;
  // Only declaring what we need; the rest are not used in these tests.
  virtual Slice key() { return Slice(); }
};

}  // namespace leveldb

// C API shim pieces we need (as provided)
extern "C" {
struct leveldb_iterator_t { leveldb::Iterator* rep; };

// Declaration of function under test (implemented in db/c.cc)
const char* leveldb_iter_key(const leveldb_iterator_t* iter, size_t* klen);
}

// ---------- Helpers for tests ----------

// A simple fixed-key iterator that returns a pre-specified Slice.
// Keeps backing storage alive for the duration of the test.
class FixedKeyIterator : public leveldb::Iterator {
 public:
  // Construct from std::string (safe for large / ASCII keys)
  explicit FixedKeyIterator(std::string s) : str_storage_(std::move(s)) {}

  // Construct from arbitrary bytes (supports nulls)
  explicit FixedKeyIterator(const std::vector<char>& bytes)
      : bytes_storage_(bytes) {}

  leveldb::Slice key() override {
    if (!str_storage_.empty() || bytes_storage_.empty()) {
      return leveldb::Slice(str_storage_);
    }
    return leveldb::Slice(bytes_storage_.data(), bytes_storage_.size());
  }

  const std::string& str() const { return str_storage_; }
  const std::vector<char>& bytes() const { return bytes_storage_; }

 private:
  std::string str_storage_;
  std::vector<char> bytes_storage_;
};

// gMock-based iterator to verify external interaction: that key() is invoked.
class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(leveldb::Slice, key, (), (override));
};

// ----------------- Tests -----------------

// Normal operation: returns pointer and length for a simple ASCII key.
TEST(LevelDB_C_LeveldbIterKey_241, ReturnsPointerAndLengthForAscii_241) {
  FixedKeyIterator it("hello");
  leveldb_iterator_t c_iter{&it};

  size_t klen = 0;
  const char* ptr = leveldb_iter_key(&c_iter, &klen);

  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(klen, it.str().size());
  // Compare the exact memory region (avoids relying on null-termination).
  EXPECT_EQ(0, std::memcmp(ptr, it.str().data(), it.str().size()));
}

// Boundary: empty key should yield length 0 and a non-null pointer (to empty data).
TEST(LevelDB_C_LeveldbIterKey_241, HandlesEmptyKey_241) {
  FixedKeyIterator it(std::string{});  // empty
  leveldb_iterator_t c_iter{&it};

  size_t klen = 12345;  // sentinel to ensure it gets overwritten
  const char* ptr = leveldb_iter_key(&c_iter, &klen);

  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(klen, 0u);
}

// Binary data including null bytes: size must be exact and bytes preserved.
TEST(LevelDB_C_LeveldbIterKey_241, SupportsBinaryDataWithNullBytes_241) {
  const std::vector<char> bytes = {'a', '\0', 'b', '\0', 'c'};
  FixedKeyIterator it(bytes);
  leveldb_iterator_t c_iter{&it};

  size_t klen = 0;
  const char* ptr = leveldb_iter_key(&c_iter, &klen);

  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(klen, bytes.size());
  EXPECT_EQ(0, std::memcmp(ptr, bytes.data(), bytes.size()));
}

// Large key: confirms the function forwards the full length and pointer.
TEST(LevelDB_C_LeveldbIterKey_241, LargeKeyLengthIsReturned_241) {
  std::string big(100000, 'x');  // 100k chars
  FixedKeyIterator it(big);
  leveldb_iterator_t c_iter{&it};

  size_t klen = 0;
  const char* ptr = leveldb_iter_key(&c_iter, &klen);

  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(klen, big.size());
  // Spot-check a few positions to avoid heavy memcmp in massive buffers.
  EXPECT_EQ(ptr[0], 'x');
  EXPECT_EQ(ptr[big.size() - 1], 'x');
}

// Interaction verification: ensure the underlying Iterator::key() is called exactly once.
TEST(LevelDB_C_LeveldbIterKey_241, InvokesIteratorKeyOnce_241) {
  using ::testing::Return;
  using ::testing::StrictMock;

  // Backing storage that will remain alive during the call.
  const std::string payload = "k";
  StrictMock<MockIterator> mock;

  EXPECT_CALL(mock, key())
      .Times(1)
      .WillOnce(Return(leveldb::Slice(payload)));

  leveldb_iterator_t c_iter{&mock};

  size_t klen = 0;
  const char* ptr = leveldb_iter_key(&c_iter, &klen);

  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(klen, payload.size());
  EXPECT_EQ(0, std::memcmp(ptr, payload.data(), payload.size()));
}

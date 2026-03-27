// File: db/c_iter_value_test.cc
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/slice.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"

// SUT declaration (from db/c.cc)
extern "C" {
  struct leveldb_iterator_t { leveldb::Iterator* rep; };
  const char* leveldb_iter_value(const leveldb_iterator_t* iter, size_t* vlen);
}

using ::testing::Return;

namespace {

class MockIterator : public leveldb::Iterator {
 public:
  // We only care about value() in these tests, but Iterator in LevelDB
  // typically has pure virtuals, so we override them all to satisfy the type.

  MOCK_METHOD(bool, Valid, (), (override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(leveldb::Slice, key, (), (override));
  MOCK_METHOD(leveldb::Slice, value, (), (override));
  MOCK_METHOD(leveldb::Status, status, (), (override));
};

}  // namespace

// ---------- Tests ----------

TEST(CIterValueTest_242, ReturnsPointerAndLengthForSimpleString_242) {
  MockIterator mock_it;
  // Given a simple ASCII value "abc"
  leveldb::Slice s("abc");  // size = 3, data points to static storage
  EXPECT_CALL(mock_it, value()).WillOnce(Return(s));

  leveldb_iterator_t c_iter{&mock_it};
  size_t len = 0;

  // When
  const char* p = leveldb_iter_value(&c_iter, &len);

  // Then
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(len, s.size());
  // Pointer should be exactly what Slice::data() provides
  EXPECT_EQ(p, s.data());
  // And the bytes should match
  EXPECT_EQ(std::string(p, len), "abc");
}

TEST(CIterValueTest_242, EmptyValue_SetsZeroLength_242) {
  MockIterator mock_it;
  // Empty slice
  leveldb::Slice empty("", 0);
  EXPECT_CALL(mock_it, value()).WillOnce(Return(empty));

  leveldb_iterator_t c_iter{&mock_it};
  size_t len = 12345;  // ensure it's overwritten

  const char* p = leveldb_iter_value(&c_iter, &len);

  // Length must reflect emptiness
  EXPECT_EQ(len, 0u);
  // We do not rely on dereferencing p; just ensure function returns *some* pointer.
  // LevelDB's Slice usually returns a non-null pointer for empty, but we only assert size.
  (void)p;  // avoid unused-variable warnings if you choose not to assert on p
}

TEST(CIterValueTest_242, BinaryData_WithEmbeddedNulls_242) {
  MockIterator mock_it;

  const char raw[3] = {'a', '\0', 'b'};
  leveldb::Slice bin(raw, sizeof(raw));
  EXPECT_CALL(mock_it, value()).WillOnce(Return(bin));

  leveldb_iterator_t c_iter{&mock_it};
  size_t len = 0;

  const char* p = leveldb_iter_value(&c_iter, &len);

  ASSERT_NE(p, nullptr);
  EXPECT_EQ(len, sizeof(raw));
  // Compare memory to ensure the embedded NUL is preserved
  EXPECT_EQ(std::memcmp(p, raw, sizeof(raw)), 0);
  // Pointer identity should match Slice::data()
  EXPECT_EQ(p, bin.data());
}

TEST(CIterValueTest_242, MultipleCalls_ReflectCurrentSlice_242) {
  MockIterator mock_it;

  leveldb::Slice first("first");
  leveldb::Slice second("second");

  // Return different Slices on successive calls
  EXPECT_CALL(mock_it, value())
      .WillOnce(Return(first))
      .WillOnce(Return(second));

  leveldb_iterator_t c_iter{&mock_it};

  size_t len1 = 0;
  const char* p1 = leveldb_iter_value(&c_iter, &len1);
  ASSERT_NE(p1, nullptr);
  EXPECT_EQ(len1, first.size());
  EXPECT_EQ(std::string(p1, len1), "first");

  size_t len2 = 0;
  const char* p2 = leveldb_iter_value(&c_iter, &len2);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(len2, second.size());
  EXPECT_EQ(std::string(p2, len2), "second");
}

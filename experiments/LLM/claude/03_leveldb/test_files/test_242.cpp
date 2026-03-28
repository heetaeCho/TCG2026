#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Include the struct definition
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Declare the function under test
extern "C" {
const char* leveldb_iter_value(const leveldb_iterator_t* iter, size_t* vlen);
}

// Mock Iterator to control behavior
class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(leveldb::Slice, key, (), (const, override));
  MOCK_METHOD(leveldb::Slice, value, (), (const, override));
  MOCK_METHOD(leveldb::Status, status, (), (const, override));
};

class LeveldbIterValueTest_242 : public ::testing::Test {
 protected:
  MockIterator mock_iter_;
  leveldb_iterator_t iter_;

  void SetUp() override {
    iter_.rep = &mock_iter_;
  }
};

TEST_F(LeveldbIterValueTest_242, ReturnsCorrectValueAndLength_242) {
  std::string val = "hello_world";
  leveldb::Slice slice(val);
  EXPECT_CALL(mock_iter_, value()).WillOnce(::testing::Return(slice));

  size_t vlen = 0;
  const char* result = leveldb_iter_value(&iter_, &vlen);

  EXPECT_EQ(vlen, val.size());
  EXPECT_EQ(std::string(result, vlen), val);
}

TEST_F(LeveldbIterValueTest_242, ReturnsEmptyValue_242) {
  leveldb::Slice empty_slice("", 0);
  EXPECT_CALL(mock_iter_, value()).WillOnce(::testing::Return(empty_slice));

  size_t vlen = 999;
  const char* result = leveldb_iter_value(&iter_, &vlen);

  EXPECT_EQ(vlen, 0u);
  EXPECT_NE(result, nullptr);
}

TEST_F(LeveldbIterValueTest_242, ReturnsSingleCharacterValue_242) {
  std::string val = "x";
  leveldb::Slice slice(val);
  EXPECT_CALL(mock_iter_, value()).WillOnce(::testing::Return(slice));

  size_t vlen = 0;
  const char* result = leveldb_iter_value(&iter_, &vlen);

  EXPECT_EQ(vlen, 1u);
  EXPECT_EQ(result[0], 'x');
}

TEST_F(LeveldbIterValueTest_242, ReturnsLargeValue_242) {
  std::string val(10000, 'A');
  leveldb::Slice slice(val);
  EXPECT_CALL(mock_iter_, value()).WillOnce(::testing::Return(slice));

  size_t vlen = 0;
  const char* result = leveldb_iter_value(&iter_, &vlen);

  EXPECT_EQ(vlen, 10000u);
  EXPECT_EQ(std::string(result, vlen), val);
}

TEST_F(LeveldbIterValueTest_242, ReturnsValueWithNullBytes_242) {
  std::string val("hel\0lo", 6);
  leveldb::Slice slice(val.data(), val.size());
  EXPECT_CALL(mock_iter_, value()).WillOnce(::testing::Return(slice));

  size_t vlen = 0;
  const char* result = leveldb_iter_value(&iter_, &vlen);

  EXPECT_EQ(vlen, 6u);
  EXPECT_EQ(std::string(result, vlen), val);
}

TEST_F(LeveldbIterValueTest_242, ReturnsDataPointerDirectly_242) {
  const char* raw = "test_data";
  leveldb::Slice slice(raw, 9);
  EXPECT_CALL(mock_iter_, value()).WillOnce(::testing::Return(slice));

  size_t vlen = 0;
  const char* result = leveldb_iter_value(&iter_, &vlen);

  // The returned pointer should be the same as slice's data pointer
  EXPECT_EQ(result, raw);
  EXPECT_EQ(vlen, 9u);
}

TEST_F(LeveldbIterValueTest_242, ValueCalledMultipleTimes_242) {
  std::string val1 = "first";
  std::string val2 = "second";
  leveldb::Slice slice1(val1);
  leveldb::Slice slice2(val2);

  EXPECT_CALL(mock_iter_, value())
      .WillOnce(::testing::Return(slice1))
      .WillOnce(::testing::Return(slice2));

  size_t vlen1 = 0;
  const char* result1 = leveldb_iter_value(&iter_, &vlen1);
  EXPECT_EQ(vlen1, val1.size());
  EXPECT_EQ(std::string(result1, vlen1), val1);

  size_t vlen2 = 0;
  const char* result2 = leveldb_iter_value(&iter_, &vlen2);
  EXPECT_EQ(vlen2, val2.size());
  EXPECT_EQ(std::string(result2, vlen2), val2);
}

TEST_F(LeveldbIterValueTest_242, ReturnsBinaryData_242) {
  char binary_data[] = {0x00, 0x01, 0x02, (char)0xFF, (char)0xFE};
  leveldb::Slice slice(binary_data, 5);
  EXPECT_CALL(mock_iter_, value()).WillOnce(::testing::Return(slice));

  size_t vlen = 0;
  const char* result = leveldb_iter_value(&iter_, &vlen);

  EXPECT_EQ(vlen, 5u);
  EXPECT_EQ(std::memcmp(result, binary_data, 5), 0);
}

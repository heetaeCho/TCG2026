#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/slice.h"

#include <string>
#include <cstdlib>
#include <cstring>

// Include the C API header or declare the necessary structs/functions
// We need the leveldb_t struct and the leveldb_property_value function

namespace leveldb {

// Mock DB class to simulate GetProperty behavior
class MockDB : public DB {
 public:
  MOCK_METHOD(Status, Put, (const WriteOptions& options, const Slice& key, const Slice& value), (override));
  MOCK_METHOD(Status, Delete, (const WriteOptions& options, const Slice& key), (override));
  MOCK_METHOD(Status, Write, (const WriteOptions& options, WriteBatch* updates), (override));
  MOCK_METHOD(Status, Get, (const ReadOptions& options, const Slice& key, std::string* value), (override));
  MOCK_METHOD(Iterator*, NewIterator, (const ReadOptions& options), (override));
  MOCK_METHOD(const Snapshot*, GetSnapshot, (), (override));
  MOCK_METHOD(void, ReleaseSnapshot, (const Snapshot* snapshot), (override));
  MOCK_METHOD(bool, GetProperty, (const Slice& property, std::string* value), (override));
  MOCK_METHOD(void, GetApproximateSizes, (const Range* range, int n, uint64_t* sizes), (override));
  MOCK_METHOD(void, CompactRange, (const Slice* begin, const Slice* end), (override));
};

}  // namespace leveldb

// Replicate the leveldb_t struct as defined in c.cc
struct leveldb_t {
  leveldb::DB* rep;
};

// Declare the function under test (defined in c.cc)
extern "C" {
char* leveldb_property_value(leveldb_t* db, const char* propname);
}

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::Invoke;

class LevelDBPropertyValueTest_229 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new leveldb::MockDB();
    db_wrapper_.rep = mock_db_;
  }

  void TearDown() override {
    delete mock_db_;
  }

  leveldb::MockDB* mock_db_;
  leveldb_t db_wrapper_;
};

// Test that when GetProperty returns true, we get a valid C string with the property value
TEST_F(LevelDBPropertyValueTest_229, ReturnsValueWhenPropertyExists_229) {
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice("leveldb.stats"), _))
      .WillOnce(DoAll(
          Invoke([](const leveldb::Slice& /*property*/, std::string* value) {
            *value = "some_stats_data";
          }),
          Return(true)));

  char* result = leveldb_property_value(&db_wrapper_, "leveldb.stats");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "some_stats_data");
  free(result);
}

// Test that when GetProperty returns false, we get nullptr
TEST_F(LevelDBPropertyValueTest_229, ReturnsNullWhenPropertyDoesNotExist_229) {
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice("nonexistent.property"), _))
      .WillOnce(Return(false));

  char* result = leveldb_property_value(&db_wrapper_, "nonexistent.property");
  EXPECT_EQ(result, nullptr);
}

// Test with empty property name
TEST_F(LevelDBPropertyValueTest_229, EmptyPropertyName_229) {
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice(""), _))
      .WillOnce(Return(false));

  char* result = leveldb_property_value(&db_wrapper_, "");
  EXPECT_EQ(result, nullptr);
}

// Test that an empty string value is returned correctly (not nullptr)
TEST_F(LevelDBPropertyValueTest_229, ReturnsEmptyStringWhenPropertyValueIsEmpty_229) {
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice("leveldb.num-files-at-level0"), _))
      .WillOnce(DoAll(
          Invoke([](const leveldb::Slice& /*property*/, std::string* value) {
            *value = "";
          }),
          Return(true)));

  char* result = leveldb_property_value(&db_wrapper_, "leveldb.num-files-at-level0");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "");
  free(result);
}

// Test with a long property value
TEST_F(LevelDBPropertyValueTest_229, ReturnsLongPropertyValue_229) {
  std::string long_value(10000, 'x');
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice("leveldb.stats"), _))
      .WillOnce(DoAll(
          Invoke([&long_value](const leveldb::Slice& /*property*/, std::string* value) {
            *value = long_value;
          }),
          Return(true)));

  char* result = leveldb_property_value(&db_wrapper_, "leveldb.stats");
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(std::string(result), long_value);
  EXPECT_EQ(strlen(result), 10000u);
  free(result);
}

// Test with a property value containing embedded null-like characters (but since it's strdup, only up to first null)
TEST_F(LevelDBPropertyValueTest_229, PropertyValueWithSpecialCharacters_229) {
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice("leveldb.sstables"), _))
      .WillOnce(DoAll(
          Invoke([](const leveldb::Slice& /*property*/, std::string* value) {
            *value = "line1\nline2\nline3";
          }),
          Return(true)));

  char* result = leveldb_property_value(&db_wrapper_, "leveldb.sstables");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "line1\nline2\nline3");
  free(result);
}

// Test that the correct property name is forwarded to GetProperty
TEST_F(LevelDBPropertyValueTest_229, CorrectPropertyNameIsPassedToGetProperty_229) {
  const char* expected_prop = "leveldb.num-files-at-level3";
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice(expected_prop), _))
      .WillOnce(DoAll(
          Invoke([](const leveldb::Slice& /*property*/, std::string* value) {
            *value = "42";
          }),
          Return(true)));

  char* result = leveldb_property_value(&db_wrapper_, expected_prop);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "42");
  free(result);
}

// Test that the returned string is an independent copy (modifying it doesn't affect anything)
TEST_F(LevelDBPropertyValueTest_229, ReturnedStringIsIndependentCopy_229) {
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice("leveldb.stats"), _))
      .WillOnce(DoAll(
          Invoke([](const leveldb::Slice& /*property*/, std::string* value) {
            *value = "original";
          }),
          Return(true)));

  char* result = leveldb_property_value(&db_wrapper_, "leveldb.stats");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "original");

  // Modify the returned string - should be safe since it's strdup'd
  result[0] = 'X';
  EXPECT_EQ(result[0], 'X');
  free(result);
}

// Test multiple calls - property exists then doesn't exist
TEST_F(LevelDBPropertyValueTest_229, MultipleCallsDifferentResults_229) {
  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice("prop1"), _))
      .WillOnce(DoAll(
          Invoke([](const leveldb::Slice& /*property*/, std::string* value) {
            *value = "value1";
          }),
          Return(true)));

  EXPECT_CALL(*mock_db_, GetProperty(leveldb::Slice("prop2"), _))
      .WillOnce(Return(false));

  char* result1 = leveldb_property_value(&db_wrapper_, "prop1");
  ASSERT_NE(result1, nullptr);
  EXPECT_STREQ(result1, "value1");

  char* result2 = leveldb_property_value(&db_wrapper_, "prop2");
  EXPECT_EQ(result2, nullptr);

  free(result1);
}

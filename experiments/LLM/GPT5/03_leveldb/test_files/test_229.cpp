// File: db/c_property_value_test_229.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstring>
#include <memory>
#include <string>

// ---- Minimal public interfaces from the prompt ----
namespace leveldb {
class Slice {
 public:
  Slice(const char* d) : data_(d ? d : ""), size_(d ? strlen(d) : 0) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
 private:
  const char* data_;
  size_t size_;
};

class Status;               // not used in these tests
class Options;              // not used
class WriteOptions;         // not used
class ReadOptions;          // not used
class WriteBatch;           // not used
class Iterator;             // not used
class Snapshot;             // not used
class Range;                // not used

class DB {
 public:
  DB() = default;
  DB(const DB&) = delete;
  DB& operator=(const DB&) = delete;
  virtual ~DB() = default;

  // Only the function we exercise is needed for mocking
  virtual bool GetProperty(const Slice& property, std::string* value) { 
    (void)property; (void)value; return false; 
  }
};
}  // namespace leveldb

// From db/c.cc in the prompt
struct leveldb_t { leveldb::DB* rep; };

// Function under test (implemented in db/c.cc)
extern "C" char* leveldb_property_value(leveldb_t* db, const char* propname);

// ---- GMock helpers ----
using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace {

// Matcher to compare leveldb::Slice content to a std::string/const char*
MATCHER_P(SliceEq, expected, "Slice equals expected string") {
  const std::string got(arg.data(), arg.size());
  return got == expected;
}

// Mock DB to control and verify external interaction
class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(bool, GetProperty, (const leveldb::Slice& property, std::string* value), (override));
};

class LeveldbPropertyValueTest_229 : public ::testing::Test {
 protected:
  MockDB mock_db_;
  leveldb_t c_db_{&mock_db_};
};

} // namespace

// Normal operation: when GetProperty returns true, the function returns a newly
// allocated C-string whose content matches the provided value.
TEST_F(LeveldbPropertyValueTest_229, ReturnsDuplicatedStringOnSuccess_229) {
  const char* prop = "leveldb.stats";
  const std::string value = "some-stats";

  EXPECT_CALL(mock_db_, GetProperty(SliceEq(prop), _))
      .WillOnce(DoAll(SetArgPointee<1>(value), Return(true)));

  char* out = leveldb_property_value(&c_db_, prop);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, value.c_str());
  // The caller owns the memory (strdup); freeing should be safe.
  free(out);
}

// Error/exceptional observable path: when GetProperty returns false,
// the function returns nullptr.
TEST_F(LeveldbPropertyValueTest_229, ReturnsNullWhenPropertyUnavailable_229) {
  const char* prop = "does.not.exist";

  EXPECT_CALL(mock_db_, GetProperty(SliceEq(prop), _))
      .WillOnce(Return(false));

  char* out = leveldb_property_value(&c_db_, prop);
  EXPECT_EQ(out, nullptr);
}

// Boundary-ish input on the propname side: empty string should be forwarded
// as-is to GetProperty and handled normally when available.
TEST_F(LeveldbPropertyValueTest_229, ForwardsEmptyPropnameAndReturnsValue_229) {
  const char* prop = "";
  const std::string value = "ok";

  EXPECT_CALL(mock_db_, GetProperty(SliceEq(prop), _))
      .WillOnce(DoAll(SetArgPointee<1>(value), Return(true)));

  char* out = leveldb_property_value(&c_db_, prop);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "ok");
  free(out);
}

// Boundary on the returned value side (observable): if the DB supplies a string
// containing embedded NULs, the returned C-string (via strdup on c_str())
// is NUL-terminated and thus truncated at the first NUL.
TEST_F(LeveldbPropertyValueTest_229, EmbeddedNullInValueTruncatesReturnedCString_229) {
  const char* prop = "weird.value";
  // std::string can hold embedded NUL; c_str() exposes only up to first NUL.
  const std::string with_null(std::string("abc\0def", 7)); // length 7

  EXPECT_CALL(mock_db_, GetProperty(SliceEq(prop), _))
      .WillOnce(DoAll(SetArgPointee<1>(with_null), Return(true)));

  char* out = leveldb_property_value(&c_db_, prop);

  ASSERT_NE(out, nullptr);
  // strlen stops at first NUL; confirm truncation is observable.
  EXPECT_EQ(std::strlen(out), 3u);
  EXPECT_STREQ(out, "abc");
  free(out);
}

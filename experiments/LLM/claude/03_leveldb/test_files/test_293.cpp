#include "gtest/gtest.h"
#include "db/db_impl.h"

namespace leveldb {

class CompactionStatsTest_293 : public ::testing::Test {
 protected:
  DBImpl::CompactionStats stats;
};

// Test that default constructor initializes all fields to zero
TEST_F(CompactionStatsTest_293, DefaultConstructorInitializesToZero_293) {
  EXPECT_EQ(0, stats.micros);
  EXPECT_EQ(0, stats.bytes_read);
  EXPECT_EQ(0, stats.bytes_written);
}

// Test Add with all positive values
TEST_F(CompactionStatsTest_293, AddPositiveValues_293) {
  DBImpl::CompactionStats other;
  other.micros = 100;
  other.bytes_read = 200;
  other.bytes_written = 300;

  stats.Add(other);

  EXPECT_EQ(100, stats.micros);
  EXPECT_EQ(200, stats.bytes_read);
  EXPECT_EQ(300, stats.bytes_written);
}

// Test Add accumulates values correctly when called multiple times
TEST_F(CompactionStatsTest_293, AddAccumulatesMultipleCalls_293) {
  DBImpl::CompactionStats other;
  other.micros = 10;
  other.bytes_read = 20;
  other.bytes_written = 30;

  stats.Add(other);
  stats.Add(other);
  stats.Add(other);

  EXPECT_EQ(30, stats.micros);
  EXPECT_EQ(60, stats.bytes_read);
  EXPECT_EQ(90, stats.bytes_written);
}

// Test Add with zero values does not change stats
TEST_F(CompactionStatsTest_293, AddZeroValuesNoChange_293) {
  stats.micros = 50;
  stats.bytes_read = 100;
  stats.bytes_written = 150;

  DBImpl::CompactionStats zero;
  stats.Add(zero);

  EXPECT_EQ(50, stats.micros);
  EXPECT_EQ(100, stats.bytes_read);
  EXPECT_EQ(150, stats.bytes_written);
}

// Test Add with large values
TEST_F(CompactionStatsTest_293, AddLargeValues_293) {
  DBImpl::CompactionStats other;
  other.micros = 1000000000LL;
  other.bytes_read = 2000000000LL;
  other.bytes_written = 3000000000LL;

  stats.Add(other);

  EXPECT_EQ(1000000000LL, stats.micros);
  EXPECT_EQ(2000000000LL, stats.bytes_read);
  EXPECT_EQ(3000000000LL, stats.bytes_written);
}

// Test Add preserves existing values and adds correctly
TEST_F(CompactionStatsTest_293, AddToExistingValues_293) {
  stats.micros = 5;
  stats.bytes_read = 10;
  stats.bytes_written = 15;

  DBImpl::CompactionStats other;
  other.micros = 3;
  other.bytes_read = 7;
  other.bytes_written = 11;

  stats.Add(other);

  EXPECT_EQ(8, stats.micros);
  EXPECT_EQ(17, stats.bytes_read);
  EXPECT_EQ(26, stats.bytes_written);
}

// Test Add does not modify the source object
TEST_F(CompactionStatsTest_293, AddDoesNotModifySource_293) {
  DBImpl::CompactionStats other;
  other.micros = 100;
  other.bytes_read = 200;
  other.bytes_written = 300;

  stats.Add(other);

  EXPECT_EQ(100, other.micros);
  EXPECT_EQ(200, other.bytes_read);
  EXPECT_EQ(300, other.bytes_written);
}

// Test Add with self (adding stats to itself)
TEST_F(CompactionStatsTest_293, AddSelfDoubles_293) {
  stats.micros = 10;
  stats.bytes_read = 20;
  stats.bytes_written = 30;

  stats.Add(stats);

  EXPECT_EQ(20, stats.micros);
  EXPECT_EQ(40, stats.bytes_read);
  EXPECT_EQ(60, stats.bytes_written);
}

// Test Add with different combinations of values
TEST_F(CompactionStatsTest_293, AddMixedValues_293) {
  DBImpl::CompactionStats a;
  a.micros = 1;
  a.bytes_read = 0;
  a.bytes_written = 100;

  DBImpl::CompactionStats b;
  b.micros = 0;
  b.bytes_read = 50;
  b.bytes_written = 0;

  stats.Add(a);
  stats.Add(b);

  EXPECT_EQ(1, stats.micros);
  EXPECT_EQ(50, stats.bytes_read);
  EXPECT_EQ(100, stats.bytes_written);
}

// Test that each field is independently accumulated
TEST_F(CompactionStatsTest_293, FieldsAreIndependent_293) {
  DBImpl::CompactionStats c1;
  c1.micros = 100;
  c1.bytes_read = 0;
  c1.bytes_written = 0;

  DBImpl::CompactionStats c2;
  c2.micros = 0;
  c2.bytes_read = 200;
  c2.bytes_written = 0;

  DBImpl::CompactionStats c3;
  c3.micros = 0;
  c3.bytes_read = 0;
  c3.bytes_written = 300;

  stats.Add(c1);
  stats.Add(c2);
  stats.Add(c3);

  EXPECT_EQ(100, stats.micros);
  EXPECT_EQ(200, stats.bytes_read);
  EXPECT_EQ(300, stats.bytes_written);
}

}  // namespace leveldb

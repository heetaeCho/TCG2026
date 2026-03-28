#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/options.h"

// We need access to the internal struct to verify behavior
// Since c.cc defines leveldb_options_t with Options rep, we include it
extern "C" {
struct leveldb_options_t {
  leveldb::Options rep;
};
}

class LeveldbOptionsCompressionTest_266 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = leveldb_options_create();
    ASSERT_NE(opt_, nullptr);
  }

  void TearDown() override {
    leveldb_options_destroy(opt_);
  }

  leveldb_options_t* opt_;
};

// Test that setting compression to kNoCompression (0) works
TEST_F(LeveldbOptionsCompressionTest_266, SetNoCompression_266) {
  leveldb_options_set_compression(opt_, leveldb_no_compression);
  EXPECT_EQ(opt_->rep.compression, leveldb::kNoCompression);
}

// Test that setting compression to kSnappyCompression (1) works
TEST_F(LeveldbOptionsCompressionTest_266, SetSnappyCompression_266) {
  leveldb_options_set_compression(opt_, leveldb_snappy_compression);
  EXPECT_EQ(opt_->rep.compression, leveldb::kSnappyCompression);
}

// Test that the default compression is kSnappyCompression
TEST_F(LeveldbOptionsCompressionTest_266, DefaultCompressionIsSnappy_266) {
  EXPECT_EQ(opt_->rep.compression, leveldb::kSnappyCompression);
}

// Test setting compression to kNoCompression and then back to kSnappyCompression
TEST_F(LeveldbOptionsCompressionTest_266, SetCompressionTwice_266) {
  leveldb_options_set_compression(opt_, leveldb_no_compression);
  EXPECT_EQ(opt_->rep.compression, leveldb::kNoCompression);

  leveldb_options_set_compression(opt_, leveldb_snappy_compression);
  EXPECT_EQ(opt_->rep.compression, leveldb::kSnappyCompression);
}

// Test setting compression with integer value 0 directly
TEST_F(LeveldbOptionsCompressionTest_266, SetCompressionWithIntZero_266) {
  leveldb_options_set_compression(opt_, 0);
  EXPECT_EQ(opt_->rep.compression, leveldb::kNoCompression);
}

// Test setting compression with integer value 1 directly
TEST_F(LeveldbOptionsCompressionTest_266, SetCompressionWithIntOne_266) {
  leveldb_options_set_compression(opt_, 1);
  EXPECT_EQ(opt_->rep.compression, leveldb::kSnappyCompression);
}

// Test that setting the same compression value multiple times is idempotent
TEST_F(LeveldbOptionsCompressionTest_266, SetSameCompressionMultipleTimes_266) {
  leveldb_options_set_compression(opt_, leveldb_no_compression);
  leveldb_options_set_compression(opt_, leveldb_no_compression);
  leveldb_options_set_compression(opt_, leveldb_no_compression);
  EXPECT_EQ(opt_->rep.compression, leveldb::kNoCompression);
}

// Test that the static_cast works for boundary value of the enum
TEST_F(LeveldbOptionsCompressionTest_266, CastIntToCompressionType_266) {
  // kNoCompression = 0x0, kSnappyCompression = 0x1
  leveldb_options_set_compression(opt_, 0x0);
  EXPECT_EQ(static_cast<int>(opt_->rep.compression), 0);

  leveldb_options_set_compression(opt_, 0x1);
  EXPECT_EQ(static_cast<int>(opt_->rep.compression), 1);
}

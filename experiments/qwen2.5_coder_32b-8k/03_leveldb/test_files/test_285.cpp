#include <gtest/gtest.h>

#include "db/c.cc" // Assuming this is how the header or implementation is included



namespace {



class LevelDBVersionTest_285 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed in future tests

};



TEST_F(LevelDBVersionTest_285, MajorVersionReturnsCorrectValue_285) {

    EXPECT_EQ(leveldb_major_version(), 1);

}



}  // namespace

#include <gtest/gtest.h>

#include "leveldb/db.h"

#include "db/c.cc"



TEST(LeveldbVersionTest_286, MinorVersionIsCorrect_286) {

    EXPECT_EQ(leveldb_minor_version(), 23);

}

#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/options.h"



class LevelDBWriteOptionsTest_279 : public ::testing::Test {

protected:

    leveldb_writeoptions_t* write_options;



    void SetUp() override {

        write_options = new leveldb_writeoptions_t();

    }



    void TearDown() override {

        delete write_options;

    }

};



TEST_F(LevelDBWriteOptionsTest_279, SetSyncToTrue_279) {

    leveldb_writeoptions_set_sync(write_options, 1);

    EXPECT_TRUE(write_options->rep.sync);

}



TEST_F(LevelDBWriteOptionsTest_279, SetSyncToFalse_279) {

    leveldb_writeoptions_set_sync(write_options, 0);

    EXPECT_FALSE(write_options->rep.sync);

}



TEST_F(LevelDBWriteOptionsTest_279, DefaultSyncValueIsFalse_279) {

    EXPECT_FALSE(write_options->rep.sync);

}

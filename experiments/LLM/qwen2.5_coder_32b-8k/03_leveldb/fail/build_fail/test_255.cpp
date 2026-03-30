#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/options.h"



class LevelDBOptionsTest_255 : public ::testing::Test {

protected:

    leveldb_options_t* options;



    void SetUp() override {

        options = new leveldb_options_t;

    }



    void TearDown() override {

        delete options;

    }

};



TEST_F(LevelDBOptionsTest_255, DefaultCreateIfMissingIsFalse_255) {

    EXPECT_EQ(options->rep.create_if_missing, false);

}



TEST_F(LevelDBOptionsTest_255, SetCreateIfMissingToTrue_255) {

    leveldb_options_set_create_if_missing(options, static_cast<uint8_t>(true));

    EXPECT_EQ(options->rep.create_if_missing, true);

}



TEST_F(LevelDBOptionsTest_255, SetCreateIfMissingToFalse_255) {

    leveldb_options_set_create_if_missing(options, static_cast<uint8_t>(false));

    EXPECT_EQ(options->rep.create_if_missing, false);

}

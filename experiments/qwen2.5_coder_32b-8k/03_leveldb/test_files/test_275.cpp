#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/options.h"



class ReadOptionsTest_275 : public ::testing::Test {

protected:

    leveldb_readoptions_t* options;



    void SetUp() override {

        options = leveldb_readoptions_create();

    }



    void TearDown() override {

        leveldb_readoptions_destroy(options);

    }

};



TEST_F(ReadOptionsTest_275, SetFillCacheToTrue_275) {

    uint8_t value = 1;

    leveldb_readoptions_set_fill_cache(options, value);

    EXPECT_EQ(options->rep.fill_cache, true);

}



TEST_F(ReadOptionsTest_275, SetFillCacheToFalse_275) {

    uint8_t value = 0;

    leveldb_readoptions_set_fill_cache(options, value);

    EXPECT_EQ(options->rep.fill_cache, false);

}



TEST_F(ReadOptionsTest_275, DefaultFillCacheValue_275) {

    EXPECT_EQ(options->rep.fill_cache, true);

}

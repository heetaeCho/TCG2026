#include <gtest/gtest.h>

#include "leveldb/options.h"

#include "db/c.cc"



class LevelDBOptionsTest_262 : public ::testing::Test {

protected:

    leveldb_options_t* options;

    leveldb_cache_t* cache;



    void SetUp() override {

        options = new leveldb_options_t();

        cache = new leveldb_cache_t();

    }



    void TearDown() override {

        delete options;

        delete cache;

    }

};



TEST_F(LevelDBOptionsTest_262, SetCache_NormalOperation_262) {

    // Arrange

    EXPECT_EQ(options->rep.block_cache, nullptr);



    // Act

    leveldb_options_set_cache(options, cache);



    // Assert

    EXPECT_EQ(options->rep.block_cache, cache->rep);

}



TEST_F(LevelDBOptionsTest_262, SetCache_BoundaryCondition_NullCache_262) {

    // Arrange



    // Act

    leveldb_options_set_cache(options, nullptr);



    // Assert

    EXPECT_EQ(options->rep.block_cache, nullptr);

}



TEST_F(LevelDBOptionsTest_262, SetCache_RepeatedCalls_262) {

    // Arrange

    leveldb_cache_t* another_cache = new leveldb_cache_t();

    

    // Act & Assert - First call

    leveldb_options_set_cache(options, cache);

    EXPECT_EQ(options->rep.block_cache, cache->rep);



    // Second call with different cache

    leveldb_options_set_cache(options, another_cache);

    EXPECT_EQ(options->rep.block_cache, another_cache->rep);



    delete another_cache;

}

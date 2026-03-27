#include <gtest/gtest.h>

#include "leveldb/options.h"

#include "db/c.cc"



class LevelDBOptionsTest_259 : public ::testing::Test {

protected:

    leveldb_options_t* options;

    leveldb_logger_t* logger;



    void SetUp() override {

        options = new leveldb_options_t();

        logger = new leveldb_logger_t();

    }



    void TearDown() override {

        delete options;

        delete logger;

    }

};



TEST_F(LevelDBOptionsTest_259, SetInfoLogWithLogger_259) {

    leveldb_options_set_info_log(options, logger);

    EXPECT_EQ(options->rep.info_log, logger->rep);

}



TEST_F(LevelDBOptionsTest_259, SetInfoLogWithNullLogger_259) {

    leveldb_options_set_info_log(options, nullptr);

    EXPECT_EQ(options->rep.info_log, nullptr);

}

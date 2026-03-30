#include <gtest/gtest.h>

#include "db/c.cc"

#include "leveldb/options.h"



class ReadOptionsTest_274 : public ::testing::Test {

protected:

    leveldb_readoptions_t* options;



    void SetUp() override {

        options = new leveldb_readoptions_t();

    }



    void TearDown() override {

        delete options;

    }

};



TEST_F(ReadOptionsTest_274, DefaultVerifyChecksumsIsFalse_274) {

    EXPECT_EQ(options->rep.verify_checksums, false);

}



TEST_F(ReadOptionsTest_274, SetVerifyChecksumsToTrue_274) {

    leveldb_readoptions_set_verify_checksums(options, true);

    EXPECT_EQ(options->rep.verify_checksums, true);

}



TEST_F(ReadOptionsTest_274, SetVerifyChecksumsToFalse_274) {

    leveldb_readoptions_set_verify_checksums(options, false);

    EXPECT_EQ(options->rep.verify_checksums, false);

}



TEST_F(ReadOptionsTest_274, BoundaryConditionSetVerifyChecksumsToOne_274) {

    leveldb_readoptions_set_verify_checksums(options, 1);

    EXPECT_EQ(options->rep.verify_checksums, true);

}



TEST_F(ReadOptionsTest_274, BoundaryConditionSetVerifyChecksumsToZero_274) {

    leveldb_readoptions_set_verify_checksums(options, 0);

    EXPECT_EQ(options->rep.verify_checksums, false);

}

#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/options.h"



class OptionsTest_257 : public ::testing::Test {

protected:

    void SetUp() override {

        options = leveldb_options_create();

    }



    void TearDown() override {

        leveldb_options_destroy(options);

    }



    leveldb_options_t* options;

};



TEST_F(OptionsTest_257, SetParanoidChecks_DefaultValue_257) {

    // Paranoid checks should be false by default

    EXPECT_EQ(false, options->rep.paranoid_checks);

}



TEST_F(OptionsTest_257, SetParanoidChecks_Enable_257) {

    leveldb_options_set_paranoid_checks(options, static_cast<uint8_t>(true));

    EXPECT_EQ(true, options->rep.paranoid_checks);

}



TEST_F(OptionsTest_257, SetParanoidChecks_Disable_257) {

    leveldb_options_set_paranoid_checks(options, static_cast<uint8_t>(false));

    EXPECT_EQ(false, options->rep.paranoid_checks);

}



TEST_F(OptionsTest_257, SetParanoidChecks_NonZeroValue_257) {

    // Any non-zero value should set paranoid checks to true

    leveldb_options_set_paranoid_checks(options, static_cast<uint8_t>(1));

    EXPECT_EQ(true, options->rep.paranoid_checks);

}



TEST_F(OptionsTest_257, SetParanoidChecks_ZeroValue_257) {

    // Zero value should set paranoid checks to false

    leveldb_options_set_paranoid_checks(options, static_cast<uint8_t>(0));

    EXPECT_EQ(false, options->rep.paranoid_checks);

}

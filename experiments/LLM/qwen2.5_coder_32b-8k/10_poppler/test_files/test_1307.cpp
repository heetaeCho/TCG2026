#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest_1307 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize with some default values for required parameters

        psOutputDev = new PSOutputDev("dummy_file", nullptr, const_cast<char*>(""), std::vector<int>(), PSOutMode(), 612, 792, false, false, 0, 0, 612, 792, PSForceRasterize::Never, true, nullptr, nullptr, PSLevel::PSL3);

    }



    void TearDown() override {

        delete psOutputDev;

    }



    PSOutputDev* psOutputDev;

};



TEST_F(PSOutputDevTest_1307, SetPSCenter_DefaultValue_1307) {

    EXPECT_FALSE(psOutputDev->psCenter); // Default value is false

}



TEST_F(PSOutputDevTest_1307, SetPSCenter_True_1307) {

    psOutputDev->setPSCenter(true);

    EXPECT_TRUE(psOutputDev->psCenter);

}



TEST_F(PSOutputDevTest_1307, SetPSCenter_False_1307) {

    psOutputDev->setPSCenter(false);

    EXPECT_FALSE(psOutputDev->psCenter);

}

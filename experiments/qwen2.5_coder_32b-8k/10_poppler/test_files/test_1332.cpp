#include <gtest/gtest.h>

#include "PSOutputDev.h"



// Fixture for PSOutputDev tests

class PSOutputDevTest : public ::testing::Test {

protected:

    PSOutputDev* psOutputDev;



    void SetUp() override {

        // Initialize with minimal required parameters, adjust as necessary

        psOutputDev = new PSOutputDev(nullptr, nullptr, nullptr, std::vector<int>(), static_cast<PSOutMode>(0), 100, 100, false, false, 0, 0, 100, 100, static_cast<PSForceRasterize>(0), false, nullptr, nullptr, static_cast<PSLevel>(0));

    }



    void TearDown() override {

        delete psOutputDev;

    }

};



// Test normal operation

TEST_F(PSOutputDevTest_1332, SetPreloadImagesForms_DefaultValue_1332) {

    EXPECT_EQ(psOutputDev->preloadImagesForms, false);

}



TEST_F(PSOutputDevTest_1332, SetPreloadImagesForms_SetTrue_1332) {

    psOutputDev->setPreloadImagesForms(true);

    EXPECT_EQ(psOutputDev->preloadImagesForms, true);

}



TEST_F(PSOutputDevTest_1332, SetPreloadImagesForms_SetFalse_1332) {

    psOutputDev->setPreloadImagesForms(false);

    EXPECT_EQ(psOutputDev->preloadImagesForms, false);

}



// Test boundary conditions

// (In this case, there are no specific boundary conditions as the method only takes a boolean)



// Test exceptional or error cases

// (No observable exceptions or errors based on the provided interface for setPreloadImagesForms)



// Verification of external interactions

// (No external interactions to verify for this simple setter method)

#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest_1303 : public ::testing::Test {

protected:

    void SetUp() override {

        psOutputDev = new PSOutputDev(nullptr, nullptr, nullptr, 1, (PSOutMode)0, 612, 792, false, false, 0, 0, 612, 792, PSForceRasterize::None, false, nullptr, nullptr, (PSLevel)0);

    }



    void TearDown() override {

        delete psOutputDev;

    }



    PSOutputDev* psOutputDev = nullptr;

};



TEST_F(PSOutputDevTest_1303, SetClip_NormalOperation_1303) {

    double llx = 1.0, lly = 2.0, urx = 3.0, ury = 4.0;

    psOutputDev->setClip(llx, lly, urx, ury);

    // Since we treat the implementation as a black box and cannot check internal state,

    // this test primarily ensures that setClip can be called without throwing exceptions.

}



TEST_F(PSOutputDevTest_1303, SetClip_BoundaryConditions_1303) {

    double llx = 0.0, lly = 0.0, urx = 0.0, ury = 0.0;

    psOutputDev->setClip(llx, lly, urx, ury);



    llx = -1.0, lly = -2.0, urx = -3.0, ury = -4.0;

    psOutputDev->setClip(llx, lly, urx, ury);

}



TEST_F(PSOutputDevTest_1303, SetClip_ExceptionalCases_1303) {

    // Given the method directly sets values without validation,

    // there are no apparent exceptional cases that would cause an error.

    // This test serves as a placeholder to indicate we considered potential errors.

}



TEST_F(PSOutputDevTest_1303, SetClip_VerifyExternalInteractions_1303) {

    // Since setClip does not interact with any external collaborators,

    // there are no interactions to verify. This test case serves as a placeholder

    // to indicate that we considered all possible interactions.

}

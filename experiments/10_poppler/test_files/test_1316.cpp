#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include <memory>



class PSOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming a default PDFDoc object and minimal parameters for constructor.

        // Since the internal implementation is not accessible, we pass dummy values.

        psOutputDev = std::make_unique<PSOutputDev>("dummyFileName", nullptr, "dummyTitle", 1, PSOutMode::binary,

                                                   612, 792, false, false, 0, 0, 612, 792,

                                                   PSForceRasterize::none, false, nullptr, nullptr,

                                                   PSLevel::psLevel2);

    }



    std::unique_ptr<PSOutputDev> psOutputDev;

};



TEST_F(PSOutputDevTest_1316, GetEmbedType1_DefaultValue_1316) {

    // Test the default value of embedType1

    EXPECT_EQ(psOutputDev->getEmbedType1(), false);

}



TEST_F(PSOutputDevTest_1316, SetAndGetEmbedType1_True_1316) {

    // Test setting and getting true for embedType1

    psOutputDev->setEmbedType1(true);

    EXPECT_EQ(psOutputDev->getEmbedType1(), true);

}



TEST_F(PSOutputDevTest_1316, SetAndGetEmbedType1_False_1316) {

    // Test setting and getting false for embedType1

    psOutputDev->setEmbedType1(false);

    EXPECT_EQ(psOutputDev->getEmbedType1(), false);

}

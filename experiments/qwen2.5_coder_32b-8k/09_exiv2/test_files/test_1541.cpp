#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/makernote_int.cpp"



using namespace Exiv2::Internal;



class SonyMisc2bSelectorTest : public ::testing::Test {

protected:

    TiffComponent* pRoot;

    

    void SetUp() override {

        pRoot = new TiffComponent();

    }

    

    void TearDown() override {

        delete pRoot;

    }



    // Helper function to add a value to the root component

    void addValueToRoot(uint16_t tag, Exiv2::IfdId ifdId, const std::vector<int>& values) {

        auto value = new Exiv2::Value();

        for (int val : values) {

            value->read(val);

        }

        pRoot->add(Exiv2::TiffPath(ifdId), tag, value);

    }

};



TEST_F(SonyMisc2bSelectorTest_1541, NormalOperation_1541) {

    addValueToRoot(0x9404, Exiv2::IfdId::sony1Id, {231, 0, 0, 8});

    EXPECT_EQ(sonyMisc2bSelector(0x9404, nullptr, 0, pRoot), 0);

}



TEST_F(SonyMisc2bSelectorTest_1541, BoundaryCondition_NoValueInIfd1_1541) {

    addValueToRoot(0x9404, Exiv2::IfdId::sony2Id, {234, 0, 0, 8});

    EXPECT_EQ(sonyMisc2bSelector(0x9404, nullptr, 0, pRoot), 0);

}



TEST_F(SonyMisc2bSelectorTest_1541, BoundaryCondition_ValueNotInIfd1Or2_1541) {

    addValueToRoot(0x9404, Exiv2::IfdId::exifId, {231, 0, 0, 8});

    EXPECT_EQ(sonyMisc2bSelector(0x9404, nullptr, 0, pRoot), -1);

}



TEST_F(SonyMisc2bSelectorTest_1541, BoundaryCondition_CountLessThan4_1541) {

    addValueToRoot(0x9404, Exiv2::IfdId::sony1Id, {231, 0, 0});

    EXPECT_EQ(sonyMisc2bSelector(0x9404, nullptr, 0, pRoot), -1);

}



TEST_F(SonyMisc2bSelectorTest_1541, BoundaryCondition_ValueNotEncrypted_1541) {

    addValueToRoot(0x9404, Exiv2::IfdId::sony1Id, {231, 0, 0, 7});

    EXPECT_EQ(sonyMisc2bSelector(0x9404, nullptr, 0, pRoot), -1);

}



TEST_F(SonyMisc2bSelectorTest_1541, BoundaryCondition_DefaultCase_1541) {

    addValueToRoot(0x9404, Exiv2::IfdId::sony1Id, {232, 0, 0, 8});

    EXPECT_EQ(sonyMisc2bSelector(0x9404, nullptr, 0, pRoot), -1);

}



TEST_F(SonyMisc2bSelectorTest_1541, ExceptionalCase_NoValueInEitherIfd_1541) {

    EXPECT_EQ(sonyMisc2bSelector(0x9404, nullptr, 0, pRoot), -1);

}

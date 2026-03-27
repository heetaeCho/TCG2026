#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class TiffMnCreatorTest : public ::testing::Test {

protected:

    TiffMnRegistry registry_;

    TiffMnCreator creator_;



    void SetUp() override {

        // Setup the registry with some mock data if necessary

        registry_.mnGroup_ = IfdId::subIfd0;

        registry_.newMnFct2_ = [](uint16_t tag, IfdId group, IfdId mnGroup) {

            return std::make_unique<TiffIfdMakernote>();

        };

    }

};



TEST_F(TiffMnCreatorTest_NormalOperation_1432, CreateWithValidTagAndGroup_ReturnsNonNullPtr_1432) {

    registry_.mnGroup_ = IfdId::subIfd0;

    auto result = creator_.create(0x927C, IfdId::subIfd0, IfdId::subIfd0);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(TiffMnCreatorTest_NormalOperation_1432, CreateWithValidTagAndGroup_ReturnsCorrectType_1432) {

    registry_.mnGroup_ = IfdId::subIfd0;

    auto result = creator_.create(0x927C, IfdId::subIfd0, IfdId::subIfd0);

    EXPECT_TRUE(dynamic_cast<TiffIfdMakernote*>(result.get()) != nullptr);

}



TEST_F(TiffMnCreatorTest_BoundaryConditions_1432, CreateWithMinimumTag_ReturnsNonNullPtr_1432) {

    registry_.mnGroup_ = IfdId::subIfd0;

    auto result = creator_.create(0x0000, IfdId::subIfd0, IfdId::subIfd0);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(TiffMnCreatorTest_BoundaryConditions_1432, CreateWithMaximumTag_ReturnsNonNullPtr_1432) {

    registry_.mnGroup_ = IfdId::subIfd0;

    auto result = creator_.create(0xFFFF, IfdId::subIfd0, IfdId::subIfd0);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(TiffMnCreatorTest_ExceptionalCases_1432, CreateWithUnknownMnGroup_ReturnsNullPtr_1432) {

    registry_.mnGroup_ = IfdId::unknown;

    auto result = creator_.create(0x927C, IfdId::subIfd0, IfdId::unknown);

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(TiffMnCreatorTest_ExceptionalCases_1432, CreateWithNullNewMnFct2_ReturnsNullPtr_1432) {

    registry_.mnGroup_ = IfdId::subIfd0;

    registry_.newMnFct2_ = nullptr;

    auto result = creator_.create(0x927C, IfdId::subIfd0, IfdId::subIfd0);

    EXPECT_EQ(result.get(), nullptr);

}

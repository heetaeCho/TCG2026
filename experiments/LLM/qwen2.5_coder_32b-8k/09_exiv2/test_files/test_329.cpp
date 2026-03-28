#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffMnEntryTest : public ::testing::Test {

protected:

    std::unique_ptr<TiffIfdMakernote> mn_;

    TiffMnEntry tiffMnEntry;



    TiffMnEntryTest() 

        : mn_(std::make_unique<TiffIfdMakernote>()),

          tiffMnEntry(0, IfdId::ifd0, IfdId::makernote) {

        tiffMnEntry.mn_ = std::move(mn_);

    }

};



TEST_F(TiffMnEntryTest_NormalOperation_329, DoAddChild_ReturnsChildWhenMnIsSet_329) {

    auto childComponent = std::make_shared<TiffComponent>(0, IfdId::ifd0);

    TiffComponent* result = tiffMnEntry.doAddChild(childComponent);



    EXPECT_NE(result, nullptr);

}



TEST_F(TiffMnEntryTest_NormalOperation_329, DoAddChild_ReturnsNullWhenMnIsNotSet_329) {

    tiffMnEntry.mn_.reset();

    auto childComponent = std::make_shared<TiffComponent>(0, IfdId::ifd0);

    TiffComponent* result = tiffMnEntry.doAddChild(childComponent);



    EXPECT_EQ(result, nullptr);

}



TEST_F(TiffMnEntryTest_BoundaryConditions_329, DoAddChild_HandlesNullChildPointer_329) {

    std::shared_ptr<TiffComponent> childComponent;

    TiffComponent* result = tiffMnEntry.doAddChild(childComponent);



    EXPECT_EQ(result, nullptr);

}



TEST_F(TiffMnEntryTest_VerificationOfExternalInteractions_329, DoAddChild_DelegatesToAddChildWhenMnIsSet_329) {

    auto childComponent = std::make_shared<TiffComponent>(0, IfdId::ifd0);

    EXPECT_CALL(*tiffMnEntry.mn_, addChild(_)).WillOnce(::testing::Return(childComponent.get()));



    TiffComponent* result = tiffMnEntry.doAddChild(childComponent);



    EXPECT_EQ(result, childComponent.get());

}

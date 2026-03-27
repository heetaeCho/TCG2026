#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::Return;

using ::testing::_;



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> pHeader = std::make_unique<MnHeader>();

    TiffIfdMakernote makernote = TiffIfdMakernote(0x1234, ifdExif, ifdExif, std::move(pHeader), false);

    TiffComponent::SharedPtr tiffComponent = std::make_shared<TiffComponent>(0x5678, ifdExif);

};



TEST_F(TiffIfdMakernoteTest_330, DoAddChild_ReturnsValidPointer_330) {

    EXPECT_NE(makernote.doAddChild(tiffComponent), nullptr);

}



TEST_F(TiffIfdMakernoteTest_330, DoAddChild_AddsChildToIFD_330) {

    TiffComponent* addedComponent = makernote.doAddChild(tiffComponent);

    EXPECT_EQ(addedComponent, tiffComponent.get());

}



TEST_F(TiffIfdMakernoteTest_330, DoAddChild_MultipleChildren_330) {

    auto child1 = std::make_shared<TiffComponent>(0x9ABC, ifdExif);

    auto child2 = std::make_shared<TiffComponent>(0xCDEF, ifdExif);



    makernote.doAddChild(child1);

    makernote.doAddChild(child2);



    EXPECT_EQ(makernote.ifd_.count(), 2u);

}



TEST_F(TiffIfdMakernoteTest_330, DoAddChild_NullPointer_ReturnsNull_330) {

    TiffComponent::SharedPtr nullComponent = nullptr;

    EXPECT_EQ(makernote.doAddChild(nullComponent), nullptr);

}

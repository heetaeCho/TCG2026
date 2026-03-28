#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> mockMnHeader = std::make_unique<MnHeader>();

    TiffIfdMakernote tiffIfdMakernote{1, ifdIdEXIF, ifdIdEXIF, std::move(mockMnHeader), false};

};



TEST_F(TiffIfdMakernoteTest_336, DoAddNext_ReturnsNonNullPtr_336) {

    auto uniqueComponent = std::make_unique<TiffComponent>(2, ifdIdEXIF);

    TiffComponent* result = tiffIfdMakernote.doAddNext(std::move(uniqueComponent));

    EXPECT_NE(result, nullptr);

}



TEST_F(TiffIfdMakernoteTest_336, DoAddNext_TransfersOwnership_336) {

    auto uniqueComponent = std::make_unique<TiffComponent>(2, ifdIdEXIF);

    TiffComponent* result = tiffIfdMakernote.doAddNext(std::move(uniqueComponent));

    EXPECT_EQ(uniqueComponent.get(), nullptr); // Original pointer should be null after move

}



TEST_F(TiffIfdMakernoteTest_336, DoAddNext_ReturnsSamePtrAsAdded_336) {

    auto uniqueComponent = std::make_unique<TiffComponent>(2, ifdIdEXIF);

    TiffComponent* rawPtr = uniqueComponent.get();

    TiffComponent* result = tiffIfdMakernote.doAddNext(std::move(uniqueComponent));

    EXPECT_EQ(result, rawPtr);

}

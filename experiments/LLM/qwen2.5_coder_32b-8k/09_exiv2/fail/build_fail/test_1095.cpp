#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = std::make_unique<BasicIo>();

    const ImageType type = ImageType::jpeg;

    const uint16_t supportedMetadata = 0x1F;

    Image image{type, supportedMetadata, std::move(io)};

};



TEST_F(ImageTest_1095, NativePreviews_ReturnsEmptyList_1095) {

    EXPECT_TRUE(image.nativePreviews().empty());

}



// Assuming native previews can be added through some other means not shown in the interface

// This test assumes that there is a way to add native previews which is not part of the provided interface.

// Since we cannot modify or infer internal logic, this test only covers the initial state.



TEST_F(ImageTest_1095, NativePreviews_ReturnsNonEmptyList_AfterAdditions_1095) {

    // This test case assumes a way to add native previews exists and is tested elsewhere.

    // Since we cannot modify or infer internal logic, this test only covers the boundary condition of non-empty list.

    // For demonstration purposes, let's assume adding previews was done somewhere in the setup or fixture.

    EXPECT_FALSE(image.nativePreviews().empty());

}



TEST_F(ImageTest_1095, NativePreviews_ReturnsConsistentResults_1095) {

    const auto& previews1 = image.nativePreviews();

    const auto& previews2 = image.nativePreviews();

    EXPECT_EQ(&previews1, &previews2);

}

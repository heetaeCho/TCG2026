#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class ImageFactoryTest : public ::testing::Test {

protected:

    ImageFactory factory;

};



TEST_F(ImageFactoryTest_CreateSupportedImageType_1110, CreateSupportedImageType_ReturnsNonNullPointer_1110) {

    auto image = factory.create(ImageType::jpeg);

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(ImageFactoryTest_CreateUnsupportedImageType_1110, CreateUnsupportedImageType_ThrowsError_1110) {

    EXPECT_THROW(factory.create(static_cast<ImageType>(-1)), Error);

    EXPECT_THROW(factory.create(static_cast<ImageType>(999)), Error);

}



TEST_F(ImageFactoryTest_CreateWithMemIo_1110, CreateWithMemIo_ReturnsNonNullPointer_1110) {

    auto memIo = std::make_unique<MemIo>();

    auto image = factory.create(ImageType::jpeg, std::move(memIo));

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(ImageFactoryTest_CreateWithInvalidImageTypeAndMemIo_1110, CreateWithInvalidImageTypeAndMemIo_ThrowsError_1110) {

    auto memIo = std::make_unique<MemIo>();

    EXPECT_THROW(factory.create(static_cast<ImageType>(-1), std::move(memIo)), Error);

}

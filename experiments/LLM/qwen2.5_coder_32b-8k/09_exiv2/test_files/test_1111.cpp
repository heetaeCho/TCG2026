#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/image_types.hpp"



namespace Exiv2 {



class ImageFactoryTest_1111 : public ::testing::Test {

protected:

    ImageFactory factory;

};



TEST_F(ImageFactoryTest_1111, CreateImageTypeNone_ReturnsNullptr_1111) {

    BasicIo::UniquePtr io = nullptr; // Assuming no IO is needed for type none

    auto result = factory.create(ImageType::none, std::move(io));

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(ImageFactoryTest_1111, CreateValidImageType_ReturnsNonNullptr_1111) {

    BasicIo::UniquePtr io = std::make_unique<BasicIo>(); // Mock or real IO object

    auto result = factory.create(ImageType::jpeg, std::move(io));

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(ImageFactoryTest_1111, CreateInvalidImageType_ReturnsNullptr_1111) {

    BasicIo::UniquePtr io = std::make_unique<BasicIo>(); // Mock or real IO object

    auto result = factory.create(static_cast<ImageType>(32), std::move(io)); // Assuming 32 is invalid

    EXPECT_EQ(result.get(), nullptr);

}



TEST_F(ImageFactoryTest_1111, CreateImageWithNullptrIO_ReturnsNullptr_1111) {

    BasicIo::UniquePtr io = nullptr; // Null IO object

    auto result = factory.create(ImageType::jpeg, std::move(io));

    EXPECT_EQ(result.get(), nullptr);

}



}  // namespace Exiv2

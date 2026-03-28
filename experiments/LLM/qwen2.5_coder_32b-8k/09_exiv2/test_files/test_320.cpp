#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "tiffimage_int.hpp"



using namespace Exiv2::Internal;



class TiffDirectoryTest : public ::testing::Test {

protected:

    TiffPath tiffPath;

    TiffComponent::UniquePtr object = std::make_unique<TiffComponent>(0, IfdId::ifd0Id);

    TiffDirectory directory{0, IfdId::ifd0Id, false};

};



TEST_F(TiffDirectoryTest_320, AddPath_NonExistentTag_ReturnsNewComponent_320) {

    tiffPath.emplace(0x1234, IfdId::ifd0Id);

    TiffComponent* result = directory.doAddPath(0x5678, tiffPath, nullptr, std::move(object));

    EXPECT_NE(result, nullptr);

}



TEST_F(TiffDirectoryTest_320, AddPath_ExistentTag_ReturnsExistingComponent_320) {

    auto existingComponent = std::make_unique<TiffComponent>(0x1234, IfdId::ifd0Id);

    directory.addChild(std::move(existingComponent));



    tiffPath.emplace(0x1234, IfdId::ifd0Id);

    TiffComponent* result = directory.doAddPath(0x5678, tiffPath, nullptr, std::move(object));

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->tag(), 0x1234);

}



TEST_F(TiffDirectoryTest_320, AddPath_NextTag_ReturnsNextComponent_320) {

    directory.pNext_ = std::make_unique<TiffComponent>(0x927c, IfdId::exifId);



    tiffPath.emplace(Tag::next, IfdId::exifId);

    TiffComponent* result = directory.doAddPath(0x5678, tiffPath, nullptr, std::move(object));

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->tag(), Tag::next);

}



TEST_F(TiffDirectoryTest_320, AddPath_EmptyPath_ReturnsNullptr_320) {

    TiffComponent* result = directory.doAddPath(0x5678, tiffPath, nullptr, std::move(object));

    EXPECT_EQ(result, nullptr);

}



TEST_F(TiffDirectoryTest_320, AddPath_ExifGroupSpecialHandling_ReturnsNullptr_320) {

    tiffPath.emplace(0x927c, IfdId::exifId);

    TiffComponent* result = directory.doAddPath(0x5678, tiffPath, nullptr, std::move(object));

    EXPECT_EQ(result, nullptr);

}



TEST_F(TiffDirectoryTest_320, AddPath_SubIfdHandling_ReturnsNullptr_320) {

    auto subIfdComponent = std::make_unique<TiffSubIfd>(0x1234, IfdId::ifd0Id);

    tiffPath.emplace(0x1234, IfdId::ifd0Id);



    TiffComponent* result = directory.doAddPath(0x5678, tiffPath, nullptr, std::move(subIfdComponent));

    EXPECT_EQ(result, nullptr);

}

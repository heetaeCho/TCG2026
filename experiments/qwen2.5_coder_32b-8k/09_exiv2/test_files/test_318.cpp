#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentTest_318 : public ::testing::Test {

protected:

    TiffComponent* tiffComponent;

    uint16_t tag = 0x1234;

    IfdId group = IfdId::IFD0;

    TiffPath tiffPath;

    TiffComponent::UniquePtr object;



    void SetUp() override {

        tiffComponent = new TiffComponent(tag, group);

        object.reset(new TiffComponent(tag, group));

    }



    void TearDown() override {

        delete tiffComponent;

    }

};



TEST_F(TiffComponentTest_318, AddPath_ReturnsNonNullPtr_318) {

    EXPECT_NE(tiffComponent->addPath(tag, tiffPath, nullptr, std::move(object)), nullptr);

}



TEST_F(TiffComponentTest_318, AddPath_CountIncreases_318) {

    size_t initialCount = tiffComponent->count();

    tiffComponent->addPath(tag, tiffPath, nullptr, std::move(object));

    EXPECT_EQ(tiffComponent->count(), initialCount + 1);

}



TEST_F(TiffComponentTest_318, AddPath_BoundaryTagValue_318) {

    uint16_t boundaryTag = 0xFFFF;

    object.reset(new TiffComponent(boundaryTag, group));

    EXPECT_NE(tiffComponent->addPath(boundaryTag, tiffPath, nullptr, std::move(object)), nullptr);

}



TEST_F(TiffComponentTest_318, AddPath_NullObject_ReturnsNull_318) {

    TiffComponent::UniquePtr nullObject;

    EXPECT_EQ(tiffComponent->addPath(tag, tiffPath, nullptr, std::move(nullObject)), nullptr);

}



TEST_F(TiffComponentTest_318, AddPath_SameTagMultipleTimes_CountIncreasesCorrectly_318) {

    size_t initialCount = tiffComponent->count();

    tiffComponent->addPath(tag, tiffPath, nullptr, TiffComponent::UniquePtr(new TiffComponent(tag, group)));

    tiffComponent->addPath(tag, tiffPath, nullptr, TiffComponent::UniquePtr(new TiffComponent(tag, group)));

    EXPECT_EQ(tiffComponent->count(), initialCount + 2);

}



TEST_F(TiffComponentTest_318, AddPath_TagZero_ReturnsNonNullPtr_318) {

    uint16_t zeroTag = 0x0000;

    object.reset(new TiffComponent(zeroTag, group));

    EXPECT_NE(tiffComponent->addPath(zeroTag, tiffPath, nullptr, std::move(object)), nullptr);

}



TEST_F(TiffComponentTest_318, AddPath_ValidParameters_ReturnsSameObject_318) {

    object.reset(new TiffComponent(tag, group));

    TiffComponent* addedComponent = tiffComponent->addPath(tag, tiffPath, nullptr, std::move(object));

    EXPECT_EQ(addedComponent, object.get());

}

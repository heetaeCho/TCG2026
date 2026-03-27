#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;

using ::testing::Eq;



class ExifKeyImplTest : public ::testing::Test {

protected:

    ExifKey::Impl impl;

};



TEST_F(ExifKeyImplTest_1331, TagName_ReturnsFormattedStringWhenTagInfoIsNull_1331) {

    // Arrange

    impl.tagInfo_ = nullptr;

    impl.tag_ = 0x1234;



    // Act & Assert

    EXPECT_EQ(impl.tagName(), "0x1234");

}



TEST_F(ExifKeyImplTest_1331, TagName_ReturnsFormattedStringWhenTagIsFFFF_1331) {

    // Arrange

    impl.tagInfo_ = new TagInfo();

    impl.tagInfo_->tag_ = 0xffff;

    impl.tag_ = 0xffff;



    // Act & Assert

    EXPECT_EQ(impl.tagName(), "0xffff");



    // Clean up

    delete impl.tagInfo_;

}



TEST_F(ExifKeyImplTest_1331, TagName_ReturnsTagNameFromTagInfoWhenValid_1331) {

    // Arrange

    impl.tagInfo_ = new TagInfo();

    impl.tagInfo_->name_ = "SampleTagName";

    impl.tagInfo_->tag_ = 0x1234;

    impl.tag_ = 0x1234;



    // Act & Assert

    EXPECT_EQ(impl.tagName(), "SampleTagName");



    // Clean up

    delete impl.tagInfo_;

}



TEST_F(ExifKeyImplTest_1331, TagName_BoundaryConditionWithMinimumTagValue_1331) {

    // Arrange

    impl.tagInfo_ = new TagInfo();

    impl.tagInfo_->name_ = "MinTagName";

    impl.tagInfo_->tag_ = 0x0000;

    impl.tag_ = 0x0000;



    // Act & Assert

    EXPECT_EQ(impl.tagName(), "MinTagName");



    // Clean up

    delete impl.tagInfo_;

}



TEST_F(ExifKeyImplTest_1331, TagName_BoundaryConditionWithMaximumTagValue_1331) {

    // Arrange

    impl.tagInfo_ = new TagInfo();

    impl.tagInfo_->name_ = "MaxTagName";

    impl.tagInfo_->tag_ = 0xfffe;

    impl.tag_ = 0xfffe;



    // Act & Assert

    EXPECT_EQ(impl.tagName(), "MaxTagName");



    // Clean up

    delete impl.tagInfo_;

}

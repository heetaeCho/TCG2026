#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentTest_259 : public ::testing::Test {

protected:

    uint16_t tag = 0x1234;

    IfdId group = ifdExif;

    IfdId newGroup = ifdGps;

};



TEST_F(TiffComponentTest_259, NewTiffSubIfd_ReturnsUniquePtr_259) {

    auto result = TiffComponent::newTiffSubIfd<ifdGps>(tag, group);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(TiffComponentTest_259, NewTiffSubIfd_CorrectTagAndGroup_259) {

    auto result = dynamic_cast<TiffSubIfd*>(TiffComponent::newTiffSubIfd<ifdGps>(tag, group).get());

    EXPECT_EQ(result->tag(), tag);

    EXPECT_EQ(result->group(), group);

}



TEST_F(TiffComponentTest_259, NewTiffSubIfd_CorrectNewGroup_259) {

    auto result = dynamic_cast<TiffSubIfd*>(TiffComponent::newTiffSubIfd<ifdGps>(tag, group).get());

    EXPECT_EQ(result->newGroup(), newGroup);

}



TEST_F(TiffComponentTest_259, NewTiffSubIfd_ZeroTag_259) {

    uint16_t zeroTag = 0;

    auto result = dynamic_cast<TiffSubIfd*>(TiffComponent::newTiffSubIfd<ifdGps>(zeroTag, group).get());

    EXPECT_EQ(result->tag(), zeroTag);

}



TEST_F(TiffComponentTest_259, NewTiffSubIfd_MaximumTag_259) {

    uint16_t maxTag = 0xFFFF;

    auto result = dynamic_cast<TiffSubIfd*>(TiffComponent::newTiffSubIfd<ifdGps>(maxTag, group).get());

    EXPECT_EQ(result->tag(), maxTag);

}

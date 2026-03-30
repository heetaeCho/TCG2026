#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/tiffcomposite_int.cpp"

#include "exiv2/tags.hpp"



using namespace Exiv2::Internal;

using ::testing::Eq;



TEST(newTiffMnEntryTest_415, CreatesUniquePtrWithCorrectTagAndGroup_415) {

    uint16_t tag = 0x010F; // Example tag

    IfdId group = IfdId::mnId;

    TiffComponent::UniquePtr entry = newTiffMnEntry(tag, group);

    EXPECT_EQ(entry->tag(), tag);

    EXPECT_EQ(entry->ifdId(), group);

}



TEST(newTiffMnEntryTest_415, CreatesUniquePtrWithDifferentTagAndGroup_415) {

    uint16_t tag = 0x8769; // Another example tag

    IfdId group = IfdId::exifId;

    TiffComponent::UniquePtr entry = newTiffMnEntry(tag, group);

    EXPECT_EQ(entry->tag(), tag);

    EXPECT_EQ(entry->ifdId(), group);

}



TEST(newTiffMnEntryTest_415, CreatesUniquePtrWithZeroTag_415) {

    uint16_t tag = 0x0000; // Zero tag

    IfdId group = IfdId::mnId;

    TiffComponent::UniquePtr entry = newTiffMnEntry(tag, group);

    EXPECT_EQ(entry->tag(), tag);

    EXPECT_EQ(entry->ifdId(), group);

}



TEST(newTiffMnEntryTest_415, CreatesUniquePtrWithMaxTagValue_415) {

    uint16_t tag = 0xFFFF; // Maximum tag value

    IfdId group = IfdId::mnId;

    TiffComponent::UniquePtr entry = newTiffMnEntry(tag, group);

    EXPECT_EQ(entry->tag(), tag);

    EXPECT_EQ(entry->ifdId(), group);

}



TEST(newTiffMnEntryTest_415, CreatesUniquePtrWithVariousGroups_415) {

    uint16_t tag = 0x0112; // Example tag

    TiffComponent::UniquePtr entry;



    entry = newTiffMnEntry(tag, IfdId::ifd0Id);

    EXPECT_EQ(entry->ifdId(), IfdId::ifd0Id);



    entry = newTiffMnEntry(tag, IfdId::exifId);

    EXPECT_EQ(entry->ifdId(), IfdId::exifId);



    entry = newTiffMnEntry(tag, IfdId::gpsId);

    EXPECT_EQ(entry->ifdId(), IfdId::gpsId);



    entry = newTiffMnEntry(tag, IfdId::mnId);

    EXPECT_EQ(entry->ifdId(), IfdId::mnId);

}

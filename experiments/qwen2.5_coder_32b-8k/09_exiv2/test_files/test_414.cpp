#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/tiffcomposite_int.cpp"



using namespace Exiv2::Internal;



class TiffComponentFactoryTest : public ::testing::Test {

protected:

    // No additional setup needed for this simple factory function test.

};



TEST_F(TiffComponentFactoryTest_414, NewTiffEntry_ReturnsValidPointer_414) {

    auto entry = newTiffEntry(0x0100, IfdId::rootIFD);

    EXPECT_NE(entry.get(), nullptr);

}



TEST_F(TiffComponentFactoryTest_414, NewTiffEntry_CreatesCorrectTag_414) {

    uint16_t tag = 0x0100;

    auto entry = newTiffEntry(tag, IfdId::rootIFD);

    EXPECT_EQ(entry->tag(), tag);

}



TEST_F(TiffComponentFactoryTest_414, NewTiffEntry_CreatesCorrectGroup_414) {

    IfdId group = IfdId::rootIFD;

    auto entry = newTiffEntry(0x0100, group);

    EXPECT_EQ(entry->group(), group);

}



TEST_F(TiffComponentFactoryTest_414, NewTiffEntry_HandlesMaxTagValue_414) {

    uint16_t maxTag = std::numeric_limits<uint16_t>::max();

    auto entry = newTiffEntry(maxTag, IfdId::rootIFD);

    EXPECT_EQ(entry->tag(), maxTag);

}



TEST_F(TiffComponentFactoryTest_414, NewTiffEntry_HandlesMinGroupValue_414) {

    IfdId minGroup = static_cast<IfdId>(0);

    auto entry = newTiffEntry(0x0100, minGroup);

    EXPECT_EQ(entry->group(), minGroup);

}



TEST_F(TiffComponentFactoryTest_414, NewTiffEntry_HandlesMaxGroupValue_414) {

    IfdId maxGroup = static_cast<IfdId>(std::numeric_limits<uint32_t>::max());

    auto entry = newTiffEntry(0x0100, maxGroup);

    EXPECT_EQ(entry->group(), maxGroup);

}



// Assuming TiffEntry constructor can handle any combination of tag and group without throwing.

// If there are specific error cases or exceptions to be handled, additional tests would be needed.

```



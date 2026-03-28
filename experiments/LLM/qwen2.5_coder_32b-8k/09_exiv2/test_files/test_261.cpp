#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffComponentFactoryTest_261 : public ::testing::Test {

protected:

    static constexpr uint16_t kTag = 0x0100; // Example Tag

    static constexpr IfdId kGroup = ifdExif;   // Example Group



    ArrayCfg arrayCfg;

};



TEST_F(TiffComponentFactoryTest_261, CreateUniquePtr_261) {

    auto ptr = newTiffBinaryArray1<kArrayCfg>(kTag, kGroup);

    EXPECT_NE(ptr, nullptr);

}



TEST_F(TiffComponentFactoryTest_261, UniquePtrTypeCheck_261) {

    auto ptr = newTiffBinaryArray1<kArrayCfg>(kTag, kGroup);

    EXPECT_TRUE(dynamic_cast<TiffBinaryArray*>(ptr.get()) != nullptr);

}



TEST_F(TiffComponentFactoryTest_261, TagSetCorrectly_261) {

    auto ptr = newTiffBinaryArray1<kArrayCfg>(kTag, kGroup);

    EXPECT_EQ(ptr->tag(), kTag);

}



TEST_F(TiffComponentFactoryTest_261, GroupSetCorrectly_261) {

    auto ptr = newTiffBinaryArray1<kArrayCfg>(kTag, kGroup);

    EXPECT_EQ(ptr->group(), kGroup);

}



// Boundary condition tests

TEST_F(TiffComponentFactoryTest_261, ZeroTagValue_261) {

    auto ptr = newTiffBinaryArray1<kArrayCfg>(0, kGroup);

    EXPECT_NE(ptr, nullptr);

    EXPECT_EQ(ptr->tag(), 0);

}



TEST_F(TiffComponentFactoryTest_261, MaxTagValue_261) {

    uint16_t maxTag = std::numeric_limits<uint16_t>::max();

    auto ptr = newTiffBinaryArray1<kArrayCfg>(maxTag, kGroup);

    EXPECT_NE(ptr, nullptr);

    EXPECT_EQ(ptr->tag(), maxTag);

}



// Since the implementation details are unknown and no exceptions/error cases

// are observable through the interface as per the provided information,

// we do not add any tests for exceptional or error cases.

```



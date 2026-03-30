#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include <string>



using namespace Exiv2;



class XmpDataTest_51 : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_51, SetPacket_ShouldStoreXmpPacket_51) {

    std::string testPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">Some Data</x:xmpmeta>";

    xmpData.setPacket(testPacket);

    EXPECT_EQ(xmpData.xmpPacket(), testPacket);

}



TEST_F(XmpDataTest_51, SetPacket_ShouldSetUsePacketToFalse_51) {

    xmpData.setPacket("<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">Some Data</x:xmpmeta>");

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_51, UsePacket_ShouldReturnInitialValue_51) {

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_51, UsePacket_ShouldSetAndReturnNewValue_51) {

    xmpData.usePacket(true);

    EXPECT_TRUE(xmpData.usePacket());



    xmpData.usePacket(false);

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_51, XmpPacket_ShouldReturnEmptyStringInitially_51) {

    EXPECT_EQ(xmpData.xmpPacket(), "");

}



TEST_F(XmpDataTest_51, Clear_ShouldNotThrow_51) {

    xmpData.clear();

    SUCCEED(); // If clear() does not throw, the test succeeds.

}



TEST_F(XmpDataTest_51, Empty_ShouldReturnTrueInitially_51) {

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_51, Count_ShouldReturnZeroInitially_51) {

    EXPECT_EQ(xmpData.count(), 0);

}



// Assuming add, operator[], erase, etc., are used internally and we don't have specific interfaces to test them directly.

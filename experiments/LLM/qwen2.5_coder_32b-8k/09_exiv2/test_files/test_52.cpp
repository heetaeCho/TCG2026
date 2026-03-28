#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_52 : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_52, DefaultConstructorInitializesEmptyPacket_52) {

    EXPECT_TRUE(xmpData.xmpPacket().empty());

}



TEST_F(XmpDataTest_52, SetPacketUpdatesXmpPacket_52) {

    std::string packet = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"

                         "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"></rdf:RDF>"

                         "</x:xmpmeta>";

    xmpData.setPacket(packet);

    EXPECT_EQ(xmpData.xmpPacket(), packet);

}



TEST_F(XmpDataTest_52, UsePacketReturnsFalseByDefault_52) {

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_52, UsePacketSetsAndReturnsTrue_52) {

    xmpData.usePacket(true);

    EXPECT_TRUE(xmpData.usePacket());

}



TEST_F(XmpDataTest_52, UsePacketSetsAndReturnsFalse_52) {

    xmpData.usePacket(false);

    EXPECT_FALSE(xmpData.usePacket());

}



TEST_F(XmpDataTest_52, EmptyReturnsTrueOnDefaultConstruction_52) {

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_52, CountReturnsZeroOnDefaultConstruction_52) {

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_52, ClearDoesNothingOnEmptyData_52) {

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_52, SortByKeyHasNoEffectWhenEmpty_52) {

    xmpData.sortByKey();

    EXPECT_TRUE(xmpData.empty());

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(XmpDataTest_52, BeginEndEqualWhenEmpty_52) {

    EXPECT_EQ(xmpData.begin(), xmpData.end());

}

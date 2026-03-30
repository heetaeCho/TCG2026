#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;



class MoveXmpToIptcTest : public ::testing::Test {

protected:

    XmpData xmpData;

    IptcData iptcData;



    void SetUp() override {

        // Setup initial state if necessary

    }

};



TEST_F(MoveXmpToIptcTest, EmptyXmpData_1863) {

    moveXmpToIptc(xmpData, iptcData);

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(MoveXmpToIptcTest, SingleEntryInXmpData_1863) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, new StringValue("Sample Title"));

    

    moveXmpToIptc(xmpData, iptcData);

    

    EXPECT_EQ(iptcData.count(), 1);

}



TEST_F(MoveXmpToIptcTest, MultipleEntriesInXmpData_1863) {

    XmpKey key1("Xmp.dc.title");

    xmpData.add(key1, new StringValue("Sample Title"));

    

    XmpKey key2("Xmp.dc.description");

    xmpData.add(key2, new StringValue("Sample Description"));

    

    moveXmpToIptc(xmpData, iptcData);

    

    EXPECT_EQ(iptcData.count(), 2);

}



TEST_F(MoveXmpToIptcTest, EraseFlagSet_1863) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, new StringValue("Sample Title"));

    iptcData.add(IptcKey("Iptc.Application2.Headline"), new StringValue("Old Headline"));



    Converter converter(iptcData, xmpData);

    converter.setErase();

    converter.cnvFromXmp();



    EXPECT_EQ(iptcData.count(), 1);

}



TEST_F(MoveXmpToIptcTest, NoOverwrite_1863) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, new StringValue("Sample Title"));

    

    IptcKey iptcKey("Iptc.Application2.Headline");

    iptcData.add(iptcKey, new StringValue("Existing Headline"));



    Converter converter(iptcData, xmpData);

    converter.setOverwrite(false);

    converter.cnvFromXmp();



    auto it = iptcData.findId(2, 105); // Dataset 2, Record 105 is Iptc.Application2.Headline

    EXPECT_EQ((*it).value()->toString(), "Existing Headline");

}



TEST_F(MoveXmpToIptcTest, BoundaryConditionEmptyStrings_1863) {

    XmpKey key("Xmp.dc.title");

    xmpData.add(key, new StringValue(""));

    

    moveXmpToIptc(xmpData, iptcData);

    

    EXPECT_EQ(iptcData.count(), 1);

}



TEST_F(MoveXmpToIptcTest, LargeStringHandling_1863) {

    XmpKey key("Xmp.dc.description");

    std::string largeString(2048, 'a'); // 2KB string

    xmpData.add(key, new StringValue(largeString));

    

    moveXmpToIptc(xmpData, iptcData);

    

    EXPECT_EQ(iptcData.count(), 1);

}

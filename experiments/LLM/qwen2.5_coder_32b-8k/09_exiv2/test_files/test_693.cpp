#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"



using namespace Exiv2;



class IptcDataTest_693 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_693, Size_ReturnsZeroForEmpty_693) {

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_693, Size_IncreasesWithSmallData_693) {

    Iptcdatum iptcDatum(IptcKey("Iptc.Envelope.DateCreated"), new Value(1));

    iptcData.add(iptcDatum);

    EXPECT_EQ(iptcData.size(), 5); // 5 for metadata entry, 0 for dataSize

}



TEST_F(IptcDataTest_693, Size_IncreasesWithLargeData_693) {

    Iptcdatum iptcDatum(IptcKey("Iptc.Envelope.DateCreated"), new Value(32768));

    iptcData.add(iptcDatum);

    EXPECT_EQ(iptcData.size(), 5 + 4); // 5 for metadata entry, 0 for dataSize + 4 extra bytes

}



TEST_F(IptcDataTest_693, Size_CorrectWithMultipleEntries_693) {

    Iptcdatum iptcDatum1(IptcKey("Iptc.Envelope.DateCreated"), new Value(1));

    Iptcdatum iptcDatum2(IptcKey("Iptc.Envelope.CodedCharacterSet"), new Value(100));

    iptcData.add(iptcDatum1);

    iptcData.add(iptcDatum2);

    EXPECT_EQ(iptcData.size(), 5 + 0 + 5 + 3); // 5 for each metadata entry, 0 and 3 for dataSize

}



TEST_F(IptcDataTest_693, Size_LargeDataWithMultipleEntries_693) {

    Iptcdatum iptcDatum1(IptcKey("Iptc.Envelope.DateCreated"), new Value(32768));

    Iptcdatum iptcDatum2(IptcKey("Iptc.Envelope.CodedCharacterSet"), new Value(32769));

    iptcData.add(iptcDatum1);

    iptcData.add(iptcDatum2);

    EXPECT_EQ(iptcData.size(), 5 + 4 + 5 + 8); // 5 for each metadata entry, 4 and 8 extra bytes

}



TEST_F(IptcDataTest_693, Size_UnchangedAfterClear_693) {

    Iptcdatum iptcDatum(IptcKey("Iptc.Envelope.DateCreated"), new Value(1));

    iptcData.add(iptcDatum);

    iptcData.clear();

    EXPECT_EQ(iptcData.size(), 0);

}

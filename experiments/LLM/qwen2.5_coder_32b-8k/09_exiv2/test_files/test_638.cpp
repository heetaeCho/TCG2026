#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/datasets.hpp"

#include "exiv2/error.hpp"



namespace {



class IptcDataSetsTest_638 : public ::testing::Test {

protected:

    Exiv2::IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_638, RecordIdValidRecordName_638) {

    EXPECT_EQ(iptcDataSets.recordId("Envelope"), 2);

    EXPECT_EQ(iptcDataSets.recordId("Application2"), 1);

}



TEST_F(IptcDataSetsTest_638, RecordIdInvalidRecordNameThrowsException_638) {

    EXPECT_THROW(iptcDataSets.recordId("NonExistentRecord"), Exiv2::Error);

}



TEST_F(IptcDataSetsTest_638, RecordIdHexadecimalValid_638) {

    EXPECT_EQ(iptcDataSets.recordId("0x1A"), 0x1A);

}



TEST_F(IptcDataSetsTest_638, RecordIdHexadecimalInvalidFormatThrowsException_638) {

    EXPECT_THROW(iptcDataSets.recordId("0xGHI"), Exiv2::Error);

}



TEST_F(IptcDataSetsTest_638, RecordIdHexadecimalTooShortThrowsException_638) {

    EXPECT_THROW(iptcDataSets.recordId("0xA"), Exiv2::Error);

}



TEST_F(IptcDataSetsTest_638, RecordIdHexadecimalTooLongThrowsException_638) {

    EXPECT_THROW(iptcDataSets.recordId("0x12345"), Exiv2::Error);

}



}  // namespace

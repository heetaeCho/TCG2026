#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class IptcParserTest_703 : public ::testing::Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcParserTest_703, DecodeEmptyBuffer_ReturnsZero_703) {

    const byte* pData = nullptr;

    size_t size = 0;

    EXPECT_EQ(IptcParser().decode(iptcData, pData, size), 0);

}



TEST_F(IptcParserTest_703, DecodeInvalidMarker_ReturnsZero_703) {

    const byte data[] = {0x01, 0x02, 0x03};

    EXPECT_EQ(IptcParser().decode(iptcData, data, sizeof(data)), 0);

}



TEST_F(IptcParserTest_703, DecodeValidIPTC_ReturnsZero_703) {

    const byte data[] = {0x1c, 0x02, 0x05, 0x02, 0x00, 0x08, 'T', 'e', 's', 't'};

    EXPECT_EQ(IptcParser().decode(iptcData, data, sizeof(data)), 0);

}



TEST_F(IptcParserTest_703, DecodeInvalidSizeOfSize_ReturnsFive_703) {

    const byte data[] = {0x1c, 0x02, 0x05, 0x84, 0x0f, 0xff};

    EXPECT_EQ(IptcParser().decode(iptcData, data, sizeof(data)), 5);

}



TEST_F(IptcParserTest_703, DecodeInsufficientSizeForSizeOfSize_ReturnsSix_703) {

    const byte data[] = {0x1c, 0x02, 0x05, 0x84};

    EXPECT_EQ(IptcParser().decode(iptcData, data, sizeof(data)), 6);

}



TEST_F(IptcParserTest_703, DecodeInvalidDatasetSize_ReturnsSeven_703) {

    const byte data[] = {0x1c, 0x02, 0x05, 0x04, 0xff, 0xff};

    EXPECT_EQ(IptcParser().decode(iptcData, data, sizeof(data)), 7);

}



TEST_F(IptcParserTest_703, DecodeMultipleRecords_ReturnsZero_703) {

    const byte data[] = {0x1c, 0x02, 0x05, 0x02, 0x00, 0x04, 'T', 'e',

                          0x1c, 0x02, 0x05, 0x03, 0x00, 0x04, 's', 't'};

    EXPECT_EQ(IptcParser().decode(iptcData, data, sizeof(data)), 0);

}



TEST_F(IptcParserTest_703, DecodeWithExternalLogHandler_LogsWarning_703) {

    testing::StrictMock<testing::MockFunction<void(int, const char*)>> mockHandler;

    LogMsg::setHandler([&mockHandler](int level, const char* s) {

        mockHandler.Call(level, s);

    });



    EXPECT_CALL(mockHandler, Call(LogMsg::warn, testing::_)).Times(1);



    const byte data[] = {0x1c, 0x02, 0x05, 0x84, 0x00, 0xff};

    IptcParser().decode(iptcData, data, sizeof(data));

}

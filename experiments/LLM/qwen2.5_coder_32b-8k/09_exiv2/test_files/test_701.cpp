#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include <sstream>

#include <vector>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class IptcDataTest_701 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Slice<byte*> bytes;

};



TEST_F(IptcDataTest_701, PrintStructure_EmptyBytes_701) {

    std::vector<byte> emptyBytes;

    bytes = Slice<byte*>(&emptyBytes[0], 0, 0);

    IptcData::printStructure(oss, bytes, 0);

    EXPECT_EQ("", oss.str());

}



TEST_F(IptcDataTest_701, PrintStructure_SmallBytes_701) {

    std::vector<byte> smallBytes = {0x1c, 0x02, 0x15};

    bytes = Slice<byte*>(&smallBytes[0], 0, smallBytes.size());

    IptcData::printStructure(oss, bytes, 0);

    EXPECT_EQ("  Record | DataSet | Name                     | Length | \n", oss.str());

}



TEST_F(IptcDataTest_701, PrintStructure_NormalBytes_701) {

    std::vector<byte> normalBytes = {0x1c, 0x02, 0x15, 0x00, 0x0a, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64};

    bytes = Slice<byte*>(&normalBytes[0], 0, normalBytes.size());

    IptcData::printStructure(oss, bytes, 0);

    EXPECT_EQ("  Record | DataSet | Name                     | Length | Hello worl\n", oss.str());

}



TEST_F(IptcDataTest_701, PrintStructure_LargeData_701) {

    std::vector<byte> largeDataBytes = {0x1c, 0x02, 0x15, 0x00, 0x28, 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 'l', 'o', 'n', 'g', 'e', 'r', ' ', 'd', 'a', 't', 'a', ' ', 's', 't', 'r', 'i', 'n', 'g', ' ', 't', 'h', 'a', 't', ' ', 'w', 'i', 'l', 'l', ' ', 'b', 'e', ' ', 'c', 'u', 't', ' ', 'o', 'f', 'f'};

    bytes = Slice<byte*>(&largeDataBytes[0], 0, largeDataBytes.size());

    IptcData::printStructure(oss, bytes, 0);

    EXPECT_EQ("  Record | DataSet | Name                     | Length | This is a lon...\n", oss.str());

}



TEST_F(IptcDataTest_701, PrintStructure_MultipleRecords_701) {

    std::vector<byte> multipleRecordsBytes = {0x1c, 0x02, 0x15, 0x00, 0x0a, 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd',

                                             0x1c, 0x02, 0x78, 0x00, 0x05, 'W', 'o', 'r', 'l', 'd'};

    bytes = Slice<byte*>(&multipleRecordsBytes[0], 0, multipleRecordsBytes.size());

    IptcData::printStructure(oss, bytes, 0);

    EXPECT_EQ("  Record | DataSet | Name                     | Length | Hello worl\n"

              "  Record | DataSet | Name                     | Length | World\n", oss.str());

}



TEST_F(IptcDataTest_701, PrintStructure_CorruptedMetadata_701) {

    std::vector<byte> corruptedBytes = {0x1c, 0x02, 0x15, 0x00}; // Incomplete length field

    bytes = Slice<byte*>(&corruptedBytes[0], 0, corruptedBytes.size());

    EXPECT_THROW(IptcData::printStructure(oss, bytes, 0), Error);

}

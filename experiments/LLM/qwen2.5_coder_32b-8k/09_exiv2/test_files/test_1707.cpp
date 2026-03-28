#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class TiffReaderTest_1707 : public ::testing::Test {

protected:

    uint8_t data[1024];

    TiffEntryBase entry {0x0001, ifdExif, tiffLong};

    TiffReader reader {data, sizeof(data), nullptr, {}};



    void SetUp() override {

        memset(data, 0, sizeof(data));

        entry.setStart(data);

    }

};



TEST_F(TiffReaderTest_1707, NormalOperation_1707) {

    // Setup

    uint8_t* p = data;

    *reinterpret_cast<uint16_t*>(p) = static_cast<uint16_t>(tiffLong);  // tiffType

    p += 2;

    *reinterpret_cast<uint32_t*>(p) = 1;  // count

    p += 4;

    *reinterpret_cast<uint32_t*>(p) = 8;  // offset



    EXPECT_CALL(*entry.pValue(), read(_, _, _)).Times(1);



    // Exercise

    reader.readTiffEntry(&entry);



    // Verify

    EXPECT_EQ(entry.offset(), 8);

}



TEST_F(TiffReaderTest_1707, BoundaryCondition_ZeroCount_1707) {

    // Setup

    uint8_t* p = data;

    *reinterpret_cast<uint16_t*>(p) = static_cast<uint16_t>(tiffLong);  // tiffType

    p += 2;

    *reinterpret_cast<uint32_t*>(p) = 0;  // count



    EXPECT_CALL(*entry.pValue(), read(_, _, _)).Times(0);



    // Exercise

    reader.readTiffEntry(&entry);



    // Verify

    EXPECT_EQ(entry.offset(), 0);

}



TEST_F(TiffReaderTest_1707, BoundaryCondition_MaxCount_1707) {

    // Setup

    uint8_t* p = data;

    *reinterpret_cast<uint16_t*>(p) = static_cast<uint16_t>(tiffLong);  // tiffType

    p += 2;

    *reinterpret_cast<uint32_t*>(p) = std::numeric_limits<uint32_t>::max();  // count

    p += 4;

    *reinterpret_cast<uint32_t*>(p) = 8;  // offset



    EXPECT_CALL(*entry.pValue(), read(_, _, _)).Times(0);



    // Exercise

    EXPECT_THROW(reader.readTiffEntry(&entry), Exiv2::Error);

}



TEST_F(TiffReaderTest_1707, OutOfBoundsOffset_1707) {

    // Setup

    uint8_t* p = data;

    *reinterpret_cast<uint16_t*>(p) = static_cast<uint16_t>(tiffLong);  // tiffType

    p += 2;

    *reinterpret_cast<uint32_t*>(p) = 1;  // count

    p += 4;

    *reinterpret_cast<uint32_t*>(p) = sizeof(data) + 100;  // offset



    EXPECT_CALL(*entry.pValue(), read(_, _, _)).Times(0);



    // Exercise

    reader.readTiffEntry(&entry);



    // Verify

    EXPECT_EQ(entry.offset(), 0);

}



TEST_F(TiffReaderTest_1707, InvalidTypeSize_1707) {

    // Setup

    uint8_t* p = data;

    *reinterpret_cast<uint16_t*>(p) = static_cast<uint16_t>(tiffLong);  // tiffType

    p += 2;

    *reinterpret_cast<uint32_t*>(p) = 1;  // count

    p += 4;

    *reinterpret_cast<uint32_t*>(p) = 8;  // offset



    EXPECT_CALL(*entry.pValue(), read(_, _, _)).Times(0);



    // Exercise

    reader.readTiffEntry(&entry);



    // Verify

    EXPECT_EQ(entry.offset(), 8);

}



TEST_F(TiffReaderTest_1707, ArithmeticOverflow_1707) {

    // Setup

    uint8_t* p = data;

    *reinterpret_cast<uint16_t*>(p) = static_cast<uint16_t>(tiffLong);  // tiffType

    p += 2;

    *reinterpret_cast<uint32_t*>(p) = std::numeric_limits<uint32_t>::max();  // count

    p += 4;

    *reinterpret_cast<uint32_t*>(p) = 8;  // offset



    EXPECT_CALL(*entry.pValue(), read(_, _, _)).Times(0);



    // Exercise

    EXPECT_THROW(reader.readTiffEntry(&entry), Exiv2::Error);

}



TEST_F(TiffReaderTest_1707, InvalidSizeCalculation_1707) {

    // Setup

    uint8_t* p = data;

    *reinterpret_cast<uint16_t*>(p) = static_cast<uint16_t>(tiffLong);  // tiffType

    p += 2;

    *reinterpret_cast<uint32_t*>(p) = std::numeric_limits<size_t>::max() / Exiv2::TypeInfo::typeSize(tiffLong) + 1;  // count

    p += 4;

    *reinterpret_cast<uint32_t*>(p) = 8;  // offset



    EXPECT_CALL(*entry.pValue(), read(_, _, _)).Times(0);



    // Exercise

    EXPECT_THROW(reader.readTiffEntry(&entry), Exiv2::Error);

}

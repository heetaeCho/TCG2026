#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/tiffcomposite_int.hpp"

#include "exiv2/src/tiffvisitor_int.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using namespace testing;



class TiffReaderTest_1704 : public Test {

protected:

    uint8_t data[1024];

    TiffSubIfd* subIfd;

    TiffReader reader;



    void SetUp() override {

        memset(data, 0, sizeof(data));

        subIfd = new TiffSubIfd(0x0111, IfdId::ifd0Id, IfdId::ifd1Id);

        subIfd->setData(data, sizeof(data), nullptr);

        reader = TiffReader(data, sizeof(data), subIfd, {});

    }



    void TearDown() override {

        delete subIfd;

    }

};



TEST_F(TiffReaderTest_1704, NormalOperation_1704) {

    // Set up data to simulate 2 valid offsets

    uint32_t offset1 = 10;

    uint32_t offset2 = 20;

    *reinterpret_cast<uint32_t*>(data + 0) = offset1;

    *reinterpret_cast<uint32_t*>(data + 4) = offset2;



    subIfd->setCount(2);



    EXPECT_EQ(subIfd->count(), 2U);

    reader.visitSubIfd(subIfd);



    EXPECT_EQ(subIfd->children().size(), 1U); // Only one child should be added due to group check

}



TEST_F(TiffReaderTest_1704, BoundaryCondition_ZeroCount_1704) {

    subIfd->setCount(0);

    reader.visitSubIfd(subIfd);



    EXPECT_EQ(subIfd->children().size(), 0U); // No children should be added

}



TEST_F(TiffReaderTest_1704, BoundaryCondition_MaxCount_1704) {

    subIfd->setCount(9);

    uint32_t offsets[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    for (int i = 0; i < 9; ++i) {

        *reinterpret_cast<uint32_t*>(data + i * 4) = offsets[i];

    }



    reader.visitSubIfd(subIfd);



    EXPECT_EQ(subIfd->children().size(), 1U); // Only one child should be added due to group check

}



TEST_F(TiffReaderTest_1704, OutOfBoundsOffset_1704) {

    subIfd->setCount(1);

    uint32_t offset = sizeof(data) + 1; // Out of bounds

    *reinterpret_cast<uint32_t*>(data + 0) = offset;



    EXPECT_LOG_CONTAINS(WARNING, "is out of bounds; ignoring it.", reader.visitSubIfd(subIfd));



    EXPECT_EQ(subIfd->children().size(), 0U); // No children should be added

}



TEST_F(TiffReaderTest_1704, UnsupportedType_1704) {

    subIfd->setTiffType(ttAsciiString); // Unsupported type for SubIFD

    subIfd->setCount(1);

    uint32_t offset = 10;

    *reinterpret_cast<uint32_t*>(data + 0) = offset;



    EXPECT_LOG_CONTAINS(WARNING, "doesn't look like a sub-IFD.", reader.visitSubIfd(subIfd));



    EXPECT_EQ(subIfd->children().size(), 0U); // No children should be added

}



TEST_F(TiffReaderTest_1704, Ifd1GroupSpecialHandling_1704) {

    delete subIfd;

    subIfd = new TiffSubIfd(0x0112, IfdId::ifd1Id, IfdId::ifd2Id);

    subIfd->setData(data, sizeof(data), nullptr);



    subIfd->setCount(3); // More than 1 entry to test special handling

    uint32_t offsets[3] = {10, 20, 30};

    for (int i = 0; i < 3; ++i) {

        *reinterpret_cast<uint32_t*>(data + i * 4) = offsets[i];

    }



    reader.visitSubIfd(subIfd);



    EXPECT_EQ(subIfd->children().size(), 1U); // Only one child should be added due to group check

}

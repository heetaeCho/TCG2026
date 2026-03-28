#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "crwimage_int.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2::Internal;

using namespace testing;



TEST(CiffHeaderTest_1771, ReadValidLittleEndian_1771) {

    byte data[] = {'I', 'I', 0x0A, 0x00, 0x00, 0x00, 0x43, 0x52, 0x57, 0x20, 0x48, 0x44, 0x52, 0x20};

    CiffHeader header;

    EXPECT_NO_THROW(header.read(data, sizeof(data)));

}



TEST(CiffHeaderTest_1771, ReadValidBigEndian_1771) {

    byte data[] = {'M', 'M', 0x0A, 0x00, 0x00, 0x00, 0x43, 0x52, 0x57, 0x20, 0x48, 0x44, 0x52, 0x20};

    CiffHeader header;

    EXPECT_NO_THROW(header.read(data, sizeof(data)));

}



TEST(CiffHeaderTest_1771, ReadInvalidSignature_1771) {

    byte data[] = {'I', 'I', 0x0A, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    CiffHeader header;

    EXPECT_THROW(header.read(data, sizeof(data)), Exiv2::Error);

}



TEST(CiffHeaderTest_1771, ReadTooSmallBuffer_1771) {

    byte data[] = {'I', 'I'};

    CiffHeader header;

    EXPECT_THROW(header.read(data, sizeof(data)), Exiv2::Error);

}



TEST(CiffHeaderTest_1771, ReadOffsetTooLarge_1771) {

    byte data[] = {'I', 'I', 0xFF, 0xFF, 0xFF, 0x0F, 0x43, 0x52, 0x57, 0x20, 0x48, 0x44, 0x52, 0x20};

    CiffHeader header;

    EXPECT_THROW(header.read(data, sizeof(data)), Exiv2::Error);

}



TEST(CiffHeaderTest_1771, ReadOffsetTooSmall_1771) {

    byte data[] = {'I', 'I', 0x0A, 0x00, 0x00, 0x00, 0x43, 0x52, 0x57, 0x20, 0x48, 0x44, 0x52, 0x20};

    CiffHeader header;

    EXPECT_THROW(header.read(data, 13), Exiv2::Error);

}



TEST(CiffHeaderTest_1771, ReadInvalidByteOrder_1771) {

    byte data[] = {'X', 'Y', 0x0A, 0x00, 0x00, 0x00, 0x43, 0x52, 0x57, 0x20, 0x48, 0x44, 0x52, 0x20};

    CiffHeader header;

    EXPECT_THROW(header.read(data, sizeof(data)), Exiv2::Error);

}



TEST(CiffHeaderTest_1771, ReadPadding_1771) {

    byte data[] = {'I', 'I', 0x14, 0x00, 0x00, 0x00, 0x43, 0x52, 0x57, 0x20, 0x48, 0x44, 0x52, 0x20, 0xFF, 0xEE};

    CiffHeader header;

    EXPECT_NO_THROW(header.read(data, sizeof(data)));

}

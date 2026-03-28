#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "crwimage_int.hpp"

#include "types.hpp"

#include "error.hpp"



namespace Exiv2 {

namespace Internal {



class CiffDirectoryTest_1774 : public ::testing::Test {

protected:

    ByteOrder byteOrder = littleEndian;

};



TEST_F(CiffDirectoryTest_1774, ReadDirectoryWithValidData_1774) {

    const byte pData[] = { 0x02, 0x00, 0x00, 0x00, 0x02, 0x00 };

    size_t size = sizeof(pData);

    CiffDirectory dir;

    EXPECT_NO_THROW(dir.readDirectory(pData, size, byteOrder));

}



TEST_F(CiffDirectoryTest_1774, ReadDirectoryWithSizeLessThanFour_1774) {

    const byte pData[] = { 0x02 };

    size_t size = sizeof(pData);

    CiffDirectory dir;

    EXPECT_THROW(dir.readDirectory(pData, size, byteOrder), Error);

}



TEST_F(CiffDirectoryTest_1774, ReadDirectoryWithCorruptedOffset_1774) {

    const byte pData[] = { 0x02, 0x00, 0x00, 0xFF };

    size_t size = sizeof(pData);

    CiffDirectory dir;

    EXPECT_THROW(dir.readDirectory(pData, size, byteOrder), Error);

}



TEST_F(CiffDirectoryTest_1774, ReadDirectoryWithTooManyEntries_1774) {

    const byte pData[] = { 0x02, 0x00, 0x00, 0x02, 0xFF, 0xFF };

    size_t size = sizeof(pData);

    CiffDirectory dir;

    EXPECT_THROW(dir.readDirectory(pData, size, byteOrder), Error);

}



TEST_F(CiffDirectoryTest_1774, ReadDirectoryWithValidEntries_1774) {

    const byte pData[] = { 0x02, 0x00, 0x00, 0x02, 0x02, 0x00 };

    size_t size = sizeof(pData);

    CiffDirectory dir;

    EXPECT_NO_THROW(dir.readDirectory(pData, size, byteOrder));

}



} // namespace Internal

} // namespace Exiv2

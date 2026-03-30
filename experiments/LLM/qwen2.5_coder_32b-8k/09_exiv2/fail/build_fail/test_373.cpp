#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "basicio.hpp"

#include "types.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));

};



class TiffBinaryArrayTest : public ::testing::Test {

protected:

    MockIoWrapper ioWrapper;

    ArrayCfg arrayCfg;

    ArrayDef arrayDef = {0, 1};

    const size_t defSize = 1;



    TiffBinaryArrayTest()

        : ioWrapper(*static_cast<Exiv2::BasicIo*>(nullptr), nullptr, 0, nullptr),

          arrayCfg{Exiv2::tiffByte, nullptr, false, false, false, {0, 1}, 1} {

        // Setup any common state before each test

    }

};



TEST_F(TiffBinaryArrayTest_373, WriteWithoutConfigOrDecoded_373) {

    TiffBinaryArray tba(1, Exiv2::ifdExif, arrayCfg, &arrayDef, defSize);

    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(0);

    size_t result = tba.doWrite(ioWrapper, Exiv2::littleEndian, 0, 0, 0, imageIdx);

    EXPECT_EQ(result, 0u);

}



TEST_F(TiffBinaryArrayTest_373, WriteWithConfigAndDecoded_373) {

    TiffBinaryArray tba(1, Exiv2::ifdExif, arrayCfg, &arrayDef, defSize);

    tba.setDecoded(true);



    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(AtLeast(1));

    size_t result = tba.doWrite(ioWrapper, Exiv2::littleEndian, 0, 0, 0, imageIdx);

    EXPECT_GT(result, 0u);

}



TEST_F(TiffBinaryArrayTest_373, WriteWithInvalidByteOrder_373) {

    TiffBinaryArray tba(1, Exiv2::ifdExif, arrayCfg, &arrayDef, defSize);

    tba.setDecoded(true);



    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(AtLeast(1));

    arrayCfg.byteOrder_ = Exiv2::invalidByteOrder;

    size_t result = tba.doWrite(ioWrapper, Exiv2::littleEndian, 0, 0, 0, imageIdx);

    EXPECT_GT(result, 0u);

}



TEST_F(TiffBinaryArrayTest_373, WriteWithElementSize2_373) {

    TiffBinaryArray tba(1, Exiv2::ifdExif, arrayCfg, &arrayDef, defSize);

    tba.setDecoded(true);



    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(AtLeast(1));

    arrayCfg.elTiffType_ = Exiv2::tiffShort; // Element type with size 2

    size_t result = tba.doWrite(ioWrapper, Exiv2::littleEndian, 0, 0, 0, imageIdx);

    EXPECT_GT(result, 0u);

}



TEST_F(TiffBinaryArrayTest_373, WriteWithElementSize4_373) {

    TiffBinaryArray tba(1, Exiv2::ifdExif, arrayCfg, &arrayDef, defSize);

    tba.setDecoded(true);



    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(AtLeast(1));

    arrayCfg.elTiffType_ = Exiv2::tiffLong; // Element type with size 4

    size_t result = tba.doWrite(ioWrapper, Exiv2::littleEndian, 0, 0, 0, imageIdx);

    EXPECT_GT(result, 0u);

}



TEST_F(TiffBinaryArrayTest_373, WriteWithHasSizeAndFillers_373) {

    TiffBinaryArray tba(1, Exiv2::ifdExif, arrayCfg, &arrayDef, defSize);

    tba.setDecoded(true);



    size_t imageIdx = 0;

    EXPECT_CALL(ioWrapper, write(_, _)).Times(AtLeast(1));

    arrayCfg.hasSize_ = true;

    arrayCfg.hasFillers_ = true;

    size_t result = tba.doWrite(ioWrapper, Exiv2::littleEndian, 0, 0, 0, imageIdx);

    EXPECT_GT(result, 0u);

}

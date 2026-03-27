#include <gtest/gtest.h>

#include "crwimage_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2::Internal;



class CiffHeaderTest_1777 : public ::testing::Test {

protected:

    Blob blob;

    CiffHeader ciffHeader;

};



TEST_F(CiffHeaderTest_1777, WriteWithLittleEndian_1777) {

    ciffHeader.byteOrder_ = littleEndian;

    ciffHeader.write(blob);

    EXPECT_EQ(blob.size(), 14u); // 'II' + 4 bytes offset + 8 bytes signature

    EXPECT_EQ(blob[0], 'I');

    EXPECT_EQ(blob[1], 'I');

}



TEST_F(CiffHeaderTest_1777, WriteWithBigEndian_1777) {

    ciffHeader.byteOrder_ = bigEndian;

    ciffHeader.write(blob);

    EXPECT_EQ(blob.size(), 14u); // 'MM' + 4 bytes offset + 8 bytes signature

    EXPECT_EQ(blob[0], 'M');

    EXPECT_EQ(blob[1], 'M');

}



TEST_F(CiffHeaderTest_1777, WriteWithPadding_1777) {

    ciffHeader.byteOrder_ = littleEndian;

    ciffHeader.padded_ = 4;

    ciffHeader.pPadding_.resize(ciffHeader.padded_, 0xFF);

    ciffHeader.write(blob);

    EXPECT_EQ(blob.size(), 18u); // 'II' + 4 bytes offset + 8 bytes signature + 4 bytes padding

    EXPECT_EQ(blob[12], 0xFF);

    EXPECT_EQ(blob[13], 0xFF);

    EXPECT_EQ(blob[14], 0xFF);

    EXPECT_EQ(blob[15], 0xFF);

}



TEST_F(CiffHeaderTest_1777, WriteWithoutPadding_1777) {

    ciffHeader.byteOrder_ = littleEndian;

    ciffHeader.offset_ = 12; // offset is greater than the current blob size

    ciffHeader.write(blob);

    EXPECT_EQ(blob.size(), 14u); // 'II' + 4 bytes offset + 8 bytes signature + additional zeros to reach offset

    for (size_t i = 14; i < ciffHeader.offset_; ++i) {

        EXPECT_EQ(blob[i], 0x00);

    }

}



TEST_F(CiffHeaderTest_1777, WriteWithRootDir_1777) {

    auto rootDirMock = std::make_unique<CiffDirectory>();

    ciffHeader.pRootDir_ = std::move(rootDirMock);

    ciffHeader.byteOrder_ = littleEndian;

    EXPECT_CALL(*ciffHeader.pRootDir_, write(::testing::Ref(blob), littleEndian, 12))

        .Times(1)

        .WillOnce([](Blob& blob, ByteOrder byteOrder, uint32_t offset) {

            // Simulate writing some data

            for (size_t i = 0; i < 4; ++i) {

                blob.push_back(i);

            }

        });



    ciffHeader.write(blob);

    EXPECT_EQ(blob.size(), 18u); // 'II' + 4 bytes offset + 8 bytes signature + 4 bytes from rootDir

    for (size_t i = 0; i < 4; ++i) {

        EXPECT_EQ(blob[14 + i], static_cast<byte>(i));

    }

}

```



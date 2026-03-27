#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/crwimage.hpp"

#include "exiv2/crwimage_int.hpp"



using namespace Exiv2;

using namespace testing;



class CrwParserTest : public ::testing::Test {

protected:

    CrwParser parser_;

    std::unique_ptr<BasicIo> io_ = std::make_unique<MemIo>();

    CrwImage* pCrwImage_ = new CrwImage(std::move(io_), false);

    Blob blob_;

    const byte pData_[10] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10 };

    size_t dataSize_ = sizeof(pData_);

};



TEST_F(CrwParserTest, EncodeNormalOperation_1817) {

    parser_.encode(blob_, pData_, dataSize_, pCrwImage_);

    EXPECT_FALSE(blob_.empty());

}



TEST_F(CrwParserTest, EncodeZeroSizeData_1817) {

    parser_.encode(blob_, pData_, 0, pCrwImage_);

    EXPECT_TRUE(blob_.empty());

}



TEST_F(CrwParserTest, EncodeNullPointerData_1817) {

    parser_.encode(blob_, nullptr, dataSize_, pCrwImage_);

    EXPECT_TRUE(blob_.empty());

}



TEST_F(CrwParserTest, EncodeNullPointerImage_1817) {

    EXPECT_THROW(parser_.encode(blob_, pData_, dataSize_, nullptr), std::exception);

}



TEST_F(CrwParserTest, EncodeBoundaryConditionMaxSize_1817) {

    size_t maxSize = 1024 * 1024; // Example large size

    std::vector<byte> largeData(maxSize, 0xFF);

    parser_.encode(blob_, largeData.data(), maxSize, pCrwImage_);

    EXPECT_FALSE(blob_.empty());

}



TEST_F(CrwParserTest, EncodeBoundaryConditionMinSize_1817) {

    parser_.encode(blob_, pData_, 1, pCrwImage_);

    EXPECT_FALSE(blob_.empty());

}

#include <gtest/gtest.h>

#include "Stream.h"

#include <memory>



class CCITTFaxStreamTest_187 : public ::testing::Test {

protected:

    void SetUp() override {

        stream = std::make_unique<CCITTFaxStream>(

            nullptr, 0, false, false, 1728, 2200, true, false, 5);

    }



    std::unique_ptr<CCITTFaxStream> stream;

};



TEST_F(CCITTFaxStreamTest_187, GetKind_ReturnsCorrectType_187) {

    EXPECT_EQ(stream->getKind(), strCCITTFax);

}



TEST_F(CCITTFaxStreamTest_187, Rewind_ReturnsFalseWhenNotImplemented_187) {

    EXPECT_FALSE(stream->rewind());

}



TEST_F(CCITTFaxStreamTest_187, LookChar_ReturnsNegativeOneWhenNotImplemented_187) {

    EXPECT_EQ(stream->lookChar(), -1);

}



TEST_F(CCITTFaxStreamTest_187, GetPSFilter_ReturnsEmptyOptional_187) {

    EXPECT_FALSE(stream->getPSFilter(0, "").has_value());

}



TEST_F(CCITTFaxStreamTest_187, IsBinary_ReturnsTrueForBinaryStream_187) {

    EXPECT_TRUE(stream->isBinary(false));

}



TEST_F(CCITTFaxStreamTest_187, UnfilteredRewind_ReturnsFalseWhenNotImplemented_187) {

    EXPECT_FALSE(stream->unfilteredRewind());

}



TEST_F(CCITTFaxStreamTest_187, GetEncoding_ReturnsCorrectValue_187) {

    EXPECT_EQ(stream->getEncoding(), 0);

}



TEST_F(CCITTFaxStreamTest_187, GetEndOfLine_ReturnsFalseWhenNotSet_187) {

    EXPECT_FALSE(stream->getEndOfLine());

}



TEST_F(CCITTFaxStreamTest_187, GetEncodedByteAlign_ReturnsFalseWhenNotSet_187) {

    EXPECT_FALSE(stream->getEncodedByteAlign());

}



TEST_F(CCITTFaxStreamTest_187, GetEndOfBlock_ReturnsTrueWhenSet_187) {

    EXPECT_TRUE(stream->getEndOfBlock());

}



TEST_F(CCITTFaxStreamTest_187, GetColumns_ReturnsCorrectValue_187) {

    EXPECT_EQ(stream->getColumns(), 1728);

}



TEST_F(CCITTFaxStreamTest_187, GetBlackIs1_ReturnsFalseWhenNotSet_187) {

    EXPECT_FALSE(stream->getBlackIs1());

}



TEST_F(CCITTFaxStreamTest_187, GetDamagedRowsBeforeError_ReturnsCorrectValue_187) {

    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 5);

}

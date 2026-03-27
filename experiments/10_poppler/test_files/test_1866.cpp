#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/ImageEmbeddingUtils.h"

#include "TestProjects/poppler/goo/gfile.h"

#include "TestProjects/poppler/poppler/XRef.h"

#include "TestProjects/poppler/poppler/Error.h"



using namespace ImageEmbeddingUtils;

using namespace testing;



class MockXRef : public XRef {

public:

    MOCK_METHOD(Ref, addStreamObject, (Dict*, std::vector<char>, StreamCompression), (override));

};



class MockGooFile : public GooFile {

public:

    explicit MockGooFile(int fdA) : GooFile(fdA) {}



    MOCK_CONST_METHOD3(read, int(char *, int, Goffset));

    MOCK_CONST_METHOD0(size, Goffset());

};



TEST(ImageEmbeddingUtilsTest_1866, EmbedPngImageNormalOperation_1866) {

    MockXRef mockXRef;

    MockGooFile mockGooFile(42);



    EXPECT_CALL(mockGooFile, size()).WillOnce(Return(50));

    EXPECT_CALL(mockGooFile, read(_, 50, 0))

        .WillOnce(DoAll(SetArrayArgument<0>(PNG_MAGIC_NUM, PNG_MAGIC_NUM + sizeof(PNG_MAGIC_NUM)),

                        Return(sizeof(PNG_MAGIC_NUM))));



    Ref result = embed(&mockXRef, mockGooFile);

    EXPECT_NE(result, Ref::INVALID());

}



TEST(ImageEmbeddingUtilsTest_1866, EmbedJpegImageNormalOperation_1866) {

    MockXRef mockXRef;

    MockGooFile mockGooFile(42);



    EXPECT_CALL(mockGooFile, size()).WillOnce(Return(50));

    EXPECT_CALL(mockGooFile, read(_, 50, 0))

        .WillOnce(DoAll(SetArrayArgument<0>(JPEG_MAGIC_NUM, JPEG_MAGIC_NUM + sizeof(JPEG_MAGIC_NUM)),

                        Return(sizeof(JPEG_MAGIC_NUM))));



    Ref result = embed(&mockXRef, mockGooFile);

    EXPECT_NE(result, Ref::INVALID());

}



TEST(ImageEmbeddingUtilsTest_1866, EmbedUnsupportedImageFormat_1866) {

    MockXRef mockXRef;

    MockGooFile mockGooFile(42);



    uint8_t unsupportedMagicNum[4] = {0, 0, 0, 0};



    EXPECT_CALL(mockGooFile, size()).WillOnce(Return(50));

    EXPECT_CALL(mockGooFile, read(_, 50, 0))

        .WillOnce(DoAll(SetArrayArgument<0>(unsupportedMagicNum, unsupportedMagicNum + sizeof(unsupportedMagicNum)),

                        Return(sizeof(unsupportedMagicNum))));



    Ref result = embed(&mockXRef, mockGooFile);

    EXPECT_EQ(result, Ref::INVALID());

}



TEST(ImageEmbeddingUtilsTest_1866, EmbedJpeg2000ImageUnsupported_1866) {

    MockXRef mockXRef;

    MockGooFile mockGooFile(42);



    EXPECT_CALL(mockGooFile, size()).WillOnce(Return(50));

    EXPECT_CALL(mockGooFile, read(_, 50, 0))

        .WillOnce(DoAll(SetArrayArgument<0>(JPEG2000_MAGIC_NUM, JPEG2000_MAGIC_NUM + sizeof(JPEG2000_MAGIC_NUM)),

                        Return(sizeof(JPEG2000_MAGIC_NUM))));



    Ref result = embed(&mockXRef, mockGooFile);

    EXPECT_EQ(result, Ref::INVALID());

}



TEST(ImageEmbeddingUtilsTest_1866, EmbedImageFileSizeTooSmall_1866) {

    MockXRef mockXRef;

    MockGooFile mockGooFile(42);



    EXPECT_CALL(mockGooFile, size()).WillOnce(Return(MAX_MAGIC_NUM_SIZE - 1));

    EXPECT_CALL(mockGooFile, read(_, _, _)).Times(0);



    Ref result = embed(&mockXRef, mockGooFile);

    EXPECT_EQ(result, Ref::INVALID());

}



TEST(ImageEmbeddingUtilsTest_1866, EmbedImageFileSizeTooLarge_1866) {

    MockXRef mockXRef;

    MockGooFile mockGooFile(42);



    EXPECT_CALL(mockGooFile, size()).WillOnce(Return(std::numeric_limits<int>::max() + 1));

    EXPECT_CALL(mockGooFile, read(_, _, _)).Times(0);



    Ref result = embed(&mockXRef, mockGooFile);

    EXPECT_EQ(result, Ref::INVALID());

}



TEST(ImageEmbeddingUtilsTest_1866, EmbedImageReadError_1866) {

    MockXRef mockXRef;

    MockGooFile mockGooFile(42);



    EXPECT_CALL(mockGooFile, size()).WillOnce(Return(50));

    EXPECT_CALL(mockGooFile, read(_, 50, 0)).WillOnce(Return(-1));



    Ref result = embed(&mockXRef, mockGooFile);

    EXPECT_EQ(result, Ref::INVALID());

}



TEST(ImageEmbeddingUtilsTest_1866, EmbedImagePartialRead_1866) {

    MockXRef mockXRef;

    MockGooFile mockGooFile(42);



    EXPECT_CALL(mockGooFile, size()).WillOnce(Return(50));

    EXPECT_CALL(mockGooFile, read(_, 50, 0)).WillOnce(Return(10));



    Ref result = embed(&mockXRef, mockGooFile);

    EXPECT_EQ(result, Ref::INVALID());

}

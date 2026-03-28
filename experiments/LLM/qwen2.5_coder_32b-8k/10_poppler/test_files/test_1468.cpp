#include <gtest/gtest.h>

#include "JPEG2000Stream.h"

#include "Stream.h"



class JPXStreamTest_1468 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_stream = std::make_unique<MockStream>();

        jpx_stream = std::make_unique<JPXStream>(std::move(mock_stream));

    }



    void TearDown() override {}



    class MockStream : public Stream {

    public:

        MOCK_METHOD(int, doGetChars, (int nChars, unsigned char *buffer), (override));

        MOCK_METHOD(bool, rewind, (), (override));

        MOCK_METHOD(void, close, (), (override));

        MOCK_METHOD(Goffset, getPos, (), (override));

        MOCK_METHOD(StreamKind, getKind, (), (const override));

        MOCK_METHOD(int, getChar, (), (override));

        MOCK_METHOD(int, lookChar, (), (override));

        MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));

        MOCK_METHOD(bool, isBinary, (bool last), (const override));

        MOCK_METHOD(BaseStream*, getBaseStream, (), (override));

        MOCK_METHOD(Stream*, getUndecodedStream, (), (override));

        MOCK_METHOD(Dict*, getDict, (), (override));

        MOCK_METHOD(Object*, getDictObject, (), (override));

        MOCK_METHOD(Stream*, getNextStream, (), (const override));

        MOCK_METHOD(int, getUnfilteredChar, (), (override));

        MOCK_METHOD(bool, unfilteredRewind, (), (override));

    };



    std::unique_ptr<MockStream> mock_stream;

    std::unique_ptr<JPXStream> jpx_stream;

};



TEST_F(JPXStreamTest_1468, ReadStream_NormalOperation_1468) {

    unsigned char buffer[5];

    EXPECT_CALL(*mock_stream, doGetChars(5, testing::_)).WillOnce(testing::Return(5));

    int result = jpx_stream->readStream(5, buffer);

    EXPECT_EQ(result, 5);

}



TEST_F(JPXStreamTest_1468, ReadStream_ZeroCharacters_1468) {

    unsigned char buffer[5];

    EXPECT_CALL(*mock_stream, doGetChars(0, testing::_)).WillOnce(testing::Return(0));

    int result = jpx_stream->readStream(0, buffer);

    EXPECT_EQ(result, 0);

}



TEST_F(JPXStreamTest_1468, ReadStream_LessThanRequestedCharacters_1468) {

    unsigned char buffer[5];

    EXPECT_CALL(*mock_stream, doGetChars(5, testing::_)).WillOnce(testing::Return(3));

    int result = jpx_stream->readStream(5, buffer);

    EXPECT_EQ(result, 3);

}



TEST_F(JPXStreamTest_1468, ReadStream_ExceptionalCase_NegativeCharacters_1468) {

    unsigned char buffer[5];

    EXPECT_CALL(*mock_stream, doGetChars(-5, testing::_)).WillOnce(testing::Return(-1));

    int result = jpx_stream->readStream(-5, buffer);

    EXPECT_EQ(result, -1);

}



TEST_F(JPXStreamTest_1468, ReadStream_ExceptionalCase_NullBuffer_1468) {

    EXPECT_CALL(*mock_stream, doGetChars(5, testing::_)).WillOnce(testing::Return(0));

    int result = jpx_stream->readStream(5, nullptr);

    // Since the buffer is null, we expect an exceptional case to be handled internally.

    // The exact behavior is not specified, but we can assume it returns 0 or some error code.

    EXPECT_EQ(result, 0);

}



TEST_F(JPXStreamTest_1468, Rewind_NormalOperation_1468) {

    EXPECT_CALL(*mock_stream, rewind()).WillOnce(testing::Return(true));

    bool result = jpx_stream->rewind();

    EXPECT_TRUE(result);

}



TEST_F(JPXStreamTest_1468, Close_NormalOperation_1468) {

    EXPECT_CALL(*mock_stream, close());

    jpx_stream->close();

}



TEST_F(JPXStreamTest_1468, GetPos_NormalOperation_1468) {

    Goffset expected_pos = 123;

    EXPECT_CALL(*mock_stream, getPos()).WillOnce(testing::Return(expected_pos));

    Goffset result = jpx_stream->getPos();

    EXPECT_EQ(result, expected_pos);

}



TEST_F(JPXStreamTest_1468, GetChar_NormalOperation_1468) {

    int expected_char = 97; // ASCII 'a'

    EXPECT_CALL(*mock_stream, getChar()).WillOnce(testing::Return(expected_char));

    int result = jpx_stream->getChar();

    EXPECT_EQ(result, expected_char);

}



TEST_F(JPXStreamTest_1468, LookChar_NormalOperation_1468) {

    int expected_char = 97; // ASCII 'a'

    EXPECT_CALL(*mock_stream, lookChar()).WillOnce(testing::Return(expected_char));

    int result = jpx_stream->lookChar();

    EXPECT_EQ(result, expected_char);

}



TEST_F(JPXStreamTest_1468, GetPSFilter_NormalOperation_1468) {

    std::optional<std::string> expected_filter = "DCTDecode";

    EXPECT_CALL(*mock_stream, getPSFilter(testing::_, testing::_)).WillOnce(testing::Return(expected_filter));

    auto result = jpx_stream->getPSFilter(0, "");

    EXPECT_EQ(result, expected_filter);

}



TEST_F(JPXStreamTest_1468, IsBinary_NormalOperation_1468) {

    bool expected_is_binary = true;

    EXPECT_CALL(*mock_stream, isBinary(testing::_)).WillOnce(testing::Return(expected_is_binary));

    bool result = jpx_stream->isBinary(false);

    EXPECT_EQ(result, expected_is_binary);

}



TEST_F(JPXStreamTest_1468, GetBaseStream_NormalOperation_1468) {

    BaseStream* expected_base_stream = new BaseStream();

    EXPECT_CALL(*mock_stream, getBaseStream()).WillOnce(testing::Return(expected_base_stream));

    BaseStream* result = jpx_stream->getBaseStream();

    EXPECT_EQ(result, expected_base_stream);

}



TEST_F(JPXStreamTest_1468, GetUndecodedStream_NormalOperation_1468) {

    Stream* expected_undecoded_stream = new Stream();

    EXPECT_CALL(*mock_stream, getUndecodedStream()).WillOnce(testing::Return(expected_undecoded_stream));

    Stream* result = jpx_stream->getUndecodedStream();

    EXPECT_EQ(result, expected_undecoded_stream);

}



TEST_F(JPXStreamTest_1468, GetDict_NormalOperation_1468) {

    Dict* expected_dict = new Dict();

    EXPECT_CALL(*mock_stream, getDict()).WillOnce(testing::Return(expected_dict));

    Dict* result = jpx_stream->getDict();

    EXPECT_EQ(result, expected_dict);

}



TEST_F(JPXStreamTest_1468, GetDictObject_NormalOperation_1468) {

    Object* expected_dict_object = new Object();

    EXPECT_CALL(*mock_stream, getDictObject()).WillOnce(testing::Return(expected_dict_object));

    Object* result = jpx_stream->getDictObject();

    EXPECT_EQ(result, expected_dict_object);

}



TEST_F(JPXStreamTest_1468, GetNextStream_NormalOperation_1468) {

    Stream* expected_next_stream = new Stream();

    EXPECT_CALL(*mock_stream, getNextStream()).WillOnce(testing::Return(expected_next_stream));

    Stream* result = jpx_stream->getNextStream();

    EXPECT_EQ(result, expected_next_stream);

}



TEST_F(JPXStreamTest_1468, GetUnfilteredChar_NormalOperation_1468) {

    int expected_char = 97; // ASCII 'a'

    EXPECT_CALL(*mock_stream, getUnfilteredChar()).WillOnce(testing::Return(expected_char));

    int result = jpx_stream->getUnfilteredChar();

    EXPECT_EQ(result, expected_char);

}



TEST_F(JPXStreamTest_1468, UnfilteredRewind_NormalOperation_1468) {

    EXPECT_CALL(*mock_stream, unfilteredRewind()).WillOnce(testing::Return(true));

    bool result = jpx_stream->unfilteredRewind();

    EXPECT_TRUE(result);

}

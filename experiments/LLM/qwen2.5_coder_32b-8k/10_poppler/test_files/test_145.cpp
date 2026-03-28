#include <gtest/gtest.h>

#include <gmock/gmock.h>



using ::testing::NiceMock;

using ::testing::Return;



// Mock class for Stream

class MockStream : public Stream {

public:

    MOCK_METHOD(int, getUnfilteredChar, (), (override));

};



TEST_F(FilterStreamTest_145, GetUnfilteredChar_NormalOperation_145) {

    NiceMock<MockStream> mockStream;

    EXPECT_CALL(mockStream, getUnfilteredChar()).WillOnce(Return(42));



    FilterStream filterStream(&mockStream);

    int result = filterStream.getUnfilteredChar();

    

    EXPECT_EQ(result, 42);

}



TEST_F(FilterStreamTest_145, GetUnfilteredChar_ReturnsEOF_145) {

    NiceMock<MockStream> mockStream;

    EXPECT_CALL(mockStream, getUnfilteredChar()).WillOnce(Return(-1));



    FilterStream filterStream(&mockStream);

    int result = filterStream.getUnfilteredChar();

    

    EXPECT_EQ(result, -1);

}



TEST_F(FilterStreamTest_145, Close_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    EXPECT_CALL(mockStream, close());



    FilterStream filterStream(&mockStream);

    filterStream.close();

}



TEST_F(FilterStreamTest_145, SetPos_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    Goffset pos = 1024;

    int dir = 0;



    EXPECT_CALL(mockStream, setPos(pos, dir));



    FilterStream filterStream(&mockStream);

    filterStream.setPos(pos, dir);

}



TEST_F(FilterStreamTest_145, GetPos_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    Goffset expectedPos = 2048;



    EXPECT_CALL(mockStream, getPos()).WillOnce(Return(expectedPos));



    FilterStream filterStream(&mockStream);

    Goffset result = filterStream.getPos();

    

    EXPECT_EQ(result, expectedPos);

}



TEST_F(FilterStreamTest_145, GetBaseStream_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    BaseStream* expectedBaseStream = nullptr;



    EXPECT_CALL(mockStream, getBaseStream()).WillOnce(Return(expectedBaseStream));



    FilterStream filterStream(&mockStream);

    BaseStream* result = filterStream.getBaseStream();

    

    EXPECT_EQ(result, expectedBaseStream);

}



TEST_F(FilterStreamTest_145, GetUndecodedStream_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    Stream* expectedUndecodedStream = nullptr;



    EXPECT_CALL(mockStream, getUndecodedStream()).WillOnce(Return(expectedUndecodedStream));



    FilterStream filterStream(&mockStream);

    Stream* result = filterStream.getUndecodedStream();

    

    EXPECT_EQ(result, expectedUndecodedStream);

}



TEST_F(FilterStreamTest_145, GetDict_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    Dict* expectedDict = nullptr;



    EXPECT_CALL(mockStream, getDict()).WillOnce(Return(expectedDict));



    FilterStream filterStream(&mockStream);

    Dict* result = filterStream.getDict();

    

    EXPECT_EQ(result, expectedDict);

}



TEST_F(FilterStreamTest_145, GetDictObject_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    Object* expectedDictObject = nullptr;



    EXPECT_CALL(mockStream, getDictObject()).WillOnce(Return(expectedDictObject));



    FilterStream filterStream(&mockStream);

    Object* result = filterStream.getDictObject();

    

    EXPECT_EQ(result, expectedDictObject);

}



TEST_F(FilterStreamTest_145, GetNextStream_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    Stream* expectedNextStream = nullptr;



    EXPECT_CALL(mockStream, getNextStream()).WillOnce(Return(expectedNextStream));



    FilterStream filterStream(&mockStream);

    Stream* result = filterStream.getNextStream();

    

    EXPECT_EQ(result, expectedNextStream);

}



TEST_F(FilterStreamTest_145, UnfilteredRewind_DelegatesToBaseStream_145) {

    NiceMock<MockStream> mockStream;

    EXPECT_CALL(mockStream, unfilteredRewind()).WillOnce(Return(true));



    FilterStream filterStream(&mockStream);

    bool result = filterStream.unfilteredRewind();

    

    EXPECT_TRUE(result);

}



TEST_F(FilterStreamTest_145, UnfilteredRewind_Fails_145) {

    NiceMock<MockStream> mockStream;

    EXPECT_CALL(mockStream, unfilteredRewind()).WillOnce(Return(false));



    FilterStream filterStream(&mockStream);

    bool result = filterStream.unfilteredRewind();

    

    EXPECT_FALSE(result);

}

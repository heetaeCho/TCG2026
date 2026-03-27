#include <gtest/gtest.h>

#include "Stream.h"

#include <gmock/gmock.h>



using namespace testing;



class MockBaseStream : public BaseStream {

public:

    MockBaseStream(Object &&dictA, Goffset lengthA) : BaseStream(std::move(dictA), lengthA) {}



    MOCK_METHOD0(getLength, Goffset());

    MOCK_METHOD1(setPos, void(Goffset pos));

    MOCK_METHOD0(getStart, Goffset());

    MOCK_METHOD1(moveStart, void(Goffset delta));

    MOCK_CONST_METHOD1(isBinary, bool(bool last));

    MOCK_METHOD0(getBaseStream, BaseStream*());

    MOCK_METHOD0(getUndecodedStream, Stream*());

    MOCK_METHOD0(getDict, Dict*());

    MOCK_METHOD0(getDictObject, Object*());

    MOCK_METHOD0(getFileName, GooString*());

};



TEST_F(BaseStreamTest_131, GetLength_ReturnsExpectedValue_131) {

    MockBaseStream mockStream(Object(), 1234);

    EXPECT_CALL(mockStream, getLength()).WillOnce(Return(1234));



    Goffset length = mockStream.getLength();

    EXPECT_EQ(length, 1234);

}



TEST_F(BaseStreamTest_131, SetPos_CallsExpectedFunction_131) {

    MockBaseStream mockStream(Object(), 0);

    EXPECT_CALL(mockStream, setPos(5678));



    mockStream.setPos(5678);

}



TEST_F(BaseStreamTest_131, GetStart_ReturnsExpectedValue_131) {

    MockBaseStream mockStream(Object(), 0);

    EXPECT_CALL(mockStream, getStart()).WillOnce(Return(91011));



    Goffset start = mockStream.getStart();

    EXPECT_EQ(start, 91011);

}



TEST_F(BaseStreamTest_131, MoveStart_CallsExpectedFunction_131) {

    MockBaseStream mockStream(Object(), 0);

    EXPECT_CALL(mockStream, moveStart(1213));



    mockStream.moveStart(1213);

}



TEST_F(BaseStreamTest_131, IsBinary_ReturnsExpectedValue_131) {

    MockBaseStream mockStream(Object(), 0);

    EXPECT_CALL(mockStream, isBinary(true)).WillOnce(Return(true));

    EXPECT_CALL(mockStream, isBinary(false)).WillOnce(Return(false));



    bool isBinaryTrue = mockStream.isBinary(true);

    bool isBinaryFalse = mockStream.isBinary(false);



    EXPECT_TRUE(isBinaryTrue);

    EXPECT_FALSE(isBinaryFalse);

}



TEST_F(BaseStreamTest_131, GetBaseStream_ReturnsExpectedValue_131) {

    MockBaseStream mockStream(Object(), 0);

    BaseStream* expectedBaseStream = &mockStream;

    EXPECT_CALL(mockStream, getBaseStream()).WillOnce(Return(expectedBaseStream));



    BaseStream* baseStream = mockStream.getBaseStream();

    EXPECT_EQ(baseStream, expectedBaseStream);

}



TEST_F(BaseStreamTest_131, GetUndecodedStream_ReturnsExpectedValue_131) {

    MockBaseStream mockStream(Object(), 0);

    Stream* expectedUndecodedStream = &mockStream;

    EXPECT_CALL(mockStream, getUndecodedStream()).WillOnce(Return(expectedUndecodedStream));



    Stream* undecodedStream = mockStream.getUndecodedStream();

    EXPECT_EQ(undecodedStream, expectedUndecodedStream);

}



TEST_F(BaseStreamTest_131, GetDict_ReturnsExpectedValue_131) {

    MockBaseStream mockStream(Object(), 0);

    Dict* expectedDict = new Dict;

    EXPECT_CALL(mockStream, getDict()).WillOnce(Return(expectedDict));



    Dict* dict = mockStream.getDict();

    EXPECT_EQ(dict, expectedDict);



    delete expectedDict; // Clean up

}



TEST_F(BaseStreamTest_131, GetDictObject_ReturnsExpectedValue_131) {

    MockBaseStream mockStream(Object(), 0);

    Object* expectedDictObject = new Object;

    EXPECT_CALL(mockStream, getDictObject()).WillOnce(Return(expectedDictObject));



    Object* dictObject = mockStream.getDictObject();

    EXPECT_EQ(dictObject, expectedDictObject);



    delete expectedDictObject; // Clean up

}



TEST_F(BaseStreamTest_131, GetFileName_ReturnsExpectedValue_131) {

    MockBaseStream mockStream(Object(), 0);

    GooString* expectedFileName = new GooString("testfile.pdf");

    EXPECT_CALL(mockStream, getFileName()).WillOnce(Return(expectedFileName));



    GooString* fileName = mockStream.getFileName();

    EXPECT_EQ(fileName->cmp("testfile.pdf"), 0);



    delete expectedFileName; // Clean up

}

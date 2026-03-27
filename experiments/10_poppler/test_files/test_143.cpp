#include <gtest/gtest.h>

#include "Stream.h"



using namespace poppler;



class FilterStreamTest_143 : public ::testing::Test {

protected:

    Stream* mockStream;

    FilterStream* filterStream;



    void SetUp() override {

        mockStream = new Stream();

        filterStream = new FilterStream(mockStream);

    }



    void TearDown() override {

        delete filterStream;

        delete mockStream;

    }

};



TEST_F(FilterStreamTest_143, GetDictObject_ReturnsCorrectObject_143) {

    // Arrange

    Object* expectedObject = new Object();

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(::testing::Return(expectedObject));



    // Act

    Object* result = filterStream->getDictObject();



    // Assert

    EXPECT_EQ(result, expectedObject);

}



TEST_F(FilterStreamTest_143, Close_CallsBaseClose_143) {

    // Arrange

    EXPECT_CALL(*mockStream, close());



    // Act

    filterStream->close();

}



TEST_F(FilterStreamTest_143, SetPos_CallsBaseSetPosWithSameParameters_143) {

    // Arrange

    Goffset pos = 1024;

    int dir = 0;

    EXPECT_CALL(*mockStream, setPos(pos, dir));



    // Act

    filterStream->setPos(pos, dir);

}



TEST_F(FilterStreamTest_143, GetPos_ReturnsBaseGetPosValue_143) {

    // Arrange

    Goffset expectedPos = 2048;

    EXPECT_CALL(*mockStream, getPos()).WillOnce(::testing::Return(expectedPos));



    // Act

    Goffset result = filterStream->getPos();



    // Assert

    EXPECT_EQ(result, expectedPos);

}



TEST_F(FilterStreamTest_143, GetBaseStream_ReturnsBaseGetBaseStreamValue_143) {

    // Arrange

    BaseStream* expectedBaseStream = new BaseStream();

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(::testing::Return(expectedBaseStream));



    // Act

    BaseStream* result = filterStream->getBaseStream();



    // Assert

    EXPECT_EQ(result, expectedBaseStream);



    delete expectedBaseStream;

}



TEST_F(FilterStreamTest_143, GetUndecodedStream_ReturnsBaseGetUndecodedStreamValue_143) {

    // Arrange

    Stream* expectedUndecodedStream = new Stream();

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(::testing::Return(expectedUndecodedStream));



    // Act

    Stream* result = filterStream->getUndecodedStream();



    // Assert

    EXPECT_EQ(result, expectedUndecodedStream);



    delete expectedUndecodedStream;

}



TEST_F(FilterStreamTest_143, GetDict_ReturnsBaseGetDictValue_143) {

    // Arrange

    Dict* expectedDict = new Dict();

    EXPECT_CALL(*mockStream, getDict()).WillOnce(::testing::Return(expectedDict));



    // Act

    Dict* result = filterStream->getDict();



    // Assert

    EXPECT_EQ(result, expectedDict);



    delete expectedDict;

}



TEST_F(FilterStreamTest_143, GetNextStream_ReturnsBaseGetNextStreamValue_143) {

    // Arrange

    Stream* expectedNextStream = new Stream();

    EXPECT_CALL(*mockStream, getNextStream()).WillOnce(::testing::Return(expectedNextStream));



    // Act

    Stream* result = filterStream->getNextStream();



    // Assert

    EXPECT_EQ(result, expectedNextStream);



    delete expectedNextStream;

}



TEST_F(FilterStreamTest_143, GetUnfilteredChar_ReturnsBaseGetUnfilteredCharValue_143) {

    // Arrange

    int expectedChar = 'A';

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(::testing::Return(expectedChar));



    // Act

    int result = filterStream->getUnfilteredChar();



    // Assert

    EXPECT_EQ(result, expectedChar);

}



TEST_F(FilterStreamTest_143, UnfilteredRewind_CallsBaseUnfilteredRewindAndReturnsValue_143) {

    // Arrange

    bool expectedResult = true;

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(::testing::Return(expectedResult));



    // Act

    bool result = filterStream->unfilteredRewind();



    // Assert

    EXPECT_EQ(result, expectedResult);

}

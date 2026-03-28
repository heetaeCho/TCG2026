#include <gtest/gtest.h>

#include "Stream.h"



class FilterStreamTest_144 : public ::testing::Test {

protected:

    Stream mockStream;

    FilterStream filterStream;



    FilterStreamTest_144() : filterStream(&mockStream) {}

};



TEST_F(FilterStreamTest_144, getNextStream_ReturnsStrPointer_144) {

    EXPECT_EQ(filterStream.getNextStream(), &mockStream);

}



TEST_F(FilterStreamTest_144, close_DoesNotThrowException_144) {

    EXPECT_NO_THROW(filterStream.close());

}



TEST_F(FilterStreamTest_144, setPos_DoesNotThrowException_144) {

    EXPECT_NO_THROW(filterStream.setPos(0, 0));

}



TEST_F(FilterStreamTest_144, getPos_ReturnsZero_WhenNoSetPosCalled_144) {

    Goffset pos = filterStream.getPos();

    EXPECT_EQ(pos, 0);

}



TEST_F(FilterStreamTest_144, getBaseStream_DoesNotThrowException_144) {

    EXPECT_NO_THROW(filterStream.getBaseStream());

}



TEST_F(FilterStreamTest_144, getUndecodedStream_ReturnsStrPointer_144) {

    EXPECT_EQ(filterStream.getUndecodedStream(), &mockStream);

}



TEST_F(FilterStreamTest_144, getDict_DoesNotThrowException_144) {

    EXPECT_NO_THROW(filterStream.getDict());

}



TEST_F(FilterStreamTest_144, getDictObject_DoesNotThrowException_144) {

    EXPECT_NO_THROW(filterStream.getDictObject());

}



TEST_F(FilterStreamTest_144, getUnfilteredChar_ReturnsZero_WhenNoDataAvailable_144) {

    int result = filterStream.getUnfilteredChar();

    EXPECT_EQ(result, 0);

}



TEST_F(FilterStreamTest_144, unfilteredRewind_ReturnsFalse_WhenNotImplemented_144) {

    bool result = filterStream.unfilteredRewind();

    EXPECT_FALSE(result);

}

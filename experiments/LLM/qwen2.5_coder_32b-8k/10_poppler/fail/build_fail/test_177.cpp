#include <gtest/gtest.h>

#include "Stream.h"

#include <memory>



using namespace std;



// Mock class for Stream to simulate external dependency

class MockStream : public Stream {

public:

    MOCK_METHOD(int, getUnfilteredChar, (), (override));

};



class EmbedStreamTest_177 : public ::testing::Test {

protected:

    unique_ptr<MockStream> mockStream;

    Object dict;

    bool limited = true;

    Goffset length = 1024;

    bool reusable = false;



    void SetUp() override {

        mockStream = make_unique<MockStream>();

    }

};



TEST_F(EmbedStreamTest_177, GetUnfilteredChar_DelegatesToBaseStream_177) {

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(::testing::Return(42));



    EmbedStream embedStream(mockStream.get(), move(dict), limited, length, reusable);

    int result = embedStream.getUnfilteredChar();



    EXPECT_EQ(result, 42);

}



TEST_F(EmbedStreamTest_177, GetUnfilteredChar_ReturnsMinusOneOnEOF_177) {

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(::testing::Return(-1));



    EmbedStream embedStream(mockStream.get(), move(dict), limited, length, reusable);

    int result = embedStream.getUnfilteredChar();



    EXPECT_EQ(result, -1);

}



TEST_F(EmbedStreamTest_177, Rewind_DelegatesToBaseStream_ReturnsTrue_177) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(true));



    EmbedStream embedStream(mockStream.get(), move(dict), limited, length, reusable);

    bool result = embedStream.rewind();



    EXPECT_TRUE(result);

}



TEST_F(EmbedStreamTest_177, Rewind_DelegatesToBaseStream_ReturnsFalseOnFailure_177) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(false));



    EmbedStream embedStream(mockStream.get(), move(dict), limited, length, reusable);

    bool result = embedStream.rewind();



    EXPECT_FALSE(result);

}



TEST_F(EmbedStreamTest_177, UnfilteredRewind_DelegatesToBaseStream_ReturnsTrue_177) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(::testing::Return(true));



    EmbedStream embedStream(mockStream.get(), move(dict), limited, length, reusable);

    bool result = embedStream.unfilteredRewind();



    EXPECT_TRUE(result);

}



TEST_F(EmbedStreamTest_177, UnfilteredRewind_DelegatesToBaseStream_ReturnsFalseOnFailure_177) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(::testing::Return(false));



    EmbedStream embedStream(mockStream.get(), move(dict), limited, length, reusable);

    bool result = embedStream.unfilteredRewind();



    EXPECT_FALSE(result);

}

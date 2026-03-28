#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <cstring>



using namespace Exiv2;



class CommentValueTest_820 : public ::testing::Test {

protected:

    CommentValue commentValue;

};



TEST_F(CommentValueTest_820, ReadWithValidBufferAndLength_820) {

    const byte buffer[] = "Sample comment";

    size_t length = sizeof(buffer) - 1; // Exclude the null terminator

    ByteOrder byteOrder = littleEndian;



    int result = commentValue.read(buffer, length, byteOrder);



    EXPECT_EQ(result, static_cast<int>(length));

}



TEST_F(CommentValueTest_820, ReadWithZeroLengthBuffer_820) {

    const byte buffer[] = "";

    size_t length = 0;

    ByteOrder byteOrder = littleEndian;



    int result = commentValue.read(buffer, length, byteOrder);



    EXPECT_EQ(result, 0);

}



TEST_F(CommentValueTest_820, ReadWithLargeBuffer_820) {

    const char* largeString = "A very long comment that exceeds typical lengths to test buffer handling capabilities.";

    const byte* buffer = reinterpret_cast<const byte*>(largeString);

    size_t length = std::strlen(largeString);

    ByteOrder byteOrder = bigEndian;



    int result = commentValue.read(buffer, length, byteOrder);



    EXPECT_EQ(result, static_cast<int>(length));

}



TEST_F(CommentValueTest_820, ReadWithNullBuffer_820) {

    const byte* buffer = nullptr;

    size_t length = 10; // Arbitrary non-zero length

    ByteOrder byteOrder = littleEndian;



    int result = commentValue.read(buffer, length, byteOrder);



    EXPECT_EQ(result, 0); // Assuming read with null buffer returns 0 or error code

}



TEST_F(CommentValueTest_820, ReadWithDifferentByteOrders_820) {

    const byte buffer[] = "Sample comment";

    size_t length = sizeof(buffer) - 1; // Exclude the null terminator



    int resultLittleEndian = commentValue.read(buffer, length, littleEndian);

    int resultBigEndian = commentValue.read(buffer, length, bigEndian);



    EXPECT_EQ(resultLittleEndian, static_cast<int>(length));

    EXPECT_EQ(resultBigEndian, static_cast<int>(length));

}

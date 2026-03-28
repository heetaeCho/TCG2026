#include <gtest/gtest.h>

#include <exiv2/types.hpp>



using namespace Exiv2::Internal;



// Test fixture for equalsQTimeTag function

class EqualsQTimeTagTest_653 : public ::testing::Test {

protected:

    Exiv2::DataBuf buffer;

};



TEST_F(EqualsQTimeTagTest_653, NormalOperationLowerCase_653) {

    const char str[] = "qtst";

    buffer.alloc(4);

    buffer.write_uint8(0, 'q');

    buffer.write_uint8(1, 't');

    buffer.write_uint8(2, 's');

    buffer.write_uint8(3, 't');



    EXPECT_TRUE(equalsQTimeTag(buffer, str));

}



TEST_F(EqualsQTimeTagTest_653, NormalOperationUpperCase_653) {

    const char str[] = "QTST";

    buffer.alloc(4);

    buffer.write_uint8(0, 'q');

    buffer.write_uint8(1, 't');

    buffer.write_uint8(2, 's');

    buffer.write_uint8(3, 't');



    EXPECT_TRUE(equalsQTimeTag(buffer, str));

}



TEST_F(EqualsQTimeTagTest_653, DifferentCaseMismatch_653) {

    const char str[] = "qtsT";

    buffer.alloc(4);

    buffer.write_uint8(0, 'Q');

    buffer.write_uint8(1, 't');

    buffer.write_uint8(2, 's');

    buffer.write_uint8(3, 't');



    EXPECT_TRUE(equalsQTimeTag(buffer, str));

}



TEST_F(EqualsQTimeTagTest_653, DifferentStringMismatch_653) {

    const char str[] = "abcd";

    buffer.alloc(4);

    buffer.write_uint8(0, 'q');

    buffer.write_uint8(1, 't');

    buffer.write_uint8(2, 's');

    buffer.write_uint8(3, 't');



    EXPECT_FALSE(equalsQTimeTag(buffer, str));

}



TEST_F(EqualsQTimeTagTest_653, BufferTooShortMismatch_653) {

    const char str[] = "qtst";

    buffer.alloc(3);

    buffer.write_uint8(0, 'q');

    buffer.write_uint8(1, 't');

    buffer.write_uint8(2, 's');



    EXPECT_FALSE(equalsQTimeTag(buffer, str));

}



TEST_F(EqualsQTimeTagTest_653, BufferTooLongMismatch_653) {

    const char str[] = "qtst";

    buffer.alloc(5);

    buffer.write_uint8(0, 'q');

    buffer.write_uint8(1, 't');

    buffer.write_uint8(2, 's');

    buffer.write_uint8(3, 't');



    EXPECT_TRUE(equalsQTimeTag(buffer, str));

}



TEST_F(EqualsQTimeTagTest_653, EmptyStringMismatch_653) {

    const char str[] = "";

    buffer.alloc(4);

    buffer.write_uint8(0, 'q');

    buffer.write_uint8(1, 't');

    buffer.write_uint8(2, 's');

    buffer.write_uint8(3, 't');



    EXPECT_FALSE(equalsQTimeTag(buffer, str));

}



TEST_F(EqualsQTimeTagTest_653, EmptyBufferMismatch_653) {

    const char str[] = "qtst";

    buffer.alloc(0);



    EXPECT_FALSE(equalsQTimeTag(buffer, str));

}

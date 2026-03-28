#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



using ::testing::_;

using ::testing::Invoke;

using ::testing::Return;



// Mock function signature for XMP_TextOutputProc

class MockXMP_TextOutputProc {

public:

    MOCK_METHOD3(Call, XMP_Status(void* refCon, const char* buffer, size_t count));

};



extern "C" {

    XMP_Status DumpClearString(const XMP_VarString &value, XMP_TextOutputProc outProc, void *refCon) {

        // Placeholder for the actual implementation

        return 0;

    }

}



// Adapter to use with Google Mock

XMP_Status TextOutputAdapter(void* refCon, const char* buffer, size_t count) {

    return static_cast<MockXMP_TextOutputProc*>(refCon)->Call(refCon, buffer, count);

}



class DumpClearStringTest : public ::testing::Test {

protected:

    MockXMP_TextOutputProc mockOutProc;

};



TEST_F(DumpClearStringTest, NormalOperation_2138) {

    XMP_VarString value = "Hello, World!";

    EXPECT_CALL(mockOutProc, Call(_, "Hello, World!", 13)).Times(1).WillOnce(Return(0));



    XMP_Status status = DumpClearString(value, TextOutputAdapter, &mockOutProc);

    EXPECT_EQ(status, 0);

}



TEST_F(DumpClearStringTest, BoundaryEmptyString_2138) {

    XMP_VarString value = "";

    EXPECT_CALL(mockOutProc, Call(_, _, _)).Times(0);



    XMP_Status status = DumpClearString(value, TextOutputAdapter, &mockOutProc);

    EXPECT_EQ(status, 0);

}



TEST_F(DumpClearStringTest, BoundarySingleNormalChar_2138) {

    XMP_VarString value = "A";

    EXPECT_CALL(mockOutProc, Call(_, "A", 1)).Times(1).WillOnce(Return(0));



    XMP_Status status = DumpClearString(value, TextOutputAdapter, &mockOutProc);

    EXPECT_EQ(status, 0);

}



TEST_F(DumpClearStringTest, BoundarySingleNonPrintableChar_2138) {

    XMP_VarString value = "\x09"; // Tab character

    EXPECT_CALL(mockOutProc, Call(_, "<\t>", 3)).Times(1).WillOnce(Return(0));



    XMP_Status status = DumpClearString(value, TextOutputAdapter, &mockOutProc);

    EXPECT_EQ(status, 0);

}



TEST_F(DumpClearStringTest, MixedContent_2138) {

    XMP_VarString value = "Hello\x09World!";

    EXPECT_CALL(mockOutProc, Call(_, "Hello<\t>World!", 15)).Times(1).WillOnce(Return(0));



    XMP_Status status = DumpClearString(value, TextOutputAdapter, &mockOutProc);

    EXPECT_EQ(status, 0);

}



TEST_F(DumpClearStringTest, ExceptionalNonPrintableSequence_2138) {

    XMP_VarString value = "Hello\x00World!";

    EXPECT_CALL(mockOutProc, Call(_, "Hello<\x00>World!", 17)).Times(1).WillOnce(Return(0));



    XMP_Status status = DumpClearString(value, TextOutputAdapter, &mockOutProc);

    EXPECT_EQ(status, 0);

}



TEST_F(DumpClearStringTest, ExceptionalInvalidUTF8_2138) {

    XMP_VarString value = "Hello\xC3World!";

    EXPECT_CALL(mockOutProc, Call(_, "Hello<\xC3>World!", 17)).Times(1).WillOnce(Return(0));



    XMP_Status status = DumpClearString(value, TextOutputAdapter, &mockOutProc);

    EXPECT_EQ(status, 0);

}



TEST_F(DumpClearStringTest, ExceptionalOutputFailure_2138) {

    XMP_VarString value = "Hello";

    EXPECT_CALL(mockOutProc, Call(_, "Hello", 5)).Times(1).WillOnce(Return(1));



    XMP_Status status = DumpClearString(value, TextOutputAdapter, &mockOutProc);

    EXPECT_EQ(status, 1);

}

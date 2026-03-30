#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"



using namespace testing;



class MockXMLParserAdapter : public XMLParserAdapter {

public:

    MOCK_METHOD(void, ParseBuffer, (const void* buffer, size_t length, bool last), (override));

};



class ProcessUTF8PortionTest_1973 : public Test {

protected:

    MockXMLParserAdapter mockXmlParser;

};



TEST_F(ProcessUTF8PortionTest_1973, NormalOperation_AsciiOnly_1973) {

    const XMP_Uns8 buffer[] = "HelloWorld";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("HelloWorld "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, NormalOperation_Utf8Only_1973) {

    const XMP_Uns8 buffer[] = "\xC2\xA9Copyright";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("\302\251Copyright "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, NormalOperation_MixedContent_1973) {

    const XMP_Uns8 buffer[] = "Hello\xC2\xA9World";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("Hello\302\251World "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, BoundaryCondition_EmptyBuffer_1973) {

    const XMP_Uns8 buffer[] = "";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer), true);

    EXPECT_EQ(result, 0);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq(" "), Eq(1), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, BoundaryCondition_SingleNonAscii_1973) {

    const XMP_Uns8 buffer[] = "\xC2\xA9";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("\302\251 "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, BoundaryCondition_SingleControlCharacter_Tab_1973) {

    const XMP_Uns8 buffer[] = "\t";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("\t "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, BoundaryCondition_SingleControlCharacter_LF_1973) {

    const XMP_Uns8 buffer[] = "\n";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("\n "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, BoundaryCondition_SingleControlCharacter_CR_1973) {

    const XMP_Uns8 buffer[] = "\r";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("\r "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, BoundaryCondition_SingleControlCharacter_Other_1973) {

    const XMP_Uns8 buffer[] = "\x01";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq(" "), Eq(1), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, ExceptionalCase_IncompleteUtf8Sequence_MidBuffer_1973) {

    const XMP_Uns8 buffer[] = "\xC2";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, false);

    EXPECT_EQ(result, 0);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq(" "), Eq(1), Eq(false)));

}



TEST_F(ProcessUTF8PortionTest_1973, ExceptionalCase_IncompleteUtf8Sequence_EndBuffer_1973) {

    const XMP_Uns8 buffer[] = "\xC2";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("\302\202 "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, ExceptionalCase_EscapeSequence_MidBuffer_1973) {

    const XMP_Uns8 buffer[] = "Hello&";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, false);

    EXPECT_EQ(result, 5);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("Hello "), Eq(6), Eq(false)));

}



TEST_F(ProcessUTF8PortionTest_1973, ExceptionalCase_EscapeSequence_EndBuffer_1973) {

    const XMP_Uns8 buffer[] = "Hello&";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("Hello& "), Eq(sizeof(buffer)), Eq(true)));

}



TEST_F(ProcessUTF8PortionTest_1973, ExceptionalCase_ControlCharacter_Sequence_MidBuffer_1973) {

    const XMP_Uns8 buffer[] = "Hello\x01World";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, false);

    EXPECT_EQ(result, 5);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("Hello "), Eq(6), Eq(false)));

}



TEST_F(ProcessUTF8PortionTest_1973, ExceptionalCase_ControlCharacter_Sequence_EndBuffer_1973) {

    const XMP_Uns8 buffer[] = "Hello\x01World";

    size_t result = ProcessUTF8Portion(&mockXmlParser, buffer, sizeof(buffer) - 1, true);

    EXPECT_EQ(result, sizeof(buffer) - 1);

    EXPECT_CALL(mockXmlParser, ParseBuffer(StrEq("Hello World "), Eq(sizeof(buffer)), Eq(true)));

}

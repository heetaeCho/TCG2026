#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock function for XMP_TextOutputProc

class MockTextOutputProc {

public:

    MOCK_METHOD(void, Call, (const char* buffer, std::size_t count));

};



extern "C" void OutProcNChars(const char* buffer, std::size_t count) {

    static_cast<MockTextOutputProc*>(refCon)->Call(buffer, count);

}



extern "C" void OutProcHexInt(XMP_OptionBits options) {

    // Mocking this function is not necessary for the test as we are only interested in the string outputs

}



extern "C" void OutProcLiteral(const char* literal) {

    static_cast<MockTextOutputProc*>(refCon)->Call(literal, strlen(literal));

}



// Assuming XMP_Status and XMP_OptionBits are defined somewhere

typedef unsigned long XMP_OptionBits;

typedef int XMP_Status;



extern "C" XMP_Status DumpNodeOptions(XMP_OptionBits options, void (*outProc)(const char*, std::size_t), void* refCon);



class DumpNodeOptionsTest_2140 : public ::testing::Test {

protected:

    MockTextOutputProc mockOutProc;

};



TEST_F(DumpNodeOptionsTest_2140, ZeroOptions_2140) {

    EXPECT_CALL(mockOutProc, Call("(0x0)", 5)).Times(1);



    XMP_Status status = DumpNodeOptions(0, reinterpret_cast<XMP_TextOutputProc>(&MockTextOutputProc::Call), &mockOutProc);

    EXPECT_EQ(status, 0); // Assuming success status is 0

}



TEST_F(DumpNodeOptionsTest_2140, SingleOption_2140) {

    EXPECT_CALL(mockOutProc, Call("(0x", 3)).Times(1);

    EXPECT_CALL(mockOutProc, Call("80000000", 8)).Times(1); // Hex representation of 0x80000000

    EXPECT_CALL(mockOutProc, Call(" :", 2)).Times(1);

    EXPECT_CALL(mockOutProc, Call(" schema", 7)).Times(1);

    EXPECT_CALL(mockOutProc, Call(")", 1)).Times(1);



    XMP_Status status = DumpNodeOptions(0x80000000, reinterpret_cast<XMP_TextOutputProc>(&MockTextOutputProc::Call), &mockOutProc);

    EXPECT_EQ(status, 0); // Assuming success status is 0

}



TEST_F(DumpNodeOptionsTest_2140, MultipleOptions_2140) {

    XMP_OptionBits options = 0x80000000 | 0x00080000; // schema and -BEFORE-

    EXPECT_CALL(mockOutProc, Call("(0x", 3)).Times(1);

    EXPECT_CALL(mockOutProc, Call("80080000", 8)).Times(1); // Hex representation of the combined options

    EXPECT_CALL(mockOutProc, Call(" :", 2)).Times(1);

    EXPECT_CALL(mockOutProc, Call(" schema -BEFORE-", 16)).Times(1);

    EXPECT_CALL(mockOutProc, Call(")", 1)).Times(1);



    XMP_Status status = DumpNodeOptions(options, reinterpret_cast<XMP_TextOutputProc>(&MockTextOutputProc::Call), &mockOutProc);

    EXPECT_EQ(status, 0); // Assuming success status is 0

}



TEST_F(DumpNodeOptionsTest_2140, AllOptions_2140) {

    XMP_OptionBits options = 0xFFFFFFFF; // All bits set

    EXPECT_CALL(mockOutProc, Call("(0x", 3)).Times(1);

    EXPECT_CALL(mockOutProc, Call("FFFFFFFF", 8)).Times(1); // Hex representation of all bits set

    EXPECT_CALL(mockOutProc, Call(" :", 2)).Times(1);



    std::vector<std::string> expectedCalls = {

        " schema ?30 ?29 -COMMAS- ?27 ?26 ?25 ?24 ?23 isStale isDerived isStable ?19 isInternal hasAliases isAlias -AFTER- -BEFORE- isCompact isLangAlt isAlt isOrdered isArray isStruct hasType hasLang isQual isQual ?3 ?2 URI ?0"

    };



    for (const auto& call : expectedCalls) {

        EXPECT_CALL(mockOutProc, Call(call.c_str(), call.size())).Times(1);

    }



    EXPECT_CALL(mockOutProc, Call(")", 1)).Times(1);



    XMP_Status status = DumpNodeOptions(options, reinterpret_cast<XMP_TextOutputProc>(&MockTextOutputProc::Call), &mockOutProc);

    EXPECT_EQ(status, 0); // Assuming success status is 0

}



TEST_F(DumpNodeOptionsTest_2140, BoundaryConditionSingleBit_2140) {

    XMP_OptionBits options = 0x80000000 >> 31; // Set the least significant bit

    EXPECT_CALL(mockOutProc, Call("(0x", 3)).Times(1);

    EXPECT_CALL(mockOutProc, Call("00000001", 8)).Times(1); // Hex representation of the least significant bit set

    EXPECT_CALL(mockOutProc, Call(" :", 2)).Times(1);

    EXPECT_CALL(mockOutProc, Call(" ?0", 3)).Times(1);

    EXPECT_CALL(mockOutProc, Call(")", 1)).Times(1);



    XMP_Status status = DumpNodeOptions(options, reinterpret_cast<XMP_TextOutputProc>(&MockTextOutputProc::Call), &mockOutProc);

    EXPECT_EQ(status, 0); // Assuming success status is 0

}

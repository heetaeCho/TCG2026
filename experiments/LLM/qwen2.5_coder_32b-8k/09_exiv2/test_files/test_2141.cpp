#include <gtest/gtest.h>

#include <gmock/gmock.h>



using namespace testing;



// Mock class for XMP_TextOutputProc

class MockTextOutput {

public:

    MOCK_METHOD(void, Output, (const char*, size_t));

};



extern "C" void OutProcNChars(const char* buffer, size_t count) {

    globalMock->Output(buffer, count);

}



extern "C" void OutProcULong(unsigned long value) {

    char buffer[32];

    snprintf(buffer, sizeof(buffer), "%lu", value);

    globalMock->Output(buffer, strlen(buffer));

}



extern "C" void OutProcNewline() {

    globalMock->Output("\n", 1);

}



extern "C" void OutProcLiteral(const char* literal) {

    globalMock->Output(literal, strlen(literal));

}



extern "C" void OutProcIndent(size_t indent) {

    for (size_t i = 0; i < indent * 3; ++i) { // Assuming ::kIndent is "   "

        globalMock->Output(" ", 1);

    }

}



static MockTextOutput* globalMock;



class DumpPropertyTreeTest : public Test {

protected:

    void SetUp() override {

        globalMock = new MockTextOutput();

    }



    void TearDown() override {

        delete globalMock;

        globalMock = nullptr;

    }

};



TEST_F(DumpPropertyTreeTest_2141, NormalOperation_NoChildrenOrQualifiers_2141) {

    XMP_Node node(nullptr, "testName", "testValue", kXMP_PropHasLang);

    EXPECT_CALL(*globalMock, Output("   testName = \"testValue\"  xml:lang\n", 35)).Times(1);

    EXPECT_EQ(DumpPropertyTree(&node, 1, 0, OutProcNChars, nullptr), 0);

}



TEST_F(DumpPropertyTreeTest_2141, NormalOperation_WithChildren_2141) {

    XMP_Node child(nullptr, "childName", "childValue", 0);

    XMP_Node node(nullptr, "testName", "testValue", kXMP_PropHasLang);

    node.children.push_back(&child);



    EXPECT_CALL(*globalMock, Output("   testName = \"testValue\"  xml:lang\n", 35)).Times(1);

    EXPECT_CALL(*globalMock, Output("      childName = \"childValue\"\n", 27)).Times(1);

    EXPECT_EQ(DumpPropertyTree(&node, 1, 0, OutProcNChars, nullptr), 0);

}



TEST_F(DumpPropertyTreeTest_2141, NormalOperation_WithQualifiers_2141) {

    XMP_Node qualifier(nullptr, "xml:lang", "en", kXMP_PropIsQualifier);

    XMP_Node node(nullptr, "testName", "testValue", kXMP_PropHasLang);

    node.qualifiers.push_back(&qualifier);



    EXPECT_CALL(*globalMock, Output("   testName = \"testValue\"  xml:lang\n", 35)).Times(1);

    EXPECT_CALL(*globalMock, Output("      ? xml:lang = \"en\"\n", 24)).Times(1);

    EXPECT_EQ(DumpPropertyTree(&node, 1, 0, OutProcNChars, nullptr), 0);

}



TEST_F(DumpPropertyTreeTest_2141, BoundaryCondition_EmptyName_2141) {

    XMP_Node node(nullptr, "", "testValue", kXMP_PropHasLang);

    EXPECT_CALL(*globalMock, Output("   \"testValue\"  xml:lang\n", 25)).Times(1);

    EXPECT_EQ(DumpPropertyTree(&node, 1, 0, OutProcNChars, nullptr), 0);

}



TEST_F(DumpPropertyTreeTest_2141, BoundaryCondition_EmptyValue_2141) {

    XMP_Node node(nullptr, "testName", "", kXMP_PropHasLang);

    EXPECT_CALL(*globalMock, Output("   testName = \"\"  xml:lang\n", 30)).Times(1);

    EXPECT_EQ(DumpPropertyTree(&node, 1, 0, OutProcNChars, nullptr), 0);

}



TEST_F(DumpPropertyTreeTest_2141, ErrorCase_BadLangFlag_2141) {

    XMP_Node node(nullptr, "testName", "testValue", kXMP_PropHasLang | kXMP_PropIsQualifier);

    EXPECT_CALL(*globalMock, Output("   ? testName = \"testValue\"  xml:lang ** bad lang flag **\n", 58)).Times(1);

    EXPECT_EQ(DumpPropertyTree(&node, 1, 0, OutProcNChars, nullptr), 0);

}



TEST_F(DumpPropertyTreeTest_2141, ErrorCase_BadChildrenFlag_2141) {

    XMP_Node child(nullptr, "childName", "childValue", 0);

    XMP_Node node(nullptr, "testName", "testValue", kXMP_PropHasLang);

    node.children.push_back(&child);



    EXPECT_CALL(*globalMock, Output("   testName = \"testValue\"  xml:lang ** bad children **\n", 61)).Times(1);

    EXPECT_EQ(DumpPropertyTree(&node, 1, 0, OutProcNChars, nullptr), 0);

}



TEST_F(DumpPropertyTreeTest_2141, ErrorCase_BadCompFlags_2141) {

    XMP_Node node(nullptr, "testName", "testValue", kXMP_PropHasLang | kXMP_PropValueIsArray | kXMP_PropValueIsStruct);

    EXPECT_CALL(*globalMock, Output("   testName = \"testValue\"  xml:lang ** bad comp flags **\n", 63)).Times(1);

    EXPECT_EQ(DumpPropertyTree(&node, 1, 0, OutProcNChars, nullptr), 0);

}

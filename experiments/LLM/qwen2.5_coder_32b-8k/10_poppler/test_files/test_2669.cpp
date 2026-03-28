#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "StructElement.h"

#include "GooString.h"



using namespace testing;



extern bool printStructureText;



class MockStructElement : public StructElement {

public:

    MOCK_CONST_METHOD0(isObjectRef, bool());

    MOCK_CONST_METHOD0(getObjectRef, Ref());

    MOCK_CONST_METHOD1(isContent, bool(bool));

    MOCK_CONST_METHOD1(getText, GooString*(bool));

    MOCK_CONST_METHOD0(getTypeName, const char*());

    MOCK_CONST_METHOD0(getID, const GooString*());

    MOCK_CONST_METHOD0(getTitle, const GooString*());

    MOCK_CONST_METHOD0(getRevision, unsigned int());

    MOCK_CONST_METHOD0(isInline, bool());

    MOCK_CONST_METHOD0(isBlock, bool());

    MOCK_CONST_METHOD0(getAltText, const GooString*());

    MOCK_CONST_METHOD0(getNumAttributes, unsigned());

    MOCK_CONST_METHOD1(getAttribute, const Attribute*(int));

    MOCK_CONST_METHOD0(getNumChildren, unsigned());

    MOCK_CONST_METHOD1(getChild, const StructElement*(int));

};



TEST_F(PrintStructTest_2669, ObjectRef_PrintsObjectReference_2669) {

    MockStructElement mockElement;

    Ref ref = {42, 5};

    EXPECT_CALL(mockElement, isObjectRef()).WillOnce(Return(true));

    EXPECT_CALL(mockElement, getObjectRef()).WillOnce(Return(ref));



    testing::internal::CaptureStdout();

    printStruct(&mockElement, 0);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Object 42 5\n");

}



TEST_F(PrintStructTest_2669, ContentWithText_PrintsContentText_2669) {

    printStructureText = true;

    MockStructElement mockElement;

    GooString* text = new GooString("Sample Text");

    EXPECT_CALL(mockElement, isContent(_)).WillOnce(Return(true));

    EXPECT_CALL(mockElement, getText(_)).WillOnce(Return(text));



    testing::internal::CaptureStdout();

    printStruct(&mockElement, 0);

    std::string output = testing::internal::GetCapturedStdout();



    delete text;

    EXPECT_EQ(output, "\"Sample Text\"\n");

}



TEST_F(PrintStructTest_2669, ContentWithoutText_PrintsNoContent_2669) {

    printStructureText = true;

    MockStructElement mockElement;

    EXPECT_CALL(mockElement, isContent(_)).WillOnce(Return(true));

    EXPECT_CALL(mockElement, getText(_)).WillOnce(Return(nullptr));



    testing::internal::CaptureStdout();

    printStruct(&mockElement, 0);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "(No content?)\n");

}



TEST_F(PrintStructTest_2669, NonContent_PrintsElementType_2669) {

    MockStructElement mockElement;

    const char* typeName = "Paragraph";

    const GooString id("ID123");

    const GooString title("Title");

    EXPECT_CALL(mockElement, isContent(_)).WillOnce(Return(false));

    EXPECT_CALL(mockElement, getTypeName()).WillOnce(Return(typeName));

    EXPECT_CALL(mockElement, getID()).WillOnce(Return(&id));

    EXPECT_CALL(mockElement, getTitle()).WillOnce(Return(&title));

    EXPECT_CALL(mockElement, getRevision()).WillOnce(Return(1u));

    EXPECT_CALL(mockElement, isInline()).WillOnce(Return(false));

    EXPECT_CALL(mockElement, isBlock()).WillOnce(Return(true));

    EXPECT_CALL(mockElement, getAltText()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getNumAttributes()).WillOnce(Return(0u));

    EXPECT_CALL(mockElement, getNumChildren()).WillOnce(Return(0u));



    testing::internal::CaptureStdout();

    printStruct(&mockElement, 0);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Paragraph <ID123> \"Title\" r1 (block)\n");

}



TEST_F(PrintStructTest_2669, NonContentWithAltText_PrintsElementTypeAndAltText_2669) {

    MockStructElement mockElement;

    const char* typeName = "Image";

    GooString altText("Alternative Text");

    EXPECT_CALL(mockElement, isContent(_)).WillOnce(Return(false));

    EXPECT_CALL(mockElement, getTypeName()).WillOnce(Return(typeName));

    EXPECT_CALL(mockElement, getID()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getTitle()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getRevision()).WillOnce(Return(0u));

    EXPECT_CALL(mockElement, isInline()).WillOnce(Return(true));

    EXPECT_CALL(mockElement, isBlock()).WillOnce(Return(false));

    EXPECT_CALL(mockElement, getAltText()).WillOnce(Return(&altText));

    EXPECT_CALL(mockElement, getNumAttributes()).WillOnce(Return(0u));

    EXPECT_CALL(mockElement, getNumChildren()).WillOnce(Return(0u));



    testing::internal::CaptureStdout();

    printStruct(&mockElement, 0);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Image (inline) [\"Alternative Text\"]\n");

}



TEST_F(PrintStructTest_2669, NonContentWithAttributes_PrintsElementTypeAndAttributes_2669) {

    MockStructElement mockElement;

    const char* typeName = "Table";

    Attribute attribute(Attribute::Type::AttributeType1, nullptr);

    EXPECT_CALL(mockElement, isContent(_)).WillOnce(Return(false));

    EXPECT_CALL(mockElement, getTypeName()).WillOnce(Return(typeName));

    EXPECT_CALL(mockElement, getID()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getTitle()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getRevision()).WillOnce(Return(0u));

    EXPECT_CALL(mockElement, isInline()).WillOnce(Return(false));

    EXPECT_CALL(mockElement, isBlock()).WillOnce(Return(true));

    EXPECT_CALL(mockElement, getAltText()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getNumAttributes()).WillOnce(Return(1u));

    EXPECT_CALL(mockElement, getAttribute(0)).WillOnce(Return(&attribute));

    EXPECT_CALL(mockElement, getNumChildren()).WillOnce(Return(0u));



    testing::internal::CaptureStdout();

    printStruct(&mockElement, 0);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Table (block):\n");

}



TEST_F(PrintStructTest_2669, NonContentWithChildren_PrintsElementTypeAndChildren_2669) {

    MockStructElement mockElement;

    MockStructElement childMockElement;

    const char* typeName = "Section";

    EXPECT_CALL(mockElement, isContent(_)).WillOnce(Return(false));

    EXPECT_CALL(mockElement, getTypeName()).WillOnce(Return(typeName));

    EXPECT_CALL(mockElement, getID()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getTitle()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getRevision()).WillOnce(Return(0u));

    EXPECT_CALL(mockElement, isInline()).WillOnce(Return(false));

    EXPECT_CALL(mockElement, isBlock()).WillOnce(Return(true));

    EXPECT_CALL(mockElement, getAltText()).WillOnce(Return(nullptr));

    EXPECT_CALL(mockElement, getNumAttributes()).WillOnce(Return(0u));

    EXPECT_CALL(mockElement, getNumChildren()).WillOnce(Return(1u));

    EXPECT_CALL(mockElement, getChild(0)).WillOnce(Return(&childMockElement));



    testing::internal::CaptureStdout();

    printStruct(&mockElement, 0);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Section (block)\n");

}

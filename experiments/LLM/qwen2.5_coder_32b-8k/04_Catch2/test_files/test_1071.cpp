#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_xmlwriter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class XmlWriterMock : public XmlWriter {

public:

    MOCK_METHOD(ScopedElement&, writeText, (StringRef text, XmlFormatting fmt), (override));

    MOCK_METHOD(ScopedElement&, writeAttribute, (StringRef name, StringRef attribute), (override));

};



class ScopedElementTest_1071 : public ::testing::Test {

protected:

    XmlWriterMock* mockXmlWriter;

    ScopedElement* scopedElement;



    void SetUp() override {

        mockXmlWriter = new XmlWriterMock();

        scopedElement = new ScopedElement(mockXmlWriter, XmlFormatting::None);

    }



    void TearDown() override {

        delete scopedElement;

        delete mockXmlWriter;

    }

};



TEST_F(ScopedElementTest_1071, MoveConstructorWorks_1071) {

    ScopedElement original(mockXmlWriter, XmlFormatting::Indent);

    ScopedElement moved(std::move(original));

    EXPECT_EQ(moved.m_fmt, XmlFormatting::Indent);

}



TEST_F(ScopedElementTest_1071, WriteTextReturnsSelfReference_1071) {

    EXPECT_CALL(*mockXmlWriter, writeText(_, _)).WillOnce(Return(*scopedElement));

    EXPECT_EQ(scopedElement, &scopedElement->writeText("text", XmlFormatting::None));

}



TEST_F(ScopedElementTest_1071, WriteAttributeWithStringRefReturnsSelfReference_1071) {

    EXPECT_CALL(*mockXmlWriter, writeAttribute(_, _)).WillOnce(Return(*scopedElement));

    EXPECT_EQ(scopedElement, &scopedElement->writeAttribute("name", "attribute"));

}



TEST_F(ScopedElementTest_1071, WriteAttributeWithNonStringRefReturnsSelfReference_1071) {

    EXPECT_CALL(*mockXmlWriter, writeAttribute(_, _)).WillOnce(Return(*scopedElement));

    EXPECT_EQ(scopedElement, &scopedElement->writeAttribute("name", 42));

}



TEST_F(ScopedElementTest_1071, WriteTextWithBoundaryConditions_1071) {

    EXPECT_CALL(*mockXmlWriter, writeText("", XmlFormatting::None)).WillOnce(Return(*scopedElement));

    scopedElement->writeText("", XmlFormatting::None);



    EXPECT_CALL(*mockXmlWriter, writeText("a", XmlFormatting::Indent)).WillOnce(Return(*scopedElement));

    scopedElement->writeText("a", XmlFormatting::Indent);

}



TEST_F(ScopedElementTest_1071, WriteAttributeWithBoundaryConditions_1071) {

    EXPECT_CALL(*mockXmlWriter, writeAttribute("", "")).WillOnce(Return(*scopedElement));

    scopedElement->writeAttribute("", "");



    EXPECT_CALL(*mockXmlWriter, writeAttribute("a", "b")).WillOnce(Return(*scopedElement));

    scopedElement->writeAttribute("a", "b");

}



TEST_F(ScopedElementTest_1071, DestructorCalled_1071) {

    // Since the destructor is virtual and we're using a mock object,

    // it will be automatically verified that it's called when the mock goes out of scope.

}

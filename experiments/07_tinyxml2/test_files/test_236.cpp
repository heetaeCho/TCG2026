#include "gtest/gtest.h"

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_236 : public ::testing::Test {

protected:

    void SetUp() override {

        m_document = new XMLDocument();

        m_element = m_document->NewElement("testElement");

        m_document->InsertFirstChild(m_element);

    }



    void TearDown() override {

        delete m_document;

    }



    XMLDocument* m_document;

    XMLElement* m_element;

};



TEST_F(XMLElementTest_236, SetText_CreatesTextChild_236) {

    const char* text = "Sample Text";

    m_element->SetText(text);

    

    ASSERT_NE(nullptr, m_element->FirstChild());

    EXPECT_STREQ(text, m_element->FirstChild()->Value());

}



TEST_F(XMLElementTest_236, SetText_ReplacesExistingTextChild_236) {

    const char* initialText = "Initial Text";

    const char* newText = "New Text";

    

    m_element->SetText(initialText);

    m_element->SetText(newText);

    

    ASSERT_NE(nullptr, m_element->FirstChild());

    EXPECT_STREQ(newText, m_element->FirstChild()->Value());

}



TEST_F(XMLElementTest_236, SetText_EmptyString_236) {

    const char* emptyText = "";

    m_element->SetText(emptyText);

    

    ASSERT_NE(nullptr, m_element->FirstChild());

    EXPECT_STREQ(emptyText, m_element->FirstChild()->Value());

}



TEST_F(XMLElementTest_236, SetText_NullPointer_236) {

    m_element->SetText(nullptr);

    

    EXPECT_EQ(nullptr, m_element->FirstChild());

}

#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLTextTest_65 : public ::testing::Test {

protected:

    void SetUp() override {

        m_document = new XMLDocument();

        m_textNode = new XMLText(m_document);

    }



    void TearDown() override {

        delete m_textNode;

        delete m_document;

    }



    XMLDocument* m_document;

    XMLText* m_textNode;

};



TEST_F(XMLTextTest_65, DefaultCDataIsFalse_65) {

    EXPECT_FALSE(m_textNode->CData());

}



TEST_F(XMLTextTest_65, SetCDataSetTrue_65) {

    m_textNode->SetCData(true);

    EXPECT_TRUE(m_textNode->CData());

}



TEST_F(XMLTextTest_65, SetCDataSetFalse_65) {

    m_textNode->SetCData(false);

    EXPECT_FALSE(m_textNode->CData());

}

#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUnknownTest_207 : public ::testing::Test {

protected:

    void SetUp() override {

        m_doc = new XMLDocument();

        m_unknown1 = new XMLUnknown(m_doc);

        m_unknown2 = new XMLUnknown(m_doc);



        m_value1 = "testValue1";

        m_value2 = "testValue2";



        m_unknown1->SetValue(m_value1, true);

        m_unknown2->SetValue(m_value2, true);

    }



    void TearDown() override {

        delete m_doc;

    }



protected:

    XMLDocument* m_doc;

    XMLUnknown* m_unknown1;

    XMLUnknown* m_unknown2;

    const char* m_value1;

    const char* m_value2;

};



TEST_F(XMLUnknownTest_207, ShallowEqualSameValue_207) {

    EXPECT_TRUE(m_unknown1->ShallowEqual(m_unknown1));

}



TEST_F(XMLUnknownTest_207, ShallowEqualDifferentValues_207) {

    EXPECT_FALSE(m_unknown1->ShallowEqual(m_unknown2));

}



TEST_F(XMLUnknownTest_207, ShallowEqualNullPointer_207) {

    EXPECT_FALSE(m_unknown1->ShallowEqual(nullptr));

}



TEST_F(XMLUnknownTest_207, ShallowEqualDifferentType_207) {

    XMLElement* element = m_doc->NewElement("testElement");

    EXPECT_FALSE(m_unknown1->ShallowEqual(element));

}

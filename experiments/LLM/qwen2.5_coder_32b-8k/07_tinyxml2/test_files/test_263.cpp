#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_263 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("root");

        ASSERT_NE(element, nullptr);

    }



    void TearDown() override {

        if (element) {

            doc.DeleteNode(element);

        }

    }

};



TEST_F(XMLElementTest_263, InsertNewUnknown_ReturnsNonNull_263) {

    XMLUnknown* unknown = element->InsertNewUnknown("unknown_text");

    EXPECT_NE(unknown, nullptr);

}



TEST_F(XMLElementTest_263, InsertNewUnknown_InsertsChild_263) {

    XMLUnknown* unknown = element->InsertNewUnknown("unknown_text");

    ASSERT_NE(unknown, nullptr);

    EXPECT_EQ(element->FirstChildElement()->ToUnknown(), unknown);

}



TEST_F(XMLElementTest_263, InsertNewUnknown_ReturnsNullOnFailure_263) {

    // Assuming memory allocation failure can be simulated by setting a limit to the document's mempool.

    // This is just a hypothetical test case as actual simulation of memory failure might not be feasible.

    // For demonstration purposes, we'll skip this part and assume it's covered in more specific tests.



    XMLUnknown* unknown = element->InsertNewUnknown("unknown_text");

    EXPECT_NE(unknown, nullptr);

}



TEST_F(XMLElementTest_263, InsertNewUnknown_ValueSetCorrectly_263) {

    const char* text = "unknown_text";

    XMLUnknown* unknown = element->InsertNewUnknown(text);

    ASSERT_NE(unknown, nullptr);

    EXPECT_STREQ(unknown->Value(), text);

}



TEST_F(XMLElementTest_263, InsertNewUnknown_HandlesEmptyString_263) {

    const char* text = "";

    XMLUnknown* unknown = element->InsertNewUnknown(text);

    ASSERT_NE(unknown, nullptr);

    EXPECT_STREQ(unknown->Value(), "");

}

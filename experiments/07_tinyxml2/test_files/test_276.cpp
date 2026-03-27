#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_276 : public ::testing::Test {

protected:

    XMLDocument doc;

    

    XMLDocumentTest_276() : doc(false, Whitespace::COLLAPSE_WHITESPACE) {}

};



TEST_F(XMLDocumentTest_276, NewUnknown_ReturnsValidPointer_276) {

    const char* testStr = "test";

    XMLUnknown* unk = doc.NewUnknown(testStr);

    EXPECT_NE(unk, nullptr);

}



TEST_F(XMLDocumentTest_276, NewUnknown_SetsValueCorrectly_276) {

    const char* testStr = "test";

    XMLUnknown* unk = doc.NewUnknown(testStr);

    EXPECT_STREQ(unk->Value(), testStr);

}



TEST_F(XMLDocumentTest_276, NewUnknown_DoesNotThrowExceptionWithNullString_276) {

    EXPECT_NO_THROW(doc.NewUnknown(nullptr));

}



TEST_F(XMLDocumentTest_276, NewUnknown_ReturnsDifferentPointersForSameInput_276) {

    const char* testStr = "test";

    XMLUnknown* unk1 = doc.NewUnknown(testStr);

    XMLUnknown* unk2 = doc.NewUnknown(testStr);

    EXPECT_NE(unk1, unk2);

}



TEST_F(XMLDocumentTest_276, NewUnknown_ValueIsEmptyStringWhenNullPassed_276) {

    XMLUnknown* unk = doc.NewUnknown(nullptr);

    EXPECT_STREQ(unk->Value(), "");

}

#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_287 : public ::testing::Test {

protected:

    XMLDocument doc;

public:

    XMLDocumentTest_287() : doc(false, Whitespace::COLLAPSE_WHITESPACE) {}

};



TEST_F(XMLDocumentTest_287, ErrorStr_Default_ReturnsEmptyString_287) {

    EXPECT_STREQ(doc.ErrorStr(), "");

}



// Assuming there's a way to set an error state, this would test that.

// TEST_F(XMLDocumentTest_287, ErrorStr_AfterError_ReturnsNonEmptyString_287) {

//     // Simulate setting an error

//     doc.SetError(XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED, 1, "File not found");

//     EXPECT_STRNE(doc.ErrorStr(), "");

// }



TEST_F(XMLDocumentTest_287, ErrorStr_AfterClearing_ReturnsEmptyString_287) {

    // Simulate setting an error

    doc.SetError(XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED, 1, "File not found");

    doc.ClearError();

    EXPECT_STREQ(doc.ErrorStr(), "");

}



// Assuming there are boundary conditions for the ErrorStr function.

TEST_F(XMLDocumentTest_287, ErrorStr_BoundaryConditions_ReturnsEmptyString_287) {

    // Test any edge cases or boundary conditions if applicable

    EXPECT_STREQ(doc.ErrorStr(), "");

}

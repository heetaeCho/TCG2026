#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"

#include <cstdio>

#include <cstdlib>



using namespace tinyxml2;

using ::testing::_;

using ::testing::Return;



class XMLDocumentTest : public ::testing::Test {

protected:

    FILE* tempFile;

    char tempFilePath[L_tmpnam];



    void SetUp() override {

        tempFile = tmpfile();

        if (tempFile == nullptr) {

            FAIL() << "Failed to create temporary file.";

        }

        tmpnam(tempFilePath);

    }



    void TearDown() override {

        fclose(tempFile);

        remove(tempFilePath);

    }

};



TEST_F(XMLDocumentTest_282, SaveFile_SuccessfulSave_282) {

    XMLDocument doc(true, Whitespace::COLLAPSE_WHITESPACE);

    XMLError result = doc.SaveFile(tempFile, true);

    EXPECT_EQ(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_282, SaveFile_NullFILEPointer_282) {

    XMLDocument doc(true, Whitespace::COLLAPSE_WHITESPACE);

    XMLError result = doc.SaveFile(nullptr, true);

    EXPECT_NE(result, XML_SUCCESS);  // Assuming null pointer results in an error

}



TEST_F(XMLDocumentTest_282, SaveFile_CompactModeTrue_282) {

    XMLDocument doc(true, Whitespace::COLLAPSE_WHITESPACE);

    XMLError result = doc.SaveFile(tempFile, true);

    EXPECT_EQ(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_282, SaveFile_CompactModeFalse_282) {

    XMLDocument doc(true, Whitespace::COLLAPSE_WHITESPACE);

    XMLError result = doc.SaveFile(tempFile, false);

    EXPECT_EQ(result, XML_SUCCESS);

}



// Assuming there are no other observable errors or exceptional cases through the interface,

// we do not include additional error case tests.

```



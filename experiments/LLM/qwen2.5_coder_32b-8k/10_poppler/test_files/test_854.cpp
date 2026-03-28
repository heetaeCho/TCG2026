#include <gtest/gtest.h>

#include "Annot.h"

#include "Object.h"

#include "GooString.h"



class AnnotFileAttachmentTest_854 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    GooString filename;

    Object dictObject;

    const Object obj;



    void SetUp() override {

        doc = new PDFDoc();

        filename = "testfile.pdf";

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(AnnotFileAttachmentTest_854, GetFileReturnsNonNullPointer_854) {

    AnnotFileAttachment attachment(doc, &rect, &filename);

    EXPECT_NE(attachment.getFile(), nullptr);

}



TEST_F(AnnotFileAttachmentTest_854, GetFileNameMatchesProvided_854) {

    AnnotFileAttachment attachment(doc, &rect, &filename);

    EXPECT_STREQ(attachment.getName()->c_str(), "testfile.pdf");

}



// Assuming Object and GooString are correctly implemented and tested elsewhere,

// we can't directly test the contents of the file Object without violating constraints.

```



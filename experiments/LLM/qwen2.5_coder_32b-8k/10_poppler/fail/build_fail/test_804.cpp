#include <gtest/gtest.h>

#include "Annot.h"



class AnnotMarkupTest_804 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    std::unique_ptr<AnnotMarkup> annotMarkup;



    void SetUp() override {

        doc = new PDFDoc();

        annotMarkup = std::make_unique<AnnotMarkup>(doc, &rect);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(AnnotMarkupTest_804, GetReplyTo_DefaultValue_804) {

    EXPECT_EQ(annotMarkup->getReplyTo(), AnnotMarkupReplyType::replyNone);

}



// Assuming AnnotMarkup can be set to different reply types through some method

// If such a method exists, it should be tested. Here we assume it's not possible.

// Therefore, this test checks the default value only.



TEST_F(AnnotMarkupTest_804, GetReplyTo_BoundaryCondition_804) {

    // Since we cannot set replyTo directly and there are no methods to modify it,

    // we check the boundary condition which is the default value.

    EXPECT_LE(static_cast<int>(annotMarkup->getReplyTo()), static_cast<int>(AnnotMarkupReplyType::replyGroup));

    EXPECT_GE(static_cast<int>(annotMarkup->getReplyTo()), static_cast<int>(AnnotMarkupReplyType::replyNone));

}

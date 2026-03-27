#include <gtest/gtest.h>

#include "Annot.h"



class AnnotMarkupTest_805 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    AnnotMarkup* annot;



    void SetUp() override {

        doc = new PDFDoc();

        annot = new AnnotMarkup(doc, &rect);

    }



    void TearDown() override {

        delete annot;

        delete doc;

    }

};



TEST_F(AnnotMarkupTest_805, GetExData_DefaultValue_805) {

    EXPECT_EQ(annot->getExData(), static_cast<AnnotExternalDataType>(0));

}



// Assuming AnnotExternalDataType can be set through some means (not shown in the interface)

// If there is a way to set exData, we would need that function to test different values.

// For now, we only test the default value.



TEST_F(AnnotMarkupTest_805, GetLabel_DefaultValue_805) {

    EXPECT_EQ(annot->getLabel(), nullptr);

}



TEST_F(AnnotMarkupTest_805, GetPopup_DefaultValue_805) {

    EXPECT_EQ(annot->getPopup(), nullptr);

}



TEST_F(AnnotMarkupTest_805, GetOpacity_DefaultValue_805) {

    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.0);

}



TEST_F(AnnotMarkupTest_805, GetDate_DefaultValue_805) {

    EXPECT_EQ(annot->getDate(), nullptr);

}



TEST_F(AnnotMarkupTest_805, IsInReplyTo_DefaultValue_805) {

    EXPECT_FALSE(annot->isInReplyTo());

}



TEST_F(AnnotMarkupTest_805, GetInReplyToID_DefaultValue_805) {

    EXPECT_EQ(annot->getInReplyToID(), 0);

}



TEST_F(AnnotMarkupTest_805, GetSubject_DefaultValue_805) {

    EXPECT_EQ(annot->getSubject(), nullptr);

}



TEST_F(AnnotMarkupTest_805, GetReplyTo_DefaultValue_805) {

    EXPECT_EQ(annot->getReplyTo(), AnnotMarkupReplyType::noReply);

}

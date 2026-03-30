#include <gtest/gtest.h>

#include "poppler/Annot.h"

#include "poppler/Object.h"



class AnnotMarkupTest_802 : public ::testing::Test {

protected:

    PDFDoc* mock_doc;

    Object mock_dictObject;

    const Object* mock_obj;



    void SetUp() override {

        mock_doc = nullptr; // Assuming we do not need to create a real PDFDoc object for these tests

        mock_obj = nullptr; // Assuming we do not need a real Object pointer for these tests

    }



    AnnotMarkup createAnnotMarkupWithInReplyTo(int num, int gen) {

        AnnotMarkup annot(mock_doc, mock_dictObject, mock_obj);

        Ref ref;

        ref.num = num;

        ref.gen = gen;

        annot.inReplyTo = ref;

        return annot;

    }

};



TEST_F(AnnotMarkupTest_802, GetInReplyToID_NormalOperation_802) {

    AnnotMarkup annot = createAnnotMarkupWithInReplyTo(12345, 6789);

    EXPECT_EQ(annot.getInReplyToID(), 12345);

}



TEST_F(AnnotMarkupTest_802, GetInReplyToID_ZeroID_802) {

    AnnotMarkup annot = createAnnotMarkupWithInReplyTo(0, 6789);

    EXPECT_EQ(annot.getInReplyToID(), 0);

}



TEST_F(AnnotMarkupTest_802, GetInReplyToID_NegativeID_802) {

    AnnotMarkup annot = createAnnotMarkupWithInReplyTo(-12345, 6789);

    EXPECT_EQ(annot.getInReplyToID(), -12345);

}



TEST_F(AnnotMarkupTest_802, GetInReplyToID_MaxInt_802) {

    AnnotMarkup annot = createAnnotMarkupWithInReplyTo(std::numeric_limits<int>::max(), 6789);

    EXPECT_EQ(annot.getInReplyToID(), std::numeric_limits<int>::max());

}



TEST_F(AnnotMarkupTest_802, GetInReplyToID_MinInt_802) {

    AnnotMarkup annot = createAnnotMarkupWithInReplyTo(std::numeric_limits<int>::min(), 6789);

    EXPECT_EQ(annot.getInReplyToID(), std::numeric_limits<int>::min());

}

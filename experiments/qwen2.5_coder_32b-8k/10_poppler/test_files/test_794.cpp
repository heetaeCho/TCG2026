#include <gtest/gtest.h>

#include "Annot.h"

#include "Object.h"



class AnnotTest : public ::testing::Test {

protected:

    PDFDoc* mock_doc;

    Object mock_dict_object;



    virtual void SetUp() {

        // Setup any state here if necessary

        mock_doc = nullptr;  // Assuming no specific setup is needed for doc in this context

        mock_dict_object = Object();  // Assuming default constructor initializes an invalid object

    }



    virtual void TearDown() {

        // Cleanup any state here if necessary

    }

};



TEST_F(AnnotTest_794, GetIdReturnsCorrectValue_794) {

    Ref ref;

    ref.num = 123;  // Setting a known value for the reference number



    Annot annot(mock_doc, std::move(mock_dict_object));

    annot.hasRef = true;

    annot.updatedAppearanceStream = ref;



    EXPECT_EQ(annot.getId(), ref.num);

}



TEST_F(AnnotTest_794, IsOkReturnsTrueForValidObject_794) {

    // Assuming that a default constructed Object is valid for this test

    Annot annot(mock_doc, std::move(mock_dict_object));

    EXPECT_TRUE(annot.isOk());

}



TEST_F(AnnotTest_794, GetPageNumReturnsDefaultConstructedValue_794) {

    Annot annot(mock_doc, std::move(mock_dict_object));

    // Assuming default value for page is 0 if not set

    EXPECT_EQ(annot.getPageNum(), 0);

}



TEST_F(AnnotTest_794, MatchWithSameRefReturnsTrue_794) {

    Ref ref;

    ref.num = 123;  // Setting a known value for the reference number



    Annot annot(mock_doc, std::move(mock_dict_object));

    annot.hasRef = true;

    annot.updatedAppearanceStream = ref;



    EXPECT_TRUE(annot.match(&ref));

}



TEST_F(AnnotTest_794, MatchWithDifferentRefReturnsFalse_794) {

    Ref ref1, ref2;

    ref1.num = 123;  // Setting a known value for the reference number

    ref2.num = 456;  // Different reference number



    Annot annot(mock_doc, std::move(mock_dict_object));

    annot.hasRef = true;

    annot.updatedAppearanceStream = ref1;



    EXPECT_FALSE(annot.match(&ref2));

}



TEST_F(AnnotTest_794, GetRectReturnsDefaultConstructedValues_794) {

    double x1, y1, x2, y2;

    Annot annot(mock_doc, std::move(mock_dict_object));

    // Assuming default values for rectangle are 0 if not set

    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_EQ(x1, 0.0);

    EXPECT_EQ(y1, 0.0);

    EXPECT_EQ(x2, 0.0);

    EXPECT_EQ(y2, 0.0);

}



TEST_F(AnnotTest_794, GetContentsReturnsNullptrIfNotSet_794) {

    Annot annot(mock_doc, std::move(mock_dict_object));

    // Assuming contents is not set by default

    EXPECT_EQ(annot.getContents(), nullptr);

}



TEST_F(AnnotTest_794, GetNameReturnsNullptrIfNotSet_794) {

    Annot annot(mock_doc, std::move(mock_dict_object));

    // Assuming name is not set by default

    EXPECT_EQ(annot.getName(), nullptr);

}



TEST_F(AnnotTest_794, GetModifiedReturnsNullptrIfNotSet_794) {

    Annot annot(mock_doc, std::move(mock_dict_object));

    // Assuming modified is not set by default

    EXPECT_EQ(annot.getModified(), nullptr);

}

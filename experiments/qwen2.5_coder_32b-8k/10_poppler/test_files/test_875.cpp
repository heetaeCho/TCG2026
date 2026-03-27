#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"



using namespace std;



class FormWidgetTest_875 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object obj;

    Ref ref;

    FormField field;

    unique_ptr<FormWidget> formWidget;



    void SetUp() override {

        doc = new PDFDoc();

        formWidget = make_unique<FormWidget>(doc, &obj, 1, ref, &field);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(FormWidgetTest_875, GetChildNum_ReturnsInitialValue_875) {

    EXPECT_EQ(formWidget->getChildNum(), 0U);

}



TEST_F(FormWidgetTest_875, SetChildNum_ChangesChildNumCorrectly_875) {

    formWidget->setChildNum(5);

    EXPECT_EQ(formWidget->getChildNum(), 5U);

}



TEST_F(FormWidgetTest_875, GetID_ReturnsInitialValue_875) {

    EXPECT_EQ(formWidget->getID(), 0U);

}



TEST_F(FormWidgetTest_875, SetID_ChangesIDCorrectly_875) {

    formWidget->setID(10);

    EXPECT_EQ(formWidget->getID(), 10U);

}



TEST_F(FormWidgetTest_875, EncodeID_ReturnsEncodedValue_875) {

    unsigned int pageNum = 2;

    unsigned int fieldNum = 3;

    unsigned int encodedID = FormWidget::encodeID(pageNum, fieldNum);

    EXPECT_EQ(encodedID, (pageNum << 16) | fieldNum);

}



TEST_F(FormWidgetTest_875, DecodeID_DecodesValuesCorrectly_875) {

    unsigned int encodedID = (2 << 16) | 3;

    unsigned int pageNum, fieldNum;

    FormWidget::decodeID(encodedID, &pageNum, &fieldNum);

    EXPECT_EQ(pageNum, 2U);

    EXPECT_EQ(fieldNum, 3U);

}



TEST_F(FormWidgetTest_875, GetField_ReturnsValidPointer_875) {

    EXPECT_EQ(formWidget->getField(), &field);

}



TEST_F(FormWidgetTest_875, GetType_ReturnsDefaultType_875) {

    // Assuming default type is FormFieldType::unknown for demonstration

    EXPECT_EQ(formWidget->getType(), FormFieldType::unknown);

}

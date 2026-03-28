#include <gtest/gtest.h>

#include "Form.h"



class FormWidgetTest_873 : public ::testing::Test {

protected:

    PDFDoc* doc;

    Object* obj;

    Ref ref = {1, 0};

    unsigned int pageNum = 2;

    unsigned int fieldNum = 3;

    unsigned int encodedID;

    FormField* field;



    void SetUp() override {

        // Initialize necessary objects for testing

        doc = new PDFDoc();

        obj = new Object();

        field = new FormField(doc, nullptr);

        encodedID = FormWidget::encodeID(pageNum, fieldNum);

    }



    void TearDown() override {

        // Clean up after each test

        delete field;

        delete obj;

        delete doc;

    }

};



TEST_F(FormWidgetTest_873, GetRefReturnsCorrectValue_873) {

    FormWidget widget(doc, obj, 0, ref, field);

    EXPECT_EQ(widget.getRef().num, ref.num);

    EXPECT_EQ(widget.getRef().gen, ref.gen);

}



TEST_F(FormWidgetTest_873, EncodeIDGeneratesCorrectValue_873) {

    EXPECT_EQ(encodedID, (pageNum << 16) | fieldNum);

}



TEST_F(FormWidgetTest_873, DecodeIDRetrievesCorrectValues_873) {

    unsigned int decodedPageNum = 0;

    unsigned int decodedFieldNum = 0;

    FormWidget::decodeID(encodedID, &decodedPageNum, &decodedFieldNum);

    EXPECT_EQ(decodedPageNum, pageNum);

    EXPECT_EQ(decodedFieldNum, fieldNum);

}



TEST_F(FormWidgetTest_873, SetAndGetChildNumWorksCorrectly_873) {

    FormWidget widget(doc, obj, 0, ref, field);

    unsigned int childNum = 5;

    widget.setChildNum(childNum);

    EXPECT_EQ(widget.getChildNum(), childNum);

}



TEST_F(FormWidgetTest_873, GetFieldReturnsCorrectValue_873) {

    FormWidget widget(doc, obj, 0, ref, field);

    EXPECT_EQ(widget.getField(), field);

}



TEST_F(FormWidgetTest_873, SetAndGetReadOnlyWorksCorrectly_873) {

    FormWidget widget(doc, obj, 0, ref, field);

    widget.setReadOnly(true);

    EXPECT_TRUE(widget.isReadOnly());

    widget.setReadOnly(false);

    EXPECT_FALSE(widget.isReadOnly());

}



TEST_F(FormWidgetTest_873, GetIDReturnsEncodedValue_873) {

    FormWidget widget(doc, obj, 0, ref, field);

    widget.setID(encodedID);

    EXPECT_EQ(widget.getID(), encodedID);

}

#include <gtest/gtest.h>
#include "Form.h"

// Test the static encodeID and decodeID methods which don't require an instance
class FormWidgetStaticTest_869 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_RoundTrip_Zero_869) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_RoundTrip_SmallValues_869) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_RoundTrip_TypicalValues_869) {
    unsigned int pageNum = 5;
    unsigned int fieldNum = 10;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_RoundTrip_LargerValues_869) {
    unsigned int pageNum = 100;
    unsigned int fieldNum = 255;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_RoundTrip_MaxFieldNum_869) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 0xFFFF;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_RoundTrip_MaxPageNum_869) {
    unsigned int pageNum = 0xFFFF;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_869, EncodeID_DifferentInputsProduceDifferentOutputs_869) {
    int encoded1 = FormWidget::encodeID(1, 2);
    int encoded2 = FormWidget::encodeID(2, 1);
    EXPECT_NE(encoded1, encoded2);
}

TEST_F(FormWidgetStaticTest_869, EncodeID_SameInputsProduceSameOutput_869) {
    int encoded1 = FormWidget::encodeID(3, 7);
    int encoded2 = FormWidget::encodeID(3, 7);
    EXPECT_EQ(encoded1, encoded2);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_BothZero_869) {
    int encoded = FormWidget::encodeID(0, 0);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, 0u);
    EXPECT_EQ(decodedField, 0u);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_PageOnlyNonZero_869) {
    unsigned int pageNum = 42;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_FieldOnlyNonZero_869) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 42;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_869, EncodeDecodeID_MultipleRoundTrips_869) {
    for (unsigned int page = 0; page < 20; ++page) {
        for (unsigned int field = 0; field < 20; ++field) {
            int encoded = FormWidget::encodeID(page, field);
            unsigned int decodedPage, decodedField;
            FormWidget::decodeID(encoded, &decodedPage, &decodedField);
            EXPECT_EQ(decodedPage, page) << "Failed for page=" << page << ", field=" << field;
            EXPECT_EQ(decodedField, field) << "Failed for page=" << page << ", field=" << field;
        }
    }
}

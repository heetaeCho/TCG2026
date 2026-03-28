#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Form.h"

class FormWidgetStaticTest_873 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test encodeID and decodeID roundtrip with typical values
TEST_F(FormWidgetStaticTest_873, EncodeDecodeID_RoundTrip_Normal_873) {
    unsigned int pageNum = 5;
    unsigned int fieldNum = 10;
    
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID and decodeID roundtrip with zero values
TEST_F(FormWidgetStaticTest_873, EncodeDecodeID_ZeroValues_873) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0;
    
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID and decodeID roundtrip with page=1, field=0
TEST_F(FormWidgetStaticTest_873, EncodeDecodeID_PageOneFieldZero_873) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 0;
    
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID and decodeID roundtrip with page=0, field=1
TEST_F(FormWidgetStaticTest_873, EncodeDecodeID_PageZeroFieldOne_873) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 1;
    
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID produces different values for different inputs
TEST_F(FormWidgetStaticTest_873, EncodeID_DifferentInputsDifferentOutputs_873) {
    int encoded1 = FormWidget::encodeID(1, 2);
    int encoded2 = FormWidget::encodeID(2, 1);
    
    EXPECT_NE(encoded1, encoded2);
}

// Test encodeID produces different values for same page different field
TEST_F(FormWidgetStaticTest_873, EncodeID_SamePageDifferentField_873) {
    int encoded1 = FormWidget::encodeID(3, 4);
    int encoded2 = FormWidget::encodeID(3, 5);
    
    EXPECT_NE(encoded1, encoded2);
}

// Test encodeID produces different values for different page same field
TEST_F(FormWidgetStaticTest_873, EncodeID_DifferentPageSameField_873) {
    int encoded1 = FormWidget::encodeID(3, 4);
    int encoded2 = FormWidget::encodeID(4, 4);
    
    EXPECT_NE(encoded1, encoded2);
}

// Test encodeID and decodeID roundtrip with larger values
TEST_F(FormWidgetStaticTest_873, EncodeDecodeID_LargerValues_873) {
    unsigned int pageNum = 100;
    unsigned int fieldNum = 200;
    
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID and decodeID with boundary-like values
TEST_F(FormWidgetStaticTest_873, EncodeDecodeID_MaxFieldNum_873) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 0xFFFF;
    
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID consistency - same inputs always produce same output
TEST_F(FormWidgetStaticTest_873, EncodeID_Consistency_873) {
    int encoded1 = FormWidget::encodeID(7, 13);
    int encoded2 = FormWidget::encodeID(7, 13);
    
    EXPECT_EQ(encoded1, encoded2);
}

// Test multiple roundtrips to verify stability
TEST_F(FormWidgetStaticTest_873, EncodeDecodeID_MultipleRoundTrips_873) {
    for (unsigned int page = 0; page < 20; ++page) {
        for (unsigned int field = 0; field < 20; ++field) {
            int encoded = FormWidget::encodeID(page, field);
            
            unsigned int decodedPage = 0;
            unsigned int decodedField = 0;
            FormWidget::decodeID(encoded, &decodedPage, &decodedField);
            
            EXPECT_EQ(decodedPage, page) << "Failed for page=" << page << " field=" << field;
            EXPECT_EQ(decodedField, field) << "Failed for page=" << page << " field=" << field;
        }
    }
}

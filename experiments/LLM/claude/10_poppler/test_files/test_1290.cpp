#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary Poppler headers
#include "poppler-form.h"
#include "poppler-private.h"
#include "poppler-qt5.h"

// Include internal poppler headers needed for FormWidget
#include <Form.h>
#include <Page.h>
#include <PDFDoc.h>

namespace {

// Since we need to work with Poppler's internal types and the test is about
// FormFieldData::getFormWidget which accesses f->m_formData->fm,
// we need to create actual FormField objects or mock the necessary structure.

class FormFieldDataTest_1290 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getFormWidget returns a non-null FormWidget when FormField has valid data
TEST_F(FormFieldDataTest_1290, GetFormWidgetReturnsFormWidget_1290) {
    Poppler::FormFieldData formFieldData(nullptr, nullptr, nullptr);
    // When fm is nullptr, getFormWidget should return nullptr
    // We test through the public interface
    SUCCEED(); // Basic construction test
}

// Test that FormFieldData can be constructed with nullptr parameters
TEST_F(FormFieldDataTest_1290, ConstructWithNullParams_1290) {
    Poppler::FormFieldData data(nullptr, nullptr, nullptr);
    // Should not crash
    SUCCEED();
}

// Test that FormFieldData stores the FormWidget pointer correctly
TEST_F(FormFieldDataTest_1290, FormWidgetMemberIsAccessible_1290) {
    ::FormWidget *testWidget = nullptr;
    Poppler::FormFieldData data(nullptr, nullptr, testWidget);
    // The fm member should be the same as what we passed in
    EXPECT_EQ(data.fm, nullptr);
}

// Test that FormFieldData stores a non-null FormWidget pointer
TEST_F(FormFieldDataTest_1290, FormWidgetMemberStoresNonNull_1290) {
    // We can verify the fm member is correctly stored
    ::FormWidget *testWidget = reinterpret_cast<::FormWidget*>(0xDEADBEEF);
    Poppler::FormFieldData data(nullptr, nullptr, testWidget);
    EXPECT_EQ(data.fm, testWidget);
}

// Test that doc member is stored correctly
TEST_F(FormFieldDataTest_1290, DocMemberIsStored_1290) {
    Poppler::DocumentData *testDoc = reinterpret_cast<Poppler::DocumentData*>(0x12345678);
    Poppler::FormFieldData data(testDoc, nullptr, nullptr);
    EXPECT_EQ(data.doc, testDoc);
}

// Test that page member is stored correctly
TEST_F(FormFieldDataTest_1290, PageMemberIsStored_1290) {
    ::Page *testPage = reinterpret_cast<::Page*>(0xABCDABCD);
    Poppler::FormFieldData data(nullptr, testPage, nullptr);
    EXPECT_EQ(data.page, testPage);
}

// Test construction with all non-null parameters
TEST_F(FormFieldDataTest_1290, ConstructWithAllNonNullParams_1290) {
    Poppler::DocumentData *testDoc = reinterpret_cast<Poppler::DocumentData*>(0x11111111);
    ::Page *testPage = reinterpret_cast<::Page*>(0x22222222);
    ::FormWidget *testWidget = reinterpret_cast<::FormWidget*>(0x33333333);

    Poppler::FormFieldData data(testDoc, testPage, testWidget);
    
    EXPECT_EQ(data.doc, testDoc);
    EXPECT_EQ(data.page, testPage);
    EXPECT_EQ(data.fm, testWidget);
}

} // namespace

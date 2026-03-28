#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler-qt5 headers
#include "poppler-qt5.h"
#include "poppler-form.h"
#include "poppler-private.h"

namespace {

class FormFieldIconDataTest_1291 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getData returns a non-null pointer for a default-constructed FormFieldIcon
TEST_F(FormFieldIconDataTest_1291, GetDataReturnsPointerForDefaultIcon_1291)
{
    // FormFieldIcon with default construction
    Poppler::FormFieldIcon icon(nullptr);
    Poppler::FormFieldIconData accessor;
    
    Poppler::FormFieldIconData *result = accessor.getData(icon);
    // The d_ptr should exist (allocated during construction)
    EXPECT_NE(result, nullptr);
}

// Test that getData returns the internal d_ptr consistently
TEST_F(FormFieldIconDataTest_1291, GetDataReturnsSamePointerOnMultipleCalls_1291)
{
    Poppler::FormFieldIcon icon(nullptr);
    Poppler::FormFieldIconData accessor;
    
    Poppler::FormFieldIconData *result1 = accessor.getData(icon);
    Poppler::FormFieldIconData *result2 = accessor.getData(icon);
    
    // Multiple calls on the same icon should return the same d_ptr
    EXPECT_EQ(result1, result2);
}

// Test that different FormFieldIcon instances have different d_ptr
TEST_F(FormFieldIconDataTest_1291, DifferentIconsHaveDifferentData_1291)
{
    Poppler::FormFieldIcon icon1(nullptr);
    Poppler::FormFieldIcon icon2(nullptr);
    Poppler::FormFieldIconData accessor;
    
    Poppler::FormFieldIconData *data1 = accessor.getData(icon1);
    Poppler::FormFieldIconData *data2 = accessor.getData(icon2);
    
    // Two separately constructed icons should have distinct d_ptrs
    EXPECT_NE(data1, data2);
}

// Test that a copy-constructed FormFieldIcon shares or has valid d_ptr
TEST_F(FormFieldIconDataTest_1291, CopiedIconGetDataReturnsValidPointer_1291)
{
    Poppler::FormFieldIcon icon1(nullptr);
    Poppler::FormFieldIcon icon2(icon1);
    Poppler::FormFieldIconData accessor;
    
    Poppler::FormFieldIconData *data1 = accessor.getData(icon1);
    Poppler::FormFieldIconData *data2 = accessor.getData(icon2);
    
    // Both should return valid pointers
    EXPECT_NE(data1, nullptr);
    EXPECT_NE(data2, nullptr);
}

// Test getData can be called on a const reference to FormFieldIcon
TEST_F(FormFieldIconDataTest_1291, GetDataWorksWithConstReference_1291)
{
    Poppler::FormFieldIcon icon(nullptr);
    const Poppler::FormFieldIcon &constRef = icon;
    Poppler::FormFieldIconData accessor;
    
    Poppler::FormFieldIconData *result = accessor.getData(constRef);
    EXPECT_NE(result, nullptr);
}

// Test that the accessor object itself doesn't affect the result
TEST_F(FormFieldIconDataTest_1291, DifferentAccessorsSameResult_1291)
{
    Poppler::FormFieldIcon icon(nullptr);
    Poppler::FormFieldIconData accessor1;
    Poppler::FormFieldIconData accessor2;
    
    Poppler::FormFieldIconData *result1 = accessor1.getData(icon);
    Poppler::FormFieldIconData *result2 = accessor2.getData(icon);
    
    // Different accessor instances should return the same d_ptr for the same icon
    EXPECT_EQ(result1, result2);
}

} // namespace

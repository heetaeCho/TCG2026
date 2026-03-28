#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Mock classes for testing
class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visit, (const TiffSizeEntry&), (override));
};

class MockTiffEncoder : public TiffEncoder {
public:
    MOCK_METHOD(void, encode, (const TiffSizeEntry&, const Exifdatum*), (override));
};

// Unit Test for TiffSizeEntry
TEST_F(TiffSizeEntryTest_244, DefaultConstructor_244) {
    uint16_t tag = 42;
    IfdId group = 1;
    uint16_t dtTag = 100;
    IfdId dtGroup = 2;
    
    // Create a TiffSizeEntry instance
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    // Verify constructor sets the values correctly
    EXPECT_EQ(entry.dtTag(), dtTag);
    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

TEST_F(TiffSizeEntryTest_244, DtGroupFunction_244) {
    uint16_t tag = 42;
    IfdId group = 1;
    uint16_t dtTag = 100;
    IfdId dtGroup = 2;
    
    // Create a TiffSizeEntry instance
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    // Test dtGroup function
    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

TEST_F(TiffSizeEntryTest_244, DoAccept_244) {
    uint16_t tag = 42;
    IfdId group = 1;
    uint16_t dtTag = 100;
    IfdId dtGroup = 2;
    
    // Create a TiffSizeEntry instance
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    // Mock the visitor
    MockTiffVisitor visitor;

    // Set up expectations
    EXPECT_CALL(visitor, visit(testing::Ref(entry))).Times(1);

    // Call doAccept
    entry.doAccept(visitor);
}

TEST_F(TiffSizeEntryTest_244, DoEncode_244) {
    uint16_t tag = 42;
    IfdId group = 1;
    uint16_t dtTag = 100;
    IfdId dtGroup = 2;
    
    // Create a TiffSizeEntry instance
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    // Mock the encoder
    MockTiffEncoder encoder;

    // Set up expectations
    Exifdatum datum;
    EXPECT_CALL(encoder, encode(testing::Ref(entry), &datum)).Times(1);

    // Call doEncode
    entry.doEncode(encoder, &datum);
}

TEST_F(TiffSizeEntryTest_244, DoClone_244) {
    uint16_t tag = 42;
    IfdId group = 1;
    uint16_t dtTag = 100;
    IfdId dtGroup = 2;

    // Create a TiffSizeEntry instance
    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    // Test the clone functionality
    const TiffSizeEntry* clonedEntry = entry.doClone();
    EXPECT_NE(clonedEntry, nullptr);
    EXPECT_EQ(clonedEntry->dtTag(), dtTag);
    EXPECT_EQ(clonedEntry->dtGroup(), dtGroup);
}

TEST_F(TiffSizeEntryTest_244, ExceptionalCase_244) {
    // Test if creating TiffSizeEntry with invalid dtGroup throws an exception
    uint16_t tag = 42;
    IfdId group = 1;
    uint16_t dtTag = 100;
    IfdId invalidDtGroup = static_cast<IfdId>(-1);  // Invalid value
    
    try {
        TiffSizeEntry entry(tag, group, dtTag, invalidDtGroup);
        FAIL() << "Expected exception for invalid dtGroup";
    } catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "Invalid IfdId");
    }
}
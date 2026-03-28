#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::AtLeast;

// Mock TiffVisitor to observe interactions
class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visitEntry, (TiffEntry* object), (override));
    MOCK_METHOD(void, visitDataEntry, (TiffDataEntry* object), (override));
    MOCK_METHOD(void, visitImageEntry, (TiffImageEntry* object), (override));
    MOCK_METHOD(void, visitSizeEntry, (TiffSizeEntry* object), (override));
    MOCK_METHOD(void, visitDirectory, (TiffDirectory* object), (override));
    MOCK_METHOD(void, visitDirectoryNext, (TiffDirectory* object), (override));
    MOCK_METHOD(void, visitDirectoryEnd, (TiffDirectory* object), (override));
    MOCK_METHOD(void, visitSubIfd, (TiffSubIfd* object), (override));
    MOCK_METHOD(void, visitMnEntry, (TiffMnEntry* object), (override));
    MOCK_METHOD(void, visitIfdMakernote, (TiffIfdMakernote* object), (override));
    MOCK_METHOD(void, visitIfdMakernoteEnd, (TiffIfdMakernote* object), (override));
    MOCK_METHOD(void, visitBinaryArray, (TiffBinaryArray* object), (override));
    MOCK_METHOD(void, visitBinaryArrayEnd, (TiffBinaryArray* object), (override));
    MOCK_METHOD(void, visitBinaryElement, (TiffBinaryElement* object), (override));
};

class TiffMnEntryTest_344 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that accept calls visitMnEntry on the visitor
TEST_F(TiffMnEntryTest_344, AcceptCallsVisitMnEntry_344) {
    // Create a TiffMnEntry with some tag, group, and mnGroup
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    MockTiffVisitor visitor;

    // When mn_ is null (default constructed), only visitMnEntry should be called
    EXPECT_CALL(visitor, visitMnEntry(&entry)).Times(1);

    entry.accept(visitor);
}

// Test that when geKnownMakernote go event is true (default), behavior is normal
TEST_F(TiffMnEntryTest_344, AcceptWithGoKnownMakernoteTrue_344) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    MockTiffVisitor visitor;

    // Default go state should be true for all events
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));

    EXPECT_CALL(visitor, visitMnEntry(&entry)).Times(1);

    entry.accept(visitor);
}

// Test that when geKnownMakernote is set to false, mn_ gets nullified
// This is observable because on subsequent accept calls, mn_->accept won't be called
TEST_F(TiffMnEntryTest_344, AcceptWithGoKnownMakernoteFalse_NullsMn_344) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    MockTiffVisitor visitor;

    // Set geKnownMakernote to false
    visitor.setGo(TiffVisitor::geKnownMakernote, false);

    EXPECT_CALL(visitor, visitMnEntry(&entry)).Times(1);

    entry.accept(visitor);

    // mn_ should now be null. Calling accept again should still call visitMnEntry
    // but no mn_->accept since mn_ was set to nullptr
    MockTiffVisitor visitor2;
    EXPECT_CALL(visitor2, visitMnEntry(&entry)).Times(1);

    entry.accept(visitor2);
}

// Test basic construction with different tag values
TEST_F(TiffMnEntryTest_344, ConstructionWithDifferentTags_344) {
    TiffMnEntry entry1(0x0001, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry1.tag(), 0x0001);
    EXPECT_EQ(entry1.group(), IfdId::exifId);

    TiffMnEntry entry2(0xFFFF, IfdId::ifd0Id, IfdId::nikonId);
    EXPECT_EQ(entry2.tag(), 0xFFFF);
    EXPECT_EQ(entry2.group(), IfdId::ifd0Id);
}

// Test that tag 0 is valid
TEST_F(TiffMnEntryTest_344, ConstructionWithZeroTag_344) {
    TiffMnEntry entry(0x0000, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry.tag(), 0x0000);
}

// Test TiffVisitor setGo and go methods
TEST_F(TiffMnEntryTest_344, VisitorGoEvents_344) {
    MockTiffVisitor visitor;

    // Default should be true
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));

    // Set to false
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));

    // Set back to true
    visitor.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
}

// Test multiple accept calls - visitor should be called each time
TEST_F(TiffMnEntryTest_344, MultipleAcceptCalls_344) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visitMnEntry(&entry)).Times(3);

    entry.accept(visitor);
    entry.accept(visitor);
    entry.accept(visitor);
}

// Test that destruction of TiffMnEntry doesn't crash (no mn_ set)
TEST_F(TiffMnEntryTest_344, DestructionWithNullMn_344) {
    auto entry = std::make_unique<TiffMnEntry>(0x927c, IfdId::exifId, IfdId::canonId);
    // Should not crash on destruction
    entry.reset();
}

// Test that setGo with geKnownMakernote false causes mn_ to be cleared
// and subsequent accept doesn't crash
TEST_F(TiffMnEntryTest_344, AcceptAfterMnCleared_344) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    // First accept with geKnownMakernote = false to clear mn_
    MockTiffVisitor visitor1;
    visitor1.setGo(TiffVisitor::geKnownMakernote, false);
    EXPECT_CALL(visitor1, visitMnEntry(&entry)).Times(1);
    entry.accept(visitor1);

    // Second accept with geKnownMakernote = true, mn_ should be null so no crash
    MockTiffVisitor visitor2;
    EXPECT_CALL(visitor2, visitMnEntry(&entry)).Times(1);
    entry.accept(visitor2);
}

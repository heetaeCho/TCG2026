#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

// Mock TiffVisitor to verify that doAccept calls visitSizeEntry
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

class TiffSizeEntryTest_341 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffSizeEntry can be constructed with valid parameters
TEST_F(TiffSizeEntryTest_341, Construction_ValidParameters_341) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0111;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtTag(), dtTag);
    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

// Test dtTag() returns the correct data tag
TEST_F(TiffSizeEntryTest_341, DtTagReturnsCorrectValue_341) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0202;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtTag(), 0x0202);
}

// Test dtGroup() returns the correct data group
TEST_F(TiffSizeEntryTest_341, DtGroupReturnsCorrectValue_341) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0202;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtGroup(), IfdId::ifd1Id);
}

// Test doAccept calls visitSizeEntry on the visitor with the correct pointer
TEST_F(TiffSizeEntryTest_341, DoAcceptCallsVisitSizeEntry_341) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0111;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitSizeEntry(&entry)).Times(1);

    entry.accept(mockVisitor);
}

// Test that visitSizeEntry is called (not visitEntry or other visit methods)
TEST_F(TiffSizeEntryTest_341, DoAcceptCallsOnlyVisitSizeEntry_341) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0111;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitSizeEntry(&entry)).Times(1);
    EXPECT_CALL(mockVisitor, visitEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitDataEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitImageEntry(::testing::_)).Times(0);

    entry.accept(mockVisitor);
}

// Test construction with boundary tag values
TEST_F(TiffSizeEntryTest_341, ConstructionWithBoundaryTagValues_341) {
    // Test with maximum uint16_t values
    uint16_t tag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0xFFFF;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtTag(), 0xFFFF);
}

// Test construction with zero tag values
TEST_F(TiffSizeEntryTest_341, ConstructionWithZeroTagValues_341) {
    uint16_t tag = 0x0000;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0000;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.dtTag(), 0x0000);
}

// Test that tag and group from TiffEntryBase are properly set
TEST_F(TiffSizeEntryTest_341, BaseClassTagAndGroupAreSet_341) {
    uint16_t tag = 0x0117;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0111;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(entry.tag(), tag);
}

// Test multiple accept calls on the same entry
TEST_F(TiffSizeEntryTest_341, MultipleAcceptCalls_341) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0111;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry entry(tag, group, dtTag, dtGroup);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitSizeEntry(&entry)).Times(3);

    entry.accept(mockVisitor);
    entry.accept(mockVisitor);
    entry.accept(mockVisitor);
}

// Test different dtTag and dtGroup combinations
TEST_F(TiffSizeEntryTest_341, DifferentDtTagAndDtGroupCombinations_341) {
    {
        TiffSizeEntry entry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
        EXPECT_EQ(entry.dtTag(), 0x0111);
        EXPECT_EQ(entry.dtGroup(), IfdId::ifd0Id);
    }
    {
        TiffSizeEntry entry(0x0202, IfdId::ifd1Id, 0x0201, IfdId::ifd1Id);
        EXPECT_EQ(entry.dtTag(), 0x0201);
        EXPECT_EQ(entry.dtGroup(), IfdId::ifd1Id);
    }
}

}  // namespace Internal
}  // namespace Exiv2

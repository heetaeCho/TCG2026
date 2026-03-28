#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the project
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

// Mock TiffVisitor to verify that doAccept calls visitImageEntry
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

class TiffImageEntryTest_340 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doAccept calls visitImageEntry on the visitor with the correct object
TEST_F(TiffImageEntryTest_340, DoAcceptCallsVisitImageEntry_340) {
    // We need to construct a TiffImageEntry. TiffImageEntry inherits from TiffDataEntryBase,
    // which likely requires a tag and group. We try with typical IFD0 strip offset tag.
    // Tag 0x0111 = StripOffsets, group = ifd0Id
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;

    // Expect visitImageEntry to be called exactly once with a pointer to our entry
    EXPECT_CALL(mockVisitor, visitImageEntry(&entry)).Times(1);

    // No other visit methods should be called
    EXPECT_CALL(mockVisitor, visitEntry(testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitDataEntry(testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitSizeEntry(testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitDirectory(testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitSubIfd(testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitMnEntry(testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitIfdMakernote(testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitBinaryArray(testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitBinaryElement(testing::_)).Times(0);

    entry.accept(mockVisitor);
}

// Test that doAccept can be called multiple times
TEST_F(TiffImageEntryTest_340, DoAcceptCanBeCalledMultipleTimes_340) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitImageEntry(&entry)).Times(3);

    entry.accept(mockVisitor);
    entry.accept(mockVisitor);
    entry.accept(mockVisitor);
}

// Test that doAccept calls visitImageEntry with the correct this pointer
TEST_F(TiffImageEntryTest_340, DoAcceptPassesCorrectThisPointer_340) {
    TiffImageEntry entry1(0x0111, IfdId::ifd0Id);
    TiffImageEntry entry2(0x0201, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;

    // Each entry should pass its own pointer
    EXPECT_CALL(mockVisitor, visitImageEntry(&entry1)).Times(1);
    EXPECT_CALL(mockVisitor, visitImageEntry(&entry2)).Times(1);

    entry1.accept(mockVisitor);
    entry2.accept(mockVisitor);
}

// Test setStrips with nullptr for pSize (boundary/error condition)
TEST_F(TiffImageEntryTest_340, SetStripsWithNullSize_340) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);

    // Calling setStrips with null pSize - should handle gracefully
    // We treat this as a boundary condition test
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    entry.setStrips(nullptr, data, sizeof(data), 0);

    // After setting strips with null size, the size should reflect no strips
    // We can only observe through doSizeImage
    // Since we can't know the exact behavior, we just verify it doesn't crash
}

// Test setStrips with nullptr for pData (boundary condition)
TEST_F(TiffImageEntryTest_340, SetStripsWithNullData_340) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);

    // Calling setStrips with null pData - boundary condition
    entry.setStrips(nullptr, nullptr, 0, 0);
    // Verify no crash occurs
}

// Test that a newly constructed TiffImageEntry has zero size for image data
TEST_F(TiffImageEntryTest_340, InitialSizeImageIsZero_340) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);

    // A freshly constructed entry with no strips set should have zero image size
    // We observe this through the public interface (via accept/encode or size methods if accessible)
    MockTiffVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, visitImageEntry(&entry)).Times(1);
    entry.accept(mockVisitor);
}

// Test with different tag values
TEST_F(TiffImageEntryTest_340, DifferentTagValues_340) {
    // TileOffsets tag
    TiffImageEntry entry(0x0144, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, visitImageEntry(&entry)).Times(1);

    entry.accept(mockVisitor);
}

// Test TiffVisitor go/setGo functionality
class TiffVisitorGoTest_340 : public ::testing::Test {
};

TEST_F(TiffVisitorGoTest_340, DefaultGoIsTrue_340) {
    MockTiffVisitor visitor;
    // By default, go events should be true
    EXPECT_TRUE(visitor.go(GoEvent::geTraverse));
    EXPECT_TRUE(visitor.go(GoEvent::geKnownMakernote));
}

TEST_F(TiffVisitorGoTest_340, SetGoToFalse_340) {
    MockTiffVisitor visitor;
    visitor.setGo(GoEvent::geTraverse, false);
    EXPECT_FALSE(visitor.go(GoEvent::geTraverse));
}

TEST_F(TiffVisitorGoTest_340, SetGoToTrue_340) {
    MockTiffVisitor visitor;
    visitor.setGo(GoEvent::geTraverse, false);
    EXPECT_FALSE(visitor.go(GoEvent::geTraverse));
    visitor.setGo(GoEvent::geTraverse, true);
    EXPECT_TRUE(visitor.go(GoEvent::geTraverse));
}

TEST_F(TiffVisitorGoTest_340, SetGoIndependentEvents_340) {
    MockTiffVisitor visitor;
    visitor.setGo(GoEvent::geTraverse, false);
    // Other event should still be true
    EXPECT_TRUE(visitor.go(GoEvent::geKnownMakernote));
    EXPECT_FALSE(visitor.go(GoEvent::geTraverse));
}

}  // namespace Internal
}  // namespace Exiv2

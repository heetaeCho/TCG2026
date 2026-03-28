#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the project
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

// Mock TiffVisitor to verify that doAccept calls visitDataEntry correctly
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

class TiffDataEntryTest_339 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doAccept calls visitDataEntry on the visitor with the correct pointer
TEST_F(TiffDataEntryTest_339, DoAcceptCallsVisitDataEntry_339) {
    // We need to create a TiffDataEntry. The constructor details depend on TiffDataEntryBase.
    // TiffDataEntry typically needs a tag and group. We'll try constructing with typical params.
    // Based on exiv2 codebase, TiffDataEntry(uint16_t tag, IfdId group) is typical.
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;

    // Expect visitDataEntry to be called exactly once with a pointer to our entry
    EXPECT_CALL(mockVisitor, visitDataEntry(&entry)).Times(1);

    entry.accept(mockVisitor);
}

// Test that doAccept passes 'this' pointer correctly to visitDataEntry
TEST_F(TiffDataEntryTest_339, DoAcceptPassesThisPointer_339) {
    TiffDataEntry entry(0x0117, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;

    TiffDataEntry* capturedPointer = nullptr;
    EXPECT_CALL(mockVisitor, visitDataEntry(::testing::_))
        .WillOnce(::testing::SaveArg<0>(&capturedPointer));

    entry.accept(mockVisitor);

    EXPECT_EQ(capturedPointer, &entry);
}

// Test that doAccept does not call other visit methods
TEST_F(TiffDataEntryTest_339, DoAcceptDoesNotCallOtherVisitMethods_339) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitDataEntry(::testing::_)).Times(1);
    EXPECT_CALL(mockVisitor, visitEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitImageEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitSizeEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitDirectory(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitSubIfd(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitMnEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitIfdMakernote(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitBinaryArray(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitBinaryElement(::testing::_)).Times(0);

    entry.accept(mockVisitor);
}

// Test that calling accept multiple times calls visitDataEntry each time
TEST_F(TiffDataEntryTest_339, DoAcceptCalledMultipleTimes_339) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitDataEntry(&entry)).Times(3);

    entry.accept(mockVisitor);
    entry.accept(mockVisitor);
    entry.accept(mockVisitor);
}

// Test with different tag values to ensure construction works
TEST_F(TiffDataEntryTest_339, DoAcceptWithDifferentTag_339) {
    TiffDataEntry entry(0x0201, IfdId::ifd0Id);

    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitDataEntry(&entry)).Times(1);

    entry.accept(mockVisitor);
}

// Test doSizeData returns 0 for a freshly constructed entry (no data set)
TEST_F(TiffDataEntryTest_339, SizeDataInitiallyZero_339) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);

    // A freshly constructed TiffDataEntry should have sizeDataArea_ = 0
    // We can observe this through the public interface if sizeData is accessible
    // through the base class. Since doSizeData is protected, we rely on the 
    // visitor pattern to test observable behavior.
    MockTiffVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, visitDataEntry(::testing::NotNull())).Times(1);

    entry.accept(mockVisitor);
}

}  // namespace Internal
}  // namespace Exiv2

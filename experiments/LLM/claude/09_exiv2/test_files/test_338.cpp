#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and minimal includes to make the test compile
// We need to include the relevant headers from the project
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2::Internal;

// Mock TiffVisitor to verify interactions
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

class TiffEntryTest_338 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doAccept calls visitEntry on the visitor with the correct TiffEntry pointer
TEST_F(TiffEntryTest_338, DoAcceptCallsVisitEntry_338) {
    // Create a TiffEntry - using a tag and group that are valid
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    MockTiffVisitor mockVisitor;

    // Expect visitEntry to be called exactly once with a pointer to our entry
    EXPECT_CALL(mockVisitor, visitEntry(&entry)).Times(1);

    entry.accept(mockVisitor);
}

// Test that doAccept passes 'this' pointer correctly to visitor
TEST_F(TiffEntryTest_338, DoAcceptPassesCorrectThisPointer_338) {
    TiffEntry entry(0x0110, IfdId::ifd0Id);
    MockTiffVisitor mockVisitor;

    TiffEntry* capturedPtr = nullptr;
    EXPECT_CALL(mockVisitor, visitEntry(::testing::_))
        .WillOnce(::testing::SaveArg<0>(&capturedPtr));

    entry.accept(mockVisitor);

    EXPECT_EQ(capturedPtr, &entry);
}

// Test that doAccept does not call other visit methods
TEST_F(TiffEntryTest_338, DoAcceptDoesNotCallOtherVisitMethods_338) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitEntry(::testing::_)).Times(1);
    EXPECT_CALL(mockVisitor, visitDataEntry(::testing::_)).Times(0);
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

// Test with multiple TiffEntry objects to ensure each passes its own pointer
TEST_F(TiffEntryTest_338, MultipleEntriesPassCorrectPointers_338) {
    TiffEntry entry1(0x0100, IfdId::ifd0Id);
    TiffEntry entry2(0x0110, IfdId::ifd0Id);
    MockTiffVisitor mockVisitor;

    ::testing::InSequence seq;
    EXPECT_CALL(mockVisitor, visitEntry(&entry1)).Times(1);
    EXPECT_CALL(mockVisitor, visitEntry(&entry2)).Times(1);

    entry1.accept(mockVisitor);
    entry2.accept(mockVisitor);
}

// Test that calling doAccept multiple times on the same entry calls visitEntry each time
TEST_F(TiffEntryTest_338, DoAcceptCalledMultipleTimes_338) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitEntry(&entry)).Times(3);

    entry.accept(mockVisitor);
    entry.accept(mockVisitor);
    entry.accept(mockVisitor);
}

// Test TiffVisitor go/setGo functionality
class TiffVisitorGoTest_338 : public ::testing::Test {
protected:
    MockTiffVisitor visitor;
};

// Test that TiffVisitor default go state is true
TEST_F(TiffVisitorGoTest_338, DefaultGoStateIsTrue_338) {
    // By default, go events should be true
    EXPECT_TRUE(visitor.go(GoEvent::geTraverse));
    EXPECT_TRUE(visitor.go(GoEvent::geKnownMakernote));
}

// Test setGo to false
TEST_F(TiffVisitorGoTest_338, SetGoToFalse_338) {
    visitor.setGo(GoEvent::geTraverse, false);
    EXPECT_FALSE(visitor.go(GoEvent::geTraverse));
}

// Test setGo to true after setting false
TEST_F(TiffVisitorGoTest_338, SetGoBackToTrue_338) {
    visitor.setGo(GoEvent::geTraverse, false);
    EXPECT_FALSE(visitor.go(GoEvent::geTraverse));
    
    visitor.setGo(GoEvent::geTraverse, true);
    EXPECT_TRUE(visitor.go(GoEvent::geTraverse));
}

// Test that setting one GoEvent does not affect others
TEST_F(TiffVisitorGoTest_338, SetGoIndependentEvents_338) {
    visitor.setGo(GoEvent::geTraverse, false);
    EXPECT_FALSE(visitor.go(GoEvent::geTraverse));
    EXPECT_TRUE(visitor.go(GoEvent::geKnownMakernote));
}

// Test with different TiffEntry tags
TEST_F(TiffEntryTest_338, DifferentTagValues_338) {
    TiffEntry entry(0x0000, IfdId::ifd0Id);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitEntry(&entry)).Times(1);
    entry.accept(mockVisitor);
}

TEST_F(TiffEntryTest_338, MaxTagValue_338) {
    TiffEntry entry(0xFFFF, IfdId::ifd0Id);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitEntry(&entry)).Times(1);
    entry.accept(mockVisitor);
}

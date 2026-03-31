#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::AtLeast;

// Mock TiffVisitor to observe calls
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

class TiffSubIfdTest_343 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that accept calls visitSubIfd on the visitor with the correct object
TEST_F(TiffSubIfdTest_343, AcceptCallsVisitSubIfd_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visitSubIfd(&subIfd)).Times(1);

    subIfd.accept(visitor);
}

// Test that constructor sets tag correctly
TEST_F(TiffSubIfdTest_343, ConstructorSetsTag_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.tag(), 0x014a);
}

// Test that constructor sets group correctly
TEST_F(TiffSubIfdTest_343, ConstructorSetsGroup_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.group(), IfdId::ifd0Id);
}

// Test with different tag values
TEST_F(TiffSubIfdTest_343, ConstructorWithDifferentTag_343) {
    TiffSubIfd subIfd(0x0000, IfdId::ifd1Id, IfdId::subImage2Id);
    EXPECT_EQ(subIfd.tag(), 0x0000);
    EXPECT_EQ(subIfd.group(), IfdId::ifd1Id);
}

// Test with max tag value
TEST_F(TiffSubIfdTest_343, ConstructorWithMaxTag_343) {
    TiffSubIfd subIfd(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.tag(), 0xFFFF);
}

// Test that accept with no child IFDs only calls visitSubIfd
TEST_F(TiffSubIfdTest_343, AcceptNoChildrenOnlyVisitsSubIfd_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    MockTiffVisitor visitor;

    // Only visitSubIfd should be called, no other visit methods for children
    EXPECT_CALL(visitor, visitSubIfd(&subIfd)).Times(1);
    // No calls to visitDirectory or other child-related methods expected
    // since there are no child IFDs

    subIfd.accept(visitor);
}

// Test that when go(geTraverse) is false after visitSubIfd, children are not traversed
TEST_F(TiffSubIfdTest_343, AcceptStopsWhenGoTraverseIsFalse_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visitSubIfd(&subIfd)).WillOnce([&visitor](TiffSubIfd*) {
        visitor.setGo(TiffVisitor::geTraverse, false);
    });

    subIfd.accept(visitor);
}

// Test that start() returns nullptr by default
TEST_F(TiffSubIfdTest_343, StartReturnsNullByDefault_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.start(), nullptr);
}

// Test setStart
TEST_F(TiffSubIfdTest_343, SetStartUpdatesStart_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    Exiv2::byte data[] = {0x01, 0x02, 0x03};
    subIfd.setStart(data);
    EXPECT_EQ(subIfd.start(), data);
}

// Test idx returns default value
TEST_F(TiffSubIfdTest_343, IdxReturnsDefaultValue_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    // idx() should return some default integer value
    int idx = subIfd.idx();
    // Just verify it doesn't crash and returns a value
    (void)idx;
}

// Test that visitor's go state is properly checked
TEST_F(TiffSubIfdTest_343, VisitorGoStateDefaultTrue_343) {
    MockTiffVisitor visitor;
    // By default, go should be true for geTraverse
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
}

// Test that visitor's go state can be set to false
TEST_F(TiffSubIfdTest_343, VisitorSetGoToFalse_343) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
}

// Test that visitor's go for knownMakernote is independent
TEST_F(TiffSubIfdTest_343, VisitorGoKnownMakernoteIndependent_343) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));
}

// Test count on empty TiffSubIfd
TEST_F(TiffSubIfdTest_343, CountOnEmptySubIfd_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t c = subIfd.count();
    // Empty sub IFD should have count 0
    EXPECT_EQ(c, 0u);
}

// Test size on empty TiffSubIfd
TEST_F(TiffSubIfdTest_343, SizeOnEmptySubIfd_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t s = subIfd.size();
    // Verify it returns without error
    (void)s;
}

// Test sizeData on empty TiffSubIfd
TEST_F(TiffSubIfdTest_343, SizeDataOnEmptySubIfd_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t sd = subIfd.sizeData();
    EXPECT_EQ(sd, 0u);
}

// Test sizeImage on empty TiffSubIfd
TEST_F(TiffSubIfdTest_343, SizeImageOnEmptySubIfd_343) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t si = subIfd.sizeImage();
    EXPECT_EQ(si, 0u);
}

// Test that assignment operator is deleted (compile-time check is implicit)
// We test that the class can be constructed and used normally
TEST_F(TiffSubIfdTest_343, NoCopyAssignment_343) {
    TiffSubIfd subIfd1(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    // TiffSubIfd subIfd2 = subIfd1; // This should not compile - assignment is deleted
    // Just verify the object is usable
    EXPECT_EQ(subIfd1.tag(), 0x014a);
}

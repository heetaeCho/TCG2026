#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

// Mock TiffVisitor to observe calls made during doAccept
class MockTiffVisitor : public TiffVisitor {
public:
    // We need to track go() calls - but go() is not virtual in the provided interface,
    // it's a regular method. We'll use setGo to control behavior.
    // We mock the virtual visit methods.
    MOCK_METHOD(void, visitEntry, (TiffEntry*), (override));
    MOCK_METHOD(void, visitDataEntry, (TiffDataEntry*), (override));
    MOCK_METHOD(void, visitImageEntry, (TiffImageEntry*), (override));
    MOCK_METHOD(void, visitSizeEntry, (TiffSizeEntry*), (override));
    MOCK_METHOD(void, visitDirectory, (TiffDirectory*), (override));
    MOCK_METHOD(void, visitDirectoryNext, (TiffDirectory*), (override));
    MOCK_METHOD(void, visitDirectoryEnd, (TiffDirectory*), (override));
    MOCK_METHOD(void, visitSubIfd, (TiffSubIfd*), (override));
    MOCK_METHOD(void, visitMnEntry, (TiffMnEntry*), (override));
    MOCK_METHOD(void, visitIfdMakernote, (TiffIfdMakernote*), (override));
    MOCK_METHOD(void, visitIfdMakernoteEnd, (TiffIfdMakernote*), (override));
    MOCK_METHOD(void, visitBinaryArray, (TiffBinaryArray*), (override));
    MOCK_METHOD(void, visitBinaryArrayEnd, (TiffBinaryArray*), (override));
    MOCK_METHOD(void, visitBinaryElement, (TiffBinaryElement*), (override));
};

class TiffIfdMakernoteTest_345 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: Construction with basic parameters
TEST_F(TiffIfdMakernoteTest_345, ConstructionBasic_345) {
    // Construct with nullptr header
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.tag(), 0x927c);
    EXPECT_EQ(makernote.group(), IfdId::exifId);
}

// Test: byteOrder returns invalidByteOrder by default
TEST_F(TiffIfdMakernoteTest_345, DefaultByteOrderIsInvalid_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.byteOrder(), invalidByteOrder);
}

// Test: setByteOrder changes byte order
TEST_F(TiffIfdMakernoteTest_345, SetByteOrderChangesOrder_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(bigEndian);
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
}

// Test: setByteOrder to littleEndian
TEST_F(TiffIfdMakernoteTest_345, SetByteOrderLittleEndian_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
}

// Test: mnOffset returns default 0
TEST_F(TiffIfdMakernoteTest_345, DefaultMnOffsetIsZero_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.mnOffset(), 0u);
}

// Test: sizeHeader with nullptr header returns 0
TEST_F(TiffIfdMakernoteTest_345, SizeHeaderWithNullHeader_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.sizeHeader(), 0u);
}

// Test: readHeader with nullptr header
TEST_F(TiffIfdMakernoteTest_345, ReadHeaderWithNullHeader_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    const Exiv2::byte data[] = {0x00, 0x01, 0x02, 0x03};
    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    // With no header, readHeader should return true (no header to fail)
    EXPECT_TRUE(result);
}

// Test: readHeader with null data and zero size
TEST_F(TiffIfdMakernoteTest_345, ReadHeaderWithNullData_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    bool result = makernote.readHeader(nullptr, 0, littleEndian);
    EXPECT_TRUE(result);
}

// Test: accept calls visitIfdMakernote when geTraverse is true
TEST_F(TiffIfdMakernoteTest_345, AcceptCallsVisitIfdMakernote_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    MockTiffVisitor visitor;

    // Both go events are true by default
    EXPECT_CALL(visitor, visitIfdMakernote(&makernote)).Times(1);
    EXPECT_CALL(visitor, visitIfdMakernoteEnd(&makernote)).Times(1);
    // The ifd_.accept will call visitDirectory on the internal ifd
    EXPECT_CALL(visitor, visitDirectory(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(visitor, visitDirectoryNext(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(visitor, visitDirectoryEnd(_)).Times(::testing::AnyNumber());

    makernote.accept(visitor);
}

// Test: accept does not call visitIfdMakernote when geTraverse is false
TEST_F(TiffIfdMakernoteTest_345, AcceptSkipsVisitWhenTraverseFalse_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    MockTiffVisitor visitor;

    visitor.setGo(TiffVisitor::geTraverse, false);

    EXPECT_CALL(visitor, visitIfdMakernote(_)).Times(0);
    EXPECT_CALL(visitor, visitIfdMakernoteEnd(_)).Times(0);
    // ifd_.accept might still be called if geKnownMakernote is true
    EXPECT_CALL(visitor, visitDirectory(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(visitor, visitDirectoryNext(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(visitor, visitDirectoryEnd(_)).Times(::testing::AnyNumber());

    makernote.accept(visitor);
}

// Test: accept does not traverse ifd when geKnownMakernote is false
TEST_F(TiffIfdMakernoteTest_345, AcceptSkipsIfdWhenKnownMakernoteFalse_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    MockTiffVisitor visitor;

    visitor.setGo(TiffVisitor::geKnownMakernote, false);

    EXPECT_CALL(visitor, visitIfdMakernote(&makernote)).Times(1);
    // Should NOT call visitDirectory since geKnownMakernote is false
    EXPECT_CALL(visitor, visitDirectory(_)).Times(0);
    // Should NOT call visitIfdMakernoteEnd since geKnownMakernote is false
    EXPECT_CALL(visitor, visitIfdMakernoteEnd(_)).Times(0);

    makernote.accept(visitor);
}

// Test: accept with both go events false
TEST_F(TiffIfdMakernoteTest_345, AcceptBothEventsFalse_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    MockTiffVisitor visitor;

    visitor.setGo(TiffVisitor::geTraverse, false);
    visitor.setGo(TiffVisitor::geKnownMakernote, false);

    EXPECT_CALL(visitor, visitIfdMakernote(_)).Times(0);
    EXPECT_CALL(visitor, visitIfdMakernoteEnd(_)).Times(0);
    EXPECT_CALL(visitor, visitDirectory(_)).Times(0);

    makernote.accept(visitor);
}

// Test: tag and group accessors
TEST_F(TiffIfdMakernoteTest_345, TagAndGroupAccessors_345) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::nikonId, nullptr, true);
    EXPECT_EQ(makernote.tag(), 0x0001);
    EXPECT_EQ(makernote.group(), IfdId::ifd0Id);
}

// Test: start() returns nullptr initially
TEST_F(TiffIfdMakernoteTest_345, StartReturnsNullInitially_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.start(), nullptr);
}

// Test: setStart and start
TEST_F(TiffIfdMakernoteTest_345, SetStartAndStart_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    Exiv2::byte data[] = {0x01, 0x02};
    makernote.setStart(data);
    EXPECT_EQ(makernote.start(), data);
}

// Test: accept with geTraverse true and geKnownMakernote true - ordering
TEST_F(TiffIfdMakernoteTest_345, AcceptCallOrderWithBothEventsTrue_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    MockTiffVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, visitIfdMakernote(&makernote)).Times(1);
        // ifd_.accept will trigger directory visits
        EXPECT_CALL(visitor, visitDirectory(_)).Times(::testing::AnyNumber());
        EXPECT_CALL(visitor, visitIfdMakernoteEnd(&makernote)).Times(1);
    }
    EXPECT_CALL(visitor, visitDirectoryNext(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(visitor, visitDirectoryEnd(_)).Times(::testing::AnyNumber());

    makernote.accept(visitor);
}

// Test: setImageByteOrder
TEST_F(TiffIfdMakernoteTest_345, SetImageByteOrder_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // setImageByteOrder should not affect byteOrder() directly (byteOrder is mnByteOrder)
    makernote.setImageByteOrder(bigEndian);
    // byteOrder should still be invalid since we didn't call setByteOrder
    // (imageByteOrder and byteOrder may be different fields)
    // We can't assert much without knowing internals, but at least it shouldn't crash
    SUCCEED();
}

// Test: Construction with hasNext true vs false
TEST_F(TiffIfdMakernoteTest_345, ConstructionWithHasNextTrue_345) {
    TiffIfdMakernote makernoteWithNext(0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    TiffIfdMakernote makernoteWithoutNext(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // Both should construct without issues
    EXPECT_EQ(makernoteWithNext.tag(), 0x927c);
    EXPECT_EQ(makernoteWithoutNext.tag(), 0x927c);
}

// Test: Multiple setByteOrder calls
TEST_F(TiffIfdMakernoteTest_345, MultipleSetByteOrderCalls_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(bigEndian);
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
    makernote.setByteOrder(littleEndian);
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
    makernote.setByteOrder(invalidByteOrder);
    EXPECT_EQ(makernote.byteOrder(), invalidByteOrder);
}

// Test: TiffVisitor go() default values
TEST_F(TiffIfdMakernoteTest_345, VisitorGoDefaultValues_345) {
    MockTiffVisitor visitor;
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));
}

// Test: TiffVisitor setGo and go
TEST_F(TiffIfdMakernoteTest_345, VisitorSetGoAndGo_345) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));

    visitor.setGo(TiffVisitor::geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geKnownMakernote));

    visitor.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
}

// Test: accept when visitor changes go state during visitIfdMakernote
// This tests that go() is checked after visitIfdMakernote returns
TEST_F(TiffIfdMakernoteTest_345, AcceptVisitorChangesGoStateDuringVisit_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    MockTiffVisitor visitor;

    // When visitIfdMakernote is called, set geKnownMakernote to false
    EXPECT_CALL(visitor, visitIfdMakernote(&makernote))
        .WillOnce(::testing::Invoke([&visitor](TiffIfdMakernote*) {
            visitor.setGo(TiffVisitor::geKnownMakernote, false);
        }));

    // Since geKnownMakernote becomes false after visitIfdMakernote,
    // ifd_.accept should NOT be called, and visitIfdMakernoteEnd should NOT be called
    EXPECT_CALL(visitor, visitDirectory(_)).Times(0);
    EXPECT_CALL(visitor, visitIfdMakernoteEnd(_)).Times(0);

    makernote.accept(visitor);
}

// Test: accept when visitor changes geTraverse to false during ifd visit
TEST_F(TiffIfdMakernoteTest_345, AcceptVisitorChangesTraverseDuringIfdVisit_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visitIfdMakernote(&makernote)).Times(1);

    // During visitDirectory (ifd_.accept), set geTraverse to false
    EXPECT_CALL(visitor, visitDirectory(_))
        .WillOnce(::testing::Invoke([&visitor](TiffDirectory*) {
            visitor.setGo(TiffVisitor::geTraverse, false);
        }));

    // visitIfdMakernoteEnd requires both geKnownMakernote AND geTraverse to be true
    // Since geTraverse is now false, visitIfdMakernoteEnd should NOT be called
    EXPECT_CALL(visitor, visitIfdMakernoteEnd(_)).Times(0);
    EXPECT_CALL(visitor, visitDirectoryNext(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(visitor, visitDirectoryEnd(_)).Times(::testing::AnyNumber());

    makernote.accept(visitor);
}

// Test: ifdOffset default
TEST_F(TiffIfdMakernoteTest_345, IfdOffsetDefault_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // ifdOffset is computed, but with no data it should have a deterministic value
    size_t offset = makernote.ifdOffset();
    // We just verify it doesn't crash and returns some value
    (void)offset;
    SUCCEED();
}

// Test: baseOffset default
TEST_F(TiffIfdMakernoteTest_345, BaseOffsetDefault_345) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t offset = makernote.baseOffset();
    (void)offset;
    SUCCEED();
}

// Test: Copy constructor is deleted
// This is a compile-time test - we verify the class is non-copyable
// by checking that TiffIfdMakernote is not copy constructible
TEST_F(TiffIfdMakernoteTest_345, NonCopyable_345) {
    EXPECT_FALSE(std::is_copy_constructible<TiffIfdMakernote>::value);
    EXPECT_FALSE(std::is_copy_assignable<TiffIfdMakernote>::value);
}

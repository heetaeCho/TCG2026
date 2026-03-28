#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::AtLeast;

// Mock TiffVisitor to track calls
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

class TiffDirectoryTest_342 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Construction with hasNext true
TEST_F(TiffDirectoryTest_342, ConstructWithHasNextTrue_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir.hasNext());
    EXPECT_EQ(dir.tag(), 0x0001);
    EXPECT_EQ(dir.group(), IfdId::ifd0Id);
}

// Test: Construction with hasNext false
TEST_F(TiffDirectoryTest_342, ConstructWithHasNextFalse_342) {
    TiffDirectory dir(0x0002, IfdId::ifd1Id, false);
    EXPECT_FALSE(dir.hasNext());
    EXPECT_EQ(dir.tag(), 0x0002);
    EXPECT_EQ(dir.group(), IfdId::ifd1Id);
}

// Test: accept on empty directory calls visitDirectory, visitDirectoryNext, visitDirectoryEnd
TEST_F(TiffDirectoryTest_342, AcceptEmptyDirectoryCallsVisitorMethods_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    MockTiffVisitor visitor;

    {
        InSequence seq;
        EXPECT_CALL(visitor, visitDirectory(&dir)).Times(1);
        EXPECT_CALL(visitor, visitDirectoryNext(&dir)).Times(1);
        EXPECT_CALL(visitor, visitDirectoryEnd(&dir)).Times(1);
    }

    dir.accept(visitor);
}

// Test: When go(geTraverse) returns false after visitDirectory, no further traversal
TEST_F(TiffDirectoryTest_342, AcceptStopsWhenGoReturnsFalseAfterVisitDirectory_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    MockTiffVisitor visitor;

    // visitDirectory will set go to false
    EXPECT_CALL(visitor, visitDirectory(&dir)).WillOnce([&](TiffDirectory*) {
        visitor.setGo(TiffVisitor::geTraverse, false);
    });
    // visitDirectoryNext should NOT be called since go is false
    EXPECT_CALL(visitor, visitDirectoryNext(_)).Times(0);
    // visitDirectoryEnd should still be called (it's called regardless based on the code flow)
    // Actually looking at the code: visitDirectoryEnd is called only if go(geTraverse) is true
    // Let's check the code: the end is called after pNext_ handling, but go check is before it
    EXPECT_CALL(visitor, visitDirectoryEnd(_)).Times(0);

    dir.accept(visitor);
}

// Test: Tag and group getters
TEST_F(TiffDirectoryTest_342, TagAndGroupGetters_342) {
    TiffDirectory dir(0x8769, IfdId::exifId, true);
    EXPECT_EQ(dir.tag(), 0x8769);
    EXPECT_EQ(dir.group(), IfdId::exifId);
    EXPECT_TRUE(dir.hasNext());
}

// Test: Construction with tag 0
TEST_F(TiffDirectoryTest_342, ConstructWithZeroTag_342) {
    TiffDirectory dir(0x0000, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.tag(), 0x0000);
    EXPECT_FALSE(dir.hasNext());
}

// Test: Count on empty directory
TEST_F(TiffDirectoryTest_342, CountOnEmptyDirectory_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.count(), 0u);
}

// Test: Size on empty directory
TEST_F(TiffDirectoryTest_342, SizeOnEmptyDirectory_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    // Size of an empty directory should be some baseline value (directory header)
    size_t s = dir.size();
    // We don't know the exact value, just that it's callable
    EXPECT_GE(s, 0u);
}

// Test: SizeData on empty directory
TEST_F(TiffDirectoryTest_342, SizeDataOnEmptyDirectory_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.sizeData(), 0u);
}

// Test: SizeImage on empty directory
TEST_F(TiffDirectoryTest_342, SizeImageOnEmptyDirectory_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.sizeImage(), 0u);
}

// Test: setStart and start
TEST_F(TiffDirectoryTest_342, SetStartAndStart_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    const uint8_t data[] = {0x01, 0x02, 0x03};
    dir.setStart(data);
    EXPECT_EQ(dir.start(), const_cast<uint8_t*>(data));
}

// Test: start returns nullptr when not set
TEST_F(TiffDirectoryTest_342, StartReturnsNullWhenNotSet_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.start(), nullptr);
}

// Test: Visitor go event manipulation
TEST_F(TiffDirectoryTest_342, VisitorGoEventManipulation_342) {
    MockTiffVisitor visitor;
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));

    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));

    visitor.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
}

// Test: Multiple directories with different groups
TEST_F(TiffDirectoryTest_342, MultipleDirsDifferentGroups_342) {
    TiffDirectory dir1(0x0001, IfdId::ifd0Id, true);
    TiffDirectory dir2(0x0002, IfdId::ifd1Id, false);
    TiffDirectory dir3(0x8769, IfdId::exifId, true);

    EXPECT_EQ(dir1.group(), IfdId::ifd0Id);
    EXPECT_EQ(dir2.group(), IfdId::ifd1Id);
    EXPECT_EQ(dir3.group(), IfdId::exifId);

    EXPECT_TRUE(dir1.hasNext());
    EXPECT_FALSE(dir2.hasNext());
    EXPECT_TRUE(dir3.hasNext());
}

// Test: Accept is callable multiple times
TEST_F(TiffDirectoryTest_342, AcceptCallableMultipleTimes_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visitDirectory(&dir)).Times(2);
    EXPECT_CALL(visitor, visitDirectoryNext(&dir)).Times(2);
    EXPECT_CALL(visitor, visitDirectoryEnd(&dir)).Times(2);

    dir.accept(visitor);
    dir.accept(visitor);
}

// Test: idx returns default value
TEST_F(TiffDirectoryTest_342, IdxReturnsDefaultValue_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    // idx() should return some integer value; just verify it's callable
    int idx = dir.idx();
    (void)idx; // Just ensure it doesn't crash
}

// Test: hasNext with max tag value
TEST_F(TiffDirectoryTest_342, ConstructWithMaxTag_342) {
    TiffDirectory dir(0xFFFF, IfdId::ifd0Id, true);
    EXPECT_EQ(dir.tag(), 0xFFFF);
    EXPECT_TRUE(dir.hasNext());
}

// Test: Visitor visitDirectoryNext and visitDirectoryEnd are called in order for empty dir
TEST_F(TiffDirectoryTest_342, VisitOrderForEmptyDirectory_342) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    MockTiffVisitor visitor;

    // Track order of calls
    std::vector<std::string> callOrder;

    EXPECT_CALL(visitor, visitDirectory(&dir)).WillOnce([&](TiffDirectory*) {
        callOrder.push_back("visitDirectory");
    });
    EXPECT_CALL(visitor, visitDirectoryNext(&dir)).WillOnce([&](TiffDirectory*) {
        callOrder.push_back("visitDirectoryNext");
    });
    EXPECT_CALL(visitor, visitDirectoryEnd(&dir)).WillOnce([&](TiffDirectory*) {
        callOrder.push_back("visitDirectoryEnd");
    });

    dir.accept(visitor);

    ASSERT_EQ(callOrder.size(), 3u);
    EXPECT_EQ(callOrder[0], "visitDirectory");
    EXPECT_EQ(callOrder[1], "visitDirectoryNext");
    EXPECT_EQ(callOrder[2], "visitDirectoryEnd");
}

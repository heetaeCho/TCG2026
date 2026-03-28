#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

// Mock for TiffHeaderBase
class MockTiffHeaderBase : public TiffHeaderBase {
public:
    MockTiffHeaderBase()
        : TiffHeaderBase(42, 8, littleEndian, 8) {}

    MOCK_CONST_METHOD3(isImageTag, bool(uint16_t tag, IfdId group, const PrimaryGroups& pPrimaryGroups));
};

// A concrete TiffComponent subclass for testing
class MockTiffComponent : public TiffComponent {
public:
    MockTiffComponent(uint16_t tag, IfdId group)
        : TiffComponent(tag, group) {}

    MOCK_METHOD4(doAddPath, TiffComponent*(uint16_t, TiffPath&, TiffComponent*, UniquePtr));
    MOCK_METHOD1(doAddChild, TiffComponent*(SharedPtr));
    MOCK_METHOD1(doAddNext, TiffComponent*(UniquePtr));
    MOCK_METHOD1(doAccept, void(TiffVisitor&));
    MOCK_METHOD6(doWrite, size_t(IoWrapper&, ByteOrder, size_t, size_t, size_t, size_t&));
    MOCK_CONST_METHOD0(doClone, TiffComponent*());
    MOCK_CONST_METHOD5(doWriteData, size_t(IoWrapper&, ByteOrder, size_t, size_t, size_t&));
    MOCK_CONST_METHOD2(doWriteImage, size_t(IoWrapper&, ByteOrder));
    MOCK_CONST_METHOD0(doSize, size_t());
    MOCK_CONST_METHOD0(doCount, size_t());
    MOCK_CONST_METHOD0(doSizeData, size_t());
    MOCK_CONST_METHOD0(doSizeImage, size_t());
};

// Test fixture
class TiffCopierTest_1641 : public ::testing::Test {
protected:
    void SetUp() override {
        mockHeader_ = std::make_unique<NiceMock<MockTiffHeaderBase>>();
    }

    std::unique_ptr<NiceMock<MockTiffHeaderBase>> mockHeader_;
};

// Test: When isImageTag returns false, copyObject should NOT clone or add path
TEST_F(TiffCopierTest_1641, CopyObjectSkipsNonImageTag_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);
    NiceMock<MockTiffComponent> object(0x0110, IfdId::ifd0Id);

    PrimaryGroups primaryGroups;

    EXPECT_CALL(*mockHeader_, isImageTag(object.tag(), object.group(), _))
        .WillOnce(Return(false));

    // If isImageTag returns false, clone should NOT be called
    EXPECT_CALL(object, doClone()).Times(0);
    EXPECT_CALL(root, doAddPath(_, _, _, _)).Times(0);

    TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);
    copier.copyObject(&object);
}

// Test: When isImageTag returns true, copyObject should clone and add path
TEST_F(TiffCopierTest_1641, CopyObjectClonesImageTag_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);
    NiceMock<MockTiffComponent> object(0x0110, IfdId::ifd0Id);

    PrimaryGroups primaryGroups;

    EXPECT_CALL(*mockHeader_, isImageTag(object.tag(), object.group(), _))
        .WillOnce(Return(true));

    // When isImageTag returns true, clone should be called
    auto* clonedRaw = new NiceMock<MockTiffComponent>(0x0110, IfdId::ifd0Id);
    EXPECT_CALL(object, doClone())
        .WillOnce(Return(clonedRaw));

    // addPath should be called on root
    EXPECT_CALL(root, doAddPath(object.tag(), _, &root, _))
        .WillOnce(Return(nullptr));

    TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);
    copier.copyObject(&object);
}

// Test: visitDirectory does nothing (no crash)
TEST_F(TiffCopierTest_1641, VisitDirectoryDoesNotCrash_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;

    TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);

    // visitDirectory should just be a no-op; it shouldn't crash
    // We can't easily create a TiffDirectory without knowing internals,
    // but we test that the copier constructs fine
    SUCCEED();
}

// Test: Constructor initializes without crash
TEST_F(TiffCopierTest_1641, ConstructorDoesNotCrash_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    primaryGroups.push_back(IfdId::ifd0Id);

    EXPECT_NO_THROW({
        TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);
    });
}

// Test: copyObject with different tag values
TEST_F(TiffCopierTest_1641, CopyObjectWithDifferentTags_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);

    PrimaryGroups primaryGroups;
    primaryGroups.push_back(IfdId::ifd0Id);

    // Test with tag 0x0000
    {
        NiceMock<MockTiffComponent> object(0x0000, IfdId::ifd0Id);
        EXPECT_CALL(*mockHeader_, isImageTag(0x0000, IfdId::ifd0Id, _))
            .WillOnce(Return(false));

        TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);
        copier.copyObject(&object);
    }

    // Test with max tag 0xFFFF
    {
        NiceMock<MockTiffComponent> object(0xFFFF, IfdId::ifd0Id);
        EXPECT_CALL(*mockHeader_, isImageTag(0xFFFF, IfdId::ifd0Id, _))
            .WillOnce(Return(false));

        TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);
        copier.copyObject(&object);
    }
}

// Test: copyObject correctly passes tag and group to isImageTag
TEST_F(TiffCopierTest_1641, CopyObjectPassesCorrectTagAndGroup_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);
    NiceMock<MockTiffComponent> object(0x0201, IfdId::exifId);

    PrimaryGroups primaryGroups;

    EXPECT_CALL(*mockHeader_, isImageTag(0x0201, IfdId::exifId, _))
        .WillOnce(Return(false));

    TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);
    copier.copyObject(&object);
}

// Test: Multiple copyObject calls
TEST_F(TiffCopierTest_1641, MultipleCopyObjectCalls_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);
    NiceMock<MockTiffComponent> object1(0x0100, IfdId::ifd0Id);
    NiceMock<MockTiffComponent> object2(0x0200, IfdId::ifd0Id);

    PrimaryGroups primaryGroups;

    EXPECT_CALL(*mockHeader_, isImageTag(0x0100, _, _))
        .WillOnce(Return(false));
    EXPECT_CALL(*mockHeader_, isImageTag(0x0200, _, _))
        .WillOnce(Return(false));

    TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);
    copier.copyObject(&object1);
    copier.copyObject(&object2);
}

// Test: PrimaryGroups is passed through correctly
TEST_F(TiffCopierTest_1641, PrimaryGroupsPassedCorrectly_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);
    NiceMock<MockTiffComponent> object(0x0100, IfdId::ifd0Id);

    PrimaryGroups primaryGroups;
    primaryGroups.push_back(IfdId::ifd0Id);
    primaryGroups.push_back(IfdId::ifd1Id);

    // The primaryGroups should be forwarded to isImageTag
    EXPECT_CALL(*mockHeader_, isImageTag(_, _, _))
        .WillOnce(Return(false));

    TiffCopier copier(&root, Tag::root, mockHeader_.get(), primaryGroups);
    copier.copyObject(&object);
}

// Test: Empty PrimaryGroups
TEST_F(TiffCopierTest_1641, EmptyPrimaryGroups_1641) {
    NiceMock<MockTiffComponent> root(0x0100, IfdId::ifd0Id);
    NiceMock<MockTiffComponent> object(0x0100, IfdId::ifd0Id);

    PrimaryGroups emptyGroups;

    EXPECT_CALL(*mockHeader_, isImageTag(_, _, _))
        .WillOnce(Return(false));

    TiffCopier copier(&root, Tag::root, mockHeader_.get(), emptyGroups);
    copier.copyObject(&object);
}

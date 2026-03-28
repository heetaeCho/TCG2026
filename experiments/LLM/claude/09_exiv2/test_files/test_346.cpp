#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::AtLeast;

// Mock TiffVisitor to observe calls
class MockTiffVisitor : public TiffVisitor {
public:
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

// A minimal ArrayCfg for constructing TiffBinaryArray
// We need valid configs to construct the object

class TiffBinaryArrayAcceptTest_346 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that doAccept calls visitBinaryArray and visitBinaryArrayEnd when no elements
TEST_F(TiffBinaryArrayAcceptTest_346, AcceptWithNoElements_CallsVisitBinaryArrayAndEnd_346) {
    // We need a valid ArrayCfg to construct TiffBinaryArray
    // Using a simple configuration
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,  // group
        invalidByteOrder,    // byte order
        ttUndefined,         // elTiffType
        notEncrypted,        // cryptFct
        false,               // hasSize
        false,               // hasFillers
        false                // concat
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    MockTiffVisitor mockVisitor;

    {
        InSequence seq;
        EXPECT_CALL(mockVisitor, visitBinaryArray(&binaryArray)).Times(1);
        EXPECT_CALL(mockVisitor, visitBinaryArrayEnd(&binaryArray)).Times(1);
    }

    binaryArray.accept(mockVisitor);
}

// Test that when visitor.go(geTraverse) is set to false, visitBinaryArrayEnd is NOT called
TEST_F(TiffBinaryArrayAcceptTest_346, AcceptWithGoFalse_DoesNotCallVisitBinaryArrayEnd_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitBinaryArray(&binaryArray))
        .WillOnce([&mockVisitor](TiffBinaryArray*) {
            mockVisitor.setGo(TiffVisitor::geTraverse, false);
        });

    EXPECT_CALL(mockVisitor, visitBinaryArrayEnd(_)).Times(0);

    binaryArray.accept(mockVisitor);
}

// Test basic properties after construction with ArrayCfg
TEST_F(TiffBinaryArrayAcceptTest_346, ConstructWithArrayCfg_HasCorrectTagAndGroup_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x1234, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    EXPECT_EQ(binaryArray.tag(), 0x1234);
    EXPECT_EQ(binaryArray.group(), IfdId::ifdIdNotSet);
}

// Test cfg() returns the ArrayCfg pointer
TEST_F(TiffBinaryArrayAcceptTest_346, CfgReturnsCorrectPointer_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    EXPECT_EQ(binaryArray.cfg(), &arrayCfg);
}

// Test def() and defSize() return correct values
TEST_F(TiffBinaryArrayAcceptTest_346, DefAndDefSizeReturnCorrectValues_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    static const ArrayDef arrayDef[] = {
        {0, ttUnsignedByte, 1}
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, arrayDef, 1);

    EXPECT_EQ(binaryArray.def(), arrayDef);
    EXPECT_EQ(binaryArray.defSize(), 1u);
}

// Test decoded() default value and setDecoded
TEST_F(TiffBinaryArrayAcceptTest_346, DecodedDefaultIsFalse_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    EXPECT_FALSE(binaryArray.decoded());
}

TEST_F(TiffBinaryArrayAcceptTest_346, SetDecodedTrue_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    binaryArray.setDecoded(true);
    EXPECT_TRUE(binaryArray.decoded());
}

TEST_F(TiffBinaryArrayAcceptTest_346, SetDecodedFalseAfterTrue_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    binaryArray.setDecoded(true);
    EXPECT_TRUE(binaryArray.decoded());
    binaryArray.setDecoded(false);
    EXPECT_FALSE(binaryArray.decoded());
}

// Test construction with ArraySet and CfgSelFct
TEST_F(TiffBinaryArrayAcceptTest_346, ConstructWithArraySet_HasCorrectTagAndGroup_346) {
    TiffBinaryArray binaryArray(0x5678, IfdId::ifdIdNotSet, nullptr, 0, nullptr);

    EXPECT_EQ(binaryArray.tag(), 0x5678);
    EXPECT_EQ(binaryArray.group(), IfdId::ifdIdNotSet);
}

// Test that cfg() returns nullptr when constructed with ArraySet constructor
TEST_F(TiffBinaryArrayAcceptTest_346, CfgReturnsNullptrForArraySetConstructor_346) {
    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, nullptr, 0, nullptr);

    EXPECT_EQ(binaryArray.cfg(), nullptr);
}

// Test def() returns nullptr when constructed without ArrayDef
TEST_F(TiffBinaryArrayAcceptTest_346, DefReturnsNullptrWhenNotProvided_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    EXPECT_EQ(binaryArray.def(), nullptr);
    EXPECT_EQ(binaryArray.defSize(), 0u);
}

// Test iniOrigDataBuf - just ensure it doesn't crash with empty state
TEST_F(TiffBinaryArrayAcceptTest_346, IniOrigDataBuf_DoesNotCrash_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    EXPECT_NO_THROW(binaryArray.iniOrigDataBuf());
}

// Test accept is called properly (public interface delegates to doAccept)
TEST_F(TiffBinaryArrayAcceptTest_346, AcceptDelegatesToDoAccept_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitBinaryArray(&binaryArray)).Times(1);
    EXPECT_CALL(mockVisitor, visitBinaryArrayEnd(&binaryArray)).Times(1);

    binaryArray.accept(mockVisitor);
}

// Test that initialize with nullptr pRoot doesn't crash
TEST_F(TiffBinaryArrayAcceptTest_346, InitializeWithNullRoot_346) {
    static const ArrayCfg arrayCfg = {
        IfdId::ifdIdNotSet,
        invalidByteOrder,
        ttUndefined,
        notEncrypted,
        false,
        false,
        false
    };

    TiffBinaryArray binaryArray(0x0001, IfdId::ifdIdNotSet, arrayCfg, nullptr, 0);

    bool result = binaryArray.initialize(static_cast<TiffComponent*>(nullptr));
    // Just check it returns without crashing; result depends on implementation
    (void)result;
}

// Test TiffVisitor go/setGo mechanism
TEST_F(TiffBinaryArrayAcceptTest_346, VisitorGoDefaultIsTrue_346) {
    MockTiffVisitor visitor;
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));
}

TEST_F(TiffBinaryArrayAcceptTest_346, VisitorSetGoFalse_346) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    // Other events should remain unchanged
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));
}

TEST_F(TiffBinaryArrayAcceptTest_346, VisitorSetGoTrueAfterFalse_346) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    visitor.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
}

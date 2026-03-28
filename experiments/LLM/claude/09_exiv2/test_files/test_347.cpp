#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the project
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

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

class TiffBinaryElementTest_347 : public ::testing::Test {
protected:
    void SetUp() override {
        // TiffBinaryElement requires a tag and group for TiffEntryBase construction
        // Using tag 0x0001 and group 0 as defaults
    }
};

// Test that doAccept calls visitBinaryElement on the visitor with the correct object
TEST_F(TiffBinaryElementTest_347, DoAcceptCallsVisitBinaryElement_347) {
    // Create a TiffBinaryElement - using tag 0x0001, ifdId ifdIdNotSet (or similar)
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitBinaryElement(&element)).Times(1);

    element.accept(mockVisitor);
}

// Test that visitBinaryElement receives the correct pointer
TEST_F(TiffBinaryElementTest_347, DoAcceptPassesCorrectPointer_347) {
    TiffBinaryElement element(0x0002, IfdId::ifdIdNotSet);
    MockTiffVisitor mockVisitor;

    TiffBinaryElement* capturedPtr = nullptr;
    EXPECT_CALL(mockVisitor, visitBinaryElement(::testing::_))
        .WillOnce(::testing::SaveArg<0>(&capturedPtr));

    element.accept(mockVisitor);
    EXPECT_EQ(capturedPtr, &element);
}

// Test setElDef and elDef - normal operation
TEST_F(TiffBinaryElementTest_347, SetAndGetElDef_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    ArrayDef def = {0, ttUnsignedShort, 2};
    element.setElDef(def);

    const ArrayDef* result = element.elDef();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type_, ttUnsignedShort);
    EXPECT_EQ(result->count_, 2u);
}

// Test setElByteOrder and elByteOrder - normal operation
TEST_F(TiffBinaryElementTest_347, SetAndGetElByteOrder_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    element.setElByteOrder(bigEndian);

    EXPECT_EQ(element.elByteOrder(), bigEndian);
}

// Test elByteOrder default value is invalidByteOrder
TEST_F(TiffBinaryElementTest_347, DefaultElByteOrderIsInvalid_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);
}

// Test setting elByteOrder to littleEndian
TEST_F(TiffBinaryElementTest_347, SetElByteOrderLittleEndian_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    element.setElByteOrder(littleEndian);

    EXPECT_EQ(element.elByteOrder(), littleEndian);
}

// Test setting elByteOrder to invalidByteOrder explicitly
TEST_F(TiffBinaryElementTest_347, SetElByteOrderInvalid_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);

    element.setElByteOrder(invalidByteOrder);
    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);
}

// Test that accept does not call other visit methods
TEST_F(TiffBinaryElementTest_347, DoAcceptDoesNotCallOtherVisitMethods_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitBinaryElement(::testing::_)).Times(1);
    EXPECT_CALL(mockVisitor, visitEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitDataEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitImageEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitSizeEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitDirectory(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitSubIfd(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitMnEntry(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitIfdMakernote(::testing::_)).Times(0);
    EXPECT_CALL(mockVisitor, visitBinaryArray(::testing::_)).Times(0);

    element.accept(mockVisitor);
}

// Test setElDef with zero-initialized ArrayDef
TEST_F(TiffBinaryElementTest_347, SetElDefWithZeroValues_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    ArrayDef def = {0, ttUndefined, 0};
    element.setElDef(def);

    const ArrayDef* result = element.elDef();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type_, ttUndefined);
    EXPECT_EQ(result->count_, 0u);
}

// Test multiple calls to setElByteOrder - last one wins
TEST_F(TiffBinaryElementTest_347, MultipleSetElByteOrder_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    
    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);
    
    element.setElByteOrder(littleEndian);
    EXPECT_EQ(element.elByteOrder(), littleEndian);
    
    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);
}

// Test multiple calls to setElDef - last one wins
TEST_F(TiffBinaryElementTest_347, MultipleSetElDef_347) {
    TiffBinaryElement element(0x0001, IfdId::ifdIdNotSet);
    
    ArrayDef def1 = {0, ttUnsignedByte, 1};
    element.setElDef(def1);
    EXPECT_EQ(element.elDef()->type_, ttUnsignedByte);
    
    ArrayDef def2 = {0, ttUnsignedShort, 2};
    element.setElDef(def2);
    EXPECT_EQ(element.elDef()->type_, ttUnsignedShort);
}

// Test creating elements with different tags
TEST_F(TiffBinaryElementTest_347, DifferentTagElements_347) {
    TiffBinaryElement element1(0x0001, IfdId::ifdIdNotSet);
    TiffBinaryElement element2(0x0002, IfdId::ifdIdNotSet);
    
    MockTiffVisitor mockVisitor;
    
    EXPECT_CALL(mockVisitor, visitBinaryElement(&element1)).Times(1);
    EXPECT_CALL(mockVisitor, visitBinaryElement(&element2)).Times(1);
    
    element1.accept(mockVisitor);
    element2.accept(mockVisitor);
}

}  // namespace Internal
}  // namespace Exiv2

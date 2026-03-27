#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

// Mock class for TiffVisitor
class MockTiffVisitor : public Exiv2::Internal::TiffVisitor {
public:
    MOCK_METHOD(void, visitBinaryElement, (Exiv2::Internal::TiffBinaryElement* object), (override));
};

// Unit test for TiffBinaryElement::doAccept method
TEST_F(TiffBinaryElementTest_347, DoAcceptCallsVisitBinaryElement_347) {
    // Arrange
    Exiv2::Internal::TiffBinaryElement element;
    MockTiffVisitor mockVisitor;

    // Expect the visitBinaryElement method to be called with the element
    EXPECT_CALL(mockVisitor, visitBinaryElement(&element)).Times(1);

    // Act
    element.doAccept(mockVisitor);  // This should call visitBinaryElement on the visitor

    // Assert: The expectation set above will verify if the method was called
}

// Unit test for TiffBinaryElement::setElDef and elDef method
TEST_F(TiffBinaryElementTest_348, SetElDefSetsArrayDef_348) {
    // Arrange
    Exiv2::Internal::TiffBinaryElement element;
    Exiv2::Internal::ArrayDef def = {5, Exiv2::Internal::ttByte, 10};

    // Act
    element.setElDef(def);

    // Assert
    const Exiv2::Internal::ArrayDef* result = element.elDef();
    ASSERT_EQ(result->count, 5);
    ASSERT_EQ(result->type, Exiv2::Internal::ttByte);
    ASSERT_EQ(result->size, 10);
}

// Unit test for TiffBinaryElement::setElByteOrder and elByteOrder method
TEST_F(TiffBinaryElementTest_349, SetElByteOrderSetsByteOrder_349) {
    // Arrange
    Exiv2::Internal::TiffBinaryElement element;
    Exiv2::Internal::ByteOrder byteOrder = Exiv2::Internal::bigEndian;

    // Act
    element.setElByteOrder(byteOrder);

    // Assert
    ASSERT_EQ(element.elByteOrder(), byteOrder);
}

// Unit test for TiffBinaryElement::doClone method
TEST_F(TiffBinaryElementTest_350, DoCloneCreatesCopy_350) {
    // Arrange
    Exiv2::Internal::TiffBinaryElement element;
    element.setElDef({5, Exiv2::Internal::ttByte, 10});
    element.setElByteOrder(Exiv2::Internal::bigEndian);

    // Act
    const Exiv2::Internal::TiffBinaryElement* clone = element.doClone();

    // Assert
    ASSERT_NE(clone, &element);  // Assert that the clone is a different object
    ASSERT_EQ(clone->elDef()->count, 5);
    ASSERT_EQ(clone->elDef()->type, Exiv2::Internal::ttByte);
    ASSERT_EQ(clone->elDef()->size, 10);
    ASSERT_EQ(clone->elByteOrder(), Exiv2::Internal::bigEndian);
}

// Unit test for TiffBinaryElement::doSize method
TEST_F(TiffBinaryElementTest_351, DoSizeReturnsCorrectSize_351) {
    // Arrange
    Exiv2::Internal::TiffBinaryElement element;
    element.setElDef({5, Exiv2::Internal::ttByte, 10});

    // Act
    size_t size = element.doSize();

    // Assert
    ASSERT_EQ(size, 50);  // 5 * 10 = 50
}

// Unit test for TiffBinaryElement::doWrite method (boundary condition)
TEST_F(TiffBinaryElementTest_352, DoWriteHandlesLargeOffsets_352) {
    // Arrange
    Exiv2::Internal::TiffBinaryElement element;
    element.setElDef({10, Exiv2::Internal::ttByte, 100});
    Exiv2::Internal::IoWrapper ioWrapper;
    size_t offset = 0xFFFFFFFF;  // Boundary value
    size_t valueIdx = 0;
    size_t dataIdx = 0;
    size_t imageIdx = 0;

    // Act
    size_t written = element.doWrite(ioWrapper, Exiv2::Internal::bigEndian, offset, valueIdx, dataIdx, imageIdx);

    // Assert
    ASSERT_GT(written, 0);  // Assert some data was written
}

// Unit test for exceptional case (invalid byte order)
TEST_F(TiffBinaryElementTest_353, SetInvalidByteOrderThrowsException_353) {
    // Arrange
    Exiv2::Internal::TiffBinaryElement element;
    Exiv2::Internal::ByteOrder invalidByteOrder = Exiv2::Internal::invalidByteOrder;

    // Act & Assert
    ASSERT_THROW(element.setElByteOrder(invalidByteOrder), std::invalid_argument);
}
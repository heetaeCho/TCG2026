#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp" // Assuming the path is correctly linked.

namespace Exiv2 { namespace Internal {

// Mock classes for external collaborators, as per constraints
class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visit, (const TiffBinaryElement& element), (override));
};

class MockTiffEncoder : public TiffEncoder {
public:
    MOCK_METHOD(void, encode, (const TiffBinaryElement& element, const Exifdatum* datum), (override));
};

class MockIoWrapper : public IoWrapper {
public:
    MOCK_METHOD(size_t, write, (ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t& imageIdx), (override));
};

TEST_F(TiffBinaryElementTest_363, DoCountReturnsCorrectCount_363) {
    // Arrange
    ArrayDef def = {1, 10}; // Example: Array with count 10.
    TiffBinaryElement element;
    element.setElDef(def);

    // Act
    size_t count = element.doCount();

    // Assert
    EXPECT_EQ(count, 10);  // Verifying that count matches the expected value.
}

TEST_F(TiffBinaryElementTest_364, DoCountHandlesZeroCount_364) {
    // Arrange
    ArrayDef def = {1, 0}; // Example: Array with count 0.
    TiffBinaryElement element;
    element.setElDef(def);

    // Act
    size_t count = element.doCount();

    // Assert
    EXPECT_EQ(count, 0);  // Verifying that count is zero.
}

TEST_F(TiffBinaryElementTest_365, SetElDefUpdatesElementDefinition_365) {
    // Arrange
    ArrayDef def = {5, 20}; // Example definition with index 5 and count 20.
    TiffBinaryElement element;

    // Act
    element.setElDef(def);

    // Assert
    EXPECT_EQ(element.elDef()->count_, 20); // Verify that the count is updated.
    EXPECT_EQ(element.elDef()->idx_, 5);    // Verify that the index is updated.
}

TEST_F(TiffBinaryElementTest_366, DoAcceptCallsVisitor_366) {
    // Arrange
    MockTiffVisitor visitor;
    TiffBinaryElement element;

    // Act
    EXPECT_CALL(visitor, visit(testing::_)); // Expect the visit function to be called.
    element.doAccept(visitor);

    // Assert
    // No need for further asserts, the call expectation ensures correct interaction.
}

TEST_F(TiffBinaryElementTest_367, DoEncodeCallsEncoder_367) {
    // Arrange
    MockTiffEncoder encoder;
    Exifdatum datum;
    TiffBinaryElement element;

    // Act
    EXPECT_CALL(encoder, encode(testing::_, testing::_));  // Expect encode to be called.
    element.doEncode(encoder, &datum);

    // Assert
    // No further asserts, the call expectation ensures interaction is correct.
}

TEST_F(TiffBinaryElementTest_368, DoWriteReturnsCorrectSize_368) {
    // Arrange
    MockIoWrapper ioWrapper;
    TiffBinaryElement element;
    size_t offset = 0, valueIdx = 0, dataIdx = 0, imageIdx = 0;

    // Act
    EXPECT_CALL(ioWrapper, write(testing::_, testing::_, testing::_, testing::_, testing::_)).WillOnce(testing::Return(100)); // Simulating the return value as 100.
    size_t result = element.doWrite(ioWrapper, ByteOrder::bigEndian, offset, valueIdx, dataIdx, imageIdx);

    // Assert
    EXPECT_EQ(result, 100); // Verifying that the result matches the expected value.
}

TEST_F(TiffBinaryElementTest_369, DoSizeReturnsCorrectSize_369) {
    // Arrange
    TiffBinaryElement element;

    // Act
    size_t size = element.doSize();

    // Assert
    EXPECT_GT(size, 0);  // Assert that the size is greater than 0 (non-zero).
}

} } // namespace Exiv2::Internal
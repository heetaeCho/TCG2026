#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffReaderVisitBinaryElementTest_1709 : public ::testing::Test {
protected:
    // Helper to create a TiffReader with given data and byte order
    std::unique_ptr<TiffReader> createReader(const byte* pData, size_t size, TiffComponent* pRoot, ByteOrder bo) {
        TiffRwState state(bo, 0);
        return std::make_unique<TiffReader>(pData, size, pRoot, state);
    }
};

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitBinaryElementSetsValueAndOffset_1709) {
    // Create some test data
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    
    // Create a TiffBinaryElement
    TiffBinaryElement element(0x0001, IfdId::ifd0Id, ttUndefined);
    element.setStart(data);
    
    // Set data so doSize() returns something meaningful
    element.setData(data, sizeof(data), std::make_shared<DataBuf>(data, sizeof(data)));
    
    // Set the element definition
    ArrayDef def = {0, ttUndefined, 4};
    element.setElDef(def);
    
    // Create a root component and reader
    TiffDirectory root(0, IfdId::ifd0Id);
    auto reader = createReader(data, sizeof(data), &root, littleEndian);
    
    // Visit the element
    reader->visitBinaryElement(&element);
    
    // After visiting, the element should have a value set
    EXPECT_NE(nullptr, element.pValue());
    // Offset should be set to 0
    EXPECT_EQ(0u, element.offset());
}

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitBinaryElementWithBigEndian_1709) {
    byte data[] = {0x00, 0x0A};
    
    TiffBinaryElement element(0x0001, IfdId::ifd0Id, ttUnsignedShort);
    element.setStart(data);
    element.setData(data, sizeof(data), std::make_shared<DataBuf>(data, sizeof(data)));
    
    ArrayDef def = {0, ttUnsignedShort, 1};
    element.setElDef(def);
    
    TiffDirectory root(0, IfdId::ifd0Id);
    auto reader = createReader(data, sizeof(data), &root, bigEndian);
    
    reader->visitBinaryElement(&element);
    
    ASSERT_NE(nullptr, element.pValue());
    EXPECT_EQ(0u, element.offset());
}

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitBinaryElementWithLittleEndian_1709) {
    byte data[] = {0x0A, 0x00};
    
    TiffBinaryElement element(0x0001, IfdId::ifd0Id, ttUnsignedShort);
    element.setStart(data);
    element.setData(data, sizeof(data), std::make_shared<DataBuf>(data, sizeof(data)));
    
    ArrayDef def = {0, ttUnsignedShort, 1};
    element.setElDef(def);
    
    TiffDirectory root(0, IfdId::ifd0Id);
    auto reader = createReader(data, sizeof(data), &root, littleEndian);
    
    reader->visitBinaryElement(&element);
    
    ASSERT_NE(nullptr, element.pValue());
    EXPECT_EQ(0u, element.offset());
}

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitBinaryElementFallsBackToReaderByteOrder_1709) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    
    TiffBinaryElement element(0x0001, IfdId::ifd0Id, ttUnsignedLong);
    element.setStart(data);
    element.setData(data, sizeof(data), std::make_shared<DataBuf>(data, sizeof(data)));
    
    // Don't set element byte order - should remain invalidByteOrder
    // so the reader's byte order should be used
    ArrayDef def = {0, ttUnsignedLong, 1};
    element.setElDef(def);
    
    TiffDirectory root(0, IfdId::ifd0Id);
    auto reader = createReader(data, sizeof(data), &root, littleEndian);
    
    reader->visitBinaryElement(&element);
    
    ASSERT_NE(nullptr, element.pValue());
    EXPECT_EQ(0u, element.offset());
}

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitBinaryElementWithExplicitByteOrder_1709) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    
    TiffBinaryElement element(0x0001, IfdId::ifd0Id, ttUnsignedLong);
    element.setStart(data);
    element.setData(data, sizeof(data), std::make_shared<DataBuf>(data, sizeof(data)));
    
    // Set explicit element byte order
    element.setElByteOrder(bigEndian);
    
    ArrayDef def = {0, ttUnsignedLong, 1};
    element.setElDef(def);
    
    TiffDirectory root(0, IfdId::ifd0Id);
    // Reader uses littleEndian but element specifies bigEndian
    auto reader = createReader(data, sizeof(data), &root, littleEndian);
    
    reader->visitBinaryElement(&element);
    
    ASSERT_NE(nullptr, element.pValue());
    EXPECT_EQ(0u, element.offset());
}

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitBinaryElementSingleByte_1709) {
    byte data[] = {0xFF};
    
    TiffBinaryElement element(0x0001, IfdId::ifd0Id, ttUnsignedByte);
    element.setStart(data);
    element.setData(data, sizeof(data), std::make_shared<DataBuf>(data, sizeof(data)));
    
    ArrayDef def = {0, ttUnsignedByte, 1};
    element.setElDef(def);
    
    TiffDirectory root(0, IfdId::ifd0Id);
    auto reader = createReader(data, sizeof(data), &root, littleEndian);
    
    reader->visitBinaryElement(&element);
    
    ASSERT_NE(nullptr, element.pValue());
    EXPECT_EQ(0u, element.offset());
}

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitMultipleBinaryElementsIncrementsIdx_1709) {
    byte data1[] = {0x01};
    byte data2[] = {0x02};
    
    TiffBinaryElement element1(0x0001, IfdId::ifd0Id, ttUnsignedByte);
    element1.setStart(data1);
    element1.setData(data1, sizeof(data1), std::make_shared<DataBuf>(data1, sizeof(data1)));
    ArrayDef def1 = {0, ttUnsignedByte, 1};
    element1.setElDef(def1);
    
    TiffBinaryElement element2(0x0002, IfdId::ifd0Id, ttUnsignedByte);
    element2.setStart(data2);
    element2.setData(data2, sizeof(data2), std::make_shared<DataBuf>(data2, sizeof(data2)));
    ArrayDef def2 = {0, ttUnsignedByte, 1};
    element2.setElDef(def2);
    
    TiffDirectory root(0, IfdId::ifd0Id);
    auto reader = createReader(data1, sizeof(data1), &root, littleEndian);
    
    reader->visitBinaryElement(&element1);
    reader->visitBinaryElement(&element2);
    
    // The idx values should be different (incrementing)
    EXPECT_NE(element1.idx(), element2.idx());
}

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitBinaryElementUndefinedType_1709) {
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    
    TiffBinaryElement element(0x0001, IfdId::ifd0Id, ttUndefined);
    element.setStart(data);
    element.setData(data, sizeof(data), std::make_shared<DataBuf>(data, sizeof(data)));
    
    ArrayDef def = {0, ttUndefined, 5};
    element.setElDef(def);
    
    TiffDirectory root(0, IfdId::ifd0Id);
    auto reader = createReader(data, sizeof(data), &root, littleEndian);
    
    reader->visitBinaryElement(&element);
    
    ASSERT_NE(nullptr, element.pValue());
    EXPECT_EQ(0u, element.offset());
}

TEST_F(TiffReaderVisitBinaryElementTest_1709, VisitBinaryElementSignedShort_1709) {
    byte data[] = {0xFF, 0x7F}; // 32767 in little-endian
    
    TiffBinaryElement element(0x0001, IfdId::ifd0Id, ttSignedShort);
    element.setStart(data);
    element.setData(data, sizeof(data), std::make_shared<DataBuf>(data, sizeof(data)));
    
    ArrayDef def = {0, ttSignedShort, 1};
    element.setElDef(def);
    
    TiffDirectory root(0, IfdId::ifd0Id);
    auto reader = createReader(data, sizeof(data), &root, littleEndian);
    
    reader->visitBinaryElement(&element);
    
    ASSERT_NE(nullptr, element.pValue());
    EXPECT_EQ(0u, element.offset());
}

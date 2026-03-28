#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "value.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffSizeEntry tests
class TiffSizeEntryTest_1699 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test fixture for TiffFinder tests
class TiffFinderTest_1699 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test fixture for TiffReader tests
class TiffReaderTest_1699 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test TiffSizeEntry construction and accessors
TEST_F(TiffSizeEntryTest_1699, ConstructorSetsTagAndGroup_1699) {
    TiffSizeEntry entry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0117);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

TEST_F(TiffSizeEntryTest_1699, ConstructorSetsDtTagAndDtGroup_1699) {
    TiffSizeEntry entry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd1Id);
    EXPECT_EQ(entry.dtTag(), 0x0111);
    EXPECT_EQ(entry.dtGroup(), IfdId::ifd1Id);
}

TEST_F(TiffSizeEntryTest_1699, DifferentTagValues_1699) {
    TiffSizeEntry entry(0x0201, IfdId::ifd1Id, 0x0202, IfdId::ifd1Id);
    EXPECT_EQ(entry.tag(), 0x0201);
    EXPECT_EQ(entry.group(), IfdId::ifd1Id);
    EXPECT_EQ(entry.dtTag(), 0x0202);
    EXPECT_EQ(entry.dtGroup(), IfdId::ifd1Id);
}

// Test TiffFinder initialization and result
TEST_F(TiffFinderTest_1699, InitialResultIsNull_1699) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);
    EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1699, InitResetsState_1699) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);
    finder.init(0x0202, IfdId::ifd1Id);
    EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1699, FindObjectMatchingComponent_1699) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);
    TiffEntry entry(0x0111, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), &entry);
}

TEST_F(TiffFinderTest_1699, FindObjectNonMatchingComponent_1699) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);
    TiffEntry entry(0x0112, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1699, FindObjectDifferentGroup_1699) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);
    TiffEntry entry(0x0111, IfdId::ifd1Id);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test TiffDataEntryBase construction and accessors
class TiffDataEntryBaseTest_1699 : public ::testing::Test {
};

TEST_F(TiffDataEntryBaseTest_1699, ConstructorSetsSzTagAndSzGroup_1699) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    EXPECT_EQ(entry.szTag(), 0x0117);
    EXPECT_EQ(entry.szGroup(), IfdId::ifd0Id);
}

// Test TiffReader construction
TEST_F(TiffReaderTest_1699, ConstructorInitialization_1699) {
    byte data[12] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

TEST_F(TiffReaderTest_1699, ByteOrderBigEndian_1699) {
    byte data[12] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

TEST_F(TiffReaderTest_1699, BaseOffsetNonZero_1699) {
    byte data[12] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 8);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_EQ(reader.baseOffset(), 8u);
}

TEST_F(TiffReaderTest_1699, CircularReferenceFirstVisit_1699) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    EXPECT_FALSE(reader.circularReference(data + 10, IfdId::ifd0Id));
}

TEST_F(TiffReaderTest_1699, CircularReferenceSecondVisitSameAddress_1699) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    reader.circularReference(data + 10, IfdId::ifd0Id);
    EXPECT_TRUE(reader.circularReference(data + 10, IfdId::ifd0Id));
}

TEST_F(TiffReaderTest_1699, NextIdxIncrementsPerGroup_1699) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    int idx1 = reader.nextIdx(IfdId::ifd0Id);
    int idx2 = reader.nextIdx(IfdId::ifd0Id);
    EXPECT_EQ(idx2, idx1 + 1);
}

TEST_F(TiffReaderTest_1699, NextIdxDifferentGroupsIndependent_1699) {
    byte data[64] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    int idx_g0 = reader.nextIdx(IfdId::ifd0Id);
    int idx_g1 = reader.nextIdx(IfdId::ifd1Id);
    EXPECT_EQ(idx_g0, idx_g1);
}

TEST_F(TiffReaderTest_1699, SetOrigStateRestoresByteOrder_1699) {
    byte data[12] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    
    TiffRwState mnState(littleEndian, 0);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    
    reader.setOrigState();
    EXPECT_EQ(reader.byteOrder(), bigEndian);
}

TEST_F(TiffReaderTest_1699, SetMnStateChangesByteOrder_1699) {
    byte data[12] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(bigEndian, 0);
    TiffReader reader(data, sizeof(data), &root, state);
    
    TiffRwState mnState(littleEndian, 4);
    reader.setMnState(&mnState);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
}

// Test TiffEntryBase accessors
class TiffEntryBaseTest_1699 : public ::testing::Test {
};

TEST_F(TiffEntryBaseTest_1699, InitialPValueIsNull_1699) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest_1699, InitialPDataIsNull_1699) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(entry.pData(), nullptr);
}

TEST_F(TiffEntryBaseTest_1699, SetValueUpdatesValue_1699) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    auto value = Value::create(unsignedLong);
    value->read("42");
    entry.setValue(std::move(value));
    EXPECT_NE(entry.pValue(), nullptr);
}

// Test that TiffSizeEntry inherits from TiffEntryBase properly
TEST_F(TiffSizeEntryTest_1699, InheritsFromTiffEntryBase_1699) {
    TiffSizeEntry entry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    TiffEntryBase* base = &entry;
    EXPECT_EQ(base->tag(), 0x0117);
    EXPECT_EQ(base->group(), IfdId::ifd0Id);
}

TEST_F(TiffSizeEntryTest_1699, InitialPValueIsNull_1699) {
    TiffSizeEntry entry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test boundary: zero-size data for TiffReader
TEST_F(TiffReaderTest_1699, ZeroSizeData_1699) {
    byte data[1] = {0};
    TiffDirectory root(0, IfdId::ifd0Id);
    TiffRwState state(littleEndian, 0);
    TiffReader reader(data, 0, &root, state);
    EXPECT_EQ(reader.byteOrder(), littleEndian);
    EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test that TiffFinder can visit a SizeEntry
TEST_F(TiffFinderTest_1699, VisitSizeEntryMatching_1699) {
    TiffFinder finder(0x0117, IfdId::ifd0Id);
    TiffSizeEntry sizeEntry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    finder.visitSizeEntry(&sizeEntry);
    EXPECT_EQ(finder.result(), &sizeEntry);
}

TEST_F(TiffFinderTest_1699, VisitSizeEntryNonMatching_1699) {
    TiffFinder finder(0x0118, IfdId::ifd0Id);
    TiffSizeEntry sizeEntry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    finder.visitSizeEntry(&sizeEntry);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test TiffFinder visiting a DataEntry
TEST_F(TiffFinderTest_1699, VisitDataEntryMatching_1699) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);
    TiffDataEntry dataEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    finder.visitDataEntry(&dataEntry);
    EXPECT_EQ(finder.result(), &dataEntry);
}

TEST_F(TiffFinderTest_1699, VisitDataEntryNonMatching_1699) {
    TiffFinder finder(0x0112, IfdId::ifd0Id);
    TiffDataEntry dataEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    finder.visitDataEntry(&dataEntry);
    EXPECT_EQ(finder.result(), nullptr);
}

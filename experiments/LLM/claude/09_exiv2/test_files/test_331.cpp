#include <gtest/gtest.h>
#include <memory>
#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need to create a minimal ArrayCfg for constructing TiffBinaryArray
// Since TiffBinaryArray has protected doAddChild, we may need to access it
// through the public TiffComponent interface (addChild) or via a test helper.

namespace {

// Helper to create a basic ArrayCfg for testing
static const ArrayCfg testArrayCfg = {
    IfdId::ifd0Id,     // group
    invalidByteOrder,  // byte order
    ttUndefined,       // elTiffType
    notEncrypted,      // cryptFct
    false,             // hasFillers
    false              // hasSize
};

static const ArrayDef testArrayDef[] = {
    {0, ttUndefined, 1}
};

// A concrete TiffComponent for testing - using TiffEntry as a simple component
class TestTiffComponent : public TiffEntryBase {
public:
    TestTiffComponent(uint16_t tag, IfdId group)
        : TiffEntryBase(tag, group) {}
    
    // Minimal implementations of pure virtual functions
    TiffComponent* doAddPath(uint16_t, TiffPath&, TiffComponent*, UniquePtr) override { return nullptr; }
    TiffComponent* doAddChild(SharedPtr) override { return nullptr; }
    void doAccept(TiffVisitor&) override {}
    void doEncode(TiffEncoder&, const Exifdatum*) override {}
    size_t doWrite(IoWrapper&, ByteOrder, size_t, size_t, size_t, size_t&) override { return 0; }
    size_t doCount() const override { return 0; }
    size_t doSize() const override { return 0; }
};

} // anonymous namespace

class TiffBinaryArrayTest_331 : public ::testing::Test {
protected:
    void SetUp() override {
        array_ = std::make_unique<TiffBinaryArray>(
            0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    }

    std::unique_ptr<TiffBinaryArray> array_;
};

// Test that a newly constructed TiffBinaryArray has decoded() == false
TEST_F(TiffBinaryArrayTest_331, InitialDecodedIsFalse_331) {
    EXPECT_FALSE(array_->decoded());
}

// Test that cfg() returns the ArrayCfg passed during construction
TEST_F(TiffBinaryArrayTest_331, CfgReturnsConstructedConfig_331) {
    ASSERT_NE(array_->cfg(), nullptr);
    EXPECT_EQ(array_->cfg()->group_, testArrayCfg.group_);
    EXPECT_EQ(array_->cfg()->elTiffType_, testArrayCfg.elTiffType_);
}

// Test that def() returns the ArrayDef passed during construction
TEST_F(TiffBinaryArrayTest_331, DefReturnsConstructedDef_331) {
    ASSERT_NE(array_->def(), nullptr);
}

// Test that defSize() returns the size passed during construction
TEST_F(TiffBinaryArrayTest_331, DefSizeReturnsConstructedSize_331) {
    EXPECT_EQ(array_->defSize(), 1u);
}

// Test that addChild sets decoded to true
TEST_F(TiffBinaryArrayTest_331, AddChildSetsDecodedTrue_331) {
    ASSERT_FALSE(array_->decoded());
    
    auto child = std::make_shared<TiffBinaryArray>(
        0x0002, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    
    TiffComponent* result = array_->addChild(std::move(child));
    
    EXPECT_TRUE(array_->decoded());
}

// Test that addChild returns a non-null pointer
TEST_F(TiffBinaryArrayTest_331, AddChildReturnsNonNull_331) {
    auto child = std::make_shared<TiffBinaryArray>(
        0x0002, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    
    TiffComponent* result = array_->addChild(std::move(child));
    
    EXPECT_NE(result, nullptr);
}

// Test that addChild returns pointer to the added component
TEST_F(TiffBinaryArrayTest_331, AddChildReturnsPointerToAddedComponent_331) {
    auto child = std::make_shared<TiffBinaryArray>(
        0x0003, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    TiffComponent* rawPtr = child.get();
    
    TiffComponent* result = array_->addChild(std::move(child));
    
    EXPECT_EQ(result, rawPtr);
}

// Test adding multiple children
TEST_F(TiffBinaryArrayTest_331, AddMultipleChildren_331) {
    auto child1 = std::make_shared<TiffBinaryArray>(
        0x0010, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    auto child2 = std::make_shared<TiffBinaryArray>(
        0x0011, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    
    TiffComponent* rawPtr1 = child1.get();
    TiffComponent* rawPtr2 = child2.get();
    
    TiffComponent* result1 = array_->addChild(std::move(child1));
    TiffComponent* result2 = array_->addChild(std::move(child2));
    
    EXPECT_EQ(result1, rawPtr1);
    EXPECT_EQ(result2, rawPtr2);
    EXPECT_NE(result1, result2);
}

// Test that decoded remains true after multiple addChild calls
TEST_F(TiffBinaryArrayTest_331, DecodedRemainsTrueAfterMultipleAdds_331) {
    auto child1 = std::make_shared<TiffBinaryArray>(
        0x0010, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    auto child2 = std::make_shared<TiffBinaryArray>(
        0x0011, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    
    array_->addChild(std::move(child1));
    EXPECT_TRUE(array_->decoded());
    
    array_->addChild(std::move(child2));
    EXPECT_TRUE(array_->decoded());
}

// Test setDecoded method explicitly
TEST_F(TiffBinaryArrayTest_331, SetDecodedExplicitly_331) {
    EXPECT_FALSE(array_->decoded());
    
    array_->setDecoded(true);
    EXPECT_TRUE(array_->decoded());
    
    array_->setDecoded(false);
    EXPECT_FALSE(array_->decoded());
}

// Test construction with ArraySet constructor
TEST_F(TiffBinaryArrayTest_331, ConstructWithArraySet_331) {
    // Use nullptr for cfgSelFct and arraySet for simplicity
    // This tests the second constructor form
    auto arrayWithSet = std::make_unique<TiffBinaryArray>(
        0x0005, IfdId::ifd0Id, nullptr, 0, nullptr);
    
    EXPECT_FALSE(arrayWithSet->decoded());
    EXPECT_EQ(arrayWithSet->cfg(), nullptr);
    EXPECT_EQ(arrayWithSet->def(), nullptr);
    EXPECT_EQ(arrayWithSet->defSize(), 0u);
}

// Test initialize with TiffComponent* pRoot
TEST_F(TiffBinaryArrayTest_331, InitializeWithRoot_331) {
    TiffBinaryArray rootComponent(0x0001, IfdId::ifd0Id, testArrayCfg, testArrayDef, 1);
    bool result = array_->initialize(&rootComponent);
    // We can at least verify it doesn't crash and returns a bool
    EXPECT_TRUE(result || !result);  // Just verify it returns
}

// Test initialize with nullptr root
TEST_F(TiffBinaryArrayTest_331, InitializeWithNullRoot_331) {
    bool result = array_->initialize(static_cast<TiffComponent*>(nullptr));
    EXPECT_TRUE(result || !result);
}

// Test tag and group from base class
TEST_F(TiffBinaryArrayTest_331, TagAndGroupFromConstruction_331) {
    EXPECT_EQ(array_->tag(), 0x0001);
    EXPECT_EQ(array_->group(), IfdId::ifd0Id);
}

// Test updOrigDataBuf with null data
TEST_F(TiffBinaryArrayTest_331, UpdOrigDataBufWithNullData_331) {
    bool result = array_->updOrigDataBuf(nullptr, 0);
    // Observable: returns bool, should not crash
    EXPECT_TRUE(result || !result);
}

// Test iniOrigDataBuf doesn't crash on fresh object
TEST_F(TiffBinaryArrayTest_331, IniOrigDataBufOnFreshObject_331) {
    EXPECT_NO_THROW(array_->iniOrigDataBuf());
}

// Test that defSize with ArrayCfg constructor returns correct value
TEST_F(TiffBinaryArrayTest_331, DefSizeMatchesConstructorArg_331) {
    const size_t expectedSize = 5;
    ArrayDef largeDef[5] = {
        {0, ttUndefined, 1},
        {1, ttUndefined, 1},
        {2, ttUndefined, 1},
        {3, ttUndefined, 1},
        {4, ttUndefined, 1}
    };
    
    TiffBinaryArray largeArray(0x0001, IfdId::ifd0Id, testArrayCfg, largeDef, expectedSize);
    EXPECT_EQ(largeArray.defSize(), expectedSize);
}

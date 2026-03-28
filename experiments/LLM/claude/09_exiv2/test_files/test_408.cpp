size_t doSizeImage() const { return 0; }
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

#include <memory>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffEntryBase may have pure virtual methods from TiffComponent,
// we need a concrete subclass for testing. TiffEntry is a known concrete subclass.
// We'll use TiffEntry or create a minimal testable wrapper.

// TiffEntry is typically: class TiffEntry : public TiffEntryBase
// Let's try using TiffEntry directly if available, otherwise create a test derivative.

namespace {

// A concrete subclass that exposes protected methods for testing
class TestableTiffEntryBase : public TiffEntryBase {
public:
    TestableTiffEntryBase(uint16_t tag, IfdId group, TiffType tiffType = ttUndefined)
        : TiffEntryBase(tag, group, tiffType) {}

    // Expose protected methods for testing
    using TiffEntryBase::doSizeImage;
    using TiffEntryBase::doSizeData;
    using TiffEntryBase::doSize;
    using TiffEntryBase::doCount;

    // Implement any pure virtual methods from TiffComponent if needed
    TiffComponent* doClone() const override {
        return new TestableTiffEntryBase(*this);
    }

    void doAccept(TiffVisitor& /*visitor*/) override {}

protected:
    TestableTiffEntryBase(const TestableTiffEntryBase& rhs) = default;
};

} // anonymous namespace

class TiffEntryBaseTest_408 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that doSizeImage returns 0
TEST_F(TiffEntryBaseTest_408, DoSizeImageReturnsZero_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0u, entry.doSizeImage());
}

// Test constructor sets tiffType correctly
TEST_F(TiffEntryBaseTest_408, ConstructorSetsTiffType_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttShort);
    EXPECT_EQ(ttShort, entry.tiffType());
}

// Test constructor with different tiff types
TEST_F(TiffEntryBaseTest_408, ConstructorWithLongType_408) {
    TestableTiffEntryBase entry(0x0101, IfdId::ifd0Id, ttLong);
    EXPECT_EQ(ttLong, entry.tiffType());
}

// Test initial pData is nullptr
TEST_F(TiffEntryBaseTest_408, InitialPDataIsNull_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(nullptr, entry.pData());
}

// Test initial pValue is nullptr
TEST_F(TiffEntryBaseTest_408, InitialPValueIsNull_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(nullptr, entry.pValue());
}

// Test initial offset is 0
TEST_F(TiffEntryBaseTest_408, InitialOffsetIsZero_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0u, entry.offset());
}

// Test initial idx is 0
TEST_F(TiffEntryBaseTest_408, InitialIdxIsZero_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0, entry.idx());
}

// Test setOffset
TEST_F(TiffEntryBaseTest_408, SetOffsetUpdatesOffset_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(42);
    EXPECT_EQ(42u, entry.offset());
}

// Test setOffset with large value
TEST_F(TiffEntryBaseTest_408, SetOffsetLargeValue_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(0xFFFFFFFF);
    EXPECT_EQ(0xFFFFFFFF, entry.offset());
}

// Test setOffset with zero
TEST_F(TiffEntryBaseTest_408, SetOffsetZero_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    entry.setOffset(100);
    entry.setOffset(0);
    EXPECT_EQ(0u, entry.offset());
}

// Test setData with shared buffer
TEST_F(TiffEntryBaseTest_408, SetDataWithSharedBuffer_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    std::memset(buf->data(), 0xAB, 10);
    entry.setData(buf);
    EXPECT_NE(nullptr, entry.pData());
}

// Test setData with raw pointer and storage
TEST_F(TiffEntryBaseTest_408, SetDataWithRawPointerAndStorage_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto storage = std::make_shared<DataBuf>(5);
    std::memset(storage->data(), 0xCD, 5);
    entry.setData(storage->data(), 5, storage);
    EXPECT_EQ(storage->data(), entry.pData());
}

// Test setValue
TEST_F(TiffEntryBaseTest_408, SetValueUpdatesPValue_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Hello");
    entry.setValue(std::move(value));
    EXPECT_NE(nullptr, entry.pValue());
}

// Test setValue with nullptr-like (empty unique_ptr)
TEST_F(TiffEntryBaseTest_408, SetValueWithNullptr_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttAscii);
    std::unique_ptr<Value> nullValue;
    entry.setValue(std::move(nullValue));
    EXPECT_EQ(nullptr, entry.pValue());
}

// Test doCount initially returns 0
TEST_F(TiffEntryBaseTest_408, DoCountInitiallyZero_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0u, entry.doCount());
}

// Test doSizeData returns 0 by default
TEST_F(TiffEntryBaseTest_408, DoSizeDataReturnsZeroByDefault_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0u, entry.doSizeData());
}

// Test doSize returns 0 when no data
TEST_F(TiffEntryBaseTest_408, DoSizeReturnsZeroWhenNoData_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0u, entry.doSize());
}

// Test tag is set correctly from constructor (inherited from TiffComponent)
TEST_F(TiffEntryBaseTest_408, TagIsSetCorrectly_408) {
    TestableTiffEntryBase entry(0x0110, IfdId::ifd0Id, ttAscii);
    EXPECT_EQ(0x0110, entry.tag());
}

// Test group is set correctly
TEST_F(TiffEntryBaseTest_408, GroupIsSetCorrectly_408) {
    TestableTiffEntryBase entry(0x0110, IfdId::exifId, ttAscii);
    EXPECT_EQ(IfdId::exifId, entry.group());
}

// Test updateValue with a value and byte order
TEST_F(TiffEntryBaseTest_408, UpdateValueSetsValue_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("256");
    entry.updateValue(std::move(value), littleEndian);
    EXPECT_NE(nullptr, entry.pValue());
    EXPECT_NE(nullptr, entry.pData());
}

// Test updateValue with big endian
TEST_F(TiffEntryBaseTest_408, UpdateValueBigEndian_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttShort);
    auto value = Value::create(unsignedShort);
    value->read("1");
    entry.updateValue(std::move(value), bigEndian);
    EXPECT_NE(nullptr, entry.pValue());
}

// Test doSizeImage with data set
TEST_F(TiffEntryBaseTest_408, DoSizeImageWithDataStillZero_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(100);
    entry.setData(buf);
    EXPECT_EQ(0u, entry.doSizeImage());
}

// Test multiple setData calls
TEST_F(TiffEntryBaseTest_408, MultipleSetDataCalls_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf1 = std::make_shared<DataBuf>(10);
    entry.setData(buf1);
    EXPECT_EQ(buf1->data(), entry.pData());

    auto buf2 = std::make_shared<DataBuf>(20);
    entry.setData(buf2);
    EXPECT_EQ(buf2->data(), entry.pData());
}

// Test with ttUndefined type
TEST_F(TiffEntryBaseTest_408, UndefinedTiffType_408) {
    TestableTiffEntryBase entry(0x9000, IfdId::exifId, ttUndefined);
    EXPECT_EQ(ttUndefined, entry.tiffType());
}

// Test with ttByte type
TEST_F(TiffEntryBaseTest_408, ByteTiffType_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttByte);
    EXPECT_EQ(ttByte, entry.tiffType());
}

// Test with ttRational type
TEST_F(TiffEntryBaseTest_408, RationalTiffType_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttRational);
    EXPECT_EQ(ttRational, entry.tiffType());
}

// Test tag boundary: tag = 0
TEST_F(TiffEntryBaseTest_408, TagZero_408) {
    TestableTiffEntryBase entry(0x0000, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0x0000, entry.tag());
}

// Test tag boundary: tag = max uint16
TEST_F(TiffEntryBaseTest_408, TagMaxUint16_408) {
    TestableTiffEntryBase entry(0xFFFF, IfdId::ifd0Id, ttUndefined);
    EXPECT_EQ(0xFFFF, entry.tag());
}

// Test setValue then check pData behavior (setValue may or may not set pData)
TEST_F(TiffEntryBaseTest_408, SetValueAsciiCheckPValue_408) {
    TestableTiffEntryBase entry(0x010E, IfdId::ifd0Id, ttAscii);
    auto value = Value::create(asciiString);
    value->read("Test description");
    entry.setValue(std::move(value));
    ASSERT_NE(nullptr, entry.pValue());
    EXPECT_EQ("Test description", entry.pValue()->toString());
}

// Test setData with zero-length buffer
TEST_F(TiffEntryBaseTest_408, SetDataZeroLengthBuffer_408) {
    TestableTiffEntryBase entry(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);
    // pData might be nullptr for empty buffer
    // Just ensure no crash
}

// Test destruction doesn't crash
TEST_F(TiffEntryBaseTest_408, DestructorDoesNotCrash_408) {
    auto entry = std::make_unique<TestableTiffEntryBase>(0x0100, IfdId::ifd0Id, ttUndefined);
    auto buf = std::make_shared<DataBuf>(10);
    entry->setData(buf);
    auto value = Value::create(unsignedShort);
    value->read("42");
    entry->setValue(std::move(value));
    entry.reset(); // Explicitly destroy
    SUCCEED();
}

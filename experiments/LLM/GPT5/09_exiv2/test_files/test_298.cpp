#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "tiffcomposite_int.hpp"
#include "types.hpp"

namespace Exiv2 { namespace Internal {

class MockTiffEncoder : public TiffEncoder {
public:
    MOCK_METHOD(void, encode, (const TiffEntryBase&, const Exifdatum*), (override));
};

class TiffEntryBaseTest : public ::testing::Test {
protected:
    TiffEntryBaseTest() = default;
    ~TiffEntryBaseTest() override = default;

    // Common mock objects
    std::shared_ptr<DataBuf> mockDataBuf;
    MockTiffEncoder encoder;
    Exifdatum datum;  // Used in encode test
    TiffEntryBase entry;

    void SetUp() override {
        mockDataBuf = std::make_shared<DataBuf>(128);  // Allocate a buffer of size 128
        entry.setData(mockDataBuf);  // Initialize the entry with mock data
    }
};

TEST_F(TiffEntryBaseTest, SetData_SetsBufferCorrectly_298) {
    ASSERT_NE(entry.storage(), nullptr);
    ASSERT_EQ(entry.storage()->size(), 128);
    ASSERT_EQ(entry.pData(), entry.storage()->c_data(0));
}

TEST_F(TiffEntryBaseTest, Encode_CallsEncodeMethod_299) {
    // Verify that encoder.encode() is called with the correct parameters
    EXPECT_CALL(encoder, encode(::testing::Ref(entry), ::testing::_)).Times(1);
    entry.encode(encoder, &datum);
}

TEST_F(TiffEntryBaseTest, SetData_UpdatesDataCorrectly_300) {
    // New data to set
    std::shared_ptr<DataBuf> newBuf = std::make_shared<DataBuf>(256);
    entry.setData(newBuf);

    ASSERT_EQ(entry.storage()->size(), 256);
    ASSERT_EQ(entry.pData(), entry.storage()->c_data(0));
}

TEST_F(TiffEntryBaseTest, SetData_ResizesStorageBuffer_301) {
    // Create a new DataBuf, verify that the size changes when new data is set
    std::shared_ptr<DataBuf> newBuf = std::make_shared<DataBuf>(512);
    entry.setData(newBuf);

    ASSERT_EQ(entry.storage()->size(), 512);
}

TEST_F(TiffEntryBaseTest, SetValue_UpdatesValue_302) {
    // Testing the setValue function
    std::unique_ptr<Value> newValue = std::make_unique<Value>();
    entry.setValue(std::move(newValue));

    ASSERT_NE(entry.pValue(), nullptr);
}

TEST_F(TiffEntryBaseTest, SetOffset_UpdatesOffset_303) {
    entry.setOffset(1024);
    ASSERT_EQ(entry.offset(), 1024);
}

TEST_F(TiffEntryBaseTest, TiffType_IsSetCorrectly_304) {
    TiffType type = entry.tiffType();
    ASSERT_EQ(type, TiffType::Unknown);  // assuming default is Unknown, modify as needed
}

TEST_F(TiffEntryBaseTest, Destructor_CleansUpCorrectly_305) {
    {
        TiffEntryBase tempEntry(1, IfdId::Image, TiffType::Byte);
    }  // Ensure destructor is called without any issues
    ASSERT_TRUE(true);  // If no crash happens, the destructor works as expected
}

TEST_F(TiffEntryBaseTest, BoundaryCondition_NoData_306) {
    TiffEntryBase emptyEntry(1, IfdId::Image, TiffType::Byte);
    emptyEntry.setData(nullptr);  // Null data
    ASSERT_EQ(emptyEntry.storage(), nullptr);
}

TEST_F(TiffEntryBaseTest, BoundaryCondition_ZeroSizeData_307) {
    std::shared_ptr<DataBuf> emptyBuf = std::make_shared<DataBuf>(0);  // 0 size data
    entry.setData(emptyBuf);
    ASSERT_EQ(entry.storage()->size(), 0);
}

TEST_F(TiffEntryBaseTest, ExceptionalCase_SetNullData_308) {
    ASSERT_THROW(entry.setData(nullptr), std::invalid_argument);
}

} }  // namespace Exiv2::Internal
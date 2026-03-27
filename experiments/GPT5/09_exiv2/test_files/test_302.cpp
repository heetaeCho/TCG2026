#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/error.hpp"
#include "exiv2/value.hpp"
#include "exiv2/tiffcomposite_int.hpp"

namespace Exiv2 {
    namespace Internal {

        // Mocking the Value class for testing
        class MockValue : public Value {
        public:
            MOCK_METHOD(size_t, count, (), (const, override));
            MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));
            MOCK_METHOD(void, setDataArea, (byte* buf, size_t len), (override));
        };

        // Test Fixture for TiffDataEntry
        class TiffDataEntryTest : public testing::Test {
        protected:
            TiffDataEntry tiffDataEntry;

            // Test helper for setting up a MockValue
            std::unique_ptr<MockValue> mockValue;
            std::shared_ptr<DataBuf> mockStorage;

            void SetUp() override {
                mockValue = std::make_unique<MockValue>();
                mockStorage = std::make_shared<DataBuf>();
            }
        };

        // Test for normal operation: when all values are valid
        TEST_F(TiffDataEntryTest, SetStrips_Success_302) {
            const size_t sizeData = 100;
            const size_t baseOffset = 10;
            byte data[sizeData];
            const byte* pData = data;

            // Mocking Value behavior
            EXPECT_CALL(*mockValue, count()).WillOnce(testing::Return(2));
            EXPECT_CALL(*mockValue, toUint32(0)).WillOnce(testing::Return(10));
            EXPECT_CALL(*mockValue, toUint32(1)).WillOnce(testing::Return(20));
            EXPECT_CALL(*mockValue, setDataArea(testing::NotNull(), testing::_));

            // Call setStrips
            tiffDataEntry.setStrips(mockValue.get(), pData, sizeData, baseOffset);

            // Verify that the function has completed as expected (set the data area)
            ASSERT_EQ(tiffDataEntry.pData(), pData + baseOffset + 10);
        }

        // Test for boundary condition: when size and data offset entries have different components
        TEST_F(TiffDataEntryTest, SetStrips_DifferentSizeAndDataCount_303) {
            const size_t sizeData = 100;
            const size_t baseOffset = 10;
            byte data[sizeData];
            const byte* pData = data;

            // Mocking Value behavior with mismatched count
            EXPECT_CALL(*mockValue, count()).WillOnce(testing::Return(1)); // Mismatch: expected 2
            EXPECT_CALL(*mockValue, toUint32(0)).WillOnce(testing::Return(10));
            EXPECT_CALL(*mockValue, toUint32(1)).WillOnce(testing::Return(20));

            // Call setStrips (should ignore due to mismatch)
            tiffDataEntry.setStrips(mockValue.get(), pData, sizeData, baseOffset);
            ASSERT_EQ(tiffDataEntry.pData(), nullptr);
        }

        // Test for boundary condition: when data area exceeds data buffer size
        TEST_F(TiffDataEntryTest, SetStrips_DataAreaExceeds_304) {
            const size_t sizeData = 100;
            const size_t baseOffset = 10;
            byte data[sizeData];
            const byte* pData = data;

            // Mocking Value behavior
            EXPECT_CALL(*mockValue, count()).WillOnce(testing::Return(1));
            EXPECT_CALL(*mockValue, toUint32(0)).WillOnce(testing::Return(200)); // Exceeds sizeData

            // Call setStrips (should ignore due to size issue)
            tiffDataEntry.setStrips(mockValue.get(), pData, sizeData, baseOffset);
            ASSERT_EQ(tiffDataEntry.pData(), nullptr);
        }

        // Test for exceptional case: when either pSize or pData is null
        TEST_F(TiffDataEntryTest, SetStrips_NullSizeOrData_305) {
            const size_t sizeData = 100;
            const size_t baseOffset = 10;
            byte data[sizeData];
            const byte* pData = nullptr; // Null data

            // Mocking Value behavior
            EXPECT_CALL(*mockValue, count()).WillOnce(testing::Return(1));
            EXPECT_CALL(*mockValue, toUint32(0)).WillOnce(testing::Return(10));

            // Call setStrips (should ignore due to null data)
            tiffDataEntry.setStrips(mockValue.get(), pData, sizeData, baseOffset);
            ASSERT_EQ(tiffDataEntry.pData(), nullptr);
        }

        // Test for logging warning when invalid conditions are met
        TEST_F(TiffDataEntryTest, SetStrips_LogWarning_306) {
            const size_t sizeData = 100;
            const size_t baseOffset = 10;
            byte data[sizeData];
            const byte* pData = data;

            // Mocking Value behavior
            EXPECT_CALL(*mockValue, count()).WillOnce(testing::Return(0)); // Empty count

            // Expect a warning to be logged
            testing::internal::CaptureStderr();
            tiffDataEntry.setStrips(mockValue.get(), pData, sizeData, baseOffset);
            std::string output = testing::internal::GetCapturedStderr();
            EXPECT_NE(output.find("Size or data offset value not set"), std::string::npos);
        }
    }
}
#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking IoWrapper for testing purposes

namespace Exiv2 {

    namespace Internal {



        class MockIoWrapper : public IoWrapper {

        public:

            MOCK_METHOD(void, write, (const byte* data, size_t length), (override));

            MOCK_METHOD(void, putb, (byte b), (override));

        };



        // Test fixture for TiffImageEntry

        class TiffImageEntryTest_387 : public ::testing::Test {

        protected:

            MockIoWrapper mockIoWrapper;

            std::shared_ptr<TiffData> testData;

            std::vector<std::pair<const byte*, size_t>> testStrips;



            void SetUp() override {

                testData = std::make_shared<TiffData>();

                testData->setDataArea({0x01, 0x02, 0x03});

                testData->setSizeDataArea(3);

            }

        };



        // Test normal operation with a data area

        TEST_F(TiffImageEntryTest_387, DoWriteImageData_Normal_387) {

            TiffImageEntry entry;

            entry.pValue_ = testData;



            EXPECT_CALL(mockIoWrapper, write(testData->dataArea().c_data(), testData->sizeDataArea()));

            EXPECT_CALL(mockIoWrapper, putb(0x0)).Times(1);



            size_t result = entry.doWriteImage(mockIoWrapper, ByteOrder::big);

            EXPECT_EQ(result, 4); // Data length (3) + alignment byte (1)

        }



        // Test normal operation with strips

        TEST_F(TiffImageEntryTest_387, DoWriteStrips_Normal_387) {

            TiffImageEntry entry;

            testStrips = {{testData->dataArea().c_data(), testData->sizeDataArea()}};

            entry.strips_ = testStrips;



            EXPECT_CALL(mockIoWrapper, write(testData->dataArea().c_data(), testData->sizeDataArea())).Times(1);

            EXPECT_CALL(mockIoWrapper, putb(0x0)).Times(1);



            size_t result = entry.doWriteImage(mockIoWrapper, ByteOrder::big);

            EXPECT_EQ(result, 4); // Strip length (3) + alignment byte (1)

        }



        // Test boundary condition with zero-length data area

        TEST_F(TiffImageEntryTest_387, DoWriteImageData_ZeroLength_387) {

            TiffImageEntry entry;

            testData->setSizeDataArea(0);

            entry.pValue_ = testData;



            EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_)).Times(0);

            EXPECT_CALL(mockIoWrapper, putb(0x0)).Times(0);



            size_t result = entry.doWriteImage(mockIoWrapper, ByteOrder::big);

            EXPECT_EQ(result, 0); // No data to write

        }



        // Test boundary condition with zero-length strips

        TEST_F(TiffImageEntryTest_387, DoWriteStrips_ZeroLength_387) {

            TiffImageEntry entry;

            testStrips = {{testData->dataArea().c_data(), 0}};

            entry.strips_ = testStrips;



            EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_)).Times(0);

            EXPECT_CALL(mockIoWrapper, putb(0x0)).Times(0);



            size_t result = entry.doWriteImage(mockIoWrapper, ByteOrder::big);

            EXPECT_EQ(result, 0); // No data to write

        }



        // Test exception handling when pValue is null

        TEST_F(TiffImageEntryTest_387, DoWriteImageData_Exception_387) {

            TiffImageEntry entry;

            entry.pValue_ = nullptr;



            EXPECT_THROW(entry.doWriteImage(mockIoWrapper, ByteOrder::big), Error);

        }



    } // namespace Internal

} // namespace Exiv2

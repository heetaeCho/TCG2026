#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/minoltamn_int.cpp"



namespace Exiv2 {

    namespace Internal {



        using ::testing::_;

        using ::testing::Return;

        using ::testing::Ref;



        class MockValue : public Value {

        public:

            MOCK_METHOD(int, read, (const byte* buf, size_t len, ByteOrder byteOrder), (override));

            MOCK_METHOD(int, read, (const std::string& buf), (override));

            MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

            MOCK_METHOD(const size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));

            MOCK_METHOD(const size_t, count, (), (const, override));

            MOCK_METHOD(const size_t, size, (), (const, override));

            MOCK_METHOD(const std::ostream&, write, (std::ostream& os), (const, override));

            MOCK_METHOD(const std::string, toString, (), (const, override));

            MOCK_METHOD(const int64_t, toInt64, (size_t n), (const, override));

            MOCK_METHOD(const uint32_t, toUint32, (size_t n), (const, override));

            MOCK_METHOD(const float, toFloat, (size_t n), (const, override));

            MOCK_METHOD(const Rational, toRational, (size_t n), (const, override));

            MOCK_METHOD(const size_t, sizeDataArea, (), (const, override));

            MOCK_METHOD(const DataBuf, dataArea, (), (const, override));



            MockValue(TypeId typeId) : Value(typeId) {}

        };



        class PrintMinoltaSonySceneModeTest : public ::testing::Test {

        protected:

            std::ostringstream os;

            MockValue mockValue;

            ExifData metadata;



            PrintMinoltaSonySceneModeTest() : mockValue(0) {}



            void SetUp() override {

                ON_CALL(mockValue, toInt64(0)).WillByDefault(Return(0));

            }

        };



        TEST_F(PrintMinoltaSonySceneModeTest, StandardScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(0));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Standard");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, PortraitScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(1));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Portrait");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, TextScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(2));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Text");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, NightScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(3));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Night Scene");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, SunsetScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(4));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Sunset");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, SportsScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(5));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Sports");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, LandscapeScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(6));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Landscape");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, NightPortraitScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(7));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Night Portrait");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, MacroScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(8));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Macro");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, SuperMacroScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(9));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Super Macro");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, AutoScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(16));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Auto");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, NightViewPortraitScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(17));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Night View/Portrait");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, SweepPanoramaScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(18));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Sweep Panorama");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, HandheldNightShotScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(19));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Handheld Night Shot");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, AntiMotionBlurScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(20));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Anti Motion Blur");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, ContPriorityAEScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(21));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Cont. Priority AE");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, AutoPlusScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(22));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Auto+");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, ThreeDSweepPanoramaScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(23));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "3D Sweep Panorama");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, SuperiorAutoScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(24));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Superior Auto");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, HighSensitivityScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(25));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "High Sensitivity");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, FireworksScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(26));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Fireworks");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, FoodScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(27));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Food");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, PetScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(28));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "Pet");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, HDRScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(33));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "HDR");

        }



        TEST_F(PrintMinoltaSonySceneModeTest, UnknownScene_1035) {

            EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(99));



            printMinoltaSonySceneMode(os, mockValue, &metadata);

            EXPECT_EQ(os.str(), "n/a");

        }



    } // namespace Internal

} // namespace Exiv2

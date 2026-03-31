#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonySceneMode(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonySceneModeTest_1035 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test standard scene mode (value 0)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Standard_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Standard");
}

// Test portrait scene mode (value 1)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Portrait_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Portrait");
}

// Test text scene mode (value 2)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Text_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Text");
}

// Test night scene mode (value 3)
TEST_F(PrintMinoltaSonySceneModeTest_1035, NightScene_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Night Scene");
}

// Test sunset scene mode (value 4)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Sunset_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Sunset");
}

// Test sports scene mode (value 5)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Sports_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("5");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Sports");
}

// Test landscape scene mode (value 6)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Landscape_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("6");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Landscape");
}

// Test night portrait scene mode (value 7)
TEST_F(PrintMinoltaSonySceneModeTest_1035, NightPortrait_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("7");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Night Portrait");
}

// Test macro scene mode (value 8)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Macro_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("8");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Macro");
}

// Test super macro scene mode (value 9)
TEST_F(PrintMinoltaSonySceneModeTest_1035, SuperMacro_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("9");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Super Macro");
}

// Test auto scene mode (value 16)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Auto_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("16");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

// Test night view/portrait scene mode (value 17)
TEST_F(PrintMinoltaSonySceneModeTest_1035, NightViewPortrait_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("17");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Night View/Portrait");
}

// Test sweep panorama scene mode (value 18)
TEST_F(PrintMinoltaSonySceneModeTest_1035, SweepPanorama_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("18");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Sweep Panorama");
}

// Test handheld night shot scene mode (value 19)
TEST_F(PrintMinoltaSonySceneModeTest_1035, HandheldNightShot_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("19");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Handheld Night Shot");
}

// Test anti motion blur scene mode (value 20)
TEST_F(PrintMinoltaSonySceneModeTest_1035, AntiMotionBlur_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("20");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Anti Motion Blur");
}

// Test cont. priority AE scene mode (value 21)
TEST_F(PrintMinoltaSonySceneModeTest_1035, ContPriorityAE_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("21");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Cont. Priority AE");
}

// Test auto+ scene mode (value 22)
TEST_F(PrintMinoltaSonySceneModeTest_1035, AutoPlus_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("22");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Auto+");
}

// Test 3D sweep panorama scene mode (value 23)
TEST_F(PrintMinoltaSonySceneModeTest_1035, ThreeDSweepPanorama_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("23");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "3D Sweep Panorama");
}

// Test superior auto scene mode (value 24)
TEST_F(PrintMinoltaSonySceneModeTest_1035, SuperiorAuto_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("24");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Superior Auto");
}

// Test high sensitivity scene mode (value 25)
TEST_F(PrintMinoltaSonySceneModeTest_1035, HighSensitivity_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("25");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "High Sensitivity");
}

// Test fireworks scene mode (value 26)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Fireworks_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("26");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Fireworks");
}

// Test food scene mode (value 27)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Food_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("27");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Food");
}

// Test pet scene mode (value 28)
TEST_F(PrintMinoltaSonySceneModeTest_1035, Pet_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("28");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Pet");
}

// Test HDR scene mode (value 33)
TEST_F(PrintMinoltaSonySceneModeTest_1035, HDR_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("33");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "HDR");
}

// Test n/a scene mode (value 65535)
TEST_F(PrintMinoltaSonySceneModeTest_1035, NotApplicable_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "n/a");
}

// Test unknown value (value 10 - gap between 9 and 16)
TEST_F(PrintMinoltaSonySceneModeTest_1035, UnknownValueInGap_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("10");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    // For unknown values, EXV_PRINT_TAG typically prints "(10)"
    EXPECT_EQ(os.str(), "(10)");
}

// Test unknown value (value 15 - just before Auto)
TEST_F(PrintMinoltaSonySceneModeTest_1035, UnknownValue15_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("15");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(15)");
}

// Test unknown value (value 29 - between Pet and HDR)
TEST_F(PrintMinoltaSonySceneModeTest_1035, UnknownValue29_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("29");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(29)");
}

// Test unknown value (value 100 - well beyond known range)
TEST_F(PrintMinoltaSonySceneModeTest_1035, UnknownValue100_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("100");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(100)");
}

// Test unknown value (value 34 - just after HDR)
TEST_F(PrintMinoltaSonySceneModeTest_1035, UnknownValue34_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("34");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(34)");
}

// Test with ExifData pointer (non-null but empty)
TEST_F(PrintMinoltaSonySceneModeTest_1035, WithEmptyExifData_1035) {
    Exiv2::ExifData exifData;
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Standard");
}

// Test with signed long value type
TEST_F(PrintMinoltaSonySceneModeTest_1035, WithSignedLongValue_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedLong);
    value->read("6");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Landscape");
}

// Test value 65534 - just before n/a
TEST_F(PrintMinoltaSonySceneModeTest_1035, UnknownValue65534_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("65534");
    Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(65534)");
}

// Test return value is reference to the same stream
TEST_F(PrintMinoltaSonySceneModeTest_1035, ReturnsSameStream_1035) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    std::ostream& result = Exiv2::Internal::printMinoltaSonySceneMode(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

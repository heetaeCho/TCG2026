#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration for the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa407(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa407Test_1417 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation: value 0 should print "None"
TEST_F(Print0xa407Test_1417, ValueZeroPrintsNone_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    EXPECT_EQ(os.str(), "None");
}

// Test normal operation: value 1 should print "Low gain up"
TEST_F(Print0xa407Test_1417, ValueOnePrintsLowGainUp_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Low gain up");
}

// Test normal operation: value 2 should print "High gain up"
TEST_F(Print0xa407Test_1417, ValueTwoPrintsHighGainUp_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    EXPECT_EQ(os.str(), "High gain up");
}

// Test normal operation: value 3 should print "Low gain down"
TEST_F(Print0xa407Test_1417, ValueThreePrintsLowGainDown_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Low gain down");
}

// Test normal operation: value 4 should print "High gain down"
TEST_F(Print0xa407Test_1417, ValueFourPrintsHighGainDown_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    EXPECT_EQ(os.str(), "High gain down");
}

// Test boundary condition: value 5 is out of known range
TEST_F(Print0xa407Test_1417, ValueFiveIsOutOfRange_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("5");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    // Out of range values typically print as "(5)"
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "None");
    EXPECT_NE(result, "Low gain up");
    EXPECT_NE(result, "High gain up");
    EXPECT_NE(result, "Low gain down");
    EXPECT_NE(result, "High gain down");
}

// Test boundary condition: large value out of range
TEST_F(Print0xa407Test_1417, LargeValueOutOfRange_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should not match any known gain control string
    EXPECT_NE(result, "None");
    EXPECT_NE(result, "Low gain up");
    EXPECT_NE(result, "High gain up");
    EXPECT_NE(result, "Low gain down");
    EXPECT_NE(result, "High gain down");
}

// Test with nullptr metadata - should still work
TEST_F(Print0xa407Test_1417, NullMetadataWorks_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    EXPECT_EQ(os.str(), "None");
}

// Test with actual ExifData object
TEST_F(Print0xa407Test_1417, WithExifDataObject_1417) {
    Exiv2::ExifData exifData;
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0xa407(os, *value, &exifData);
    EXPECT_EQ(os.str(), "High gain up");
}

// Test return value is the same ostream reference
TEST_F(Print0xa407Test_1417, ReturnsOstreamReference_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    std::ostream& result = Exiv2::Internal::print0xa407(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with signed long value type
TEST_F(Print0xa407Test_1417, SignedLongValueType_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedLong);
    value->read("3");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Low gain down");
}

// Test negative value (out of range)
TEST_F(Print0xa407Test_1417, NegativeValueOutOfRange_1417) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedLong);
    value->read("-1");
    Exiv2::Internal::print0xa407(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should not match any known gain control string
    EXPECT_NE(result, "None");
    EXPECT_NE(result, "Low gain up");
    EXPECT_NE(result, "High gain up");
    EXPECT_NE(result, "Low gain down");
    EXPECT_NE(result, "High gain down");
}

// Test all boundary values in sequence to verify each maps correctly
TEST_F(Print0xa407Test_1417, AllValidValuesInSequence_1417) {
    const std::pair<int, std::string> expected[] = {
        {0, "None"},
        {1, "Low gain up"},
        {2, "High gain up"},
        {3, "Low gain down"},
        {4, "High gain down"},
    };

    for (const auto& [val, name] : expected) {
        std::ostringstream localOs;
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
        value->read(std::to_string(val));
        Exiv2::Internal::print0xa407(localOs, *value, nullptr);
        EXPECT_EQ(localOs.str(), name) << "Failed for value " << val;
    }
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iostream>

// Assuming `Value` and `ExifData` are defined somewhere and have the methods used in the code.
namespace Exiv2 {
    namespace Internal {
        static std::ostream& printCameraTemperature(std::ostream& os, const Value& value, const ExifData*) {
            if (value.count() != 1 || value.typeId() != signedRational) {
                return os << value;
            }
            return os << value.toFloat() << " C";
        }
    }
}

// Mock class for ExifData, assuming it's a dependency we can mock
class MockExifData : public ExifData {
    // Mock necessary methods here
};

// Assuming the `Value` class looks like this, for the sake of testing
class Value {
public:
    enum Type { signedRational = 1, otherType = 2 };
    
    Value(int count, Type type) : count_(count), type_(type) {}
    
    int count() const { return count_; }
    Type typeId() const { return type_; }
    float toFloat() const { return 25.5f; }

private:
    int count_;
    Type type_;
};

// Test class definition
class PrintCameraTemperatureTest : public ::testing::Test {
protected:
    MockExifData mockExifData; // Mock ExifData object
};

// Test case 1: Test normal behavior where the value type is signedRational and count is 1
TEST_F(PrintCameraTemperatureTest, NormalCase_1721) {
    std::ostringstream os;
    Value value(1, Value::signedRational);

    Exiv2::Internal::printCameraTemperature(os, value, &mockExifData);
    
    // Verify if the printed output is as expected
    EXPECT_EQ(os.str(), "25.5 C");
}

// Test case 2: Test when the value type is not signedRational
TEST_F(PrintCameraTemperatureTest, IncorrectType_1722) {
    std::ostringstream os;
    Value value(1, Value::otherType);  // Other type instead of signedRational

    Exiv2::Internal::printCameraTemperature(os, value, &mockExifData);
    
    // Verify if the printed output is just the value
    EXPECT_EQ(os.str(), "25.5");
}

// Test case 3: Test when the value count is not 1
TEST_F(PrintCameraTemperatureTest, IncorrectCount_1723) {
    std::ostringstream os;
    Value value(2, Value::signedRational);  // Count is not 1

    Exiv2::Internal::printCameraTemperature(os, value, &mockExifData);
    
    // Verify if the printed output is just the value
    EXPECT_EQ(os.str(), "25.5");
}

// Test case 4: Test when the value count is 0
TEST_F(PrintCameraTemperatureTest, ZeroCount_1724) {
    std::ostringstream os;
    Value value(0, Value::signedRational);  // Count is 0

    Exiv2::Internal::printCameraTemperature(os, value, &mockExifData);
    
    // Verify if the printed output is just the value
    EXPECT_EQ(os.str(), "25.5");
}

// Test case 5: Test when the ExifData object is nullptr (edge case)
TEST_F(PrintCameraTemperatureTest, NullExifData_1725) {
    std::ostringstream os;
    Value value(1, Value::signedRational);  // Valid type and count

    Exiv2::Internal::printCameraTemperature(os, value, nullptr);  // Pass nullptr for ExifData
    
    // Verify if the printed output is as expected
    EXPECT_EQ(os.str(), "25.5 C");
}
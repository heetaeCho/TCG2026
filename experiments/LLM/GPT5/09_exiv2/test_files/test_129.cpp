#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/value.hpp"

using namespace Exiv2;

class StringValueBaseTest_129 : public ::testing::Test {
protected:
    // Set up any necessary preconditions
    StringValueBaseTest_129() {}
    ~StringValueBaseTest_129() override {}
};

TEST_F(StringValueBaseTest_129, Clone_129) {
    // Test the clone method of StringValueBase
    StringValueBase base(TypeId::string, "Test Value");
    auto cloned = base.clone();
    
    // Verify that the cloned object is of the correct type
    ASSERT_NE(cloned, nullptr);
    ASSERT_EQ(cloned->value_, base.value_);
}

TEST_F(StringValueBaseTest_129, ReadString_129) {
    // Test the read method with a string buffer
    StringValueBase base(TypeId::string, "");
    std::string test_str = "Test Buffer";
    int result = base.read(test_str);

    ASSERT_EQ(result, 0);  // Assuming 0 means success
    ASSERT_EQ(base.value_, test_str);
}

TEST_F(StringValueBaseTest_129, ReadByteBuffer_129) {
    // Test the read method with a byte buffer
    StringValueBase base(TypeId::string, "");
    const byte buffer[] = {'T', 'e', 's', 't', ' ', 'B', 'u', 'f', 'f', 'e', 'r'};
    size_t len = sizeof(buffer);
    int result = base.read(buffer, len, ByteOrder::littleEndian);

    ASSERT_EQ(result, 0);  // Assuming 0 means success
    ASSERT_EQ(base.value_, "Test Buffer");
}

TEST_F(StringValueBaseTest_129, Copy_129) {
    // Test the copy method
    StringValueBase base(TypeId::string, "Test Copy");
    byte buffer[128] = {0};
    size_t len = base.copy(buffer, ByteOrder::littleEndian);

    ASSERT_GT(len, 0);  // Verify some data was copied
    ASSERT_EQ(std::string(reinterpret_cast<char*>(buffer), len), "Test Copy");
}

TEST_F(StringValueBaseTest_129, Count_129) {
    // Test the count method
    StringValueBase base(TypeId::string, "Test Count");
    size_t count = base.count();

    ASSERT_GT(count, 0);  // Verify count is greater than 0
    ASSERT_EQ(count, base.value_.size());
}

TEST_F(StringValueBaseTest_129, Size_129) {
    // Test the size method
    StringValueBase base(TypeId::string, "Test Size");
    size_t size = base.size();

    ASSERT_EQ(size, base.value_.size());
}

TEST_F(StringValueBaseTest_129, ToInt64_129) {
    // Test the toInt64 method
    StringValueBase base(TypeId::string, "12345");
    int64_t result = base.toInt64(0);

    ASSERT_EQ(result, 12345);
}

TEST_F(StringValueBaseTest_129, ToUint32_129) {
    // Test the toUint32 method
    StringValueBase base(TypeId::string, "12345");
    uint32_t result = base.toUint32(0);

    ASSERT_EQ(result, 12345);
}

TEST_F(StringValueBaseTest_129, ToFloat_129) {
    // Test the toFloat method
    StringValueBase base(TypeId::string, "123.45");
    float result = base.toFloat(0);

    ASSERT_FLOAT_EQ(result, 123.45f);
}

TEST_F(StringValueBaseTest_129, ToRational_129) {
    // Test the toRational method
    StringValueBase base(TypeId::string, "1/2");
    Rational result = base.toRational(0);

    ASSERT_EQ(result.numerator(), 1);
    ASSERT_EQ(result.denominator(), 2);
}

TEST_F(StringValueBaseTest_129, Write_129) {
    // Test the write method
    StringValueBase base(TypeId::string, "Test Write");
    std::ostringstream os;
    base.write(os);

    ASSERT_EQ(os.str(), "Test Write");
}

TEST_F(StringValueBaseTest_129, CloneErrorHandling_129) {
    // Test clone behavior in case of an error (e.g., invalid memory or invalid object state)
    StringValueBase base(TypeId::string, "Invalid Clone");
    // Assuming we can simulate a failure using mocks or other techniques (if relevant)
    ASSERT_THROW(base.clone(), std::exception);
}
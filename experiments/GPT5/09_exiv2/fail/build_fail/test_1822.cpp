#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>

namespace Exiv2 {
    namespace Internal {
        class Value {
        public:
            virtual size_t size() const = 0;
            virtual long toInt64(size_t index) const = 0;
        };

        class Casio2MakerNote {
        public:
            std::ostream& print0x2001(std::ostream& os, const Value& value, const ExifData*) {
                std::vector<char> numbers;
                for (size_t i = 0; i < value.size(); i++) {
                    const auto l = value.toInt64(i);
                    if (l != 0) {
                        numbers.push_back(l);
                    }
                }
                if (numbers.size() >= 10) {
                    long l = ((numbers[0] - 48) * 10) + (numbers[1] - 48);
                    if (l < 70) l += 2000;
                    else l += 1900;
                    os << l << ":";
                    os << numbers[2] << numbers[3] << ":" << numbers[4] << numbers[5] << " "
                       << numbers[6] << numbers[7] << ":" << numbers[8] << numbers[9];
                } else os << value;
                return os;
            }
        };
    }
}

using namespace Exiv2::Internal;

class MockValue : public Value {
public:
    MOCK_CONST_METHOD0(size, size_t());
    MOCK_CONST_METHOD1(toInt64, long(size_t index));
};

// Test Case 1: TEST_ID 1822
TEST_F(Casio2MakerNoteTest_1822, Print0x2001_ValidValues_1822) {
    MockValue value;
    std::vector<long> values = {49, 50, 51, 52, 53, 54, 55, 56, 57, 48}; // Example data for printing
    size_t size = values.size();
    
    EXPECT_CALL(value, size()).WillOnce(testing::Return(size));
    for (size_t i = 0; i < size; ++i) {
        EXPECT_CALL(value, toInt64(i)).WillOnce(testing::Return(values[i]));
    }

    std::ostringstream os;
    Casio2MakerNote makerNote;
    makerNote.print0x2001(os, value, nullptr);

    EXPECT_EQ(os.str(), "2020:1234:56 78:90");
}

// Test Case 2: TEST_ID 1823
TEST_F(Casio2MakerNoteTest_1823, Print0x2001_InvalidSize_1823) {
    MockValue value;
    std::vector<long> values = {49, 50, 51};  // Less than 10 valid values

    size_t size = values.size();
    
    EXPECT_CALL(value, size()).WillOnce(testing::Return(size));
    for (size_t i = 0; i < size; ++i) {
        EXPECT_CALL(value, toInt64(i)).WillOnce(testing::Return(values[i]));
    }

    std::ostringstream os;
    Casio2MakerNote makerNote;
    makerNote.print0x2001(os, value, nullptr);

    // If the value size is less than 10, it should print the entire value as is
    EXPECT_EQ(os.str(), "123");
}

// Test Case 3: TEST_ID 1824
TEST_F(Casio2MakerNoteTest_1824, Print0x2001_EmptyValues_1824) {
    MockValue value;
    std::vector<long> values = {};  // Empty value

    EXPECT_CALL(value, size()).WillOnce(testing::Return(values.size()));

    std::ostringstream os;
    Casio2MakerNote makerNote;
    makerNote.print0x2001(os, value, nullptr);

    // Expecting the value to be printed as is, which should be empty
    EXPECT_EQ(os.str(), "");
}

// Test Case 4: TEST_ID 1825
TEST_F(Casio2MakerNoteTest_1825, Print0x2001_BoundaryValue_1825) {
    MockValue value;
    std::vector<long> values = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57};  // Boundary values for testing

    size_t size = values.size();
    
    EXPECT_CALL(value, size()).WillOnce(testing::Return(size));
    for (size_t i = 0; i < size; ++i) {
        EXPECT_CALL(value, toInt64(i)).WillOnce(testing::Return(values[i]));
    }

    std::ostringstream os;
    Casio2MakerNote makerNote;
    makerNote.print0x2001(os, value, nullptr);

    EXPECT_EQ(os.str(), "2020:1234:56 78:90");
}
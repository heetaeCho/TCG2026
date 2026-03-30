#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iomanip>
#include <cmath>

// Mock for external collaborators (if any)
class MockHandler {
public:
    MOCK_METHOD(void, handle, (const std::string&), ());
};

// The function we are testing
namespace Exiv2 { namespace Internal {
    static std::ostream& printFlashCompensationValue(std::ostream& os, const unsigned char value, const bool manualScale) {
        std::ios::fmtflags f(os.flags());
        std::ostringstream oss;
        oss.copyfmt(os);
        if (manualScale) {
            if (value > 48) {
                os << "(" << value << ")";
                os.flags(f);
                return os;
            }
            const auto mod = value % 6;
            auto temp = (value < 6) ? 0 : (value - mod) / 6;
            os << "1/" << std::exp2(temp);
            if (mod != 0) {
                os << " (-";
                switch (mod) {
                case 1: os << "1/6 EV)"; break;
                case 2: os << "1/3 EV)"; break;
                case 3: os << "1/2 EV)"; break;
                case 4: os << "2/3 EV)"; break;
                case 5: os << "5/6 EV)"; break;
                }
            }
        } else {
            auto output = 0.0f;
            if (value < 128) {
                if (value != 0) output = static_cast<float>(value) * -1.0f;
            } else {
                output = 256.0f - static_cast<float>(value);
            }
            os.precision(1);
            if (value != 0) os << std::showpos;
            os << std::fixed << (output / 6) << " EV";
        }
        os.copyfmt(os);
        os.flags(f);
        return os;
    }
} }

class FlashCompensationValueTest : public ::testing::Test {
protected:
    std::ostringstream os;
};

TEST_F(FlashCompensationValueTest, TestFlashCompensationNormalValueManualScale) {
    // The TEST_ID is 458
    unsigned char value = 6;
    bool manualScale = true;
    std::string expectedOutput = "1/4";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationValueGreaterThan48ManualScale) {
    // The TEST_ID is 459
    unsigned char value = 50;
    bool manualScale = true;
    std::string expectedOutput = "(50)";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationNegativeValueManualScale) {
    // The TEST_ID is 460
    unsigned char value = 5;
    bool manualScale = true;
    std::string expectedOutput = "1/2 (-5/6 EV)";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationZeroManualScale) {
    // The TEST_ID is 461
    unsigned char value = 0;
    bool manualScale = true;
    std::string expectedOutput = "1/1";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationNegativeEV) {
    // The TEST_ID is 462
    unsigned char value = 100;
    bool manualScale = false;
    std::string expectedOutput = "-16.7 EV";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationPositiveEV) {
    // The TEST_ID is 463
    unsigned char value = 200;
    bool manualScale = false;
    std::string expectedOutput = "+0.2 EV";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationEdgeValueManualScale) {
    // The TEST_ID is 464
    unsigned char value = 48;
    bool manualScale = true;
    std::string expectedOutput = "1/256";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationValueEdgeValueManualScale) {
    // The TEST_ID is 465
    unsigned char value = 129;
    bool manualScale = false;
    std::string expectedOutput = "+21.2 EV";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationValueEdgeCasePositive) {
    // The TEST_ID is 466
    unsigned char value = 128;
    bool manualScale = false;
    std::string expectedOutput = "+21.3 EV";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}

TEST_F(FlashCompensationValueTest, TestFlashCompensationEdgeCaseNegative) {
    // The TEST_ID is 467
    unsigned char value = 127;
    bool manualScale = false;
    std::string expectedOutput = "-21.2 EV";

    Exiv2::Internal::printFlashCompensationValue(os, value, manualScale);
    EXPECT_EQ(os.str(), expectedOutput);
}
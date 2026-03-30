#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using testing::_;



class MockValue : public Value {

public:

    MOCK_METHOD(std::ostream&, write, (std::ostream& os), (const override));

};



class PrintMinoltaSonyBoolValueTest_1027 : public ::testing::Test {

protected:

    MockValue mockValue;

    ExifData metadata;

};



TEST_F(PrintMinoltaSonyBoolValueTest_1027, NormalOperationFalse_1027) {

    EXPECT_CALL(mockValue.write, testing::_)

        .WillOnce(testing::Invoke([](std::ostream& os) -> std::ostream& { return os << "Off"; }));



    std::ostringstream oss;

    printMinoltaSonyBoolValue(oss, mockValue, &metadata);

    EXPECT_EQ(oss.str(), "Off");

}



TEST_F(PrintMinoltaSonyBoolValueTest_1027, NormalOperationTrue_1027) {

    ON_CALL(mockValue.toInt64, (testing::_)).WillByDefault(testing::Return(1));

    EXPECT_CALL(mockValue.write, testing::_)

        .WillOnce(testing::Invoke([](std::ostream& os) -> std::ostream& { return os << "On"; }));



    std::ostringstream oss;

    printMinoltaSonyBoolValue(oss, mockValue, &metadata);

    EXPECT_EQ(oss.str(), "On");

}



TEST_F(PrintMinoltaSonyBoolValueTest_1027, BoundaryConditionZero_1027) {

    ON_CALL(mockValue.toInt64, (testing::_)).WillByDefault(testing::Return(0));

    EXPECT_CALL(mockValue.write, testing::_)

        .WillOnce(testing::Invoke([](std::ostream& os) -> std::ostream& { return os << "Off"; }));



    std::ostringstream oss;

    printMinoltaSonyBoolValue(oss, mockValue, &metadata);

    EXPECT_EQ(oss.str(), "Off");

}



TEST_F(PrintMinoltaSonyBoolValueTest_1027, BoundaryConditionOne_1027) {

    ON_CALL(mockValue.toInt64, (testing::_)).WillByDefault(testing::Return(1));

    EXPECT_CALL(mockValue.write, testing::_)

        .WillOnce(testing::Invoke([](std::ostream& os) -> std::ostream& { return os << "On"; }));



    std::ostringstream oss;

    printMinoltaSonyBoolValue(oss, mockValue, &metadata);

    EXPECT_EQ(oss.str(), "On");

}



TEST_F(PrintMinoltaSonyBoolValueTest_1027, ExceptionalCaseInvalidValue_1027) {

    ON_CALL(mockValue.toInt64, (testing::_)).WillByDefault(testing::Return(2));

    EXPECT_CALL(mockValue.write, testing::_)

        .WillOnce(testing::Invoke([](std::ostream& os) -> std::ostream& { return os; }));



    std::ostringstream oss;

    printMinoltaSonyBoolValue(oss, mockValue, &metadata);

    EXPECT_EQ(oss.str(), ""); // Assuming invalid values are not printed

}

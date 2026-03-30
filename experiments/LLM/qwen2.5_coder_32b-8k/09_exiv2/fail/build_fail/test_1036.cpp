#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

namespace Internal {



std::ostream& printMinoltaSonyTeleconverterModel(std::ostream& os, const Value& value, const ExifData* metadata);



}  // namespace Internal

}  // namespace Exiv2



using ::testing::_;

using ::testing::NiceMock;

using ::testing::Return;



class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(const std::string&, toString, (size_t n), const);

};



class MockExifData : public Exiv2::ExifData {};



TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, NormalOperation_1036) {

    NiceMock<MockValue> value;

    MockExifData metadata;



    EXPECT_CALL(value, toString(0)).WillOnce(Return("4"));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyTeleconverterModel(os, value, &metadata);



    EXPECT_EQ(os.str(), "Minolta/Sony AF 1.4x APO (D) (0x04)");

}



TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, BoundaryCondition_Zero_1036) {

    NiceMock<MockValue> value;

    MockExifData metadata;



    EXPECT_CALL(value, toString(0)).WillOnce(Return("0"));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyTeleconverterModel(os, value, &metadata);



    EXPECT_EQ(os.str(), "None");

}



TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, BoundaryCondition_MaximumKnownValue_1036) {

    NiceMock<MockValue> value;

    MockExifData metadata;



    EXPECT_CALL(value, toString(0)).WillOnce(Return("160"));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyTeleconverterModel(os, value, &metadata);



    EXPECT_EQ(os.str(), "Minolta AF 1.4x APO");

}



TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, ExceptionalCase_UnknownValue_1036) {

    NiceMock<MockValue> value;

    MockExifData metadata;



    EXPECT_CALL(value, toString(0)).WillOnce(Return("999"));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyTeleconverterModel(os, value, &metadata);



    EXPECT_EQ(os.str(), "");

}



TEST_F(PrintMinoltaSonyTeleconverterModelTest_1036, MetadataNullPointer_1036) {

    NiceMock<MockValue> value;



    EXPECT_CALL(value, toString(0)).WillOnce(Return("4"));



    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyTeleconverterModel(os, value, nullptr);



    EXPECT_EQ(os.str(), "Minolta/Sony AF 1.4x APO (D) (0x04)");

}

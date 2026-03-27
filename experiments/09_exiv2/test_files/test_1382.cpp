#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tags_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class ValueMock : public Exiv2::Value {

public:

    MOCK_METHOD(Exiv2::TypeId, typeId, (), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(std::pair<long, long>, toRational, (size_t), (const, override));

    MOCK_METHOD(float, toFloat, (size_t), (const, override));

};



TEST_F(Exiv2LensSpecificationTest_1382, NormalOperationWithValidValues_1382) {

    ValueMock value;

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(Exiv2::unsignedRational));

    EXPECT_CALL(value, count()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, toRational(0)).WillOnce(::testing::Return(std::make_pair(100, 1)));

    EXPECT_CALL(value, toRational(1)).WillOnce(::testing::Return(std::make_pair(200, 1)));

    EXPECT_CALL(value, toRational(2)).WillOnce(::testing::Return(std::make_pair(56, 1)));

    EXPECT_CALL(value, toRational(3)).WillOnce(::testing::Return(std::make_pair(80, 1)));



    std::ostringstream os;

    printLensSpecification(os, value, nullptr);

    EXPECT_EQ(os.str(), "100.00000-200.00000mm F56-80");

}



TEST_F(Exiv2LensSpecificationTest_1382, BoundaryConditionWithZeroValues_1382) {

    ValueMock value;

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(Exiv2::unsignedRational));

    EXPECT_CALL(value, count()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, toRational(0)).WillOnce(::testing::Return(std::make_pair(0, 1)));

    EXPECT_CALL(value, toRational(1)).WillOnce(::testing::Return(std::make_pair(0, 1)));

    EXPECT_CALL(value, toRational(2)).WillOnce(::testing::Return(std::make_pair(0, 1)));

    EXPECT_CALL(value, toRational(3)).WillOnce(::testing::Return(std::make_pair(0, 1)));



    std::ostringstream os;

    printLensSpecification(os, value, nullptr);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Exiv2LensSpecificationTest_1382, BoundaryConditionWithSingleNonZeroValue_1382) {

    ValueMock value;

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(Exiv2::unsignedRational));

    EXPECT_CALL(value, count()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, toRational(0)).WillOnce(::testing::Return(std::make_pair(100, 1)));

    EXPECT_CALL(value, toRational(1)).WillOnce(::testing::Return(std::make_pair(0, 1)));

    EXPECT_CALL(value, toRational(2)).WillOnce(::testing::Return(std::make_pair(0, 1)));

    EXPECT_CALL(value, toRational(3)).WillOnce(::testing::Return(std::make_pair(0, 1)));



    std::ostringstream os;

    printLensSpecification(os, value, nullptr);

    EXPECT_EQ(os.str(), "100.00000mm n/a");

}



TEST_F(Exiv2LensSpecificationTest_1382, ExceptionalCaseWithInvalidTypeId_1382) {

    ValueMock value;

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(Exiv2::shortType));



    std::ostringstream os;

    printLensSpecification(os, value, nullptr);

    EXPECT_EQ(os.str(), "(short(0))");

}



TEST_F(Exiv2LensSpecificationTest_1382, ExceptionalCaseWithInvalidCount_1382) {

    ValueMock value;

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(Exiv2::unsignedRational));

    EXPECT_CALL(value, count()).WillOnce(::testing::Return(5));



    std::ostringstream os;

    printLensSpecification(os, value, nullptr);

    EXPECT_EQ(os.str(), "(unsigned rational())");

}



TEST_F(Exiv2LensSpecificationTest_1382, ExceptionalCaseWithZeroDenominator_1382) {

    ValueMock value;

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(Exiv2::unsignedRational));

    EXPECT_CALL(value, count()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, toRational(0)).WillOnce(::testing::Return(std::make_pair(100, 0)));

    EXPECT_CALL(value, toRational(1)).WillOnce(::testing::Return(std::make_pair(200, 1)));

    EXPECT_CALL(value, toRational(2)).WillOnce(::testing::Return(std::make_pair(56, 1)));

    EXPECT_CALL(value, toRational(3)).WillOnce(::testing::Return(std::make_pair(80, 1)));



    std::ostringstream os;

    printLensSpecification(os, value, nullptr);

    EXPECT_EQ(os.str(), "(unsigned rational())");

}



TEST_F(Exiv2LensSpecificationTest_1382, NormalOperationWithFloatingPointValues_1382) {

    ValueMock value;

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(Exiv2::unsignedRational));

    EXPECT_CALL(value, count()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, toFloat(0)).WillOnce(::testing::Return(100.5f));

    EXPECT_CALL(value, toFloat(1)).WillOnce(::testing::Return(200.75f));

    EXPECT_CALL(value, toFloat(2)).WillOnce(::testing::Return(56.3f));

    EXPECT_CALL(value, toFloat(3)).WillOnce(::testing::Return(80.99f));



    std::ostringstream os;

    printLensSpecification(os, value, nullptr);

    EXPECT_EQ(os.str(), "100.50000-200.75000mm F56.30-81");

}



TEST_F(Exiv2LensSpecificationTest_1382, BoundaryConditionWithSingleFNumber_1382) {

    ValueMock value;

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(Exiv2::unsignedRational));

    EXPECT_CALL(value, count()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, toRational(0)).WillOnce(::testing::Return(std::make_pair(100, 1)));

    EXPECT_CALL(value, toRational(1)).WillOnce(::testing::Return(std::make_pair(0, 1)));

    EXPECT_CALL(value, toRational(2)).WillOnce(::testing::Return(std::make_pair(56, 1)));

    EXPECT_CALL(value, toRational(3)).WillOnce(::testing::Return(std::make_pair(0, 1)));



    std::ostringstream os;

    printLensSpecification(os, value, nullptr);

    EXPECT_EQ(os.str(), "100.00000mm F56");

}

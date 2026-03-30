#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {

    class MockExifdatum : public Exifdatum {

    public:

        using Exifdatum::Exifdatum;

        MOCK_METHOD(Exifdatum&, operator=, (const uint32_t& value), (override));

    };

}



class ExifdatumTest_733 : public ::testing::Test {

protected:

    void SetUp() override {

        exifKey = std::make_unique<Exiv2::ExifKey>("0th", 0x10F, "Make");

        exifdatum = new Exiv2::MockExifdatum(*exifKey, nullptr);

    }



    void TearDown() override {

        delete exifdatum;

    }



    std::unique_ptr<Exiv2::ExifKey> exifKey;

    Exiv2::MockExifdatum* exifdatum;

};



TEST_F(ExifdatumTest_733, AssignmentOperatorNormalOperation_733) {

    EXPECT_CALL(*exifdatum, operator=(testing::_)).Times(1);

    *exifdatum = static_cast<uint32_t>(42);

}



TEST_F(ExifdatumTest_733, AssignmentOperatorBoundaryCondition_733) {

    EXPECT_CALL(*exifdatum, operator=(testing::_)).Times(1);

    *exifdatum = std::numeric_limits<uint32_t>::max();

}



// Exceptional cases might not be directly observable through the interface,

// but if there are known exceptional conditions, they can be tested.

// Since no specific exceptional behavior is documented for this method,

// we skip that section here.



TEST_F(ExifdatumTest_733, AssignmentOperatorExternalInteractionVerification_733) {

    EXPECT_CALL(*exifdatum, operator=(testing::_)).WillOnce(testing::ReturnRef(*exifdatum));

    *exifdatum = static_cast<uint32_t>(42);

}

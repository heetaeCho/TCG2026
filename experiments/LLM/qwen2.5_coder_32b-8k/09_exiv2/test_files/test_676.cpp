#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"



using namespace Exiv2;

using ::testing::Eq;



class IptcdatumTest_676 : public ::testing::Test {

protected:

    // Create a mock key for testing purposes

    class MockIptcKey : public IptcKey {

    public:

        MOCK_CONST_METHOD0(typeId, TypeId());

    };



    MockIptcKey mockKey;

    std::unique_ptr<Iptcdatum> iptcdatum;



    void SetUp() override {

        // Initialize Iptcdatum with a mock key

        iptcdatum = std::make_unique<Iptcdatum>(mockKey, nullptr);

    }

};



TEST_F(IptcdatumTest_676, TypeSize_ReturnsCorrectSizeBasedOnTypeId_676) {

    // Arrange

    EXPECT_CALL(mockKey, typeId()).WillOnce(::testing::Return(typeLong));



    // Act

    size_t result = iptcdatum->typeSize();



    // Assert

    EXPECT_EQ(result, TypeInfo::typeSize(typeLong));

}



TEST_F(IptcdatumTest_676, TypeSize_ReturnsCorrectSizeForBoundaryTypeId_676) {

    // Arrange

    EXPECT_CALL(mockKey, typeId()).WillOnce(::testing::Return(static_cast<TypeId>(0)));



    // Act

    size_t result = iptcdatum->typeSize();



    // Assert

    EXPECT_EQ(result, TypeInfo::typeSize(static_cast<TypeId>(0)));

}



TEST_F(IptcdatumTest_676, TypeSize_ReturnsCorrectSizeForMaxTypeId_676) {

    // Arrange

    EXPECT_CALL(mockKey, typeId()).WillOnce(::testing::Return(static_cast<TypeId>(std::numeric_limits<uint16_t>::max())));



    // Act

    size_t result = iptcdatum->typeSize();



    // Assert

    EXPECT_EQ(result, TypeInfo::typeSize(static_cast<TypeId>(std::numeric_limits<uint16_t>::max())));

}

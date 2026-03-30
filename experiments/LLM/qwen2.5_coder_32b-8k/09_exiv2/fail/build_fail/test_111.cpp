#include <gtest/gtest.h>

#include <exiv2/metadatum.hpp>



using namespace Exiv2;



class MetadatumTest_111 : public ::testing::Test {

protected:

    class MockMetadatum : public Metadatum {

    public:

        MOCK_CONST_METHOD1(toInt64, int64_t(size_t n));

    };



    std::unique_ptr<MockMetadatum> mockMetadatum;



    void SetUp() override {

        mockMetadatum = std::make_unique<MockMetadatum>();

    }

};



TEST_F(MetadatumTest_111, ToUint32_ConvertsPositiveInt64ToUint32_111) {

    EXPECT_CALL(*mockMetadatum, toInt64(0)).WillOnce(::testing::Return(42));

    EXPECT_EQ(mockMetadatum->toUint32(0), 42u);

}



TEST_F(MetadatumTest_111, ToUint32_ConvertsZeroInt64ToUint32_111) {

    EXPECT_CALL(*mockMetadatum, toInt64(0)).WillOnce(::testing::Return(0));

    EXPECT_EQ(mockMetadatum->toUint32(0), 0u);

}



TEST_F(MetadatumTest_111, ToUint32_ConvertsMaxUint32ToInt64ToUint32_111) {

    EXPECT_CALL(*mockMetadatum, toInt64(0)).WillOnce(::testing::Return(4294967295));

    EXPECT_EQ(mockMetadatum->toUint32(0), 4294967295u);

}



TEST_F(MetadatumTest_111, ToUint32_ConvertsNegativeInt64ToUint32_111) {

    EXPECT_CALL(*mockMetadatum, toInt64(0)).WillOnce(::testing::Return(-1));

    EXPECT_EQ(mockMetadatum->toUint32(0), 4294967295u);

}

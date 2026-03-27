#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

    namespace Internal {

        int sonyMisc3cSelector(uint16_t tag, const byte* pData, size_t size, TiffComponent* pRoot);

    }

}



using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockTiffComponent : public Exiv2::TiffComponent {

public:

    MOCK_METHOD(Exiv2::Value*, getExifValue, (uint16_t tag, Exiv2::IfdId ifdId), (override));

};



TEST_F(MockTiffComponentTest_1542, NormalOperation_ReturnsZero_1542) {

    NiceMock<MockTiffComponent> mockRoot;

    auto mockValue = std::make_unique<NiceMock<Exiv2::Value>>();

    EXPECT_CALL(*mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(*mockValue, toInt64())

        .WillOnce(Return(35))

        .WillOnce(Return(36))

        .WillOnce(Return(38))

        .WillOnce(Return(40))

        .WillOnce(Return(49))

        .WillOnce(Return(50));



    EXPECT_CALL(mockRoot, getExifValue(0x9400, Exiv2::IfdId::sony1Id))

        .WillRepeatedly(Return(mockValue.get()));



    EXPECT_EQ(Exiv2::Internal::sonyMisc3cSelector(0, nullptr, 0, &mockRoot), 0);

}



TEST_F(MockTiffComponentTest_1542, BoundaryCondition_CountZero_ReturnsNegativeOne_1542) {

    NiceMock<MockTiffComponent> mockRoot;

    auto mockValue = std::make_unique<NiceMock<Exiv2::Value>>();

    EXPECT_CALL(*mockValue, count()).WillRepeatedly(Return(0));



    EXPECT_CALL(mockRoot, getExifValue(0x9400, Exiv2::IfdId::sony1Id))

        .WillOnce(Return(mockValue.get()))

        .WillOnce(Return(nullptr));



    EXPECT_CALL(mockRoot, getExifValue(0x9400, Exiv2::IfdId::sony2Id))

        .WillOnce(Return(mockValue.get()));



    EXPECT_EQ(Exiv2::Internal::sonyMisc3cSelector(0, nullptr, 0, &mockRoot), -1);

}



TEST_F(MockTiffComponentTest_1542, ExceptionalCase_ValueNotFound_ReturnsNegativeOne_1542) {

    NiceMock<MockTiffComponent> mockRoot;

    EXPECT_CALL(mockRoot, getExifValue(0x9400, Exiv2::IfdId::sony1Id))

        .WillOnce(Return(nullptr));



    EXPECT_CALL(mockRoot, getExifValue(0x9400, Exiv2::IfdId::sony2Id))

        .WillOnce(Return(nullptr));



    EXPECT_EQ(Exiv2::Internal::sonyMisc3cSelector(0, nullptr, 0, &mockRoot), -1);

}



TEST_F(MockTiffComponentTest_1542, ExceptionalCase_ValueNotMatching_ReturnsNegativeOne_1542) {

    NiceMock<MockTiffComponent> mockRoot;

    auto mockValue = std::make_unique<NiceMock<Exiv2::Value>>();

    EXPECT_CALL(*mockValue, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(*mockValue, toInt64())

        .WillOnce(Return(0))

        .WillOnce(Return(34));



    EXPECT_CALL(mockRoot, getExifValue(0x9400, Exiv2::IfdId::sony1Id))

        .WillRepeatedly(Return(mockValue.get()));



    EXPECT_EQ(Exiv2::Internal::sonyMisc3cSelector(0, nullptr, 0, &mockRoot), -1);

}

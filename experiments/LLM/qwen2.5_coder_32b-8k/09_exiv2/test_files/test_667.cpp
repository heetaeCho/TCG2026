#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"



namespace Exiv2 {

    class MockIptcKey : public IptcKey {

    public:

        MOCK_CONST_METHOD0(record, uint16_t());

    };

}



using namespace Exiv2;



class IptcdatumTest_667 : public ::testing::Test {

protected:

    std::unique_ptr<MockIptcKey> mockKey;

    Iptcdatum iptcdatum;



    void SetUp() override {

        mockKey = std::make_unique<MockIptcKey>();

        iptcdatum = Iptcdatum(*mockKey, nullptr);

    }

};



TEST_F(IptcdatumTest_667, Record_ReturnsCorrectValue_667) {

    EXPECT_CALL(*mockKey, record()).WillOnce(::testing::Return(42));

    EXPECT_EQ(iptcdatum.record(), 42);

}



TEST_F(IptcdatumTest_667, Record_ReturnsZeroWhenKeyIsNull_667) {

    Iptcdatum iptcdatumWithoutKey(IptcKey("dummy"), nullptr);

    EXPECT_EQ(iptcdatumWithoutKey.record(), 0);

}

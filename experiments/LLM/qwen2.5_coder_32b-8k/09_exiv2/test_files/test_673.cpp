#include <gtest/gtest.h>

#include "iptc.hpp"

#include "datasets.hpp"



namespace Exiv2 {

class MockIptcKey : public IptcKey {

public:

    MOCK_CONST_METHOD0(tag, uint16_t());

};

}



using namespace Exiv2;



class IptcdatumTest_673 : public ::testing::Test {

protected:

    std::unique_ptr<MockIptcKey> mockKey;

    Iptcdatum* iptcdatum;



    void SetUp() override {

        mockKey = std::make_unique<MockIptcKey>();

        iptcdatum = new Iptcdatum(*mockKey, nullptr);

    }



    void TearDown() override {

        delete iptcdatum;

    }

};



TEST_F(IptcdatumTest_673, TagReturnsCorrectValue_673) {

    EXPECT_CALL(*mockKey, tag()).WillOnce(::testing::Return(123));

    EXPECT_EQ(iptcdatum->tag(), 123);

}



TEST_F(IptcdatumTest_673, TagReturnsZeroWhenKeyIsNull_673) {

    Iptcdatum iptcdatumNull(nullptr, nullptr);

    EXPECT_EQ(iptcdatumNull.tag(), 0);

}

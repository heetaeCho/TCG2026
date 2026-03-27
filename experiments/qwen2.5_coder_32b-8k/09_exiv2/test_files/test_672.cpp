#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/datasets.hpp"



using namespace Exiv2;

using ::testing::NiceMock;



class MockIptcKey : public IptcKey {

public:

    MOCK_CONST_METHOD0(tagDesc, std::string());

};



class IptcdatumTest_672 : public ::testing::Test {

protected:

    NiceMock<MockIptcKey> mockKey;

    Iptcdatum iptcdatum;



    IptcdatumTest_672() : iptcdatum(mockKey, nullptr) {}

};



TEST_F(IptcdatumTest_672, TagDesc_ReturnsCorrectValue_672) {

    EXPECT_CALL(mockKey, tagDesc()).WillOnce(::testing::Return("ExpectedTagDescription"));

    EXPECT_EQ(iptcdatum.tagDesc(), "ExpectedTagDescription");

}



TEST_F(IptcdatumTest_672, TagDesc_ReturnsEmptyStringWhenKeyIsNull_672) {

    Iptcdatum iptcdatumNull(nullptr);

    EXPECT_EQ(iptcdatumNull.tagDesc(), "");

}

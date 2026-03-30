#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

namespace Exiv2 {

class XmpData {
public:
    const std::string& xmpPacket() const { return xmpPacket_; }
    bool usePacket() const { return usePacket_; }
    bool usePacket(bool b) { return usePacket_ = b; }
    void setPacket(std::string xmpPacket) { xmpPacket_ = std::move(xmpPacket); }

private:
    std::string xmpPacket_;
    bool usePacket_ = false;
};

// Test Fixture for XmpData
class XmpDataTest : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData;
};

// Test 1: Verify that xmpPacket returns an empty string initially
TEST_F(XmpDataTest, XmpPacketInitialValue_52) {
    EXPECT_EQ(xmpData.xmpPacket(), "");
}

// Test 2: Test that setting a new xmpPacket updates the packet correctly
TEST_F(XmpDataTest, SetXmpPacket_52) {
    std::string newPacket = "new_xmp_packet";
    xmpData.setPacket(newPacket);
    EXPECT_EQ(xmpData.xmpPacket(), newPacket);
}

// Test 3: Verify that usePacket initially returns false
TEST_F(XmpDataTest, UsePacketInitialValue_52) {
    EXPECT_FALSE(xmpData.usePacket());
}

// Test 4: Verify that usePacket can be set to true and false
TEST_F(XmpDataTest, UsePacketSetter_52) {
    xmpData.usePacket(true);
    EXPECT_TRUE(xmpData.usePacket());

    xmpData.usePacket(false);
    EXPECT_FALSE(xmpData.usePacket());
}

}  // namespace Exiv2
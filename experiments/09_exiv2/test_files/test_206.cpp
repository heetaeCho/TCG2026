#include <gtest/gtest.h>

#include <string>



// Mock implementation of Tag class to simulate behavior based on provided context

class Tag {

public:

    Tag(const std::string& name) : name_(name) {}



    const std::string& name() const { return name_; }



private:

    std::string name_;

};



// Assuming a function getLensName(int tagValue) that returns the lens name based on the provided tag value

std::string getLensName(int tagValue) {

    // This is a mock implementation, in real code this would search through a map or array similar to pentax_lens_tags[]

    switch (tagValue) {

        case 768: return "smc PENTAX-FA* 250-600mm F5.6 ED[IF]";

        case 1539: return "smc PENTAX-FA* 300mm F2.8 ED[IF]";

        case 1792: return "smc PENTAX-DA 21mm F3.2 AL Limited";

        case 2064: return "Sigma 50-500mm F4.5-6.3 DG OS HSM";

        case 3348: return "HD PENTAX-D FA 645 90mm F2.8 ED AW SR";

        default: return "Unknown Lens";

    }

}



// Test cases to verify the getLensName function

TEST(PentaxLensTest, TestKnownTags) {

    EXPECT_EQ(getLensName(768), "smc PENTAX-FA* 250-600mm F5.6 ED[IF]");

    EXPECT_EQ(getLensName(1539), "smc PENTAX-FA* 300mm F2.8 ED[IF]");

    EXPECT_EQ(getLensName(1792), "smc PENTAX-DA 21mm F3.2 AL Limited");

    EXPECT_EQ(getLensName(2064), "Sigma 50-500mm F4.5-6.3 DG OS HSM");

    EXPECT_EQ(getLensName(3348), "HD PENTAX-D FA 645 90mm F2.8 ED AW SR");

}



TEST(PentaxLensTest, TestUnknownTag) {

    EXPECT_EQ(getLensName(9999), "Unknown Lens"); // Assuming 9999 is not a valid tag

}

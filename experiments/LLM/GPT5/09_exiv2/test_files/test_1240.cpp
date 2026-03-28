#include <gtest/gtest.h>
#include <string>

// Assuming the necessary Exiv2 headers are included
namespace Exiv2 {

    // Mocking the XmpNsInfo structure
    struct XmpNsInfo {
    public:
        const char *ns_;
        const char *prefix_;
        const XmpPropertyInfo *xmpPropertyInfo_;

        struct Ns {
            std::string ns_;
        };

        bool operator==(const Ns &ns) const {
            return ns_ == ns.ns_;
        }

        bool operator==(const Prefix &prefix) const {
            return prefix_ == prefix.prefix_;
        }

        bool operator==(const XmpNsInfo::Ns& ns) const {
            return ns_ == ns.ns_;
        }

        bool operator==(const XmpNsInfo::Prefix& prefix) const {
            return prefix_ == prefix.prefix_;
        }
    };

    struct Prefix {
        std::string prefix_;
    };

    struct XmpPropertyInfo {};

}

TEST_F(XmpNsInfoTest_1240, EqualityOperatorNs_1240) {
    // Test the equality of two XmpNsInfo objects based on the Ns object

    Exiv2::XmpNsInfo ns1;
    ns1.ns_ = "namespace1";

    Exiv2::XmpNsInfo::Ns ns2;
    ns2.ns_ = "namespace1";

    EXPECT_TRUE(ns1 == ns2);
}

TEST_F(XmpNsInfoTest_1241, InequalityOperatorNs_1241) {
    // Test the inequality of two XmpNsInfo objects based on the Ns object

    Exiv2::XmpNsInfo ns1;
    ns1.ns_ = "namespace1";

    Exiv2::XmpNsInfo::Ns ns2;
    ns2.ns_ = "namespace2";

    EXPECT_FALSE(ns1 == ns2);
}

TEST_F(XmpNsInfoTest_1242, EqualityOperatorPrefix_1242) {
    // Test the equality of two XmpNsInfo objects based on the Prefix object

    Exiv2::XmpNsInfo ns1;
    ns1.prefix_ = "prefix1";

    Exiv2::Prefix prefix2;
    prefix2.prefix_ = "prefix1";

    EXPECT_TRUE(ns1 == prefix2);
}

TEST_F(XmpNsInfoTest_1243, InequalityOperatorPrefix_1243) {
    // Test the inequality of two XmpNsInfo objects based on the Prefix object

    Exiv2::XmpNsInfo ns1;
    ns1.prefix_ = "prefix1";

    Exiv2::Prefix prefix2;
    prefix2.prefix_ = "prefix2";

    EXPECT_FALSE(ns1 == prefix2);
}

TEST_F(XmpNsInfoTest_1244, EqualityOperatorXmpNsInfo_1244) {
    // Test the equality of two XmpNsInfo objects

    Exiv2::XmpNsInfo ns1;
    ns1.ns_ = "namespace1";

    Exiv2::XmpNsInfo ns2;
    ns2.ns_ = "namespace1";

    EXPECT_TRUE(ns1 == ns2);
}

TEST_F(XmpNsInfoTest_1245, InequalityOperatorXmpNsInfo_1245) {
    // Test the inequality of two XmpNsInfo objects

    Exiv2::XmpNsInfo ns1;
    ns1.ns_ = "namespace1";

    Exiv2::XmpNsInfo ns2;
    ns2.ns_ = "namespace2";

    EXPECT_FALSE(ns1 == ns2);
}

}  // namespace Exiv2
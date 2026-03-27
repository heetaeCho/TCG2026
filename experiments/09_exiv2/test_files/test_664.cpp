#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/iptc.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::MockFunction;



class IptcdatumTest : public ::testing::Test {

protected:

    MockFunction<std::ostream&(std::ostream&, const std::string&)> mockWriteString;

    Iptcdatum iptcdatum;



    void SetUp() override {

        // No setup needed for this simple test case

    }



    void TearDown() override {

        // No teardown needed for this simple test case

    }

};



TEST_F(IptcdatumTest_664, WriteOutputsValue_664) {

    std::ostringstream os;

    EXPECT_CALL(mockWriteString, Call(os, iptcdatum.value()))

        .WillOnce(testing::Invoke([](std::ostream& os, const std::string& value) -> std::ostream& {

            return os << value;

        }));



    std::ostream& result = iptcdatum.write(os, nullptr);

    EXPECT_EQ(result.str(), iptcdatum.value());

}



TEST_F(IptcdatumTest_664, WriteWithNullExifData_664) {

    std::ostringstream os;

    std::string expectedValue = iptcdatum.value();

    std::ostream& result = iptcdatum.write(os, nullptr);

    EXPECT_EQ(result.str(), expectedValue);

}



// Assuming value() returns a non-empty string by default

TEST_F(IptcdatumTest_664, WriteNonEmptyValue_664) {

    std::ostringstream os;

    std::string expectedValue = iptcdatum.value();

    ASSERT_FALSE(expectedValue.empty());

    std::ostream& result = iptcdatum.write(os, nullptr);

    EXPECT_EQ(result.str(), expectedValue);

}



// Assuming value() can return an empty string

TEST_F(IptcdatumTest_664, WriteEmptyValue_664) {

    std::ostringstream os;

    EXPECT_CALL(mockWriteString, Call(os, ""))

        .WillOnce(testing::Invoke([](std::ostream& os, const std::string& value) -> std::ostream& {

            return os << value;

        }));



    iptcdatum = Iptcdatum(); // Reset or set to an empty value if possible

    std::string expectedValue = iptcdatum.value();

    ASSERT_TRUE(expectedValue.empty());

    std::ostream& result = iptcdatum.write(os, nullptr);

    EXPECT_EQ(result.str(), expectedValue);

}

```



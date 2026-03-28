#include <gtest/gtest.h>
#include <memory>
#include "xmp_exiv2.hpp"  // Assuming the full path is used here

namespace Exiv2 {

class XmpdatumTest_1290 : public ::testing::Test {
protected:
    // Setup any common data used across tests, if necessary.
};

TEST_F(XmpdatumTest_1290, SizeReturnsZeroWhenNoValue) {
    // TEST_ID: 1290
    // Verifying that the size function returns 0 when there is no value (nullptr).
    Xmpdatum xmpDatum(XmpKey(), nullptr);

    EXPECT_EQ(xmpDatum.size(), 0);
}

TEST_F(XmpdatumTest_1290, SizeReturnsValueSizeWhenValueIsPresent) {
    // TEST_ID: 1291
    // Verifying that the size function returns the correct size when a valid value is set.
    XmpKey key("TestKey");
    std::unique_ptr<Value> value = std::make_unique<Value>(TypeId::kString);
    value->setDataArea(reinterpret_cast<const byte*>("Test data"), 9); // Simulate a value with 9 bytes

    Xmpdatum xmpDatum(key, value.get());

    EXPECT_EQ(xmpDatum.size(), 9);
}

TEST_F(XmpdatumTest_1290, SizeReturnsZeroWhenValueIsEmpty) {
    // TEST_ID: 1292
    // Verifying that the size function returns 0 when the value is empty.
    XmpKey key("TestKey");
    std::unique_ptr<Value> value = std::make_unique<Value>(TypeId::kString);
    value->setDataArea(reinterpret_cast<const byte*>(""), 0); // Empty value

    Xmpdatum xmpDatum(key, value.get());

    EXPECT_EQ(xmpDatum.size(), 0);
}

TEST_F(XmpdatumTest_1290, SizeThrowsExceptionWhenValueIsCorrupted) {
    // TEST_ID: 1293
    // Verifying that an exception is thrown when the internal value is corrupted (invalid data).
    XmpKey key("TestKey");
    std::unique_ptr<Value> value = std::make_unique<Value>(TypeId::kString);
    // Intentionally setting invalid data
    value->setDataArea(nullptr, 0);

    Xmpdatum xmpDatum(key, value.get());

    EXPECT_THROW(xmpDatum.size(), std::runtime_error);  // Assuming the implementation throws std::runtime_error for such cases
}

}  // namespace Exiv2
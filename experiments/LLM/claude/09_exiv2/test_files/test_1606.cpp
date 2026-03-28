#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <cstdint>
#include <string>
#include <vector>

// We need access to the findLensSpecFlags function which is in an anonymous/static context
// within the Internal namespace. Since it's static, we need to include the source or
// declare it. Let's include the necessary headers and use a workaround.

// Forward declaration approach - since the function is static in the .cpp file,
// we'll need to include the actual source to test it.
// We include the source file to get access to the static function.
#include "sonymn_int.cpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper class to create a Value with specific uint32 values at specific indices
class TestValue : public Value {
 public:
  TestValue() : Value(TypeId::unsignedShort) {}
  
  void setValues(const std::vector<uint32_t>& vals) {
    values_ = vals;
  }
  
  int read(const byte* buf, size_t len, ByteOrder byteOrder) override { return 0; }
  int read(const std::string& buf) override { return 0; }
  size_t copy(byte* buf, ByteOrder byteOrder) const override { return 0; }
  size_t count() const override { return values_.size(); }
  size_t size() const override { return values_.size() * 4; }
  std::ostream& write(std::ostream& os) const override { return os; }
  
  int64_t toInt64(size_t n) const override {
    if (n < values_.size()) return static_cast<int64_t>(values_[n]);
    return 0;
  }
  
  uint32_t toUint32(size_t n) const override {
    if (n < values_.size()) return values_[n];
    return 0;
  }
  
  float toFloat(size_t n) const override { return 0.0f; }
  Rational toRational(size_t n) const override { return {0, 1}; }
  
  UniquePtr clone() const {
    auto p = std::make_unique<TestValue>();
    p->setValues(values_);
    return p;
  }
  
 private:
  const Value* clone_() const override {
    return new TestValue(*this);
  }
  std::vector<uint32_t> values_;
};

class FindLensSpecFlagsTest_1606 : public ::testing::Test {
 protected:
  void SetUp() override {
    flagsStart.clear();
    flagsEnd.clear();
  }
  
  // Helper to create a TestValue with value[0] and value[7] set
  // joinedV0V7 = (value[0] << 8) + value[7]
  // So to get a specific joinedV0V7, we set value[0] = high byte, value[7] = low byte
  TestValue createValue(uint32_t v0, uint32_t v7) {
    TestValue val;
    std::vector<uint32_t> vals(8, 0);
    vals[0] = v0;
    vals[7] = v7;
    val.setValues(vals);
    return val;
  }
  
  // Create value from a desired joinedV0V7 directly
  TestValue createValueFromJoined(uint32_t joined) {
    uint32_t v0 = (joined >> 8) & 0xFF;
    uint32_t v7 = joined & 0xFF;
    // But joined could be > 0xFFFF, so handle higher bits too
    // Actually v0 could be larger if joined has bits beyond 16
    // joinedV0V7 = (value[0] << 8) + value[7]
    // value[0] can be any uint32, so v0 = joined >> 8, v7 = joined & 0xFF
    // But then (v0 << 8) + v7 = (joined >> 8) << 8 + (joined & 0xFF)
    // = joined & ~0xFF + joined & 0xFF = joined only if no overflow
    // Actually: (joined >> 8) << 8 = joined & 0xFFFFFF00
    // So (joined & 0xFFFFFF00) + (joined & 0xFF) = joined. This works!
    v0 = joined >> 8;
    v7 = joined & 0xFF;
    return createValue(v0, v7);
  }
  
  std::string flagsStart;
  std::string flagsEnd;
};

// Test with all zeros - no flags should be set
TEST_F(FindLensSpecFlagsTest_1606, AllZeros_NoFlags_1606) {
  auto val = createValueFromJoined(0x0000);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_TRUE(flagsEnd.empty());
}

// Test PZ flag (0x4000, prepend)
TEST_F(FindLensSpecFlagsTest_1606, PZFlag_1606) {
  auto val = createValueFromJoined(0x4000);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsStart, "PZ");
  EXPECT_TRUE(flagsEnd.empty());
}

// Test DT flag (0x0100, prepend)
TEST_F(FindLensSpecFlagsTest_1606, DTFlag_1606) {
  auto val = createValueFromJoined(0x0100);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsStart, "DT");
  EXPECT_TRUE(flagsEnd.empty());
}

// Test FE flag (0x0200, prepend)
TEST_F(FindLensSpecFlagsTest_1606, FEFlag_1606) {
  auto val = createValueFromJoined(0x0200);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsStart, "FE");
  EXPECT_TRUE(flagsEnd.empty());
}

// Test E flag (0x0300, prepend)
TEST_F(FindLensSpecFlagsTest_1606, EFlag_1606) {
  auto val = createValueFromJoined(0x0300);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsStart, "E");
  EXPECT_TRUE(flagsEnd.empty());
}

// Test STF flag (0x0020, append)
TEST_F(FindLensSpecFlagsTest_1606, STFFlag_1606) {
  auto val = createValueFromJoined(0x0020);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "STF");
}

// Test Reflex flag (0x0040, append)
TEST_F(FindLensSpecFlagsTest_1606, ReflexFlag_1606) {
  auto val = createValueFromJoined(0x0040);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  // Reflex might be translated via N_(), but in test context it should be "Reflex"
  EXPECT_FALSE(flagsEnd.empty());
}

// Test Macro flag (0x0060, append)
TEST_F(FindLensSpecFlagsTest_1606, MacroFlag_1606) {
  auto val = createValueFromJoined(0x0060);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_FALSE(flagsEnd.empty());
}

// Test Fisheye flag (0x0080, append)
TEST_F(FindLensSpecFlagsTest_1606, FisheyeFlag_1606) {
  auto val = createValueFromJoined(0x0080);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_FALSE(flagsEnd.empty());
}

// Test ZA flag (0x0004, append)
TEST_F(FindLensSpecFlagsTest_1606, ZAFlag_1606) {
  auto val = createValueFromJoined(0x0004);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "ZA");
}

// Test G flag (0x0008, append)
TEST_F(FindLensSpecFlagsTest_1606, GFlag_1606) {
  auto val = createValueFromJoined(0x0008);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "G");
}

// Test SSM flag (0x0001, append)
TEST_F(FindLensSpecFlagsTest_1606, SSMFlag_1606) {
  auto val = createValueFromJoined(0x0001);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "SSM");
}

// Test SAM flag (0x0002, append)
TEST_F(FindLensSpecFlagsTest_1606, SAMFlag_1606) {
  auto val = createValueFromJoined(0x0002);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "SAM");
}

// Test OSS flag (0x8000, append)
TEST_F(FindLensSpecFlagsTest_1606, OSSFlag_1606) {
  auto val = createValueFromJoined(0x8000);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "OSS");
}

// Test LE flag (0x2000, append)
TEST_F(FindLensSpecFlagsTest_1606, LEFlag_1606) {
  auto val = createValueFromJoined(0x2000);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "LE");
}

// Test II flag (0x0800, append)
TEST_F(FindLensSpecFlagsTest_1606, IIFlag_1606) {
  auto val = createValueFromJoined(0x0800);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "II");
}

// Test combined PZ + DT flags (prepend flags combined)
TEST_F(FindLensSpecFlagsTest_1606, PZAndDTCombined_1606) {
  auto val = createValueFromJoined(0x4100);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  // PZ is processed first (prepend), then DT (prepend)
  // PZ sets flagsStart = "PZ"
  // DT: flagsStart = "DT PZ" (since format is "{} {}", f->label_, flagsStart)
  // Wait, the code says: stringFormat("{} {}", f->label_, flagsStart)
  // So for DT: stringFormat("{} {}", "DT", "PZ") = "DT PZ"
  EXPECT_EQ(flagsStart, "DT PZ");
  EXPECT_TRUE(flagsEnd.empty());
}

// Test combined PZ + E flags
TEST_F(FindLensSpecFlagsTest_1606, PZAndECombined_1606) {
  auto val = createValueFromJoined(0x4300);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsStart, "E PZ");
  EXPECT_TRUE(flagsEnd.empty());
}

// Test combined append flags: ZA + SSM
TEST_F(FindLensSpecFlagsTest_1606, ZAAndSSMCombined_1606) {
  auto val = createValueFromJoined(0x0005);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  // ZA processed first, then SSM
  // ZA: flagsEnd = "ZA"
  // SSM: flagsEnd = "ZA SSM" (stringFormat("{} {}", flagsEnd, f->label_))
  EXPECT_EQ(flagsEnd, "ZA SSM");
}

// Test combined prepend and append flags: DT + G + SSM
TEST_F(FindLensSpecFlagsTest_1606, DTAndGAndSSMCombined_1606) {
  auto val = createValueFromJoined(0x0109);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsStart, "DT");
  EXPECT_EQ(flagsEnd, "G SSM");
}

// Test combined: PZ + E + STF + ZA + SSM + OSS + LE + II
TEST_F(FindLensSpecFlagsTest_1606, AllFlagsCombined_1606) {
  // PZ=0x4000, E=0x0300, STF=0x0020, ZA=0x0004, SSM=0x0001, OSS=0x8000, LE=0x2000, II=0x0800
  uint32_t joined = 0x4000 | 0x0300 | 0x0020 | 0x0004 | 0x0001 | 0x8000 | 0x2000 | 0x0800;
  auto val = createValueFromJoined(joined);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  // Prepend: PZ first, then E -> "E PZ"
  EXPECT_EQ(flagsStart, "E PZ");
  // Append: STF, ZA, SSM, OSS, LE, II in order
  EXPECT_EQ(flagsEnd, "STF ZA SSM OSS LE II");
}

// Test that an invalid mask/flag combination throws an error
// For the mask 0x00e0, if we set bits that don't match any defined flag
// e.g., 0x00a0 masked with 0x00e0 = 0x00a0, which isn't in {0x0020, 0x0040, 0x0060, 0x0080}
TEST_F(FindLensSpecFlagsTest_1606, InvalidFlagThrowsError_1606) {
  // 0x00a0 has bits 0x0080 | 0x0020 = 0x00a0
  // mask 0x00e0 & 0x00a0 = 0x00a0, which is not in the flags array
  auto val = createValueFromJoined(0x00a0);
  EXPECT_THROW(findLensSpecFlags(val, flagsStart, flagsEnd), Error);
}

// Test another invalid combination for mask 0x000c
// 0x000c masked gives 0x000c which is not in {0x0004, 0x0008}
TEST_F(FindLensSpecFlagsTest_1606, InvalidFlagMask000cThrowsError_1606) {
  auto val = createValueFromJoined(0x000c);
  EXPECT_THROW(findLensSpecFlags(val, flagsStart, flagsEnd), Error);
}

// Test another invalid combination for mask 0x0003
// 0x0003 masked gives 0x0003 which is not in {0x0001, 0x0002}
TEST_F(FindLensSpecFlagsTest_1606, InvalidFlagMask0003ThrowsError_1606) {
  auto val = createValueFromJoined(0x0003);
  EXPECT_THROW(findLensSpecFlags(val, flagsStart, flagsEnd), Error);
}

// Test invalid combination for mask 0x00e0 with value 0x00c0
TEST_F(FindLensSpecFlagsTest_1606, InvalidFlagMask00e0WithC0ThrowsError_1606) {
  auto val = createValueFromJoined(0x00c0);
  EXPECT_THROW(findLensSpecFlags(val, flagsStart, flagsEnd), Error);
}

// Test invalid combination for mask 0x00e0 with value 0x00e0
TEST_F(FindLensSpecFlagsTest_1606, InvalidFlagMask00e0WithE0ThrowsError_1606) {
  auto val = createValueFromJoined(0x00e0);
  EXPECT_THROW(findLensSpecFlags(val, flagsStart, flagsEnd), Error);
}

// Test that value[0] contributes to high byte and value[7] to low byte
TEST_F(FindLensSpecFlagsTest_1606, ValueIndexMapping_1606) {
  // SSM = 0x0001, should come from value[7] = 1, value[0] = 0
  auto val = createValue(0, 1);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsEnd, "SSM");
}

// Test that value[0] = 0x40 gives PZ (0x40 << 8 = 0x4000)
TEST_F(FindLensSpecFlagsTest_1606, Value0GivesPZ_1606) {
  auto val = createValue(0x40, 0);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsStart, "PZ");
}

// Test FE + G combination
TEST_F(FindLensSpecFlagsTest_1606, FEAndGCombined_1606) {
  auto val = createValueFromJoined(0x0208);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsStart, "FE");
  EXPECT_EQ(flagsEnd, "G");
}

// Test OSS alone with higher bits
TEST_F(FindLensSpecFlagsTest_1606, OSSAloneHighBit_1606) {
  // OSS = 0x8000, value[0] = 0x80, value[7] = 0
  auto val = createValue(0x80, 0);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsEnd, "OSS");
}

// Test LE alone
TEST_F(FindLensSpecFlagsTest_1606, LEAlone_1606) {
  // LE = 0x2000, value[0] = 0x20, value[7] = 0
  auto val = createValue(0x20, 0);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsEnd, "LE");
}

// Test II alone
TEST_F(FindLensSpecFlagsTest_1606, IIAlone_1606) {
  // II = 0x0800, value[0] = 0x08, value[7] = 0
  auto val = createValue(0x08, 0);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_EQ(flagsEnd, "II");
}

// Test multiple append flags in correct order: STF + G + SAM + OSS + LE + II
TEST_F(FindLensSpecFlagsTest_1606, MultipleAppendFlagsOrder_1606) {
  // STF=0x0020, G=0x0008, SAM=0x0002, OSS=0x8000, LE=0x2000, II=0x0800
  uint32_t joined = 0x0020 | 0x0008 | 0x0002 | 0x8000 | 0x2000 | 0x0800;
  auto val = createValueFromJoined(joined);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  EXPECT_TRUE(flagsStart.empty());
  EXPECT_EQ(flagsEnd, "STF G SAM OSS LE II");
}

// Test PZ + FE combined (both prepend)
TEST_F(FindLensSpecFlagsTest_1606, PZAndFECombined_1606) {
  auto val = createValueFromJoined(0x4200);
  findLensSpecFlags(val, flagsStart, flagsEnd);
  // PZ first -> flagsStart = "PZ"
  // FE next (prepend) -> flagsStart = "FE PZ"
  EXPECT_EQ(flagsStart, "FE PZ");
  EXPECT_TRUE(flagsEnd.empty());
}

// ============================================================================
// tests_casio2_mnheader_1508.cpp
// Unit tests for Exiv2::Internal::Casio2MnHeader (makernote_int.cpp)
// TEST_ID: 1508
// ============================================================================

#include <gtest/gtest.h>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Exiv2 {

// Minimal enums/types used by the interface under test.
enum ByteOrder { littleEndian, bigEndian };

// External collaborator interface (only what the CUT needs).
class IoWrapper {
 public:
  virtual ~IoWrapper() = default;
  virtual void write(const void* data, size_t size) = 0;
};

namespace Internal {

// Forward declare class under test with the method we are testing.
// The real implementation is in the codebase; this is only a declaration.
class Casio2MnHeader {
 public:
  size_t write(IoWrapper& ioWrapper, ByteOrder byteOrder) const;
};

}  // namespace Internal
}  // namespace Exiv2

// --------------------------- Test doubles ----------------------------------

// Captures calls to IoWrapper::write without assuming anything about internals.
class CapturingIoWrapper final : public Exiv2::IoWrapper {
 public:
  struct Call {
    const void* dataPtr;
    size_t size;
  };

  void write(const void* data, size_t size) override {
    calls_.push_back(Call{data, size});
  }

  const std::vector<Call>& calls() const { return calls_; }

 private:
  std::vector<Call> calls_;
};

namespace {

class Casio2MnHeaderTest_1508 : public ::testing::Test {
 protected:
  Exiv2::Internal::Casio2MnHeader header_;
};

TEST_F(Casio2MnHeaderTest_1508, WriteReturnsValueAndInvokesIoWriteExactlyOnce_1508) {
  CapturingIoWrapper io;

  const size_t ret = header_.write(io, Exiv2::littleEndian);

  // Observable behavior: should invoke io.write(...) and return some size.
  ASSERT_EQ(io.calls().size(), 1u);
  EXPECT_EQ(io.calls()[0].size, ret);
}

TEST_F(Casio2MnHeaderTest_1508, WriteIsDeterministicForSameInputs_1508) {
  CapturingIoWrapper io1;
  CapturingIoWrapper io2;

  const size_t r1 = header_.write(io1, Exiv2::bigEndian);
  const size_t r2 = header_.write(io2, Exiv2::bigEndian);

  ASSERT_EQ(io1.calls().size(), 1u);
  ASSERT_EQ(io2.calls().size(), 1u);

  // Boundary/consistency: returned size should be stable for the same call shape.
  EXPECT_EQ(r1, r2);
  EXPECT_EQ(io1.calls()[0].size, r1);
  EXPECT_EQ(io2.calls()[0].size, r2);
}

TEST_F(Casio2MnHeaderTest_1508, WriteIgnoresByteOrderInObservableEffects_1508) {
  CapturingIoWrapper ioLe;
  CapturingIoWrapper ioBe;

  const size_t rLe = header_.write(ioLe, Exiv2::littleEndian);
  const size_t rBe = header_.write(ioBe, Exiv2::bigEndian);

  ASSERT_EQ(ioLe.calls().size(), 1u);
  ASSERT_EQ(ioBe.calls().size(), 1u);

  // Based on the given interface snippet, ByteOrder is not used to compute size.
  // Observable expectations: size/return should match.
  EXPECT_EQ(rLe, rBe);
  EXPECT_EQ(ioLe.calls()[0].size, rLe);
  EXPECT_EQ(ioBe.calls()[0].size, rBe);
}

TEST_F(Casio2MnHeaderTest_1508, WriteProvidesNonNullBufferPointerWhenSizeNonZero_1508) {
  CapturingIoWrapper io;

  const size_t ret = header_.write(io, Exiv2::littleEndian);

  ASSERT_EQ(io.calls().size(), 1u);
  // Boundary condition: if a non-zero size is written, pointer should be non-null.
  if (ret != 0u) {
    EXPECT_NE(io.calls()[0].dataPtr, nullptr);
  }
}

}  // namespace
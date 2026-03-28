// File: status_printer_set_explanations_test.cc

#include "gtest/gtest.h"

#include "status_printer.h"
#include "explanations.h"

// NOTE:
// We treat StatusPrinter as a black box.
// These tests only verify observable, interface-level behavior of SetExplanations,
// without accessing private members or assuming internal implementation details.

TEST(StatusPrinterTest_127, SetExplanationsAcceptsNullPointer_127) {
  // Arrange
  BuildConfig config = BuildConfig();  // value-initialize (safe zero-init for POD)
  StatusPrinter printer(config);

  // Act: calling with nullptr must be allowed and not crash.
  printer.SetExplanations(nullptr);

  // Also exercise a typical usage sequence to ensure no adverse effects.
  printer.BuildStarted();
  printer.BuildFinished();

  SUCCEED();  // If we reach here, the behavior is acceptable.
}

TEST(StatusPrinterTest_127, SetExplanationsAcceptsNonNullPointer_127) {
  // Arrange
  BuildConfig config = BuildConfig();
  StatusPrinter printer(config);
  Explanations explanations;

  // Act: calling with a valid pointer must be allowed and not crash.
  printer.SetExplanations(&explanations);

  // Again, run through a simple lifecycle to ensure no unexpected issues.
  printer.BuildStarted();
  printer.BuildFinished();

  SUCCEED();
}

TEST(StatusPrinterTest_127, SetExplanationsCanBeCalledMultipleTimes_127) {
  // Arrange
  BuildConfig config = BuildConfig();
  StatusPrinter printer(config);
  Explanations explanations1;
  Explanations explanations2;

  // Act: SetExplanations should safely accept multiple calls,
  // changing the explanations instance over time.
  printer.SetExplanations(&explanations1);
  printer.SetExplanations(&explanations2);
  printer.SetExplanations(nullptr);  // And back to nullptr is also allowed.

  // Exercise a basic lifecycle to ensure everything still works.
  printer.BuildStarted();
  printer.BuildFinished();

  SUCCEED();
}

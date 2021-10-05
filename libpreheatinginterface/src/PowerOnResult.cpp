#include "LibPreheatingInterface.hpp"

LibPreheatingInterface::PowerOnResult::PowerOnResult(PreheatingAnswer result) : result(result) {}

bool LibPreheatingInterface::PowerOnResult::IsSuccessful() {
  return result.CountGreenFlashesBetween(1000, 2500) == 2;
}
bool LibPreheatingInterface::PowerOnResult::IsError() {
  return !IsSuccessful();
}
bool LibPreheatingInterface::PowerOnResult::IsLowBattery() {
  return result.CountRedFlashesBetween(50, 400) > 3;
}
bool LibPreheatingInterface::PowerOnResult::IsOutOfRange() {
  return result.CountGreenFlashesBetween(50, 400) > 3;
}


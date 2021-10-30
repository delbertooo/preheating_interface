#include "LibPreheatingInterface.hpp"

LibPreheatingInterface::PowerOffResult::PowerOffResult(PreheatingAnswer result) : result(result) {}

bool LibPreheatingInterface::PowerOffResult::IsSuccessful() {
  return result.CountRedFlashesBetween(1000, 2500) == 2;
}
bool LibPreheatingInterface::PowerOffResult::IsError() {
  return !IsSuccessful();
}
bool LibPreheatingInterface::PowerOffResult::IsOutOfRange() {
  return result.CountRedFlashesBetween(50, 400) > 3;
}

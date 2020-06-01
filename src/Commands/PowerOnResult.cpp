#include "PowerOnCommand.hpp"

Commands::PowerOnResult::PowerOnResult(HardwareInterface::PreheatingAnswer result) : result(result) {}

bool Commands::PowerOnResult::IsSuccessful() {
  return result.CountGreenFlashesBetween(1000, 2500) == 2;
}
bool Commands::PowerOnResult::IsError() {
  return !IsSuccessful();
}
bool Commands::PowerOnResult::IsLowBattery() {
  return result.CountRedFlashesBetween(50, 400) > 3;
}
bool Commands::PowerOnResult::IsOutOfRange() {
  return result.CountGreenFlashesBetween(50, 400) > 3;
}


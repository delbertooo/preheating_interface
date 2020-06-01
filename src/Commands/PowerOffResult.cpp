#include "PowerOffCommand.hpp"

Commands::PowerOffResult::PowerOffResult(HardwareInterface::PreheatingAnswer result) : result(result) {}

bool Commands::PowerOffResult::IsSuccessful() {
  return result.CountRedFlashesBetween(1000, 2500) == 2;
}
bool Commands::PowerOffResult::IsError() {
  return !IsSuccessful();
}
bool Commands::PowerOffResult::IsOutOfRange() {
  return result.CountRedFlashesBetween(50, 400) > 3;
}

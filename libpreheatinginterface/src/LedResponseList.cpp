#include "LibPreheatingInterface.hpp"


LibPreheatingInterface::LedResponseList::LedResponseList() : alreadyEnabled(false) { }

std::vector<unsigned long> LibPreheatingInterface::LedResponseList::EnabledTimes() {
  return enabledTimes;
}

void LibPreheatingInterface::LedResponseList::AddValue(unsigned long millis, bool enabled) {
  if (enabled && !alreadyEnabled) {
    alreadyEnabled = true;
    enabledStartMillis = millis;
  } else if (!enabled && alreadyEnabled) {
    alreadyEnabled = false;
    unsigned long elapsed = millis - enabledStartMillis;
    if (elapsed >= MIN_ENABLED_TIME) {
      enabledTimes.push_back(elapsed);
    }
  }
}


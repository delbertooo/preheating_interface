#include "LibPreheatingInterface.hpp"

using namespace LibPreheatingInterface;


PreheatingAnswer::PreheatingAnswer(std::vector<unsigned long> greenFlashes, std::vector<unsigned long> redFlashes) : greenFlashes(greenFlashes), redFlashes(redFlashes) { }

unsigned int PreheatingAnswer::CountProcessorFlashesWithLength(std::vector<unsigned long> &flashes, unsigned long lengthInMilliseconds) {
  unsigned long thresh = lengthInMilliseconds * .1;
  unsigned long minTime = lengthInMilliseconds - thresh;
  unsigned long maxTime = lengthInMilliseconds + thresh;
  return CountProcessorFlashesWithLengthBetween(flashes, minTime, maxTime);
}

unsigned int PreheatingAnswer::CountProcessorFlashesWithLengthBetween(std::vector<unsigned long> &flashes, unsigned long minTime, unsigned long maxTime) {
  unsigned int num = 0;
  for (unsigned long &t : flashes) {
    if (t >= minTime && t <= maxTime) {
      ++num;
    }
  }
  return num;
}

unsigned int PreheatingAnswer::CountRedFlashesWithLength(unsigned long lengthInMilliseconds) {
  return CountProcessorFlashesWithLength(redFlashes, lengthInMilliseconds);
}

unsigned int PreheatingAnswer::CountGreenFlashesWithLength(unsigned long lengthInMilliseconds) {
  return CountProcessorFlashesWithLength(greenFlashes, lengthInMilliseconds);
}

unsigned int PreheatingAnswer::CountRedFlashesBetween(unsigned long minTime, unsigned long maxTime) {
  return CountProcessorFlashesWithLengthBetween(redFlashes, minTime, maxTime);
}
unsigned int PreheatingAnswer::CountGreenFlashesBetween(unsigned long minTime, unsigned long maxTime) {
  return CountProcessorFlashesWithLengthBetween(greenFlashes, minTime, maxTime);
}

#include <vector>
#include "Runnable.hpp"

#ifndef __PREHEATINGANSWER_HPP
#define __PREHEATINGANSWER_HPP 1

class PreheatingAnswer {
  private:
    std::vector<unsigned long> greenFlashes;
    std::vector<unsigned long> redFlashes;
    unsigned int CountProcessorFlashesWithLength(std::vector<unsigned long> &flashes, unsigned long lengthInMilliseconds);
  public:
    PreheatingAnswer(std::vector<unsigned long> greenFlashes, std::vector<unsigned long> redFlashes);
    unsigned int CountRedFlashesWithLength(unsigned long lengthInMilliseconds);
    unsigned int CountGreenFlashesWithLength(unsigned long lengthInMilliseconds);
};

PreheatingAnswer::PreheatingAnswer(std::vector<unsigned long> greenFlashes, std::vector<unsigned long> redFlashes) : greenFlashes(greenFlashes), redFlashes(redFlashes) { }

unsigned int PreheatingAnswer::CountProcessorFlashesWithLength(std::vector<unsigned long> &flashes, unsigned long lengthInMilliseconds) {
  unsigned long thresh = lengthInMilliseconds * .9;
  unsigned long minTime = lengthInMilliseconds - thresh;
  unsigned long maxTime = lengthInMilliseconds + thresh;
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

#endif

#include <StandardCplusplus.h>
#include <vector>
#include "Runnable/Runnable.hpp"

class PreheatingAnswer {
  private:
    std::vector<long> greenFlashes;
    std::vector<long> redFlashes;
    unsigned int CountProcessorFlashesWithLength(std::vector<long> &flashes, unsigned int lengthInMilliseconds);
  public:
    PreheatingAnswer(std::vector<long> greenFlashes, std::vector<long> redFlashes);
    unsigned int CountRedFlashesWithLength(unsigned long lengthInMilliseconds);
    unsigned int CountGreenFlashesWithLength(unsigned long lengthInMilliseconds);
};

PreheatingAnswer::PreheatingAnswer(std::vector<long> greenFlashes, std::vector<long> redFlashes) : greenFlashes(greenFlashes), redFlashes(redFlashes) { }

unsigned int PreheatingAnswer::CountProcessorFlashesWithLength(std::vector<long> &flashes, unsigned int lengthInMilliseconds) {
  unsigned int thresh = lengthInMilliseconds * .9;
  unsigned int minTime = lengthInMilliseconds - thresh;
  unsigned int maxTime = lengthInMilliseconds + thresh;
  unsigned int num = 0;
  for (long &t : flashes) {
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


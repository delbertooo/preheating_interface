#include <vector>

#ifndef __PREHEATINGANSWER_HPP
#define __PREHEATINGANSWER_HPP 1

namespace HardwareInterface {

  class PreheatingAnswer {
    private:
      std::vector<unsigned long> greenFlashes;
      std::vector<unsigned long> redFlashes;
      unsigned int CountProcessorFlashesWithLength(std::vector<unsigned long> &flashes, unsigned long lengthInMilliseconds);
      unsigned int CountProcessorFlashesWithLengthBetween(std::vector<unsigned long> &flashes, unsigned long minTime, unsigned long maxTime);
    public:
      PreheatingAnswer(std::vector<unsigned long> greenFlashes, std::vector<unsigned long> redFlashes);
      unsigned int CountRedFlashesWithLength(unsigned long lengthInMilliseconds);
      unsigned int CountGreenFlashesWithLength(unsigned long lengthInMilliseconds);
      unsigned int CountRedFlashesBetween(unsigned long minTime, unsigned long maxTime);
      unsigned int CountGreenFlashesBetween(unsigned long minTime, unsigned long maxTime);
  };

}

#endif

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

#endif

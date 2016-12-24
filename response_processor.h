#include <vector>

class ResponseProcessor {
  const int THRESHOLD_MIN = 200;
  const int THRESHOLD_MAX = 500;
  const int MIN_PRESSED_TIME = 10;
  bool alreadyPressed = false;
  std::vector<long> pressedTimes;
  unsigned long l;
  bool isPressed(int);
  public:
    ResponseProcessor();
    void addMeasurement(int);
    void printDebugOutput();
    //std::string toString();
    std::vector<long> getPressedTimes();
};


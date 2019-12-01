#pragma once

#include "PreheatingCommand.hpp"
#include "actions.hpp"

#ifndef __HS5_HPP
#define __HS5_HPP 1
class SwitchOnCommand : public PreheatingCommand {
  private:
    PressOnButton pressOnButton;
    ReleaseOnButton releaseOnButton;
    PressOffButton pressOffButton;
    ReleaseOffButton releaseOffButton;
  public:
    bool Run();
};

bool SwitchOnCommand::Run() {
  PreheatingAnswer heat_on = Execute(RunnableSequence().Run(pressOnButton).Wait(1000).Run(releaseOnButton).Wait(3000));
  if (heat_on.CountGreenFlashesWithLength(999) == 1 )
    {return true;}
    else
    {return false;}
}

class SwitchOffCommand : public PreheatingCommand {
  private:
    PressOffButton pressOffButton;
    ReleaseOffButton releaseOffButton;
  public:
    bool Run();
};

bool SwitchOffCommand::Run() {return Execute(RunnableSequence().Run(pressOffButton).Wait(1000).Run(releaseOffButton).Wait(3000)).CountRedFlashesWithLength(999) == 1;}

#endif

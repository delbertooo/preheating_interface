#include "LibPreheatingInterface.hpp"

using namespace LibPreheatingInterface;

PowerOnCommand::PowerOnCommand(CommandHelper &helper) : AbstractCommand(helper) {}

struct pressOn : public LibScheduling::Runnable
{
        LibPreheatingInterface::PreheatingRemote &remote;
        pressOn(LibPreheatingInterface::PreheatingRemote &remote) : remote(remote) {}
        void operator()() const override
        {
                remote.PressOn();
        }
};

struct releaseOn : public LibScheduling::Runnable
{
        LibPreheatingInterface::PreheatingRemote &remote;
        releaseOn(LibPreheatingInterface::PreheatingRemote &remote) : remote(remote) {}
        void operator()() const override
        {
                remote.ReleaseOn();
        }
};

PowerOnResult PowerOnCommand::PowerOn() {
return helper.Run(LibScheduling::RunnableSequence{}
        // .Run([this]() { remote.PressOn(); })
        .Run(pressOn{remote})
        .Wait(1000)
        // .Run([this]() { remote.ReleaseOn(); })
        .Run(releaseOn{remote})
        .Wait(3000));
}

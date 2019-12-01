#pragma once

class IPreheatingCommandResult {
  public:
    virtual bool IsError() = 0;
    virtual char* ErrorMessage() = 0;
};

class IPreheatingCommand {
  public:
    virtual IPreheatingCommandResult& Execute() = 0;
};


class PreheatingCommandResult : public IPreheatingCommandResult {
  private:
    char* message = NULL;
  public:
    PreheatingCommandResult(char* message) : message(message) { }
    bool IsError() override { return message != NULL; }
    char* ErrorMessage() override { return message; }
};

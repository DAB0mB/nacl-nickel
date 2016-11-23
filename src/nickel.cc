#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

using pp::Instance;
using pp::Module;
using pp::Var;
using std::string;

namespace {
  const char* const reqMessage = "nickel";
  const char* const resMessage = "Cha-Ching!";
}

class NickelInstance : public Instance {
 public:
  explicit NickelInstance(PP_Instance instance) : Instance(instance) {}
  virtual ~NickelInstance() {}

  virtual void HandleMessage(const Var& var_message) {
    if (!var_message.is_string()) return;

    string message = var_message.AsString();

    if (message == reqMessage) {
      Var var_reply(resMessage);
      PostMessage(var_reply);
    }
  }
};

class NickelModule : public Module {
 public:
  NickelModule() : Module() {}
  virtual ~NickelModule() {}

  virtual Instance* CreateInstance(PP_Instance instance) {
    return new NickelInstance(instance);
  }
};

namespace pp {
  Module* CreateModule() {
    return new NickelModule();
  }
}
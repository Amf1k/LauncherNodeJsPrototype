#include <napi.h>

#include "Launcher.hpp"
#include "LauncherWrapper.hpp"

Napi::Object Main(Napi::Env env, Napi::Object exports) {
  return amf::LauncherWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)

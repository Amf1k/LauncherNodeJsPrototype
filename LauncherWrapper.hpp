#ifndef LAUNCHERWRAPPER_HPP
#define LAUNCHERWRAPPER_HPP
#include <napi.h>

#include <QScopedPointer>

namespace amf {
class Launcher;
class LauncherWrapper : public Napi::ObjectWrap<LauncherWrapper> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  explicit LauncherWrapper(const Napi::CallbackInfo& info);
  Napi::Value exec(const Napi::CallbackInfo& info);
  Napi::Value startGame(const Napi::CallbackInfo& info);
  Napi::Value stopGame(const Napi::CallbackInfo& info);
  Napi::Value games(const Napi::CallbackInfo& info);
  Napi::Value CallAndEmit(const Napi::CallbackInfo& info);

  Napi::FunctionReference emitOnNode;

  void connectSignalsToEventEmitter();

 private:
  QScopedPointer<Launcher> _pLauncher;
};

}  // namespace amf
#endif  // LAUNCHERWRAPPER_HPP

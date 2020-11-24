#include "LauncherWrapper.hpp"

#include <QDebug>
#include <QObject>
#include <chrono>

#include "Game.hpp"
#include "Launcher.hpp"

Napi::Object amf::LauncherWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  Napi::Function func = DefineClass(
      env, "Launcher",
      {InstanceMethod("startGame", &amf::LauncherWrapper::startGame),
       InstanceMethod("stopGame", &amf::LauncherWrapper::stopGame),
       InstanceMethod("exec", &amf::LauncherWrapper::exec),
       InstanceMethod("games", &amf::LauncherWrapper::games),
       InstanceMethod("callAndEmit", &amf::LauncherWrapper::CallAndEmit)});

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  exports.Set("Launcher", func);
  return exports;
}

amf::LauncherWrapper::LauncherWrapper(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<LauncherWrapper>(info), _pLauncher(new Launcher) {}

Napi::Value amf::LauncherWrapper::exec(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int exitCode = _pLauncher->exec();
  return Napi::Number::New(env, exitCode);
}

Napi::Value amf::LauncherWrapper::startGame(const Napi::CallbackInfo& info) {
  _pLauncher->startGame("1");
  return info.Env().Null();
}

Napi::Value amf::LauncherWrapper::stopGame(const Napi::CallbackInfo& info) {
  return info.Env().Null();
}

Napi::Value amf::LauncherWrapper::games(const Napi::CallbackInfo& info) {
  auto games = _pLauncher->games();
  return Napi::String::New(info.Env(), games[0]->name().toStdString());
}

Napi::Value amf::LauncherWrapper::CallAndEmit(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  emitOnNode = Napi::Persistent(info[0].As<Napi::Function>());
  connectSignalsToEventEmitter();
  return env.Null();
}

void amf::LauncherWrapper::connectSignalsToEventEmitter() {
  QObject::connect(
      _pLauncher.data(), &Launcher::inGameTimeChanged,
      [=](std::chrono::seconds time) {
        Napi::Env env = this->emitOnNode.Env();
        Napi::HandleScope scope(env);
        this->emitOnNode.Call({Napi::String::New(env, "inGameTimeChanged"),
                               Napi::Value::From(env, time.count())});
      });
}

#include "Game.hpp"

#include <QProcess>
#include <QTimer>
using namespace std;

constexpr std::chrono::seconds TIMER_TICK = 1s;

amf::Game::Game(QString id, QString name, QString processPath, QObject* parent)
    : QObject(parent),
      _id(std::move(id)),
      _name(std::move(name)),
      _processPath(std::move(processPath)),
      _inGameTime(0s),
      _pInGameTimeTimer(new QTimer),
      _pProcess(new QProcess) {
  connect(_pInGameTimeTimer.data(), &QTimer::timeout, this, [this] {
    _inGameTime += TIMER_TICK;
    emit inGameChanged(inGameTime());
  });
}

const QString& amf::Game::id() const {
  return _id;
}

const QString& amf::Game::name() const {
  return _name;
}

void amf::Game::start() const {
  _pProcess->start(_processPath);
}

void amf::Game::stop() const {
  _pProcess->kill();
}

std::chrono::seconds amf::Game::inGameTime() const {
  return _inGameTime;
}

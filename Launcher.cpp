#include "Launcher.hpp"

#include <QDebug>

#include "Game.hpp"

std::vector<char*> args = {"test_program", "arg1", "arg2"};
static int argc = 3;

amf::Launcher::Launcher()
    : QCoreApplication(argc, args.data()),
      _games{QSharedPointer<Game>::create("1", "Super Game", "notepad.exe"),
             QSharedPointer<Game>::create("2", "Bad Game", "notepad.exe")} {}

int amf::Launcher::exec() {
  return QCoreApplication::exec();
}

void amf::Launcher::startGame(const QString& gameId) const {
  auto it = std::find_if(
      _games.begin(), _games.end(),
      [&gameId](QSharedPointer<Game> pGame) { return pGame->id() == gameId; });
  if (it == _games.end()) {
    qWarning() << "Not found game for start with id:" << gameId;
    return;
  }
  (*it)->start();
}

void amf::Launcher::stopGame(const QString& gameId) const {
  auto it = std::find_if(
      _games.begin(), _games.end(),
      [gameId](QSharedPointer<Game> pGame) { return pGame->id() == gameId; });
  if (it == _games.end()) {
    qWarning() << "Not found game for stop with id:" << gameId;
    return;
  }
  (*it)->stop();
}

const amf::GamesList& amf::Launcher::games() const {
  return _games;
}

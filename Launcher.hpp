#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <QCoreApplication>
#include <QList>
#include <QSharedPointer>
#include <chrono>

namespace amf {
class Game;
class QTimer;

using GamesList = QList<QSharedPointer<Game>>;

class Launcher : public QCoreApplication {
  Q_OBJECT
 public:
  Launcher();
  int exec();
  void startGame(const QString& gameId) const;
  void stopGame(const QString& gameId) const;
  const GamesList& games() const;

 signals:
  void inGameTimeChanged(std::chrono::seconds time);

 private:
  GamesList _games;
};
}  // namespace amf

#endif  // LAUNCHER_HPP

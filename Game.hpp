#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <chrono>

class QProcess;
class QTimer;

namespace amf {
class Game : public QObject {
  Q_OBJECT
 public:
  explicit Game(QString id,
                QString name,
                QString processPath,
                QObject* parent = nullptr);
  const QString& id() const;
  const QString& name() const;
  void start() const;
  void stop() const;
  std::chrono::seconds inGameTime() const;

 signals:
  void inGameChanged(std::chrono::seconds time);

 private:
  QString _id;
  QString _name;
  QString _processPath;
  std::chrono::seconds _inGameTime;
  QScopedPointer<QTimer> _pInGameTimeTimer;
  QScopedPointer<QProcess> _pProcess;
};
}  // namespace amf

#endif  // GAME_HPP

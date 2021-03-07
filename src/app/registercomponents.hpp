#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

class RegisterComponentsPrivate;
class Clock;

class RegisterComponents : public QObject {
    Q_OBJECT
public:
    explicit RegisterComponents( QQmlApplicationEngine* engine, QObject* parent = nullptr );
    ~RegisterComponents();
    void init();

private:
    RegisterComponentsPrivate* d;
};

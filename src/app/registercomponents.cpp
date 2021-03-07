#include <spdlog/spdlog.h>

#include "registercomponents.hpp"

class RegisterComponentsPrivate {
public:
    RegisterComponentsPrivate() = default;

    void setEngine( QQmlApplicationEngine* engine ) {
        if ( engine == nullptr ) {
            return;
        }
        m_engine = engine;
    }

    [[nodiscard]] QQmlApplicationEngine* engine() const {
        return m_engine;
    }

private:
    QQmlApplicationEngine* m_engine { nullptr };
};

RegisterComponents::RegisterComponents( QQmlApplicationEngine* engine, QObject* parent )
    : QObject( parent )
    , d( new RegisterComponentsPrivate() ) {
    d->setEngine( engine );
}

RegisterComponents::~RegisterComponents() {
    delete d;
}

void RegisterComponents::init() {
    if ( d->engine() == nullptr ) {
        spdlog::critical( "{} >> Can't load engine", __PRETTY_FUNCTION__ );
        return;
    }
}

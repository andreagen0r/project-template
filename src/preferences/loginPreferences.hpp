#pragma once

#include <QDir>
#include <QSettings>

#include "ipreferences.hpp"
namespace foo {

class PREFERENCES_EXPORT LoginPreferences : public foo::Preferences {
public:
    LoginPreferences() = default;

    virtual void save() override;
    virtual void load() override;
};

} // namespace foo

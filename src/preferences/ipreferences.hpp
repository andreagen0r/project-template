#pragma once

#include "preferences_export.h"
#include <QSettings>

namespace foo {

struct PREFERENCES_EXPORT Preferences {
    Preferences() { }

    virtual void load() = 0;
    virtual void save() = 0;
};

} // namespace foo

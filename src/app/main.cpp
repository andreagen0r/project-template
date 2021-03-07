#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QSettings>

#include <spdlog/spdlog.h>

#include "version.h"
#include "registercomponents.hpp"

#include <core/entities/user.hpp>

using foo::entities::User;

auto main( int argc, char* argv[] ) -> int {
#if QT_VERSION < QT_VERSION_CHECK( 6, 1, 0 )
    qputenv( "QT_IM_MODULE", QByteArray( "qtvirtualkeyboard" ) );
#endif

    if ( qEnvironmentVariableIsEmpty( "QTGLESSTREAM_DISPLAY" ) ) {
        qputenv( "QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray( "213" ) );
        qputenv( "QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray( "120" ) );
    }

    QCoreApplication::setOrganizationName( QStringLiteral( "foo" ) );
    QCoreApplication::setOrganizationDomain( QStringLiteral( "com.foo" ) );
    QCoreApplication::setApplicationName( QStringLiteral( "FooApp" ) );
    QCoreApplication::setApplicationVersion( QLatin1String( foo::info::projectVersion.data() ) );

    QGuiApplication app( argc, argv );

    User::print();

    const auto authors = foo::info::gitAuthors;
    spdlog::info( "Authors: {}", authors.substr( 0, authors.size() - 2 ) );
    spdlog::info( "{}", foo::info::projectInfo );

    QQuickWindow::setTextRenderType( QQuickWindow::NativeTextRendering );

    QQmlDebuggingEnabler enabler;

    QQmlApplicationEngine engine;

    RegisterComponents rt( &engine );
    rt.init();

    const QUrl url( QStringLiteral( "qrc:/main.qml" ) );
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url]( QObject* obj, const QUrl& objUrl ) {
            if ( !static_cast<bool>( obj ) && url == objUrl ) {
                spdlog::critical( "{} >> Can't load engine.", __PRETTY_FUNCTION__ );
                QCoreApplication::exit( -1 );
            }
        },
        Qt::QueuedConnection );
    engine.load( url );

    spdlog::info( "{} >> Application is loaded successfully.", __PRETTY_FUNCTION__ );

    return QGuiApplication::exec();
}

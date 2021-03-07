/***************************************************************************
**
**  Copyright (C) 2020 by Jean Lima Andrade <jeno.andrade@gmail.com>
**  Copyright (C) 2020 by Vinicius Melo <vinimelo@riseup.net>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Foobar. If not, see <https://www.gnu.org/licenses/>.
**
***************************************************************************/

#ifndef NETWORKCONTROLLER_H_
#define NETWORKCONTROLLER_H_

#include <QJsonValue>
#include <QNetworkAccessManager>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QQmlEngine>  // For QML_ELEMENT and QML_SINGLETON
#endif
#include <QQmlPropertyMap>  // Qt6 complains if a forward decl is used here

class RESTReply : public QObject
{
    Q_OBJECT

public:
    explicit RESTReply(QNetworkReply *networkReply, QObject *parent = nullptr);

Q_SIGNALS:
    void finished(const QJsonValue &jsonValue);
    void errorStringChanged(const QString &errorString);
};

// cppcheck-suppress noConstructor
class NetworkController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlPropertyMap * context READ context CONSTANT)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QML_ELEMENT
    QML_SINGLETON

public:
#endif
    explicit NetworkController(QObject *parent = nullptr);
public:
    static NetworkController *self();
    ~NetworkController() Q_DECL_OVERRIDE;

    enum class Status {Null, Loading, Ready, Error};
    Q_ENUM(Status)

    Q_INVOKABLE RESTReply *get(const QString &endpoint,
                               const QString &resourceName = QLatin1String(""));
    Q_INVOKABLE RESTReply *post(const QString &endpoint,
                                const QJsonObject &resourceData,
                                const QString &resourceName = QLatin1String(""));
    Q_INVOKABLE RESTReply *put(const QString &endpoint,
                               const QJsonObject &resourceData,
                               const QString &resourceName = QLatin1String(""));
    Q_INVOKABLE RESTReply *del(const QString &endpoint,
                               const QString &resourceName = QLatin1String(""));

    QQmlPropertyMap *context() const;
    NetworkController::Status status() const;
    QString errorString() const;

    Q_INVOKABLE void login(bool dryRun = false);
    Q_INVOKABLE void logout();
    Q_INVOKABLE void handleAuthenticationChange(const QString &token,
                                                const QString &displayName,
                                                const QString &email,
                                                const QString &photoUrl);

Q_SIGNALS:
    void statusChanged(NetworkController::Status);
    void errorStringChanged(const QString &errorString);

private:
#ifdef Q_OS_ANDROID
    void handlePushNotificationNavigation();
#endif

    enum class RequestType {Get, Post, Put, Delete};

    RESTReply *request(const QString &url,
                       RequestType requestType = RequestType::Get,
                       const QJsonValue &jsonValue = QJsonValue{});
    void setStatus(Status status);
    void setErrorString(const QString &errorString);

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)
    static constexpr char _RESTFULSERVERURL[] =
        "https://cohope.sandroandrade.org";

    static NetworkController *_self;
    QQmlPropertyMap *_context;
    QNetworkAccessManager _networkManager;
    QNetworkRequest _request;
    QString _errorString;
    int _pendingRequests {0};
    Status _status {Status::Null};
};

#endif  // NETWORKCONTROLLER_H_

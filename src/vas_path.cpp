///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005-2008 Martin Boehme
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////////////

#include "vas_path.h"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>

//QString VasPath::m_path=".";
QString VasPath::m_path;

/////////////////////////////////////////////////////////////////////////////

//QString VasPath::prependPath(const QString &relativePath)
//{
//    QString ret;
//    QString tmpPath = QDir::fromNativeSeparators(relativePath);
//    if (relativePath.isEmpty()) ret = m_path;
//    else ret = m_path + (tmpPath[0] == '/' ? "" : "/") +  relativePath;
//    return ret.trimmed();
//}


QString VasPath::prependPath(const QString &relativePath, VasPath::EDataPath pathType) {
    QString dataPath;
    if (m_path.isEmpty()) {
        dataPath = getUserDataPath();
        if (pathType == dpApp) {
            dataPath = getAppDataPath();
        }
    } else {
        dataPath = m_path;
    }

    QString ret;
    QString tmpPath = QDir::fromNativeSeparators(relativePath);
    if (relativePath.isEmpty()) ret = dataPath;
    else ret = dataPath + (tmpPath[0] == '/' ? "" : "/") +  relativePath;
    return ret.trimmed();
}

/////////////////////////////////////////////////////////////////////////////

QString VasPath::getUserDataPath() {
    return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/vasFMC";
}

/////////////////////////////////////////////////////////////////////////////

QString VasPath::getAppDataPath() {
    //XXX: need some work on linux (if we will be support linux), because data can be stored anywhere in /usr or /usr/local, etc.
    return QApplication::applicationDirPath();
}

/////////////////////////////////////////////////////////////////////////////

bool VasPath::checkUserDataPath() {
    QDir dir(getUserDataPath());
    if (dir.exists()) return true;
    return dir.mkpath(dir.absolutePath());
}

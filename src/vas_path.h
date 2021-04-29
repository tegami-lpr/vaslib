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

#ifndef VAS_PATH_H
#define VAS_PATH_H

#include <QString>

/////////////////////////////////////////////////////////////////////////////

class VasPath
{
public:

    enum EDataPath {
        dpUser = 0,
        dpApp = 1
    };

    static void setPath(const QString &path) { m_path = path.trimmed(); }
    static const QString& getPath() { return m_path; }

//    static QString prependPath(const QString &relativePath);

    //! Function prepend \param relativePath by path where data is stored
    static QString prependPath(const QString &relativePath, EDataPath pathType = dpUser);

    //! Returns path to user writable directory for app configs
    static QString getUserDataPath();
    //! Returns path to static (non writable) app data
    static QString getAppDataPath();
    //! Function check and create if needed user data path
    static bool checkUserDataPath();

private:

    static QString m_path;
};

#endif // VAS_PATH_H

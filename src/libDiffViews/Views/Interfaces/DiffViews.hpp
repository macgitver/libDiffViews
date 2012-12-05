/*
 * MacGitver
 * Copyright (C) 2012 Sascha Cunz <sascha@babbelbox.org>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License (Version 2) as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MGV_DIFF_VIEWS_HPP
#define MGV_DIFF_VIEWS_HPP

#include <QObject>

#include "libDiffViews/DiffViewsApi.hpp"

namespace DiffViews
{

    class DiffViewCreator;

    class DIFF_VIEWS_API DiffViews : public QObject
    {
        Q_OBJECT
    public:
        ~DiffViews();
        static DiffViews& self();

    public:
        QList< DiffViewCreator* > creators() const;
        void registerCreator( DiffViewCreator* creator );
        void unregisterCreator( DiffViewCreator* creator );

        DiffViewCreator* defaultCreator();
        DiffViewCreator* creator( const QString& name );

        void setDefaultCreatorName( const QString& id );
        QString defaultCreatorName() const;

    private:
        static DiffViews* sSelf;
        DiffViews();
        QString mDefaultCreatorName;
        QList< DiffViewCreator* > mCreators;
    };

}

#endif

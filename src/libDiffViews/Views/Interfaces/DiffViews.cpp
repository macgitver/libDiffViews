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

#include "DiffViews.hpp"
#include "DiffView.hpp"

namespace DiffViews
{

    class RawView;
    MGVDV_DECLARE_DIFFVIEWCREATOR(RawView)

    class SequentialView;
    MGVDV_DECLARE_DIFFVIEWCREATOR(SequentialView)

    DiffViews::DiffViews()
    {
        sSelf = this;
        registerDiffView_RawView();
        registerDiffView_SequentialView();
        setDefaultCreatorName( QLatin1String( "SequentialView" ) );
    }

    DiffViews::~DiffViews()
    {
        foreach( DiffViewCreator* c, mCreators )
        {
            delete c;
        }

        sSelf = NULL;
    }

    DiffViews* DiffViews::sSelf = NULL;

    DiffViews& DiffViews::self()
    {
        if( sSelf == NULL )
            return *(new DiffViews);
        return *sSelf;
    }

    QList< DiffViewCreator* > DiffViews::creators() const
    {
        return mCreators;
    }

    void DiffViews::registerCreator( DiffViewCreator* creator )
    {
        mCreators.append( creator );
    }

    void DiffViews::unregisterCreator( DiffViewCreator* creator )
    {
        mCreators.removeAll( creator );
    }

    DiffViewCreator* DiffViews::defaultCreator()
    {
        return creator( mDefaultCreatorName );
    }

    DiffViewCreator* DiffViews::creator( const QString& name )
    {
        foreach( DiffViewCreator* c, mCreators )
        {
            if( c->name() == name )
            {
                return c;
            }
        }

        return NULL;
    }

    void DiffViews::setDefaultCreatorName( const QString& id )
    {
        mDefaultCreatorName = id;
    }

    QString DiffViews::defaultCreatorName() const
    {
        return mDefaultCreatorName;
    }

}

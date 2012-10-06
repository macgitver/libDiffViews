/*
 * libDiffViews
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

#include <QTextStream>

#include "libDiffViews/Model/Hunk.hpp"

namespace DiffViews
{

    Hunk::Hunk()
    {
    }

    Hunk::~Hunk()
    {
    }

    void Hunk::addPart( HunkPart::Ptr part )
    {
        mParts.append( part );
    }

    HunkPart::List Hunk::parts() const
    {
        return mParts;
    }

    int Hunk::numLines( int side ) const
    {
        int l = 0;

        for( int i = 0; i < mParts.count(); i ++ )
        {
            l += mParts[ i ]->numLines( side );
        }

        return l;
    }

    int Hunk::firstLine( int side ) const
    {
        Q_ASSERT( mParts.count() > 0 );
        return mParts[ 0 ]->firstLine( side );
    }

    void Hunk::exportRaw( QTextStream& stream )
    {
        stream << "@@ " << firstLine( 0 ) << "," << numLines( 0 ) << " "
               << firstLine( 1 ) << "," << numLines( 1 ) << " @@";

        if( !mHunkHeader.isEmpty() )
        {
            stream << " " << mHunkHeader;
        }

        stream << "\n";

        for( int i = 0; i < mParts.count(); i++ )
        {
            mParts[ i ]->exportRaw( stream );
        }
    }

    void Hunk::setHunkHeader( const QString& header )
    {
        mHunkHeader = header;
    }

    QString Hunk::hunkHeader() const
    {
        return mHunkHeader;
    }

}

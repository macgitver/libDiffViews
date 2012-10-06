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

#include "libDiffViews/Model/TextFilePatch.hpp"

namespace DiffViews
{

    TextFilePatch::TextFilePatch( const QStringList& pathNames )
        : mPathNames( pathNames )
    {
    }

    TextFilePatch::~TextFilePatch()
    {
    }

    QStringList TextFilePatch::pathNames() const
    {
        return mPathNames;
    }

    Hunk::List TextFilePatch::allHunks() const
    {
        return mHunks;
    }

    void TextFilePatch::addHunk( Hunk::Ptr hunk )
    {
        mHunks.append( hunk );
    }

    int TextFilePatch::numHunks() const
    {
        return mHunks.count();
    }

    void TextFilePatch::addOptionLine( const QString& line )
    {
        mOptionLines.append( line );
    }

    void TextFilePatch::addOption( const QString& option )
    {
        mOptions.append( option );
    }

    void TextFilePatch::exportRaw( QTextStream& stream )
    {
        Q_ASSERT( mPathNames.count() == 2 );

        stream << "diff " << mOptions.join( QLatin1String( " " ) );
        if( mOptions.count() > 0 )
            stream << ' ';
        stream << mPathNames.join( QLatin1String( " " ) ) << '\n';

        stream << mOptionLines.join( QLatin1String( "\n" ) );
        if( mOptionLines.count() > 0 )
            stream << '\n';

        stream << "--- " << mPathNames[ 0 ] << '\n';
        stream << "+++ " << mPathNames[ 1 ] << '\n';

        for( int i = 0; i < mHunks.count(); i++ )
        {
            mHunks[ i ]->exportRaw( stream );
        }
    }

    TextFilePatch::Type TextFilePatch::type() const
    {
        return TextPatch;
    }

    TextFilePatch::Ptr TextFilePatch::asTextFilePatch()
    {
        return Ptr( this );
    }

}

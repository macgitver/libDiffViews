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

#include <QDebug>
#include <QTextStream>
#include <QPainter>

#include "SequentialView.hpp"
#include "SeqViewHunk.hpp"

namespace DiffViews
{

    SeqViewHunkHeader::SeqViewHunkHeader( SeqViewInfo* info, Hunk::Ptr hunk, const QFont& font )
        : SeqViewItem( info )
        , mFont( font )
        , mText( hunk->completeHeader() )
    {
    }

    qreal SeqViewHunkHeader::setWidth( qreal width )
    {
        QFontMetricsF fm( mFont );
        qreal height = qRound( fm.lineSpacing() );

        SeqViewItem::setWidth( width, height );
        return height;
    }

    void SeqViewHunkHeader::paint( QPainter* p, const QStyleOptionGraphicsItem*, QWidget* )
    {
        SeqViewInfo* i = info();

        p->setPen( i->clrSeparator );
        p->setBrush( i->clrDeltaFirst );
        p->drawRect( 10, 0, width() - 20, height() );

        p->setPen( i->clrText );
        p->setFont( mFont );
        p->drawText( QRectF( 12, 1, width() - 24, height() - 2 ),
                     Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWrapAnywhere, mText );
    }

    SeqViewHunkContent::SeqViewHunkContent( SeqViewInfo* info, Hunk::Ptr hunk, const QFont& font )
        : SeqViewItem( info )
        , mFont( font )
    {
        #if 0
        QString s; QTextStream ts( &s ); hunk->exportRaw( ts );
        qDebug() << s;
        #endif

        int l = hunk->firstLine( 0 );
        int r = hunk->firstLine( 1 );
        foreach( HunkPart::Ptr part, hunk->parts() )
        {
            Line line;
            switch( part->type() )
            {
            case HunkPart::Context:
                for( int i = 0; i < part->numLines( 0 ); ++i )
                {
                    line.leftNr = l++;
                    line.rightNr = r++;
                    line.text = part->sideLines( 0 )->lineAt( i );
                    mLines.append( line );
                }
                break;

            /*
            Obviously, something is wrong with HunkPart::Insert. It doesn't show up at all.
            However, everything but Context can be output as "Change", so no reason to be alarmed
            here, NOW. But we'll have to look for that some day...

            case HunkPart::Insert:
                for( int i = 0; i < part->numLines( 1 ); ++i )
                {
                    line.leftNr = 0;
                    line.rightNr = r++;
                    line.text = part->sideLines( 1 )->lineAt( i );
                    mLines.append( line );
                }
                break;

            case HunkPart::Delete:
                for( int i = 0; i < part->numLines( 0 ); ++i )
                {
                    line.leftNr = l++;
                    line.rightNr = 0;
                    line.text = part->sideLines( 0 )->lineAt( i );
                    mLines.append( line );
                }
                break;
            */
            default:
            case HunkPart::Change:
                for( int i = 0; i < part->numLines( 0 ); ++i )
                {
                    line.leftNr = l++;
                    line.rightNr = 0;
                    line.text = part->sideLines( 0 )->lineAt( i );
                    mLines.append( line );
                }
                for( int i = 0; i < part->numLines( 1 ); ++i )
                {
                    line.leftNr = 0;
                    line.rightNr = r++;
                    line.text = part->sideLines( 1 )->lineAt( i );
                    mLines.append( line );
                }
                break;
            }
        }
    }

    qreal SeqViewHunkContent::setWidth( qreal width )
    {
        QFontMetricsF fm( mFont );
        qreal height = qRound( fm.lineSpacing() + 1 ) * mLines.count();

        mSpaceLeft = mSpaceRight = 20;
        for( int i = 0; i < mLines.count(); ++i )
        {
            if( mLines[ i ].leftNr )
            {
                int space = qRound( fm.width( QString::number( mLines[ i ].leftNr ) ) );
                mSpaceLeft = qMax( mSpaceLeft, space );
            }

            if( mLines[ i ].rightNr )
            {
                int space = qRound( fm.width( QString::number( mLines[ i ].rightNr ) ) );
                mSpaceRight = qMax( mSpaceRight, space );
            }
        }

        SeqViewItem::setWidth( width, height );
        return height;
    }

    void SeqViewHunkContent::paint( QPainter* p, const QStyleOptionGraphicsItem*, QWidget* )
    {
        SeqViewInfo* ifo = info();

        QFontMetricsF fm( mFont );
        qreal lh = qRound( fm.lineSpacing() + 1 );
        qreal top;

        p->setPen( ifo->clrSeparator );
        p->setBrush( ifo->clrDeltaFirst );
        p->drawRect( 10, 0, width() - 20, height() );

        qreal left = 12 + mSpaceLeft + mSpaceRight + 6;
        qreal wide = width() - 12 - left;
        for( int i = 0; i < mLines.count(); ++i )
        {
            if( !mLines[ i ].rightNr )
            {
                p->fillRect( QRectF( 11, 1 + top, width() - 21, lh ), ifo->clrRemoved );
            }
            else if( !mLines[ i ].leftNr )
            {
                p->fillRect( QRectF( 11, 1 + top, width() - 21, lh ), ifo->clrAdded );
            }
            p->setPen( ifo->clrText );
            p->setFont( mFont );

            if( mLines[ i ].leftNr )
            {
                p->drawText( QRectF( 12, 1 + top, mSpaceLeft, lh - 1 ),
                             Qt::AlignRight | Qt::AlignVCenter | Qt::TextWrapAnywhere,
                             QString::number( mLines[ i ].leftNr ) );
            }

            if( mLines[ i ].rightNr )
            {
                p->drawText( QRectF( 12 + mSpaceLeft + 2, 1 + top, mSpaceRight, lh - 1 ),
                             Qt::AlignRight | Qt::AlignVCenter | Qt::TextWrapAnywhere,
                             QString::number( mLines[ i ].rightNr ) );
            }

            p->drawText( QRectF( left, 1 + top, wide, lh - 1 ),
                         Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWrapAnywhere,
                         mLines[ i ].text );

            top += lh;
        }

        p->setPen( ifo->clrSeparator );
        p->drawLine( 12 + mSpaceLeft + 1, 0,
                     12 + mSpaceLeft + 1, height() );

        p->drawLine( 12 + mSpaceLeft + mSpaceRight + 2, 0,
                     12 + mSpaceLeft + mSpaceRight + 2, height() );
    }

}

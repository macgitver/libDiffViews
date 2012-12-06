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

#include <QPainter>
#include <QFontMetricsF>
#include <QFont>
#include <QDebug>

#include "SequentialView.hpp"
#include "SeqViewDiffStat.hpp"

namespace DiffViews
{

    SeqViewDiffStat::SeqViewDiffStat( const QFont& font )
    {
        mFont = font;
        mAdded = mRemoved = 0;
        mBinary = false;
    }

    qreal SeqViewDiffStat::setWidth( qreal width, SeqViewInfo& info )
    {
        QFontMetricsF fm( mFont );
        qreal height = qRound( fm.lineSpacing() + 3. );

        qreal textWidth = fm.width( mPathName );
        info.maxDiffStatTextLength = qMax( textWidth, info.maxDiffStatTextLength );

        qreal statsWidth = fm.width( statsText() );
        info.maxDiffStatStatLength = qMax( statsWidth, info.maxDiffStatStatLength );

        info.maxChange = qMax( qMax( mAdded, mRemoved ), info.maxChange );

        SeqViewItem::setWidth( width, height );

        return height;
    }

    QString SeqViewDiffStat::statsText() const
    {
        if( mBinary )
        {
            return QLatin1String( "Bin" );
        }
        return QString( QLatin1String( "+%1 -%2" ) ).arg( mAdded ).arg( mRemoved );
    }

    void SeqViewDiffStat::postRendering( const SeqViewInfo& info )
    {
        mTextWidth = info.maxDiffStatTextLength;
        mStatsWidth = info.maxDiffStatStatLength;
        mClrSeparator = info.clrSeparator;
        mClrAdded = info.clrAdded;
        mClrRemoved = info.clrRemoved;
        mClrText = info.clrText;
        mMaxChange = info.maxChange;
    }

    void SeqViewDiffStat::paint( QPainter* p, const QStyleOptionGraphicsItem*, QWidget* )
    {
        p->setFont( mFont );
        p->setPen( mClrText );
        p->drawText( QRectF( 5, 0, mTextWidth, height() ),
                     Qt::AlignVCenter | Qt::AlignLeft, mPathName );

        p->drawText( QRectF( width() - mStatsWidth, 0, mStatsWidth, height() ),
                     Qt::AlignVCenter | Qt::AlignRight, statsText() );

        qreal changeWidth = width() - mStatsWidth - mTextWidth - 5 - 3;
        int halfHeight = height() / 2;
        if( mAdded )
        {
            QRectF r( mTextWidth + 5 + qreal(mMaxChange-mAdded)/mMaxChange*changeWidth, 2,
                      mAdded / qreal(mMaxChange) * changeWidth, halfHeight - 2 );
            p->fillRect( r, mClrAdded );
        }
        if( mRemoved )
        {
            QRectF r( mTextWidth + 5 + qreal(mMaxChange-mRemoved)/mMaxChange*changeWidth, halfHeight,
                      mRemoved / qreal(mMaxChange) * changeWidth, halfHeight - 1 );
            p->fillRect( r, mClrRemoved );
        }

        p->setPen( mClrSeparator );
        p->drawLine( QPointF( 0, height() ), QPointF( width(), height() ) );
    }

    void SeqViewDiffStat::setPathName( const QString& name )
    {
        mPathName = name;
    }

    void SeqViewDiffStat::setChangeCount( int added, int removed )
    {
        mAdded = added;
        mRemoved = removed;
    }

}

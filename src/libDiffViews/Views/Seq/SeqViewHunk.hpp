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

#ifndef MGV_DIFF_SEQ_VIEW_HUNK_HPP
#define MGV_DIFF_SEQ_VIEW_HUNK_HPP

#include "libDiffViews/Model/Hunk.hpp"

#include "SeqViewItem.hpp"

namespace DiffViews
{

    class SeqViewHunkHeader : public SeqViewItem
    {
    public:
        SeqViewHunkHeader( Hunk::Ptr patch, const QFont& font );

    public:
        qreal setWidth( qreal width, SeqViewInfo& info );
        void postRendering( const SeqViewInfo& info );
        void paint( QPainter*, const QStyleOptionGraphicsItem*, QWidget* );

    private:
        QColor  mClrDeltaFirst;
        QColor  mClrSeparator;
        QColor  mClrText;
        QFont   mFont;
        QString mText;
    };

    class SeqViewHunkContent : public SeqViewItem
    {
    public:
        SeqViewHunkContent( Hunk::Ptr patch, const QFont& font );

    public:
        qreal setWidth( qreal width, SeqViewInfo& info );
        void postRendering( const SeqViewInfo& info );
        void paint( QPainter*, const QStyleOptionGraphicsItem*, QWidget* );

    private:
        QColor  mClrDeltaFirst;
        QColor  mClrSeparator;
        QColor  mClrText;
        QColor  mClrAdded;
        QColor  mClrRemoved;
        QFont   mFont;
        int     mSpaceLeft;
        int     mSpaceRight;

        struct Line
        {
            QString     text;
            int         leftNr;
            int         rightNr;
        };
        QList< Line > mLines;
    };

}

#endif

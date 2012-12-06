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

#ifndef MGV_DIFF_SEQ_VIEW_DELTA_HPP
#define MGV_DIFF_SEQ_VIEW_DELTA_HPP

#include "libDiffViews/Model/FilePatch.hpp"

#include "SeqViewContainer.hpp"

namespace DiffViews
{

    class SeqViewDeltaHeader : public SeqViewItem
    {
    public:
        SeqViewDeltaHeader( FilePatch::Ptr patch, const QFont& font );

    public:
        qreal setWidth( qreal width, SeqViewInfo& info );
        void postRendering( const SeqViewInfo& info );
        void paint( QPainter*, const QStyleOptionGraphicsItem*, QWidget* );

    private:
        QColor          mClrSeparator;
        QColor          mClrDeltaFirst;
        QColor          mClrDeltaSecond;
        QColor          mClrText;
        QFont           mFont;
        QStringList     mTextLines;
    };

    class SeqViewDelta : public SeqViewContainer
    {
    public:
        SeqViewDelta();

    };

}

#endif

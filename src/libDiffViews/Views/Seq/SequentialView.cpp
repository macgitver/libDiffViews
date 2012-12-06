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

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>

#include "Views/Interfaces/DiffViews.hpp"

#include "Views/Seq/SequentialView.hpp"
#include "Views/Seq/SeqViewContainer.hpp"
#include "Views/Seq/SeqViewDiffStat.hpp"
#include "Views/Seq/SeqViewDelta.hpp"
#include "Views/Seq/SeqViewHunk.hpp"

namespace DiffViews
{

    SequentialView::SequentialView( QWidget* parent )
        : DiffView( parent )
    {
        mFixedFont = QFont( QLatin1String( "Courier New" ), 12 );
        mScene = NULL;

        mView = new QGraphicsView;
        mView->setFrameShape( QFrame::NoFrame );
        mView->setAlignment( Qt::AlignTop | Qt::AlignHCenter );

        QVBoxLayout* l = new QVBoxLayout;
        l->setMargin( 0 );
        l->setSpacing( 0 );
        l->addWidget( mView );
        setLayout( l );
    }

    SequentialView::~SequentialView()
    {
    }

    void SequentialView::setPatch( Patch::Ptr patch )
    {
        mCurrentPatch = patch;

        generateScene();
    }

    void SequentialView::generateScene()
    {
        delete mScene;

        mScene = new QGraphicsScene( this );

        mRoot = new SeqViewContainer;

        mDiffStats = new SeqViewContainer;
        mDiffStats->setVerticalMargins( 0., 4. );

        mDeltas = new SeqViewContainer;
        mDeltas->setVerticalMargins( 0., 10. );

        mDiffStats->setParentItem( mRoot );
        mDeltas->setParentItem( mRoot );
        mScene->addItem( mRoot );

        mView->setScene( mScene );

        if( mCurrentPatch )
        {
            FilePatch::List paths = mCurrentPatch->allPaths();
            foreach( FilePatch::Ptr filePatch, paths )
            {
                if( filePatch->type() == FilePatch::BinaryPatch )
                {
                    continue;   // for now
                }
                else
                {
                    TextFilePatch::Ptr textPatch = filePatch->asTextFilePatch();

                    SeqViewDiffStat* item = new SeqViewDiffStat( font() );
                    item->setPathName( textPatch->pathNames()[ 0 ] );

                    int added = 0, removed = 0;
                    textPatch->totalChanges( added, removed );
                    item->setChangeCount( added, removed );

                    item->setParentItem( mDiffStats );

                    SeqViewDelta* delta = new SeqViewDelta;
                    delta->setVerticalMargins( 3., 3. );
                    delta->setParentItem( mDeltas );

                    SeqViewDeltaHeader* deltaHeader = new SeqViewDeltaHeader( filePatch, mFixedFont );
                    deltaHeader->setParentItem( delta );

                    foreach( Hunk::Ptr hunk, textPatch->allHunks() )
                    {
                        SeqViewHunkHeader* hunkHead = new SeqViewHunkHeader( hunk, mFixedFont );
                        hunkHead->setParentItem( delta );

                        SeqViewHunkContent* hunkContent = new SeqViewHunkContent( hunk, mFixedFont );
                        hunkContent->setParentItem( delta );
                    }
                }
            }
        }

        updateWidth();
    }

    void SequentialView::resizeEvent( QResizeEvent* ev )
    {
        QWidget::resizeEvent( ev );
        updateWidth();
    }

    void SequentialView::updateWidth()
    {
        if( !mScene || !mDiffStats )
        {
            return;
        }

        mInfo.minWidth = 0;
        mInfo.maxDiffStatTextLength = 0;
        mInfo.maxDiffStatStatLength = 0;
        mInfo.maxChange = 0;
        mInfo.clrAdded          = QColor( 0x99, 0xCC, 0x99 );
        mInfo.clrRemoved        = QColor( 0xCC, 0x99, 0x99 );
        mInfo.clrContext        = QColor( 0x00, 0x00, 0x00 );
        mInfo.clrSeparator      = QColor( 0xCC, 0xCC, 0xCC );
        mInfo.clrDeltaFirst     = QColor( 0xEE, 0xEE, 0xEE );
        mInfo.clrDeltaSecond    = QColor( 0xCC, 0xCC, 0xCC );
        mInfo.clrText           = QColor( 0x00, 0x00, 0x00 );

        qreal width = mView->viewport()->width();
        qreal height = mRoot->setWidth( width, mInfo );

        width = qMax( mInfo.minWidth, width );

        mScene->setSceneRect( 0., 0., width, height );

        mDiffStats->postRendering( mInfo );
        mDeltas->postRendering( mInfo );
    }

    MGVDV_IMPLEMENT_DIFFVIEWCREATOR(SequentialView)

}

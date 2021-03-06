/*
** Copyright (C) 2012 Sebastian Roeglinger <wast.drumster@gmail.com>
** 
** This file is part of TheClick.
** 
** TheClick is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** TheClick is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with TheClick.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ClICKGENERATORABSTRACTWIDGET_H
#define ClICKGENERATORABSTRACTWIDGET_H

#include "MainWindow/SoundConfigurationTab/XToXAssociationAbstractWidget.h"
#include <QWidget>
#include <QList>
#include "libTheClick/libTheClick.h"

class ClickGeneratorAbstractWidget : public QWidget
{
    Q_OBJECT
    
    //********** PRELIMINARY **********
    public:
        typedef int32_t clickgensound_id;

        struct clickgensound_strings
        {
            QString drumkitName;
            QString instrumentName;
        };

    //********** (DE/CON)STRUCTORS **********
    public:
        ClickGeneratorAbstractWidget(QWidget *parent = 0) : QWidget(parent) {}
        virtual ~ClickGeneratorAbstractWidget() {}
        
    private:

    //********** ATTRIBUTES **********
    public: 
        
    protected: 
        
    private:
        
    //********** METHODS **********
    public:
        virtual int getMinimumWidthForMainWindowHeight(int h) const = 0;
        virtual QList<XToXAssociationAbstractWidget*>* XToXAssociationWidgetFactory() = 0;
        virtual void setSoundConfiguration(clickgensound_id cgsID, drumkit_id dkID, instrument_id instrumentID) = 0;

        virtual clickgensound_strings getClickGenSoundStrings(clickgensound_id cgsID) = 0;
        virtual void setClickGenSoundStrings(clickgensound_id cgsID, clickgensound_strings cgsSt) = 0;

    protected: 
        
    private:
        
    //********** SIGNALS **********
    signals:
        void shouldResize();

    //********** SLOTS **********
    private slots:

};

#endif // ClICKGENERATORABSTRACTWIDGET_H

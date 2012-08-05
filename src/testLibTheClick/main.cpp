//
//  main.cpp
//  PortAudioTest
//
//  Created by Sebastian Röglinger on 17.06.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>


//*********   LIBTHECLOCK   *********
#include "libTheClick/libTheClick.h"

//*********   FUNCTIONS   *********

void beatCallBack(int beats)
{
    std::cout << "beats: " << beats << std::endl;
}

int main(int argc, const char * argv[])
{
    //generate objects
    libTheClick::ClickGenerator_DivisionSubdivision* cg1 = new libTheClick::ClickGenerator_DivisionSubdivision();
    libTheClick::ClickGenerator_XoverY* cg2 = new libTheClick::ClickGenerator_XoverY();
    libTheClick::ClickGenerator_Rudiments* cg3 = new libTheClick::ClickGenerator_Rudiments();
    libTheClick::ClickGenerator_DummyBeatCount* cg4 = new libTheClick::ClickGenerator_DummyBeatCount();
    libTheClick::ClickController *cc = new libTheClick::ClickController();

//    cc->getSoundBase()->loadDrumKit( "/home/wast/Daten/Projekte/TheClick/drumkits/Beep" );
//    cc->getSoundBase()->loadDrumKit( "/Users/wast/Documents/Projekte/2012_06_16-TheClick/TheClick@GitHub/drumkits/The Black Pearl 1.0 subset for TheClick" );
    cc->getSoundBase()->loadDrumKit( "/Users/wast/Library/Application Support/Hydrogen/drumkits/Boss DR-110" );

    //DivisionSubdivision
    cg1->setAmountDivisions(4);
    cg1->setAmountSubdivisions(2);
    cg1->setDivisionPattern(0, cc->getSoundBase()->getSoundElement(0, 0, 1.0f));
    cg1->setDivisionPattern(1, cc->getSoundBase()->getSoundElement(0, 0, 0.5f));
    cg1->setDivisionPattern(2, cc->getSoundBase()->getSoundElement(0, 0, 0.5f));
    cg1->setDivisionPattern(3, cc->getSoundBase()->getSoundElement(0, 0, 0.0f));
//    cg1->setSubdivisionPattern(0, cc->getSoundBase()->getSoundElement(0, 5, 0.5f));
    cg1->setSubdivisionPattern(1, cc->getSoundBase()->getSoundElement(0, 18, 0.3f));
    cg1->setSubdivisionPattern(2, cc->getSoundBase()->getSoundElement(0, 4, 0.3f));
//    cg1->setSubdivisionPattern(3, cc->getSoundBase()->getSoundElement(0, 8, 0.5f));

    //XoverY
    cg2->setX(3);
    cg2->setY(4);
    cg2->setXSoundElement(cc->getSoundBase()->getSoundElement(0, 1, 0.8f));
    cg2->setYSoundElement(cc->getSoundBase()->getSoundElement(0, 1, 0.2f));

    //Rudiments
    cg3->setRudimentsID(40);
    cg3->setSoundElement(RIGHT, NORMAL, cc->getSoundBase()->getSoundElement(0, 1, 0.5f));
    cg3->setSoundElement(RIGHT, GHOST,  cc->getSoundBase()->getSoundElement(0, 1, 0.2f));
    cg3->setSoundElement(RIGHT, ACCENT, cc->getSoundBase()->getSoundElement(0, 1, 1.0f));
    cg3->setSoundElement(LEFT,  NORMAL, cc->getSoundBase()->getSoundElement(0, 5, 0.5f));
    cg3->setSoundElement(LEFT,  GHOST,  cc->getSoundBase()->getSoundElement(0, 5, 0.2f));
    cg3->setSoundElement(LEFT,  ACCENT, cc->getSoundBase()->getSoundElement(0, 5, 1.0f));

    //set call back function
    cg4->setBeatCountCallbackFunction( &beatCallBack );

    //play click
    clickgen_id cg1id = cc->addClickGenerator(cg1, 1.0);
    clickgen_id cg2id = cc->addClickGenerator(cg2, 0.3);
//    clickgen_id cg3id = cc->addClickGenerator(cg3, 0.8);
    clickgen_id cg4id = cc->addClickGenerator(cg4, 0.0);
    cc->setBeatsPerMinute(60);
    cc->start();
    sleep(15);
//    cc->setVolumeforClickGenerator(cg1id, 0.2);

//    for(int32_t i = 0; i<50; i++)
//    {
//        usleep(5E6);
//        cc->setBeatsPerMinute( cc->getBeatsPerMinute() + 5 );
//    }
    sleep(5);
//    cc->stop();
//    cc->reset();
//    sleep(2);
//    cc->start();
    sleep(30);

    //clean up
    delete cc;

    //exit
    return 0;
}

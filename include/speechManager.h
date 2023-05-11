#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <time.h>
#include <deque>
#include <numeric>
#include <stdlib.h>
#include <fstream>

#define FileName "speech.csv"

using namespace std;

class speechManager
{
public:

    vector<int> v1;
    vector<int> v2;
    vector<int> Victory;
    map<int,speaker> m_speaker;
    int m_idx;

    bool fileIsEmpty;
    map<int, vector<string>> m_Record;

    speechManager(/* args */);

    void show_Menu();
    void exitSystem();

    void initSpeech();

    void createSpeaker();

    void startSpeech();
    void speechDraw();
    void speechContest();
    void showScore();

    void saveRecord();

    void loadRecord();
    void showRecord();

    void clearRecord();
};

#include "../include/speechManager.h"


speechManager::speechManager(/* args */)
{
    this->initSpeech();

    this->createSpeaker();

    this->loadRecord();
}

void speechManager::show_Menu()
{
    cout<<"**************************************"<<endl;
    cout<<"*********��ӭ�μ��ݽ����� ************"<<endl;
    cout<<"*********1����ʼ�ݽ����� *************"<<endl;
    cout<<"*********2���鿴�����¼ *************"<<endl;
    cout<<"*********3����ձ�����¼ *************"<<endl;
    cout<<"*********0���˳��������� *************"<<endl;
    cout<<"**************************************"<<endl;
    cout<<endl;
}
void speechManager::exitSystem()
{
    cout << "��ӭ�´�ʹ��" << endl;
    exit(0);
}
void speechManager::initSpeech()
{
    this->v1.clear();
    this->v2.clear();
    this->Victory.clear();
    this->m_speaker.clear();
    this->m_Record.clear();

    this->m_idx = 1;
}

void speechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";

    int num = nameSeed.size();
    for(int i = 0; i < num; i ++ )
    {
        string name = "ѡ��";
        name += nameSeed[i];

        speaker sp;
        sp.m_Name = name;

        for(int j = 0; j < 2; j ++ )
        {
            sp.m_Sorce[j] = 0;
        }

        this->v1.push_back(i + 10001);
        this->m_speaker.insert(make_pair(i + 10001, sp));
    }
}

void speechManager::startSpeech()
{
    for(int i = 0; i < 2; i ++)
    {
        speechDraw();
        speechContest();
        showScore();
        this->m_idx ++ ;
    }
    saveRecord();

    initSpeech();
    createSpeaker();
    loadRecord();

    cout << "���������ϣ�" << endl;
    system("pause");
    system("cls");
}

void speechManager::speechDraw()
{
    cout << "�ڡ�" << this->m_idx << "���ֱ���ѡ�����ڳ�ǩ" << endl;
    cout << "--------------------" << endl;
    cout << "��ǩ���ݽ�˳������" << endl; 

    if(this->m_idx == 1)
    {
        srand(time(0));
        random_shuffle(v1.begin(), v1.end());

        for(int i = 0; i < (int)v1.size(); i ++ )
        {
            if(i == 0)
            {
                cout << "��һ�飺 ";
            }
            else if(i == 6)
            {
                cout << endl << "�ڶ��飺 ";
            }
            cout << v1[i] << " ";
        }
    }
    else 
    {
        srand(time(0));
        random_shuffle(v2.begin(), v2.end());

        for(int i = 0; i < (int)v2.size(); i ++ )
        {
            if(i == 0)
            {
                cout << "��һ�飺 ";
            }
            cout << v2[i] << " ";
        }
    }

    cout << endl;
    cout << "--------------------" << endl;
    system("pause");
}

void speechManager::speechContest()
{
    cout << "-----�ڡ�" << this->m_idx << "���ֱ�����ʽ��ʼ-----" << endl;

    multimap<double, int, greater<double>> groupS;

    vector<int> v_src;
    if(this->m_idx == 1)
    {
        v_src = v1;
    }
    else 
    {
        v_src = v2;
    }

    for(int i = 0; i < (int)v_src.size(); i ++ )
    {
        deque<double> d;

        for(int j = 0; j < 10; j ++ )
        {
            
            double s = (rand() % 401 + 600) / 10.f;
            // cout << s << " ";
            d.push_back(s);
        }
        // cout<<endl;

        sort(d.begin(), d.end());
        d.pop_back();
        d.pop_front();

        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum * 1.0 / d.size();

        this->m_speaker[v_src[i]].m_Sorce[this->m_idx - 1] = avg;
        
        groupS.insert(make_pair(avg, v_src[i]));

        if(i % 6 == 5)
        {
            cout << "��" << i / 6 + 1 << "С������������£� " <<endl;
            for(auto &[x,k] : groupS)
            {
                cout << "ѡ�ֱ�ţ�" << k << " "
                    << "����: " << m_speaker[k].m_Name << " "
                    << "�ɼ��� " << m_speaker[k].m_Sorce[this->m_idx - 1] << endl;
            }
            cout<<endl;

            int cnt = 0;
            for(auto &[x,k] : groupS)
            {
                if(cnt < 3)
                {
                    if(this->m_idx == 1)
                    {
                        v2.push_back(k);
                    }
                    else 
                    {
                        Victory.push_back(k);
                    }
                }
                else break;
                cnt ++;
            }

            groupS.clear();
        }
    }
    cout << "-----�ڡ�" << this->m_idx << "���ֱ�������-----" << endl;
    system("pause");
}

void speechManager::showScore()
{
    cout << "-----�ڡ�" << this->m_idx << "���ֱ�������ѡ������-----" << endl;

    vector<int> v_src;
    if(this->m_idx == 1)
    {
        v_src = v2;
    }
    else 
    {
        v_src = Victory;
    }

    for(auto &k : v_src)
    {
        cout << "ѡ�ֱ�ţ�" << k << " "
            << "����: " << m_speaker[k].m_Name << " "
            << "�ɼ��� " << m_speaker[k].m_Sorce[this->m_idx - 1] << endl;
    }
    cout<<endl;
    system("pause");
    system("cls");

    this->show_Menu();
}

void speechManager::saveRecord()
{
    ofstream ofs;
    ofs.open(FileName, ios::out | ios::app);

    for(auto &x: Victory)
    {
        ofs << x << ","
            << this->m_speaker[x].m_Sorce[1] << ",";
    }
    ofs<<endl;

    ofs.close();

    cout << "��¼�Ѿ�����" << endl;

    this->fileIsEmpty = false;
}

void speechManager::loadRecord()
{
    ifstream ifs;
    ifs.open(FileName, ios :: in);

    if(!ifs.is_open())
    {
        this->fileIsEmpty = true;
        cout << "�ļ�������" << endl;
        ifs.close();
        return ;
    }

    char c;
    ifs >> c;
    if(ifs.eof())
    {
        cout << "�ļ�Ϊ��" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return ;
    }

    this->fileIsEmpty = false;

    ifs.putback(c);

    string data;
    int idx = 1;

    while (ifs >> data)
    {
        int pos = -1;
        int start = 0;

        vector<string> v;

        while (true)
        {
            pos = data.find(",",start);
            if(pos == -1)
            {
                break;
            }
            else 
            {
                string temp = data.substr(start, pos - start);
                start = pos + 1;
                v.push_back(temp);
            }
        }
        this->m_Record.insert(make_pair(idx, v));
        idx++;
    }

    ifs.close();
}

void speechManager::showRecord()
{

    if(this->fileIsEmpty)
    {
        cout << "�ļ������ڣ����¼Ϊ��" << endl;
    }
    else 
    {
        int cnt = 1;
        for(auto [x,k] : this->m_Record)
        {
            cout << "��" << cnt << "��"
                << "�ھ���ţ�" << k[0] << " �÷֣� " << k[1] << " "
                << "�Ǿ���ţ�" << k[2] << " �÷֣� " << k[3] << " "
                << "������ţ�" << k[4] << " �÷֣� " << k[5] << " "
                << endl;
                cnt ++ ;
        }
    }
    system("pause");
    system("cls");
}

void speechManager::clearRecord()
{
    cout << "��ȷ�����" <<endl;
    cout << "1��ȷ��" <<endl;
    cout << "2��ȡ��" <<endl;

    int s = 0;
    cin>>s;

    if(s == 1)
    { 
        ofstream ofs;
        ofs.open(FileName, ios::trunc);
        ofs.close();

        this->initSpeech();

        this->createSpeaker();

        this->loadRecord();

        cout << "��ճɹ�" << endl;
    }
    system("pause");
    system("cls");
}
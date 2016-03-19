#include<bits/stdc++.h>

using namespace std;

int main()
{
    vector<string>Nonterminal,terminal;
    set<string>::iterator st;
    map<string,int>noOfSymbol;
    map<string,int>::iterator it;
    vector<string>splitgrammer[100][100];
    vector<string>FIRST[100],FOLLOW[100];
    int totProduction[100];
    int idx=1;
    freopen("input.txt","r",stdin);
    string s;
    while(getline(cin,s))
    {
        string left="";
        int i=0;
        while(s[i]!='-')
        {
            left+=s[i];
            i++;
        }

        if(noOfSymbol.find(left)==noOfSymbol.end())
        {
            noOfSymbol[left]=idx++;
            Nonterminal.push_back(left);
        }

        string temp="";
        int noofProduction=1;
        for(i=i+1; s[i]; i++)
        {
            if(s[i]==' ')
            {
                if(noOfSymbol.find(temp)==noOfSymbol.end())
                {
                    noOfSymbol[temp]=idx++;

                    if(temp[0]>='A'&&temp[0]<='Z')
                        Nonterminal.push_back(temp);
                    else
                        terminal.push_back(temp);
                }

                splitgrammer[noOfSymbol[left]][noofProduction].push_back(temp);
                temp="";
            }
            else if(s[i]=='|')
            {
                if(noOfSymbol.find(temp)==noOfSymbol.end())
                {
                    noOfSymbol[temp]=idx++;

                    if(temp[0]>='A'&&temp[0]<='Z')
                        Nonterminal.push_back(temp);
                    else
                        terminal.push_back(temp);
                }
                splitgrammer[noOfSymbol[left]][noofProduction].push_back(temp);
                temp="";
                noofProduction++;
            }
            else
                temp+=s[i];
        }
        if(noOfSymbol.find(temp)==noOfSymbol.end())
        {
            noOfSymbol[temp]=idx++;

            if(temp[0]>='A'&&temp[0]<='Z')
                Nonterminal.push_back(temp);
            else
                terminal.push_back(temp);
        }

        splitgrammer[noOfSymbol[left]][noofProduction].push_back(temp);
        /*for(int i=1; i<=noofProduction; i++)
        {
            for(int j=0; j<parseTable[noOfSymbol[left]][i].size(); j++)
                cout<<parseTable[noOfSymbol[left]][i][j]<<ends;
        }
        cout<<endl<<endl;
        */

        totProduction[noOfSymbol[left]]=noofProduction;
    }
    /*
    for(it=noOfSymbol.begin(); it!=noOfSymbol.end(); it++)
        cout<<it->first<<" "<<it->second<<endl;

    cout<<"Nonterminal "<<endl;

    for(int i=0; i<Nonterminal.size(); i++)
        cout<<Nonterminal[i]<<ends;
    cout<<endl;

    cout<<"terminal "<<endl;

    for(int i=0; i<terminal.size(); i++)
        cout<<terminal[i]<<ends;
    cout<<endl;
    */

    for(int i=0; i<Nonterminal.size(); i++)
    {
        int main_idx = noOfSymbol[Nonterminal[i]];

        queue<string>q;

        q.push(Nonterminal[i]);

        while(!q.empty())
        {

            string Non = q.front();
            q.pop();
            idx = noOfSymbol[Non];

            //cout<<Nonterminal[i]<<" "<<totProduction[idx]<<endl;
            for(int j=1; j<=totProduction[idx]; j++)
            {
                //cout<<splitgrammer[idx][j][0]<<ends;
                if(splitgrammer[idx][j][0][0]>='A'&&splitgrammer[idx][j][0][0]<='Z')
                    q.push(splitgrammer[idx][j][0]);
                else
                    FIRST[main_idx].push_back(splitgrammer[idx][j][0]);
            }
        }
        //cout<<endl;
    }

    for(int i=0; i<Nonterminal.size(); i++)
    {
        idx = noOfSymbol[Nonterminal[i]];
        cout<<"FIRST of "<<Nonterminal[i]<<"   --------->  ";
        for(int j=0; j<FIRST[idx].size(); j++)
            cout<<FIRST[idx][j]<<" ";
        cout<<endl;
    }

    cout<<endl<<endl;

    for(int i=0; i<Nonterminal.size(); i++)
    {
        idx = noOfSymbol[Nonterminal[i]];
        if(Nonterminal[i]=="S")
            FOLLOW[idx].push_back("#");
        //cout<<Nonterminal[i]<<endl;
        for(int k=1; k<=totProduction[idx]; k++)
        {
            vector<string>v;
            for(int j=0; j<splitgrammer[idx][k].size(); j++)
            {
                //cout<<splitgrammer[idx][k][j]<<ends;
                v.push_back(splitgrammer[idx][k][j]);

            }
            //cout<<endl<<endl;
            if(v.size()==1)
            {
                string tmp1 = v[0];
                //cout<<"temp "<<tmp1<<" "<<Nonterminal[i]<<" "<<idx<<" "<<FOLLOW[idx].size()<<endl;
                if((tmp1[0]>='A'&&tmp1[0]<='Z'))
                {
                    int idx2 =  noOfSymbol[tmp1];
                    if(FOLLOW[idx2].size()==0)
                    {
                        for(int x=0; x<FOLLOW[idx].size(); x++)
                        {
                            FOLLOW[idx2].push_back(FOLLOW[idx][x]);
                            //cout<<FOLLOW[idx][x]<<ends;
                        }
                        FOLLOW[idx2].push_back("#");
                    }
                    //cout<<endl<<endl;
                }
            }
            else
            {
                string tmp1,tmp2;
                tmp1 = v[0];
                tmp2 = v[1];
                if((tmp1[0]>='A'&&tmp1[0]<='Z')&&(tmp2[0]>='A'&&tmp2[0]<='Z'))
                {
                    int idx1 =  noOfSymbol[tmp1];
                    int idx2 =  noOfSymbol[tmp2];
                    if(FOLLOW[idx1].size()==0)
                        for(int x=0; x<FIRST[idx2].size(); x++)
                        {
                            FOLLOW[idx1].push_back(FIRST[idx2][x]);
                        }
                }

                if((tmp1[0]>='a'&&tmp1[0]<='z')&&(tmp2[0]>='A'&&tmp2[0]<='Z'))
                {
                    int idx2 =  noOfSymbol[tmp2];
                    if(FOLLOW[idx2].size()==0)
                        for(int x=0; x<FOLLOW[idx].size(); x++)
                        {
                            FOLLOW[idx2].push_back(FOLLOW[idx][x]);
                        }
                }

                tmp1=v[v.size()-1];
                tmp2=v[v.size()-2];

                if((tmp1[0]>='A'&&tmp1[0]<='Z')&&(tmp2[0]>='A'&&tmp2[0]<='Z'))
                {
                    int idx1 =  noOfSymbol[tmp1];
                    if(FOLLOW[idx1].size()==0)
                        FOLLOW[idx1].push_back("#");
                }
            }
        }
    }

    for(int i=0; i<Nonterminal.size(); i++)
    {
        idx = noOfSymbol[Nonterminal[i]];
        cout<<"FOLLOW of "<<Nonterminal[i]<<"   --------->  ";
        for(int j=0; j<FOLLOW[idx].size(); j++)
            cout<<FOLLOW[idx][j]<<" ";
        cout<<endl;
    }

    return 0;
}

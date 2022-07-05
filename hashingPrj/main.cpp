#include <iostream>
#include <fstream>

using namespace std;

class node{
public:
    string word;
    string lines;
    node()
    {
        word = "";
        lines = "";
    }
};

node* hashTable[2000];

int hashFunction(string key)
{
    long unsigned number = 0;
    for(int i = 0; i < key.length(); i++)
    {
        number += ((int) key[i])^2;
    }
    return number%1999;
}

string search(string searchMe)
{
    int place = hashFunction(searchMe);
    int firstPlace = place;
    while((place+1) != firstPlace)
    {
        if(hashTable[place] == nullptr)
        {
            return "word not found!\n";
        }
        if(hashTable[place]->word == searchMe)
        {
            return hashTable[place]->lines;
        }
        else if(place >= 1998)
        {
            place = 0;
        } else{
            place++;
        }
    }
    return "word not found!\n";
}

void putIntoMap(string key, int lineNumber)
{
    int place = hashFunction(key);
    int firstPlace = place;
    if(hashTable[place] == nullptr)
    {
        node* newNode = new node();
        newNode->word = key;
        newNode->lines = "lines: " + to_string(lineNumber);
        hashTable[place] = newNode;
        return;
    }
    else
    {
//        if(hashTable[place]->word == key)
//        {
//            hashTable[place]->lines += (" " + to_string(lineNumber));
//            return;
//        }
//        else
//        {
            while(hashTable[place] != nullptr && (place+1!= firstPlace))
            {
                if(hashTable[place]->word == key)
                {
                    hashTable[place]->lines += (" " + to_string(lineNumber));
                    return;
                }
                if(place >= 1998)
                {
                    place = 0;
                }
                else
                {
                    place ++;
                }

            }
            if(place+1 == firstPlace)
            {
                cerr << "no enough space\n";
            }
        node* newNode = new node();
        newNode->word = key;
        newNode->lines = "lines: " + to_string(lineNumber);
        hashTable[place] = newNode;
        return;

        //}
    }

}

void parseLinesToWords(string text, int lineNumber)
{
    string words[500];
    int wordCounter = 0;  //points to empty space of array
    string word;
    for(int i=0; i<text.length(); i++)
    {
        if(i == text.length()-1)
        {
            word.push_back(text[i]);
            words[wordCounter] = word;
            wordCounter++;
            word.clear();
            break;
        }
        if(text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
        {
            words[wordCounter] = word;
            wordCounter++;
            word.clear();
        }
        else
        {
            word.push_back(text[i]);
        }
    }


    for(int i = 0; i < wordCounter; i++)
    {
        //cout <<"word counter is: " << i << " word is: " << words[i] << " \n";
        //TODO: send words to hashing function.
        putIntoMap(words[i],lineNumber);
    }
}

int main()
{
    string searchMe;
    cin >> searchMe;
    fstream file;
    file.open("MyText.txt", ios::in);
    if(file.is_open())
    {
        string line;
        int lineNumber = 0;
        while(getline(file, line))
        {
            lineNumber++;
            //cout << line << "\nline number:" << lineNumber << "\n\n";
            // Todo: do something with lineNumber and line.
            parseLinesToWords(line ,lineNumber);
            line.clear();
        }
    }
    else{
        cerr << "file can not be opened!";
        return 0;
    }
    file.close();

    cout << search(searchMe);
    return 0;
}

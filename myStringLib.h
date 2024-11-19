#ifndef MYSTRINGLIB_H_INCLUDED
#define MYSTRINGLIB_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


enum whatToCount {smallLetters = 1, capitalLetter = 2, all = 3};

string readString(string message){

    string myString;

    cout << message ; getline(cin >> ws, myString);

    return myString;
}
char readChar(string message)
{
    char charcter;

    cout << message ; cin >> charcter; cout << endl;
    return charcter;
}

string UpperFirstLetterFromEachWord(string myString){

    bool isFirstLetter = true;


    for(int i = 0; i < myString.length(); i++){
        if(myString[i] != ' ' && isFirstLetter)
           myString[i] = toupper(myString[i]);
        isFirstLetter = (myString[i] == ' ' ? true : false);
    }

    return myString;
}

short countLetter (string s, whatToCount type = whatToCount::all){

    if(type == whatToCount::all){
        return s.length();
    }

    short counter = 0;

    for(short i = 0; i < s.length(); i++)
    {
        if(type == whatToCount::capitalLetter && isupper(s[i]))
            counter++;
        if(type == whatToCount::smallLetters && islower(s[i]))
            counter++;
    }

    return counter;
}

short numOfLetter (string s, char letter, bool matchCase = true)
{
    int counter = 0;
    for(short i = 0; i < s.length(); i++){
        if(matchCase){
             if(letter == s[i])
                counter++;
        }else{
            if(tolower(s[i]) == tolower(letter))
                counter++;
        }
    }
    return counter;
}

bool isVoual (char c)
{
    c = tolower(c);
    return ((c == 'a') || (c == 'i') || (c == 'e')|| (c == 'o') || (c == 'u'));
}

short countVoual (string s)
{
    short counter = 0;

    for (short i = 0; i < s.length(); i++){
        if(isVoual(s[i]))
            counter++;
    }
    return counter;
}

void printEachWordInString (string s)
{
    string delimiter = " ";
    cout << "\n your string words are: \n\n";

    short pos = 0;
    string sword; //define a string variable

    //use find() function to get the position of delimiters
    while((pos = s.find(delimiter)) != string::npos){
        sword = s.substr(0, pos); //store the word
        if(sword != "")
        {
            cout << sword << endl;
        }

        s.erase(0, pos + delimiter.length()); // erase until position and move to next word.
    }
    if(s != "")
    {
        cout << s << endl;
    }
}

vector<string> splitString (string s, string delimiter)
{
    int pos = 0;
    vector<string> tokens;
    string sword;

    while( (pos = s.find(delimiter)) != string::npos ){

        sword = s.substr(0, pos);
        if(sword != "")
            tokens.push_back(sword);


        s.erase(0, pos + delimiter.length());
    }
    if(s != "")
        tokens.push_back(s);

    return tokens;
}
string joinString (vector<string> v, string separator)
{
    string s = "";

    for(string& item : v){
        s += item + separator;
    }
    return s.substr(0, s.length() - separator.length());
}
string joinString (string arr[100],int length, string separator)
{
    string s = "";

    for(int i = 0; i < length; i++){
        s += arr[i] + separator;
    }
    return s.substr(0, s.length() - separator.length());
}
string trimLeft (string s)
{
    for(int i = 0; i < s.length(); i++){
        if (s[i] != ' '){

            return s.substr(i, s.length() - i);
        }
    }
}
string trimRight (string s)
{
    for(int i = s.length() - 1; i >= 0; i--){
        if(s[i] != ' '){
            return s.substr(0, i+1);
        }
    }
}

string trim (string s)
{


    return (trimLeft(trimRight(s)));
}

string reverseWordsInString (string s)
{
    vector <string> items = splitString(s, " ");
    string s1 = "";

    vector<string>::iterator iter = items.end();

    while( iter != items.begin()){

        iter--;

        s1 += *iter + " ";
    }
    return trimRight(s1);
}
string lowerAll (string s)
{
    for(int i = 0; i < s.length(); i++){
        if(isupper(s[i]))
            s[i] = tolower(s[i]);
    }
    return s;
}

string removePunctuationsFromString(string s)
{
    string s2 = "";

    for(int i = 0; i < s.length(); i++){
        if(!ispunct(s[i]))
            s2 += s[i];
    }

    return s2;
}

string replaceWordInString (string s, string stringToReplace, string sReplaceTo)
{
    int pos = 0;

    while( (pos = s.find(stringToReplace)) != string::npos ){
        s = s.replace(pos, stringToReplace.length(), sReplaceTo);
    }

    return s;

}
string replaceWordInString2 (string s, string stringToReplace, string sReplaceTo,string separetor, bool matchCase = true)
{
    vector <string> vString = splitString(s, separetor);


    for( string &item : vString){
        if(matchCase){
            if(item == stringToReplace)
            item = sReplaceTo;
        }else{
            if(lowerAll(item) == lowerAll(stringToReplace))
                item = sReplaceTo;
        }
    }

    s = joinString(vString, " ");


    return s;

}

#endif // MYSTRINGLIB_H_INCLUDED

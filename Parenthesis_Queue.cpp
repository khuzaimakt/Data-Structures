//#include <iostream>
//#include<string>
//#include<fstream>
//using namespace std;
//
//template <class T>
// class Node
//{
//     T data;
//     Node<T>* next;
//public:
//    template <class T>
//    friend class Stack;
//    Node();
//    Node(const T val);
//    
//  
//};
//
// template <class T>
// class Stack
//{
//     Node<T>* top;
//public:
//    Stack();
//    bool IsEmpty();
//    bool push(const T& val);
//    bool pop(T& val);
//    T Top();
//    void print();
//    ~Stack();
//};
//
//
//class XMLData
//{
//public:
//    int lineNumber;
//    bool StartOrEnd;//0 -> start  and  1 -> end
//    string tagText;
//    XMLData();
//    void printXML();
//};
//
//
//template <class T>
// Node<T>::Node()
// { 
//     data = NULL;
//     next = NULL; 
// }
//
// template <class T>
// Node<T>::Node(const T d)
//{
//    data = d;
//}
//
// template <class T>
//Stack<T>::Stack()
//{
//    top = nullptr;
//}
//template <class T>
// bool Stack<T>::IsEmpty()
//{
//    if (top==nullptr)
//        return true;
//    return false;
//}
//
// template <class T>
// bool Stack<T>::pop(T& val)
//{
//    if (!IsEmpty())
//    {
//        val = top->data;
//
//        Node<T>* temp = top;
//        top = top->next;
//        temp->next = nullptr;
//        temp = nullptr;
//        return true;
//    }
//    return false;
//}
//
// template <class T>
// bool Stack<T>::push(const T& val)
//{
//    Node<T>* temp = new Node<T>(val);
//    temp->next = top;
//    top = temp;
//    return true;
//}
//
// template <class T>
// void Stack<T>::print()
//{
//    
//    for (Node<T>* temp = top; temp != nullptr; temp = temp->next)
//    {
//        cout << temp->data << " ";
//
//    }
//    cout << endl;
//}
// template <class T>
// T Stack<T>::Top()
//{
//    return top->data;
//}
//
// template <class T>
// Stack<T>::~Stack()
//{
//
//}
//
// 
//
//XMLData::XMLData()
//{
//    lineNumber = 0;
//    StartOrEnd = 0;
//}
//
//void XMLData::printXML()
//{
//    cout << "Tag name = " << tagText << ",  Line Number = " << lineNumber << ", ";
//    if (!StartOrEnd)
//        cout << "Starting tag\n";
//    else
//        cout << "Ending tag\n";
//}
//
//
//
//int main()
//{
//    Stack<XMLData> St;
//    int lineCounter = 1;
//    bool foundError = false;
//    bool attributeError = false;
//
//    ifstream fin;
//    fin.open("xml.txt");
//
//    while (!fin.eof())
//    {
//        XMLData xml;
//        string line;
//
//        getline(fin, line, '\n');//reads whole line so that line number can be tracked
//        int CurrentLineLength = line.length();
//
//        while (CurrentLineLength > 0)
//        {
//            int OpeningAngularBracketIndex = line.find('<');
//            int ClosingAngularBracketIndex = line.find('>');
//
//            if (OpeningAngularBracketIndex == -1 && ClosingAngularBracketIndex == -1)//if true, it means the current line contain no tag
//                break;
//
//            //NOTE: XML prolog is optional. If it exists, it must come first in the document.
//            if (line[OpeningAngularBracketIndex + 1] == '?')//if true, it's a prolog
//            {
//                if (lineCounter == 1)
//                {
//                    line = line.substr(OpeningAngularBracketIndex + 2, line.size());//ignore s[0]='<' and s[1]='?'
//                    CurrentLineLength = line.length();
//
//                    int endOfProlog = line.find("?>");
//                    if (endOfProlog == -1)//if false, it means prolog is complete
//                    {
//                        cout << "---- ERROR ---- \tThe prolog is not complete.\n";
//                        foundError = true;
//                        break;
//                    }
//                    else//if prolog is complete, then check if there is another tag
//                    {
//                        int secondAngularBracketIndex = line.find('<');
//                        if (secondAngularBracketIndex == -1)//if there is no other tag besides prolog, then clear the current line
//                        {
//                            CurrentLineLength = 0;
//                        }
//                        else//else, delete the contents of line before another tag (i.e., tag after prolog in the current line)
//                        {
//                            line = line.substr(secondAngularBracketIndex, line.size());
//                            CurrentLineLength = line.length();
//                        }
//
//                    }
//                }
//                else//if prolog is not in the first line; show error
//                {
//                    cout << "---- ERROR ---- \tProlog must be at the start of xml file.\n";
//                    foundError = true;
//                    break;
//                }
//
//            }
//            //check if there's a proper end of prolog
//            else if ((OpeningAngularBracketIndex == -1 || OpeningAngularBracketIndex > ClosingAngularBracketIndex) && line[ClosingAngularBracketIndex - 1] == '?')
//            {
//
//                if (lineCounter == 1)
//                {
//                    cout << "---- ERROR ---- \tThere's no start of prolog but its end exists.\n";
//                    foundError = true;
//                    break;
//                }
//                else
//                {
//                    cout << "---- ERROR ---- \tThere's no start of prolog but its end exists. It's at line " << lineCounter << " (prolog must be at line 1)\n";
//                    foundError = true;
//                    break;
//                }
//
//            }
//
//            //check if it's end of a comment
//            else if ((line[ClosingAngularBracketIndex - 1] == '-') && (line[ClosingAngularBracketIndex - 2] == '-') && (line.find("-->") == line.find("--")))
//            {
//                xml = St.Top();
//                if (xml.tagText == "Comment")
//                {
//                    St.pop(xml);
//                    //cout<<"Popped: "; xml.printXML();
//                }
//                else
//                {
//                    cout << "---- ERROR ---- \tfound closing tag of Comment at line " << lineCounter << ", but there's no starting tag for it.";
//                    foundError = true;
//                    break;
//                }
//
//                line = line.substr(ClosingAngularBracketIndex + 1, line.size());
//                CurrentLineLength = line.length();
//            }
//
//            //check if it's start of a simple tag with or without attribute.
//            else if ((line[OpeningAngularBracketIndex] == '<') && ((line[OpeningAngularBracketIndex + 1] >= 65 && line[OpeningAngularBracketIndex + 1] <= 90) || (line[OpeningAngularBracketIndex + 1] >= 97 && line[OpeningAngularBracketIndex + 1] <= 122))  /*&&  (OpeningAngularBracketIndex < ClosingAngularBracketIndex)*/)
//            {
//                xml.lineNumber = lineCounter;
//                xml.StartOrEnd = 0;
//
//                string Tag;
//                int FirstSpaceAfterTag = line.find(' ');
//
//                //check if there's an attribute
//                if (FirstSpaceAfterTag != -1 && (FirstSpaceAfterTag < ClosingAngularBracketIndex || ClosingAngularBracketIndex == -1))
//                {
//                    Tag = line.substr(1, FirstSpaceAfterTag - 1);
//
//                    line = line.substr(FirstSpaceAfterTag + 1, line.size());//delete tag name from current line
//
//                    int firstQuoteS = line.find("'");//find first single quote
//                    int firstQuoteD = line.find('"');//find first double quote
//
//                    //if first "double quote" exists and there's a charachter after that double quote (i.e., name of attribute)
//                    if (firstQuoteD < firstQuoteS && firstQuoteD != -1 && ((line[firstQuoteD + 1] >= 65 && line[firstQuoteD + 1] <= 90) || (line[firstQuoteD + 1] >= 97 && line[firstQuoteD + 1] <= 122)))
//                    {
//                        line = line.substr(firstQuoteD + 1, line.size());//delete line from start upto first double quote(icluding)
//
//                        int secondQuoteD = line.find('"');//find second double quote
//                        ClosingAngularBracketIndex = line.find('>');//update index of '>'
//
//                        //checking if current tag is properly closed; both when there's only one tag or multiple tags in a single line.
//                        if ((ClosingAngularBracketIndex == -1 || (secondQuoteD != -1 && secondQuoteD < ClosingAngularBracketIndex)) && ((line.find("\">") == -1) || (line.find("\">") != -1 && secondQuoteD < line.find("\">"))))
//                        {
//                            cout << "---- ERROR ---- \tNo proper closing of tag: <" << Tag << "> at line " << lineCounter;
//                            foundError = true;
//                            break;
//                        }
//                        //checking if current attribute is quoted; both when there's only one attribute or multiple attributes in a single line.
//                        else if (ClosingAngularBracketIndex != -1 && (secondQuoteD > ClosingAngularBracketIndex || secondQuoteD == -1))
//                        {
//                            cout << "---- ERROR ---- \tThe attribute is not properly quoted at line " << lineCounter;
//                            attributeError = true;
//                            break;
//                        }
//                    }
//
//                    //if first 'single quote' exists and there's a charachter after that single quote (i.e., name of attribute)
//                    else if (firstQuoteS != -1 && ((line[firstQuoteS + 1] >= 65 && line[firstQuoteS + 1] <= 90) || (line[firstQuoteS + 1] >= 97 && line[firstQuoteS + 1] <= 122)))
//                    {
//                        line = line.substr(firstQuoteS + 1, line.size());//delete line from start upto first single quote(icluding)
//
//                        int secondQuoteS = line.find("'");//find second 'single quote'
//                        ClosingAngularBracketIndex = line.find('>');//update index of '>'
//
//                        //checking if current tag is properly closed; both when there's only one tag or multiple tags in a single line.
//                        if ((ClosingAngularBracketIndex == -1 || (secondQuoteS != -1 && secondQuoteS < ClosingAngularBracketIndex)) && ((line.find("'>") == -1) || (line.find("'>") != -1 && secondQuoteS < line.find("'>"))))
//                        {
//                            cout << "---- ERROR ---- \tNo proper closing of tag: <" << Tag << "> at line " << lineCounter;
//                            foundError = true;
//                            break;
//                        }
//                        //checking if current attribute is quoted; both when there's only one attribute or multiple attributes in a single line.
//                        else if (ClosingAngularBracketIndex != -1 && (secondQuoteS > ClosingAngularBracketIndex || secondQuoteS == -1))
//                        {
//                            cout << "---- ERROR ---- \tThe attribute is not properly quoted at line " << lineCounter;
//                            attributeError = true;
//                            break;
//                        }
//                    }
//                }
//
//                else//if there's no attribute
//                    Tag = line.substr(1, ClosingAngularBracketIndex - 1);
//
//                xml.tagText = Tag;
//
//                St.push(xml);
//                //cout<<"Pushed: "; xml.printXML();
//
//                ClosingAngularBracketIndex = line.find('>');
//                line = line.substr(ClosingAngularBracketIndex + 1, line.size());
//                CurrentLineLength = line.length();
//            }
//            //icheck if it's end of a simple tag with or without attribute.
//            else if ((line[OpeningAngularBracketIndex] == '<') && (line[OpeningAngularBracketIndex + 1] == '/') && ((line[OpeningAngularBracketIndex + 2] >= 65 && line[OpeningAngularBracketIndex + 2] <= 90) || (line[OpeningAngularBracketIndex + 2] >= 97 && line[OpeningAngularBracketIndex + 2] <= 122)))
//            {
//                line = line.substr(OpeningAngularBracketIndex + 2, line.size());
//                int TagLength = line.find('>');
//                string Tag = line.substr(0, TagLength);
//
//                if (!St.IsEmpty())//check if there's a starting tag against incoming ending tag
//                    xml = St.Top();
//                else
//                {
//                    cout << "---- ERROR ---- \tfound closing tag: </" << Tag << "> at line " << lineCounter << ", but there's no starting tag for it.";
//                    foundError = true;
//                    break;
//                }
//
//
//                int x = xml.tagText.compare(Tag);
//                if (x == 0)
//                {
//                    St.pop(xml);
//                    //cout<<"Popped: "; xml.printXML();
//                }
//                else
//                {
//                    cout << "---- ERROR ---- \tThere MUST be a closing tag: </" << xml.tagText << "> before encountered closing tag i.e., </" << Tag << "> at line " << lineCounter;
//                    foundError = true;
//                    break;
//                }
//
//                line = line.substr(TagLength + 1, line.size());
//                CurrentLineLength = line.length();
//            }
//
//
//            //check if it's start of a comment
//            else if (line[OpeningAngularBracketIndex + 1] == '!' && line[OpeningAngularBracketIndex + 2] == '-' && line[OpeningAngularBracketIndex + 3] == '-')
//            {
//                line = line.substr(OpeningAngularBracketIndex + 4, line.size());// <!-- these 4 charachters are deleted from string
//                CurrentLineLength = line.length();
//
//                xml.lineNumber = lineCounter;
//                xml.StartOrEnd = 0;
//                xml.tagText = "Comment";
//
//                St.push(xml);
//                //cout<<"Pushed: "; xml.printXML();
//            }
//
//            //check if there are double dashes in the comment
//            else if (line.find("--") != line.find("-->"))
//            {
//                if (OpeningAngularBracketIndex == -1 && ClosingAngularBracketIndex == -1)
//                {
//                    CurrentLineLength = 0;
//                }
//                else
//                {
//                    cout << "---- ERROR ---- \tAt line " << lineCounter << ", Two dashes in the middle of a comment are not allowed.";
//                    foundError = true;
//                    break;
//                }
//
//            }
//        }
//
//        if (foundError || attributeError)
//            break;
//
//        lineCounter++;
//    }
//
//    //show error if stack is not empty
//    if (!St.IsEmpty() && !attributeError && !foundError)
//    {
//        cout << "---- ERROR ---- \tFound ";
//
//        if (St.Top().StartOrEnd == 0)
//            cout << "Starting";
//        else
//            cout << "Ending";
//
//        cout << " tag \"" << St.Top().tagText << "\" at line " << St.Top().lineNumber << " but it has no ";
//
//        if (St.Top().StartOrEnd == 0)
//            cout << "Ending";
//        else
//            cout << "Starting";
//
//        cout << " tag\n";
//    }
//    else if (!foundError && !attributeError)
//        cout << "No Error found in this xml file.\n";
//
//    fin.close();
//
//    return 0;
//}




#include <iostream>
#include<string>
#include<fstream>
using namespace std;

template <class T>
class Node
{
    T data;
    Node<T>* next;
public:
    template <class T>
    friend class Stack;
    Node();
    Node(const T val);


};

template<class T>
class SLinked
{
    Node<T>* head;


public:
    template<class T>
    friend class Stack;
    SLinked()
    {
        head = nullptr;
    }



};

template<class T>
class Stack
{
    SLinked<T>* S;

public:
    Stack() {
        S = new SLinked<T>();
    }


    bool IsEmpty()
    {
        if (S->head == nullptr)
        {
            return true;
        }
        else
            return false;
    }

    T Top()
    {
        return S->head->data;
    }
    bool pop(T& val)
    {
        if (!IsEmpty())
        {
            val = S->head->data;

            Node<T>* temp = S->head;
            S->head = S->head->next;
            temp->next = nullptr;
            temp = nullptr;
            return true;
        }
        return false;
    }

    bool push(T const& e)
    {
        Node<T>* t = new Node<T>(e);
        if (IsEmpty())
        {
            S->head = t;
            return true;
        }
        else
        {
            t->next = S->head;
            S->head = t;
            return true;
        }

    }

    void print()
    {
        if (IsEmpty())
        {
            cout << "Stack is empty" << endl;
        }

        for (Node<T>* t = S->head; t != nullptr; t = t->next)
        {
            cout << t->data << " " << endl;
        }
    }

    void printerror()
    {
        cout << "ERROR: Found ";

        if (this->Top().position == 0)
            cout << "Starting Tag" << endl;
        else
            cout << "Ending Tag" << endl;


        cout << this->Top().text << "\" at line " << this->Top().ln << " but it has no ";

        if (this->Top().position == 0)
            cout << "Ending tag" << endl;
        else
            cout << "Starting tag" << endl;


    }
};

class XMLData
{
public:
    int ln;
    bool position;
    string text;
    XMLData() {
        ln = 0;
        position = 0;
    }

};


template <class T>
Node<T>::Node()
{
    data = NULL;
    next = NULL;
}

template <class T>
Node<T>::Node(const T d)
{
    data = d;
}




void prologcheck(int OA, int CA, bool& flag, string & l, int& CLL)
{
    l = l.substr(OA + 2, l.size());
    CLL = l.length();


    int eop = l.find("?>");
    if (eop == -1)
    {
        flag = true;
        cout << "ERROR:The prolog is not complete." << endl;

        return;
    }
    else
    {
        int SA = l.find('<');
        if (SA == -1)
        {
            CLL = 0;
        }
        else
        {
            l = l.substr(SA, l.size());
            CLL = l.length();
        }

    }
}


void prologafterhead(int LC, bool& flag)
{
    if (LC == 1)
    {
        cout << "ERROR: There's no start of prolog but its end exists." << endl;;
        flag = true;
        return;
    }
    else
    {
        cout << "ERROR: There's no start of prolog but its end exists. It's at line " << LC << " Prolog must be at line 1";
        flag = true;
        return;
    }
}


void commentendcheck(XMLData & x, Stack<XMLData>&S1, string & l, bool& flag, int& CLL, int& CA, int LC)
{
    x = S1.Top();
    if (x.text == "Comment")
    {
        S1.pop(x);

    }
    else
    {
        cout << "ERROR: Found closing tag of Comment at line " << LC << ", but there's no starting tag for it.";
        flag = true;
        return;;
    }

    l = l.substr(CA + 1, l.size());
    CLL = l.length();
}


void engoftag(XMLData & x, Stack<XMLData>&S1, string & l, bool& flag, int& CLL, int& CA, int& OA, int LC)
{
    l = l.substr(OA + 2, l.size());
    int TL = l.find('>');
    string T = l.substr(0, TL);

    if (!S1.IsEmpty())
        x = S1.Top();
    else
    {
        cout << "ERROR:found closing tag: </" << T << "> at line " << LC << ", but there's no starting tag for it.";
        flag = true;
        return;
    }


    int X = x.text.compare(T);
    if (X == 0)
    {
        S1.pop(x);

    }
    else
    {
        cout << "ERROR: There MUST be a closing tag: </" << x.text << "> before encountered closing tag i.e., </" << T << "> at line " << LC;
        flag = true;
        return;
    }

    l = l.substr(TL + 1, l.size());
    CLL = l.length();
}

void singleordoublequote(XMLData & x, Stack<XMLData>&S1, string & l, bool& flag, int& CLL, int& CA, int& OA, int LC)
{

    x.ln = LC;
    x.position = 0;

    string Tag;
    int FS = l.find(' ');


    if (FS != -1 && (FS < CA || CA == -1))
    {
        Tag = l.substr(1, FS - 1);

        l = l.substr(FS + 1, l.size());

        int fqs = l.find("'");
        int fqd = l.find('"');


        if ((fqd < fqs || fqs == -1) && fqd != -1)
        {
            l = l.substr(fqd + 1, l.size());

            int sqd = l.find('"');
            CA = l.find('>');


            if ((CA == -1 || (sqd != -1 && sqd < CA)) && ((l.find("\">") == -1) || (l.find("\">") != -1 && sqd < l.find("\">"))))
            {
                cout << " ERROR: No proper closing of tag: <" << Tag << "> at line " << LC << endl;
                flag = true;
                return;
            }

            else if (CA != -1 && (sqd > CA || sqd == -1))
            {
                cout << "ERROR: The attribute is not properly quoted at line " << LC << endl;
                flag = true;
                return;
            }
        }


        else if (fqs != -1)
        {
            l = l.substr(fqs + 1, l.size());

            int sqs = l.find("'");
            CA = l.find('>');


            if ((CA == -1 || (sqs != -1 && sqs < CA)) && ((l.find("'>") == -1) || (l.find("'>") != -1 && sqs < l.find("'>"))))
            {
                cout << "ERROR: No proper closing of tag: <" << Tag << "> at line " << LC;
                flag = true;
                return;
            }

            else if (CA != -1 && (sqs > CA || sqs == -1))
            {
                cout << "ERROR: The attribute is not properly quoted at line " << LC;
                flag = true;
                return;
            }
        }
        CLL = 0;
    }

    else

        Tag = l.substr(1, CA - 1);

    x.text = Tag;
    S1.push(x);
    CA = l.find('>');
    l = l.substr(CA + 1, l.size());
    if (CLL == l.length() && CA == -1) {
        cout << "ERROR: No ending bracket for " << Tag << endl;
        flag = true;
        return;
    }
    CLL = l.length();

}

void doubledash(int OA, int CA, bool& flag, int& CLL, int LC)
{
    if (OA == -1 && CA == -1)
    {
        CLL = 0;
    }
    else
    {
        cout << "ERROR: At line " << LC << ", Two dashes in the middle of a comment are not allowed.";
        flag = true;
        return;
    }

}

void startofcomment(XMLData & x, Stack<XMLData>&S1, string & l, int& CLL, int OA, int LC)
{
    l = l.substr(OA + 4, l.size());
    CLL = l.length();

    x.ln = LC;
    x.position = 0;
    x.text = "Comment";

    S1.push(x);

}

int main()
{

    Stack<XMLData> S1;
    int LC = 1;
    bool flag = false;

    XMLData x;
    string l;
    ifstream fin;
    fin.open("xml.txt");

    while (!fin.eof())
    {


        getline(fin, l, '\n');
        int CLL = l.length();

        while (CLL > 0)
        {
            int OA = l.find('<');
            int CA = l.find('>');
            if ((OA != -1 && l[OA + 1] == '/') && CA == -1)
            {
                cout << " Mismatch of tag </>" << " at line " << LC << endl;
                flag = true;
                break;
            }

            if (OA == -1 && CA == -1)
                break;


            if (l[OA + 1] == '?')
            {
                if (LC == 1)
                {
                    prologcheck(OA, CA, flag, l, CLL);
                    if (flag)
                        break;
                }
                else
                {
                    cout << "ERROR: Prolog must be at the start of xml file." << endl;
                    flag = true;
                    break;
                }

            }

            else if (CA != -1 && ((OA == -1 || OA > CA) && l[CA - 1] == '?'))
            {

                prologafterhead(LC, flag);
                if (flag)
                    break;

            }


            else if (CA != -1 && (l[CA - 1] == '-') && (l[CA - 2] == '-') && (l.find("-->") == l.find("--")))
            {
                commentendcheck(x, S1, l, flag, CLL, CA, LC);
                if (flag)
                    break;
            }

            else if (OA != -1 && (l[OA] == '<') && (l[OA + 1] == '/') && ((l[OA + 2] >= 65 && l[OA + 2] <= 90) || (l[OA + 2] >= 97 && l[OA + 2] <= 122)))
            {
                engoftag(x, S1, l, flag, CLL, CA, OA, LC);
                if (flag)
                    break;
            }

            else if (OA != -1 && (l[OA] == '<') && ((l[OA + 1] >= 65 && l[OA + 1] <= 90) || (l[OA + 1] >= 97 && l[OA + 1] <= 122)))
            {
                singleordoublequote(x, S1, l, flag, CLL, CA, OA, LC);
                if (flag)
                    break;
            }
            else if (l.find("--") != l.find("-->"))
            {
                doubledash(OA, CA, flag, CLL, LC);
                if (flag)
                    break;
            }




            else if (l[OA + 1] == '!' && l[OA + 2] == '-' && l[OA + 3] == '-')
            {
                startofcomment(x, S1, l, CLL, OA, LC);
                if (flag)
                    break;
            }



        }

        if (flag)
            break;

        LC++;
    }


    if (!S1.IsEmpty() && !flag)
    {
        S1.printerror();

    }
    else if (flag == false)
        cout << "No Error found in this xml file." << endl;

    fin.close();

    return 0;
}

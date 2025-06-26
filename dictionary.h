#include <bits/stdc++.h>
using namespace std;

//1.convert letter in lowercase
string toLower(string s)
{
    // using transform() function and ::tolower in STL
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
//2. First word will be capital
string capitalizeFirstLetter(string text)
{
    if (text.empty()) return text;

    text[0]= toupper(text[0]); // Convert first character to uppercase
    transform(text.begin()+ 1, text.end(), text.begin()+ 1, ::tolower); // Lowercase the rest

    return text; // Return formatted text
}
//3.first meaning letter will be capital
string capitalizeFirstMeaning(string text)
{
    if (text.empty()) return text;
    text[0]= toupper(text[0]); // Capitalize only the first letter.

    return text;


}

class Node
{
public:
    string word, meaning;
    Node *L, *R;
    Node(string w, string m)
    {
        word= w;
        meaning= m;
        L=nullptr;
        R=nullptr;
    }
};

class Dictionary
{
public:


    Node*create(Node* root, string w, string m)
    {
        w = capitalizeFirstLetter(w);
        m = capitalizeFirstMeaning(m);
        if(root==nullptr)
        {
            root=new Node(w, m); //store words in original case
        }

        else if(toLower(w) >= toLower(root->word))
            root->R= create(root->R, w, m);

        else
            root->L= create(root->L, w, m);
        return root;

    }
//inorder
    void inorder(Node* root)
    {
        if(root!=nullptr)
        {
            inorder(root->L);
            cout<<root->word<<": "<<root->meaning <<endl ;
            inorder(root->R);
        }
    }

    void search(Node* root, string w)
    {
        if (root== nullptr)
        {
            cout << "Not Found!" << endl;
            return;
        }

        if (toLower(w)== toLower(root->word))
        {
            cout <<root->word << ": " << root->meaning << endl;
            return;
        }

        if (toLower(w)< toLower(root->word))
        {
            search(root->L, w);// Search left subtree

        }
        else
        {
            search(root->R, w); // Search right subtree
        }
    }


//Particular element delete
    Node* deleteNode(string w, Node* root)
    {
        if(root!=nullptr)  //base case
        {
            if(toLower(w) < toLower(root->word))
                root->L=deleteNode(w, root->L);

            else if(toLower(w) > toLower(root->word))
                root->R=deleteNode(w, root->R);
            else
            {
//case-1
                if(root->L==nullptr && root->R==nullptr)
                {
                    Node*temp=root;
                    delete temp;
                    root=nullptr;
                    return root;
                }
// case-2 for right child
                else if(root->L == nullptr && root->R !=nullptr)
                {
                    Node*temp=root;
                    root=root->R;
                    delete temp;
                    return root;
                }
//case 2 for left child
                else if (root->L !=nullptr && root->R !=nullptr)
                {
                    Node*temp=root;
                    root=root-> L;
                    delete temp;
                    return root;
                }

                else
                {
                    string minWord= findmin(root->R);
                    root->word= minWord;
                    root->meaning = ""; // delete the meaning when delete the word
                    root->R= deleteNode(minWord,root->R);
                }

            }

            return root;
        }
    }
//findmin
    string findmin(Node*root)
    {
        if (root == nullptr) return "";
        if(root->L==nullptr)
        {
            cout<<"\nSmallest element: "<<root->word<<endl;
            return root->word;
        }

        return findmin(root->L);
    }

// find the nearest words
    void findNearestWord(Node* root, string query, string &closestWord)
    {
        if(root== nullptr) return;

        if (abs(query[0] - root->word[0]) < abs(query[0] - closestWord[0]))
        {
            closestWord = root->word;
        }

        findNearestWord(root->L, query, closestWord);
        findNearestWord(root->R, query, closestWord);
    }

    void searchNearestWord(Node* root, string query)
    {
        if (root== nullptr)
        {
            cout << "No similar words found!" << endl;
            return;
        }

        string closestWord= root->word;
        findNearestWord(root, query, closestWord);

        cout << "Did you mean: " << closestWord << "?" << endl;
    }


    Node* loadFromFile(Node* root, string Dictionary)
    {
        ifstream file(Dictionary);

        if (!file)
        {
            cout <<"Error opening file!";
            return root;
        }

        string w, m, temp;
        while (file>> w)
        {
            m= "";
            while (file.peek()!='\n' && file>> temp)
            {
                m+= (m.empty() ? "" : " ") + temp;
            }
            root= create(root, w, m);
        }

        file.close();
        return root;
    }
};

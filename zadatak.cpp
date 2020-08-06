#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<cctype>
#include<algorithm>

using namespace std;
using std::string;


int m,n;
//char img[250][250];
string **img;

bool validCoordinates(int x,int y){
    return (x<n && x>=0 && y<m && y>=0);
}

void displayWrongParametersMessage(){
    cout << "Wrong parameters!" <<endl;
}

vector<string> tokenize(string const & str, char delimiter)
{
    string s;
    
    vector<string> tokenized;
    stringstream tmp_str(str);
    
    while(getline(tmp_str,s,delimiter)){
        tokenized.push_back(s);
    }
    
    return tokenized;
}

void colorPixel(int x,int y,string color){
    if(!validCoordinates(x,y)){
        return displayWrongParametersMessage();
    }

    img[x][y]=color;
}

string getColor(int x,int y){
    if(!validCoordinates(x,y)){
        return "";
    }
    return img[x][y];
}

void fillRegion(int x,int y,string color)
{   
    string current_color=getColor(x,y);
    colorPixel(x,y,color);
    
    if(current_color=="")
        return;
    if(getColor(x,y-1)==current_color) 
        fillRegion(x,y-1,color);
    if(getColor(x,y+1)==current_color) 
        fillRegion(x,y+1,color);
    if(getColor(x-1,y)==current_color) 
        fillRegion(x-1,y,color);
    if(getColor(x+1,y)==current_color) 
        fillRegion(x+1,y,color);
}

void initializePicture(string m_,string n_)
{
    m=stoi(m_), n=stoi(n_);
    int row,col;
    if(m>250 || m<1 || n>250 || n<1)
        return displayWrongParametersMessage();
    int i;

    img=new string*[n];

    for(i=0;i<n;i++)
        img[i]=new string[m];
    
    

    for(row=0;row<n;row++){
        for(col=0;col<m;col++){
            colorPixel(row,col,"O");
        }
    }
}

void clearPicture()
{
    int row,col;
    for(row=0;row<n;row++){
        for(col=0;col<m;col++){
            colorPixel(row,col,"O");
        }
    }
}

// funkcija uzeta sa stack overlow-a...https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void colorVerticalSegment(string x_,string y1_,string y2_,string color)
{
    int x,y1,y2;
    if(isNumber(x_) && isNumber(y1_) && isNumber(y2_))
        x=stoi(x_), y1=stoi(y1_),y2=stoi(y2_);
    else{
        return displayWrongParametersMessage();
    }
   
    int r;
    for(r=y1-1;r<y2;r++)
        colorPixel(r,x-1,color);
}

void colorHorizontalSegment(string x1_,string x2_,string y_,string color)
{
    int x1,x2,y;
    if(isNumber(x1_) && isNumber(x2_) && isNumber(y_))
        x1=stoi(x1_), x2=stoi(x2_),y=stoi(y_);
    else{
        return displayWrongParametersMessage();
    }
            
    int c;
    for(c=x1-1;c<x2;c++)
        colorPixel(y-1,c,color);
}

void showPicture()
{
    int row,col;
    for(row=0;row<n;row++){
        for(col=0;col<m;col++){
            cout << img[row][col];
        }
        cout << endl;
    } 
}

int main()
{
    string c,tmp;
    int row,col;
    bool end=0;

    while(!end)
    {
        vector<string> tokenized;
        getline(cin,tmp);
        tokenized=tokenize(tmp,' ');

        switch(tmp[0])
        {
        case 'I':
            initializePicture(tokenized[1],tokenized[2]);
            break;
        case 'C':
            clearPicture();
            break;
        case 'L':
            colorPixel(stoi(tokenized[2])-1,stoi(tokenized[1])-1,tokenized[3]);
            break;
        case 'V':
            colorVerticalSegment(tokenized[1],tokenized[2],tokenized[3],tokenized[4]);
            break;
        case 'H':
            colorHorizontalSegment(tokenized[1],tokenized[2],tokenized[3],tokenized[4]);
            break;
        case 'F':
            fillRegion(stoi(tokenized[1])-1,stoi(tokenized[2])-1,tokenized[3]);
            break;
        case 'S':
            showPicture();
            break;
        case 'X':
            end=1;
            break;
        }   
    }

    return 0;
}
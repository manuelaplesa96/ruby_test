#include<iostream>
#include<string>


using namespace std;
using std::string;

int m,n;
char img[250][250];

void fill_the_region(int x,int y,char color,char old_color)
{
    int old_x=x,old_y=y;
    img[x][y]=color;
    while(img[++x][y]==old_color && x<=n)
    {
        img[x][y]=color;
    }
    x=old_x,y=old_y;
    while(img[x][++y]==old_color && y<=m)
    {
        img[x][y]=color;
    }
    x=old_x,y=old_y;
    while(img[--x][y]==old_color && x>=0)
    {
        img[x][y]=color;
    }
    x=old_x,y=old_y;
    while(img[x][--y]==old_color && y>=0)
    {
        img[x][y]=color;
    }
    x=old_x,y=old_y;
    if(img[x-1][y-1]==old_color)
        fill_the_region(x-1,y-1,color,old_color);
    if(img[x-1][y+1]==old_color)
        fill_the_region(x-1,y+1,color,old_color);
    if(img[x+1][y-1]==old_color)
        fill_the_region(x+1,y-1,color,old_color);
    if(img[x+1][y+1]==old_color)
        fill_the_region(x+1,y+1,color,old_color);
    if(x>n || x<1 || y>m || y<1)
        return;
}

int main()
{
    string c,tmp;
    int row,col;

    while(1)
    {
        getline(cin,tmp);
        if(tmp[0]=='I') // new image
        { 
            int i=2;
            string digit;
            // očita m
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            }    
            while(isdigit(tmp[i]))
                digit+=tmp[i++];
            m=stoi(digit); i++;

            string digit2;
            // očita n
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit2+=tmp[i++];
            n=stoi(digit2);
            
            if(m>250 || m<1 || n>250 || n<1)
            {
                cout << "Wrong!" <<endl;
                break;
            }
            for(row=0;row<n;row++)
            {
                for(col=0;col<m;col++)
                {
                    img[row][col]='O';
                }
            }             
        }
        else if(tmp[0]=='C') // clear table -> all pixels to O
        { 
            for(row=0;row<n;row++)
            {
                for(col=0;col<m;col++)
                {
                    img[row][col]='O';
                }
            } 
        }
        else if(tmp[0]=='L') // color pixel (x,y) with color C
        { 
            int i=2,x,y;
            string digit;
            // očita x
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit+=tmp[i++];
            x=stoi(digit); i++;

            string digit2;
            // očita y
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit2+=tmp[i++];
            y=stoi(digit2); i++;
            
            if(x>n || x<1 || y>m || y<1)
            {
                cout << "Wrong!" <<endl;
                break;
            }
            char color=tmp[i];
            img[y-1][x-1]=color;

        }
        else if(tmp[0]=='V') // vertical segment of color C in column x between Y1 and Y2        
        { 
            string digit;
            int x,y1,y2,i=2;
            // očita stupac
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit+=tmp[i++];
            x=stoi(digit); i++;

            
            string digit2;
            // očita y1
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit2+=tmp[i++];
            y1=stoi(digit2); i++;

            string digit3;
            // očita y1
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit3+=tmp[i++];
            y2=stoi(digit3); i++;
            
            if(x>n || x<1 || y1>m || y1<1 || y2>m || y2<1)
            {
                cout << "Wrong!" <<endl;
                break;
            }  
            char color=tmp[i];
            int r;
            for(r=y1-1;r<y2;r++)
                img[r][x-1]=color;
            
            
        }
        else if(tmp[0]=='H') // horizontal segment of color C in row y between x1 and x2
        { 
            string digit;
            int x1,x2,y,i=2;
            // očita redak
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit+=tmp[i++];
            x1=stoi(digit); i++;
            
            string digit2;
            // očita y1
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit2+=tmp[i++];
            x2=stoi(digit2); i++;

            string digit3;
            // očita y1
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit3+=tmp[i++];
            y=stoi(digit3); i++;
             
            if(x1>n || x2<1 || x2>n || x2<1 || y>m || y<1)
            {
                cout << "Wrong!" <<endl;
                break;
            }  
            char color=tmp[i];
            int c;
            for(c=x1-1;c<x2;c++)
                img[y-1][c]=color;
            
        }
        else if(tmp[0]=='F') // fill the region
        {
            int i=2,x,y;
            string digit;
            // očita x
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit+=tmp[i++];
            x=stoi(digit); i++;

            string digit2;
            // očita y
            if(isdigit(tmp[i])==0)
            {
                cout << "Wrong!" <<endl;
                break;
            } 
            while(isdigit(tmp[i]))
                digit2+=tmp[i++];
            y=stoi(digit2); i++;
            
            if(x>n || x<1 || y>m || y<1)
            {
                cout << "Wrong!" <<endl;
                break;
            }
            char color=tmp[i];
            char old_color=img[x-1][y-1];
            fill_the_region(x-1,y-1,color,old_color);  
        }
        else if(tmp[0]=='S') // print
        { 
            for(row=0;row<n;row++)
            {
                for(col=0;col<m;col++)
                {
                    cout << img[row][col];
                }
                cout << endl;
            } 
        }
        else if(tmp[0]=='X') // end
            break;
        
    }

    return 0;
}
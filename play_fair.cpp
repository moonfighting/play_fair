#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

vector<char> transformed_key(string key)//transform the key to a char vector 将密钥转换为字符向量
{
    vector<char> letters;
    char c;
    letters.push_back(key[0]);
    for(int i=1;i<key.size();i++)
    {
        c=key[i];
        if(c==' '||c=='z')
            continue;
        else
        {
            int j=0;
            while(c!=letters[j])
            {
                if(j==letters.size())
                    letters.push_back(c);
                else 
                  j++;
            }
        }
            
    }
    vector<char>::const_iterator c_iter=letters.begin();
 /*   while(c_iter!=letters.end())
    {
        cout<<*c_iter;
        ++c_iter;
    }*/
    cout<<endl;
    return letters;
}

vector<vector<char> >builded_matrix(vector<char>letters)
{
    
    vector<vector<char> > letter_matrix;
    vector<char>row;
    vector<char>::const_iterator iter=letters.begin();
    vector<char>letter_table;
    char a='a';
    while(a!='z')
    {
        letter_table.push_back(a);
        a++;
    }
    vector<char>::iterator l_table_iter=letter_table.begin();
    vector<char>::iterator p2;
    while(l_table_iter!=letter_table.end())
    {
        p2=find(letters.begin(),letters.end(),*l_table_iter);
        if(p2!=letters.end())
        {
            l_table_iter=letter_table.erase(l_table_iter);
        }
        else
        l_table_iter++;
    }
   /* for(int i=0;i<letter_table.size();i++)
    {
        cout<<letter_table[i]<<" ";
    }*/
    cout<<endl;
    while(iter!=letters.end())
    {
        row.push_back(*iter);
        if(row.size()==5)
        {
            letter_matrix.push_back(row);
            row.clear();
        }
        iter++;
    }
    l_table_iter=letter_table.begin();
    while(l_table_iter!=letter_table.end())
    {
        row.push_back(*l_table_iter);
        if(row.size()==5)
        {
            letter_matrix.push_back(row);
            row.clear();
        }
        l_table_iter++;
    }
    
    return letter_matrix;
}

vector<char> transformed_sentence(string sentence)
{
    vector<char>word;
    for(int i=0;i<sentence.size();i++)
    {
        if(sentence[i]>=65&&sentence[i]<90)
            word.push_back(tolower(sentence[i]));
        else if(sentence[i]>=97&&sentence[i]<=121)
            word.push_back(sentence[i]);
        else
            continue;
    }
    
    vector<char>::iterator p=word.begin();
   /* for(p;p!=word.end();p++)
        cout<<*p<<" ";
    cout<<endl;*/
    p=word.begin();
    if(word.begin()!=word.end())
    {
        while(p<word.end())
        {
            if((p+1)==word.end())
            {
                word.push_back(*p=='x'?'q':'x');
                p=word.end();
            }
            else if(*p==*(p+1))
            {
                p=word.insert(p+1,(*p=='x'?'q':'x'));
                p=p+1;
            }
            else
                p+=2;   
        }
    
      /*  p=word.begin();
        for(p;p!=word.end();p++)
        {
            cout<<*p<<" ";
        }
        cout<<endl;*/
        return word;
    }
    else
        exit(-1);
}

string encode_result(vector<char>words,vector<vector<char> >matrix)
{
    vector<char>result;
    int first_row;
    int first_col;
    int second_row;
    int second_col;
    for(int i=0;i<words.size();i+=2)
    {
        for(int r=0;r<matrix.size();r++)
        {
            for(int c=0;c<matrix[0].size();c++)
            {
                if(words[i]==matrix[r][c])
                {
                    first_row=r;
                    first_col=c;
                }
               else if(words[i+1]==matrix[r][c])
                {
                    second_row=r;
                    second_col=c;
                }
    
            }
        }
        
        if(first_row==second_row)
        {
            if(first_col==(matrix[0].size()-1)&&second_col!=4)
                {
                    first_col=0;
                    second_col+=1;
                }
            else if(second_col==(matrix[0].size()-1)&&first_col!=4)
                {
                    second_col=0;
                    first_col+=1;
                }
            else
            {
                first_col+=1;
                second_col+=1;
            }
       }
        
        else if(first_col==second_col)
        {
            if(first_row==(matrix.size()-1)&&second_row!=4)
            {
                first_row=0;
                second_row+=1;
            }
            else if(second_row==(matrix.size()-1)&&first_row!=4)
            {
                second_row=0;
                first_row+=1;
            }
            else
            {
                first_row+=1;
                second_row+=1;
            }
        }
        
        else if(first_row!=second_row&&first_col!=second_col)
        {
            int temp1;
            temp1=first_col;
            first_col=second_col;
            second_col=temp1;
        }
        result.push_back(matrix[first_row][first_col]);
        result.push_back(matrix[second_row][second_col]);
    }
    string result_code;
    for(int k=0;k<result.size();k++)
    {
        result_code+=result[k];
    }
    return result_code;
    
}

string decodes(string words,vector<vector<char> > matrix)
{
    vector<char>result;
    string result_code;
    int first_row;
    int first_col;
    int second_row;
    int second_col;
    for(int i=0;i<words.size();i+=2)
    {
        for(int r=0;r<matrix.size();r++)
        {
            for(int c=0;c<matrix[0].size();c++)
            {
                if(words[i]==matrix[r][c])
                {
                    first_row=r;
                    first_col=c;
                }
               else if(words[i+1]==matrix[r][c])
                {
                    second_row=r;
                    second_col=c;
                }
    
            }
        }
        
        if(first_row==second_row)
        {
            if(first_col==0&&second_col!=0)
                {
                    first_col=4;
                    second_col-=1;
                }
            else if(second_col==0&&first_col!=0)
                {
                    second_col=4;
                    first_col-=1;
                }
            else
            {
                first_col-=1;
                second_col-=1;
            }
       }
        
        else if(first_col==second_col)
        {
            if(first_row==0&&second_row!=0)
            {
                first_row=4;
                second_row-=1;
            }
            else if(second_row==0&&first_row!=0)
            {
                second_row=4;
                first_row-=1;
            }
            else
            {
                first_row-=1;
                second_row-=1;
            }
        }
        
        else if(first_row!=second_row&&first_col!=second_col)
        {
            int temp1;
            temp1=first_col;
            first_col=second_col;
            second_col=temp1;
        }
        result.push_back(matrix[first_row][first_col]);
        result.push_back(matrix[second_row][second_col]);
    }
    for(int k=0;k<result.size();k++)
    {
        result_code+=result[k];
    }
    return result_code;
}
    
int main(int argc,char **argv)
{
    string key;
    string sentence;
    cout<<"请输入密钥:"<<endl;
    getline(cin,key);
    cout<<"请输入要加密的英文:"<<endl;
    getline(cin,sentence);
    cout<<"key:"<<key<<" "<<"密文:"<<sentence<<endl;
    vector<char>letters=transformed_key(key);
    vector<vector<char> > letter_matrix=builded_matrix(letters);
    for(int i=0;i<letter_matrix.size();i++)
    {
        for(int j=0;j<letter_matrix[i].size();j++)
        {
            cout<<letter_matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    vector<char>words=transformed_sentence(sentence);
    string codes=encode_result(words,letter_matrix);
    cout<<"加密后的密文为:"<<endl;
    cout<<codes<<endl;
    string decode_words=decodes(codes,letter_matrix);
    cout<<"解密后的密文为:"<<endl;

    cout<<decode_words<<endl;
    return 0;
}


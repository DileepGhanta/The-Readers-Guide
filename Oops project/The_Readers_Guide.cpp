#include<iostream>
#include<conio.h>
#include<cstring>
#include<time.h>
#include<windows.h>
#include<fstream>
#include<vector>
#include"password.hpp"
using namespace std;
string info="";
class User_details{
    protected:
    string user_name,password;
    friend void user_login();
};
class Books_Searched: protected User_details{
    protected:
    int index =0;
    string books[300];
    friend void book_details(string); 
    friend void logout();
}b;
void print_searchbar(string s) {
   cout<<"\t\t\t\t\t\t\t---------------------------------\n";
   cout<<"\t\t\t\t\t\t\t\x1b[1;33m"<<s<<"|                          \n";
   cout<<"\x1b[0;39m";
   cout<<"\t\t\t\t\t\t\t---------------------------------\n\n\n";   
}
void printmat(int line_ct,vector<string> &v){
    cout<<"\n\n";
    cout<<"\t\t\t\t\t\x1b[38;5;161m"<<v[0]<<endl;
    cout<<"\x1b[0;0m\n";
    for (int i = 1; i < v.size(); i++){
        if (i == line_ct){
            cout << "\t\t\t\t\t\t\t>";
            cout << "\x1b[1;36m" << v[i] << "\x1b[22;0m\n"<<endl;
        }
        else{
            cout << "\t\t\t\t\t\t\t" << v[i] << "\n\n";
            printf(" ");
        }
    }
}
void display_menu();
void book_details(string s){
    system("cls");
    string sym="_|_";
    int count=0,ct=0;
    ifstream in("Book_Details.txt");
    cout<<"\n\n\n\n\n\n\n";
    while(!in.eof()){
        string k="";
        getline(in,k);
        size_t found = k.find(s);//size_t typedef of unsigned int
        if((found!=string::npos) || ct==1){
            ct=1;
            if(k == sym){
                count++;
                if(count==2){
                    in.close();
                    break;
                }
            }
            else {
                cout<<"\x1b[22;32m";
               cout<<"\t\t\t\t\t\t"<<k<<endl;
            }
        }
    }
    cout<<"\x1b[2;0m";
    cout<<"\n\n\n\n\n\t\t\t\t\t\tPress any key to continue... ";
    int ch;
    ch=getch();
    fflush(stdin);
    b.books[b.index++]=s;
    display_menu();
}
void display_genres_books(string input_string){
    vector<string> s;
    int index=0;
    string s1=input_string;
    string sym="_|_";
    int ct=0;
    string book;
    int count=0;
    ifstream in("Genres_Books.txt");
    while(!in.eof()){
        string k="";
        getline(in,k);
        size_t found = k.find(s1);//size_t typedef of unsigned int
        if((found!=string::npos) || ct==1){
                ct=1;
            if(k == sym){
                count++;
                if(count==2){
                    in.close();
                    break;
                }
            }
            else {
                s.push_back(k);
                index++;
            }
        }
    }
    int ch;
    system("cls");
    printmat(1,s);
    int ct0 = 1;
    while (true){
        ch = getch();
        if (ch == 72){
            if (ct0 <= 1)
                ct0 = s.size()-1;
            else
                ct0--;
        }
        else if (ch == 80){
            if (ct0 == s.size()-1)
                ct0 = 1;
            else
                ct0++;
        }
        else if (ch == 13){
            system("cls");
            book=s[ct0];
            break;
        }
        system("cls");
        printmat(ct0,s);
    }
    book_details(book);
}
void display_Author_books(string input_string){
    vector<string> s;
    int index=0;
    string s1=input_string;
    string sym="_|_";
    string book;
    int ct=0;
    int count=0;
    ifstream in("Author_Books.txt");
    while(!in.eof()){
        string k="";
        getline(in,k);
        size_t found = k.find(s1);//size_t typedef of unsigned int
        if((found!=string::npos) || ct==1){
                ct=1;
            if(k == sym){
                count++;
                if(count==2){
                    in.close();
                    break;
                }
            }
            else {
                s.push_back(k);
                index++;
            }
        }
    }
    int ch;
    system("cls");
    printmat(1,s);
    int ct0 = 1;
    while (true){
        ch = getch();
        if (ch == 72){
            if (ct0 <= 1)
                ct0 = s.size()-1;
            else
                ct0--;
        }
        else if (ch == 80){
            if (ct0 == s.size()-1)
                ct0 = 1;
            else
                ct0++;
        }
        else if (ch == 13){
            system("cls");
            book= s[ct0];
            break;
        }
        system("cls");
        printmat(ct0,s);
    }
    book_details(book);
}
void print_logo(int t){
    if(t==0){
        system("cls");
       cout<<"\x1b[1;31m"; 
        FILE *ptr = fopen("logo.txt", "r");
        char ch;
        int ct=0;
        while (ch != EOF){
            ct++;
            ch = fgetc(ptr);
           cout<<ch;
            if(ct%4==0) Sleep(3);
        }
       cout<<"\x1b[2;0m"; 
        fflush(stdin);
    }
    else{
        system("cls");
       cout<<"\x1b[1;31m";//colours
        FILE *ptr = fopen("logo.txt", "r");
        char ch;
        int ct=0;
        while (ch != EOF){
            ct++;
            ch = fgetc(ptr);
         cout<<ch;
        }
      cout<<"\x1b[2;0m"; 
        fflush(stdin);
    }
      cout<<endl;
}
void print_ThankYou(){
    system("cls");
       cout<<"\x1b[1;36m";//colours
        FILE *ptr = fopen("Thank_you.txt", "r");
        char ch;
        while (ch != EOF){
            ch = fgetc(ptr);
         cout<<ch;
        }
      cout<<"\x1b[22;0m"; 
      fflush(stdin);
      cout<<endl;
}
void logout(){
        time_t ltime;
        time(&ltime);
        ofstream out("login_history.txt",ios::app);
        if(b.index==0)
        out<<"No Books Searched"<<endl;
        for(int i=0;i<b.index;i++)
        out<<i+1<<".) "<<b.books[i]<<endl;
        out<<"Logout at : "<<ctime(&ltime);
        out<<endl;
        out.close();
        system("cls");
        print_ThankYou();
}
void user_login(){
    User_details user;
   cout<<"      \t\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\t\xdb\xdb            \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\t\xdb\xdb Login Page \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\t\xdb\xdb            \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n\n";
   cout<<"      \t\t\t\t\t\t.--------------------------------------------------.\n";
   cout<<"      \t\t\t\t\t\t|   Password should contain atleast 8 characters   |\n";
   cout<<"      \t\t\t\t\t\t'--------------------------------------------------'\n\n\n";
   cout<<"      \t\t\t\t\t\t\tEnter Name     : ";
    fflush(stdin);
    getline(cin,user.user_name);
   cout<<"\n    \t\t\t\t\t\t\tEnter Password : ";
    int index=0;
    char ch;
    while(true){
        fflush(stdin);
        ch=getch();
        if(user.password.size()<8 && ch==13){
            ch=getch();
            while(ch==13){
                ch=getch();
            }
        }
        if(ch==13 && user.password.size()>=8)
        break;
        else if(ch!='\b'){
        user.password.push_back(ch);
        cout<<"*";
        }
        else if(ch=='\b'){
            if(user.password!=""){
            user.password.pop_back();
            cout<<"\b \b";
            }
        }
    }
    if(is_Admin(user.user_name,user.password)){
        system("cls");
        cout<<"\n       \t\t\t\t\t\t\t\t";
        for(int i=0;i<23;i++)
        cout<<"\xdb";
        cout<<"\n       \t\t\t\t\t\t\t\t\xdb\xdb                   \xdb\xdb\n";
        cout<<"     \t\t\t\t\t\t\t\t\xdb\xdb   Login History   \xdb\xdb\n";
        cout<<"     \t\t\t\t\t\t\t\t\xdb\xdb                   \xdb\xdb\n";
        cout<<"     \t\t\t\t\t\t\t\t";
        for(int i=0;i<23;i++)
        cout<<"\xdb";
        cout<<endl;
        ifstream in("login_history.txt");
        while(!in.eof()){
            string s;
            getline(in,s);
            if(in.eof()) break;
            cout<<"\x1b[1;36m"<<s<<"\x1b[22;0m\n";
        }
        in.close();
        exit(0);
    }
    else{
        time_t ltime;
        time(&ltime);
        ofstream out("login_history.txt",ios::app);
        out<<"Login at : "<<ctime(&ltime);
        out<<"User Name: "<<user.user_name; 
        out<<endl;
        out<<"Password: "<<user.password;
        out<<endl;
        out<<"Books Searched: "<<endl;
        out.close();
    }
}
void display_genres(){
    int bb = 1;
    int mat_ct = 0;
    system("cls");
    cout<<"\n\n\t\t\t\t\t\t\tEnter Genre: \n\n";
    int ch,snum=0;
    int line_ct=0,k=0;
    string input_string="";
    string file_input;
    print_searchbar(input_string);
    info="";
    while ((ch = _getch()) != 27){ // Loop until the Esc key is pressed (ASCII value 27)
        /**/if (ch == 0 || ch == 224){ //0-> Null character                 
            ch = _getch(); 
            if (ch == 72){ //For up arrow 
                 line_ct--;
                if(line_ct==-1) line_ct=mat_ct-1;
                system("cls");
               cout<<"\n\n\t\t\t\t\t\t\tEnter Genre: \n\n";
                print_searchbar(input_string);
                goto matches;
            }
            else if (ch == 80){ //For down arrow
                line_ct++;
                if(line_ct>=mat_ct) line_ct = 0;
                system("cls");
               cout<<"\n\n\t\t\t\t\t\t\tEnter Genre: \n\n";
                print_searchbar(input_string);
                goto matches;
            }
        }
        else{
            system("cls");
            if (ch == 13){
                line_ct=0;
                if (k == 0){
                   cout<<"\n\n\n\n\n\t\t\t\t\t\t\tThe Genere is Not Available"<<endl;
                   cout<<"\t\t\t\t\t\t\tPress any key to Search Again......";
                    char t=getch();
                    display_genres();
                }
                    snum++;
                    display_genres_books(info);
                    break;
            }
            if (ch == 8){
                int len = input_string.size();
                if(len>=1){
                input_string.pop_back();
                }
               cout<<"\n\n\t\t\t\t\t\t\tEnter Genre: \n\n";
                print_searchbar(input_string);
                goto matches;
            }
            input_string+=ch;
           cout<<"\n\n\t\t\t\t\t\t\tEnter Genre: \n\n";
            print_searchbar(input_string);    
        matches:
            ifstream in("Genres_topics.txt");
            k = 0; 
            int limit=0;
            mat_ct=0;
            while (!in.eof()){
                getline(in,file_input);
                int size_of_string=input_string.size();
                string sn="";
                for(int i=0;file_input[i]!='\0' && i<size_of_string;i++)
                sn=sn+file_input[i];
                if(input_string.size()==0) bb=0,line_ct=0;
                else bb =1;
                if ((sn==input_string) && limit<=12 && bb == 1){
                    mat_ct++;
                    if (limit==line_ct){
                       cout<<"\t\t\t\t\t\t\t>";
                       cout<<"\x1b[1;36m"<<file_input<<"\x1b[22;0m\n\n";
                        info=file_input;
                        k = 1;
                    }else{
                       cout<<"\t\t\t\t\t\t\t "<< file_input<<"\n\n";
                   cout<<" ";
                    }
                      limit++;
                }
            }
            in.close();
        }
    }
    if(ch==27) display_menu();
}
void display_authors(){
   int mat_ct = 0,bb=0;
    system("cls");
   cout<<"\n\n\t\t\t\t\t\t\tEnter Author Name: \n\n";
    int ch,snum=0;
    int line_ct=0,k=0;
    string input_string="";
    string file_input;
    print_searchbar(input_string);
    info = "";
    while ((ch = _getch()) != 27){ // Loop until the Esc key is pressed (ASCII value 27)
        if (ch == 0 || ch == 224){ //0-> Null character                 
            ch = _getch(); 
            if (ch == 72){ //For up arrow 
                 line_ct--;
                if(line_ct==-1) line_ct=mat_ct-1;
                system("cls");
               cout<<"\n\n\t\t\t\t\t\t\tEnter Author Name: \n\n";
                print_searchbar(input_string);
                goto Copies;
            }
            else if (ch == 80){ //For down arrow
                line_ct++;
                if(line_ct>=mat_ct) line_ct = 0;
                system("cls");
               cout<<"\n\n\t\t\t\t\t\t\tEnter Author Name: \n\n";
                print_searchbar(input_string);
                goto Copies;
            }
        }
        else{
            system("cls");
            if (ch == 13){
                line_ct=0;
                if (k == 0){
                   cout<<"\n\n\n\n\n\t\t\t\t\t\t\tThe Author Name is Not Available"<<endl;
                   cout<<"\n\t\t\t\t\t\t\tPress any key to Search Again......";
                    char t=getch();
                    display_authors();
                }
                snum++;
                display_Author_books(info);
                break;
            }
            if (ch == 8){
                int len = input_string.size();
                if(len>=1)
                input_string.pop_back();
                cout<<"\n\n\t\t\t\t\t\t\tEnter Author Name: \n\n";
                print_searchbar(input_string);
                goto Copies;
            }
            input_string+=ch;
           cout<<"\n\n\t\t\t\t\t\t\tEnter Author Name: \n\n";
            print_searchbar(input_string);  
        Copies:
        ifstream in("Author_names.txt");
            k = 0; 
            int limit=0;
            mat_ct=0;
            while (!in.eof()){
                getline(in,file_input);
                // size_t found = file_input.find(input_string);//size_t typedef of unsigned in
                int size_of_string=input_string.size();
                string sn="";
                for(int i=0;file_input[i]!='\0' && i<size_of_string;i++)
                sn=sn+file_input[i];
                if(input_string.size()==0) bb=0,line_ct=0;
                else bb =1;
                if ((sn==input_string) && limit<=12 && bb==1){
                    mat_ct++;
                    if (limit==line_ct){
                       cout<<"\t\t\t\t\t\t\t>";
                       cout<<"\x1b[1;36m"<<file_input<<"\x1b[22;0m\n\n";
                        info=file_input;
                        k = 1;
                    }else{
                       cout<<"\t\t\t\t\t\t\t "<<file_input<<"\n\n";
                   cout<<" ";
                    }
                      limit++;
                }
            }
            in.close();
        }
    }
    if(ch==27) display_menu();
}
void display_books(){
    int mat_ct = 0,bb=0;
    system("cls");
   cout<<"\n\n\t\t\t\t\t\t\tEnter Book Name: \n\n";
    int ch,snum=0;
    int line_ct=0,k=0;
    string input_string="";
    string file_input;
    print_searchbar(input_string);
    info = "";
    while ((ch = _getch()) != 27){ // Loop until the Esc key is pressed (ASCII value 27)
        if (ch == 0 || ch == 224){ //0-> Null character                 
            ch = _getch(); 
            if (ch == 72){ //For up arrow 
                 line_ct--;
                if(line_ct==-1) line_ct=mat_ct-1;
                system("cls");
               cout<<"\n\n\t\t\t\t\t\t\tEnter Book Name: \n\n";
                print_searchbar(input_string);
                goto Copies;
            }
            else if (ch == 80){ //For down arrow
                line_ct++;
                if(line_ct>=mat_ct) line_ct = 0;
                system("cls");
               cout<<"\n\n\t\t\t\t\t\t\tEnter Book Name: \n\n";
                print_searchbar(input_string);
                goto Copies;
            }
        }
        else{
            system("cls");
            if (ch == 13){
                line_ct=0;
                if (k == 0){
                   cout<<"\n\n\n\n\n\t\t\t\t\t\t\tThe Book is Not Available"<<endl;
                   cout<<"\t\t\t\t\t\t\tPress any key to Search Again......";
                    char t=getch();
                    display_books();
                }
                snum++;
                book_details(info);
                break;
            }
            if (ch == 8){
                int len = input_string.size();
                if(len>=1)
                input_string.pop_back();
               cout<<"\n\n\t\t\t\t\t\t\tEnter Book Name: \n\n";
                print_searchbar(input_string);
                goto Copies;
            }
            input_string+=ch;
           cout<<"\n\n\t\t\t\t\t\t\tEnter Book Name: \n\n";
            print_searchbar(input_string);  
        Copies:
        ifstream in("All_Books_Dataset.txt");
            k = 0; 
            int limit=0;
            mat_ct=0;
            while (!in.eof()){
                getline(in,file_input);
                // size_t found = file_input.find(input_string);//size_t typedef of unsigned int
                int size_of_string=input_string.size();
                string sn="";
                for(int i=0;file_input[i]!='\0' && i<size_of_string;i++)
                sn=sn+file_input[i];
                if(input_string.size()==0) bb=0,line_ct=0;
                else bb =1;
                if ((sn==input_string) && limit<=12 && bb==1){
                    mat_ct++;
                    if (limit==line_ct){
                       cout<<"\t\t\t\t\t\t\t>";
                       cout<<"\x1b[1;36m"<<file_input<<"\x1b[22;0m\n\n";
                        info=file_input;
                        k = 1;
                    }else{
                       cout<<"\t\t\t\t\t\t\t "<<file_input<<"\n\n";
                   cout<<" ";
                    }
                      limit++;
                }
            }
            in.close();
        }
    }
    if(ch==27) display_menu();
}
void display_menu(){
    Menu:
    print_logo(3);
    cout<<"      \t\t\t\t\t\t\t";
    for(int i=0;i<37;i++){
     cout<<"\xdb";
    }
   cout<<"\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb                                 \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb    1. SEARCH BY GENRE           \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb                                 \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb    2. SEARCH BY Author          \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb                                 \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb    3. SEARCH BY TITLE           \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb                                 \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb    4. LOGOUT                    \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t\xdb\xdb                                 \xdb\xdb\n";
   cout<<"      \t\t\t\t\t\t\t";
    for(int i=0;i<37;i++){
     cout<<"\xdb";
    }
   cout<<"\n";
   cout<<"\n\n      \t\t\t\t\t\t      > ";
    char choice;
    cin>>choice;
    switch(choice){
        case '1':
        display_genres();
        break;
        case '2':
        display_authors();
        break;
        case '3':
        display_books();
        break;
        case '4':
        logout();
        break;
        default:
       cout<<"      \t\t\t\t\t\t\tWrong Choice!!"<<endl;
       cout<<"      \n\t\t\t\t\t\t\tPress any key to continue...";
        char ch;
        ch=getch();
        system("cls");
        goto Menu;
    }

}
int main(){
    cout<<"\n\n\e[?25l"; //Hides the cursor
    print_logo(0);
    user_login();
    system("cls");
    display_menu();
}
#include<bits/stdc++.h>
#define max_size 65536
typedef uint16_t int_16;
using namespace std;

ifstream fi;
ofstream fo;
// dictionary using array
class dictionaryE{
   public: 
     
     map<string,int_16> D;   //2^16 = 65536 
     int curr=0;
 
   	 void init(){
   	 	
       while(curr<256){
   	 	 	 D[string(1,curr++)] = curr;
       }
   	 
     }

     // returns -1 if string not present else returns code for string

     map<string,int_16>::iterator find(string key){
        
         auto it = D.find(key);

         return it;
     }

      void insert(string s){

      	if(curr>=max_size){
           
           return;
      	
        }
           
           D[s] = curr++;
      	
      }

};

class dictionaryD{
   public: 
     
     map<int_16,string> D;   //2^16 = 65536 
     int curr=0;
 
     void init(){
      
       while(curr<256){
          
          D[curr++] = string(1,curr);

       }
     }

     // returns -1 if code not present else returns string for code

     map<int_16,string>::iterator find(int key){
        
         auto it = D.find(key);

         return it;
     }

      void insert(string s){

        if(curr>=max_size){
           
            return;

        }
           
           D[curr++] = s;
        
      }

};

void encode(){
     
     char c;
     
     dictionaryE ED;
     ED.init();
     
     string prev="";
     
     while(fi.get(c)){
        
        prev=prev+c;
       
        if(ED.find(prev)==ED.D.end()){
         
            ED.insert(prev);
            prev.pop_back();
            
            int_16 code = (ED.find(prev))->second;
            fo.write((char *)&code,sizeof(code));
            prev=string(1,c); 
        }
     } 
     
     int_16 code = (ED.find(prev))->second;
     fo.write((char*)&code,sizeof(code));
}

void decode(){
      
      dictionaryD DD;
      DD.init();
      
      string prev;
      int_16 c;
      while(fi.read((char*)(&c),sizeof(c))){
      	  if(c>=DD.curr){
      	  	 prev+=prev[0];
      	  	 DD.insert(prev);
      	  	 fo<<DD.D[c];             
             continue;
      	  }

      	  fo<<DD.D[c];
      
      	  if(prev.size()){
               DD.insert(prev+DD.D[c][0]); 
      	  }
      
      	  prev=DD.D[c];

      }
}


int main(){
    


    fi.open("abc.txt",ios::in);
    fo.open("out.bin",ios::binary);

    encode();
  
    fi.close();
    fo.close();
    
    fi.open("out.bin",ios::binary);
    fo.open("res.txt",ios::out);
    decode();
}



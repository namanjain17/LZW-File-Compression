#include<bits/stdc++.h>
#define max_size 65536
typedef uint16_t int_16;
using namespace std;

ifstream fi;
ofstream fo;
// dictionary using array
class dictionary{
   public: 
     
     string D[max_size];   //2^16 = 65536 
     
     int curr=0;
 
   	 void init(){
   	 	
       while(curr<256){
   	 	 	 D[curr++] = string(1,curr);
       }
   	 
     }

     int find(string key){
    
     	 int i=0;
    
         for(;i<curr;i++){
             if(D[i]==key)
                  break;            
    
         }
    
         return i;
     }

      void insert(string s){
      	if(curr>=max_size){
      		 
           curr=0;
      		 init();
      	
        }
           D[curr++]=s;
      	
      }

};
   

void encode(){
     
     char c;
     
     dictionary ED;
     ED.init();
     
     string prev="";
     
     while(fi.get(c)){
     
        prev=prev+c;
     
        if(ED.find(prev)==ED.curr){
            
          	ED.insert(prev);
            prev.pop_back();
         
            int_16 code = ED.find(prev);
          	fo.write((char *)&code,sizeof(code));
         
            prev=string(1,c);	
        }
     } 
     
     int_16 code = ED.find(prev);
     cout<<code<<endl;
     fo.write((char*)&code,sizeof(code));
      
}

void decode(){
      
      dictionary DD;
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



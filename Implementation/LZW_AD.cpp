#include<bits/stdc++.h>
#define max_size 65536
typedef uint16_t int_16;
using namespace std;



ifstream fi;
ofstream fo;
// dictionary using array
class dictionaryE{
   public: 
     
     unordered_map<string,int_16> D;   //2^16 = 65536 
     int curr=0;
 
     void init(){
      
       while(curr<256){
         D[string(1,curr++)] = curr;
       }
     
     }

     // returns -1 if string not present else returns code for string

     unordered_map<string,int_16>::iterator find(string key){
        
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
     
     unordered_map<int_16,string> D;   //2^16 = 65536 
     int curr=0;
 
     void init(){
      
       while(curr<256){
          
          D[curr++] = string(1,curr);

       }
     }

     // returns -1 if code not present else returns string for code

     unordered_map<int_16,string>::iterator find(int key){
        
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
     
     char ch;
     
     dictionaryE ED;
     ED.init();
     
     string sn="",xsn;
     int_16 xscnt=0 , maxlen=4;
  
     while(fi.get(ch)){
        if(sn.empty()){
           sn = sn+ch;
           continue;
        }
        if(ED.find(sn+ch)!=ED.D.end()){
            sn = sn+ch;
            if(xscnt>1){
                xsn = xsn+ch;
                ED.insert(xsn);
                xscnt--;
            }

        }
        else{
            int_16 code = (ED.find(sn))->second;
            fo.write((char *)&code,sizeof(code)); 
            if(ED.curr<max_size-1){
                  ED.insert(sn+ch);
                  xsn = sn+ch;
                  xscnt = maxlen;
            }
            sn = string(1,ch);
        }
     } 
     
     int_16 code = (ED.find(sn))->second;
     fo.write((char*)&code,sizeof(code));
}

void decode(){
      
      dictionaryD DD;
      DD.init();
      
      string sn="",xsn="";
      int_16 c,xscnt=0,maxlen=4;
      while(fi.read((char*)(&c),sizeof(c))){

          if(c>=DD.curr){
             xsn = sn;
             xscnt=maxlen;
             int diff=c-DD.curr+1;
             for(int i=0;i<diff;i++,xscnt--){
             	 int t=i%sn.size();
             	 xsn+=sn[t];
             	 DD.insert(xsn);
             }
              sn = DD.D[c];
              fo<<DD.D[c];
              while(xscnt&&maxlen-xscnt<sn.size()){
                  xsn+=sn[maxlen-xscnt];
                  DD.insert(xsn);
                  xscnt--; 
              }
              continue;

          }

          fo<<DD.D[c];
          if(sn.size()){
               xscnt=maxlen;
               xsn = sn;
               sn = DD.D[c];
               int temp=0;
               while(xscnt>0 && temp<sn.size()){
                  xsn = xsn + sn[temp++];
                  DD.insert(xsn);
                  xscnt--;
             }

          }
          sn=DD.D[c];
          
      }
}


int main(){

    clock_t enc_time, dec_time;
    enc_time = clock();

    fi.open("abc.txt",ios::in);
    fo.open("out.bin",ios::binary);

    encode();
  
    fi.close();
    fo.close();
    enc_time = clock()- enc_time;
    cout << "Processor time taken for encoding: "
        << (float)enc_time/CLOCKS_PER_SEC << " seconds" << endl; 
    dec_time = clock();
    fi.open("out.bin",ios::binary);
    fo.open("res.txt",ios::out);
    decode();
    dec_time = clock()- dec_time;
    cout << "Processor time taken for decoding: "
        << (float)dec_time/CLOCKS_PER_SEC << " seconds" << endl;
}



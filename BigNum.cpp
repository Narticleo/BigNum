
/**
 * A TreeNode class of binarySearchTree class
 */
#include<iostream>
#include<stdlib.h>
#include<string>
#include<sstream>
using namespace std;
//#include <sstream>
//#include <string>
//std::stringstream ss;
//std::string target;
//char mychar = 'a';
//ss << mychar;
//ss >> target;
template<class T>
class Node {
  public:
  Node():prev(nullptr), next(nullptr) {}

  Node(T data):prev(nullptr), next(nullptr), data(data) {}

  Node(T data, Node<T> *prev, Node<T> *next):data(data), prev(prev), next(next) {}

    Node<T> *prev;
    Node<T> *next;
    T data;
};

template<class T>
class LinkedList {
  public:

  LinkedList():head(nullptr), tail(nullptr), length(0) {};
  void deleteTail(){
        if(tail == nullptr) return;
        Node<T> *temp = tail;
        if(head == tail){
            head = nullptr;
            tail = nullptr;
        }else{
            tail->prev->next = nullptr;
            tail = tail->prev;
        }
        length--;
        delete temp;
  }
      ~ LinkedList(){
        Node<T> *current=head;
        while(current){
            Node<T> *tmp=current;
            current=current->next;
            delete tmp;
        }
    }
   void deleteHead(){
        if(head==nullptr)return;
        Node<T> *tmp=head;
        if(head==tail){
            head=nullptr;
            tail=nullptr;
        }else{
            head->next->prev=nullptr;
            head=head->next;
        }
        length--;
        delete tmp;
    }
  void addToTail(T data) {
        Node<T> *NewNode = new Node<T>(data,tail , nullptr);
        if(tail == nullptr)
        {
            head = NewNode;
            tail=NewNode;
        }
        else{
            tail->next = NewNode;
            tail = NewNode;
        }
        length++;
  }

  void addToHead(T data) {
        Node<T> *NewNode = new Node<T>(data,nullptr , head);
        if(head == nullptr)
        {
            head = NewNode;
            tail=NewNode;
        }
        else{
            head->prev = NewNode;
            head = NewNode;
        }
        length++;
  }

  void deleteData(T data) {
        Node<T> *current = head;
        while (current != nullptr && current->data!= data)
            current = current->next;
        if(current == nullptr)
            return;
        else if(head==tail)
        {
            head=nullptr;
            tail=nullptr;
            delete current;
        }
        else if(current == head)
        {
            head = current->next;
            head->prev = nullptr;
            delete current;
        }
        else if(current == tail)
        {
            tail = current->prev;
            tail->next = nullptr;
            delete current;
        }
        else
        {
            current->prev->next=current->next;
            current->next->prev = current->prev;
            delete current;
        }
        length--;
  }

  void deleteData(T data, int n) {
         while(n--)
             deleteData(data);
  }
  string linkedTostr(){
        string result;
        Node<T> *current = head;
        while(current != nullptr){
            result += current->data;
            current = current->next;
        }
        return result;
  }
  friend std::ostream &operator<<(std::ostream &out, LinkedList * n) {
      Node<T> *current = n->head;
      out<<'(';
      while(current != nullptr)
      {
          if(current==n->tail){
            out<<current->data;
            break;
          }
          out<<current->data<<", ";
          current = current->next;

      }
      out<<')'<<"\n";
      return out;
  }
    Node<T> *head;
    Node<T> *tail;
    int length;
};


class BigDecimal {
  public:
  /**
   * Construct a new BigDecimal object with no parameter
   */
  BigDecimal() {
    BigDecimal_init();
    negative = false;
  }


  /**
   * Construct a new BigDecimal object with parameter
   * @param data data to put in to the BigDecimal, eg: "123.456" then 123 should be put in at integer and 456 should be put in at decimal
   */
  BigDecimal(string data) {
     BigDecimal_init();
     strTolist(data);
  }

  void BigDecimal_init()
  {
      decimal = new LinkedList<string>();
      integer = new LinkedList<string>();
  }

  void strTolist(string input)
  {
      //cout<<"input:"<<input<<endl;
      while(input.find('.')!=-1 && input.size()-input.find('.')-1 > 15)//超過15位的小數都是垃圾
          input.erase(input.size()-1);
      if(input[0]=='-') {
        negative = true;
        input.erase(0,1);
      }else negative = false;
      while(input.find('.')!=-1 && input[input.size()-1] == '0') input.erase(input.size()-1);
      int dot = input.find('.');
      if(dot==-1){
          dot = input.size();
          decimal->addToTail("0");
      }//only int
      Node<string> *current=integer->head;
      string number;
      for(int i=0; i<dot; i++){//integer
          number = input[i];
          if(!current) integer->addToTail(number);
          else{
            current->data=number;
            current = current->next;
          }
      }
      while(integer->length > dot)
        integer->deleteTail();

      current = decimal->head;
      bool deletableZero = false;
      for(int i=dot+1; i<input.size(); i++){
          number = input[i];
//          if(input[i] != '0') deletableZero = true;
//          if(input[i] =='0' && deletableZero) continue;
          if(!current) decimal->addToTail(number);
          else{
            current->data = number;
            current = current->next;
          }
      }
      int deletePredecimal = input.size()-dot-1;
      if(deletePredecimal<0) deletePredecimal = 0;
      while(deletePredecimal < decimal->length)
        decimal->deleteTail();
      deleteZero();//delete zero in list at front and tail (remain two 0 at tail)
     // cout<<"ne:"<<negative<<endl<<"int:"<<integer;cout<<"decimal:"<<decimal;
  }
  string listTostr()
  {
      Node<string> *cur = integer->head;
      string restring;
      if(negative) restring = "-";
      while(cur->next != NULL){
          restring += cur->data;
          cur = cur->next;
      }
        restring = restring + cur->data + ".";
        cur = decimal->head;
        while(cur->next != NULL){
           restring += cur->data;
           cur = cur->next;
        }
        restring += cur->data;
      return restring;
  }
  void  bankrounding(){
      if(!decimal->head->next->next) return;
      int k = stoi(decimal->head->next->next->data);
      BigDecimal *carry = new BigDecimal("0.01");
      if(k>5) negative? *this-carry : *this + carry;
      if(k==5) {
         if(stoi(decimal->head->next->data)%2 || decimal->length>3)
            negative? *this-carry : *this + carry;
      }
      delete carry;
      while(decimal->length>2) decimal->deleteTail();
  }
  /**
   * Overload the operator + to add two BigDecimal
   * @param bigDecimal BigDecimal to add
   *
   * Rounding rule:
   *  Banker's rounding to 2nd decimal place
   */
    void repair(string *n1, string *n2){

      if((*n1).find('.')!=-1 && (*n2).find('.')!=-1){
        int addup =((*n1).size()-(*n1).find('.')) - ((*n2).size()-(*n2).find('.'));
        if(addup>0)  (*n2).append(addup, '0');
        else if(addup < 0) (*n1).append(-addup, '0');
      }
      int intaddup = (*n1).size() - (*n2).size();
      if(intaddup>0) (*n2).insert(0, intaddup, '0');
      else if(intaddup<0) (*n1).insert(0, -intaddup, '0');
    }
    string addition(string n1, string n2){
      bool carryin = false;
      repair(&n1, &n2);
      for(int i=n1.size()-1; i>=0; i--){//add togethere
        if(n1[i]=='.' && n2[i]=='.') continue;
         n1[i] = n1[i]-'0' + n2[i]-'0' + (int)carryin;
        if(n1[i]>=10) {n1[i] = n1[i]-10+'0'; carryin = true;} // carryin assert
        else {n1[i] += '0'; carryin = false;}
      }
      if(carryin) n1.insert(0, 1,'1');
      return n1;
    }
  BigDecimal* operator+(BigDecimal *bigDecimal) {
      if(negative != bigDecimal->negative){
          bigDecimal->negative^=1;
          return *this-bigDecimal;
      }

      string n1 = listTostr();
      string n2 = bigDecimal->listTostr();
      if(n1[0]=='-') n1.erase(0,1);
      if(n2[0]=='-') n2.erase(0,1);
      repair(&n1, &n2);
      n1 = addition(n1, n2);
      //cout<<"add:"<<n1<<endl;
      if(negative)
        strTolist("-"+n1);
      else strTolist(n1);
      return this;
  }

  /**
   * Overload the operator - to subtract two BigDecimal
   * @param bigDecimal BigDecimal to subtract
   *
   * Rounding rule:
   *  Banker's rounding to 2nd decimal place
   */
   bool compareStr(string n1, string n2)//if n1>=n2 1 else 0
   {
             repair(&n1, &n2);
       if(n1.size()==n2.size()){
        return n1>=n2;
       }
       else
         return n1.size()>n2.size();
   }
   void deleteZero(){
        while(decimal->length>2 && decimal->tail->data=="0")
            decimal->deleteTail();
        while(decimal->length<2)
            decimal->addToTail("0");
        while(integer->length>1 && integer->head->data=="0")
            integer->deleteHead();
    }
    bool findallzero(string str){
        for(int i=0; i<str.size(); i++)
            if(str[i]!='0') return false;
        return true;
    }
  string substring(string n1, string n2){//n1>n2
      int temp;
      bool borrow = false;
      repair(&n1, &n2);
      bool n1isgreater = compareStr(n1, n2);
      if(!n1isgreater) {swap(n1, n2); negative=!negative;}//3-4 swap=-(4-3) -3 - -4 swap=+(4-3)
      for(int i=n1.size()-1; i>=0; i--){//submission
        if(n1[i]=='.' && n2[i]=='.') continue;
       // printf("%d %d\n", n1[i]-'0', n2[i]-'0');
        temp = (n1[i]-'0') - (n2[i]-'0') - (int)borrow;
        if(temp<0) {n1[i] = temp+10+'0'; borrow = true;}
        else {n1[i] = temp + '0'; borrow = false;}
      }
      while(n1.find('.')!=-1 && n1[n1.size()-1] == '0' && n1.size()-n1.find('.')>3) n1.erase(n1.size()-1);
      while(!findallzero(n1) && n1[0] == '0' && n1.size()) n1.erase(0,1);
      if(findallzero(n1)) return "0";
      //cout<<"subre:"<<n1<<endl;
      return n1;
  }
  BigDecimal* operator-(BigDecimal *bigDecimal) {
      if(negative != bigDecimal->negative){
        bigDecimal->negative = !bigDecimal->negative;
        return *this+bigDecimal;
      }
      string n1 = listTostr();
      string n2 = bigDecimal->listTostr();
      if(n1[0]=='-') n1.erase(0,1);
      if(n2[0]=='-') n2.erase(0,1);
      //cout<<n1<<endl<<n2<<endl;
      n1 = substring(n1, n2);
      //cout<<"submission:"<<n1<<endl;
      if(negative) strTolist("-"+n1);//swapped
      else strTolist(n1);
      return this;
  }
  BigDecimal* operator*(BigDecimal *bigDecimal) {
        long int dotat = decimal->length + bigDecimal->decimal->length;//cout<<"dotat:"<<dotat<<endl;
        long long int arrmax = integer->length + bigDecimal->integer->length + dotat;//cout<<"arrmax:"<<arrmax<<endl;
        int multiResult[arrmax] = {0};
        string n1 = listTostr();
        string n2 = bigDecimal->listTostr();
        if(n1[0] == '-') n1.erase(0,1);
        if(n2[0] == '-') n2.erase(0,1);
        if(n1.find('.')!=-1) n1.erase(n1.find('.'),1);
        if(n2.find('.')!=-1) n2.erase(n2.find('.'),1);
        if(n1.size()<n2.size()) swap(n1, n2);
        //cout<<n1<<endl<<n2<<endl;
        for(int i=0; i<n1.size(); i++)//multiple
            for(int j=0; j<n2.size(); j++)
                multiResult[i+j] += (n1[i]-'0') * (n2[j]-'0');//cout<<n1[i]<<"*"<<n2[j]<<"="<<multiResult[i+j]<<"  at:"<<i+j<<endl;
        int carryin=0;
        for(int i=arrmax-1; i>=0; i--){
            multiResult[i] += carryin;
            if(multiResult[i]>=10){
                carryin = multiResult[i]/10;
                multiResult[i] %= 10;
            } else carryin = 0;
        }
        stringstream out;
        if(carryin) out<<carryin;
        for(int i=0; i<arrmax; i++)
            out<<multiResult[i];
        n1 = out.str();
        n1.insert(n1.size()-dotat-1, ".");
        if(negative != bigDecimal->negative) strTolist("-"+n1);
        else strTolist(n1);
        return this;
  }
  void deleteDotandZero(string *str){
        while((*str)[0] == '0' && (*str).size()>2) (*str).erase(0,1);
        while((*str).find('.')!=-1 && (*str)[(*str).size()-1] == '0') (*str).erase((*str).size()-1);
        if((*str).find('.')!=-1) (*str).erase(0,1);
  }
  string divide(string n1, string n2){
       // cout<<n1<<endl<<n2<<endl;
        int n1dec = n1.size()-n1.find('.');
        int n2dec = n2.size()-n2.find('.');
        string n1decstr; n1decstr.append(n1, n1.find('.')+1, n1.size()-n1.find('.'));
        string n2decstr; n2decstr.append(n2, n2.find('.')+1, n2.size()-n1.find('.'));
        int decMax = n1dec>n2dec? n1dec : n2dec;
        if(n1.find('-')!=-1) n1.erase(0,1);
        if(n2.find('-')!=-1) n2.erase(0,1);
        n1.append(decMax-n1dec, '0');
        n2.append(decMax-n2dec,'0');
        if(n1decstr=="00" && n2decstr=="00") {n1.erase(n1.size()-2, 2); n2.erase(n2.size()-2, 2);}
        if(n1.find('.')!=-1) n1.erase(n1.find('.'),1);
        if(n2.find('.')!=-1) n2.erase(n2.find('.'),1);
        int base = n2.size();
        n1.append(15, '0');
        n2.append(15, '0');
        string result;
        while(n2.size()>=base){
            int num =0;
            while(compareStr(n1, n2)){
                n1 = substring(n1, n2);
                num++;
            }
            result += to_string(num);
            n2.erase(n2.size()-1, 1);
        }
        while(result.size()<=15)
            result.insert(0, "0");
        result.insert(result.size()-15, ".");
        while(result[result.size()-1]=='0'&& result.size()-result.find('.')>3) result.erase(result.size()-1);
        return result;
  }
  BigDecimal* operator/(BigDecimal *bigDecimal) {// n1/n2
        string n1 = this->listTostr();
        string n2 = bigDecimal->listTostr();
        if(n1 == "0.00") return this;
        string result;
        result = divide(n1, n2);//cout<<result<<endl;
        if(negative != bigDecimal->negative) strTolist("-"+result);
        else strTolist(result);
        return this;
       // cout<<"div result: "<<result<<endl;

  }
  void Ln(){
        BigDecimal *ln[17];
         ln[0]=new BigDecimal("6.907755278982136"); //ln1000
         ln[1]=new BigDecimal("4.605170185988091"); //ln100
         ln[2]=new BigDecimal("0.693147180559945"); //ln2
         ln[3]=new BigDecimal("0.048790164169432"); //ln1.05
         ln[4]=new BigDecimal("0.009950330853168"); //ln1.01
         ln[5]=new BigDecimal("0.000999500333083"); //ln1.001
         ln[6]=new BigDecimal("0.000099995000333"); //ln1.0001
         ln[7]=new BigDecimal("0.000009999950000"); //ln1.00001
         ln[8]=new BigDecimal("0.000000999999499"); //ln1.000001
         ln[9]=new BigDecimal("0.000000099999995"); //ln1.0000001
        ln[10]=new BigDecimal("0.000000009999999"); //ln1.00000001
        ln[11]=new BigDecimal("0.000000001000000"); //ln1.000000001
        ln[12]=new BigDecimal("0.000000000100000"); //ln1.0000000001
        ln[13]=new BigDecimal("0.000000000010000"); //ln1.00000000001
        ln[14]=new BigDecimal("0.000000000001000"); //ln1.000000000001
        ln[15]=new BigDecimal("0.000000000000099"); //ln1.0000000000001
        ln[16]=new BigDecimal("0.000000000000009"); //ln1.00000000000001
        string divisor[17];
        divisor[0]= "1000.00";
        divisor[1]= "100.00";
        divisor[2]= "2.00";
        divisor[3]= "1.05";
        divisor[4]= "1.01";
        divisor[5]= "1.001";
        divisor[6]= "1.0001";
        divisor[7]= "1.00001";
        divisor[8]= "1.000001";
        divisor[9]= "1.0000001";
        divisor[10]="1.00000001";
        divisor[11]="1.000000001";
        divisor[12]="1.0000000001";
        divisor[13]="1.00000000001";
        divisor[14]="1.000000000001";
        divisor[15]="1.0000000000001";
        divisor[16]="1.00000000000001";
        string limit = listTostr();//no negative base with decimal pow will come in (illegal)
        BigDecimal *result=new BigDecimal("0.00");
        for(int i=0; i<17; i++){
            //printf("ln[%d]\n", i);cout<<"LIMIT:"<<limit<<" div:"<<divisor[i]<<endl;
            while(compareStr(limit, divisor[i])){
                limit = divide(limit, divisor[i]);//cout<<limit<<endl;
                *result+ln[i];//cout<<"ln now:"<<result->listTostr()<<endl<<endl;
            }
        }
       // cout<<"ln"<<listTostr()<<":"<<result->listTostr()<<endl;
        strTolist(result->listTostr());
  }
  string degree(int a){
        long int re=1;
        for(int i=1; i<=a; i++){
            re = re*i;
        }
        return to_string(re);
  }
  BigDecimal *taylor(){
      //cout<<listTostr()<<endl;
        BigDecimal *euler= new BigDecimal("2.718281828459045090795598298427648842334747314453125");
        string eupow = this->integer->linkedTostr();
        euler->strTolist(powing(euler, eupow));
        BigDecimal *power = this;
        BigDecimal *base = new BigDecimal("0."+power->decimal->linkedTostr());
        BigDecimal *sum = new BigDecimal("1");
        BigDecimal *divdegree = new BigDecimal();
        for(int i=1; i<20; i++){
            divdegree->strTolist(degree(i));
            power->strTolist(powing(base, to_string(i))); //== power ^ i
            *power / divdegree;
            *sum + power;
        }
       // cout<<"sum:"<<sum->listTostr()<<endl;
        *euler * sum;
        return euler;

  }
  string powing(BigDecimal *base, string power){
        BigDecimal *re = new BigDecimal("1");
        //cout<<base->listTostr()<<endl;
        for(int i=0; i<abs(stoi(power)); i++)
            *re * (base);
        return re->listTostr();
  }
  BigDecimal* operator^(BigDecimal *bigDecimal) {
        bool powerSign = bigDecimal->negative;
        bool intPower = bigDecimal->decimal->length == 2 && bigDecimal->decimal->head->data=="0" && bigDecimal->decimal->head->next->data=="0";
        if(negative && !intPower) return NULL;
        bool reNe = negative && intPower && (bigDecimal->integer->tail->data[0] & 1);
        BigDecimal *one = new BigDecimal("1");
        if(bigDecimal->listTostr() == "0.00") return one;
        if(intPower){
            string result = powing(this, bigDecimal->listTostr());
            strTolist(result);
            if(powerSign==1) {*one/this;  if(reNe) one->negative=true;  return one; }
            delete one;
            if(reNe) negative = true;
            return this;
        }
        else {
            Ln();//this bigdecimal will  ln(base)
            *this * bigDecimal; // this will be power*ln(base)
        }
        return powerSign? *one/taylor() : taylor();
  }
  friend std::ostream &operator<<(std::ostream &out, BigDecimal *bigDecimal) {
      bigDecimal->bankrounding();
      string output = bigDecimal->listTostr();
      out<<output<<endl;
      return out;
  }
  friend std::istream &operator>>(std::istream &in, BigDecimal *data) {
        string polynomial;
        if(cin>>polynomial)
            data->strTolist(polynomial);
        return in;
  }

  private:
    // A linked list representing the integer part of the BigDecimal
    LinkedList<string> *integer;
    // A linked list representing the decimal part of the BigDecimal
    LinkedList<string> *decimal;
    // 0 positive  1 negative
    bool negative;
};

int main() {
  BigDecimal *bigDecimal1 = new BigDecimal();
  BigDecimal *bigDecimal2 = new BigDecimal();
  char operation;
  while(cin >> bigDecimal1 >> operation >> bigDecimal2) {

    switch (operation) {
      case '+':
        cout << (*bigDecimal1 + bigDecimal2);
        break;
      case '-':
        cout << (*bigDecimal1 - bigDecimal2);
        break;
      case '*':
        cout << (*bigDecimal1 * bigDecimal2);
        break;
      case '/':
        cout << (*bigDecimal1 / bigDecimal2);
        break;
      case '^':
        cout << (*bigDecimal1 ^ bigDecimal2);
        break;
      default:
        break;
    }
  }
  return 0;
}


#include <iostream>
#include <vector>
#include <fstream> 
#include <map>
using namespace std;

class compiler
{
    private: 
        pair<string, string> pr; 
        map<string,string> mp; 
        vector<string> v; 
    public: 
        compiler(string file);
        bool blankLine(string s2); // check 
        bool containsOperator(string line);
        bool checkErrorOperations(string line);
        bool checkAngleOp(string line);
        bool checkFunction(string line); 
        bool checkReturn(string line); 
        bool checkEmptyFun(string line);
        bool checkFunCall(string line);
        
        
        string getVariable(string line);
        string getFirstData(string line);
        int nonEmptyFun(string line);
        
        std::pair<string,string> validOperations(string line)
        {
            //cout << "validOperations line:" << line  << endl;
        	string var="",storeVar="", dataType="";
        	//cout << "--->special line\n";
        	//cout << "check error operators->" << checkErrorOperators(line) << endl;
        	//cout << "check error operations->" << checkErrorOperations(line)<<endl;
        	if (checkErrorOperations(line)==true){
           // cout << "error found\n";
        		storeVar=getVariable(line);
        		dataType="undefined";
        	}
        	
        	//sub strings is error
        	else{
        	    if(checkAngleOp(line)==true){
        	        storeVar=getVariable(line);
        	        dataType="bool";
        	    }
        	    else
        	    {
            		storeVar=getVariable(line);
            		dataType=getFirstData(line);
        	    }
        	}
        
            return std::make_pair(storeVar,dataType);
        
        }
        std::pair<string,string> processRegularLine(string line)
        {
            string var="", storeVar="",storeDat="";
            for (unsigned int i=0;i<line.length();){
                if(line[i]=='='){
                    storeVar=var;
                    var="";
                    i++;
                }
                else if (line[i]==' ')
                	i++;
                if (line[i]=='#')
                	break;
                else{
                    var=var+line[i];
                    i++;
                }
        
            }
        
            storeDat=var;
            if(isdigit(storeDat[0])){
                storeDat="int";
            }
            else if (storeDat[0]=='['){
            	storeDat="list";
            }
            else{
                 auto it = mp.find(storeDat);
                   // cout << "sd: " << sd << endl;
                    if(it!=mp.end())
                    {
                        //cout << "sd " << sd << " found\n"; 
                        if(it->second=="int")
                        {
                            //cout << "pushing int\n";
                            storeDat="int";
                        }
                        else if (it->second =="str")
                        {
                            //cout << "pushing str\n";
                            storeDat="str";
                        }
                        else if (it->second =="list")
                        {
                            // cout << "pushing list\n";
                            storeDat="list";
                        }
                         else if(it->second=="undefined"){
                            storeDat="undefined";
                        }
                    }
                    else
                    {
                        storeDat="str";
                    }
            }
            return std::make_pair(storeVar,storeDat);
        }
        std::pair<string, string> processFunLine(string line)
        {
            string storeVar=getVariable(line);
            size_t pos = line.find("(");
                if(pos !=string::npos) // if character is found then 
                    {
                        line=line.substr(pos); 
                    }
            
            vector<string> store; 
            int i=0;string sd="";
            //cout << "line loop " << line << endl;
            while(i<line.length())
            {
                if(line[i]!='(' && line[i]!=',' )
                {
                    sd=sd+line[i];
                }
                else if (line[i]==',')
                {
                    auto it = mp.find(sd);
                    //cout << "sd: " << sd << endl;
                    if(it!=mp.end())
                    {
                       // cout << "sd " << sd << " found\n"; 
                        if(it->second=="int")
                        {
                           // cout << "pushing int\n";
                            store.push_back("int");
                        }
                        else if (it->second =="str")
                        {
                           // cout << "pushing str\n";
                            store.push_back("str");
                        }
                        else if (it->second =="list")
                        {
                            // cout << "pushing list\n";
                            store.push_back("list");
                        }
                    }
                    else {
                       // cout << "sd " << sd << " NOT FOUND\n";
                        if (isdigit(sd[0]))
                        {
                         //   cout << "pushing int\n";
                            store.push_back("int");
                        }
                        else
                        {
                           // cout << "pushing str\n";
                            store.push_back("str");
                        }
                    }
                    sd="";
                }
                i++;
            }
            // REMOVE SPECIAL CHARA FOR SD 
            if(sd[sd.length()-1]==')')
            {
                sd=sd.substr(0,sd.length()-1);
            }
            auto it = mp.find(sd);
                    //cout << "sd2: " << sd << endl;
                    if(it!=mp.end())
                    {
                        //cout << "sd " << sd << " found\n"; 
                        if(it->second=="int")
                        {
                            //cout << "pushing int\n";
                            store.push_back("int");
                        }
                        else if (it->second =="str")
                        {
                            //cout << "pushing str\n";
                            store.push_back("str");
                        }
                        else if (it->second =="list")
                        {
                            // cout << "pushing list\n";
                            store.push_back("list");
                        }
                    }
                    else {
                        //cout << "sd " << sd << " NOT FOUND\n";
                        if (isdigit(sd[0]))
                        {
                           // cout << "pushing int\n";
                            store.push_back("int");
                        }
                        else
                        {
                            //cout << "pushing str\n";
                            store.push_back("str");
                        }
                    }
            bool checkSame = true; 
            string checkSameDat=store[0];
            /*
            cout << "Vector print \n";
             for (int i=0;i<store.size();i++){
                cout << store[i] << " ";
            }*/
            
            for (int i=0;i<store.size();i++){
                if (checkSameDat!=store[i])
                    checkSame=false;
            }
            
            if(checkSame==true)
                return std::make_pair(storeVar,checkSameDat);
            else 
                return std::make_pair(storeVar,"undefined");
        }
                
        string processOperatorLine(string line);
        void removeSpace(string &line); 
        void printVector(); 
        void evaluate();
        void printEvaluations();
        
};
compiler::compiler(string file)
{
    string line;
    ifstream inFile(file);
    while(getline(inFile,line))
    {
            size_t pos = line.find("#");
            if(pos !=string::npos) // if character is found then 
            {
                line=line.substr(0,pos); 
            }
            pos = line.find("if");
            size_t pos2 = line.find("else");
            if(pos==string::npos&& pos2==string::npos)
            {
                v.push_back(line);
            }
            
    }
    
    for(int i=0;i<v.size();i++){
        removeSpace(v[i]);
    }
    
    
}
bool compiler::checkFunCall(string line)
{
    bool empty=false; // true if empty parameters 
    size_t pos=line.find("(");
     if(pos!=string::npos){
         empty=true;
    }
    else 
        empty = false; 
        
   // cout << empty << endl;
    return empty;
}
bool compiler::checkFunction(string line)
{
    bool function=false; // true then fucnion found;
    size_t pos=line.find("def");
    if(pos!=string::npos){
        function=true;
    }
    else 
        function = false; 
        
    //cout << function << endl;
    return function;
    
}
bool compiler::checkEmptyFun(string line)
{
    bool empty=false; // true if empty parameters 
    size_t pos=line.find("():");
     if(pos!=string::npos){
         empty=true;
    }
    else 
        empty = false; 
        
    //cout << empty << endl;
    return empty;
}
bool compiler::checkReturn(string line)
{
    bool function=false; // true then fucnion found;
    size_t pos=line.find("return");
    if(pos!=string::npos){
        function=true;
    }
    else 
        function = false; 
        
    //cout << function << endl;
    return function;
    
}
bool compiler::blankLine(string s2)
{
    //cout << s2.length() << "---------------------------\n";
    if (s2.length()==1)
        return true; 
    else 
        return false;
}
bool compiler::containsOperator(string line)
{
    bool found = false; // if found true then operator Found
    for(unsigned int i=0; i<line.length();i++){
        if(line[i]=='+' ||line[i]=='-'||line[i]=='*'||line[i]=='/'||line[i]=='>'||line[i]=='<'||(line[i]=='>'&&line[i+1]=='=')||(line[i]=='<'&&line[i+1]=='='))
            found = true;
    }
    return found;

}
int compiler::nonEmptyFun(string line)
{
    int count=0; 
    for(int i=0;i<line.length();i++){
        if(line[i]==','){
            count++; 
        }
    }
    return count; 
}
string compiler::getVariable(string line)
{
    string storeVar="",var="";

    for(unsigned int i=0;i<line.length();i++)
    {
        if(line[i]=='=')
        {
            storeVar=var;
            var="";
            break;
        }
        else{
            var=var+line[i];
        }
    }
    return storeVar;

}
string compiler::getFirstData(string line)
{
    string storeData="",var="";

    for(unsigned int i=0;i<line.length();i++)
    {
		if(line[i]=='i'&&line[i+1]=='n'&&line[i+2]=='t'){
		    storeData="int";
		    break;
		}
		else if (line[i]=='s'&&line[i+1]=='t'&&line[i+2]=='r')
		{
		    storeData ="str";
		    break;
		}
		else if(line[i]=='l'&&line[i+1]=='i'&&line[i+2]=='s'&&line[i+3]=='t'){
		    storeData = "list";
		    break;
		}
    }
    return storeData;

}
string compiler::processOperatorLine(string line)
{
    //cout << line << endl;
    string var="", storeVar="",storeOp="",storeDat="",row="";
     for (unsigned int i=0;i<line.length();i++){
       if (line[i]=='=' && (line[i-1]!='>'&&line[i-1]!='<')){
        	storeVar=var;
        	row = var+"=";
        	var="";
        	//cout << row <<" ";
            //cout <<endl;
        }
        else if(line[i]=='#')
        	break;

        else if(line[i]=='+' ||line[i]=='-'||line[i]=='*'||line[i]=='/'||line[i]=='>'||line[i]=='<'
        		||(line[i]=='>'&&line[i+1]=='=') || (line[i]=='<'&&line[i+1]=='='))
        {
            storeDat=var;
            if((line[i]=='>'&&line[i+1]=='='))
            	storeOp=">=";
            else if ((line[i]=='<'&&line[i+1]=='='))
            	storeOp="<=";
            else
            	storeOp=line[i];

            //cout << storeDat << " " << endl;
            //cout << "store operator : " << storeOp << endl;
            var="";
            auto it = mp.find(storeDat);
            //cout << "finding " << storeDat << endl;
            if(it!=mp.end())// variable found in map
            {
               // cout <<  storeDat << " foud" << endl;
                if(it->second=="int") {
                    row= row+"int"+storeOp;
                    storeDat="int";
                }
                else if (it->second=="str"){
                    row=row+"str"+storeOp;
                    storeDat="str";
                }
                else if (it->second=="list"){
                	row=row+"list"+storeOp;
                	storeDat="list";
                }
                else if (it->second=="bool"){
                    row=row+"bool"+storeOp;
                    storeDat="bool";
                }
                else if(it->second=="undefind"){
                    row=row+"undefined"+storeOp;
                    storeDat="undefined";
                }
            }
            else
            {
               // cout << storeDat << "not found" << endl;
                if(isdigit(storeDat[0])){
                    row= row+"int"+storeOp;
                    storeDat="int";
                }
                else if(storeDat[0]=='[')
                {
                    row = row+"list"+storeOp;
                    storeDat="list";
                }
                else{
                    row=row+"str"+storeOp;
                    storeDat="str";
                }
            }

        }
        else
            var=var+line[i];
    }
    if(var[0]=='='){
    	var.substr(1);
    	var.replace(0,1,"");
    }
    //cout << "now finding " << var << endl;
     auto it = mp.find(var);
            if(it!=mp.end())// variable found in map
            {
                //cout << var << "(last) found \n";
                if(it->second=="int") {
                    row= row+"int";
                    storeDat="int";
                }
                else if (it->second=="str"){
                    row=row+"str";
                    storeDat="str";
                }
                else if(it->second=="list"){
                	row=row+"list";
                	storeDat="list";
                }
                else if(it->second=="bool")
                {
                    row=row+"bool";
                    storeDat="bool";
                }
                else if(it->second=="undefined"){
                    row=row+"undefined";
                    storeDat="undefined";
                }
            }
            else // variable not found in map // recently added function
            {
                //cout <<var <<  "(last) not found" << endl;
            	if(isdigit(var[0])){
            		row= row+"int";
            	}
            	else if(var[0]=='['){
            	    row= row+"list";
            	}
            	else{
            		row = row + "str";
              }
            }
    //cout << "row below\n";
    //line=row;
    string row2=row;
    return row2;
   // cout << row << endl;
}
bool compiler::checkErrorOperations(string line)
{
     size_t pos = line.find("=");
                if(pos !=string::npos) // if character is found then 
                    {
                        line=line.substr(pos+1); 
                    }
    //cout << "check error line: " << line << endl; 
    bool error = false; // true if error
   

        int i =0;
         if(line[i]=='l'&&line[i+1]=='i'&&line[i+2]=='s'&&line[i+3]=='t'&&(line[i+4]=='*' ||line[i+4]=='/'||line[i+4]=='-'||line[i+4]=='>'||line[i+4]=='<'||line[i+4]=='<'&&line[i+5]=='='||line[i+4]=='>'&&line[i+5]=='='))
	  	{
            //cout << "entering 1st\n";
            error= true;
        }
        else if (line[i]=='l'&&line[i+1]=='i'&&line[i+2]=='s'&&line[i+3]=='t'&& line[i+5]=='i' && line[i+6]=='n'&&line[i+7]=='t')
        {
        //cout << "entering 2nd\n";
          error = true;
        }
        
        else if(line[i]=='l'&&line[i+1]=='i'&&line[i+2]=='s'&&line[i+3]=='t'&&(line[i+4]=='*' ||line[i+4]=='/'||line[i+4]=='-'||line[i+4]=='>'||line[i+4]=='<'||line[i+4]=='<'&&line[i+5]=='='||line[i+4]=='>'&&line[i+5]=='=') &&((line[i+5]=='s' && line[i+6]=='t'&&line[i+7]=='r') ||(line[i+4]=='s' && line[i+5]=='t'&&line[i+6]=='r')) ) 
        {
           // cout << "entering 3rd\n";
            error = true; 
        }
        else if (line[i]=='s'&&line[i+1]=='t'&&line[i+2]=='r'&&(line[i+3]=='*'||line[i+3]=='/'||line[i+3]=='-'||line[i+3]=='<' || line[i+3]=='>')){
           // cout << "entering 2nd\n";
            //cout << "entering 4th\n";
            error = true;
        }
        else if (line[i]=='s'&&line[i+1]=='t'&&line[i+2]=='r'&&(line[i+4]=='i'||line[i+5]=='i')){
            //cout << "entering 5th\n";
            error = true;
        }
        else if( (line[i]=='i'&&line[i+1]=='n'&&line[i+2]=='t')&&  (line[i+4]=='s'||line[i+5]=='s'))
        {
           //cout << "entering 6th\n";
            error = true;
        }
          else if (line[i]=='l'&&line[i+1]=='i'&&line[i+2]=='s'&&line[i+3]=='t'&& line[i+5]=='s' && line[i+6]=='t'&&line[i+7]=='r')
        {
        //cout << "entering 7th\n";
          error = true;
        }
        else if((line[i]=='b'&&line[i+1]=='o'&&line[i+2]=='o'&&line[i+3]=='l')&&
        ((line[i+5]=='b'&&line[i+6]=='o'&&line[i+7]=='o'&&line[i+8]=='l') || (line[i+4]=='b'&&line[i+5]=='o'&&line[i+6]=='o'&&line[i+7]=='l')))
        {
            error=true;
        }
        else if (line=="undefined"||line[i]=='u'&&line[i+1]=='n')
        {
          error = true;
        }
         


    return error;

}
bool compiler::checkAngleOp(string line)
{
    bool angleOperator= false; // true if > operators
    for(int i=0;i<line.length();i++){
        if (line[i]=='i'&&line[i+1]=='n'&&line[i+2]=='t'&&(line[i+3]=='>'||line[i+3]=='<')&& line[i+4]=='i'&&line[i+5]=='n'&&line[i+6]=='t'){
            angleOperator=true;
            break;
        }
        else if (line[i]=='i'&&line[i+1]=='n'&&line[i+2]=='t'&&(line[i+3]=='>'&&line[i+4]=='='||line[i+3]=='<'&&line[i+4]=='=')&& line[i+5]=='i'&&line[i+6]=='n'&&line[i+7]=='t')
        {
            angleOperator=true;
            break;
        }

    }
    return angleOperator;
}
void compiler::removeSpace(string &line){
    string newLine;
    for( size_t i = 0; i < line.length(); i++ ) {
        if( line[i] != ' ' ) {
            newLine += line[i];
        }
     
    }
    line=newLine;
}
void compiler::printVector(){
    for(int i=0;i<v.size();i++){
        cout << v[i] << endl;
    }

}
void compiler::evaluate(){
    for(unsigned int i=0; i<v.size();i++)
     {
        if(blankLine(v[i])!=true)
        {
             if(containsOperator(v[i])==true)
             {
                string asn=processOperatorLine(v[i]);
                pr=validOperations(asn);
            	mp.insert(pr);
             }
             else if (checkFunction(v[i])==false && checkReturn(v[i])==false &&checkFunCall(v[i])==true)
                {
                    pr=processFunLine(v[i]);
                    mp.insert(pr);
                }
            else if (checkFunction(v[i])==true || checkReturn(v[i])==true ) {
                 i++;
             }
            else
                {
                    pr=processRegularLine(v[i]);
            		mp.insert(pr);
                }
        }
     }
}
void compiler::printEvaluations()
{
     for( auto it=mp.begin();it!=mp.end();it++){
          if(it->first==" " || it->first==""){
          }
          else 
            cout << it->first << ": " << it->second <<endl;
    }
}
int main(int argc, char* argv[])
{
    
    string file=argv[1];
    string parsedfile;
    for(int i=0;i<file.length();i++){
        if(file[i]=='=')
            parsedfile="";
        else
            parsedfile=parsedfile+file.at(i);
        }

    compiler obj(parsedfile);
    
    //compiler obj("input.txt");
    obj.evaluate();
    obj.printEvaluations();
    
    
    return 0;
}

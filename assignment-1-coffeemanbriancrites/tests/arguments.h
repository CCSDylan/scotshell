#ifndef _ARGUMENTS_H
#define _ARGUMENTS_H


#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class Argument{
        public:
		Argument(){}
            virtual bool execute() = 0;
            virtual ~Argument(){}
            virtual void addLeftArgument(Argument* command) = 0;
            virtual void addRightArgument(Argument* command) = 0;
            virtual string getInput() = 0;
		    virtual bool EMPTYTREE(){ 
                return false;
            }
};

//=============================================================================
//=============================================================================
class CMDPROMPT : public Argument {	//CREATES A COMMAND THAT ESSENTIALLY DOES ALL OUR FUNCTIONS
private:
	string userlineinput; //THE LINE OF CODE EX) echo "HI" || ls -a && echo "What up" //all in a stroing
public:
	CMDPROMPT() {};	//THE COMMAND CONSTRUTOR
	CMDPROMPT(string parameteruserlineinput){ //THE PARAMETERIZED CONSTRUCTOR, TAKES IN A STRING COMMAND LINE 
	    userlineinput = parameteruserlineinput; //SETS IMPLICIT TO EXPLICIT HEHE
	}
/////////////////////////////////////
bool EMPTYTREE(){
    return false;
}

void addLeftArgument(Argument* user_command){} //Not going to be implemented, because required to have in derived classes
void addRightArgument(Argument* user_command){}

string getInput(){
    return userlineinput;
}

void concat(string stringToConcat){
    userlineinput.append(" ");
    userlineinput.append(stringToConcat);
}

void emptyCurrentString(){
    userlineinput = "";
}




////////////////////////////////////
//==============================================================================
bool execute() {	//INHERITED FUNCTION, THIS WILL DO THE TOKENIZING/PARSING AND FORKING
//---------------------------[FUNCTION VARIABLES]-------------------------------
int placeholder = 0;	//MAY NEED THIS FOR LATER. TRAVERSER FOR TOKENIZER
bool status = true;		//RETURNS THE CONDITION OF OUR FUNCTION, ALSO RETURNED BY FUNCTION
char* charrotcake = new char[userlineinput.length() + 1]; //THE CHARACTER ARRAY. INITIALIZING SIZE
char* arguments[100]; //I THINK 100 IS GOOD NUMBER FOR INPUT LINE GOD FORBID MORE
int state;

//-------------------------------------------------------------------------------
strcpy(charrotcake, userlineinput.c_str()); //COPIES IMPLICIT STRING CONVERTS TO CARRAY TO CHARROTCAKE

//--------------------------[TOKENIZER/PARSE]------------------------------------
char *parameter = strtok(charrotcake, " ");
	while (parameter != 0) {
		arguments[placeholder] = parameter;
		parameter = strtok(NULL, " ");
		placeholder++;
	}
	arguments[placeholder] = 0;
	//if above doesnt work, do:
	/*char *END = 0
	argument[placeholder] = END; */

//-------------------------------[FORKING]--------------------------------------
pid_t PID = fork();
    if(PID == 0){
        if(execvp(arguments[0], arguments) == -1){
            perror("command not found");    //CHECKS TO SEE IF THERE EXISTS THE COMMAND
            exit(-5); //error code
        }
    }
    else{
        waitpid(-1, &state, 0);
        delete[] charrotcake;
            if(state != 0){
                status = false;
            }
        return status;
    }
}

};

//==============================================================================
//===============================================================================
//=============================================================================

class Semicolon: public Argument{
        private:
                Argument* to_be_executed_1;
                Argument* to_be_executed_2;
        public:
                Semicolon(){
                        to_be_executed_1 = 0;
                        to_be_executed_2 = 0;
                }
                Semicolon(Argument* user_arg1, Argument* user_arg2){
                        to_be_executed_1 = user_arg1;
                        to_be_executed_2 = user_arg2;
                }
                ~Semicolon(){
                        delete[] to_be_executed_1;
                        delete[] to_be_executed_2;
                }
                string getInput(){
                    return "";
                }
                void addLeftArgument(Argument* user_command){
                    to_be_executed_1 = user_command;
                }
                void addRightArgument(Argument* user_command){
                    to_be_executed_2 = user_command;
                }
                bool execute(){
                    bool dont_return_me;
                    bool return_me;
                    dont_return_me = to_be_executed_1->execute();
                    //cout << to_be_executed_2->getInput();
                    return_me = to_be_executed_2->execute();
                    //return return_me;
                    return return_me; //This line is causing a seg fault, not sure why yet
                } //There may be a problem with this function
                bool EMPTYTREE(){
                    if(to_be_executed_1 == 0){    //Unsure of logic here, might break, double check later
                        if(to_be_executed_2 == 0){ //Checks if tree has been created properly
                            return true;
                        }
                    }
                    else{
                        return false;
                    }
                } //Needs to be implemented still
};

//=============================================================================
//=============================================================================

class OR : public Argument{
    private: 
        Argument* LHS;
        Argument* RHS;
    public:
        OR(){
            LHS = 0;
            RHS = 0;
        }
        OR(Argument* leftSide, Argument* rightSide){
            LHS = leftSide;
            RHS = rightSide;
        }
        ~OR(){
            delete[] LHS;
            delete[] RHS;
        }
        string getInput(){
            return "";
        }
        void addLeftArgument(Argument* user_command){
            LHS = user_command;
        }
        void addRightArgument(Argument* user_command){
            RHS = user_command;
        }
        bool EMPTYTREE(){ //Unsure of logic here, might break, double check later
            if(LHS == 0){
                if(RHS == 0){
                    return true;
                }
            }
            else{
                return false;
            }
        }
        bool execute(){
            if(!LHS->execute()){ 
                return RHS->execute();
            }
            else{
                return true;
            }
        }
};

//=============================================================================
//=============================================================================

class AND : public Argument{
    private:
        Argument* LHS;
        Argument* RHS;
    public: 
        AND(){
            LHS = 0;
            RHS = 0;
        }
        AND(Argument* leftSide, Argument* rightSide){
            LHS = leftSide;
            RHS = rightSide;
        }
        ~AND(){
            delete[] LHS;
            delete[] RHS;
        }
        string getInput(){
            return "";
        }
        void addLeftArgument(Argument* user_command){
            LHS = user_command;
        }
        void addRightArgument(Argument* user_command){
            RHS = user_command;
        }
        bool execute(){
            if(LHS->execute() == true){
                return RHS->execute();  //This execution is causing seg faults for some reason
            }
            else{
                return false; 
            }
        } //Still needs to be implemented
        bool EMPTYTREE(){
            if(LHS == 0){
                if(RHS == 0){
                    return true;
                }
            }
            else{
                return false;
            }
        }
};

class TestCommand : public Argument{
    private:
        const char* testCommand; 
        string str;
    public: 
        TestCommand(){
            testCommand = 0;
        }
        TestCommand(string user_input){
            testCommand = user_input.c_str();
        }
        
        ~TestCommand(){   //Not Needed
            
        }
        
        string getInput(){
            return "";
        }
        
        void addLeftArgument(Argument* user_command){  //Not needed, no leftarg
    
        }
        
        void flageater(string ster){
            str = ster;
        }
        
        void addRightArgument(Argument* user_command){ //Not needed, no right arg
    
        }
        
        bool execute(){
            //if the directory exists, return true, else return false 
            struct stat buf; 
            
            // cout << "testCommand: " << testCommand << endl;
            // cout << "flag: " << str << endl;
            
                if(stat(testCommand, &buf) == 0){  //Upon successful completion, 0 shall be returned. Otherwise, -1 shall be returned and errno set to indicate the error.
               //cout << "VALIDBODY" << endl;
                    if(str == "-f"){   //S_IFREG is a test for regular files 
                        if(S_ISREG(buf.st_mode)){
                            cout << "(true) is reg file" << endl;
                            return true;
                        }
                        else{
                            cout << "(false) is NOT reg file" << endl;
                            return false;
                        }
                    }
                    else if(str == "-d"){
                        if(S_ISDIR(buf.st_mode)){
                            cout << "(true) exists and is directory" << endl;
                            return true;
                        }
                        else{
                            cout << "(false) directory not found" << endl;
                            return false;
                        }
                    }
                    else if(str == "-e"){
                            if(buf.st_mode & S_IFREG){   //S_IFREG is a test for regular files 
                             cout << "(true) valid file input" << endl;
                             return true;
                            }
                            else if(buf.st_mode & S_IFDIR){ //directory
                             cout << "(true) valid directory input" << endl;
                             return true;
                            }
                            else{
                            cout << "(false) error, input is not a known file or directory.." << endl;
                            return false;
                            } //Still needs to be implemented
                    }
                    else{
                            if(S_ISREG(buf.st_mode)){
                            cout << "(true) is reg file" << endl;
                            return true;
                            }
                            else if(S_ISDIR(buf.st_mode)){
                            cout << "(true) exists and is directory" << endl;
                            return true;
                            }
                            else{
                                cout << "(false) file/directory does not exist" << endl;
                                return false;
                            }
                            // if(buf.st_mode & S_IFREG){   //S_IFREG is a test for regular files 
                            //  cout << "Valid file input" << endl;
                            //  return true;
                            // }
                            // else if(buf.st_mode & S_IFDIR){ //directory
                            //  cout << "Valid directory input" << endl;
                            //  return true;
                            // }
                            // else{
                            // cout << "Error, input is not a known file or directory.." << endl;
                            // return false;
                            // } //Still needs to be implemented
                    }
                }
                
                
                else{
                        cout << "(false) File/Directory does not exist." << endl;
                        return false;
                }
                
            
                    
            // cout << "Inside testCommand is: " << testCommand[0] << endl;
            // cout << "Inside str is: " << str << endl;
            // if(stat(testCommand, &buf) == 0){  //Upon successful completion, 0 shall be returned. Otherwise, -1 shall be returned and errno set to indicate the error.
            //     if(buf.st_mode & S_IFREG){   //S_IFREG is a test for regular files 
            //         cout << "Valid file input" << endl;
            //     }
            //     else if(buf.st_mode & S_IFDIR){ //directory
            //         cout << "Valid directory input" << endl;
            //     }
            //     return true;
            // }
            // else{
            //     cout << "Error, input is not a known file or directory.." << endl;
            //     return false;
            // } //Still needs to be implemented
}   
        bool EMPTYTREE(){
                return false;
        }
};

class InputRedirect : public Argument{
    private: 
        Argument* LHS;
        Argument* RHS; 
    public:
        InputRedirect(){
             LHS = 0;
             RHS = 0; 
         }
        ~InputRedirect(){}
        bool execute(){
            int fid = dup(0);

            int file = open(RHS->getInput().c_str(), O_RDONLY);
    
            if(file == -1)
            {
                perror("Error opening the file!");
                return false;
            }
    
    
            close(0);
            dup2(file, 0);
    
            bool result = LHS->execute();
    
            close(0);
            dup2(fid, 0);
    
            return result;
        }
        void addLeftArgument(Argument* command){
            LHS = command; 
        }
        void addRightArgument(Argument* command){
            RHS = command; 
        }
        string getInput(){
            return "";
        }
        bool EMPTYTREE(){
            return (LHS == 0 && RHS == 0);
        }
        
};
//=============================================================================
class OutputRedirect : public Argument{
    private:
        Argument* LHS;
        Argument* RHS; 
    public: 
        OutputRedirect(){
             LHS = 0;
             RHS = 0; 
         }
        ~OutputRedirect(){}
        bool execute(){
            int fid  = dup(1);
            int file = open(RHS->getInput().c_str() , O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    
            if(file == -1)
            {
                perror("Could not open file!");
                return false;
            }
    
            close(1);
            dup2(file, 1);
    
            bool result = LHS->execute();
    
    
            close(1);
            dup2(fid, 1);
    
    
            return result;

        }
        void addLeftArgument(Argument* command){
            LHS = command; 
        }
        void addRightArgument(Argument* command){
            RHS = command; 
        }
        string getInput(){
            return "";
        }
        bool EMPTYTREE(){
            if (LHS == 0 && RHS == 0){
                return true;
            }
            else{
                return false; 
            }
        }
};

//=============================================================================
class OutputRedirect_Append: public Argument{
    private: 
        Argument* LHS;
        Argument* RHS;
    public: 
        OutputRedirect_Append(){
             LHS = 0;
             RHS = 0; 
         }
        ~OutputRedirect_Append(){}
        bool execute(){
            int fid  = dup(1);
            int file = open(RHS->getInput().c_str() , O_CREAT|O_APPEND|O_RDWR, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

            if(file == -1)
            {
                perror("Could not open file!");
                return false;
            }
    
            close(1);
            dup2(file, 1);
    
            bool result = LHS->execute();
    
    
            close(1);
            dup2(fid, 1);


            return result;
        }
        void addLeftArgument(Argument* command){
            LHS = command; 
        }
        void addRightArgument(Argument* command){
            RHS = command; 
        }
        string getInput(){
            return "";
        }
        bool EMPTYTREE(){
            if (LHS == 0 && RHS == 0){
                return true;
            }
            else{
                return false; 
            }
        }
};

//=============================================================================
class Pipe: public Argument{
    private:
        Argument* LHS;
        Argument* RHS; 
    public: 
        Pipe(){
             LHS = 0;
             RHS = 0; 
         }
        ~Pipe(){}
        bool execute(){
            pid_t pid;
            int fd[2];
            bool returnValue = true;
            
            pipe(fd);
            pid = fork();
            
            if(pid==0){
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                returnValue = LHS->execute();
                exit(0);
            }
            else{
                pid=fork();
                
                if(pid == 0){
                    dup2(fd[0], STDIN_FILENO);
                    close(fd[1]);
                    close(fd[0]);
                    returnValue = RHS->execute();
                    exit(0);
                }
                else{
                    int status;
                    close(fd[1]);
                    close(fd[0]);
                    waitpid(pid, &status, 0);
                    return returnValue;
                }
            }
        }
        void addLeftArgument(Argument* command){
            LHS = command; 
        }
        void addRightArgument(Argument* command){
            RHS = command; 
        }
        string getInput(){
            return "";
        }
        bool EMPTYTREE(){
            if (LHS == 0 && RHS == 0){
                return true;
            }
            else{
                return false; 
            }
        }
    
};

//=============================================================================

#endif

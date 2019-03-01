#ifndef _RSHELL_H
#define _RSHELL_H

#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cctype>
#include <vector>
#include <string>
#include <string.h>
using namespace std;
#include "arguments.h"


//*Quick Note
//*************
//Argument classes are working when commands are hard coded, but there's issues when taking in from the command line

//[FUNCTIONS DELCARATIONS]
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void CREATECOMMANDARRAY(vector<string>& SSCOMMANDS3, vector<Argument*>& COMMANDVECTOR2){
	CMDPROMPT cmd_temp;
		for(int i = 0; i < SSCOMMANDS3.size() - 1; i++){
			if(SSCOMMANDS3.at(i) == "&&"){
				CMDPROMPT* AndCMD = new CMDPROMPT(SSCOMMANDS3.at(i));
				COMMANDVECTOR2.push_back(new AND());	
			}
			else if(SSCOMMANDS3.at(i) == "||"){
				CMDPROMPT* OrCMD = new CMDPROMPT(SSCOMMANDS3.at(i));
				COMMANDVECTOR2.push_back(new OR());
			}
//=======================[assignment 4!!]=====================================
        	else if(SSCOMMANDS3.at(i) == "|"){
            	COMMANDVECTOR2.push_back(new Pipe());
	        }
        	else if(SSCOMMANDS3.at(i) == "<"){
        	    COMMANDVECTOR2.push_back(new InputRedirect());
        	}
        	else if(SSCOMMANDS3.at(i) == ">"){
            	COMMANDVECTOR2.push_back(new OutputRedirect());
        	}
        	else if(SSCOMMANDS3.at(i) == ">>"){
            	COMMANDVECTOR2.push_back(new OutputRedirect_Append());
        	}
//============================================================================
			else if(SSCOMMANDS3.at(i) == "test"){
				// cout << "WHATS INSIDE: " << SSCOMMANDS3.at(i+1) << endl;
				// cout << "WHATS INSIDE: " << SSCOMMANDS3.at(i+2) << endl;
				if(SSCOMMANDS3.at(i + 1) == " "){ //Edge case if only "test" is inputted
					cout << "Not enough arguments inputted" << endl;
					break;
				}
				else{
		            bool semiColonFound = false;
		            
		            // if(SSCOMMANDS3.at(i+2).back() == ';'){
		            //     semiColonFound = true;
		            //     SSCOMMANDS3.at(i+2).back() = 0;
		            // }
		            	
		            	// cout << "one" << endl;
		            	// cout << "INSIDE SSCOMMANDS3: " << SSCOMMANDS3.at(i+1) << endl;
		            	if( (SSCOMMANDS3.at(i+1) == "-e") || (SSCOMMANDS3.at(i+1) == "-f") || (SSCOMMANDS3.at(i+1) == "-d") ){
		            		// cout << "two" << endl;
		            	//	cout << SSCOMMANDS3.at(i+2) << "<----lookhere" << endl;
		            		TestCommand *SHELLY = new TestCommand(SSCOMMANDS3.at(i+2));
		            	//	cout << SSCOMMANDS3.at(i+2) << "<----lookhere" << endl;
		            		SHELLY->flageater(SSCOMMANDS3.at(i+1));
		            		COMMANDVECTOR2.push_back(SHELLY); //Might need to change index later when integrating -e, -d and -f
		            		i+=2;
		            		
		            	}
		            	
		            	else{
		            		// cout << "three" << endl;
		            		// cout << "INSIDE SSCOMMANDS3: " << SSCOMMANDS3.at(i+2) << endl;
		            		COMMANDVECTOR2.push_back(new TestCommand(SSCOMMANDS3.at(i+1)));
		            		i++;
		            	}
		            	
		            if(semiColonFound){
		                COMMANDVECTOR2.push_back(new Semicolon());
		            }
		            
		            //COMMANDVECTOR2.at(i)->execute();
				}
			}
			
			else if(SSCOMMANDS3.at(i) == "["){  ///DOESN'T WORK

				// cout << "WHATS INSIDE: " << SSCOMMANDS3.at(i+1) << endl;
				// cout << "WHATS INSIDE: " << SSCOMMANDS3.at(i+2) << endl;

				if(SSCOMMANDS3.at(i+1) == " "){
					cout << "Not enough arguments" << endl;
					break;
				}
	            bool semiColonFound = false;
	            if(SSCOMMANDS3.at(i+3).back() == ';'){
	                semiColonFound = true;
	            }
	            
		            	if( (SSCOMMANDS3.at(i+1) == "-e") || (SSCOMMANDS3.at(i+1) == "-f") || (SSCOMMANDS3.at(i+1) == "-d") ){
		            		// cout << "two" << endl;
		            		TestCommand *OPPA = new TestCommand(SSCOMMANDS3.at(i+2));
		            		OPPA->flageater(SSCOMMANDS3.at(i+1));
		            		COMMANDVECTOR2.push_back(OPPA); //Might need to change index later when integrating -e, -d and -f
		            	
		            		i += 3;
		            	}
		            	
		            	else{
		            		// cout << "three" << endl;
		            		// cout << "INSIDE SSCOMMANDS3: " << SSCOMMANDS3.at(i+2) << endl;
		            		//cout << SSCOMMANDS3.at(i+1) << "IS DYLAN" << endl;
		            		COMMANDVECTOR2.push_back(new TestCommand(SSCOMMANDS3.at(i+1)));
		            		i += 2;
		            		
		            	}	            
		        
		        
		        
		        
	            if(semiColonFound){
	                COMMANDVECTOR2.push_back(new Semicolon());
	            
	            	
	            }
	            
	          
	        }
	        
			else{
				if(SSCOMMANDS3.at(i).at(SSCOMMANDS3.at(i).length()-1) == ';'){
					SSCOMMANDS3.at(i).at(SSCOMMANDS3.at(i).length()-1) = ' ';
					cmd_temp.concat(SSCOMMANDS3.at(i));
					COMMANDVECTOR2.push_back(new CMDPROMPT(cmd_temp.getInput()));
					COMMANDVECTOR2.push_back(new Semicolon());
					cmd_temp.emptyCurrentString();
				}
				else{
					cmd_temp.concat(SSCOMMANDS3.at(i));
					if( (SSCOMMANDS3.at(i+1) == "&&") || ((SSCOMMANDS3.at(i+1)) == "||") || (SSCOMMANDS3.at(i+1) == " ") || (SSCOMMANDS3.at(i+1) == "|") || (SSCOMMANDS3.at(i+1) == ">>") || (SSCOMMANDS3.at(i+1) == ">") || (SSCOMMANDS3.at(i+1) == "<")){
						COMMANDVECTOR2.push_back(new CMDPROMPT(cmd_temp.getInput()));
						cmd_temp.emptyCurrentString();
		// 				for(int i = 0; i < COMMANDVECTOR2.size(); i++){
		// 					cout << COMMANDVECTOR2.at(i)->getInput() << endl;;
		//				} Test to check that command vector 2 has been populated correctly
					}
				}
			}
		}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void CREATETREE(vector<Argument*>& COMMANDVECTOR3, Argument* &TREE2){ 
	//cout << "Test Create Tree" << endl;
	Argument *TEMPCONTAINER = 0;
	for(int i = 0; i < COMMANDVECTOR3.size(); i++){
		if(COMMANDVECTOR3.size() == 1){
			TEMPCONTAINER = COMMANDVECTOR3.at(0);
		}
		else if(COMMANDVECTOR3.at(i)->EMPTYTREE() == true){
			if(TEMPCONTAINER == 0){
				COMMANDVECTOR3.at(i)->addLeftArgument(COMMANDVECTOR3.at(i-1));
			}
			else{
				COMMANDVECTOR3.at(i)->addLeftArgument(TEMPCONTAINER);
			}

			COMMANDVECTOR3.at(i)->addRightArgument(COMMANDVECTOR3.at(i+1));
			TEMPCONTAINER = COMMANDVECTOR3.at(i);
		}
		//cout << "Tree Populated" << endl;
	}
		//cout << "Here it is end of tree" << endl;
		TREE2 = TEMPCONTAINER;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void PARSE(string& INPUT3, vector<string>& SSCOMMANDS2){
	//cout << "PARSE TEST" << endl;
	char *INPUTHOLD = new char[INPUT3.length() + 1];
	strcpy(INPUTHOLD, INPUT3.c_str());
	char *NOSPACEINPUT = strtok(INPUTHOLD, " ");
		while(NOSPACEINPUT != 0){
			string sturing = NOSPACEINPUT;
			SSCOMMANDS2.push_back(sturing);
			//cout << sturing << endl;
			NOSPACEINPUT = strtok(NULL, " ");
		}
	SSCOMMANDS2.push_back(" ");
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Argument* PARSEPARENTHESIS(string INPUT4){
	
	bool parenthesisfound = false;
	
//--------------[CHECK TO SEE IF LEFT = RIGHT. PARENTHESIS SHOULD CANCEL OUT---		
		int leftcount = 0;
		int rightcount = 0;
		for(int i = 0; i < INPUT4.size(); i++){
			if(INPUT4.at(i) == '('){
				parenthesisfound = true;
				leftcount = leftcount + 1;
			}
			if(INPUT4.at(i) == ')'){
				parenthesisfound = true;
				rightcount = rightcount + 1;
			}
		}	

	if(leftcount != rightcount){
		cout  << "Parenthesis do not make sense." << endl;
		return nullptr;
	}

	
	vector<string> SSCOMMANDS4;
	vector<Argument*> COMMANDVECTOR4;
	Argument* VIRGINITREE;	

	
if(!parenthesisfound){
	PARSE(INPUT4, SSCOMMANDS4);						//STEP ONE
	CREATECOMMANDARRAY(SSCOMMANDS4, COMMANDVECTOR4);	//STEP TWO
	CREATETREE(COMMANDVECTOR4, VIRGINITREE);				//STEP THREE
	return VIRGINITREE;
}

else{
	PARSE(INPUT4,SSCOMMANDS4);
	CMDPROMPT cmd_temp;
	int COUNT = 0;
	
	while(COUNT < SSCOMMANDS4.size()-1){
/*C1=*/			if(SSCOMMANDS4.at(COUNT).front() == '('){
				SSCOMMANDS4.at(COUNT).erase(SSCOMMANDS4.at(COUNT).begin());
				int PCOUNT = 0;
				bool LASTSEMI = false;
				bool ELFIN = false;
				string newstring;
					while(ELFIN == false){
								if(SSCOMMANDS4.at(COUNT) == " "){
									cout << "dont make sense" << endl;
									return nullptr;
								}
								for(int i = 0; i < SSCOMMANDS4.at(COUNT).length(); i++){
										if(SSCOMMANDS4.at(COUNT).at(i) == '('){
									//			cout << "one" << endl;
			                            		PCOUNT++;
		                        		}
				                		else if(SSCOMMANDS4.at(COUNT).at(i) == ')' && PCOUNT > 0){
			 	                	//	        cout << "two" << endl;
			 	                		        PCOUNT--;
    				            		}
				                		else if(SSCOMMANDS4.at(COUNT).at(i) == ')' && PCOUNT == 0){
    				             	//			cout << "three" << endl;
    				             				ELFIN = true;
            				        		    	if(i < SSCOMMANDS4.at(COUNT).length()-1){
                        					     		if(SSCOMMANDS4.at(COUNT).at(i+1) == ';'){
                    			        		   		LASTSEMI = true;
                                						}
                            						}
                				    			SSCOMMANDS4.at(COUNT).erase(SSCOMMANDS4.at(COUNT).begin() + i, SSCOMMANDS4.at(COUNT).end());
                    					}
      
								}
									//cout << "added to string" << endl;
									newstring.append(SSCOMMANDS4.at(COUNT));
									newstring.append(" ");
									COUNT++;
									// cout << newstring << endl;
									// cout << COUNT << endl;
					}
					//cout << "Did i reach here?" << endl;
				COMMANDVECTOR4.push_back(PARSEPARENTHESIS(newstring));
				if(LASTSEMI){
					COMMANDVECTOR4.push_back(new Semicolon());	
				}	
			}


/*C2=*/		else{
					if(SSCOMMANDS4.at(COUNT) == "&&"){
							CMDPROMPT* AndCMD = new CMDPROMPT(SSCOMMANDS4.at(COUNT));
							COMMANDVECTOR4.push_back(new AND());	
					}
					else if(SSCOMMANDS4.at(COUNT) == "||"){
							CMDPROMPT* OrCMD = new CMDPROMPT(SSCOMMANDS4.at(COUNT));
							COMMANDVECTOR4.push_back(new OR());
					}
					else if(SSCOMMANDS4.at(COUNT) == "test"){
							if(SSCOMMANDS4.at(COUNT + 1) == " "){ //Edge case if only "test" is inputted
								cout << "Not enough arguments inputted" << endl;
								break;
							}
							else{
		            			bool semiColonFound = false;
		            				if(SSCOMMANDS4.at(COUNT+2).back() == ';'){
		                				semiColonFound = true;
		                				SSCOMMANDS4.at(COUNT+2).back() = 0;
		            				}
		            				if( (SSCOMMANDS4.at(COUNT+1) == "-e") || (SSCOMMANDS4.at(COUNT+1) == "-f") || (SSCOMMANDS4.at(COUNT+1) == "-d") ){
		            					TestCommand *OPPA = new TestCommand(SSCOMMANDS4.at(COUNT+2));
		            					OPPA->flageater(SSCOMMANDS4.at(COUNT+1));
		            					COMMANDVECTOR4.push_back(OPPA); //Might need to change index later when integrating -e, -d and -f
		            			        COUNT += 2;
		            				}
		            				else{
		            					COMMANDVECTOR4.push_back(new TestCommand(SSCOMMANDS4.at(COUNT+1)));
		            			        COUNT++;
		            				}
		            				
		            			if(semiColonFound){
		                			COMMANDVECTOR4.push_back(new Semicolon());
		            			}
							}
					}
					else if(SSCOMMANDS4.at(COUNT) == "["){  ///DOESN'T WORK
						cout << "WHATS INSIDE: " << SSCOMMANDS4.at(COUNT+1) << endl;
						cout << "WHATS INSIDE: " << SSCOMMANDS4.at(COUNT+2) << endl;
								if(SSCOMMANDS4.at(COUNT+1) == " "){
									cout << "Not enough arguments" << endl;
									break;
								}
	            			bool semiColonFound = false;
	            			if(SSCOMMANDS4.at(COUNT+3).back() == ';'){
	                		semiColonFound = true;
	            			}
		            		if( (SSCOMMANDS4.at(COUNT+1) == "-e") || (SSCOMMANDS4.at(COUNT+1) == "-f") || (SSCOMMANDS4.at(COUNT+1) == "-d") ){
		            			TestCommand *OPPA = new TestCommand(SSCOMMANDS4.at(COUNT+2));
		            			OPPA->flageater(SSCOMMANDS4.at(COUNT+1));
		            			COMMANDVECTOR4.push_back(OPPA); //Might need to change index later when integrating -e, -d and -f
		            				       COUNT += 3;
		            		}
		            		else{
		            			COMMANDVECTOR4.push_back(new TestCommand(SSCOMMANDS4.at(COUNT+1)));
		            				       COUNT += 2;
		            		}	            
	            			if(semiColonFound){
	                			COMMANDVECTOR4.push_back(new Semicolon());
	            			}
	        		}
//########
					
					else{
							if(SSCOMMANDS4.at(COUNT).at(SSCOMMANDS4.at(COUNT).length()-1) == ';'){
							SSCOMMANDS4.at(COUNT).at(SSCOMMANDS4.at(COUNT).length()-1) = ' ';
							cmd_temp.concat(SSCOMMANDS4.at(COUNT));
							COMMANDVECTOR4.push_back(new CMDPROMPT(cmd_temp.getInput()));
							COMMANDVECTOR4.push_back(new Semicolon());
							cmd_temp.emptyCurrentString();
							}
							else{
							cmd_temp.concat(SSCOMMANDS4.at(COUNT));
								if( (SSCOMMANDS4.at(COUNT+1) == "&&") || ((SSCOMMANDS4.at(COUNT+1)) == "||") || (SSCOMMANDS4.at(COUNT+1) == " ") || (SSCOMMANDS4.at(COUNT+1) == "|") || (SSCOMMANDS4.at(COUNT+1) == ">>") || (SSCOMMANDS4.at(COUNT+1) == ">") || (SSCOMMANDS4.at(COUNT+1) == "<") ){
									COMMANDVECTOR4.push_back(new CMDPROMPT(cmd_temp.getInput()));
									cmd_temp.emptyCurrentString();
								}
							}
					}
						COUNT++;
				}						
			}
		// if(SSCOMMANDS4.at(COUNT).front() == '('){
		// 	bool ELFIN = false;
		// 	bool LASTSEMI = false;
		// 	int PCOUNT = 0;
		// 	string yelp;
		// 	while(ELFIN != true){
		// 		for(int i = 0; i < SSCOMMANDS4.at(COUNT).length(); i++){
		// 			if(SSCOMMANDS4.at(COUNT).at(i) == '('){
  //                          PCOUNT = PCOUNT + 1;
  //                      }
  //                  else if(SSCOMMANDS4.at(COUNT).at(i) == ')' && PCOUNT > 0){
  //                          PCOUNT = PCOUNT - 1;
  //                  }
  //                  else if(SSCOMMANDS4.at(COUNT).at(i) == ')' && PCOUNT == 0){
  //                  		ELFIN = true;
  //                          	if(i < SSCOMMANDS4.at(COUNT).length()-1){
  //                              	if(SSCOMMANDS4.at(COUNT).at(i+1) == ';'){
  //                                  	LASTSEMI = true;
  //                              	}
  //                          	}
  //                      SSCOMMANDS4.at(COUNT).erase(SSCOMMANDS4.at(COUNT).begin() + i, SSCOMMANDS4.at(COUNT).end());
  //                  }
		// 		}
		// 		yelp.append(SSCOMMANDS4.at(COUNT));
		// 		yelp.append(" ");
		// 		COUNT++;
		// 	}
		// 	PARSEPARENTHESIS(INPUT4, SSCOMMANDS4,COMMANDVECTOR4,yelp);
		// 	if(LASTSEMI){
		// 		COMMANDVECTOR4.push_back(new Semicolon());	
		// 	}
		// }
		// else{
		// 	CREATECOMMANDARRAY(SSCOMMANDS4, COMMANDVECTOR4);
		// }
		// 					COUNT++;
	
	// cout << "Before I run execute" << endl;
	// //cout  << newstring << endl;
	// CREATETREE(SSCOMMANDS4, TREE4);
	// if(!TREE4){
	// 	cout << "This bitch empty" << endl;
	// }
	CREATETREE(COMMANDVECTOR4, VIRGINITREE);
	return VIRGINITREE;
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void EXECUTEINPUT(string& INPUT1){	//check to see if comment # is found
	//cout << "Testing Execute Input" << endl;
	Argument* TREE;
	vector<string> SSCOMMANDS;
	vector<Argument*> COMMANDVECTOR;
	bool HASHTAGFOUND = false;
	int HASHTAGLOCATION = 0;


//----------------[HASTAG COMMENT FINDER]---------------------------------------
		for(int i = 0; i < INPUT1.length(); i++){			//CHECK FOR COMMENTS
			 	if(INPUT1[i] == '#'){
			 		HASHTAGFOUND = true;					//SETS TO FOUND
					HASHTAGLOCATION = i;					//SAVES LOCATION OF HASTAG
	 			}
		}
		if(HASHTAGFOUND == true){
			INPUT1.erase( INPUT1.begin() + HASHTAGLOCATION, INPUT1.end()); //ERASES EVERYTHING AFTER HASHTAG INCLUDING
		}
//----------------------[PARENTHESIS FINDER]------------------------------------

//----------------[PREVIOUS SECTION DECIDES OPTION #1 OR #2]--------------------

			//OPTION #1: HAS PARENTHESIS
	TREE = PARSEPARENTHESIS(INPUT1);			//STEP ONE


        if(TREE){									//FINAL STEP
	   		TREE->execute();						//CALLS OUR BEAUTIFUL BASE CLASS
		}
		else{
			cout << "Invalid Inputs" << endl;
		}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//[MAIN FUNCTION]
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// int main(int args, char* argv[]) {

// //char*[256] arguments;
// 	string input;
// 	vector<string> insertparam;
	
// 	char hostname[HOST_NAME_MAX];
// 	char username[LOGIN_NAME_MAX];
// 	gethostname(hostname, HOST_NAME_MAX);
// 	getlogin_r(username, LOGIN_NAME_MAX);
	
// //-----------------------------------------------------------------------------
// 		cout << "Welcome to Scotshell!" << endl; //INTRODUCTORY COUT

// 		while(input != "quit" && input != "exit"){
// 			cout << username << "@" << hostname << "$ ";
// 			getline(cin, input);
// 				if(input != "quit" && input != "exit"){
// 					//cout << "test0";
// 					EXECUTEINPUT(input);
// 				}
// 			//cout << "RAN THE LOOP ONCE" << endl;
// 		}
// //-----------------------------------------------------------------------------

// 	return 0;
// }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//[FUNCTIONS IMPLEMENTATIONS]
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//=============================================================================

//==============================================================================



//==============================================================================



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif

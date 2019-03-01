#include "arguments.h"
#include "rshell.h"

using namespace std;

int main(int args, char* argv[]) {

//char*[256] arguments;
	string input;
	vector<string> insertparam;
	
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);
	
//-----------------------------------------------------------------------------
		cout << "Welcome to Scotshell!" << endl; //INTRODUCTORY COUT

		while(input != "quit" && input != "exit"){
			cout << username << "@" << hostname << " $ ";
			getline(cin, input);
				if(input != "quit" && input != "exit"){
					//cout << "test0";
					EXECUTEINPUT(input);
				}
			//cout << "RAN THE LOOP ONCE" << endl;
		}
//-----------------------------------------------------------------------------

	return 0;
}

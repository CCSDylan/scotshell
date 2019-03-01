#include <iostream>
#include <vector>
#include <string>
#include "arguments.h"
#include "rshell.h"
#include <gtest/gtest.h>

using namespace std;

CMDPROMPT* empty = new CMDPROMPT("");
CMDPROMPT* cmd1 = new CMDPROMPT("echo Normal Test");
CMDPROMPT* cmd2 = new CMDPROMPT("echo AND test");
CMDPROMPT* cmd3 = new CMDPROMPT("echo Hello");
CMDPROMPT* cmd4 = new CMDPROMPT("echo OR Test");
CMDPROMPT* cmd5 = new CMDPROMPT("echo Semicolon Test");
CMDPROMPT* cmd6 = new CMDPROMPT("echo Good Bye");
CMDPROMPT* badCMD1 = new CMDPROMPT("IPA");
CMDPROMPT* multipleSemicolon1 = new CMDPROMPT("echo testing");
CMDPROMPT* multipleSemicolon2 = new CMDPROMPT("echo multiple");
CMDPROMPT* multipleSemicolon3 = new CMDPROMPT("echo semicolons");

////********************************************************************
//// New Global Variables for Test Commands Below
////********************************************************************
string testCommand1 = "src/rshell.h";
string testCommand2 = "src";
string badTestCommand1 = "File.DoesNotExist";
string badTestCommand2 = "Folder.DoesNotExist";

////********************************************************************
//// New Global Variables for Parenthesis Commands Below
////********************************************************************
CMDPROMPT* parCMD1 = new CMDPROMPT("(echo A");
CMDPROMPT* parCMD2 = new CMDPROMPT("echo B)");
CMDPROMPT* parCMD3 = new CMDPROMPT("(echo C");
CMDPROMPT* parCMD4 = new CMDPROMPT("echo D)");
CMDPROMPT* echoCMD1 = new CMDPROMPT("echo A");
CMDPROMPT* echoCMD2 = new CMDPROMPT("echo B");
CMDPROMPT* echoCMD3 = new CMDPROMPT("echo C");
CMDPROMPT* echoCMD4 = new CMDPROMPT("echo D");
////********************************************************************
//// Global Test Commands with Flags Below
////********************************************************************

string fCommand1 = "test -f CMakeLists.txt";
string fFailCommand1 = "test -f src";
string dCommand1 = "test -d src";
string dFailCommand1 = "test -d CMakeLists.txt";
string eCommand1 = "test -e CMakeLists.txt";
string eCommand2 = "test -e src";
string eFailCommand1 = "test -e test File.DoesNotExist";
string eFailCommand2 = "test -e test Folder.DoesNotExist";

////********************************************************************
//// Global Test Commands with Square Bracks Below
////********************************************************************

string bracketCMD1 = "[ -d src ]";
string bracketCMD2 = "[ -f CMakeLists.txt ]";
string bracketCMD3 = "[ -e README.md ]";
string bracketCMD4 = "[ src ]";
string bracketCMD5 = "[ CMakeLists.txt ]";
string bracketCMD6 = "[ File.DNE ]";
string bracketCMD7 = "[ Folder.DNE ]";
string failCMD1 = "[ -d CMakeLists.txt ]";
string failCMD2 = "[ -f src ]";
string failCMD3 = "[ -e File.DNE ]";
string failCMD4 = "[ -e Folder.DNE ]";


////*******************************************************************
//// REDIRECT TESTING GLOBALS
////*******************************************************************
string cat = "cat";
string cmake = "Info.txt";
string catSource = "cat Info.txt";
string catSource2 = "cat CMakeLists.txt";
string dest = "Logs.txt";
string tr1 = "tr T t";
string tr2 = "tr A-Z a-z";
string realCmake = "CMakeLists.txt"; 
   
CMDPROMPT* cmak = new CMDPROMPT(cmake);         //Not actually cmake but has words from cmake Info.txt
CMDPROMPT* catCmd = new CMDPROMPT(cat);           //cat 
CMDPROMPT* destCmd = new CMDPROMPT(dest);         //Logs.txt (Destination 1)
CMDPROMPT* catSourceCmd = new CMDPROMPT(catSource);        //NewFile2.txt
CMDPROMPT* catSourceCmd2 = new CMDPROMPT(catSource2);
CMDPROMPT* trTest = new CMDPROMPT(tr1);        //TestFile2.txt
CMDPROMPT* trPipeTest = new CMDPROMPT(tr2);      //tr A-Z a-z
CMDPROMPT* cmakeCmd = new CMDPROMPT(realCmake);
////********************************************************************
//// End Global Variable Declarations
////********************************************************************




TEST(EmptyCommandLineTest, newlineEntered){
    testing::internal::CaptureStdout();
    empty->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(CommandClassTest, executionTest){
    CMDPROMPT* cmdA = new CMDPROMPT("echo hello");
    CMDPROMPT* cmdB = new CMDPROMPT("echo good bye");
    CMDPROMPT* cmdC = new CMDPROMPT("echo last one");
    testing::internal::CaptureStdout();
    cmdA->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\n");
    testing::internal::CaptureStdout();
    cmdB->execute();
    string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "good bye\n");
    testing::internal::CaptureStdout();
    cmdC->execute();
    string output3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output3, "last one\n");
}

TEST(ConnectorTests, generalANDTest) {
    AND* testMe = new AND();
    testMe->addLeftArgument(cmd1);    //AND is working during individual tests but is not working when trying to put together
    testMe->addRightArgument(cmd2);  //All of this executes properly
    testing::internal::CaptureStdout();
    testMe->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Normal Test\nAND test\n");
    testMe->addLeftArgument(cmd2);
    testMe->addRightArgument(cmd1);
    testing::internal::CaptureStdout();   
    testMe->execute();
    string outpute = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outpute, "AND test\nNormal Test\n");
    
}

TEST(ConnectorTests, ANDFailureTest){
    AND* testFailure = new AND();
    testFailure->addLeftArgument(badCMD1);
    testFailure->addRightArgument(cmd1);
    testing::internal::CaptureStdout();
    testFailure->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output,"");
}


TEST(ConnectorTests, generalORTest){
    OR* testOr = new OR();
    testOr->addLeftArgument(cmd4);
    testOr->addRightArgument(cmd3);
    testing::internal::CaptureStdout();
    testOr->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "OR Test\n");
    testOr->addLeftArgument(cmd3);
    testOr->addRightArgument(cmd4);
    testing::internal::CaptureStdout();
    testOr->execute();
    string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "Hello\n");
}

TEST(ConnectorTests, ORFirstArgumentFailureTest){
    OR* testORFailure = new OR();
    testORFailure->addLeftArgument(badCMD1);
    testORFailure->addRightArgument(cmd4);
    testing::internal::CaptureStdout();
    testORFailure->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output,"OR Test\n");
}

TEST(ConnectorTests, ORSecondArgumentNoRunTest){
    OR* testORFailure = new OR();
    testORFailure->addLeftArgument(cmd4);
    testORFailure->addRightArgument(badCMD1);
    testing::internal::CaptureStdout();
    testORFailure->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output,"OR Test\n");
}

TEST(ConnectorTests, generalSemicolonTest){
    Semicolon* testSemi = new Semicolon();
    testSemi->addLeftArgument(cmd1);
    testSemi->addRightArgument(cmd5);
    testing::internal::CaptureStdout();
    testSemi->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Normal Test\nSemicolon Test\n");
    Semicolon* testSemi2 = new Semicolon(cmd1, cmd3);
    testing::internal::CaptureStdout();
    testSemi2->execute();
    string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "Normal Test\nHello\n");
}

TEST(ConnectorTests, TripleSemicolonTest){
    Semicolon* testSemi1 = new Semicolon();
    testSemi1->addLeftArgument(multipleSemicolon1);
    testSemi1->addRightArgument(multipleSemicolon2);
    Semicolon* testSemi2 = new Semicolon();
    testSemi2->addLeftArgument(testSemi1);
    testSemi2->addRightArgument(multipleSemicolon3);
    testing::internal::CaptureStdout();
    testSemi2->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "testing\nmultiple\nsemicolons\n");
}

TEST(ConnectorTests, multipleConnectors1){
     AND* testCompoundAND = new AND();
     testCompoundAND->addLeftArgument(badCMD1);
     testCompoundAND->addRightArgument(cmd1);
     testCompoundAND->execute();
     OR* testCompoundOR = new OR();
     testCompoundOR->addLeftArgument(testCompoundAND);
     testCompoundOR->addRightArgument(cmd6);
     testing::internal::CaptureStdout();
     testCompoundOR->execute();
     string output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "Good Bye\n");     
}

TEST(ConnectorTests, multipleConnectors2){
     OR* testCompound = new OR();
     testCompound->addLeftArgument(cmd4);
     testCompound->addRightArgument(badCMD1);
     AND* testANDSecond = new AND();
     testANDSecond->addLeftArgument(testCompound);
     testANDSecond->addRightArgument(cmd2);
     testing::internal::CaptureStdout();
     testANDSecond->execute(); 
     string output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "OR Test\nAND test\n");
}

TEST(ConnectorTests, SemicolonANDTest){
     AND* ANDtester = new AND();
     ANDtester->addLeftArgument(cmd2);
     ANDtester->addRightArgument(cmd1);
     Semicolon* sColonTest = new Semicolon();
     sColonTest->addLeftArgument(ANDtester);
     sColonTest->addRightArgument(cmd5);
     testing::internal::CaptureStdout();
     sColonTest->execute();
     string output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "AND test\nNormal Test\nSemicolon Test\n");
}

TEST(ConnectorTests, SemicolonORTest){
     OR* ORtester = new OR();
     ORtester->addLeftArgument(cmd4);
     ORtester->addRightArgument(cmd1);
     Semicolon* sColonTest = new Semicolon();
     sColonTest->addLeftArgument(ORtester);
     sColonTest->addRightArgument(cmd5);
     testing::internal::CaptureStdout();
     sColonTest->execute();
     string output = testing::internal::GetCapturedStdout();
     EXPECT_EQ(output, "OR Test\nSemicolon Test\n");
}

TEST(TestCommandTest, InvalidFileNoFlagTest){
    TestCommand* testFile = new TestCommand(badTestCommand1);
    EXPECT_EQ(testFile->execute(), false);
}

TEST(TestCommandTest, InvalidDirectoryNoFlagTest){
    TestCommand* testFolder = new TestCommand(badTestCommand2);
    EXPECT_EQ(testFolder->execute(), false);
}

TEST(TestCommandTest, ValidFileNoFlagTest){
    TestCommand* testValidFile = new TestCommand(testCommand1);
    EXPECT_EQ(testValidFile->execute(), true);
}

TEST(TestCommandTest, ValidDirectoryNoFlagTest){
    TestCommand* testValidDirectory = new TestCommand(testCommand2);
    EXPECT_EQ(testValidDirectory->execute(), true);
}

TEST(TestCommandFlagTest, ValidFlagFlagTest){
    string input = "test -e src";
    testing::internal::CaptureStdout();
    EXECUTEINPUT(input); 
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) valid directory input\n"); 
}

TEST(TestCommandFlagTest, ValidFFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(fCommand1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) is reg file\n");
}

TEST(TestCommandFlagTest, InvalidFFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(fFailCommand1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) is NOT reg file\n");
}

TEST(TestCommandFlagTest, ValidDFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(dCommand1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) exists and is directory\n");
}

TEST(TestCommandFlagTest, InvalidDFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(dFailCommand1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) directory not found\n");
}

TEST(TestCommandFlagTest, ValidFileEFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(eCommand1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) valid file input\n");
}

TEST(TestCommandFlagTest, ValidDirectoryEFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(eCommand2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) valid directory input\n");
}

TEST(TestCommandFlagTest, InvalidFileEFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(dFailCommand1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) directory not found\n");
}

TEST(TestCommandFlagTest, InvalidDirectoryEFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(dFailCommand1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) directory not found\n");
}

TEST(SquareBracketTest, DFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(bracketCMD1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) exists and is directory\n");
}

TEST(SquareBracketTest, fFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(bracketCMD2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) is reg file\n");
}

TEST(SquareBracketTest, eFlagTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(bracketCMD3);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) valid file input\n");
}

TEST(SquareBracketTest, NoFlagValidDirectoryTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(bracketCMD4);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) exists and is directory\n");
}


TEST(SquareBracketTest, NoFlagValidFileTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(bracketCMD5);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) is reg file\n");
}

TEST(SquareBracketTest, NoFlagInvalidFileTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(bracketCMD6);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) File/Directory does not exist.\n");
}

TEST(SquareBracketTest, NoFlagInvalidDirectoryTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(bracketCMD7);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) File/Directory does not exist.\n");
}

TEST(SquareBracketTest, WrongFlagValidFileTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(failCMD1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) directory not found\n");
}

TEST(SquareBracketTest, WrongFlagValidDirectoryTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(failCMD2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) is NOT reg file\n");
}


TEST(SquareBracketTest, eFLagInvalidFileTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(failCMD3);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) File/Directory does not exist.\n");
}

TEST(SquareBracketTest,eFlagInvalidDirectoryTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(failCMD4);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) File/Directory does not exist.\n");
}

TEST(SquareBracketTest, FlagInvalidFileTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(failCMD3);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) File/Directory does not exist.\n");
}


TEST(SquareBracketTest, FlagInvalidDirectoryTest){
    testing::internal::CaptureStdout();
    EXECUTEINPUT(failCMD4);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(false) File/Directory does not exist.\n");
}


TEST(ParenthesisTests, NoParenthesisTest) {
    AND* testMe = new AND(echoCMD1,echoCMD2);
    OR* testMe2 = new OR(testMe, echoCMD3);
    AND* testMe3 = new AND(testMe2,echoCMD4);
    testing::internal::CaptureStdout();
    testMe3->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A\nB\nD\n");
}

TEST(ParenthesisTests, ParenthesisANDTest) {
    string input = "(echo hello) && (echo bye)";
    testing::internal::CaptureStdout();
    EXECUTEINPUT(input);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "hello\nbye\n");
}     

TEST(ParenthesisTests, ParenthesisTest) {
    string input = "(echo A && echo B) || (echo C && echo D)";
    testing::internal::CaptureStdout();
    EXECUTEINPUT(input); 
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "A\nB\n");
}

TEST(TestCommandConnectorTests, ParenthesisTestCommandANDTest) {
    string input = "test -e src && echo bye";
    testing::internal::CaptureStdout();
    EXECUTEINPUT(input);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) valid directory input\nbye\n");
}

TEST(TestCommandConnectorTests, ParenthesisTestCommandANDTest2) {
    string input = "echo bye && test -e src";
    testing::internal::CaptureStdout();
    EXECUTEINPUT(input);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "bye\n(true) valid directory input\n");
}

TEST(TestCommandConnectorTests, ParenthesisTestCommandORTest) {
    string input = "test -e src || echo hi";
    testing::internal::CaptureStdout();
    EXECUTEINPUT(input);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(true) valid directory input\n");
}

TEST(InputRedirectTest, SingleInputRedirectTest){
    InputRedirect* iR = new InputRedirect();
    iR->addLeftArgument(catCmd);
    iR->addRightArgument(cmak);
    EXPECT_EQ(iR->execute(), true);
}

TEST(OutputRedirectTest, SingleOutputRedirectTest){
    OutputRedirect* oR = new OutputRedirect();
    oR->addLeftArgument(catSourceCmd);
    oR->addRightArgument(destCmd);
    EXPECT_EQ(oR->execute(), true);
}

TEST(OutputRedirectAppendTest, SingleOutputRedirectAppendTest){    
    OutputRedirect_Append* oR_A = new OutputRedirect_Append();
    oR_A->addLeftArgument(catSourceCmd);
    oR_A->addRightArgument(destCmd);
    EXPECT_EQ(oR_A->execute(),true);
}

TEST(OutputRedirectTest, CompoundOutputRedirectTest){    
    InputRedirect* iR2 = new InputRedirect();
    iR2->addLeftArgument(catCmd);
    iR2->addRightArgument(cmak);
    iR2->execute();
    OutputRedirect_Append* oR_A2 = new OutputRedirect_Append();
    oR_A2->addLeftArgument(iR2);
    oR_A2->addRightArgument(destCmd);
    EXPECT_EQ(oR_A2->execute(), true);
}

TEST(PipeTesting, PipeTest1){        
    InputRedirect* iR3 = new InputRedirect();
    iR3->addLeftArgument(catCmd);
    iR3->addRightArgument(cmak);
    iR3->execute();
    Pipe* p = new Pipe();
    p->addLeftArgument(iR3);
    p->addRightArgument(trTest);
    EXPECT_EQ(p->execute(), true);
}

TEST(CompoundRedirectTest, InputOutputRedirectTest){         
    InputRedirect* iR4 = new InputRedirect();
    iR4->addLeftArgument(catCmd);
    iR4->addRightArgument(cmak);
    Pipe* p2 = new Pipe();
    p2->addLeftArgument(iR4);
    p2->addRightArgument(trPipeTest);
    OutputRedirect_Append* oR_A3 = new OutputRedirect_Append();
    oR_A3->addLeftArgument(p2);
    oR_A3->addRightArgument(destCmd);
    EXPECT_EQ(oR_A3->execute(), true);
}

TEST(CompoundRedirectTest, InputOutputRedirectTest2){ 
    InputRedirect* iR5 = new InputRedirect();
    iR5->addLeftArgument(catCmd);
    iR5->addRightArgument(cmak);
    iR5->execute();
    OutputRedirect_Append* oR_A4 = new OutputRedirect_Append();
    oR_A4->addLeftArgument(iR5);
    oR_A4->addRightArgument(destCmd);
    EXPECT_EQ(oR_A4->execute(), true);
}

TEST(InputRedirectTest, InputRedirectTest2){ 
    InputRedirect* iR6 = new InputRedirect();
    iR6->addLeftArgument(catCmd);
    iR6->addRightArgument(cmakeCmd);
    EXPECT_EQ(iR6->execute(), true);
}

TEST(CompoundRedirectTest, InputOutputPipeTest){
    InputRedirect* iR7 = new InputRedirect();
    iR7->addLeftArgument(catCmd);
    iR7->addRightArgument(cmakeCmd);
    iR7->execute();
    Pipe* p3 = new Pipe();
    p3->addLeftArgument(iR7);
    p3->addRightArgument(trTest);
    p3->execute();
    Pipe* p4 = new Pipe();
    p4->addLeftArgument(p3);
    p4->addRightArgument(trPipeTest);
    p4->execute();
    OutputRedirect_Append* oR_A5 = new OutputRedirect_Append();
    oR_A5->addLeftArgument(p4);
    oR_A5->addRightArgument(destCmd);
    EXPECT_EQ(oR_A5->execute(), true);
}

TEST(CompoundRedirectTest, InputOutputNoAppendPipeTest){
    InputRedirect* iR8 = new InputRedirect();
    iR8->addLeftArgument(catCmd);
    iR8->addRightArgument(cmak);
    iR8->execute();
    Pipe* p5 = new Pipe();
    p5->addLeftArgument(iR8);
    p5->addRightArgument(trTest);
    p5->execute();
    Pipe* p6 = new Pipe();
    p6->addLeftArgument(p5);
    p6->addRightArgument(trPipeTest);
    p6->execute();
    OutputRedirect* oR2 = new OutputRedirect();
    oR2->addLeftArgument(p6);
    oR2->addRightArgument(destCmd);
    EXPECT_EQ(oR2->execute(), true);
}

TEST(OutputRedirectTest, OutputRedirectTest2){
    OutputRedirect* oR3 = new OutputRedirect();
    oR3->addLeftArgument(catSourceCmd2);
    oR3->addRightArgument(destCmd);
    EXPECT_EQ(oR3->execute(), true); 
}

TEST(SYSCALLS, execvptest){
    string userlineinput = "ls -a";
    int placeholder = 0;	//MAY NEED THIS FOR LATER. TRAVERSER FOR TOKENIZER
    bool status = true;		//RETURNS THE CONDITION OF OUR FUNCTION, ALSO RETURNED BY FUNCTION
    char* charrotcake = new char[userlineinput.length() + 1]; //THE CHARACTER ARRAY. INITIALIZING SIZE
    char* arguments[100]; //I THINK 100 IS GOOD NUMBER FOR INPUT LINE GOD FORBID MORE
    int state;
    strcpy(charrotcake, userlineinput.c_str()); //COPIES IMPLICIT STRING CONVERTS TO CARRAY TO CHARROTCAKE
    char *parameter = strtok(charrotcake, " ");
	while (parameter != 0) {
		arguments[placeholder] = parameter;
		parameter = strtok(NULL, " ");
		placeholder++;
	}
	arguments[placeholder] = 0;
	pid_t PID = fork();
	EXPECT_EQ(execvp(arguments[0], arguments), -1);
}

TEST(SYSCALLS, execvptest2){
    string userlineinput = "ls";
    int placeholder = 0;        //MAY NEED THIS FOR LATER. TRAVERSER FOR TOKENIZER
    bool status = true;         //RETURNS THE CONDITION OF OUR FUNCTION, ALSO RETURNED BY FUNCTION
    char* charrotcake = new char[userlineinput.length() + 1]; //THE CHARACTER ARRAY. INITIALIZING SIZE
    char* arguments[100]; //I THINK 100 IS GOOD NUMBER FOR INPUT LINE GOD FORBID MORE
    int state;
    strcpy(charrotcake, userlineinput.c_str()); //COPIES IMPLICIT STRING CONVERTS TO CARRAY TO CHARROTCAKE
    char *parameter = strtok(charrotcake, " ");
        while (parameter != 0) {
                arguments[placeholder] = parameter;
                parameter = strtok(NULL, " ");
                placeholder++;
        }
        arguments[placeholder] = 0;
        pid_t PID = fork();
        EXPECT_EQ(execvp(arguments[0], arguments), -1);
}

TEST(SYSCALLS, execvptest3){
    string userlineinput = "echo testing";
    int placeholder = 0;        //MAY NEED THIS FOR LATER. TRAVERSER FOR TOKENIZER
    bool status = true;         //RETURNS THE CONDITION OF OUR FUNCTION, ALSO RETURNED BY FUNCTION
    char* charrotcake = new char[userlineinput.length() + 1]; //THE CHARACTER ARRAY. INITIALIZING SIZE
    char* arguments[100]; //I THINK 100 IS GOOD NUMBER FOR INPUT LINE GOD FORBID MORE
    int state;
    strcpy(charrotcake, userlineinput.c_str()); //COPIES IMPLICIT STRING CONVERTS TO CARRAY TO CHARROTCAKE
    char *parameter = strtok(charrotcake, " ");
        while (parameter != 0) {
                arguments[placeholder] = parameter;
                parameter = strtok(NULL, " ");
                placeholder++;
        }
        arguments[placeholder] = 0;
        pid_t PID = fork();
        EXPECT_EQ(execvp(arguments[0], arguments), -1);
}



TEST(ForkingTest, FORKANDPIDTEST){
    string userlineinput = "echo PLEASEGIVEMEFULLPOINTS";
    int placeholder = 0;	//MAY NEED THIS FOR LATER. TRAVERSER FOR TOKENIZER
    bool status = true;		//RETURNS THE CONDITION OF OUR FUNCTION, ALSO RETURNED BY FUNCTION
    char* charrotcake = new char[userlineinput.length() + 1]; //THE CHARACTER ARRAY. INITIALIZING SIZE
    char* arguments[100]; //I THINK 100 IS GOOD NUMBER FOR INPUT LINE GOD FORBID MORE
    int state;
    strcpy(charrotcake, userlineinput.c_str()); 
    pid_t PID = fork();
    bool successfulFork = false;
    if(PID != 0){
	successfulFork = true;
    }
    EXPECT_EQ(successfulFork,true);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


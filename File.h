#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class File {
	private:
		string fileName;
		string fileFullPath;
		string currentPath;
		string exeCreator = "BatToExe.exe";
		string exeEmulator = "ePSXe.exe";
		string exeEmulator2 = "pcsx2.exe";
		string batFileName;
	public:
		File(string filepath,string currentDir);
		int createEXE();
		int createBAT();
		int createBAT2();
		bool exists(char* filename);
		void showCurrentPath(){cout << "\n\nCurrentPath: " << currentPath << "\n";};
		void showFileName(){cout << "FileName: " << fileName << "\n";};
		void showFilePath(){cout << "FileFullPath: " << fileFullPath << "\n";};
};

File::File(string filepath,string currentDir){
    string::size_type pos1 = string(filepath).find_last_of("\\/");
    string::size_type pos2 = string(filepath).find_last_of(".");
	fileFullPath = filepath;
	fileName = string(filepath).substr(pos1+1,pos2-pos1-1);
	currentPath = string(currentDir).substr(0,string(currentDir).find_last_of("\\/"));
	File::showCurrentPath();
	File::showFileName();
	File::showFilePath();
}

int File::createEXE(){
	string commandLine = "\"\""+currentPath+"\\"+exeCreator+"\" -bat \""+batFileName+"\" -save \""+fileName+".exe\" -invisible\"";
	system(commandLine.c_str());
	cout << commandLine << "\n";
	commandLine = "del /Q \""+batFileName+"\"";
	system(commandLine.c_str());
	return(0);
}

int File::createBAT(){
	ofstream myfile;
	string commandLine = "\""+currentPath+"\\"+exeEmulator+"\"";
	/*
	char* response;
	cout << "\nEl juego " << fileName << " requiere cambios de CD in-game? (s|n)";
	cin >> response;
	while(response[0]!='s'&&response[0]!='S'&&response[0]!='n'&&response[0]!='N'){
		cout << "\nEl juego requiere cambios de CD in-game? Responda s o n)";
		cin >> response;
	}
	if(response[0]=='n'||response[0]=='N'){
		commandLine += " -nogui";
	}
	*/
	commandLine += " -nogui -loadbin \""+fileFullPath+"\" -loadmemc0 \"memCard1.mcr\" -loadmemc1 \"memCard2.mcr\"\n";
	cout << commandLine;
	batFileName = fileName+".bat";
  	myfile.open(batFileName.c_str());
  	myfile << "@echo off\n" << commandLine << "\n";
	myfile.close();
	return(0);
}

int File::createBAT2(){
	ofstream myfile;
	string commandLine = "\""+currentPath+"\\"+exeEmulator2+"\"";
	commandLine += " --fullscreen --nogui \""+fileFullPath+"\"\n";
	cout << commandLine;
	batFileName = fileName+".bat";
  	myfile.open(batFileName.c_str());
  	myfile << "@echo off\n" << commandLine << "\n";
	myfile.close();
	return(0);
}

bool File::exists(char* filename){
	cout << "Archivo " << filename << ".....";
	string fullpath = currentPath+"\\"+filename;
	ifstream infile(fullpath.c_str());
	/*
	if(infile.good()){
		cout << "FOUND\n";
	}else{
		cout << "NOT FOUND\n";
	}
	*/
	return infile.good();
}

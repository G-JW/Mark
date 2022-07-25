#pragma once
#include <vector>
#include <string>
#include <time.h>

using std::vector;
using std::string;

class Note
{
private:
	string label;
	string name;
	string content;
	int score;
	time_t createTime;
public:
	inline static const string ROOT_FOLDER_NAME = "Mark";
	inline static const string NOTE_FOLDER_NAME = "Notes";
	inline static const string CONFIG_TXT_NAME = "config.txt";
	inline static const string CONFIG_PATH = ROOT_FOLDER_NAME + "\\" + CONFIG_TXT_NAME;
	inline static vector<string> labels;
	inline static vector<string> names;
	static string getPath(string noteName);
	static void createConfig();
	static void readConfig();
	static void saveConfig();
	static void printConfig();
	static void createLabel();
	static void removeLabel(int index);
	static void printLabel();
	static void removeNote(int index);
	Note();
	Note(string label, string name, string content, int score);
	void set(string label, string name, string content, int score);
	void read(string);
	void save();
	void print();
};
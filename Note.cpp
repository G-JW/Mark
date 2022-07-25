#include "Note.h"
#include <iostream>
#include <direct.h>
#include <fstream>
#include <time.h>

using std::ofstream;
using std::ifstream;
using std::ios;
using std::cin;
using std::cout;
using std::endl;

inline string Note::getPath(string noteName)
{
	return ROOT_FOLDER_NAME + "\\" + NOTE_FOLDER_NAME + "\\" + noteName + ".txt";
}

void Note::createConfig()
{
	int dustbin;
	dustbin = _mkdir(ROOT_FOLDER_NAME.c_str());
	dustbin = _mkdir((ROOT_FOLDER_NAME + "\\" + NOTE_FOLDER_NAME).c_str());
	saveConfig();
}

void Note::readConfig()
{
	ifstream config;
	config.open(CONFIG_PATH, ios::in);
	int i;
	string buffer;
	config >> i;
	while (i--) {
		config >> buffer;
		labels.push_back(buffer);
	}
	config >> i;
	while (i--) {
		config >> buffer;
		names.push_back(buffer);
	}
}

void Note::saveConfig()
{
	ofstream config;
	config.open(CONFIG_PATH, ios::out);
	config << labels.size() << endl;;
	for (string i : labels)
		config << i << ' ';
	config << endl;
	config << names.size() << endl;
	for (string i : names)
		config << i << ' ';
	config << endl;
}

void Note::printConfig()
{
	cout << labels.size() << " label:" << endl;
	for (string i : labels)
		cout << i << ' ';
	cout << endl;
	cout << names.size() << " notes:" << endl;
	for (string i : names)
		cout << i << ' ';
	cout << endl;
}

void Note::createLabel()
{
	string temp;
	cin >> temp;
	labels.push_back(temp);
}

void Note::removeLabel(int index)
{
	Note::labels.erase(Note::labels.begin() + index);
}

void Note::printLabel()
{
	cout << labels.size() << " label:" << endl;
	for (int i = 0; i < labels.size(); ++i)
		cout << i + 1 << '-' << labels[i] << ' ';
	cout << endl;
}

void Note::removeNote(int index)
{
	if (remove(getPath(names[index]).c_str()) == 0) {
		cout << "³É¹¦É¾³ý" << names[index] << endl;
		Note::names.erase(Note::names.begin() + index);
	}
}

Note::Note()
{
	label = "defaultLabel";
	name = "defaultName";
	content = "defaultContent";
	score = 0;
	time(&createTime);
}

Note::Note(string label, string name, string content, int score)
{
	this->label = label;
	this->name = name;
	this->content = content;
	this->score = score;
	time(&createTime);
}

void Note::set(string label, string name, string content, int score)
{
	this->label = label;
	this->name = name;
	this->content = content;
	this->score = score;
	time(&createTime);
}

void Note::read(string name)
{
	ifstream note;
	note.open(getPath(name), ios::in);
	note >> this->name >> label >> score >> createTime;
	string temp;
	content = "";
	note.get();
	getline(note, temp);
	while (temp.size() != 0) {
		content += temp + '\n';
		getline(note, temp);
	}
}

void Note::save()
{
	names.push_back(name);
	ofstream note;
	note.open(getPath(name), ios::out);
	note << name << ' ' << label << ' ' << score << ' ' << createTime << '\n' << content;
}

void Note::print()
{
	cout << name << ' ' << label << ' ' << score << endl;
	cout << content;
}

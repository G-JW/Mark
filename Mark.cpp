#include <iostream>
#include <io.h>
#include <conio.h>
#include "Note.h"

using std::cin;
using std::cout;
using std::endl;

void init();
void addNote();
void removeNote();
void printNote();
void config();

int main()
{
	int buffer;
	init();
	while (1) {
		system("cls");//清屏
		cout << "按0退出" << endl
			<< "按1添加Note" << endl
			<< "按2删除Note" << endl
			<< "按3查看Note" << endl
			<< "按4进行设置" << endl;
		buffer = _getch();//无需回车即可读入
		switch (buffer) {
		case '1':
			addNote();
			continue;
		case '2':
			removeNote();
			continue;
		case '3':
			printNote();
			continue;
		case '4':
			config();
			continue;
		case '0':
		default:
			Note::saveConfig();
			return 0;
		}
	}
}

void init()
{
	if (_access(Note::ROOT_FOLDER_NAME.c_str(), 0) == 0) {
		cout << "存在根文件" << endl;
		Note::readConfig();
	}
	else if (_access(Note::ROOT_FOLDER_NAME.c_str(), 0) == -1) {
		cout << "不存在根文件" << endl;
		Note::createConfig();
	}
}

void addNote()
{
	int score;
	string tempName, tempContent, tempLabel, tempString;
	Note tempNote;
	system("cls");
	//输入类别
	Note::printLabel();
	cout << "请选择Label：";
	cin >> score;
	if (score > 0 && score <= Note::labels.size())
		tempLabel = Note::labels[score - 1];
	else {
		cout << "该Label不存在";
		_getch();
		return;
	}
	//输入标题
	cout << "请输入标题：";
	cin >> tempName;
	//输入正文
	cout << "请输入正文（以空行为结尾）" << endl;
	cin.get();
	getline(cin, tempString);
	while (tempString.size() != 0) {
		tempContent += tempString + '\n';
		getline(cin, tempString);
	}
	//输入评分
	cout << "请输入评分（0-10）：";
	cin >> score;
	//保存
	tempNote.set(tempLabel, tempName, tempContent, score);
	tempNote.save();
	return;
}

void removeNote()
{
	int buffer;
	system("cls");
	if (Note::names.size() > 0) {
		for (int i = 0; i < Note::names.size(); ++i)
			cout << i + 1 << '-' << Note::names[i] << endl;
		cout << "请选择Note：";
		cin >> buffer;
		system("cls");
		if (buffer > 0 && buffer <= Note::names.size()) {
			Note::removeNote(buffer - 1);
		}
		else
			cout << "该Note不存在" << endl;
	}
	else
		cout << "无可用Note" << endl;
	_getch();
	return;
}

void printNote()
{
	int buffer;
	Note tempNote;
	system("cls");
	if (Note::names.size() > 0) {
		for (int i = 0; i < Note::names.size(); ++i)
			cout << i + 1 << '-' << Note::names[i] << endl;
		cout << "请选择Note：";
		cin >> buffer;
		system("cls");
		if (buffer > 0 && buffer <= Note::names.size()) {
			tempNote.read(Note::names[buffer - 1]);
			tempNote.print();
		}
		else
			cout << "该Note不存在" << endl;
	}
	else
		cout << "无可用Note" << endl;
	_getch();
	return;
}

void config()
{
	int buffer;
	while (1) {
		system("cls");
		cout << "按0退出" << endl
			<< "按1添加标签" << endl
			<< "按2查看标签" << endl
			<< "按3删除标签" << endl;
		buffer = _getch();
		switch (buffer) {
		case '1':
			system("cls");
			cout << "请输入类别名：";
			Note::createLabel();
			continue;
		case '2':
			system("cls");
			Note::printLabel();
			_getch();
			continue;
		case '3':
			system("cls");
			if (Note::labels.size() > 0) {
				Note::printLabel();
				cout << "请输入要删除Label的编号：";
				cin >> buffer;
				if (buffer > 0 && buffer <= Note::labels.size()) {
					Note::removeLabel(buffer - 1);
					cout << "删除成功" << endl;
				}
				else
					cout << "删除失败" << endl;
			}
			else {
				cout << "无可删除类别" << endl;
			}
			_getch();
			continue;
		case '0':
		default:
			return;
		}
	}
}
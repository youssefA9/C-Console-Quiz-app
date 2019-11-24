#include <iostream>
#include<cstring>
#include<string>
#include<fstream>
#include <iomanip>
#include <stdlib.h>
#include<time.h>

using namespace std;
string name = "USER";

char program();
int admin();
//  options function
char options() {
	char choice;
	cout << endl;
	cout << "Welcome " << name << ", please choose from the following options:" << endl;
	cout << "[1] Go to administration menu" << endl;
	cout << "[2] update your name" << endl;
	cout << "[3] start a new quiz" << endl;
	cout << "[4] Display your scores statistics" << endl;
	cout << "[5] Display all your scores" << endl;
	cout << "[6] Exit" << endl;

	cin >> choice;
	while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6') {
		cout << "Invalid input, please enter one of the choices " << endl;
		cin >> choice;
	}
	return choice;
}

//administration function
int adminfunction() {
	char choice;
	cout << endl;
	cout << "Welcome to the administration menu, please choose from the following options" << endl;
	cout << "[1] View all questions" << endl;
	cout << "[2] add new question" << endl;
	cout << "[3] load questions from file" << endl;
	cout << "[4] Go back to main menu" << endl;
	cin >> choice;
	while (choice != '1' && choice != '2' && choice != '3' && choice != '4') {
		cout << "Invalid input, please enter one of the choices " << endl;
		cin >> choice;
	}
	return choice;
}

//Counting the number of lines that the file contains
int countques(fstream &file) {
	string line;
	int file_counter = 0, num = 0;
	while (getline(file, line)) {
		file_counter++;
		if (((file_counter - 1) % 5 == 0) || (file_counter == 1)) {
			num++;
		}
		if (file.eof())
			break;
	}
	return num;
}

//Print Answers
void print_answ(int x, int& y, string& sent) {
	int ans_num = 0;
	if ((x - 1) % 5 != 0) {//
		char z;
		switch (y) {
		case 0:
			z = 'a';
			break;
		case 1:
			z = 'b';
			break;
		case 2:
			z = 'c';
			break;
		case 3:
			z = 'd';
			break;
		}
		if (y == 0)
			cout << setw(5) << "[" << z << "] *" << sent;
		else
			cout << setw(5) << "[" << z << "]" << sent;
		y++;
		if (z == 'd') {
			cout << endl;
		}
		ans_num++;
		if (ans_num % 4 == 0)cout << endl;
	}
}

//Printing Questions & Answers
void printall(fstream &file) {
	int count = 0, ques_num = 1, ans_letter = 0;
	string line;

	while (file) {
		//Printing Questions
		count++;
		getline(file, line);
		if (((count - 1) % 5 == 0) || (count == 1)) {
			if (!file.eof()) {
				cout << endl << "[" << ques_num << "]" << line << endl;
				ques_num++;
				ans_letter = 0;
			}
		}
		//Printing answer
		print_answ(count, ans_letter,line);
		
		if (file.eof())
			break;
	}
}

//Copy file to another file
void copy(fstream& file, fstream& filx) {
	string line;
	
	while (filx)
	{
		getline(filx, line);
		file << line;
		if (filx.eof()) { break; }
		else file << endl;
	}

}

//Deleting Question
void del(fstream &file,int x,int del) {
	string line;
	fstream temp;
	temp.open("Temp.txt", ios_base::in | ios_base::out | ios_base::trunc);


	for (int i = 1; i < x * 5 + 1; i++) {
		if (i >= del && i <= del + 4) {
			getline(file, line);
		}
		else {
			getline(file, line);
			temp << line;
			if (file.eof()) { break; }
			else temp << endl;
		}
	}
	temp.clear();
	temp.seekp(0, ios::beg);
	file.close();
	file.open("bamboozle.txt", ios_base::in | ios_base::out | ios_base::trunc);
	copy(file, temp);
}

//Enter a new Question
void new_ques(fstream& file,string dest) {
	int space_handler = 0;
	string line;
	file.clear();
	file.seekp(0, SEEK_END);
	if (space_handler == 0)
		file << endl;
	space_handler++;
	cout << "Enter your Question" << endl;
	cin.ignore();
	if (dest != "bamboozle.txt")
		cout << endl;
	file.clear();
	file.seekp(0, SEEK_END);
	getline(cin, line);
	file << line << endl;
	for (int i = 0; i <= 3; i++) {
		if (i == 0)
			cout << "Please Enter the correct answer" << endl;
		else
			cout << "Please Enter your Answer" << endl;
		getline(cin, line);
		file << line;
		if (i < 4)	file << endl;
	}
}

int main()
{
	char program;
	int del_num = 0;
	string newname;
	program = options();

	string line;
	fstream orig_file;
	fstream exe_file;
	string dest="bamboozle.txt";
	exe_file.open(dest, ios_base::in | ios_base::out | ios_base::trunc);
	int score = 0, high = 0, low = 10, num_quz = 0, R_keeper = 0;
	int ri[100], wr[100], s[100];

	//starting the console
	while (program != '6' && program > '0' && program < '6') {
		int count = 0, numOfQues = 0, y = 0, qes_num = 1, ans_num = 0, ans_letter = 0, Rnd, counter, k, right = 0, wrong = 0, Checker = 1, to = 5, ques_ans = 0, rnd = 0, checker = 1, r_keeper = 0;
		int Randcount[5] = { 0 }, randcount[4] = { 0 };
		float aver = 0.0, total_score = 0;
		char answ,choicy;
		string choice[4];
		string ri_answ;
		orig_file.open("exam_questions.txt");
		
		//Loading a new file
		if (dest != "bamboozle.txt") {
			exe_file.open(dest);
		}

		//Copying the txt from the original file to the exectuted file
		else {
			copy(exe_file, orig_file);
		}

		//Reset the fp to the begining
		exe_file.clear();
		exe_file.seekg(0, ios::beg);
		
		//Counting the number of lines that the file contains
		numOfQues = countques(exe_file);
		
		switch (program) {
		case '1':
		//Entering administration options

			char admin;
			admin = adminfunction();
			exe_file.clear();
			exe_file.seekg(0, ios::beg);
			switch (admin) {

			case '1':
			refre1:
				qes_num = 1;
				exe_file.clear();
				exe_file.seekg(0, ios::beg);
				numOfQues = 0;
				
				//Counting Number of questions
				numOfQues = countques(exe_file);
				
				exe_file.clear();
				exe_file.seekg(0, ios::beg);
				cout << "Number of questions available : " << numOfQues << endl;
				cout << "Questions list : " << endl;
				cout << "==========================" << endl;
				
				printall(exe_file);

				cout <<endl<< "=================================================================================" << endl;
				cout << "Press [d] and the question ID if you want to delete a question (Example: d 2)" << endl;
				cout << "press [b] if you want to go back to the main menu" << endl;
				// Deleting
				cin>>choicy;
				while (choicy != 'b' && choicy != 'd') {
					cout << "invalid input, please enter [b] to go back or [d] and question ID to delete a question" << endl;
					cin >> choicy;
					
				}
				if (choicy == 'b')
					break;
				else if (choicy == 'd') {

					cin >> del_num;
					del_num = (del_num * 5) - 4;
					exe_file.clear();
					exe_file.seekp(0, ios::beg);
					if (numOfQues == 5) {
						cout << "Can't delete more questions (Min: 5 Questions Remaining)" << endl;
						goto retr;
					}
					
					del(exe_file, numOfQues, del_num);
					
					goto refre1;
				}
				break;
			
			case '2':
			insrt:
				new_ques(exe_file, dest);
				break;
			
			case '3':
				cout << "Enter the destination of the new file" << endl;
				cin.ignore();
				getline(cin, dest);
				orig_file.close();
				exe_file.close();
				break;
			
			case '4':
				break;
			}
			break;

		case '2':

			cout << "Enter your name" << endl;
			cin.ignore();
			getline(cin, newname);
			name.replace(0, name.length(), newname);
			break;

		case '3':
			if (numOfQues < 5) {
				cout << "Enter at least " << 5 - numOfQues << " to get to start new Quiz" << endl;
				goto insrt;
			}

			R_keeper = 0;
			exe_file.clear();
			exe_file.seekp(0, ios::beg);
			score = 0;
			counter = 1;
			num_quz++;
			k = 1;

			for (int ix = 0; ix < 5; ix++) {
				for (int i = 0; i < 4; i++)
					randcount[i] = 0;
				r_keeper = 0;
				do
				{
					//Randomizing the Questions
					if (numOfQues < 5)
						to = numOfQues;
					srand(time(NULL));
					Rnd = 0;
					Rnd = 1 + rand() % numOfQues;
					for (int i = 0; i < 5; i++) {
						//Checking the previous Questions
						if (Rnd == Randcount[i]) {
							Checker = 0;
							break;
						}
						else {
							Checker = 1;
						}
					}
					if (Checker == 1) {
						Randcount[R_keeper] = Rnd;
						R_keeper++;
					}
					Rnd = (Rnd * 5) - 4;


				} while (Checker == 0);

				exe_file.clear();
				exe_file.seekp(0, ios::beg);
				for (int i = 1; i < numOfQues * 5 + 1; i++) {
					if (i == Rnd) {
						getline(exe_file, line);
						cout << endl << "[" << k << "]" << line << endl;

						for (int i = 0; i < 4; i++) {
							exe_file.clear();
							exe_file.seekp(0, ios::beg);

							//Randomizing the answers
							do
							{
								rnd = 0;
								rnd = (1 + rand() % 4);

								//Checking the random of the answers
								for (int i = 0; i < 4; i++) {
									if (rnd == randcount[i]) {

										checker = 0;
										break;
									}
									else {
										checker = 1;

									}
								}
								if (checker == 1) {
									randcount[r_keeper] = rnd;
									r_keeper++;
									rnd = rnd + (Rnd);
								}

							} while (checker == 0);

							for (int i = 1; i < numOfQues * 5 + 1; i++) {
								if (i == rnd) {
									getline(exe_file, line);
									break;
								}
								else
									getline(exe_file, line);
							}

							char y;
							switch (i) {
							case 0:
								y = 'a';
								choice[i] = line;
								break;
							case 1:
								y = 'b';
								choice[i] = line;
								break;
							case 2:
								y = 'c';
								choice[i] = line;
								break;
							case 3:
								y = 'd';
								choice[i] = line;
								break;
							}
							cout << setw(5) << "[" << y << "]" << line;
							exe_file.clear();
							exe_file.seekp(0, ios::beg);

						}
						counter++;
						k++;
						cout << endl;

						while (true) {
							cout << "Enter your choice:   ";
							cin >> answ;
							if (answ == 'a') {
								ques_ans = 0;
								break;
							}
							else if (answ == 'b') {
								ques_ans = 1;
								break;
							}
							else if (answ == 'c') {
								ques_ans = 2;
								break;
							}
							else if (answ == 'd') {
								ques_ans = 3;
								break;
							}
							cout << "Please Enter a Valid letter" << endl;
						}
						exe_file.clear();
						exe_file.seekp(0, ios::beg);
						for (int i = 0; i < numOfQues * 5 - 1; i++) {
							if (i == Rnd) {
								getline(exe_file, ri_answ);
								break;
							}
							else
								getline(exe_file, ri_answ);
						}

						if (choice[ques_ans] == ri_answ) {
							score = score + 2;
							right = right + 1;
						}
						else { wrong = wrong + 1; }
					}
					if (counter == 6) {
						break;
					}
					else {
						getline(exe_file, line);
					}
				}
				
			}
			
			//Evaluating the score
			for (int i = 0; i < num_quz; i++) {
				if (i + 1 == num_quz) {
					ri[i] = right;
					wr[i] = wrong;
					s[i] = score;
				}
			}
			//The highest and the lowest Score
		case '4':
			char mychoice;

			if (score > high)
				high = score;
			if (score < low)
				low = score;
			//Calculating the Average
			for (int i = 0; i < num_quz; i++) {
				total_score += s[i];
			}
			
			aver = total_score / num_quz;

			if (program == '4') {
				cout << "Your score statistics: " << endl;
				cout << setw(5) << "-" << " Number of Quizzes taken: " << num_quz << endl;
				cout << setw(5) << "-" << " Highest score: " << high << "/10" << endl;
				cout << setw(5) << "-" << " Lowest score: " << low << "/10" << endl;
				cout << setw(5) << "-" << " Average score: " << fixed << setprecision(1) << aver << "/10" << endl;
				cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
				cout << "Mychoice: ";
				cin >> mychoice;
				while (mychoice != 'e' && mychoice != 'b') {
					cout << "Invalid input, please enter [b] to go back or [e] to exit" << endl;
					cin >> mychoice;
				}

				if (mychoice == 'e')
					return 0;
				else if (mychoice == 'b')
					break;
			}
			//Shows the statistics of each Quiz
		case '5':
			if (program == '5') {
				cout << "The total number of Quizzes: " << num_quz << endl;

				for (int i = 0; i < num_quz; i++) {
					cout << "Quiz " << i + 1 << ": " << endl;
					cout << "===============" << endl;
					cout << "Number of right answers: " << ri[i] << endl;
					cout << "Number of wrong answers: " << wr[i] << endl;
					cout << "Score of quiz " << i + 1 << ": " << s[i] << endl;
					cout << "\n";
				}
			}
}
	retr:
		program = options();
	}
	orig_file.close();
	exe_file.close();
}

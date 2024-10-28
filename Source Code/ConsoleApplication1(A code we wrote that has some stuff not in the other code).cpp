#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void getOffset(string&, int&);

void print(int*, int, bool);

void ADD(int*, int*, int*);

void ADDI(int*, int*, int);

void NAND(int*, int*, int*);

void DIV(int*, int*, int*);

bool BNE(int*, int*);

void LOAD(int*, int*, int);

void STORE(int*, int*, int);

int main() {

	int pc = 0, offset = 0, memory[1024] = { 0 };

	int* R0, * R1, * R2, * R3, * R4, * R5, * R6, * R7, * rd, * rs1, * rs2, * m = &memory[0];

	bool R0Flag = false, R1Flag = false, R2Flag = false, R3Flag = false, R4Flag = false, R5Flag = false, R6Flag = false, R7Flag = false;

	R0 = new int;
	*R0 = 0;
	R0Flag = true;

	R1 = new int;
	R2 = new int;
	R3 = new int;
	R4 = new int;
	R5 = new int;
	R6 = new int;
	R7 = new int;

	rd = nullptr;
	rs1 = nullptr;
	rs2 = nullptr;

	string instruction, rdTemp, rs1Temp, rs2Temp, immediate, label, temp;

	ifstream textFile;

	cout << "Registers before implementing the instructions:\n";
	print(R0, 0, R0Flag);
	print(R1, 1, R1Flag);
	print(R2, 2, R2Flag);
	print(R3, 3, R3Flag);
	print(R4, 4, R4Flag);
	print(R5, 5, R5Flag);
	print(R6, 6, R6Flag);
	print(R7, 7, R7Flag);
	cout << endl;

	textFile.open("testCase.txt");
	if (textFile.is_open()) {
		while (!textFile.eof()) {

			textFile >> temp;

			if ((temp == "ADD") || (temp == "ADDI") || (temp == "BNE") || (temp == "LOAD") || (temp == "STORE") || (temp == "DIV") || (temp == "NAND"))
				instruction = temp;
			else
				textFile >> instruction;

			textFile >> rdTemp;
			textFile >> rs1Temp;

			if ((instruction == "ADD") || (instruction == "DIV") || (instruction == "NAND"))
				textFile >> rs2Temp;

			else if ((instruction == "ADDI"))
				textFile >> immediate;

			else if ((instruction == "BNE"))
				textFile >> label;

			if ((rdTemp == "R0,") && (instruction != "BNE")) {
				cout << "You can not change the value of the saved register R0.\n";
				return 0;
			}
			else if (rdTemp == "R1,") {
				rd = R1;
				R1Flag = true;
			}
			else if (rdTemp == "R2,") {
				rd = R2;
				R2Flag = true;
			}
			else if (rdTemp == "R3,") {
				rd = R3;
				R3Flag = true;
			}
			else if (rdTemp == "R4,") {
				rd = R4;
				R4Flag = true;
			}
			else if (rdTemp == "R5,") {
				rd = R5;
				R5Flag = true;
			}
			else if (rdTemp == "R6,") {
				rd = R6;
				R6Flag = true;
			}
			else if (rdTemp == "R7,") {
				rd = R7;
				R7Flag = true;
			}

			if (instruction == "LOAD") {
				getOffset(rs1Temp, offset);
				if (rs1Temp == "R0")
					rs1 = R0;
				else if (rs1Temp == "R1")
					rs1 = R1;
				else if (rs1Temp == "R2")
					rs1 = R2;
				else if (rs1Temp == "R3")
					rs1 = R3;
				else if (rs1Temp == "R4")
					rs1 = R4;
				else if (rs1Temp == "R5")
					rs1 = R5;
				else if (rs1Temp == "R6")
					rs1 = R6;
				else if (rs1Temp == "R7")
					rs1 = R7;
				else if (rs1Temp == "m")
					rs1 = m;
			}

			if (rs1Temp == "R0,")
				rs1 = R0;
			else if (rs1Temp == "R1,")
				rs1 = R1;
			else if (rs1Temp == "R2,")
				rs1 = R2;
			else if (rs1Temp == "R3,")
				rs1 = R3;
			else if (rs1Temp == "R4,")
				rs1 = R4;
			else if (rs1Temp == "R5,")
				rs1 = R5;
			else if (rs1Temp == "R6,")
				rs1 = R6;
			else if (rs1Temp == "R7,")
				rs1 = R7;
			else if (rs1Temp == "m,")
				rs1 = m;

			if ((instruction == "ADD") || (instruction == "NAND") || (instruction == "DIV")) {

				if (rs2Temp == "R0")
					rs2 = R0;
				else if (rs2Temp == "R1")
					rs2 = R1;
				else if (rs2Temp == "R2")
					rs2 = R2;
				else if (rs2Temp == "R3")
					rs2 = R3;
				else if (rs2Temp == "R4")
					rs2 = R4;
				else if (rs2Temp == "R5")
					rs2 = R5;
				else if (rs2Temp == "R6")
					rs2 = R6;
				else if (rs2Temp == "R7")
					rs2 = R7;
				else if (rs2Temp == "m")
					rs2 = m;
			}

			if (instruction == "ADD")
				ADD(rd, rs1, rs2);

			else if (instruction == "NAND")
				NAND(rd, rs1, rs2);

			else if (instruction == "DIV")
				DIV(rd, rs1, rs2);

			else if (instruction == "ADDI")
				ADDI(rd, rs1, stoi(immediate));

			else if (instruction == "BNE") {
				if (BNE(rd, rs1) == true) {
					textFile.clear();
					textFile.seekg(0);
					string BNETemporary;
					while (BNETemporary != (label + ":"))
						textFile >> BNETemporary;
				}
			}

			else if (instruction == "LOAD")
				LOAD(rd, rs1, offset);

			else if (instruction == "STORE")
				STORE(rs1, rd, offset);

			else
				break;
		}
	}
	else
		cout << "File does not exists\n";

	cout << "Registers after implementing the instructions:\n";
	print(R0, 0, R0Flag);
	print(R1, 1, R1Flag);
	print(R2, 2, R2Flag);
	print(R3, 3, R3Flag);
	print(R4, 4, R4Flag);
	print(R5, 5, R5Flag);
	print(R6, 6, R6Flag);
	print(R7, 7, R7Flag);
	cout << endl;

	system("pause");
	return 0;
}
void getOffset(string& rs1Temp, int& offset) {
	int imm_start = rs1Temp.find("(");
	int imm_end = rs1Temp.find(")");
	offset = stoi(rs1Temp.substr(0, imm_start));
	rs1Temp = rs1Temp.substr(imm_start + 1, imm_end - imm_start - 1);
}
void print(int* x, int y, bool f) {
	if (f == false)
		cout << "R" << y << " is not yet initialized.\n";

	else {
		cout << "R" << y << " =\n" << "Decimal: " << *x << "\n";

		if (*x == 0)
			cout << "Binary: 0\n";

		else {
			int decimal = *x, binary = 0, remainder, product = 1;
			while (decimal != 0) {
				remainder = decimal % 2;
				binary = binary + (remainder * product);
				decimal = decimal / 2;
				product *= 10;
			}
			cout << "Binary: " << binary << "\n";
		}

		if (*x == 0)
			cout << "Hexadecimal: 0\n";

		else {
			string hexadecimal = "";
			int n = *x;
			while (n != 0) {
				int r = 0;
				char c;
				r = n % 16;
				if (r < 10)
					c = r + 48;
				else
					c = r + 55;
				hexadecimal += c;
				n = n / 16;
			}
			int i = 0, j = hexadecimal.size() - 1;
			while (i <= j)
			{
				swap(hexadecimal[i], hexadecimal[j]);
				i++;
				j--;
			}
			cout << "Hexadecimal: " << hexadecimal << "\n";
		}
	}
}
void ADD(int* x, int* y, int* z) {
	*x = *y + *z;
}

void ADDI(int* x, int* y, int z) {
	*x = *y + z;
}

void NAND(int* x, int* y, int* z) {
	*x = !(*y && *z);
}

void DIV(int* x, int* y, int* z) {
	*x = (*y / *z);
}

bool BNE(int* x, int* y) {
	if (*x != *y)
		return true;
	else
		return false;
}

void LOAD(int* rd, int* rs1, int offset) {
	if (offset % 4 != 0) {
		cout << "Error: offset not valid\n";
		return;
	}
	int value = *(rs1 + (offset / 4));
	*rd = value;
}

void STORE(int* rs1, int* rd, int offset) {
	if (offset % 4 != 0) {
		cout << "Error: offset not valid\n";
		return;
	}
	*(rs1 + (offset / 4)) = *rd;
}

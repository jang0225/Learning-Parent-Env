/*
argument에 대한 내용
argc : argument개수, argv : argument 구성 요소 arry 형태
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	cout << "argc = " << argc << endl;
	for (int i = 0; i < argc; i++) {
		cout << "argv[" << i << "]" << argv[i] << endl;
	}
	return 0;
}
*/

/*
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
using namespace std;

void printEnv(const char* name) {
	const char* value = getenv(name);
	cout << name << " = "
		 << (value ? value : "<not set>") << endl;
}

int main() {
	printEnv("PATH");
	printEnv("USERPROFILE");
	printEnv("COURSE_MODE");

	return 0;
}
*/


//이제 환경변수를 직접 가져올 것임

#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <direct.h>
using namespace std;

void runChild(const char* label, const char* cmd) {
	cout << "====" << label << "=====" << endl;
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) {
		cerr << "failed\n"; return;
	}
	char buf[256];

	while (fgets(buf, sizeof(buf), pipe)) {
		cout << "  " << buf;
	}
	cout << "  exit=" << _pclose(pipe) << endl << endl;
}


int main() {
	char exeDir[512];
	_getcwd(exeDir, sizeof(exeDir));

	_putenv_s("COURSE_MODE", "spawned by parent");

	runChild("Env injection", "Test.exe");

	return 0;
}
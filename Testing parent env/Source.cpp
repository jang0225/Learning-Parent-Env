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
	std::cout << "=== " << label << " ===\n";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) { std::cerr << "failed\n"; return; }
	char buf[512];
	while (fgets(buf, sizeof(buf), pipe))
		std::cout << " " << buf;
	std::cout << " exit=" << _pclose(pipe) << "\n\n";
}
int main() {
	char exeDir[512];
	_getcwd(exeDir, sizeof(exeDir)); // x64\Debug
	_putenv_s("COURSE_MODE", "spawned_by_parent"); // 실험 1: 환경 변수 주입
	runChild("Env Injection", "child_exe.exe");
	std::string exePath = std::string(exeDir) + "\\Lab03_Cwd.exe";
	_chdir("C:\Users\ipad0\OneDrive\바탕 화면\2026-1\프방\Testing parent env\x64\Debug");
	runChild("CWD = ProjectDir", exePath.c_str()); // 실험 2: 성공 CWD를 ProjectDir로 바꾸면 성공
		_chdir("C:\\");
	runChild("CWD = C:\\", exePath.c_str()); // 실험 3: CWD를 루트로 바꾸면 실패
	_chdir(exeDir); // 복원
}


int main() {
	char exeDir[512];
	_getcwd(exeDir, sizeof(exeDir));

	_putenv_s("COURSE_MODE", "spawned by parent");

	runChild("Env injection", "Test.exe");

	return 0;
}